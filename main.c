#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include "main.h"
int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;
	char **q, **r;
	int l1, l2, i;
	struct lcslines x;
	char *file1, *file2;
	file1 = (char*)malloc(sizeof(char) * 100);
	if(file1 == NULL)
	{
		perror("malloc failed\n");
		exit(1);
	}
	file2 = (char*)malloc(sizeof(char) * 100);
	if(file2 == NULL)
	{
		perror("malloc failed\n");
		exit(1);
	}

	if(argc < 3)
	{
		if(strcmp(argv[1], "--help") == 0)
		{
			help();
			return 0;
		}
		else
		{
			perror("invalid input\n");
			return errno;
		}
	}
	switch(argc)
	{
		case 3:
			strcpy(file1, argv[1]);
			strcpy(file2, argv[2]);
			fp1 = fopen(argv[1], "r+");
			if(!fp1)
			{
				perror("fopen fails\n");
				return errno;
			}
			fp2 = fopen(argv[2], "r+");
			if(!fp2)
			{
				perror("fopen fails\n");
				return errno;
			}
			break;

		case 4:
			strcpy(file1, argv[2]);
			strcpy(file2, argv[3]);
			fp1 = fopen(argv[2], "r+");
			if(!fp1)
			{
				perror("fopen fails\n");
				return errno;
			}
			fp2 = fopen(argv[3], "r+");
			if(!fp2)
			{
				perror("fopen fails\n");
				return errno;
			}
			break;
		default:
			break;
	}
	
	// returns if two input files are identical			
	if(!strcmp(file1, file2))
		return 0;		
	
	l1 = length(fp1);   //give no of lines in file1 and file2
	l2 = length(fp2);
	
	fseek(fp1, 0, SEEK_SET);	// sets the file pointer to start of file
	fseek(fp2, 0, SEEK_SET);

	q = readline(fp1);         //read lines from files
	r = readline(fp2);
	
        
	output(q, r, l1, l2, argv, file1, file2);
	free(file1);
	free(file2);
	fclose(fp1);
	fclose(fp2);
	return 0;
}
