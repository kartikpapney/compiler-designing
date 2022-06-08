/*
	Write a program that computes the FIRST and FOLLOW sets of the non-terminals of a given grammar. Also, it creates an LL(1) parsing table for the grammar.
	Hint: Take a suitable grammar and represent it in appropriate data structures.
*/


#include<stdio.h>
#include<ctype.h>
#include<string.h>

int first[256][256] = {0};
int follow[256][256] = {0};
int MAX_SIZE = 10;
char start_symbol = 'S';
struct Rule {
	char lhs;
	char* rhs;
};
struct Rule production[] = {
	{'S', "w(C)bAe"},
	{'O', "p"},
	{'C', "iOn"},
	{'C', "iOi"},
	{'A', "L;A"},
	{'A', "f"},
	{'L', "i=E"},
	{'E', "T*F"},
	{'T', "i"},
	{'F', "n"},
};

void find_first(char LHS, int arr[]) {
	for(int i=0; i<MAX_SIZE; i++) {
        if(production[i].lhs == LHS) {
            char* rhs = production[i].rhs;
            int size = strlen(rhs);
            if(rhs[0]>='A' && rhs[0]<='Z') {
                if(rhs[0] != LHS) find_first(rhs[0], arr);
            } else {
                arr[rhs[0]] = 1;
            }
        }
    }
}

void find_follow(char c, int arr[]) {
	for(int i=0; i<MAX_SIZE; i++) {
		char* rhs = production[i].rhs;
		int len = strlen(rhs);
		for(int j=0; j<len; j++) {
			char ch = rhs[j];
			if(ch == c) {
				if(j == len-1) {
					if(production[i].lhs != c) {
						find_follow(production[i].lhs, arr);
					}
				}
				else {
					char chf = rhs[j+1];
					if(!(chf >='A' && chf <= 'Z')) {
						arr[chf] = 1;
					} else {
						find_first(chf, arr);
					}
				}
			}
		}
	}
}

int main() {
	printf("Submitted By: CSB19047 (Kartik Papney) \n");
	printf("Question: Write a program that computes the FIRST and FOLLOW sets of the non-terminals of a given grammar. Also, it creates an LL(1) parsing table for the grammar.\n\n");
	for(int i=0; i<MAX_SIZE; i++) {
		printf("%c -> %s\n", production[i].lhs, production[i].rhs);
	}
	printf("\n");
	int LHS[256] = {0};
	int RHS[256] = {0};
	for(int i=0; i<MAX_SIZE; i++) {
		char c = production[i].lhs;
		LHS[c] = 1;
	}
	for(int i=0; i<256; i++) {
		if(LHS[i] == 1) {
			printf("FIRST(%c) -> {", (char)i);
			find_first((char)(i), first[i]);
			for(int j=0; j<256; j++) {
				if(first[i][j] == 1) {
					printf("%c, ", (char)j);
				}
			}
			printf("}\n");
		}
	}
	// follow of start symbol is dollar ...
	follow[start_symbol]['$'] = 1;
	// remaining... 
	for(int i=0; i<MAX_SIZE; i++) {
		char* rhs = production[i].rhs;
		int len = strlen(rhs);
		for(int j=0; j<len; j++) {
			char c = rhs[j];
			if(c >= 'A' && c <= 'Z') RHS[c] = 1;
		}
	}
	RHS[start_symbol] = 1;
	printf("----------------------------------------------------\n");

	for(int i=0; i<256; i++) {
		if(RHS[i] == 1) {
			printf("FOLLOW(%c) -> {", (char)i);
			find_follow(i, follow[i]);
			for(int j=0; j<256; j++) {
				if(follow[i][j] == 1) {
					printf("%c, ", (char)j);
				}
			}
			printf("}\n");
		}
	}

}





