#include <stdio.h>
#define STACK_SIZE 50

int call_stack[STACK_SIZE];
char stack_info[STACK_SIZE][20];

int SP = -1;
int FP = -1;

void push(int value, const char* info);
int pop();
void print_stack();
void func1(int arg1, int arg2, int arg3);
void func2(int arg1, int arg2);
void func3(int arg1);

void push(int value, const char* info)
{
    if (SP >= STACK_SIZE - 1) {
        printf("ERROR : Stack Overflow\n");
        return;
    }
    SP++;
    call_stack[SP] = value;
    snprintf(stack_info[SP], sizeof(stack_info[SP]), "%s", info);
}

int pop()
{
    if (SP == -1) {
        printf("ERROR : Stack Underflow\n");
        return -1;
    }
    int value = call_stack[SP];
    SP--;
    return value;
}

void print_stack()
{
    if (SP == -1)
    {
        printf("Stack is empty.\n");
        return;
    }

    printf("====== Current Call Stack ======\n");

    for (int i = SP; i >= 0; i--)
    {
        if (call_stack[i] != -1)
            printf("%d : %s = %d", i ,stack_info[i], call_stack[i]);
        else
            printf("%d : %s", i, stack_info[i]);

        if (i == SP)
            printf("    <=== [esp]\n");
        else if (i == FP)
            printf("    <=== [ebp]\n");
        else
            printf("\n");
    }
    printf("================================\n\n");
}

void prologue()
{
    push(FP, "old EBP");
    FP = SP;
}

void epilogue()
{
    SP = FP;
    FP = pop();
}

void func1(int arg1, int arg2, int arg3)
{
    prologue();

    int var_1 = 100;

    push(var_1, "var_1");
    push(arg1, "arg1");
    push(arg2, "arg2");
    push(arg3, "arg3");

    print_stack();
    func2(11, 13);

    print_stack();
    pop();  // arg3
    pop();  // arg2
    pop();  // arg1
    pop();  // var_1

    epilogue();
}

void func2(int arg1, int arg2)
{
    prologue();

    int var_2 = 200;

    push(var_2, "var_2");
    push(arg1, "arg1");
    push(arg2, "arg2");

    print_stack();
    func3(77);

    print_stack();
    pop();  // arg2
    pop();  // arg1
    pop();  // var_2

    epilogue();
}

void func3(int arg1)
{
    prologue();

    int var_3 = 300;
    int var_4 = 400;

    push(var_3, "var_3");
    push(var_4, "var_4");
    push(arg1, "arg1");

    print_stack();

    pop();  // arg1
    pop();  // var_4
    pop();  // var_3

    epilogue();
}

int main()
{
    func1(1, 2, 3);

    print_stack();
    return 0;
}
