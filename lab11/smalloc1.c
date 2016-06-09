#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>

#include "smalloc1.h"

#define MAX_ITEMS 20


typedef struct {
	int sz;
	int line;
	char file[256];
	void* addr;
} mem_usage;

static int _idx = 0;
static mem_usage _trmem[MAX_ITEMS];


void *smart_malloc_int (size_t size, char *file, int line)
{
	/* TODO: Add your code here */
	int i;
	void *ptr;
	if(_idx >= MAX_ITEMS){
		printf("MAX_ITEMS\n");
		return NULL;
	}
	else{
		mem_usage tmu = _trmem[_idx];
		ptr = malloc(size);
		_trmem[_idx].sz = size;
		_trmem[_idx].line = line;
		strcpy(_trmem[_idx].file, file);
		_trmem[_idx].addr = ptr;
		_idx++;
		//tmu = _trmem[_idx-1];
		//printf("i:%d Memory Info: addr=%p, size=%d (allocated %s:%d)\n", _idx, tmu.addr, tmu.sz, tmu.file, tmu.line);
	}
	return ptr;
}

void smart_free_int (void* ptr, char *file, int line)
{
	/* TODO: Add your code here */
	int i, it;
	it = -1;
	for(i = 0; i < MAX_ITEMS; i++){
		if(_trmem[i].addr == ptr){
			it = i;
		}
	}
	if(it==-1){
		printf("**************************\n");
		printf("Attempt to access a not-allocated memory location\n");
		printf("**************************\n");
		return;
	}
	else{
		mem_usage tmu = _trmem[it];
		tmu.sz = 0;
		tmu.line = 0;
		tmu.addr = 0;
		_trmem[it] = tmu;
		_idx--;
		free(ptr);
	}
	return;
}

int smart_leakcheck ()
{
	/* TODO: Add your code here */
	int mleft = _idx;
	if(mleft){
		printf("\n ***** MEMOTY-BUG DETECTED *****\n");
		int i;
		for(i = 0 ; i < MAX_ITEMS; i++){
			if(_trmem[i].addr != 0){
				mem_usage tmu = _trmem[i];
				printf("[smalloc] leak detected!");
				printf("file: %s line: %d size: %d addr: %p\n", tmu.file, tmu.line, tmu.sz, tmu.addr);
			}
		}
	}
	return 0;
}

int smart_set_int (void *ptr, int offset, int value, char *file, int line)
{
	/* TODO: Add your code here */
	int i, it;
	it = -1;
	for(i = 0; i < MAX_ITEMS; i++){
		if(_trmem[i].addr == ptr){
			it = i;
		}
	}
	//printf("ssi it: %d\n", it);
	if(it==-1){
		printf("\n**************************\n");
		printf("Attempt to access a not-allocated memory location\n");
		printf("Access Info: offset=%d (accessed at %s:%d)\n", offset, file, line);
		printf("**************************\n");
		return -1;
	}
	else{
		mem_usage tmu = _trmem[it];
		if(tmu.sz <= offset){
			printf("\n*****************************\n");
			printf("Attempt to access a memory location beyond its size\n");
			printf("Memory Info: addr=%p, size=%d (allocated %s:%d)\n", tmu.addr, tmu.sz, tmu.file, tmu.line);
			printf("Access Info: offset=%p, size=%d (accessed at %s:%d)\n", ptr, offset, file, line);
			printf("*****************************\n");
			return -1;
		}
		else{
			int *p = ptr;
			p[offset] = value;
		}
	}
	return 0;
}

int smart_get_int (void *ptr, int offset, char *file, int line)
{
	/* TODO: Add your code here */
	int i, it, ret;
	it = -1;
	for(i = 0; i < MAX_ITEMS; i++){
		if(_trmem[i].addr == ptr){
			it = i;
		}
	}
	if(it==-1){
		printf("\n**************************\n");
		printf("Attempt to access a not-allocated memory location\n");
		printf("Access Info: offset=%d (accessed at %s:%d)\n", offset, file, line);
		printf("**************************\n");
		return -1;
	}
	else{
		mem_usage tmu = _trmem[it];
		if(tmu.sz <= offset){
			printf("\n*****************************\n");
			printf("Attempt to access a memory location beyond its size\n");
			printf("Memory Info: addr=%p, size=%d (allocated %s:%d)\n", tmu.addr, tmu.sz, tmu.file, tmu.line);
			printf("Access Info: offset=%p, size=%d (accessed at %s:%d)\n", ptr, offset, file, line);
			printf("*****************************\n");
			return -1;
		}
		else{
			int *p = ptr;
			ret = p[offset];
		}
	}
	return ret;
}

