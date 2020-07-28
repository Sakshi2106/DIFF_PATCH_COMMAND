#define MAXLENGTH 200
#include"main.h"
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

// function prints the output of diff o the terminal depending on the options
void output(char **a, char **b, int len1, int len2, char**argv, char *file1, char *file2)
{
	struct lcslines x;
	int  i, n, k, j, l;
	struct stat filestat1;
	struct stat filestat2;
	stat(*a, &filestat1);
	stat(*b, &filestat2);
	char t1[100], t2[100];
	strftime(t1, 100, "%Y-%m-%d" "%H:%M:%S", localtime(&filestat1.st_mtime));
	strftime(t2, 100, "%Y-%m-%d" "%H:%M:%S", localtime(&filestat2.st_mtime));
	
	x = lcsline(a, b,  len1, len2, argv);
	n = lenlcs(a, b, len1, len2, argv);
	//printf("%d\n", n);	
	if(n == len1 &&  n == len2)
		return;
	if(strcmp(argv[1], "-u") == 0)
	{
	
		printf("--- %s\t%s\n", file1, t1);
		printf("+++ %s\t%s\n", file2, t2);
		if(n == 0 && len2 == 0)
			printf("@@ -1,%d +0,%d @@\n", len1, len2);
		else if(n == 0 && len1 == 0)
			printf("@@ -0,%d +1,%d @@\n", len1, len2);
		else
			printf("@@ -1,%d +1,%d @@\n", len1, len2);
		if(n == 0 && len1 == len2)
		{
			for(k = 0; k < len1; k++)
				printf("- %s\n", a[k]);
			for(k = 0; k < len2; k++)
				printf("+ %s\n", b[k]);
		}
		if(n == 0 && len1 > len2)
		{
			printf("1,%dd0\n", len1);
			for(k = 0; k < len1; k++)
				printf("- %s\n", a[k]);
		}
		if(n == 0 && len1 < len2)
		{
			printf("0a1%d\n", len2);
			for(k = 0; k < len2; k++)
				printf("+ %s\n", b[k]);
		}	
		for(i = 0, j = 0; i < n, j < n; i++, j++)
		{
			if(x.fil1[i] > x.fil2[j] && i == 0 && j == 0)
			{
				k  = i;
				
				while(k != (x.fil1[i] - 1))
				{
					
					printf("- %s\n", a[k]);
					k++;
				}
				printf("  %s\n", a[x.fil1[i] - 1]);
			}
			if(x.fil1[i] < x.fil2[j] && i == 0 && j == 0)
			{
				k = j;
				while(k != (x.fil2[j] - 1))
				{
					printf("+ %s\n", b[k]);
					k++;
				}
				printf("  %s\n", b[x.fil2[j] - 1]);
			}	
			 if((x.fil1[i] - x.fil1[i - 1] > 1) && (x.fil2[j] - x.fil2[j - 1] > 1))
			{
				k = i, l = j;
				while(x.fil1[k - 1] != x.fil1[k] - 1)
				{
					
					printf("- %s\n", a[x.fil1[k - 1]]);
					x.fil1[k - 1]++;
				}
				
				while(x.fil2[l - 1] != x.fil2[l] - 1)
				{
					printf("+ %s\n", b[x.fil2[l - 1]]);
					x.fil2[l - 1]++;
				}
				
			}
			if((x.fil1[i] - x.fil1[i - 1] == 1) &&  (x.fil2[j] - x.fil2[j - 1] == 1))
			{
				
				printf("  %s\n", a[x.fil1[i] - 1]);
			}
			 if((x.fil1[i] - x.fil1[i - 1] == 1) && (x.fil2[j] - x.fil2[j - 1] > 1))
			{
				while(x.fil1[j - 1] != x.fil1[j] - 1)
				{
					
					printf("+ %s\n", b[x.fil2[j - 1]]);
					x.fil2[j - 1]++;
				}
				printf("  %s\n", b[x.fil2[j] - 1]);
			}
			
			 if((x.fil1[i] - x.fil1[i - 1] > 1) && (x.fil2[j] - x.fil2[j - 1] == 1))
			{
				while(x.fil1[i - 1] != x.fil1[i] - 1)
				{
					
					printf("- %s\n", a[x.fil1[i - 1]]);
					x.fil1[i - 1]++;
				}
				printf("  %s\n", a[x.fil1[i] - 1]);
			}
			 if(x.fil1[i] != len1 && x.fil2[j] != len2 && i == n - 1 && j == n - 1) 
			{
			
				k = x.fil1[i], l = x.fil2[j];
				while(k != len1)
				{
					printf("- %s\n", a[k]);
					k++;
				}
				while(l != len2)
				{
					printf("+ %s\n", b[l]);
					l++;
				}
			}
			 if(x.fil1[i] == len1 && x.fil2[j] != len2)
			{
				while(x.fil2[j] != len2)
				{
					
					printf("+ %s\n", b[x.fil2[j]]);
					x.fil2[j]++;
				}
			}

			if(x.fil1[i] != len1 && x.fil2[j] == len2)
			{
				while(x.fil1[i] != len1)
				{
					
					printf("- %s\n", a[x.fil1[i]]);
					x.fil1[i]++;
				}
			}
			

			
			if(x.fil1[i] == x.fil2[j] && i == 0 && j == 0 && x.fil1[i] != 1 && x.fil2[j] != 1)
			{
				for(k = 0; k < x.fil1[i] - 1; k++)
					printf("- %s\n", a[k]);
				for(k = 0; k < x.fil2[j] - 1; k++)
					printf("+ %s\n", b[k]);
				printf("  %s\n", a[x.fil1[i] - 1]);
			}
			if(x.fil1[i] == 1 && x.fil2[j] == 1)
			{
				printf("  %s\n", a[0]);
			}
		}
	}
	else if(strcmp(argv[1], "-c") == 0)
	{
		
		printf("*** %s\t%s\n", file1, t1);
		printf("+++ %s\t%s\n", file2, t2);
		printf("***************\n");
		if(n == 0 && len1 == 0)
			printf("*** %d ****\n", len1);
		else
			printf("*** 1,%d ****\n", len1);
		if(n == 0)
		{
			for(k = 0; k < len1; k++)
				printf("! %s\n", a[k]);
		}
		if(n == 0 && len1 > len2)
		{
			printf("1,%dd0\n", len1);
			for(k = 0; k < len1; k++)
				printf("- %s\n", a[k]);
		}
		if(n == 0 && len1 < len2)
		{
			printf("0a1%d\n", len2);
			for(k = 0; k < len2; k++)
				printf("+ %s\n", b[k]);
		}	
		
		for(i = 0, j = 0; i < n, j < n; i++, j++)
		{
			if(x.fil1[i] > x.fil2[j] && i == 0 && j == 0)
			{
				for(k = 0; k < x.fil1[i] - 1; k++)
					printf("- %s\n", a[k]);
				printf("  %s\n", a[x.fil1[i] - 1]);
			}	

			if(x.fil1[i] < x.fil2[j] && i == 0 && j == 0)
			{
				printf(" %s\n", a[x.fil1[i] - 1]);
			}

			if((x.fil1[i] - x.fil1[i - 1] > 1) && (x.fil2[j] - x.fil2[j - 1] > 1))
			{
				for(k =x.fil1[i - 1] ; k < x.fil1[i] - 1; k++)
					printf("! %s\n", a[k]);
				printf("  %s\n", a[x.fil1[i] - 1]);
			}
			if((x.fil1[i] - x.fil1[i - 1] == 1) &&  (x.fil2[j] - x.fil2[j - 1] == 1))
			{
					printf(" %s\n", a[x.fil1[i] - 1]);
			}

			if((x.fil1[i] - x.fil1[i - 1] == 1) && (x.fil2[j] - x.fil2[j - 1] > 1) && n != len1)
			{
				printf(" %s\n", a[x.fil1[i] - 1]);
			}

			if((x.fil1[i] - x.fil1[i - 1] > 1) && (x.fil2[j] - x.fil2[j - 1] == 1))
			{
				for(k =x.fil1[i - 1] ; k < x.fil1[i] - 1; k++)
					printf("- %s\n", a[k]);
				printf("  %s\n", a[x.fil1[i] - 1]);
			}

			if(x.fil1[i] == len1 && x.fil2[j] != len2)
			{
				//printf(" %s\n", a[x.fil1[i] - 1]);
			}

			if(x.fil1[i] != len1 && x.fil2[j] == len2)
			{
				for(k =x.fil1[i] ; k < len1; k++)
				{
					
					printf("- %s\n", a[k]);
				}
			}
			
			
			if(x.fil1[i] != len1 && x.fil2[j] != len2 && i == n -1 && j == n - 1) 
			{
				for(k =x.fil1[i] ; k < len1; k++)
					printf("! %s\n", a[k]);
			}
			
			if(x.fil1[i] == x.fil2[j] && i == 0 && j == 0 && x.fil1[i] != 1 && x.fil2[j] != 1)
			{
				for(k = 0; k < x.fil1[j] - 1; k++)
					printf("!  %s\n", a[k]);
				printf("  %s\n", a[x.fil1[i] - 1]);
			}
			if(x.fil1[i] == 1 && x.fil2[j] == 1)
			{
				printf("  %s\n", a[0]);
			}
		}
		if(n == 0 && len2 == 0)
			printf("--- %d ----\n", len2);
		else
			printf("--- 1,%d ----\n", len2);
		if(n == 0)
		{
			for(k = 0; k < len2; k++)
				printf("! %s\n", b[k]);
		}
		for(i = 0, j = 0; i < n, j < n; i++, j++)
		{
			if(x.fil1[i] > x.fil2[j] && i == 0 && j == 0)
			{
				printf(" %s\n", b[x.fil2[j] - 1]);
			}

			if(x.fil1[i] < x.fil2[j] && i == 0 && j == 0)
			{
				for(k = 0; k < x.fil2[j] - 1; k++)
					printf("+ %s\n", b[k]);
				printf("  %s\n", b[x.fil2[j] - 1]);
			}

			if((x.fil1[i] - x.fil1[i - 1] > 1) && (x.fil2[j] - x.fil2[j - 1] > 1))
			{
				for(k =x.fil2[j - 1] ; k < x.fil2[j] - 1; k++)
					printf("! %s\n", b[k]);
				printf("  %s\n", a[x.fil1[i] - 1]);
			}
			if((x.fil1[i] - x.fil1[i - 1] == 1) &&  (x.fil2[j] - x.fil2[j - 1] == 1) && (n != len2))
			{
					k = x.fil2[j];
					printf(" %s\n", b[k - 1]);
			}

			if((x.fil1[i] - x.fil1[i - 1] == 1) && (x.fil2[j] - x.fil2[j - 1] > 1))
			{
				for(k =x.fil2[j - 1] ; k < x.fil2[j] - 1; k++)
					printf("+ %s\n", b[k]);
				printf("  %s\n", b[x.fil2[j] - 1]);
			}	

			if((x.fil1[i] - x.fil1[i - 1] > 1) && (x.fil2[j] - x.fil2[j - 1] == 1) && (n != len2))
			{
				printf(" %s\n", b[x.fil2[j] - 1]);
			}

			if(x.fil1[i] != len1 && x.fil2[j] == len2)
			{
			}

			if(x.fil1[i] != len1 && x.fil2[j] != len2 && i == n -1 && j == n - 1) 
			{
				for(k =x.fil1[j] ; k < len2; k++)
					printf("! %s\n", b[k]);
			}
			if(x.fil1[i] == len1 && x.fil2[j] != len2)
			{
				for(k = x.fil2[j] ; k < len2; k++)
				{
					printf("+ %s\n", b[k]);
				}
			}
			if(x.fil1[i] == x.fil2[j] && i == 0 && j == 0 && x.fil1[i] != 1 && x.fil2[j] != 1)
			{
				for(k = 0; k < x.fil2[j] - 1; k++)
					printf("!  %s\n", b[k]);
				printf("  %s\n", b[x.fil1[j] - 1]);
			}
			if(x.fil1[i] == 1 && x.fil2[j] == 1)
			{
				printf("  %s\n", b[0]);
			}
	
		}
	}
	else
	{	
		if(n == 0 && len1 == len2)
		{
			printf("1,%dc1,%d\n", len1, len2);
			for(k = 0; k < len1; k++)
				printf("< %s\n", a[k]);
			printf("---\n");
			for(k = 0; k < len2; k++)
				printf(">  %s\n", b[k]);
		}
		if(n == 0 && len1 > len2)
		{
			printf("1,%dd0\n", len1);
			for(k = 0; k < len1; k++)
				printf("< %s\n", a[k]);
		}
		if(n == 0 && len1 < len2)
		{
			printf("0a1%d\n", len2);
			for(k = 0; k < len2; k++)
				printf("> %s\n", b[k]);
		}		
		for(i = 0, j = 0; i < n, j < n; i++, j++)
		{
			
			if(x.fil1[i] > x.fil2[j] && i == 0 && j == 0)
				delete(a, b, x.fil1[i], x.fil2[j], x, n);

			 if(x.fil1[i] < x.fil2[j] && i == 0 && j == 0)
				addstart(a, b, x.fil1[i], x.fil2[i], x, n);

			 if(x.fil1[i] == x.fil2[j] && i == 0 && j ==0 && x.fil1[i] != 1 && x.fil2[j] != 1)
			{
				if(x.fil1[i] == 2 && x.fil2[j] == 2)
				{
					printf("%dc%d", x.fil1[i] - 1, x.fil2[j] - 1);
					printf("< %s\n", a[0]);
					printf("---\n");
					printf("> %s\n", b[0]);
				}
				else
				{
					printf("1,%dc1,%d\n", x.fil1[i] - 1, x.fil2[j] - 1);
					for(k = 0; k < x.fil1[i] - 1; k++)
						printf("< %s\n", a[k]);
					printf("---\n");
					for(k = 0; k < x.fil2[j] - 1; k++)
						printf("> %s\n", b[k]);
				}
			}
			 if((x.fil1[i] - x.fil1[i - 1] > 1) && (x.fil2[j] - x.fil2[j - 1] > 1))
			{
				change(a, b, x.fil1[i], x.fil2[i], x, n);
			}

			 if((x.fil1[i] - x.fil1[i - 1] == 1) && (x.fil2[j] - x.fil2[j - 1] > 1))
				addstart(a, b, x.fil1[i], x.fil2[i], x, n);

			 if((x.fil1[i] - x.fil1[i - 1] > 1) && (x.fil2[j] - x.fil2[j - 1] == 1))
				delete(a, b, x.fil1[i], x.fil2[i], x, n);

			 if(x.fil1[i] == len1 && x.fil2[j] != len2)
				addend(a, b, x.fil1[i], x.fil2[j], len2);

			 if(x.fil1[i] != len1 && x.fil2[j] == len2)
				deletend(a, b, x.fil1[i], x.fil2[j], len1);

			 if(x.fil1[i] != len1 && x.fil2[j] != len2 && i == n -1 && j == n - 1) 
			{
				changend(a, b, x.fil1[i], x.fil2[i], len1, len2);
			}
			/*if(x.fil1[i] == x.fil2[j] && i == 0 && j == 0 && x.fil1[i] != 1 && x.fil2[j] != 1)
			{
				printf("%dc%d\n",x.fil1[i], x.fil2[j]);
				for(k = 0; k < x.fil1[i] - 1; k++)
					printf("< %s\n", a[k]);
				printf("---\n");
				for(k = 0; k < x.fil2[j] - 1; k++)
					printf(">  %s\n", b[k]);
			}*/
			
		}
	}

}	



