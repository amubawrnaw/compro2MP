#include <stdio.h>

int main()
{
	int i,j,x,y;
	char moov,box[3][3]={{'.','.','.'},
						 {'.','.','.'},
						 {'.','.','.'}};
	x=1;
	y=1;
	box[x][y]='X';
	do{
		//start of loopy thingy
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		for(i=0;i<3;i++)
		{
			for(j=0;j<3;j++)
			{
				printf("%c",box[i][j]);
			}
			printf("\n");
		}
		//end of loopy thingy
		do{
		scanf(" %c",&moov);
		}while(moov!='w'&&moov!='a'&&moov!='s'&&moov!='d');
		switch(moov)
		{
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
			case 's':if (x!=2)
					{
						box[x][y]='.';
						x++;
					}						
						break;
			case 'd':if (y!=2)
					{
						box[x][y]='.';
						y++;
					}
						break;
		}
		box[x][y]='X';
		
	}while(1);
}
