#include <stdio.h>
#define MAX_STACK_SIZE 100

// stack 구조체
typedef struct stackType
{
    int data[MAX_STACK_SIZE];
    int top;
} StackType;

// 함수 선언
void initStack(StackType *s);
int isEmpty(StackType *s);
int isFull(StackType *s);
void push(StackType *s);
void pop(StackType *s);
void printAsk(void);
void printStack(StackType *s);

int main(int argc, char *argv[])
{
    StackType s;
    initStack(&s);

    int input;
    printAsk();
    scanf("%d", &input);
    while(input == 1 || input == 2)
    {
        if (input == 1)
            push(&s);
        else if (input == 2)
            pop(&s);
        printStack(&s);
        printAsk();
        scanf("%d", &input);
    }
    printf("종료");

    return (0);
}

void initStack(StackType *s)
{
    s->top = -1;
}

int isEmpty(StackType *s)
{
    return (s->top == -1);
}

int isFull(StackType *s)
{
    return (s->top == MAX_STACK_SIZE - 1);
}

void push(StackType *s)
{
    if (isFull(s))
    {
        printf("스택이 꽉 찼습니다.\n");
        return ;
    }
    int value;
    printf("PUSH 할 숫자를 입력하세요: ");
    scanf("%d", &value);
    s->data[++(s->top)] = value;
}

void pop(StackType *s)
{
    if (isEmpty(s))
    {
        printf("POP: 스택이 비어있습니다.\n");
        return ;
    }
    printf("POP : %d 나왔습니다.\n", s->data[(s->top)--]);
}

void printAsk(void)
{
    printf("1. PUSH\n2. POP\n3. QUIT\n입력: ");
}

void printStack(StackType *s)
{
    printf("Stack : ");
    if (isEmpty(s))
        printf("EMPTY");
    else if (isFull(s))
        printf("FULL");
    else
    {
        for (int i = 0; i <= s->top; i++)
        {
            printf("%d", s->data[i]);
            if (i != s->top)
                printf(" - ");
        }
    }
    printf("\n\n");
}