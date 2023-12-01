// Implementing bounded stack in C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define N 20

int top = -1;
int stack[N];


void push();
int pop();
int peek();
bool isEmpty();
bool isFull();


int main()
{
 int choice;

while(1)
    {
        printf("\nChoose operation:\n");
        printf(" 1: Push \t2: Pop \t3: Peek \t4: Is empty? \t5: Is full? \t6: Exit\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: push(); break;
            case 2: pop(); break;
            case 3: peek(); break;
            case 4: isEmpty(); break;
            case 5: isFull(); break;
            case 6: exit(0);
            default: printf("Please choose a correct option!");
        }
    }

     return 0;
}

void push(){

    if(top == N-1)  // Checking overflow state (IsFull condition)
        printf("Overflow State: can't add more elements into the stack\n");
    else
    {
        int x;
        printf("Enter element to be pushed into the stack: ");
        scanf("%d", &x);
        top+=1;
        stack[top] = x;
    }
}

int pop(){
     //Checking underflow state
    if(top == -1)
        printf("Underflow State: Stack already empty, can't remove any element\n");
    else{
        isEmpty();
        int x = stack[top];
        printf("Popping %d out of the stack\n", x);
        top-=1;
        return x;
    }
    return -1;
}

int peek(){
    printf("%d is the top most element of the stack\n", stack[top]);
    return stack[top];
}

bool isEmpty(){
    if(top == -1){
        printf("Stack is empty: Underflow State\n");
        return true;
    }
    printf("Stack is not empty\n");
    return false;
}
bool isFull(){
    if(top == N-1){
        printf("Stack is full: Overflow State\n");
        return true;
    }
    printf("Stack is not full\n");
    return false;
}
