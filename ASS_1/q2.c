#include<stdio.h>
#include<string.h>

int main()
{

	FILE* fp = fopen("test.txt","r");

	int field_no;
	printf("Enter the field number :");
	scanf("%d",&field_no);
	while(!feof(fp))
	{
		char s[100];
		fgets(s, sizeof(s), fp);
		int idx = 0;
		for(int i=0; i<strlen(s); i++) {
			if(idx == field_no-1) {
				while(i < strlen(s) && !(s[i] == ' ' || s[i] == '\n')) printf("%c", s[i++]);
				printf("\n");
				break;
			}
			char c = s[i];
			if(c == ' ') {
				idx++;
			}
		}
	}
	fclose(fp);
	return 0;
}
