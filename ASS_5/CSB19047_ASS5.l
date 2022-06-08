/*
    Assignment 5
    Implement a desk calculator using operator precedence parsing.
    (Use flex, and a stack; define a operator precedence table)
    
    Submitted By: CSB19047 (Kartik Papney)
    ..............................................................
*/


/* ......... Defination Section ...................*/
%{
    #include<string.h>
    #include<stdlib.h>
    #define YIELDS_TO -1
    #define TAKES_OVER 1
    #define ERROR -2
    #define EQUAL 0
    int operator_precedence_table[][6] = 
                        {
                            { TAKES_OVER,YIELDS_TO, TAKES_OVER,YIELDS_TO,YIELDS_TO,TAKES_OVER},
                            { TAKES_OVER, TAKES_OVER, TAKES_OVER,TAKES_OVER,YIELDS_TO,TAKES_OVER},
                            {TAKES_OVER,YIELDS_TO,TAKES_OVER,YIELDS_TO,YIELDS_TO,TAKES_OVER},
                            { TAKES_OVER, TAKES_OVER, TAKES_OVER, TAKES_OVER,YIELDS_TO,TAKES_OVER},
                            {YIELDS_TO,YIELDS_TO,YIELDS_TO,YIELDS_TO,YIELDS_TO, EQUAL},
                            {TAKES_OVER,TAKES_OVER,TAKES_OVER,TAKES_OVER,ERROR,TAKES_OVER}
                        };
    char expression[100][100];
    int operand_stack[100];
    char operator_stack[100];
    int operand_stack_size = 0, operator_stack_size = 0, size=0;

    int idx_operator_precedence_table(char operator)
    {
        switch(operator)
        {
            case '+': 
                return 0;
            case '*': 
                return 1;
            case '-': 
                return 2;
            case '/': 
                return 3;
            case '(': 
                return 4;
            case ')': 
                return 5; 
        } 
    }

    int comparePrecedence(char operator_1, char operator_2)
    {
        return operator_precedence_table[idx_operator_precedence_table(operator_1)][idx_operator_precedence_table(operator_2)];
    }

    int perform_operation()
    {
        int a = operand_stack[--operand_stack_size];
        int b = operand_stack[--operand_stack_size];   
        char operator = operator_stack[--operator_stack_size];


        switch(operator)
        {
            case '+': 
                return a + b;
            case '-': 
                return b - a;
            case '*':  
                return a * b;
            case '/':
                if (a == 0)
                    exit(-1);
                return b / a;
        }

        return 0;
    }

    int calculator()
    {
        int i=0;
        for(; i<size ; i++)
        {
            // current token is a character.
            if(expression[i][0] >= '0' && expression[i][0] <= '9')
            {
                int temp = atoi(expression[i]);
                operand_stack[operand_stack_size++] = temp;
                continue;
            }

            // current token is an operator...
            char op = expression[i][0];
            if(operator_stack_size == 0) {
                operator_stack[operator_stack_size++] = op;
            } else {
                if(op == '('){
                    operator_stack[operator_stack_size++] = op;
                } else if(op == ')') {
                    while(operator_stack[operator_stack_size-1] != '(')
                    {
                        int output = perform_operation();
                        operand_stack[operand_stack_size++]=output;
                    }
                    operator_stack_size--;
                } else {
                    int flag = comparePrecedence(operator_stack[operator_stack_size-1],op);

                    if(flag == ERROR) {
                        // Wrong Input...
                        exit(-1);
                    } else if(flag < 0 ) {
                        operator_stack[operator_stack_size++] = op;
                    } else {
                        while(operator_stack_size>0 && comparePrecedence(operator_stack[operator_stack_size-1],op)!=YIELDS_TO)
                        {
                            int output = perform_operation();
                            operand_stack[operand_stack_size++]=output;
                        }
                        operator_stack[operator_stack_size++] = op;
                    }
                }
            }
        }

        while(operator_stack_size!=0)
        {
            int output = perform_operation();
            operand_stack[operand_stack_size++] = output;
        }

        return operand_stack[operand_stack_size-1];
    }
%}

OPERAND [0-9]+
ADD "+"
SUB "-"
MUL "*"
DIV "/"
OB "("
CB ")"

/* ......... Rule Section ...................*/
%%
{ADD} {strcpy(expression[size++],yytext);}
{SUB} {strcpy(expression[size++],yytext);}
{MUL} {strcpy(expression[size++],yytext);}
{DIV} {strcpy(expression[size++],yytext);}
{OB} {strcpy(expression[size++],yytext);}
{CB} {strcpy(expression[size++],yytext);}
{OPERAND} {strcpy(expression[size++],yytext);}
%%

int yywrap(){}

int main(){
    FILE *fp;
    fp = fopen("test.txt","r");
    yyin = fp;
    yylex();
    printf("Assignment 5\nImplement a desk calculator using operator precedence parsing.\n(Use flex, and a stack; define a operator precedence table)\n\nSubmitted By: CSB19047 (Kartik Papney)\n\n..............................................................");
    printf("\nInput From Text File : ");
    for(int i=0;i<size;i++)
        printf("%s",expression[i]);
    int result = calculator();
    printf("\n");
    printf("Calculation : %d\n", result);
    return 0;
}