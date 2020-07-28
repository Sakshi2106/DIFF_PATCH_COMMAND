#include<stdio.h>
 struct lcslines{
			int fil1[100];
			int fil2[100];
			};

char **readline(FILE *file);
char **lcs(char **a, char **b, int len1, int len2, char**argv);
int lenlcs(char **a, char **b, int len1, int len2, char**argv);
int max(int a, int b); 
int length(FILE *fp);
void output(char **fil1, char **fil2, int x1, int x2, char**argv, char *file1, char *file2);
struct lcslines lcsline(char **a, char **b, int len1, int len2, char**argv);
void change(char **p, char **q, int x, int z, struct lcslines y, int r);
void addstart(char **p, char **q, int x, int z, struct lcslines y, int r);
void addend(char **p, char **q, int x, int z, int l2);
void delete(char **p, char **q, int x, int z, struct lcslines y, int r);
void deletend(char **p, char **q, int x, int z, int l1);
void changend(char **p, char **q, int x, int z, int l1, int l2);
int wStrcmp(char *str1, char *str2);
int bStrcmp(char *str1, char *str2);
int iStrcmp(char *str1, char *str2);
void help(void);
