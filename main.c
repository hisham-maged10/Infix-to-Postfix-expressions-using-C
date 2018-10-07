/**
 * @author ${hisham_maged10}
 *https://github.com/hisham-maged10
 * ${DesktopApps}
 */
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
typedef struct
{
    int top;
    int items[100];
}stack;

void initialize(stack *s);
int pop(stack *s);
void push(stack *s,float data);
int isEmpty(stack*s);
int top(stack*s);
int evaluatePostfix(char postfix[]);
char* infixtopostfix(char infix[]);
int isDigit(char element);
int isOperation(char element);
int precedence(char operation);

int main()
{
    char infix[100];
    printf("Please enter the Infix Expression: ");
    scanf("%s",infix);
    char*postfix;
    postfix=infixtopostfix(infix);
    printf("postfix Expression: %s\n",postfix);
    printf("Answer: %d",evaluatePostfix(postfix));
    return 0;
}

void initialize(stack*s)
{
    s->top=-1;
}

void push(stack*s,float data)
{
    s->items[++s->top]=data;
}

int isEmpty(stack *s)
{
    if(s->top>-1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int pop(stack*s)
{
    if(!isEmpty(&s))
    {
    return s->items[s->top--];
    }
    else
    {
        return -1.0;
    }
}

int top(stack*s)
{
    if(!isEmpty(&s))
    {
        return s->items[s->top];
    }
    else
    {
        return -1;
    }
}
int evaluatePostfix(char postfix[])
{
    char*checkletters=postfix;
    stack s;
    initialize(&s);
    int operand1;
    int operand2;
    while(*checkletters!='\0')
    {
        if(isDigit(*checkletters))
        {
            push(&s,*checkletters-'0');
        }
        else
        {
            operand1=pop(&s);
            operand2=pop(&s);
            switch (*checkletters)
            {
            case '+': push(&s,operand1+operand2);
            break;
            case '-': push(&s,operand2-operand1);
            break;
            case '*': push(&s,operand1*operand2);
            break;
            case '/': push(&s,operand2/operand1);
            break;
            }
    }
    checkletters++;
    }
    return pop(&s);
}
int precedence(char operation)
{
    switch(operation)
    {
    case '+':
    case '-':return 0;
    break;
    case '*':
    case 'x':
    case 'X':
    case '/':
    case '%':
            return 1;
    break;
    case '(':
    case ')':return 2;
    break;

    default:
    {
        puts("Error in operators!!");
        exit(1);
    }

    }

}
char* infixtopostfix(char infix[])
{
    char element;
    char*postfix;
    postfix=(char*)malloc(100*sizeof(char));
    int i,j;
    stack s;
    initialize(&s);
    i=0;
    j=0;
    while(infix[i]!='\0')
    {
        element=infix[i];
        if(isDigit(element))
        {
            postfix[j++]=element;
        }
        else if(element=='(')
        {
            push(&s,element);
        }
        else if(element==')')
        {
            if(isEmpty(&s))
            {
                puts("Error in brackets");
                exit(1);
            }
    while(top(&s)!='(')
    {
        postfix[j++]=pop(&s);
    }
    pop(&s);
        }
    else if(isOperation(element))
    {
        if(isEmpty(&s))
        {
            push(&s,element);
        }
        else
        {
        while((!isEmpty(&s)) && (top(&s)!='(') && (precedence(top(&s)) >= precedence(element)))
            {
                postfix[j++]=pop(&s);
            }

        push(&s,element);

        }
    }
   i++;

    }

    if(!isEmpty(&s))
    {
        postfix[j++]=pop(&s);
    }
    postfix[j]='\0';

    return postfix;

}

int isDigit(char element)
{
    if(isdigit(element)!=0)
        return 1;
    else
        return 0;
}
int isOperation(char element)
{
    switch(element)
    {
    case '+':return 1;
    break;
    case '-':return 1;
    break;
    case '*':return 1;
    break;
    case 'x':return 1;
    break;
    case 'X':return 1;
    break;
    case '/':return 1;
    break;
    case '(':return 1;
    break;
    case ')':return 1;
    break;
    default:
    {
     return 0;
    }
    }
}
