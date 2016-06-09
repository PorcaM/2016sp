#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int get_size (FILE *);
int my_read (int, void *, size_t);
int my_write (int, void *, size_t);
int copy (int, int, size_t);

int get_size (FILE *stream){
	int ret	= 0;
	fseek (stream, 0, SEEK_END);
	ret = ftell(stream);
	return ret;
}

int my_read (int fd, void *argbuf, size_t n){
	size_t nleft = n;
	ssize_t nread;
	char *bufp = argbuf;

	while (nleft > 0){
		if ((nread = read(fd, bufp, nleft)) < 0) {
			return -1;
		}
		else if (nread == 0)
			break;
		nleft -= nread;
		bufp += nread;
	}
	return (n-nleft);
}

int my_write (int fd, void *argbuf, size_t n){
	size_t nleft = n;
	ssize_t nwritten;
	char *bufp = argbuf;

	while (nleft > 0) {
		if ((nwritten = write(fd, bufp, nleft)) < 0) {
			return -1;
		}
		nleft -= nwritten;
		bufp += nwritten;
	}
	return n;
}

int copy(int src, int dst, size_t n){
	char *buf = malloc(n);
	my_read (src, buf, n);
	my_write (dst, buf, n);
	return 0;
}

void my_encode (int src, int dst, size_t n, char key){
	char *buf = malloc(n);
	my_read (src, buf, n);
	int i = 0;
	for (i = 0; i < n; i++){
		buf[i] ^= key;
	}
	my_write (dst, buf, n);
	return;
}

void my_decode (int src, int dst, size_t n, char key){
	char *buf = malloc(n);
	my_read (src, buf, n);
	int i = 0;
	for (i = 0; i < n; i++){
		buf[i] ^= key;
	}
	my_write (dst, buf, n);
	return;
}
