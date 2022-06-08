/*

    Submitted By: CSB19047 (Kartik Papney);

    Imagine the syntax of a programming language construct such as while-loop --  while ( condition )
    begin
        statement ;
                :
    end

    where while, begin, end are keywords; condition can be a single comparision expression (such as x == 20, etc.); and statement is the assignment to a location the result of a single arithmatic operation (eg., a = 10 * b).

    Represent the above construct in a context free grammar , and write a program to create the LEADING and TRAILING sets for the non-terminals of the grammar. Hint: First represent the grammar in appropriate data structures.

*/

#include<stdio.h>
#include<string.h>
int MAX_SIZE = 6;

struct TABLE {
    char lhs;
    char* rhs;
} t[6] = {
    {'E', "E+T"},
    {'E', "T"},
    {'T', "T*F"},
    {'T', "F"},
    {'F', "(E)"},
    {'F', "i"}
};

void leading(char LHS, int ans[]) {
    for(int i=0; i<MAX_SIZE; i++) {
        if(t[i].lhs == LHS) {
            char* rhs = t[i].rhs;
            int size = strlen(rhs);
            if(rhs[0]>='A' && rhs[0]<='Z') {
                if(size > 1) {
                    ans[rhs[1]] = 1;
                }
                if(rhs[0] != LHS) leading(rhs[0], ans);
            } else {
                ans[rhs[0]] = 1;
            }
        }
    }
}

void trailing(char LHS, int ans[]) {
    for(int i=0; i<MAX_SIZE; i++) {
        if(t[i].lhs == LHS) {
            char* rhs = t[i].rhs;
            int size = strlen(rhs);
            if(rhs[size-1]>='A' && rhs[size-1]<='Z') {
                if(size > 1) ans[rhs[1]] = 1;
                if(rhs[size-1] != LHS) trailing(rhs[size-1], ans);
            } else {
                ans[rhs[size-1]] = 1;
            }
        }
    }
}

int main()
{
    printf("Submitted By: Kartik Papney\n");
    printf("Roll No: CSB19047\n");
    printf("-----------------------QUESTION----------------------------\n");
    printf("Context Free Grammer\n");
    for(int i=0; i<MAX_SIZE; i++) {
        printf("%c -> %s\n", t[i].lhs, t[i].rhs);
    }
    int visited[26];
    printf("\n--------------LEADING SET--------------\n");
    memset(visited, 0, sizeof(visited));
    for(int i=0; i<MAX_SIZE; i++) {
        char c = t[i].lhs;
        if(visited[c-'A']) continue;
        int ans[256] = {0};
        leading(c, ans);
        printf("%c -> ", c);
        for(int j=0; j<256; j++) {
            if(ans[j] == 1) {
                printf("%c, ", (char)j);
            }
        }
        printf("\n");
        visited[c-'A'] = 1;
    }
    memset(visited, 0, sizeof(visited));
    printf("--------------TRAILING SET--------------\n");
    for(int i=0; i<MAX_SIZE; i++) {
        char c = t[i].lhs;
        if(visited[c-'A'] == 1) continue; 
        int ans[256] = {0};
        trailing(c, ans);
        printf("%c -> ", c);
        for(int j=0; j<256; j++) {
            if(ans[j] == 1) {
                printf("%c, ", (char)j);
            }
        }
        printf("\n");
        visited[c-'A'] = 1;
    }
    return 0;    
}