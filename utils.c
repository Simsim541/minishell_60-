/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberri <mberri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:31:11 by aaammari          #+#    #+#             */
/*   Updated: 2023/03/08 16:11:43 by mberri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	counter_quotes(char c, int *db, int *s)
{
	if (c == '"')
		(*db)++;
	if (c == '\'')
		(*s)++;
}

int	is_white_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	print_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (0);
}

int	there_is_a_redirection(char *str)
{
	int	i;
	int	db;
	int	s;

	i = 0;
	db = 0;
	s = 0;
	while (str[i])
	{
		counter_quotes(str[i], &db, &s);
		if ((str[i] == '>' || str[i] == '<') && (!(db % 2) && !(s % 2)))
			return (1);
		i++;
	}
	return (0);
}
/*int	nbr_of_char(char *str, char c, int n, int ds)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (str[i] && i < n && ds % 2 == 0)
	{
		if (str[i] == c)
			nbr++;
		i++;
	}
	if (nbr % 2 == 0)
		return (0);
	return (nbr);
}*/

/*you can start minishell by this code and try to understand the basic

Here are the steps to create a basic mini shell:

- Start by including necessary header files, 
    such as <stdio.h>, <stdlib.h>, <unistd.h>, <string.h>, <sys/wait.h>, and <signal.h>.
- Define constants for maximum input length,
    maximum number of arguments, and other parameters.
- Write a function to parse the user input, splitting it into individual commands and arguments. 
    This can be done using the strtok() function from <string.h>.
- Write a loop that repeatedly prompts the user for input,
    parses it, and executes the corresponding command.
- Use the fork() function to create a child process, which will execute the user's command.
    The parent process should wait for the child to finish using waitpid().
- Use the execvp() function to execute the command entered by the user in the child process.
    This function takes the command and its arguments as input.
- Handle special commands such as cd, exit, and pwd in your shell.
- Handle signals like CTRL+C (SIGINT) and CTRL+\ (SIGQUIT) using signal() from <signal.h>


 #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64

void parse_input(char* input, char** args) {
    char* token;
    int i = 0;
    token = strtok(input, " \t\n\r");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n\r");
    }
    args[i] = NULL;
}

int main() {
    char input[MAX_INPUT_LENGTH];
    char* args[MAX_ARGS];
    pid_t pid;
    int status;

    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) {
            break;
        }

        parse_input(input, args);

        if (strcmp(args[0], "exit") == 0) {
            break;
        }

        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                chdir(getenv("HOME"));
            } else {
                chdir(args[1]);
            }
            continue;
        }

        pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
            printf("Unknown command: %s\n", args[0]);
            exit(1);
        } else if (pid < 0) {
            perror("fork");
        } else {
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}*/
