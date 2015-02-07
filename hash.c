#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define PROMPT "$>"

#define MAX_LEN 256

void say(char *str);
char **parse_input(char *input, ssize_t, int *argc);

int main() {
	bool running = true;
	ssize_t sz;
	int pid, stat_loc, argc = 0;
	char buf[MAX_LEN];
	char **args;

	while (running) {
		say(PROMPT);
		sz = read(STDOUT, buf, MAX_LEN);
		if (*buf == '\n')
			continue;

		args = parse_input(buf, sz, &argc);

		if (strncmp(args[0], "exit", strlen("exit")) == 0
				|| strncmp(args[0], "quit", strlen("quit")) == 0) {
			running = false;
		} else {
			pid = fork();
			if (pid == 0) {
				execv(args[0], args);
			} else {
				wait(&stat_loc);
			}
		}
	}
	free(args);
	exit(EXIT_SUCCESS);
}


void say(char *str)
{
	write(STDOUT, str, strlen(str));
	fflush(stdout);
}

char **parse_input(char *input, ssize_t len, int *argc)
{
	int arg_start = 0;
	int i = 0;
	int lim = 2;
	char **args;

	*argc = 0;
	args = malloc(lim * sizeof(char *));

	if (!args)
		exit(EXIT_FAILURE);

	if (!input)
		return NULL;

	for (; i < len; i++) {
		if (input[i] == ' ' || input[i] == '\n') {
			input[i] = '\0';
			*(args + (*argc)++) = input + arg_start;
			arg_start = i + 1;

			if (*argc == lim) {
				lim *= 2;
				char **new = realloc(args, lim * sizeof(char *));

				if (!new) {
					free(args);
					return NULL;
				}
				args = new;
			}
		}
	}

	/* Make room to add the NULL after the last character. */
	if (*argc == lim) {
		char **new = realloc(args, (lim + 1) * sizeof(char *));
		if (!new) {
			return NULL;
		}
		args = new;
	}

	/* Add the final NULL. */
	*(args + *argc) = NULL;
	return args;
}
