
#include "ntlc.h"
#include <stdio.h>


int main(void)
{
	int i=0;
	printf("test\nnumber1:");

	Init();
	setDeg(12,0);
	setQ(7,0);
	long *test1, *test2,*test3,*test4,*test5;
	long *test6;
	initRandom();
	test1=randElement(0);
	for(i=0;i<10;i++)
	{
		test6=randNormElement(0);
		printEle(test6,0);
printf("\n");
	}
	test2=randNormElement(0);
	printEle(test1,0);
	printf("\nnumber2:");
	printEle(test2,0);
	test3=add(test1,test2,0);
	printf("\nnumber3: ");
	printEle(test3,0);
	test4=mult(test1,test2,0);
	printf("\nnumber4: ");
		printEle(test4,0);
	test5=sub(test1,test2,0);
	printf("\nnumber5: ");
		printEle(test5,0);
		randTest();
		printf("\n size: %d",sizeof(long));
return 0;
}
