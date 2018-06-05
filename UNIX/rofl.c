/*	Author: Sai Nikhil Reddy Mettupally
	Course Name: CS590
	Instructor: Dr.Stacy Lukins
	Assignment : Final Project
	Due Date: 08/03/2017
	Description: This program simulates the roller-coaster problem. */
	
#include <sys/types.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
	
//int board();
//int unboard();
//int load();
//int run();
//int unload();
	
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

int capacity;
int boarders = 0; //add
int unboarders = 0; //del

sem_t boardQueue;
sem_t Onride;
	
sem_t allAboard; //filled
sem_t allAshore; //empty


void* car(void* s) {
	pthread_t temp2 = pthread_self();
	while(1){
	int i=0;
	printf("s1\n");
	for(;i<capacity;i++)
		sem_post(&boardQueue);
		sem_wait(&allAboard);		
		printf("Roller coaster ride has started.\n");
		printf("Roller coaster ride ended\n");
		boarders=0;
	for(i=0;i<capacity;i++){
		sem_post(&Onride);
		sem_wait(&allAshore);	
		}
	sleep(2);	
	}	
}

void* passenger(void *s) {
	pthread_t temp = pthread_self();
	while(1){
		sem_wait(&boardQueue);
		pthread_mutex_lock(&mutex);
			boarders += 1;
			printf("Passenger has boarded the car.\n");
			if (boarders == capacity){
				sem_post(&allAboard);
			}
		pthread_mutex_unlock(&mutex);
		sem_wait(&Onride);
		sem_post(&allAshore);
		printf("Passenger has left the car\n");	
	}
}

int main(int argc, char **argv) {
	int C; //capacity of the car
	int n; //no. of passengers
	pthread_t C_id = 0; //car thread ID
	pthread_t n_id[100] = {0}; //passenger thread ID
	int i;
	printf("Please enter the capacity of the car\n");
	scanf("%d", &C);
	printf("Please enter the number of passenger queues\n");
	scanf("%d", &n);
	capacity = C;
	if (C >= n){
		printf("The capacity of the car should be less than the number of passengers\n");
	}
	else{
		sem_init(&allAshore,0,C);
        sem_init(&allAboard,0,0);
	sem_init(&boardQueue,0,0);
	sem_init(&Onride,0,0);
		printf("%d %d \n", C, n);
		//creating the car threads;
			pthread_create(&C_id, NULL, car, NULL);
//			pthread_join(C_id,NULL);
		// creating passenger threads;
		for(i =0;i < n;i++) {
			pthread_create(&n_id[i], NULL, passenger, NULL);
		}
	pthread_join(C_id,NULL);	
	}
return 0;
}
