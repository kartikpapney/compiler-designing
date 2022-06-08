#include<stdio.h>

void print_using_fgets(FILE* fp)
{
	char line[500];
    int i=1;
	while(fgets(line,sizeof(line),fp)) {
		printf("%d %s",i++,line);
	}
	printf("\n");
}

void print_using_fgetc(FILE* fp)
{
	int i=1;
	printf("%d ",i++);
	while(!feof(fp))
	{
		char c=fgetc(fp);
		printf("%c",c);
		if(c=='\n')
		{
			printf("%d ",i++);
		}
	}
}

int main()
{
	FILE* fp = fopen("test.txt","r");
   	print_using_fgets(fp);
	fp = fopen("test.txt","r");
	printf("--------------------------\n");
	print_using_fgetc(fp);
	fclose(fp);
	return 0;
}