#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define playerSymbol 'P'
#define Rooms 100

struct weaponTag{
	char weapName [101];
	int weapDmg;
	int weapHP;
	int weapVal;
};
struct armorTag{
	char armorName[101];
	int armorDef;
	int armorVal;
	int armorHp;
};
struct player{
	char pName[101];
	int pDmg;
	int pDef;
	int pLvl;
	int pExp;
	int pCon;
	int pHP;
	struct weaponTag pWeapon;
	struct armorTag pArmor;
};
struct enemyTag{
	char enemName[101];
	int enemDmg;
	int enemHP;
};
/****************************************************************************************************************************/
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
void printData(char dataName[][30],int data[],char ptr[],char ptr2[],int x)
{
	int i;
	system("cls");
	printf(" %s\n",dataName[0]);
	for (i=1;i<3;i++)
		printf(" %s: %d\n",dataName[i],data[i-1]);
	printf(" --------\n");
	for (i=3;i<8;i++)
		printf("%c%s: %d%c\n",ptr[i-3],dataName[i],data[i-1],ptr2[i-3  ]);
	printf("\n\n W-S  to select, ENTER to upgrade");
}
void playerData(char dataName[][30],int data[])
{ 
	int x=0,tempX;
	char ptr[5]={'>',' ',' ',' ',' '},ptr2[5]={'<',' ',' ',' ',' '},input;
	do{
		printData(dataName,data,ptr,ptr2,x);
		do{
			input=getch();
		}while(input!='w'&&input!='s'&&input!='\r'&&input!='E');
		tempX=x;
		switch (input)
		{
			case 'w':if (checkLimit(ptr,tempX-1))
					{
						ptr[x]=' ';
						ptr2[x]=' ';	
						x--;	
					}break;
			case 's':if (checkLimit(ptr,tempX+1)) 
					{
						ptr[x]=' ';
						ptr2[x]=' ';
						x++;
					}break;
			case '\r':distSkills(data,x);
		}
		ptr[x]='>';
		ptr2[x]='<';
		tempX=0;
	}while(data[0]!=0);
	ptr[x]=' ';
	ptr2[x]=' ';
	printData(dataName,data,ptr,ptr2,x);
	printf("\n Press any key to start...");
	getch();
}
void transSkills(int data[],struct player *pData)
{
	pData->pExp=data[1];
	pData->pLvl=data[2];
	pData->pDmg=data[3];
	pData->pDef=data[4];
	pData->pHP=data[5];
	pData->pCon=data[6];
}
void playerStats(char dataName[][30],struct player pData)
{
	system("cls");
	printf(" %s\n",pData.pName);
	printf(" %s: %d\n",dataName[3],pData.pLvl);
	printf(" %s: %d\n",dataName[2],pData.pExp);
	printf(" -----------\n");
	printf(" %s: %d\n",dataName[4],pData.pDmg);
	printf(" %s: %d\n",dataName[5],pData.pDef);
	printf(" %s: %d\n",dataName[6],pData.pHP);
	printf(" %s: %d\n",dataName[7],pData.pCon);
	printf(" -----------\n");
	printf(" Credits");
	printf(" Current Weapon: %s\n",pData.pWeapon.weapName);
	printf(" Current Armor: %s",pData.pArmor.armorName);
	getch();
}
void weaponStats()
{
}
void dealDamage()
{
	
	
}
/****************************************************************************************************************************/
int checkForWall(char box[][7],int x, int y)
{
	if (box[x][y]!=' '&&box[x][y]!='M'&&box[x][y]!='T'&&box[x][y]!='A'&&box[x][y]!='W')
			return 0;
    else return 1;
}
int checkForEnem(char box[][7], int x, int y)
{
	if (box[x][y]=='E')
		return 1;
	else return 0;
}
int checkForArmor(char box[][7], int x, int y)
{
	if (box[x][y]=='A')
		return 1;
	else return 0;
}
int checkForWeap(char box[][7], int x, int y)
{
	if (box[x][y]=='W')
		return 1;
	else return 0;
}
int checkForNextRoom(char box[][7], int x, int y,int a, int b)
{
	if(x==-1||x==7||y==-1||y==7)
		return 1;
	else return 0;
}
/******************************************************************************************************************************/
void printBoard(char box[][7], int start,int Px, int Py, int Rx, int Ry,int roomAlgo[][3])
{
	int i,j;
	system("cls");
	printf(" W-A-S-D to move:\n P to Check Self\n\n player X: %d\n player Y: %d\n room X: %d\n room Y: %d\n Room Code: %d\n\n\t",Px,Py,Rx,Ry,roomAlgo[Rx][Ry]);
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
	if (roomGate%1000000000/100000000)//Surface Link 
		box[3][3]='S';
	if (roomGate%100000000/10000000)//Treasure
		box[3][3]='T';
	if (roomGate%10000000/1000000)//Weapon	
		box[3][3]='W';
	if (roomGate%1000000/100000)//Armor
		box[3][3]='A';		
	if (roomGate%100000/10000)//Monster
		box[3][3]='M';
	if (roomGate%10000/1000)//North gate
		box[0][3]=' ';
	if (roomGate%1000/100)//East gate
		box[3][6]=' ';
	if (roomGate%100/10)//West gate
		box[3][0]=' ';
	if (roomGate%10)//South gate
		box[6][3]=' ';
}
/******************************************************************************************************************************/
void calcStats(struct player *pData)
{
	pData->pDmg=(pData->pLvl*.80)+pData->pDmg+pData->pWeapon.weapDmg;
	pData->pDef=(pData->pLvl*.20)+pData->pDef+pData->pArmor.armorDef;
	pData->pHP=pData->pLvl+pData->pHP+pData->pArmor.armorHp+pData->pWeapon.weapHP;
	pData->pCon=(pData->pHP*.20)+pData->pCon;
}
void enemData(struct enemyTag *currentEnem)
{
	
}
int getRoundedVal(float x)
{
	int y=x;
	float temp;
	temp=x;
	temp=temp-y;
	printf("%f\n",temp);
	if (temp>=.50)
		return y+1;
	else return y;
}
void defaultGear(struct player *pData)
{
	/************************/
	strcpy(pData->pArmor.armorName,"Standard Issue Salvager Uniform");	
	pData->pArmor.armorVal=3;
	pData->pArmor.armorHp=2;
	pData->pArmor.armorDef=1;
	/************************/
	strcpy(pData->pWeapon.weapName,"Standard Issue Force Blaster");	
	pData->pWeapon.weapDmg=1;
	pData->pWeapon.weapHP=1;
	pData->pWeapon.weapVal=2;
	/************************/
}
int main()
{
	int start=7//room size
		,i//loop
		,j//loop
		,Px=start/2//player start
		,Py=start/2//player start
		,tempX //contains the destination of X
		,tempY //contains the destination of Y
		,roomAlgo[3][3]={{0,1000010001},{1010000100,1000001111,1001000010},{0,1000101000}}//room code for rooms
		,Rx=1//x location of the center room
		,Ry=1//y location of the center room
		,data[7]={7,0,1,0,0,0,0}//starting skill distribution
		,prevLvl=0;
	
	char move//user input for player interaction
		,box[start][start]//room array
		,playerName[101]//player's name
		,dataName[8][30]={"","SP   ","exp  ","Level","dmg  ","def  ","hp   ","con  "}//starting skill names
		,temp[51]//temporary player name holder
		,monsterName[10][41]={"COMPRO2","DISCTRU","GOBLIN","ORC","DLSU","SOCTEC1","CCSTRIG","DEADLINE","MP","SLEEP" }
		,armorName[10][101]={"T-Shirt","Polo-Shirt","Polo","Shorts","Yes","Jacket","Sweater","Steel Armor","Dress","Suit"}
		,weaponName[10][101]={"Sword","Shield","Water Bottle","Pencil","Balloon","All nighter","Booster C","Chair","Stick","Spoon"};
		

	struct player pData;
	struct enemyTag currentEnem;
	printf("What is your name?: ");
	scanf("%[^\n]s",playerName);
	
	strcat(dataName[0],"Name : ");
	strcat(dataName[0],playerName);
	strcpy(pData.pName,dataName[0]);
	
	playerData(dataName,data);
	transSkills(data,&pData);
	defaultGear(&pData);
	do{
		if (prevLvl!=pData.pLvl)
		{
			calcStats(&pData);	
			prevLvl=pData.pLvl;		
		}
		generateRoom(box,roomAlgo,start,Rx,Ry);
		box[Px][Py]=playerSymbol;
		printBoard(box,start,Px,Py,Rx,Ry,roomAlgo);
		do{
			move=getch();
		}while(move!='W'&&move!='A'&&move!='S'&&move!='D'&&move!='w'&&move!='a'&&move!='s'&&move!='d'&&move!='E'&&move!='d'&&move!='p');
		tempX=Px;
		tempY=Py;
		if (move=='p')
			playerStats(dataName,pData);
		else switch(move)
		{
			case 'w'://north/up
					if (checkForEnem(box,tempX-1,Py))
					{
						enemData(&currentEnem);
					}
					else if (checkForNextRoom(box,tempX-1,Py,Rx,Ry))
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
		box[Px][Py]=playerSymbol;
		tempX=0;
		tempY=0;	
	}while(move!='E');
	system("cls");
	printf("Test End. ");
}	
