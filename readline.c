/* A static variable for holding the line. */
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
static char *line_read = (char *)NULL;


/* Read a string, and return a pointer to it.  Returns NULL on EOF. */
char *rl_gets()
{
  /* If the buffer has already been allocated, return the memory
     to the free pool. */
  if (line_read)
    {
      free (line_read);
      line_read = (char *)NULL;
    }

  /* Get a line from the user. */
  line_read = readline ("xiribar shell > ");

  /* If the line has any text in it, save it on the history. */
  if (line_read && *line_read)
    add_history (line_read);

  return (line_read);
}

int main(void)
{
    while (1)
        rl_gets();
    return (0);
}