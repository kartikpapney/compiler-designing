#include<stdio.h>
#include<ctype.h>
#include<string.h>

char* sarr[] = {"w(x!=3){p;p;p;}"
            , "w(x==4){p;p;p;}"
            , "w(x!=6){;}"
            , "w(x9){p;p;p;}"
            , "w(x<=7){p;}"
            , "w(x>=8){p;p;p;}"};

int size = 6;

/*
    Context Free Grammer .... 

    In my Context Free Grammer my while loop can print any number of printf statement inside it and the candition can be between identifier(>='a' && <= 'z') and some constant (>= '0' <= '9')

    S -> w(C){A}
    C -> id O id | id O c | c O c
    O -> <= | >= | == | !=
    A -> pE | pEA 
    E -> ;
*/

int O(char a, char b) {
    return (a == '=' && b == '=') ||
            (a == '!' && b == '=') ||
            (a == '<' && b == '=') ||
            (a == '>' && b == '=');
}

int idetifier(char a) {
    return a>='a'&& a <= 'z';
}
int constant(char a) {
    return a>='0'&&a<='9';
}
int condition(char a, char b) {
    return idetifier(a) && idetifier(b)
    || idetifier(a) && constant(b)
    || constant(a) && constant(b);
}

int C(char* s, int idx, int len) {
    if(idx+3 >= len) return 0;
    char a = s[idx], b = s[idx+1], c = s[idx+2], d = s[idx+3];
    return condition(a, d) && O(b, c);
}

int A(char* s, int idx, int len) {
    if(idx + 1 >= len) return 0;
    char c1 = s[idx];
    char c2 = s[idx+1];
    if(c1 == 'p' && c2 == ';') return 1;
    return 0;
}
int check(char* s, int len, int idx, char lchar) {
    if(idx == len) {
        if(lchar == '}') return 1;
        return 0;
    }
    char cchar = s[idx];
    if(cchar == 'w') {
        if(lchar == ';') return check(s, len, idx+1, cchar);
        else return 0;
    } else if(cchar == '(') {
        if(lchar != 'w') return 0;
        int checkForCondition = C(s, idx+1, len);
        if(checkForCondition == 0) return 0;
        return check(s, len, idx+5, cchar);
    } else if(cchar == ')') {
        if(lchar == '(') return check(s, len, idx+1, cchar);
        return 0;
    } else if(cchar == '{') {
        if(lchar == ')') {
            int aidx = idx+1;
            while(aidx < len && s[aidx] != '}') {
                int a = A(s, aidx, len);
                if(a == 0) return 0;
                aidx+=2;
            }
            if(aidx == len) return 0;
            return 1;
        } else {
            return 0;
        }
    }
}
int main()
{
    printf("Assignment 7 \n\nSubmitted By CSB19047 (Kartik Papney)\n\n");
    printf("Question: \nWrite a recursive descent parser for the while-construct described in the previous exercise.");
    printf("\n\nSolution: \n\n");
    printf("In my Context Free Grammer my while loop can print any number of printf statement inside it and the candition can be between identifier(>='a' && <= 'z') and some constant (>= '0' <= '9')\n");
    printf("\nContext Free Grammer\n");
    printf("S -> w(C){A}\nC -> id O id | id O c | c O c \nO -> <= | >= | == | != \nA -> pE | pEA  \nE -> ;");
    printf("\n--------------------------------------------------\n\n");

    for(int i=0; i<size; i++) {
        char* s = sarr[i];
        int len = strlen(s);
        int result = check(s, len, 0, ';');
        if(result == 1) {
            printf("%s is ACCEPTED\n", s);
        } else {
            printf("%s is REJECTED\n", s);
        }
    }
    
    return 0;
}