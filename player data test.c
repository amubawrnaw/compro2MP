#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void distSkills(int data[],int x)
{
	if (data[0]!=0)
	{
		data[0]--;
		data[x+2]++;
	}
}
int checkLimit(char input[], int x)
{
	if(input[x]==' ')
		return 1;
	else return 0;
}
void playerData(char dataName[][30],int data[])
{
	int x=0,tempX;
	char ptr[5]={'>',' ',' ',' ',' '},input;
	do{
		printData(dataName,data,ptr,x);
		do{
			input=getch();
		}while(input!='w'&&input!='s'&&input!='u'&&input!='E');
		tempX=x;
		switch (input)
		{
			case 'w':if (checkLimit(ptr,tempX-1))
					{
						ptr[x]=' ';	
						x--;	
					}break;
			case 's':if (checkLimit(ptr,tempX+1)) 
					{
						ptr[x]=' ';
						x++;
					}break;
			case 'u':distSkills(data,x);
		}
		ptr[x]='>';
		tempX=0;
	}while(input!='E');
}

void printData(char dataName[][30],int data[],char ptr[],int x)
{
	int i;
	system("cls");
	printf(" %s\n",dataName[0]);
	for (i=1;i<3;i++)
		printf(" %s: %d\n",dataName[i],data[i-1]);
	printf(" --------\n");
	for (i=3;i<8;i++)
		printf("%c%s: %d\n",ptr[i-3],dataName[i],data[i-1]);
}

int main()
{
	int data[8]={7,0,1,0,0,0,0};
	char dataName[8][30]={"","SP   ","exp  ","Level","dmg  ","def  ","hp   ","con  "},temp[20];
	scanf("%[^\n]s",dataName[0]);
	system("cls");
	strcpy(temp,dataName[0]);
	strcpy(dataName[0],"");
	strcat(dataName[0],"Name: ");
	strcat(dataName[0],temp);
	playerData(dataName,data);
}
