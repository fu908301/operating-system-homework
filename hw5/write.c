#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#define FILE_LENGTH 0x100
#define DATA_SIZE 100
int stop=0;
void stoploop()
{
  stop=1;
}
int main(int argc,char* const argv[])
{
  int fd;
  void *file_memory;
  char data[DATA_SIZE];
  signal(SIGINT,stoploop);
  if(argc<2)
  {
    printf("Please input a string as argv[1]\n");
    return 0;
  }
  printf("Input a string to update,and press crtl+c to stop.\n");
  while(!stop)
  {
    gets(data);
    fd = open(argv[1],O_RDWR | O_CREAT,S_IRUSR | S_IWUSR);
    lseek(fd,FILE_LENGTH+1,SEEK_SET);
    write(fd,"",1);
    lseek(fd,0,SEEK_SET);
    file_memory = mmap(0,FILE_LENGTH,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    sprintf((char *)file_memory,"%s",data);
    printf("Update sucess.\n");
  }
  close(fd);
  munmap(file_memory,FILE_LENGTH);
  return 0;
}
