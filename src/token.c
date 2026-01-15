// std libs
#include <string.h>

// project
#include "token.h"

// implements Classify token
TokenType ClassifyToken(char *str) {
    if (strlen(str) == 1 && (str[0] == ' ' || str[0] == '\n' || str[0] == '\t'))
        // blank tokens
        return TOKEN_BLANK;

    /*
    * Here add all tokens for the language
    */

    // per default it's illegal token
    return TOKEN_ILLEGAL;
}