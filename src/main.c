#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    bool isNewLine;
} Option;

typedef struct {
    const char* *args;
    size_t argc;
    Option *option;
} Echo;

Echo* Parser(int argc, const char* argv[]) {
    Echo* echo = calloc(1, sizeof(Echo));
    echo->args = NULL;
    echo->argc = 0;
    echo->option = calloc(1, sizeof(Option));

    int idx = 1;
    if (argc > idx) {
        if (strcmp(argv[idx], "-n") == 0) {
            echo->option->isNewLine = false;
            idx++;
        } else {
            echo->option->isNewLine = true;
        }
        
        echo->argc = argc - idx;
        
        if (echo->argc > 0) {
            echo->args = calloc(echo->argc, sizeof(const char*));
            for (int i = idx; i < argc; i++) {
                echo->args[i - idx] = argv[i];
            }
        }
    }

    return echo;
}

void Run(Echo* echo) {
    if (echo == NULL) {
        return;
    }

    for (int i = 0; i < echo->argc; i++) {
        write(STDOUT_FILENO, echo->args[i], strlen(echo->args[i]));

        if (i < echo->argc - 1) {
            write(STDOUT_FILENO, " ", 1);
        }
    }

    if (echo->option != NULL) {
        if (echo->option->isNewLine) {
            write(STDOUT_FILENO, "\n", 1);
        }
    }
}

int main(int argc, const char* argv[]) {
    Echo* echo = Parser(argc, argv);
    Run(echo);

    return 0;
};