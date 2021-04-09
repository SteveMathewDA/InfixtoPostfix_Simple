#include<stdio.h>
#include<string.h>
char stack[50];
char infix[50];
char postfix[50];
int stacktop = -1;
int inftop = -1;
int posttop = -1;
int len;

void pushstack(char ele)
{
    stack[++stacktop] = ele;
}
void pushpost(char ele)
{
    postfix[++posttop] = ele;
}

void popstack()
{
    stack[stacktop--];
}

void poppost()
{
    postfix[posttop--];
}
int priority(char ele)
{
    switch (ele)
    {
        case '#': return -1;
        case '(': return 0;
        case '+': return 1;
        case '-': return 1;
        case '*': return 2;
        case '/': return 2;
    }
}

int inftopos(char arr[])
{
    pushstack('#');
    for (int i = 0; i<len; i++)
    {
        char el = arr[i];
        if (isdigit(el))
        {
            pushpost(el);
        }
        else if (el == ')')
        {
            while (stack[stacktop] != '(')
            {
                char trans = stack[stacktop];
                pushpost(trans);
                popstack();
            }
            popstack();
        }
        else if (el == '(')
        {
            pushstack(el);
        }
        else
        {
            if (priority(el) > priority(stack[stacktop]))
            {
                pushstack(el);
            }
            else
            {
                while (priority(stack[stacktop])>=priority(el))
                {
                    char trans = stack[stacktop];
                    pushpost(trans);
                    popstack();
                }
                pushstack(el);
            }
        }
    }
    while (stack[stacktop] != '#')
    {
        char trans = stack[stacktop];
        pushpost(trans);
        popstack();
    }
}
int main()
{
    printf("Enter the infix expression: ");
    scanf("%s",infix);
    len = strlen(infix);
    inftopos(infix);
    printf("\nThe given infix expression is: %s",infix);
    printf("\nThe corresponding postfix expression is: %s",postfix);
    return 0;
}
