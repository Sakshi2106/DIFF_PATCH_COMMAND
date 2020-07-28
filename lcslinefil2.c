#define MAXLENGTH 200
#include"main.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

 

/* Returns structure whose members are array which store the index of lcs line*/
struct lcslines lcsline(char **a, char **b, int len1, int len2, char**argv) 
{
	int i, j;
	int k;
 	k = 0; 
  	int index;
	struct lcslines lineno, lineno1;
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
			else if(!strcmp(a[i - 1], b[j - 1]) ||
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
  	 
   	
   	// Start from the right-most-bottom-most corner and 
   	// one by one store characters in lcs[] 
   	i = len1, j = len2, index = 0; 
   	while (i > 0 && j > 0) 
   	{ 
     	 	// If current character in a and b are same, then 
      		// current character is part of LCS 
     		 if (!strcmp(a[i - 1], b[j - 1]) ||
		     (!iStrcmp(a[i - 1], b[j - 1]) && iFlag) ||
		     (!wStrcmp(a[i - 1], b[j - 1]) && wFlag) ||
		     (!bStrcmp(a[i - 1], b[j - 1]) && bFlag)) 
		{
			//strcpy(lcs[index] , a[i - 1]); // Put current character in result 
			lineno.fil1[k] = i;
			lineno.fil2[k] = j;
			
			 i--; j--; index++; k++;     // reduce values of i, j and index	
		}		
  
     	 	// If not same, then find the larger of two and 
     		 // go in the direction of larger value 
      		else if (L[i-1][j] > L[i][j-1]) 
         		i--; 
      		else
         		j--; 
   	}
	int index1 = k;
	
	for(i = 0, k = index - 1; i < index1, k >= 0; i++, k--)
	{
		lineno1.fil1[i]	= lineno.fil1[k];
		lineno1.fil2[i]	= lineno.fil2[k];
	}
	
	return lineno1;
 }

