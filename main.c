
int main(int argc, char const **argv)
{
    shell_loop();

    return EXIT_SUCCESS;
}


void shell_loop(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf("> ");
        line = shell_read_line();
        args = shell_split_line(line);
        status = shell_execute(args);

        free(line);
        free(args);
    } while (status);
}


#define SHELL_RL_BUFSIZE 1024

char *shell_read_line(void)
{
    int bufsize = SHELL_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(sizeof(char) * bufsize);

    if (!buffer) {
        fprintf(stderr, "shell: Allocation error!\n");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if (c == EOF || c == "\n") {
            buffer[position] = "\0";
            return buffer
        } else {
            buffer[position] = c;
        }
        position++;

        if (position >= bufsize) {
            bufsize += SHELL_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                fprintf(stderr, "shell: Allocation error!\n");
                exit(EXIT_FAILURE);
            }
        }
    }
}


#define SHELL_TOK_BUFSIZE 64
#define SHELL_TOK_DELIM " \t\r\n\a"

char **shell_split_line(char *line)
{
    int bufsize = SHELL_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "shell: Allocation error!\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, SHELL_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            bufsize += SHELL_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char*));
            if (!tokens) {
                fprintf(stderr, "shell: Allocation error!\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, SHELL_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}