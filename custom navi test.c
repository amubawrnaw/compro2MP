#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define player 'P'
int main()
{
	int start,i,j,x,y,a,b;
	printf("Input size of room: ");
	scanf("%d",&start);
	char moov,box[start][start];
	
	for(a=0;a<start;a++)
		{
			for(b=0;b<start;b++)
			{
				box[a][b]='.';
			}
			printf("\n");
		}
	x=start/2;
	y=start/2;
	box[x][y]=player;
	do{
		//start of loopy thingy
		system("cls");
		for(i=0;i<start;i++)
		{
			for(j=0;j<start;j++)
			{
				printf("%c",box[i][j]);
			}
			printf("\n");
		}
		printf("W-A-S-D to move: ");
		printf("%d, %d", x, y);
		//end of loopy thingy
		do{
		//scanf(" %c",&moov);
		moov=getch();
		}while(moov!='W'&&moov!='A'&&moov!='S'&&moov!='D'&&moov!='w'&&moov!='a'&&moov!='s'&&moov!='d');
		switch(moov)
		{
			case 'W':if (x!=0)
					{
						box[x][y]='.';
						x--;
					}
						break;
			case 'A':if (y!=0)
					{
						box[x][y]='.';
						y--;
					}
						break;
			case 'S':if (x!=start-1)
					{
						box[x][y]='.';
						x++;
					}						
						break;
			case 'D':if (y!=start-1)
					{
						box[x][y]='.';
						y++;
					}
						break;
			case 'w':if (x!=0)
					{
						box[x][y]='.';
						x--;
					}
						break;
			case 'a':if (y!=0)
					{
						box[x][y]='.';
						y--;
					}
						break;
			case 's':if (x!=start-1)
					{
						box[x][y]='.';
						x++;
					}						
						break;
			case 'd':if (y!=start-1)
					{
						box[x][y]='.';
						y++;
					}
						break;
		}
		box[x][y]=player;
		
	}while(moov!='E');
}	
