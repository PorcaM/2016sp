#ifdef COMPILETIME
#include <stdio.h>
#include <malloc.h>

int index = 0;
char *files[2];
int lines[2];
int sizes[2];
void *ptrs[2];
int leak[2];

void *mymalloc(size_t size, char *file, int line){
	void *ptr = malloc(size);
	printf("%s:%d: malloc(%d)%p\n", file, line, (int)size, ptr);
	files[index] = file;
	lines[index] = line;
	sizes[index] = (int)size;
	ptrs[index] = ptr;
	leak[index] = 1;
	index++;
	return ptr;
}

void myfree(void *p, char *file, int line){
	int i;
	free(p);
	for(i = 0; i < index; i++){
		if(ptrs[i] == p)
			 leak[i] = 0;
	}
}

void check_mleak(){
	int i;
	printf("[check_mleak %d]\n", index);
	for(i = 0; i < index; i++){
		if(leak[i]){
			printf("memory leak detected: ");
			printf("%s:%d, size:%d, addr:%p\n", files[i], lines[i], sizes[i], ptrs[i]);
		}
	}
}

#endif
