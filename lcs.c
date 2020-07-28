#define MAXLENGTH 200
#include"main.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>


int bStrcmp(char *str1, char *str2) //used if bFlag is 1(ignores change in amount of existing white spaces)
{
	int i = 0, j = 0;
	while(str1[i] != '\0' && str2[j] != '\0') 
	{
		if((str1[i] == str2[j]) || (str1[i] == '\t' && str2[j] == ' ') || (str1[i] == ' ' && str2[j] == '\t')) 
		{
			if(str1[i] == ' ' || str1[i] == '\t') 
			{
				while(str1[i] == ' ' || str1[i] == '\t')
					i++;
				while(str2[j] == ' ' || str2[j] == '\t')
					j++;
			}
			else 
			{
				i++;
				j++;
			}
		}
		else
			return str1[i] - str2[j];
	}
	if(str1[i] == '\0' && str2[j] == '\0')
		return 0;
	else
		return str1[i] - str2[j];
}

int wStrcmp(char *str1, char *str2) //used if wFlag is 1(ignores all the white spaces)
{
	int i = 0, j = 0;
	while(str1[i] != '\0' && str2[j] != '\0') 
	{
		while(str1[i] == ' ' || str1[i] == '\t')
			i++;
		while(str2[j] == ' ' || str2[j] == '\t')
			j++;
		if(str1[i] == str2[j]) 
		{
			i++;
			j++;
		}
		else
			return str1[i] - str2[j];
	}
	if(str1[i] == '\0' && str2[j] == '\0')
		return 0;
	else
		return str1[i] - str2[j];
}

int iStrcmp(char *str1, char *str2) //used if iFlag is 1(ignores uppercase and lowercase)
{
	int i = 0, s1, s2;
	while(str1[i] != '\0' && str2[i] != '\0') 
	{
		s1 = str1[i];
		s2 = str2[i];
		if((s1 == s2) || (s1 == (s2 - 32)) || (s1 == (s2 + 32)))
			i++;
		else
			return s1 - s2;
	}
	if(str1[i] == '\0' && str2[i] == '\0')
		return 0;
	else
		return str1[i] - str2[i];
}


/* Utility function to get max of 2 integers */
int max(int a, int b)
{
	 return (a > b)? a : b; 
}

int lenlcs(char **a, char **b, int len1, int len2, char**argv)
{
	int i, j;
	int L[len1 + 1][len2 + 1];

	/*below flags represent the status of the options specified in the command line, if mention in comman line then they
   	are reset*/
	int bFlag = 0;
	int iFlag = 0;
	int wFlag = 0;

	if(!strcmp(argv[1], "-i"))
		iFlag = 1;
	else if(!strcmp(argv[1], "-b"))
		bFlag = 1;
	else if(!strcmp(argv[1], "-w"))
		wFlag = 1;
	
	for(j = 0; j <= len2; j++)
	{
		L[0][j] = 0;
	}
	for(i = 0; i <= len1; i++)
	{	
		L[i][0] = 0;
	}
	for(i = 1; i <= len1; i++)
	{
		for(j = 1; j <= len2; j++)
		{
			if(len1 == 0 || len2 == 0)
				L[i][j] = 0;
			else if(!strcmp(a[i - 1], b[j - 1])  ||
				(!iStrcmp(a[i - 1], b[j - 1]) && iFlag) ||
				(!wStrcmp(a[i - 1], b[j - 1]) && wFlag) ||
				(!bStrcmp(a[i - 1], b[j - 1]) && bFlag) )
			{
				L[i][j] = 1 + L[i - 1][j - 1];
			}		
 			else 
				L[i][j] = max(L[i - 1][j], L[i][j - 1]);
		}
	}
	return L[len1][len2];
}

