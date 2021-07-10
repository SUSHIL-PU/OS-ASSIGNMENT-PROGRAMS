/*
        `producer Consumer problem using semaphore
    TO use semaphore have to use 3 more variable.
    Semaphore mutex  -->    initially value is 1, it ensures the mutex exclusion
    Semaphore full   -->    initially 0, count the number of full spaces in buffer
    Semaphore empty  -->    initially value is n, counts the number of empty spaces in buffer.
                                    (n is the BUFFER_SIZE)
*/


#include<stdio.h>
#include<stdlib.h>

# define BUFFER_SIZE 10

int mutex = 1;
int full = 0;
int empty = BUFFER_SIZE;

int in = 0; // index where item will be added to the buffer in producer
int out = 0; // index where item will be removed from buffer in consumer

int wait(int s){
    return --s;
}

int signal(int s){
    return ++s;
}


void producer(int buffer[]){
    if(mutex == 1 && empty != 0){
        mutex = wait(mutex);
        empty = wait(empty);

        int item;
        printf("Enter the item to be produced in buffer : ");
        scanf("%d", &item);
        buffer[in] = item;
        in = (in + 1)%BUFFER_SIZE;

        full = signal(full);
        mutex = signal(mutex);
    }else{
        printf("Buffer is full!\n ");
    }
}

void consumer(int buffer[]){
    if(mutex == 1 && full != 0){
        mutex = wait(mutex);
        full = wait(full);

        int consumed = buffer[out];
        printf("Item consumed %d", consumed);
        out = (out + 1)%BUFFER_SIZE;

        empty = signal(empty);
        mutex = signal(mutex);
    }else{
        printf("Buffer is empty!\n");
    }
}


int main(){
    int buffer[BUFFER_SIZE];
    while(1){
        printf("\nEnter 1 for Producer\n2 for Consumer\n3 for Exit\n");
        int ch;
        printf("\nEnter your choice : ");
        scanf("%d", &ch);

        switch(ch){
        case 1:
            producer(buffer);
            break;
        case 2:
            consumer(buffer);
            break;
        case 3:
            exit(0);
        default:
            printf("Enter the correct choice");
        }
    }
}
