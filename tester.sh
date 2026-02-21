#!/bin/bash

# ==============================================================================
# 42 MINISHELL TESTER - AUTOMATED EVALUATION SCRIPT
# ==============================================================================

# --- Colors ---
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
RESET='\033[0m'

# --- Configuration ---
MINISHELL="./minishell"
LOG_FILE="diff.log"
VALGRIND_LOG="valgrind_err.log"
USE_VALGRIND=0

# --- Setup & Teardown ---
if [ ! -f "$MINISHELL" ]; then
    echo -e "${RED}Error: Executable '$MINISHELL' not found. Please compile first.${RESET}"
    exit 1
fi

# Clear old log
> "$LOG_FILE"

# Temporary files for stdout/stderr capturing
BASH_OUT=$(mktemp)
BASH_ERR=$(mktemp)
MINI_OUT=$(mktemp)
MINI_ERR=$(mktemp)

cleanup() {
    rm -f "$BASH_OUT" "$BASH_ERR" "$MINI_OUT" "$MINI_ERR" "$VALGRIND_LOG" out.txt
}
trap cleanup EXIT

# --- Parse Arguments ---
for arg in "$@"; do
    if [ "$arg" == "--valgrind" ]; then
        USE_VALGRIND=1
        echo -e "${BLUE}>>> Valgrind Memory Checking Enabled <<<${RESET}\n"
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

    # 5. Evaluate Stderr (Presence only)
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
    printf "%-15s | %-50s | " "[$category]" "${cmd:0:48}"
    
    if [ $test_status -eq 0 ]; then
        echo -e "${GREEN}OK${RESET}"
    elif [ $test_status -eq 2 ]; then
        echo -e "${YELLOW}KO ${fail_reason}${RESET}"
        log_failure "$cmd"
    else
        echo -e "${RED}KO ${fail_reason}${RESET}"
        log_failure "$cmd"
    fi
}

log_failure() {
    local cmd="$1"
    echo "========================================" >> "$LOG_FILE"
    echo "COMMAND: $cmd" >> "$LOG_FILE"
    echo "--- BASH STDOUT ---" >> "$LOG_FILE"
    cat "$BASH_OUT" >> "$LOG_FILE"
    echo "--- MINI STDOUT ---" >> "$LOG_FILE"
    cat "$MINI_OUT" >> "$LOG_FILE"
    echo "--- BASH EXIT: $bash_exit | MINI EXIT: $mini_exit ---" >> "$LOG_FILE"
    echo "========================================" >> "$LOG_FILE"
    echo "" >> "$LOG_FILE"
}

# ==============================================================================
# TEST SUITES
# ==============================================================================

# --- Built-ins ---
TESTS_BUILTIN=(
    "echo"
    "echo hello"
    "echo hello world"
    "echo -n"
    "echo -n hello"
    "echo -n hello world"
    "echo -nnn hello"
    "echo -n -n -n hello"
    "echo -n-n hello"
    "echo -n -x hello"
    "echo hello -n"
    "pwd"
    "cd /"
    "cd /tmp"
    "cd does_not_exist"
    "cd /root" 
    "cd ''"
    "cd \"\""
    "export"
    "export 1INVALID=42"
    "export INVALID@CHAR=42"
    "export =42"
    "export +x=42"
    "unset does_not_exist"
    "unset 1INVALID"
    "unset INVALID@CHAR"
    "env"
    "env | grep PATH"
    "exit"
    "exit 0"
    "exit 1"
    "exit 42"
    "exit -1"
    "exit 255"
    "exit 256" 
    "exit abc" 
    "exit 1 2 3" 
    "exit 9223372036854775807"
    "exit 9223372036854775808" 
)

# --- Pipes & Redirections ---
TESTS_PIPEREDIR=(
    "ls | cat"
    "ls -la | wc -l"
    "echo hello | grep h"
    "echo hello | grep x"
    "cat /etc/passwd | head -n 5"
    "env | sort | grep PATH"
    "ls | grep a | wc -l"
    "echo a | cat | cat | cat | cat | cat | cat | cat"
    "ls does_not_exist | grep a" 
    "ls | does_not_exist | cat" 
    "ls | cat | does_not_exist" 
    "ls -la > out3.txt | wc -l" 
    "> out4.txt" 
    ">> out5.txt" 
    "cat < /etc/passwd | wc -l"
    "grep root < /etc/passwd"
    "cat < does_not_exist"
    "< /etc/passwd cat"
    "cat < /etc/passwd > out9.txt | wc -l"
    "> out10.txt echo hello"
    "echo > out11.txt hello"
)

# --- Quotes & Expansions ---
TESTS_QUOTES=(
    "echo 'hello'"
    "echo 'hello world'"
    "echo 'hello \$USER'"
    "echo ''"
    "echo '   '"
    "echo 'echo hello'"
    "echo '| <>'"
    "echo \"hello\""
    "echo \"hello world\""
    "echo \"hello \$USER\""
    "echo \"\$?\""
    "echo \"\""
    "echo \"   \""
    "echo \"| <>\""
    "echo \"'hello'\""
    "echo '\"hello\"'"
    "echo \"hello '\$USER'\""
    "echo 'hello \"\$USER\"'" 
    "echo \"hello \"\"world\""
    "echo 'hello ''world'"
    "echo \$USER"
    "echo \$USER\$PWD"
    "echo \$USER \$PWD"
    "echo \$DOES_NOT_EXIST"
    "echo hello\$DOES_NOT_EXIST"
    "echo \$DOES_NOT_EXISThello"
    "echo \$"
    "echo \"\$\""
    "echo '\$'"
)

# --- Edge Cases & Syntax Errors ---
TESTS_EDGE=(
    ""
    " "
    "    "
    " echo "
    "    ls    -l    "
    "|"
    "||"
    "| echo hello"
    "echo hello |"
    "echo hello | | cat"
    "<"
    ">"
    ">>"
    "< >"
    "> >"
    ">>>"
    "<<"
    "ls -l > > out.txt"
    "ls < < out.txt"
    "ls | >"
    "does_not_exist"
    "does_not_exist args"
    "/tmp" 
    "." 
    ".."
    "./"
    " /bin/ls " 
    "/bin/does_not_exist"
    "echo 'hello'\"world\"\$USER"
    "echo hello > out_chaos.txt | wc -l < out_chaos.txt"
    "cat /etc/passwd | head -n 5 | tail -n 2 | awk '{print \$1}' | wc -c"
    "echo '     ' | cat -e"
)
# ==============================================================================
# EXECUTION
# ==============================================================================

echo -e "${BLUE}=== RUNNING MINISHELL TEST SUITE ===${RESET}"

for cmd in "${TESTS_BUILTIN[@]}"; do run_test "$cmd" "BUILT-IN"; done
for cmd in "${TESTS_PIPEREDIR[@]}"; do run_test "$cmd" "PIPE/REDIR"; done
for cmd in "${TESTS_QUOTES[@]}"; do run_test "$cmd" "QUOTES/EXP"; done
for cmd in "${TESTS_EDGE[@]}"; do run_test "$cmd" "EDGE CASES"; done

echo -e "\n${BLUE}Tests finished. Check '$LOG_FILE' for detailed failure diffs.${RESET}"