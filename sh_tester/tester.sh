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
MINISHELL="../minishell"
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
    # --- ECHO (25 tests) ---
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
    "echo -nhello"
    "echo \" -n \" hello"
    "echo -n -n- hello"
    "echo ''"
    "echo \"\""
    "echo 'hello   world'"
    "echo hello   world"
    "echo \$?"
    "echo -n \$PWD"
    "echo \$UNSET_VAR"
    "echo -nnnnnnnnnnnnnn"
    "echo \"-n\" hello"
    "echo -n -n -n -n"
    "echo \$USER\$PWD"

    # --- PWD (8 tests) ---
    "pwd"
    "pwd ."
    "pwd .."
    "pwd multiple args ignored"
    "pwd --"
    "pwd /tmp"
    "pwd \$HOME"
    "pwd -L" # Bash handles -L by default, check your parsing

    # --- CD (20 tests) ---
    "cd /"
    "cd /tmp"
    "cd does_not_exist"
    "cd /root" 
    "cd ''"
    "cd \"\""
    "cd ."
    "cd .."
    "cd ../../"
    "cd //"
    "cd ///"
    "cd /tmp/../tmp/../tmp"
    "cd /var/log"
    "cd /dev"
    "cd /usr/bin/.."
    "cd \$HOME"
    "cd .."
    "cd /tmp/"
    "cd ./"
    "cd ../"

    # --- EXPORT (25 tests) ---
    "export"
    "export VAR=42"
    "export VAR=\"hello world\""
    "export VAR=1 VAR=2 VAR=3"
    "export 1INVALID=42"
    "export INVALID@CHAR=42"
    "export =42"
    "export +=42"
    "export +x=42"
    "export -VAR=42"
    "export _VAR=42"
    "export VAR_1=42"
    "export EMPTY="
    "export ONLY_KEY"
    "export A=B C=D"
    "export VAR=first"
    "export VAR=second"
    "export PATH=/tmp:\$PATH"
    "export ''=42"
    "export \"\"=42"
    "export VAR='hello\"world'"
    "export VAR=hello=world=42"
    "export TEST_VAR=123"
    "export TEST_VAR=456"
    "export TEST_VAR="

    # --- UNSET (10 tests) ---
    "unset does_not_exist"
    "unset 1INVALID"
    "unset INVALID@CHAR"
    "unset _VAR"
    "unset PATH"
    "unset PWD"
    "unset ''"
    "unset \"\""
    "unset =VAR"
    "unset HOME"

    # --- ENV (4 tests) ---
    "env"
    "env | grep PATH"
    "env --"
    "env IGNORE_ARGS"

    # --- EXIT (8 tests) ---
    "exit"
    "exit 0"
    "exit 1"
    "exit 42"
    "exit -1"
    "exit 255"
    "exit 256"
    "exit abc"
)

