#!/bin/bash

# ==============================================================================
# 42 MINISHELL TESTER - AUTOMATED EVALUATION SCRIPT (EVAL SHEET COMPLIANT)
# ==============================================================================

# --- Colors ---
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
RESET='\033[0m'

# --- Configuration ---
MINISHELL="../minishell"
LOG_FILE="diff.log"
VALGRIND_LOG="valgrind_err.log"
USE_VALGRIND=0

# --- Setup & Teardown ---
# 1. Pre-flight Check: Compilation & Norms (Eval Sheet Requirement)
echo -e "${MAGENTA}=== PRE-FLIGHT CHECKS ===${RESET}"
cd ..
if ! make -n | grep -qE -- "-Wall.*-Wextra.*-Werror|-Werror.*-Wall.*-Wextra"; then
    echo -e "${YELLOW}Warning: 'make -n' did not explicitly show -Wall -Wextra -Werror.${RESET}"
else
    echo -e "${GREEN}✓ Compilation flags (-Wall -Wextra -Werror) detected.${RESET}"
fi
cd - > /dev/null

if [ ! -f "$MINISHELL" ]; then
    echo -e "${RED}Error: Executable '$MINISHELL' not found. Please compile first.${RESET}"
    exit 1
fi
echo -e "${GREEN}✓ Minishell executable found.${RESET}\n"

# Clear old log
> "$LOG_FILE"

# Temporary files for stdout/stderr capturing
BASH_OUT=$(mktemp)
BASH_ERR=$(mktemp)
MINI_OUT=$(mktemp)
MINI_ERR=$(mktemp)

cleanup() {
    rm -f "$BASH_OUT" "$BASH_ERR" "$MINI_OUT" "$MINI_ERR" "$VALGRIND_LOG" out*.txt test_*.txt
}
trap cleanup EXIT

# --- Parse Arguments ---
for arg in "$@"; do
    if [ "$arg" == "--valgrind" ]; then
        USE_VALGRIND=1
        echo -e "${BLUE}>>> Valgrind Memory Checking Enabled (Checking for leaks...) <<<${RESET}\n"
    fi
done

# --- Test Runner Function ---
run_test() {
    local cmd="$1"
    local category="$2"
    local test_status=0
    local fail_reason=""

    # 1. Run System Bash
    bash -c "$cmd" > "$BASH_OUT" 2> "$BASH_ERR"
    local bash_exit=$?

    # 2. Run Minishell
    $MINISHELL -c "$cmd" > "$MINI_OUT" 2> "$MINI_ERR"
    local mini_exit=$?

    # 3. Evaluate Stdout
    if ! diff -q "$BASH_OUT" "$MINI_OUT" > /dev/null; then
        test_status=1
        fail_reason+="[STDOUT KO] "
    fi

    # 4. Evaluate Exit Status
    if [ "$bash_exit" -ne "$mini_exit" ]; then
        test_status=1
        fail_reason+="[EXIT $mini_exit != BASH $bash_exit] "
    fi

    # 5. Evaluate Stderr (Presence only, exact string diffs are unfair)
    local bash_has_err=0
    local mini_has_err=0
    [ -s "$BASH_ERR" ] && bash_has_err=1
    [ -s "$MINI_ERR" ] && mini_has_err=1

    if [ "$bash_has_err" -ne "$mini_has_err" ]; then
        test_status=1
        fail_reason+="[STDERR PRESENCE MISMATCH] "
    fi

    # 6. Evaluate Valgrind (If enabled)
    local leaks=0
    if [ $USE_VALGRIND -eq 1 ]; then
        valgrind --leak-check=full --show-leak-kinds=all --log-file="$VALGRIND_LOG" $MINISHELL -c "$cmd" > /dev/null 2>&1
        # Sum definitely lost and indirectly lost bytes
        leaks=$(grep -E "(definitely|indirectly) lost:" "$VALGRIND_LOG" | awk '{print $4}' | sed 's/,//g' | awk '{s+=$1} END {print s}')
        
        if [ -n "$leaks" ] && [ "$leaks" -gt 0 ]; then
            test_status=2 # Specific status for leaks
            fail_reason+="[LEAKS: ${leaks} bytes] "
        fi
    fi

    # 7. Print Result & Log
    # Sanitize newline for printing
    local safe_cmd="${cmd//$'\n'/\\n}"
    printf "%-15s | %-50s | " "[$category]" "${safe_cmd:0:48}"
    
    if [ $test_status -eq 0 ]; then
        echo -e "${GREEN}OK${RESET}"
    elif [ $test_status -eq 2 ]; then
        echo -e "${YELLOW}KO ${fail_reason}${RESET}"
        log_failure "$cmd" "$bash_exit" "$mini_exit"
    else
        echo -e "${RED}KO ${fail_reason}${RESET}"
        log_failure "$cmd" "$bash_exit" "$mini_exit"
    fi
}

log_failure() {
    local cmd="$1"
    local b_exit="$2"
    local m_exit="$3"
    echo "========================================" >> "$LOG_FILE"
    echo "COMMAND: $cmd" >> "$LOG_FILE"
    echo "--- BASH STDOUT ---" >> "$LOG_FILE"
    cat "$BASH_OUT" >> "$LOG_FILE"
    echo "--- MINI STDOUT ---" >> "$LOG_FILE"
    cat "$MINI_OUT" >> "$LOG_FILE"
    echo "--- BASH EXIT: $b_exit | MINI EXIT: $m_exit ---" >> "$LOG_FILE"
    echo "========================================" >> "$LOG_FILE"
    echo "" >> "$LOG_FILE"
}

# ==============================================================================
# TEST SUITES
# ==============================================================================

