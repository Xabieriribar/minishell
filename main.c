#include "minishell.h"
int main(void)
{
	int fd_grammar_tester = open("parser/grammar_tests/grammar_tester.txt", O_RDONLY);
	if (fd_grammar_tester < 0)
		perror("Failed to open tester file");
	if (test_grammar(fd_grammar_tester) != 0)
		return (perror("Failed to test grammar"), 1);
	return 0;
}