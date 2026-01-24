#ifndef HEADER_MEM
#define HEADER_MEM

/*
* is a pointer on the stack ?
* @param ptr The pointer
*/
int isstack(void *ptr);

/*
* is a heap pointer ?
* @param ptr The pointer
*/
int isheap(void *ptr);

#endif