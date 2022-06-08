/*

Submitted By CSB19047 (Kartik Papney)

Assume that in the assembly language discussed in the theory class, there is a statement -DEFINE name replace-pattern
The meaning of the statement is that afterwards in the program wherever the pattern name occurs, it will be replaced by replace-pattern. For example if there is the statement
DEFINE TRUE 1,
then everywhere in the subsequent part in the program if there is the word TRUE, it will be replaced by 1. An input program may contain several such define statements. Write a program to implement this feature.
[This is a very simple macro pre-processor]

*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

FILE *in;
FILE *out;
struct Macro
{
  char mname[100];
  int num;
} mt[100];
int count;

int cTable()
{
  char c;
  char temp[50];
  int j = 0;
  int count = 0;
  while ((c = fgetc(in)) != EOF)
  {
    char c2 = fgetc(in);
    char c3 = fgetc(in);
    char c4 = fgetc(in);
    char c5 = fgetc(in);
    char c6 = fgetc(in);
    if (c == 'D' && c2 == 'E' && c3 == 'F' && c4 == 'I' && c5 == 'N' && c6 == 'E')
    {
      int i = 0;
      while (isspace(c6 = fgetc(in))) ;
      ungetc(c6, in);
      while (isalnum(c6 = fgetc(in)))  temp[i++] = c6;
      temp[i] = '\0';
      strcpy(mt[j].mname, temp);
      i = 0;
      while (isspace(c6 = fgetc(in)));
      ungetc(c6, in);
      while (isalnum(c6 = fgetc(in))) temp[i++] = c6;
      temp[i] = '\0';
      mt[j++].num = atoi(temp);
      count++;
    }
    else {
      ungetc(c6, in);
      ungetc(c5, in);
      ungetc(c4, in);
      ungetc(c3, in);
      ungetc(c2, in);
    }

    if (c == '\n')
    {
      if ((c2 = fgetc(in)) != '#')
      {
        ungetc(c2, in);
        break;
      }
    }
  }
  return count;
}

int cmp(char temp[])
{
  for (int i = 0; i < count; i++)
  {
    int flag = 0;
    for (int j = 0; temp[j] != '\0'; j++)
    {
      if (temp[j] != mt[i].mname[j])
      {
        flag = 1;
        break;
      }
    }

    if (flag == 0) return i;
  }
  return -1;
}

void rTable()
{
  char c;
  char temp[100];
  int i;
  while ((c = fgetc(in)) != EOF)
  {
    if (isalpha(c))
    {
      i = 0;
      temp[i++] = c;
      while (!isspace(c = fgetc(in)))
      {
        if (c == EOF)
          break;
        else
          temp[i++] = c;
      }
      temp[i] = '\0';
      int res = cmp(temp);
      if (res != -1)
      {

        fprintf(out, "%d ", mt[res].num);
      }
      else
      {
        fprintf(out, "%s ", temp);
      }
    }

    if (c == '\n')
    {
      fprintf(out, "%s", "\n");
    }
  }

  fclose(in);
  fclose(out);
}

int main()
{

  in = fopen("input.txt", "r");
  out = fopen("output.txt", "w");
  count = cTable(in);
  
  rTable(in, out);
  return 0;
}