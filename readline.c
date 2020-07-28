#define MAXLENGTH 500
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include"main.h"

/* This function will read the content of file in malloced memory line by line*/
char **readline(FILE *file)
{
	char **p;
	int i = 0, j = 0;
	char ch;
	p = (char**)malloc(sizeof(char*) * 1024);
        if(p == NULL)
	{
		perror("insufficient storage");
		exit(1);
	}
        for(i = 0; i < 100; i++) 
	{
        	p[i] = (char*)malloc(sizeof(char) * MAXLENGTH);
		if(p[i] == NULL)
		{
			perror("insufficient storage");
			exit(1);
		}	
   	}
	i = 0;
	ch = getc(file);
	while(ch != EOF)
	{
		if(ch == '\n')
		{
			p[i][j] = '\0';
			i++;
			j = 0;
		}
		if(ch != '\n')
		{
			p[i][j] = ch;
			j++;
		}
		ch = getc(file);
	}
	
	
	return p;
}

//function returns the no of lines in file
int length(FILE *fp)
{
	char filearr[100][MAXLENGTH];
	int i = 0, j = 0, count = 0;
	char ch;
	while(fscanf(fp, "%c", &ch) != EOF)
	{
		if(ch == '\n')
		{
			filearr[i][j] = '\0';
			j = 0;
			i++;
		}
		if(ch != '\n')
		{
			filearr[i][j] = ch;
			j++;
		}
	}
	count = i;
	return count;
}
