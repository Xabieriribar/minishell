#include "minishell.h"
// int main(void)
// {
// 	int fd_grammar_tester = open("parser/grammar_tests/grammar_tester.txt", O_RDONLY);
// 	if (fd_grammar_tester < 0)
// 		perror("Failed to open tester file");
// 	if (test_grammar(fd_grammar_tester) != 0)
// 		return (perror("Failed to test grammar"), 1);
// 	return 0;
// }
int main(void)
{
	int fd_tree_tester = open("parser/tree_tester/tree_tests.txt", O_RDONLY);
	if (fd_tree_tester < 0)
		perror("Failed to open tester file");
	if (test_tree(fd_tree_tester) != 0)
		return (perror("Failed to test tree"), 1);
	close(fd_tree_tester);
	return 0;
}