# --- Pipes & Redirections ---
TESTS_PIPEREDIR=(
    # --- 1. Basic Single Pipes ---
    "cat Makefile | grep a"
    "ls -l | cat -e"
    "ls -a | wc -l"
    "ls | sort"
    "ls | rev"
    "cat /etc/passwd | cut -d: -f1"
    "ls -t | head -n 3"
    "cat /etc/group | tail -n 2"
    "ls | tr 'a-z' 'A-Z'"
    "cat /etc/passwd | awk -F: '{print \$1}'"

    # --- 2. Multiple Pipes (Chain Execution) ---
    "ls -la | grep d | wc -l"
    "cat /etc/passwd | cut -d: -f1 | sort | rev"
    "ls -l | grep -v total | awk '{print \$9}' | sort"
    "cat /etc/passwd | grep root | awk -F: '{print \$7}' | cat -e"
    "ls | rev | sort | rev"
    "cat /etc/group | grep -v root | head -n 5 | tail -n 2"
    "ls -1 | tr '\n' ' ' | tr ' ' '\n' | wc -l"
    "cat /dev/urandom | head -c 100 | wc -c"
    "ls -a | grep '\.' | grep -v '\.\.' | wc -l"
    "cat /etc/passwd | cut -d: -f3 | sort -n | tail -n 1"
    "ls -la | cat | cat | cat | wc -l"
    "cat /etc/passwd | grep /bin/bash | wc -l | cat"
    "ls | head -n 5 | tail -n 3 | rev | sort"
    "cat /etc/hosts | grep -v '^#' | grep -v '^$' | wc -l"
    "ls /etc | grep a | grep b | grep c | wc -c"

    # --- 3. Simple Output Redirections (>) ---
    "ls > test_out1.txt"
    "ls -la > test_out2.txt"
    "> test_out3.txt ls"
    "ls > test_out4.txt -la"
    "cat /etc/passwd > test_out5.txt"
    "> test_out6.txt cat /etc/passwd"
    "cat > test_out7.txt /etc/group"
    "grep root /etc/passwd > test_out8.txt"
    "sort /etc/passwd > test_out9.txt"
    "> test_out10.txt"

    # --- 4. Simple Input Redirections (<) ---
    "cat < /etc/passwd"
    "< /etc/passwd cat"
    "grep root < /etc/passwd"
    "< /etc/passwd grep root"
    "wc -l < /etc/passwd"
    "< /etc/passwd wc -c"
    "sort < /etc/passwd"
    "head -n 5 < /etc/passwd"
    "< /etc/passwd tail -n 3"
    "rev < /etc/passwd"

    # --- 5. Append Redirections (>>) ---
    "ls >> test_app1.txt"
    "ls -la >> test_app2.txt"
    ">> test_app3.txt ls"
    "ls >> test_app4.txt -la"
    "cat /etc/passwd >> test_app5.txt"
    ">> test_app6.txt cat /etc/passwd"
    "grep bin /etc/passwd >> test_app7.txt"
    "sort /etc/passwd >> test_app8.txt"
    ">> test_app9.txt"
    "wc -l /etc/passwd >> test_app10.txt"

    # --- 6. Mixed Output & Input Redirections ---
    "cat < /etc/passwd > test_mix1.txt"
    "< /etc/passwd cat > test_mix2.txt"
    "> test_mix3.txt cat < /etc/passwd"
    "grep root < /etc/passwd > test_mix4.txt"
    "< /etc/passwd grep bin >> test_mix5.txt"
    ">> test_mix6.txt grep daemon < /etc/passwd"
    "< /etc/passwd > test_mix7.txt wc -l"
    "> test_mix8.txt < /etc/passwd sort"
    "cat < /etc/passwd >> test_mix9.txt"
    "< /etc/passwd >> test_mix10.txt cat"

    # --- 7. Pipes AND Redirections Combined ---
    "cat < /etc/passwd | wc -l"
    "ls | grep a > test_pipeout1.txt"
    "ls -la > test_pipeout2.txt | wc -l"
    "cat < /etc/passwd | grep root > test_pipeout3.txt"
    "< /etc/passwd grep root | wc -l > test_pipeout4.txt"
    "ls | head -n 5 >> test_pipeout5.txt"
    "cat < /etc/passwd | sort | rev > test_pipeout6.txt"
    "ls -l | tail -n +2 | wc -l > test_pipeout7.txt"
    "> out_first.txt ls | cat"
    "ls | > out_mid.txt cat"
    "cat < /etc/passwd | > out_weird.txt grep bin | wc -l"
    "ls | grep a | wc -l >> test_pipeout8.txt"
    "< /etc/passwd cat | cat | cat > test_pipeout9.txt"
    "grep daemon < /etc/passwd | cut -d: -f1 > test_pipeout10.txt"
    "ls | sort -r | head -n 3 > test_pipeout11.txt"

    # --- 8. Missing/Failing Commands & Files ---
    "ls | non_existent_cmd"
    "non_existent_cmd | ls"
    "cat < does_not_exist | wc -l"
    "ls | grep a > /root/denied.txt"
    "cat < /root/shadow | grep root"
    "ls | grep root | non_existent_cmd | wc -l"
    "non_existent_cmd < /etc/passwd"
    "< does_not_exist cat > out_fail.txt"
    "> /root/denied2.txt cat < /etc/passwd"
    "ls | cat > does_not_exist/file.txt"

    # --- 9. No-Space Parsing Stress Tests ---
    "ls>out_space1.txt"
    "ls|cat"
    "cat</etc/passwd"
    "cat</etc/passwd>out_space2.txt"
    "ls -la|grep root|wc -l"
    ">out_space3.txt ls"
    "ls>>out_space4.txt"
    "cat /etc/passwd|grep bin>>out_space5.txt"
    "ls|cat>out_space6.txt|wc -l"
    "</etc/passwd grep root|cat>>out_space7.txt"

    # --- 10. Pathological & Edge Cases ---
    "cat /dev/null | wc -l"
    "ls | | cat" 
    "ls > > out_syn.txt"
    "< < ls"
    "cat /etc/passwd | grep root > out_bonus1.txt | head -n 1"
    "> a.txt > b.txt > c.txt ls"
    "< /etc/passwd < /etc/group cat"
    "ls > a1.txt >> a1.txt > a1.txt"
)