# --- EVALUATION SHEET SPECIFIC TESTS ---
TESTS_EVAL_SHEET=(
    # Simple Commands & Empty
    "/bin/ls"
    "   "
    "\t"
    " \t \t "
    
    # Arguments
    "/bin/ls -la"
    "/bin/cat Makefile"
    "/bin/echo hello args"

    # Return values ($?)
    "/bin/ls does_not_exist ; echo \$?"
    "/bin/ls ; echo \$?"
    "expr \$? + \$?"
    "echo \$? ; echo \$?"
    
    # Relative Paths
    "../../../../../../../../../../bin/ls"
    "./minishell -c 'echo nested'"
    
    # Environment Paths
    "unset PATH ; ls"
    "export PATH=/bin ; ls"
    "export PATH=/does/not/exist:/bin ; ls"
    
    # Eval Sheet specific quote tests
    "echo \"cat lol.c | cat > lol.c\""
    "echo '\$USER'"
    "echo \"\$USER\""
    
    # Go Crazy / History tests
    "cat | cat | ls"
    "cat /dev/urandom | head -c 1000 | wc -c"
    "dsbksdgbksdghsd"
)

# --- Built-ins ---
TESTS_BUILTIN=(
    # --- ECHO ---
    "echo"
    "echo hello"
    "echo -n hello"
    "echo -n -n -n hello"
    "echo -n-n hello"
    "echo \" -n \" hello"
    "echo ''"
    "echo \"\""
    "echo hello   world"

    # --- PWD ---
    "pwd"
    "pwd ."
    "pwd .."

    # --- CD ---
    "cd /"
    "cd /tmp"
    "cd does_not_exist"
    "cd .."
    "cd ../../"
    "cd \$HOME"

    # --- EXPORT ---
    "export VAR=42"
    "export 1INVALID=42"
    "export =42"
    "export EMPTY="
    "export VAR=\"hello world\""
    "export TEST_VAR=123"

    # --- UNSET ---
    "unset does_not_exist"
    "unset PATH"
    "unset PWD"

    # --- ENV ---
    "env | grep PATH"

    # --- EXIT ---
    "exit"
    "exit 0"
    "exit 42"
    "exit -1"
    "exit abc"
)

# --- Pipes & Redirections ---
TESTS_PIPEREDIR=(
    "cat Makefile | grep a"
    "ls -la | grep d | wc -l"
    "ls | rev | sort | rev"
    "ls > test_out1.txt"
    "> test_out3.txt ls"
    "cat < /etc/passwd"
    "ls >> test_app1.txt"
    "cat < /etc/passwd > test_mix1.txt"
    "ls | grep a > test_pipeout1.txt"
    "cat < /etc/passwd | wc -l"
    "ls | non_existent_cmd"
    "ls>out_space1.txt"
    "ls|cat"
    "cat /dev/null | wc -l"
    "ls | | cat" 
    "ls > > out_syn.txt"
)

# --- Quotes & Expansions ---
TESTS_QUOTES=(
    "echo 'hello'"
    "echo \"hello\""
    "echo '   hello   world   '"
    "echo \"'hello'\""
    "echo '\"hello\"'"
    "echo \"hello '\$USER'\""
    "echo 'hello \"\$USER\"'"
    "echo \"\$USER\""
    "echo \"\$DOES_NOT_EXIST\""
    "echo \$"
    "echo \"\$\""
    "echo hello\"world\""
    "echo \"|\""
    "echo '>'"
    "export VAR=\"hello world\""
)

# ==============================================================================
# EXECUTION
# ==============================================================================

echo -e "${BLUE}=== RUNNING EVALUATION SHEET SPECIFICS ===${RESET}"
for cmd in "${TESTS_EVAL_SHEET[@]}"; do run_test "$cmd" "EVAL SHEET"; done

echo -e "\n${BLUE}=== RUNNING STANDARD BUILT-INS ===${RESET}"
for cmd in "${TESTS_BUILTIN[@]}"; do run_test "$cmd" "BUILT-IN"; done

echo -e "\n${BLUE}=== RUNNING PIPES & REDIRECTIONS ===${RESET}"
for cmd in "${TESTS_PIPEREDIR[@]}"; do run_test "$cmd" "PIPE/REDIR"; done

echo -e "\n${BLUE}=== RUNNING QUOTES & EXPANSIONS ===${RESET}"
for cmd in "${TESTS_QUOTES[@]}"; do run_test "$cmd" "QUOTES/EXP"; done

echo -e "\n${MAGENTA}================================================================${RESET}"
echo -e "${MAGENTA}     AUTOMATED TESTS COMPLETE. CHECK 'diff.log' FOR ERRORS.     ${RESET}"
echo -e "${MAGENTA}================================================================${RESET}"

echo -e "\n${YELLOW}⚠️  MANUAL EVALUATION CHECKLIST (Cannot be automated) ⚠️${RESET}"
echo -e "1. ${GREEN}Signals (Empty Prompt):${RESET} Test Ctrl-C (new line), Ctrl-\\ (nothing), Ctrl-D (exit)."
echo -e "2. ${GREEN}Signals (With Text):${RESET} Type 'echo a', test Ctrl-C (clears line), Ctrl-\\ (nothing), Ctrl-D (nothing)."
echo -e "3. ${GREEN}Signals (Blocking):${RESET} Run 'cat', test Ctrl-C, Ctrl-\\, Ctrl-D."
echo -e "4. ${GREEN}History:${RESET} Press UP/DOWN arrows to navigate history."
echo -e "5. ${GREEN}Heredoc (<<):${RESET} Run 'cat << EOF', type lines, type EOF. Check behavior."
echo -e "6. ${GREEN}Global Variables:${RESET} Ask the student to explain their global variable usage."
echo -e "${YELLOW}================================================================${RESET}\n"