#ifndef __MM_H__
#define __MM_H__
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#define NALLOC 1024
typedef long Align;
union header{
	struct{
		union header *ptr;
		unsigned size;
	}s;
	Align x;
};
typedef union header Header;

Header *morecore(size_t);
void* mymalloc(size_t);
void* myrealloc(void*,size_t);
void* mycalloc(size_t,size_t);
void myfree(void*);
#endif
