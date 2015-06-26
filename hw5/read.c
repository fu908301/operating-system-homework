#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
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
  signal(SIGINT,stoploop);
  int fd;
  void *file_memory;
  char data[DATA_SIZE];
  if(argc<2)
  {
    printf("Please input a string as argv[1] for filename you write in write.c\n");
    return 0;
  }
  printf("Here is to view what is in main memory now,and press ctrl+c to stop\n");
  while(!stop)
  {
    fd = open(argv[1],O_RDWR,S_IRUSR | S_IWUSR);
    file_memory = mmap(0,FILE_LENGTH,PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
    sscanf(file_memory,"%[^\n]",data);
    printf("%s\n",data);
    printf("------------------------\n");
    
    sleep(1);
  }  
  close(fd);
  munmap(file_memory,FILE_LENGTH);
  return 0;
}