void change(char **p, char **q, int x, int z,  struct lcslines y, int a)
{
	int  r, s, i, k;
	int index, index1;
	for(i = 0; i < a; i++)
	{
		if(x == y.fil1[i])
			index = i;
	}
	for(i = 0; i < a; i++)
	{
		if(z == y.fil2[i])
			index1 = i;
	}
	if((x - y.fil1[index -1] != 1) && (z - y.fil2[index1 - 1] != 1))
	{
	 	 r = x - y.fil1[index - 1];
		s = z - y.fil2[index1 - 1];
		if(r == 2 && s > 2)
		{		
			printf("%dc%d,%d\n", y.fil1[index - 1] + 1, y.fil2[index1 - 1] + 1, y.fil2[index1] - 1);
			printf("< %s\n", p[y.fil1[index - 1] + 1 - 1]);
			printf("---\n");
			for(k = y.fil2[index1 - 1] + 1; k <= y.fil2[index1] - 1; k++)
				printf("> %s\n", q[k - 1]);
		}
		if(r > 2 && s == 2)
		{
			printf("%d,%dc%d\n", y.fil1[index - 1] + 1, y.fil1[index] - 1, y.fil2[index1] - 1);
			for(k = y.fil1[index - 1] + 1; k <= y.fil1[index] - 1; k++)
				printf("< %s\n", p[k - 1]);
			printf("---\n");
			printf("> %s\n", q[y.fil2[index1] - 1 - 1]);
		}
		if(r > 2 && s > 2)
		{
			printf("%d,%dc%d,%d\n", y.fil1[index - 1] + 1, y.fil1[index] - 1, y.fil2[index1 - 1] + 1, y.fil2[index1] - 1);
			for(k = y.fil1[index - 1] + 1; k <= y.fil1[index] - 1; k++)
				printf("< %s\n", p[k - 1]);
			printf("---\n");
			for(k = y.fil2[index1 - 1] + 1; k <= y.fil2[index1] - 1; k++)
				printf("> %s\n", q[k - 1]);
		}
		if(r == 2 && s == 2)
		{
			printf("%dc%d\n",y.fil1[index - 1] + 1, y.fil2[index1] - 1);
			printf("< %s\n", p[y.fil1[index - 1] + 1 - 1]);
			printf("---\n");
			printf("> %s\n", q[y.fil2[index1] - 1 - 1]);
		}
	}
}
void addstart(char **p, char **q, int x, int z, struct lcslines y, int r) // add at middle and start
{
	int  i, j, k;
	int index, index1;
	for(i = 0; i < r; i++)
	{
		if(x == y.fil1[i])
			index = i;
	}
	for(i = 0; i < r; i++)
	{
		if(z == y.fil2[i])
			index1 = i;
	}
	if(index == 0 && index1 == 0)
	{
		j = z - x;
		if(j == 1)
		{
			printf("%da%d\n", x - 1, z - 1);
			printf("> %s\n", q[z - 1 - 1]);
		}
		if(j > 1)
		{
			printf("%da%d,%d\n", x - 1, z - j, z - 1);
			for(i = z - j; i <= z - 1; i++)
				printf("> %s\n", q[i - 1]);
		}
	}
	if(index != 0 && index1 != 0)
	{
		k = y.fil2[index1] - y.fil2[index1 - 1];
		if(k == 2)
		{
			printf("%da%d\n", x - 1, y.fil2[index1 - 1] + 1);
			printf("> %s\n", q[y.fil2[index1 - 1] + 1 - 1]);
		}
		if(k > 2)
		{
			printf("%da%d,%d\n", x - 1, y.fil2[index1 - 1] + 1, y.fil2[index1] - 1);
			for(i =  y.fil2[index1 - 1] + 1; i <= y.fil2[index1] - 1; i++)
				printf("> %s\n", q[i - 1]);
		}	
	}
}
void addend(char **p, char **q, int x, int z, int l2) // add at end
{ 
	int k, i;
	k = l2 - z;
	if(k == 1)
	{
		printf("%da%d\n", x, z + k);
		printf("> %s\n", q[z + k - 1]);
	}
	if(k > 1)
	{
		printf("%da%d,%d\n", x, z + 1, l2);
		for(i = z + 1; i <= l2; i++)
			printf("> %s\n", q[i - 1]);
	}
}
void delete(char **p, char **q, int x, int z, struct lcslines y, int r) //delete at start and middle
{
	
	int  i, j, k;
	int index, index1;
	for(i = 0; i < r; i++)
	{
		if(x == y.fil1[i])
			index = i;
	}
	for(i = 0; i < r; i++)
	{
		if(z == y.fil2[i])
			index1 = i;
	}
	if(index == 0 && index1 == 0)
	{
		j = x - z;
		if(j == 1)
		{
			printf("%dd%d\n", x - 1, z - 1);
			printf("< %s\n", p[x - 1 - 1]);
		}
		if(j > 1)
		{
			printf("%d,%dd%d\n", x - j, x - 1, z - 1);
			for(i = x - j; i <= x - 1; i++)
				printf("< %s\n", p[i - 1]);
		}
	}
	if(index != 0 && index1 != 0)
	{
		k = y.fil1[index1] - y.fil1[index1 - 1];
		if(k == 2)
		{
			
			printf("%dd%d\n", y.fil1[index] - 1 , z - 1);
			printf("< %s\n", p[y.fil1[index] - 1 - 1]);
		}
		if(k > 2)
		{
			printf("%d,%dd%d\n",  y.fil1[index - 1] + 1, y.fil1[index] - 1,z - 1);
			for(i =  y.fil1[index - 1] + 1; i <= y.fil1[index] - 1; i++)
				printf("< %s\n", p[i - 1]);
		}	
	}
}
void deletend(char **p, char **q, int x, int z, int l1) // delete at end
{
	int k, i;
	k = l1 - x;
	if(k == 1)
	{
		printf("%dd%d\n", x + k, z);
		printf("< %s\n", p[x + k - 1]);
	}
	if(k > 1)
	{
		printf("%d,%dd%d\n", x + 1, l1, z);
		for(i = x + 1; i <= l1; i++)
			printf("< %s\n", p[i - 1]);
	}
} 
void changend(char **p, char **q, int x, int z, int l1, int l2)// change at end
{
	int i, j, k;
	j = l1 - x;
	k = l2 - z;
	if(j == 1 &&  k == 1)
	{
		printf("%dc%d\n", x + 1, z + 1);
		printf("< %s\n", p[x + 1 - 1]);
		printf("---\n");
		printf("> %s\n", q[z + 1 - 1]);
	}
	else if(j > 1 && k == 1)
	{
		printf("%d,%dc%d\n", x + 1, l1, z + 1);
		for(i = x + 1; i <= l1; i++)
			printf("< %s\n", p[i - 1]);
		printf("---\n");
		printf("> %s\n", q[z + 1 - 1]);
	}
	else if(j == 1 && k > 1)
	{
		printf("%dc%d, %d\n", x + 1, z + 1, l2);
		printf("< %s\n", p[x + 1 - 1]);
		printf("---\n");
		for(i = z + 1; i <= l2; i++)
			printf("> %s\n", q[i - 1]);
	}	
	else if(j > 1 && k > 1)
	{
		printf("%d,%dc%d,%d\n", x + 1, l1, z + 1, l2);
		for(i = x + 1; i <= l1; i++)
			printf("< %s\n", p[i - 1]);
		printf("---\n");
		for(i = z + 1; i <= l2; i++)
			printf("> %s\n", q[i - 1]);
	}
}

// function is executed when user asks for help and enters --help in command line argument
void help( )
{
	printf("Usage: diff [OPTION]... FILES\n");
	printf("Compare FILES line by line.\n");
	printf("\n");
	printf("Mandatory arguments to long options are mandatory for short options too.\n");
	printf("      --normal                  output a normal diff (the default)\n");
	printf("  -c, -C NUM, --context[=NUM]   output NUM (default 3) lines of copied context\n");
	printf("  -u, -U NUM, --unified[=NUM]   output NUM (default 3) lines of unified context\n");
	printf("  -t, --expand-tabs             expand tabs to spaces in output\n");
	printf("  -r, --recursive                 recursively compare any subdirectories found\n");
	printf("  -i, --ignore-case               ignore case differences in file contents\n");
	printf("  -b, --ignore-space-change       ignore changes in the amount of white space\n");
	printf("  -w, --ignore-all-space          ignore all white space\n");
	//printf("      %\<  lines from FILE1\n");
	//printf("      %\>  lines from FILE2\n");
	printf("      --help               display this help and exit\n");
	printf("FILES are 'FILE1 FILE2'\n");
}					
