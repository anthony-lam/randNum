#include <stdio.h> 
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int generate(){
	int file = open("/dev/random", O_RDONLY);
	if (file<0){
		printf("Error: %s\n", strerror(errno));
	}
	int num;
	int i = read(file, &num, sizeof(num));
	if (i<0){
		printf("Error: %s\n", strerror(errno));
	}
	close(file);
	return num;
}

void write_file(int file, int to_write){
	int written = write(file, &to_write, sizeof(to_write));
	if (written<0){
		printf("Error: %s\n", strerror(errno));
	}
	close(to_write);
}

int main(){
	int numbers[10];
	int i;
	printf("Generating random numbers:\n");
	for (i=0; i<10; i++){
		numbers[i] = generate();
		printf("random %d: %d\n", i, numbers[i]);
	}
	printf("\nWriting numbers to file\n");
	int written;
	int file = open("write.txt", O_WRONLY | O_CREAT, 0700);
	if (file<0){
		printf("Error: %s\n", strerror(errno));
	}
	written = write(file, numbers, sizeof(int)*10);
	if (written<0){
		printf("Error: %s\n", strerror(errno));
	}
	close(file);
	printf("\nReading numbers from file\n\n");
	int read_numbers[10];
	file = open("write.txt", O_RDONLY);
	if (file<0){
		printf("Error: %s\n", strerror(errno));
	}
	int stuff_read = read(file, read_numbers, sizeof(read_numbers));
	if (stuff_read<0){
		printf("Error: %s\n", strerror(errno));
	}
	close(file);
	printf("Verification that written values were the same:\n");
	for (i=0; i<10; i++){
		printf("random %d: %d\n", i, read_numbers[i]);
	}
	return 0;
}