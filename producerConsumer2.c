/*
    Producer Consumer with counter variable
    
	To fill the buffer fully, using a extra variable counter.
 counter counts the number of items present in the buffer. Initially counter = 0;
 value will be increasing at producer side and will be decreasing in consumer side.

 */

#include<stdio.h>
#include<stdlib.h>

#define BUFFER_SIZE 10

int in = 0;
int out = 0;
int counter = 0; // counter initialize with 0

void producer(int buffer[]){
    if(counter == BUFFER_SIZE){
        printf("BUFFER is full");
    }
    else{
        int item;
        printf("Enter the item to be produced in buffer : ");
        scanf("%d", &item);
        buffer[in] = item;
        in = (in + 1)% BUFFER_SIZE;
        counter++;
    }
}

void consumer(int buffer[]){
    if(counter == 0){
        printf("BUFFER is empty\n");
    }
    else{
        int consumed = buffer[out];
        //buffer[out] = -1; // making it -1 as consumed.
        printf("Consumed item = %d\n", consumed);
        out = (out + 1)% BUFFER_SIZE;
        counter--;
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
