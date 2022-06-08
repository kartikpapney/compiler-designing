#include<stdio.h>

int decimalToOctal(int n)
{
    int octal=0;
    int i = 1;
	
    while (n!=0)
    {
        octal+= (n%8)*i;
        n/=8;
        i*=10;
    }
    return octal;
}

int main()
{

	FILE* fp = fopen("test.txt","r");
	while(!feof(fp))
	{
		char c = getc(fp);
		int c_to_int = (int) c;
		int octal=decimalToOctal(c_to_int);
		if(octal<10) printf("00%d ", octal);
		else if(octal<100) printf("0%d ", octal);
		else printf("%d ",octal);
	}
	fclose(fp);
	return 0;
}
