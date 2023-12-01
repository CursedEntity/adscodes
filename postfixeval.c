#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define N 10
int stack[10];
int top = -1;

void push(int a)
{
  stack[++top] = a;
}

int pop()
{
  if(top == -1)
    return -1;
  else
    return stack[top--];
}

int postfix(char *x)
{
  int i = 0, val1, val2, result;
  for(i = 0; x[i] != '\0'; i++)
  {
    if(isdigit(x[i]))
      push(x[i] - '0');
    
    else
    {
      val1 = pop();
      val2 = pop();
      switch(x[i])
      {
        case '+': push(val2 + val1); break;
        case '-': push(val2 - val1); break;
        case '*': push(val2 * val1); break;
        case '/': push(val2 / val1); break;
        case '%': push(val2 % val1); break;
        default: exit(1);
      }
    }
  }
  result = pop();
  if(top != -1)
    exit(1);
  return result;
}

int main()
{
  char str[N];
  fgets(str, N, stdin);
  int result = postfix(str);
  printf("%d", result);
  
  return 0;
}