# --- Quotes & Expansions ---
TESTS_QUOTES=(
    # --- 1. Basic Quotes & Spacing Preservation ---
    "echo 'hello'"
    "echo \"hello\""
    "echo 'hello world'"
    "echo \"hello world\""
    "echo '   hello   world   '"       # Spacing must be perfectly preserved
    "echo \"   hello   world   \""
    "echo ' -n '"                      # -n should be treated as text, not a flag
    "echo \" -n \""
    "echo 'echo hello'"                # Shouldn't execute the inner echo
    "echo \"echo hello\""

    # --- 2. Empty Quotes & Whitespace Chaos ---
    "echo ''"                          # Should print empty line
    "echo \"\""
    "echo '' ''"                       # Should print a single space
    "echo \"\" \"\""
    "echo ' '"
    "echo \" \""
    "echo '  ' \"  \""
    "echo ''\"\"''\"\""                # Multiple empty strings concatenated
    "echo \"\"''\"\"''"
    "echo '' hello ''"
    "echo \"\" hello \"\""

    # --- 3. Nesting Quotes (Inner quotes become literal characters) ---
    "echo \"'hello'\""                 # Prints: 'hello'
    "echo '\"hello\"'"                 # Prints: "hello"
    "echo \"hello '\$USER'\""          # Double quotes allow $ expansion!
    "echo 'hello \"\$USER\"'"          # Single quotes STOP $ expansion!
    "echo \"'\""                       # Prints a single quote
    "echo '\"'"                        # Prints a double quote
    "echo \"'''''\""                   # Multiple single quotes inside double
    "echo '\"\"\"\"\"'"                # Multiple double quotes inside single
    "echo \"' ' ' '\""
    "echo '\" \" \" \"'"
    "echo \"'\"'\"'\""                 # Concatenated alternating quotes

    # --- 4. Variable Expansion in Double Quotes ---
    "echo \"\$USER\""
    "echo \"\$USER \$PWD\""
    "echo \"\$USER\$PWD\""             # No space between variables
    "echo \"hello \$USER\""
    "echo \"\$USER hello\""
    "echo \"\$DOES_NOT_EXIST\""        # Should expand to empty
    "echo \"hello\$DOES_NOT_EXIST\""
    "echo \"\$DOES_NOT_EXISThello\""   # Bash looks for var named 'DOES_NOT_EXISThello'
    "echo \"\$USER-\$PWD\""            # Hyphen is not a valid var char, splits them
    "echo \"\$USER_\$PWD\""            # Underscore IS valid, looks for 'USER_'
    "echo \"\$USER/\""
    "echo \" \$USER \""
    "echo \"\"\$USER\"\""              # Empty double quotes surrounding unquoted var

    # --- 5. The Lone Dollar Sign & Edge Cases ---
    "echo \$"                          # Should print: $
    "echo \"\$\""                      # Should print: $
    "echo '\$'"                        # Should print: $
    "echo \$ \"\$\" '\$'"              # Should print: $ $ $
    "echo \"\$\"hello"                 # Should print: $hello
    "echo hello\"\$\""                 # Should print: hello$
    "echo \"\$ \""                     # Should print: $ (followed by space)
    "echo \" \$ \""                    # Should print:  $ 
    "echo \"\$?\""                     # Exit status expansion
    "echo \"\$?\$?\""
    "echo \"\$? \$?\""
    "echo '\$?'"                       # Should print literal $?
    "echo \"\$?\"hello"                # E.g., 0hello
    "echo hello\"\$?\""

    # --- 6. String Concatenation (Adjacency) ---
    "echo hello\"world\""              # Prints: helloworld
    "echo \"hello\"world"              # Prints: helloworld
    "echo \"hello\"\"world\""          # Prints: helloworld
    "echo 'hello''world'"
    "echo 'hello'\"world\""
    "echo \"hello\"'world'"
    "echo h\"e\"l\"l\"o"               # Interleaved quotes
    "echo \"h\"e'l'l\"o\""
    "echo \"\$USER\"'literal'"         # Expanded variable joined with literal
    "echo 'literal'\"\$USER\""
    "echo a\"\"b\"\"c"                 # Empty quotes in the middle of a string
    "echo a''b''c"
    "echo \" \"\" \"\" \""             # Three spaces concatenated via empty quotes
    "echo ''''''''''"                  # 10 single quotes (5 empty pairs)

    # --- 7. Protecting Meta-Characters (Operators) ---
    "echo \"|\""                       # Must NOT trigger a pipe
    "echo '|'"
    "echo \"<\""                       # Must NOT trigger input redirection
    "echo '<'"
    "echo \">\""
    "echo '>'"
    "echo \">>\""
    "echo '>>'"
    "echo \"<<\""
    "echo '<<'"
    "echo \"| <> > >> <<\""            # All operators protected at once
    "echo '| <> > >> <<'"
    "echo \"ls | wc\""                 # Just a string
    "echo 'ls | wc'"
    "echo \" > out.txt \""
    "echo hello > \"out_file.txt\""    # Quotes around a valid redirection file

    # --- 8. Interactions with Builtins ---
    "export VAR=\"hello world\""       # Value with space
    "export VAR='hello world'"
    "export \"VAR\"=hello"             # Identifier is quoted
    "export 'VAR'=hello"
    "export VAR=\"\""                  # Empty value
    "export VAR=''"
    "export VAR=\"\$USER\""            # Exporting an expanded variable
    "export VAR='\$USER'"              # Exporting a literal '$USER'
    "export \"VAR=hello\""             # Bash accepts this!
    "unset \"VAR\""
    "unset 'VAR'"
    "cd \"/tmp\""
    "cd '/tmp'"
    "cd \"\"/tmp"                      # Concatenated empty quote + path
)

