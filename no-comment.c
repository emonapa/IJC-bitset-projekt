 /*
-------------------------------------------------------------
    no-comment.c
    Solution to IJC-DU1, example B)
    Date: 14.3.2024
    Author: Václav Matyáš, FIT
    Compiler: gcc 11.4.0
    Description: State machine for deleting comments
-------------------------------------------------------------
*/
#include "error.h"
#include <stdio.h>
#include <stdbool.h>

enum State {
    NORMAL,
    SLASH,
    LINE_COMMENT,
    BLOCK_COMMENT,
    STRING,
    CHAR,
    ESCAPE
};

int main(int argc, char *argv[]) {
    FILE *input;
    
    if (argc == 1) {
        input = stdin;
    } else if (argc == 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            error_exit("%s cannot be opened", argv[1]);
        }
    } else {
        error_exit("Use %s [filename]\n", argv[0]);
        return 1;
    }
    
    enum State state = NORMAL;
    int c;
    bool in_string = false;
    bool in_char = false;
    
    while ((c = fgetc(input)) != EOF) {
        switch (state) {
            case NORMAL:
                if (c == '/') {
                    state = SLASH;
                } else {
                    if (c == '\"' && !in_char) {
                        in_string = !in_string;
                    }
                    if (c == '\'' && !in_string) {
                        in_char = !in_char;
                    }
                    putchar(c);
                }
                break;
            case SLASH:
                if (c == '/') {
                    state = LINE_COMMENT;
                } else if (c == '*') {
                    state = BLOCK_COMMENT;
                } else {
                    putchar('/');
                    putchar(c);
                    state = NORMAL;
                }
                break;
            case LINE_COMMENT:
                if (c == '\n') {
                    putchar(c);
                    state = NORMAL;
                }
                break;
            case BLOCK_COMMENT:
                if (c == '*') {
                    state = ESCAPE;
                }
                break;
            case ESCAPE:
                if (c == '/') {
                    state = NORMAL;
                } else if (c != '*') {
                    state = BLOCK_COMMENT;
                }
                break;
            case STRING:
                putchar(c);
                if (c == '\\') {
                    state = ESCAPE;
                } else if (c == '\"') {
                    state = NORMAL;
                }
                break;
            case CHAR:
                putchar(c);
                if (c == '\\') {
                    state = ESCAPE;
                } else if (c == '\'') {
                    state = NORMAL;
                }
                break;
        }
    }
    
    if (input != stdin) {
        fclose(input);
    }
    
    return 0;
}
