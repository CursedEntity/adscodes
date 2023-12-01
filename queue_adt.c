#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX 4
int queue[MAX];
int front = -1;
int rear = -1;
int element;

bool isEmpty ()
{
    if(rear==-1)
        return true;
    else
        return false;
}

bool isFull ()
{
    if(rear==MAX-1)
        return true;
    else
        return false;
}

void enqueue ()
{
    if(isFull())
        printf("full ");
    else
    {	
      	scanf("%d",&element);
        if(rear==-1)
            front++;
        queue[++rear] = element;
    }
}

void dequeue ()
{
    if(isEmpty())
        printf("empty ");
    else
    {
        if(front==rear)
        {
            front =-1;
            rear =-1;
        }
        printf("%d ",queue[front]);
      	front++;
    }
}

void display ()
{
    if(isEmpty())
        printf("empty ");
    else
    {
        for(int i = front; i<=rear; i++)
            printf("%d ",queue[i]);
    }
}

int main()
{
    int choice = 0;
    while(choice!=6)
    {    
         scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                enqueue(element);
                break;    
            case 2:
                dequeue();
                break;    
            case 3:
                display();
                break;    
            case 4:
                if(isFull())
                    printf("full ");
                break;    
            case 5:
                if(isEmpty())
                    printf("empty ");
                break;    
            case 6:
                exit(0);

        }
    }
    return 0;
}