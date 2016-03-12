#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int isWithinRange(int x)
{
	if (x>=0&&x<27)
		return 1;
	else return 0;
}
void printSelection(char alphabet[],char ptr[],char currentName[])
{
	int i;
	printf(" Name : %s",currentName);
	for (i=0;i<26;i++)
	{
		if (i%7==0)
			printf("\n\n");
		printf("%c%c ",ptr[i],alphabet[i]);	
	}
	printf("%cSpace",ptr[i]);
	printf("\n\n G - Accept name\n Backspace - erase letter \n \\ - turn capslock on/off");
}
void nameGen()
{
	int i,j,tempX,PtrX=0,letter=0,min=65,max=90;
	char alphabet[27], ptr[27]={'>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		currentName[101]="",input;
	alphabet[26]=' ';
	do{
		for (i=min,j=0;i<=max;i++,j++)
			alphabet[j]=i;	
		system("cls");
		printSelection(alphabet,ptr,currentName);
		do{
			input=getch();		
		}while(input!='w'&&input!='a'&&input!='s'&&input!='d'&&input!='\r'&&input!='\b'&&input!='g'&&input!='\\');
		tempX=PtrX;
		switch (input)
		{
			case 'w':
					if (isWithinRange(tempX-7))
					{
						ptr[PtrX]=' ';	
						PtrX-=7;
					}break;
			case 'a':
					if (isWithinRange(tempX-1))
					{
						ptr[PtrX]=' ';	
						PtrX--;
					}break;
			case 's':
					if (isWithinRange(tempX+7))
					{
						ptr[PtrX]=' ';	
						PtrX+=7;
					}break;
			case 'd':
					if (isWithinRange(tempX+1))
					{
						ptr[PtrX]=' ';	
						PtrX++;
					}break;
			case '\r':
					currentName[letter]=alphabet[PtrX];
					letter++;
					break;
			case '\b':currentName[letter-1]=' ';
					letter--;break;
			case '\\':if (min==65&&max==90)
					{
						min=97;
						max=122;
					}
					else 
					{
						min=65;
						max=90;
					}break;
		}
		ptr[PtrX]='>';	
	}while(input!='g');

}
int main()
{
	nameGen();
}
