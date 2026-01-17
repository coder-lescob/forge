#include "preproc.h"
#include "stack.h"

#include <string.h>

static PreProcStatmentType GetPreProcType(TokenType type) {
    switch (type)
    {
        case TOKEN_PREPROC_ALIAS: return PREPROC_ALIAS;

        default:
            printf("Illegal preprocessing statment.");
            break;
    }
    exit(-1);
}

static size_t GetNumTokens(Token *tokens) {
    size_t numtokens = 0;
    // find the end of file token
    for (size_t i = 0; tokens[i].type != TOKEN_EOF; i++, numtokens++);

    return numtokens;
}

static Stack GetPreProcStatments(Token *tokens) {
    // Create a stack of preproc statments
    Stack statments = CreateStack(500, PreProcStatment);

    // compute the number of tokens
    size_t numtokens = GetNumTokens(tokens);

    // loop over each token
    size_t rank = 0;
    for (size_t i = 0; i < numtokens && tokens[i].type != TOKEN_EOF; i++, rank++) {
        if (rank == 0 && tokens[i].type == TOKEN_DOLLAR) {

            // preprocessing statment found
            // count how many token is it to the next line
            size_t oldIdx = i, size;
            for (
                size = 1, i++ /* skip dollar */; 
                tokens[i].type != TOKEN_NWLINE && tokens[i].type != TOKEN_EOF; 
                i++, size++
            );

            // create the proproc statment
            PreProcStatment statment = {
                .type      = GetPreProcType(tokens[oldIdx + 1 /* skip the preproc token */ ].type), 
                .tokens    = calloc(size, sizeof(Token)),
                .numtokens = size
            };

            // copy tokens
            for (size_t j = 0; j < statment.numtokens; j++) {
                statment.tokens[j] = tokens[oldIdx + j];
            }

            // erase tokens
            for (size_t j = oldIdx, k = i; tokens[j].type != TOKEN_EOF; j++, k++) {
                tokens[j] = tokens[k];
            }

            // push it
            Push(statments, statment, PreProcStatment);
        }

        if (tokens[i].type == TOKEN_NWLINE) rank = 0;
    }

    // return statments
    return statments;
}

static void FreeStatment(PreProcStatment statment) {
    for (size_t i = 0; i < statment.numtokens; i++) {
        // free each string of each token
        free(statment.tokens[i].word);
    }

    // free the overall tokens
    free(statment.tokens);
}

void PreProccess(Token *tokens) {
    // get the statments
    Stack statments = GetPreProcStatments(tokens);

    for (size_t i = 0; i < statments.ptr; i++) {
        PreProcStatment s = ((PreProcStatment *)statments.data)[i];

        // do substition

        // free every ressources
        FreeStatment(s);
    }

    FreeStack(statments);
}