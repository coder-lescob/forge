#ifndef HEADER_PREPROC
#define HEADER_PREPROC

// project
#include "token.h"

/*
* Pre-process the string of tokens.
* @param tokens The pointer to the array of token.
*   NOTE: THE LAST TOKEN SOULD HAVE TYPE TOKEN_EOF
*/
void PreProccess(Token *tokens);

#endif