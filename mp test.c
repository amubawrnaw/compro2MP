#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define player 'P'
#define Rooms 100
#define northX 0
#define eastX 3
#define westX 3
#define southX 6
#define northY 3
#define eastY 6
#define westY 0
#define southY 3
/*
int choose()
{
	int *x,y;
	x=malloc(sizeof(int));
	y=x;
	if (y%10>5)
		return 1;
	else return 0;
}
*/
/*
int getRandomNum ()//no use as of now :)
{
	int *x;
	x=malloc(sizeof(int));
	return x;
}*/
int checkForWall(char box[][7],int x, int y)
{
	if (box[x][y]!=' ')
		return 0;
    else return 1;
}
int checkForEnem(char box[][7], int x, int y)
{
	if (box[x][y]=='E')
	{
		
	}
}
int checkForNextRoom(char box[][7], int x, int y,int a, int b)
{
	if(x==-1||x==7||y==-1||y==7)
		return 1;
	else return 0;
}
void printBoard(char box[][7], int start,int Px, int Py, int Rx, int Ry,int roomAlgo[][3])
{
	int i,j;
	system("cls");

	printf("W-A-S-D to move:\n\n player X: %d\n player Y: %d\n room X: %d\n room Y: %d\n Room Code: %d\n\n\t",Px,Py,Rx,Ry,roomAlgo[Rx][Ry]);
	for(i=0;i<start;i++)
		{
			for(j=0;j<start;j++)
			{
				printf("%c",box[i][j]);
			}
			printf("\n\t");
		}
	} 
void  generateRoom (char box[][7],int roomAlgo[][3],int start,int a,int b)
{
	int x,y,roomGate=roomAlgo[a][b];
	for(x=0;x<start;x++)
		{
			for(y=0;y<start;y++)
			{
				if ((x==0||x==start-1||y==0||y==start-1))
					box[x][y]='%';
				else box[x][y]=' ';
			}
		}	
	if (roomGate/1000)//North gate
		box[0][3]=' ';
	if (roomGate%1000/100)//East gate
		box[3][6]=' ';
	if (roomGate%1000%100/10)//West gate
		box[3][0]=' ';
	if (roomGate%10)//South gate
		box[6][3]=' ';
}
void playerData()
{
	
}
int main()
{
	int start=7,i,j,Px,Py,tempX,tempY,roomAlgo[3][3]={{0,0001},{100,1111,10},{1000}},Rx=1,Ry=1;
	char move,box[start][start];
	Px=start/2;
	Py=start/2;
	do{
		generateRoom(box,roomAlgo,start,Rx,Ry);
		box[Px][Py]=player;
		printBoard(box,start,Px,Py,Rx,Ry,roomAlgo);
		do{
		move=getch();
		}while(move!='W'&&move!='A'&&move!='S'&&move!='D'&&move!='w'&&move!='a'&&move!='s'&&move!='d'&&move!='E');
		tempX=Px;
		tempY=Py;
		switch(move)
		{
			case 'w'://north/up
					if (checkForNextRoom(box,tempX-1,Py,Rx,Ry))
					{
						Rx--;
						Px=6;
					}
					else if (checkForWall(box,tempX-1,Py))
					{
						box[Px][Py]=' ';
						Px--;
					}break;
			case 'd'://east/right
					if (checkForNextRoom(box,Px,tempY+1,Rx,Ry))
					{
						Ry++;
						Py=0;
					}
					else if (checkForWall(box,Px,tempY+1))
					{
						box[Px][Py]=' ';
						Py++;
					}break;		
			case 'a'://west/left
					if (checkForNextRoom(box,Px,tempY-1,Rx,Ry))
					{
						Ry--;
						Py=6;
					}
					else if (checkForWall(box,Px,tempY-1))
					{
						box[Px][Py]=' ';
						Py--;
					}break;
			case 's'://south/down
					if (checkForNextRoom(box,tempX+1,Py,Rx,Ry))
					{
						Rx++;
						Px=0;
					}
					else if (checkForWall(box,tempX+1,Py))
					{
						box[Px][Py]=' ';
						Px++;
					}break;
		}
		box[Px][Py]=player;
		tempX=0;
		tempY=0;	
	}while(move!='E');
	system("cls");
	printf("Test End. ");
}	
