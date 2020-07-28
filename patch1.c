#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include"main.h"

/* this function will patch the given file and it will not return anything*/
void upatch(FILE *fp1, FILE *fp2, char *file1)
{
	char *line1, *line2, *line3;
	char **pfile;
	FILE *fptmp;
	fptmp = fopen("tmpfile", "w+");
	if(!fptmp)
	{
		perror("fopen fails\n");
	}
	int plen, i, j;
	line1 = (char*)malloc(sizeof(char) * 1024);
	if(line1 == NULL)
	{
		perror("malloc failed\n");
		exit(1);
	}
	line2 = (char*)malloc(sizeof(char) * 1024);
	if(line2 == NULL)
	{
		perror("malloc failed\n");
		exit(1);
	}
	line3 = (char*)malloc(sizeof(char) * 1024);
	if(line3 == NULL)
	{
		perror("malloc failed\n");
		exit(1);
	}
	
	//setting the file pointer to 4th line
	fgets(line1, 1024, fp2);
	fgets(line2, 1024, fp2);
	fgets(line3, 1024, fp2);
	//reading the content of patch file	
	pfile = readline(fp2);
	
	//setting file pointer to start of patch file
	fseek(fp2, 0, SEEK_SET);
	plen = length(fp2);

	i = 0;
	for(i = 0; i < plen - 3; i++)
	{
		if(pfile[i][0] == '+')
		{
				for(j = 1; j < strlen(pfile[i]); j++)
					fprintf(fptmp, "%c", pfile[i][j]);
				fprintf(fptmp, "%c", '\n');		
		}
		if(pfile[i][0] == '-')
		{
			
		}
		if(pfile[i][0] == ' ')
		{
			
			for(j = 1; j < strlen(pfile[i]); j++)
					fprintf(fptmp, "%c", pfile[i][j]);
			fprintf(fptmp, "%c", '\n');
		}
		
	}
	rename("tmpfile", file1); 
	
	free(line1);
	free(line2);
	free(line3);
	fclose(fptmp);
}	


void cpatch(FILE *fp1, FILE *fp2, char *file1)
{
	char **p, **q;
	FILE *fptmp;
	fptmp = fopen("tmpfile", "w+");
	if(!fptmp)
	{
		perror("fopen fails\n");
	}
	int plen, i, j;
	p = (char**)malloc(sizeof(char*) * 1024);
	if(p == NULL)
	{
		perror("insufficient storage");
		exit(1);
	}
        for(i = 0; i < 100; i++) 
	{
        	p[i] = (char*)malloc(sizeof(char) * 100);
		if(p[i] == NULL)
		{
			perror("insufficient storage");
			exit(1);
		}	
   	}
	q = (char**)malloc(sizeof(char*) * 1024);
	if(q == NULL)
	{
		perror("insufficient storage");
		exit(1);
	}
        for(i = 0; i < 100; i++) 
	{
        	q[i] = (char*)malloc(sizeof(char) * 100);
		if(q[i] == NULL)
		{
			perror("insufficient storage");
			exit(1);
		}	
   	}
	i = 0;
	while(fgets(p[i], 1024, fp2) != NULL)
	{
		if(p[i][0] == '-' && p[i][1] == '-' && p[i][2] == '-' && i != 1)
			break;
		i++;
	}
	i = 0;
	
	while(fgets(q[i], 1024, fp2) != NULL)
	{
		i++;
	}
	
	plen = i;	
	i = 0;
	for(i = 0; i < plen ; i++)
	{
		
		if(q[i][0] == '+')
		{
			for(j = 1; j < strlen(q[i]); j++)
				fprintf(fptmp, "%c", q[i][j]);		
		}
		if(q[i][0] == '!')
		{
			for(j = 1; j < strlen(q[i]); j++)
				fprintf(fptmp, "%c", q[i][j]);	
		}
		if(q[i][0] == ' ')
		{
			
			for(j = 1; j < strlen(q[i]); j++)
					fprintf(fptmp, "%c", q[i][j]);
		}
		
	}
	rename("tmpfile", file1); 
	fclose(fptmp);
}

	
int main(int argc, char *argv[])
{
	FILE *fp1, *fp2;
	char *line1, *line2;
	int upatchflag = 0;
	char *file1, *file2;
	line1 = (char*)malloc(sizeof(char) * 1024);
	if(line1 == NULL)
	{
		perror("malloc failed\n");
		exit(1);
	}
	line2 = (char*)malloc(sizeof(char) * 1024);
	if(line2 == NULL)
	{
		perror("malloc failed\n");
		exit(1);
	}
	
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
		perror("Invalid input\n");
		return errno;
	}
	
			
	fp1 = fopen(argv[1], "rw+");
	if(!fp1)
	{
		perror("fopen fails\n");
		return errno;
	}
	fp2 = fopen(argv[2], "rw+");
	if(!fp2)
	{
		perror("fopen fails\n");
		return errno;
	}
	strcpy(file1, argv[1]);
	strcpy(file2, argv[2]);
	//read the first two lines from the patch file and check if there are no lines if yes then quit
	if(!fgets(line1, 1024, fp2) || !fgets(line2, 1024, fp2))
		return 0;
	

	/*The patch file may have unified diff or context diff format. To check it has normal diff we have to check
	  if it has either --- or *** in the first line*/
	if( !strstr(line1, "***") && strstr(line1, "---"))
	{
		upatchflag = 1;
	}
	fseek(fp2, -(strlen(line1) + strlen(line2)), SEEK_SET);
	printf("patching file %s\n", argv[1]);

	//calling the patch function depeding on the type of diff in the patch file
	if(upatchflag == 1)
	{
		upatch(fp1, fp2, file1);
	}
	else
	{
		cpatch(fp1, fp2, file1);
	}
	
	free(line1);
	free(line2);
	free(file1);
	free(file2);
	//closing the files 
	fclose(fp1);
	fclose(fp2);
	return 0;
}
