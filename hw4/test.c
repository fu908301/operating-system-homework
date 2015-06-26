#include <stdio.h>
#include "mm.h"
int main()
{
	int len, i; 
	char *str, ch;
	
	printf("mymalloc test :\n");
	str = (char *)mymalloc(sizeof(char));
	printf("enter a character for mymalloc test : ");
	scanf("%c%c", &str[0], &ch);
	printf("*(str+0) is : %c\n\n", str[0]);

	printf("mycalloc test :\n");
	printf("enter a number for mycalloc test : ");
	scanf("%d%c", &len, &ch);
	str = (char *)mycalloc(len+1, sizeof(char));
	printf("enter a string : ");
	for(i = 0; i < len+1 && str[i-1] != '\n'; ++i){
		scanf("%c", &str[i]);
	}
	str[i-1] = '\0';
	printf("string : %s\n", str);
	printf("len of string is %lu.\n\n", strlen(str));

	printf("myralloc test :\n");
	printf("enter a number for myralloc test : ");
	scanf("%d%c", &len, &ch);
	str = (char *)myrealloc(str, (len+1) * sizeof(char));
	printf("enter a string : ");
	for(i = 0; i < len+1 && str[i-1] != '\n'; ++i){
		scanf("%c", &str[i]);
	}
	str[i-1] = '\0';
	printf("string : %s\n", str);
	printf("len of string is %lu.\n\n", strlen(str));

	printf("myfree test :\n");
	myfree(str);

	return 0;
}
