#include <stdio.h>
#define STACK_SIZE 50

int     call_stack[STACK_SIZE];
char    stack_info[STACK_SIZE][20];

int SP = -1; 
int FP = -1;

void func1(int arg1, int arg2, int arg3);
void func2(int arg1, int arg2);
void func3(int arg1);

void push(int value, const char* info) {
    if (SP < STACK_SIZE-1) {
        call_stack[++SP] = value;
        snprintf(stack_info[SP], sizeof stack_info[SP], "%s", info);
    }
}

int pop() {
    if (SP >= 0) {
        int v = call_stack[SP];
        call_stack[SP] = 0;
        stack_info[SP][0] = '\0';
        SP--;
        return v;
    }
    return -1;
}

void push_return_address() {
    push(-1, "Return Address");
}

void prologue(const char* func_name) {
    push_return_address();
    push(FP, func_name);
    FP = SP;
}

void epilogue() {
    FP = pop();
    pop();
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

void func1(int arg1, int arg2, int arg3)
{
    int var_1 = 100;

    push(arg3, "arg3");
    push(arg2, "arg2");
    push(arg1, "arg1");
    prologue("func1 SFP");
    push(var_1,"var_1");

    print_stack();

    func2(11, 13);
	print_stack();

    pop();       // var_1
    epilogue();
    pop();       // arg1
    pop();       // arg2
    pop();       // arg3

    print_stack();
}

void func2(int arg1, int arg2)
{
    int var_2 = 200;

    push(arg2, "arg2");
    push(arg1, "arg1");
    prologue("func2 SFP");
    push(var_2, "var_2");

    print_stack();

    func3(77);
    print_stack();

    pop();
    epilogue();
    pop();
    pop();
}

void func3(int arg1)
{
    int var_3 = 300;
    int var_4 = 400;

    push(arg1, "arg1");
    prologue("func3 SFP");
    push(var_3, "var_3");
    push(var_4, "var_4");

    print_stack();

    pop();       // var_4
    pop();       // var_3
    epilogue();
    pop();       // arg1
}

int main()
{
    func1(1, 2, 3);
    //print_stack();
    return 0;
}
