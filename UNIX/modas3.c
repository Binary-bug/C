#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>
#include<sys/types.h>
#define BUF_SIZE 6
#define THRBUF 12


char buffer[BUF_SIZE];

int add=0;                 // position at which new element can be added
int del=0;                 // position from which an element can be consumed
int sig=6;                 // number of producers remaining


FILE *fin;
pthread_mutex_t mut_readbuf = PTHREAD_MUTEX_INITIALIZER; // mutex lock for file read
pthread_mutex_t mut_writebuf = PTHREAD_MUTEX_INITIALIZER; //mutex lock for file write


sem_t empty;
sem_t filled;


int insertbuffer(pthread_t temp){
	char c='\0';
	if(read(fileno(fin),&c,1)){
	buffer[add]=c;
	add = (add + 1) % BUF_SIZE;
	//printf("Producer %d produced : %c \n",temp,c);
	return 0;
	}
	else{
		pthread_mutex_unlock(&mut_writebuf);
		sig--;
		//printf("got EOF exiting producer %d\n",temp);
		pthread_exit(NULL);
	}	

}

int removebuffer(pthread_t temp2){
	char y=buffer[del];
	del = (del + 1) % BUF_SIZE;
       	//printf("Consumer %d consumed : %c \n",temp2,y);
	printf("%c",y);
	return 0;
}
	
	
void* producer(void *assam){
	
	pthread_t temp=pthread_self();
	while(1){
        sem_wait(&empty);
		pthread_mutex_lock(&mut_writebuf);		
			insertbuffer(temp);
		pthread_mutex_unlock(&mut_writebuf);	
 	sem_post(&filled);	
	}
	
	
}

void* consumer(void *assam){
	pthread_t temp2=pthread_self();	
       while(1){	
	sem_wait(&filled);
	      pthread_mutex_lock(&mut_readbuf);
		removebuffer(temp2);
	      pthread_mutex_unlock(&mut_readbuf);
	sem_post(&empty);
     }
}       

void main(int argc,char *argv[]){

	pthread_t tid[THRBUF]={0};
	int i=0;
	int j=1;
	fin=fopen("rofl.txt","r");
	sem_init(&empty,0,BUF_SIZE);
        sem_init(&filled,0,0);

	for(i=0;i<THRBUF;i=i+2){
		if(pthread_create(&tid[i],NULL,producer,NULL)!= 0){
			printf("Unable to create producer\n");
			exit(1);
		}
		if(pthread_create(&tid[i+1],NULL,consumer,NULL)!=0){
			printf("Unable to create consumer\n");
			exit(1);
		}

	}
				
		while(j>0){if(sig == 0) {printf("waiting for consumer to complete\n");sem_getvalue(&filled,&j);}}
	        for(i=0;i<THRBUF;i=i+2)	
		pthread_cancel(tid[i+1]);
		
	printf("End of Buffer Service\n");
	exit(0);
}


