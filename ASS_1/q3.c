#include<stdio.h>

int main()
{
	char name[20];
	int rollno;
	char srollno[20];
	int select_file;
	printf("Enter 1: For txt && 2 for bin: ");
	scanf("%d",&select_file);
	
	if(select_file==1)
	{
		FILE* fp = fopen("test2.txt","w");
		for(int i=1;i<=10;i++)
		{
			printf("Name? \n");
			scanf("%s",name);
			printf("Roll No?\n");
			scanf("%3d",&rollno);
			fputs(name,fp);
			fputs(" ",fp);
			sprintf(srollno,"%d",rollno);
			fputs(srollno,fp);
			fputs("\n",fp);
		}
		fclose(fp);

	} else if(select_file==2) {
		FILE *fp2 = fopen("test2.bin","w");
		for(int i=1;i<=10;i++)
		{
			printf("Name?\n");
			scanf("%s",name);
			printf("Roll Number?\n");
			scanf("%3d",&rollno); 	
			fwrite(&name, sizeof(name), 1, fp2);
			sprintf(srollno,"%d",rollno);
			fwrite(&rollno, sizeof(rollno), 1, fp2);
		}
		fclose(fp2);
    }
	return 0;

}