# --- Edge Cases & Syntax Errors ---
TESTS_EDGE=(
    # --- Whitespace & Empty Inputs ---
    ""                          # Empty string
    " "                         # Single space
    "    "                      # Multiple spaces
    "			"                 # Tabs
    "  echo  "                  # Leading/trailing spaces
    "    ls    -l    "          # Multiple internal spaces
    "\n"                        # Newline character
    " \t \n "                   # Mixed whitespace

    # --- Pipe Operator Abuse ---
    "|"                         # Lone pipe
    "||"                        # Double pipe (often unsupported or bash-logic)
    "|||"                       # Triple pipe
    "| echo hello"              # Leading pipe
    "echo hello |"              # Trailing pipe
    "echo hello | | cat"        # Empty pipe segment
    "ls | | | | wc"             # Multiple empty segments
    "echo a |ls| wc"            # No spaces around pipes
    "ls|ls|ls|ls|ls|ls|ls"      # Long pipe chain

    # --- Redirection Syntax & Chaos ---
    "<"                         # Lone input redirect
    ">"                         # Lone output redirect
    ">>"                        # Lone append
    "< >"                       # Mixed lone redirects
    "> >"                       # Space between redirect symbols
    ">>>"                       # Triple redirect (invalid)
    "<<"                        # Here-doc symbol (if supported)
    "ls -l > > out.txt"         # Ambiguous redirect
    "ls < < out.txt"            # Ambiguous input redirect
    "ls | >"                    # Pipe into lone redirect
    "> file"                    # Redirect with no command
    "< file"                    # Input with no command
    "echo hello >out1 >out2"    # Multiple outputs (last one wins?)
    "echo hello > out1 > out2 > out3"
    "cat < out1 < out2"         # Multiple inputs
    "echo hello >> out.txt > out.txt" # Append then overwrite same file
    "ls >"                      # Missing filename after redirect
    "> out.txt ls"              # Redirect before command (Valid in Bash)
    "ls > /dev/full"            # Writing to a full device
    "ls > /dev/null/fail"       # Redirect to non-existent path

    # --- Path & Permissions ---
    "does_not_exist"            # Command not in PATH
    "does_not_exist args"       # Invalid command with args
    "/tmp"                      # Directory as command
    "."                         # Dot as command
    ".."                        # Double dot as command
    "./"                        # Current dir slash
    " /bin/ls "                 # Full path with spaces
    "/bin/does_not_exist"       # Non-existent full path
    "../../../../bin/ls"        # Relative path traversal
    "/"                         # Root as command
    "./myscript.sh"             # Script without +x permission
    "   /usr/bin/whoami   "     # Path with excessive padding

    # --- Quote & Expansion Nightmares ---
    "echo 'hello'\"world\"\$USER" # Mixed quotes and env var
    "echo \"\""                 # Empty double quotes
    "echo ''"                   # Empty single quotes
    "echo \"'\""                # Single quote inside double
    "echo '\"'"                 # Double quote inside single
    "echo \"   \""              # Spaces inside quotes
    "echo \"| > <\""            # Operators inside quotes
    "echo ' ' ' ' ' '"          # Multiple quoted spaces
    "echo \"$NON_EXISTENT\""    # Expanding undefined variable
    "echo \"$\""                # Lone dollar sign in quotes
    "echo '$USER'"              # Variable in single quotes (no expansion)
    "export A=B | echo $A"      # Pipe isolation (A should be empty/old)

    # --- Complex Logic & Nesting ---
    "echo hello > out_chaos.txt | wc -l < out_chaos.txt"
    "cat /etc/passwd | head -n 5 | tail -n 2 | awk '{print \$1}' | wc -c"
    "echo '     ' | cat -e"
    "ls -l | grep \".\" | wc -l > out.txt"
    "cat << EOF > file\ncontent\nEOF" # Heredoc into file
    "ls ; ls"                   # Semicolon (if supported)
    "ls ; ; ls"                 # Double semicolon
    "echo hello > out.txt | < out.txt cat" # Crazy redirect/pipe mix

    # --- Argument & Character Limits ---
    "echo $(seq 1 1000)"        # High argument count
    "ls \"\"\"\"\"\"\"\""       # Empty quote strings
    "echo -nnnnnnnnnnn"         # Repeated flags
    "ls -l-l-l-l"               # Malformed flags
    "echo \1 \2 \3"             # Backslash escapes (if supported)
    "echo \"\n\v\f\r\""         # Escape sequences in quotes

    # --- File System Edge Cases ---
    "cat \"filename with spaces\""
    "touch \"   leading_space\""
    "ls \"*\""                  # Literal asterisk (no globbing)
    "rm -rf /"                  # The "don't run this" test
    "cat /dev/urandom | head -c 100" # Binary data handling

    # --- Environment & Shell State ---
    "env | grep PATH"           # Checking inherited env
    "setenv TEST 123"           # Builtin check (if applicable)
    "unsetenv PATH"             # Breaking the PATH
    "cd /tmp | pwd"             # CD in a pipe (should not affect parent)
    "cd .."                     # Navigating up
    "cd /proc/self/fd"          # Deep system paths

    # --- Signal & Exit Codes ---
    "exit 0"                    # Basic exit
    "exit 1"                    # Error exit
    "exit 999"                  # Out of bounds exit
    "exit -1"                   # Negative exit
    "exit hello"                # Non-numeric exit

    # --- Final Stressors ---
    "ls | ls | ls | ls | ls"    # Process exhaustion
    "   ls   -a   -l   -t   "   # Scattered flags
    ">>>>>>"                    # Pure syntax gore
    "| | |"                     # Pure pipe gore
    "echo \"done\""             # Simple closer
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