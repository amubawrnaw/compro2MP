#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#define playerSymbol 'P'
#define roomSize 11
struct treasureTag{
	int treasVal;
};
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
struct playerTag{
	char pName[101];
	int pDmg;
	int pDef;
	int pLvl;
	int pExp;
	int pCon;
	int pHP;
	int pMaxHP;
	int pMoney;
	struct weaponTag pWeapon;
	struct armorTag pArmor;
};
struct enemyTag{
	char enemName[101];
	int enemDmg;
	int enemHP;
};
typedef struct enemyTag enemy;
typedef struct armorTag armor;
typedef struct weaponTag weapon;
typedef struct playerTag player;
typedef struct treasureTag treasure;
/****************************************************************************************************************************/
int getRoundedVal(float x)
{
	int y=x;
	float temp;
	temp=x;
	temp=temp-y;
	if (temp>0)
		return y+1;
	else return y;
}
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
void transSkills(int data[],player *pData)
{
	pData->pExp=data[1];
	pData->pLvl=data[2];
	pData->pDmg=data[3];
	pData->pDef=data[4];
	pData->pHP=data[5];
	pData->pCon=data[6];
	pData->pMoney=0;
	pData->pMaxHP=data[5];
}
void playerStats(char dataName[][30],player pData)
{
	system("cls");
	printf(" %s\n",pData.pName);
	printf(" %s: %d\n",dataName[3],pData.pLvl);
	printf(" %s: %d|%d\n",dataName[2],pData.pExp,getRoundedVal(pData.pLvl*0.3));
	printf(" %s: %d\n",dataName[8],pData.pMoney);	
	printf(" -----------\n");
	printf(" %s: %d\n",dataName[4],pData.pDmg);
	printf(" %s: %d\n",dataName[5],pData.pDef);
	printf(" %s: %d|%d\n",dataName[6],pData.pHP,pData.pMaxHP);
	printf(" %s: %d\n",dataName[7],pData.pCon);
	printf(" -----------\n");

	printf(" Current Weapon: %s\n",pData.pWeapon.weapName);
	printf(" Current Armor: %s",pData.pArmor.armorName);
	getch();
}
int getRange(float lowerLimit, float upperLimit)
{
	float rawRange;
	int x,baseRange,baseVal;
	rawRange=upperLimit-lowerLimit;
	baseVal=getRoundedVal(lowerLimit);
	baseRange=returnRand(getRoundedVal(rawRange));
	x=baseVal+baseRange;
	return x;
}
void treasureData(treasure *currentTreas,player pData)
{
	currentTreas->treasVal=(getRange(pData.pLvl,pData.pLvl+5))*10;
}
void weaponData(weapon *currentWeap, player pData)
{
	int max=pData.pLvl-3;
	char weaponName[10][101]={"Sword","Shield","Water Bottle","Pencil","Balloon","All nighter","Booster C","Chair","Stick","Spoon"};
	strcpy(currentWeap->weapName,weaponName[returnRand(10)]);//weapon Name
	if (max<0)
		max=0;
	currentWeap->weapVal=(getRange(max,pData.pLvl))*10;
	currentWeap->weapDmg=getRange(pData.pLvl*0.1,pData.pLvl*0.5);
	currentWeap->weapHP=getRange(1,5);	
}
void armorData(armor *currentArmor, player pData)
{	
	int max=pData.pLvl-3;
	char armorName[10][101]={"T-Shirt","Polo-Shirt","Polo","Shorts","Yes","Jacket","Sweater","Steel Armor","Dress","Suit"};
	strcpy(currentArmor->armorName,armorName[returnRand(10)]);//Armor name
	if (max<0)
		max=0;	
	currentArmor->armorVal=(getRange(max,pData.pLvl+1))*10;
	currentArmor->armorDef=getRange(pData.pLvl*0.1,pData.pLvl*0.7);
	currentArmor->armorHp=getRange(1,5);
}
void enemData(enemy *currentEnem, player pData)
{
	int max=pData.pLvl-3,maxHP=pData.pLvl-5;
	char monsterName[10][41]={"COMPRO2","DISCTRU","GOBLIN","ORC","DLSU","SOCTEC1","CCSTRIG","DEADLINE","MP","SLEEP" };
	strcpy(currentEnem->enemName,monsterName[returnRand(10)]);//Enem Name
	if (max<0)
		max=0;
	if (maxHP<0)
		maxHP=0;
	currentEnem->enemDmg=(getRange(max,pData.pLvl+1))*0.3;
	currentEnem->enemHP=getRange(maxHP,pData.pLvl);
}
void dealDamage(enemy *currentEnem, player *pData)
{
	int max=currentEnem->enemDmg-pData->pDef;
	currentEnem->enemHP-=pData->pDmg;
	if (max<0)
		max=1;
	pData->pHP-=max;
}
/****************************************************************************************************************************/
int checkForWall(char box[][roomSize],int x, int y)
{
	if (box[x][y]!=' '&&box[x][y]!='M'&&box[x][y]!='T'&&box[x][y]!='A'&&box[x][y]!='W')
			return 0;
    else return 1;
}
int checkForEnem(char box[][roomSize], int x, int y)
{
	if (box[x][y]=='M')
		return 1;
	else return 0;
}
int checkForArmor(char box[][roomSize], int x, int y)
{
	if (box[x][y]=='A')
		return 1;
	else return 0;
}
int checkForWeap(char box[][roomSize], int x, int y)
{
	if (box[x][y]=='W')
		return 1;
	else return 0;
}
int checkForNextRoom(char box[][roomSize], int x, int y)
{
	if(x==-1||x==roomSize||y==-1||y==roomSize)
		return 1;
	else return 0;
}
int checkForTreasure(char box[][roomSize], int x, int y)
{
	if (box[x][y]=='T')
		return 1;
	else return 0;
}
/******************************************************************************************************************************/
void printBoard(char box[][roomSize],int Px, int Py, int Rx, int Ry,int roomAlgo[][3])
{
	int i,j;
	system("cls");
	printf(" W-A-S-D to move:\n P to Check Self\n\n player X: %d\n player Y: %d\n room X: %d\n room Y: %d\n Room Code: %d\n\n\t",Px,Py,Rx,Ry,roomAlgo[Rx][Ry]);
	for(i=0;i<roomSize;i++)
		{
			for(j=0;j<roomSize;j++)
			{
				printf("%c",box[i][j]);
			}
			printf("\n\t");
		}
	} 
void  generateRoom (char box[][roomSize],int roomAlgo[][3],int a,int b,player pData,weapon *currentWeap,armor *currentArmor,enemy *currentEnem,treasure *currentTreas)
{
	int x,y,roomGate=roomAlgo[a][b];
	for(x=0;x<roomSize;x++)
		{
			for(y=0;y<roomSize;y++)
			{
				if ((x==0||x==roomSize-1||y==0||y==roomSize-1))
					box[x][y]='%';
				else box[x][y]=' ';
			}
		}	
	if (roomGate%1000000000/100000000)//Surface Link 
	{	
		box[roomSize/2][roomSize/2]='S';
	}
	if (roomGate%100000000/10000000)//Treasure
	{
		box[roomSize/2][roomSize/2]='T';	
		if (roomGate%100000000/10000000==1)
		{
			roomGate+=10000000;		
			treasureData(currentTreas,pData);
		}
	}
	if (roomGate%10000000/1000000)//Weapon	
	{
		box[roomSize/2][roomSize/2]='W';
		if (roomGate%10000000/1000000==1)
		{
			weaponData(currentWeap,pData);
			roomGate+=1000000;
		}
	}
	if (roomGate%1000000/100000)//Armor
	{
		box[roomSize/2][roomSize/2]='A';	
		if (roomGate%1000000/100000==1)
		{
			armorData(currentArmor,pData);	
			roomGate+=100000;
		}
	}
	if (roomGate%100000/10000)//Monster
	{
		box[roomSize/2][roomSize/2]='M';
		if (roomGate%100000/10000==1)
		{
			enemData(currentEnem,pData);
			roomGate+=10000;
		}
	}
	if (roomGate%10000/1000)//North gate
		box[0][roomSize/2]=' ';
	if (roomGate%1000/100)//East gate
		box[roomSize/2][roomSize-1]=' ';
	if (roomGate%100/10)//West gate
		box[roomSize/2][0]=' ';
	if (roomGate%10)//South gate
		box[roomSize-1][roomSize/2]=' ';
	roomAlgo[a][b]=roomGate;
}
/******************************************************************************************************************************/
void equipWeap(player *pData,weapon currentWeap)
{
	pData->pDmg-=pData->pWeapon.weapDmg;
	pData->pHP-=pData->pWeapon.weapHP;
	pData->pDmg+= currentWeap.weapDmg;
	pData->pHP+= currentWeap.weapHP;
}
void equipArmor(player *pData,armor currentArmor)
{
	pData->pDef-=pData->pArmor.armorDef;
	pData->pHP-=pData->pArmor.armorHp;
	pData->pDef+=currentArmor.armorDef;
	pData->pHP+=currentArmor.armorHp;
}
void calcStats(player *pData)
{
	pData->pDmg=(pData->pLvl*.80)+pData->pDmg+pData->pWeapon.weapDmg;
	pData->pDef=(pData->pLvl*.20)+pData->pDef+pData->pArmor.armorDef;
	pData->pHP=pData->pLvl+pData->pHP+pData->pArmor.armorHp+pData->pWeapon.weapHP;
	pData->pCon=(pData->pHP*.20)+pData->pCon;
	pData->pMaxHP=pData->pHP;
}
void defaultGear(player *pData)
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
int returnRand(int choices)
{
    int randNum;
    return randNum=rand()%choices;
}
void pClear(player *pData)
{
	pData->pCon=0;
	pData->pDef=0;
	pData->pDmg=0;
	pData->pHP=0;
}
////////////////////////////////////////////////////////////////////////////////////////
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
void nameGen(char currentName[])
{
	int i,j,tempX,PtrX=0,letter=0,min=65,max=90;
	char alphabet[27], ptr[27]={'>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},input;
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
	int	i//loop
		,j//loop
		,Px=roomSize/2//player start
		,Py=roomSize/2//player start
		,tempX //contains the destination of X
		,tempY //contains the destination of Y
		,roomAlgo[3][3]={{0,1000010001},{1010000100,1000001111,1001000010},{0,1000101000}}//room code for rooms
		,Rx=1//x location of the center room
		,Ry=1//y location of the center room
		,data[7]={7,0,1,0,0,0,0}//starting skill distribution
        ,randNum//contains the random number
        ,killedEnem=0//counts the number of enemy kills to level up
        ,totalEnem=0//counts how many enemies you've killed so far
		,playerHP;//player HP 
	char move//user input for player interaction
		,box[roomSize][roomSize]//room array
		,playerName[101]=""//player's name
		,dataName[9][30]={"","SP   ","exp  ","Level","dmg  ","def  ","hp   ","con  ","Money"}//starting skill names
		,temp[51];//temporary player name holder
	
	srand(time(NULL));
	struct playerTag pData;
	struct enemyTag currentEnem;
	struct weaponTag currentWeap;
	struct armorTag currentArmor;
	struct treasureTag currentTreas;
	nameGen(playerName);
	
	strcat(dataName[0],"Name : ");
	strcat(dataName[0],playerName);
	strcpy(pData.pName,dataName[0]);
	
	playerData(dataName,data);
	transSkills(data,&pData);
	defaultGear(&pData);
	calcStats(&pData);
	playerHP=pData.pHP;
	do{/////////////////////////////////////////GAME START/////////////////////////////////////////////////////////
		if (pData.pExp==getRoundedVal(pData.pLvl*0.3))
		{
			pData.pLvl++;
			pData.pExp=0;
		}
	
		pClear(&pData);
		calcStats(&pData);
		pData.pHP=playerHP;	

		if (Rx==1&&Ry==1)
		{
			roomAlgo[0][1]=1000010001;
			roomAlgo[1][0]=1010000100;
			roomAlgo[1][2]=1001000010;
			roomAlgo[2][1]=1000101000;
		}
		generateRoom(box,roomAlgo,Rx,Ry,pData,&currentWeap,&currentArmor,&currentEnem,&currentTreas);
		box[Px][Py]=playerSymbol;
		printBoard(box,Px,Py,Rx,Ry,roomAlgo);
		do{
			move=getch();
		}while(move!='W'&&move!='A'&&move!='S'&&move!='D'&&move!='w'&&move!='a'&&move!='s'&&move!='d'&&move!='E'&&move!='d'&&move!='p');
		tempX=Px;
		tempY=Py;
		if (move=='p')
			playerStats(dataName,pData);
		else switch(move)
		{
			case 'w'://north/up//////////////////////////////////////////////////////////////////////////////////
					if (checkForEnem(box,tempX-1,Py))
					{
						dealDamage(&currentEnem,&pData);
						playerHP=pData.pHP;
						if(currentEnem.enemHP<=0&&pData.pHP>0)
						{
							Px--;
							playerHP+=pData.pCon;
							if (playerHP>pData.pMaxHP)
								playerHP=pData.pHP=pData.pMaxHP;
							roomAlgo[Rx][Ry]-=20000;
							pData.pExp++;
							totalEnem++;
						}
					}
					else if(checkForArmor(box,tempX-1,Py))
					{
						roomAlgo[Rx][Ry]-=200000;
						equipArmor(&pData,currentArmor);
						pData.pArmor=currentArmor;
						Px--;
					}
					else if(checkForWeap(box,tempX-1,Py))
					{
						roomAlgo[Rx][Ry]-=2000000;
						equipWeap(&pData,currentWeap);
						pData.pWeapon=currentWeap;
						Px--;
					}
					else if(checkForTreasure(box,tempX-1,Py))
					{
						roomAlgo[Rx][Ry]-=20000000;
						pData.pMoney+=currentTreas.treasVal;
						Px--;
						pData.pExp++;
						
					}
					else if (checkForNextRoom(box,tempX-1,Py))
					{
						Rx--;
						Px=roomSize-1;
					}
					else if (checkForWall(box,tempX-1,Py))
					{
						box[Px][Py]=' ';
						Px--;
					}break;
			case 'd'://east/right//////////////////////////////////////////////////////////////////////////////////
					if (checkForEnem(box,Px,tempY+1))
					{
						dealDamage(&currentEnem,&pData);
						if(currentEnem.enemHP<=0&&pData.pHP>0)
						{
							Py++;
							pData.pHP+=pData.pCon;
							if (playerHP>pData.pMaxHP)
								playerHP=pData.pHP=pData.pMaxHP;
							roomAlgo[Rx][Ry]-=20000;
							pData.pExp++;
							totalEnem++;
						}
					}
					else if(checkForArmor(box,Px,tempY+1))
					{
						roomAlgo[Rx][Ry]-=200000;
						equipArmor(&pData,currentArmor);						
						pData.pArmor=currentArmor;
						Py++;
					}
					else if(checkForWeap(box,Px,tempY+1))
					{
						roomAlgo[Rx][Ry]-=2000000;
						equipWeap(&pData,currentWeap);
						pData.pWeapon=currentWeap;
						Py++;
					}
					else if(checkForTreasure(box,Px,tempY+1))
					{
						roomAlgo[Rx][Ry]-=20000000;
						pData.pMoney+=currentTreas.treasVal;
						pData.pExp++;
						Py++;
					}
					else if (checkForNextRoom(box,Px,tempY+1))
					{
						Ry++;
						Py=0;
					}
					else if (checkForWall(box,Px,tempY+1))
					{
						box[Px][Py]=' ';
						Py++;
					}break;		
			case 'a'://west/left//////////////////////////////////////////////////////////////////////////////////
					if (checkForEnem(box,Px,tempY-1))
					{
						dealDamage(&currentEnem,&pData);
						if(currentEnem.enemHP<=0&&pData.pHP>0)
						{
							Py--;
							pData.pHP+=pData.pCon;
							if (playerHP>pData.pMaxHP)
								playerHP=pData.pHP=pData.pMaxHP;
							roomAlgo[Rx][Ry]-=20000;
							pData.pExp++;
							totalEnem++;
						}
					}
					else if(checkForArmor(box,Px,tempY-1))
					{
						roomAlgo[Rx][Ry]-=200000;
						equipArmor(&pData,currentArmor);						
						pData.pArmor=currentArmor;
						Py--;
					}
					else if(checkForWeap(box,Px,tempY-1))
					{
						roomAlgo[Rx][Ry]-=2000000;
						equipWeap(&pData,currentWeap);
						pData.pWeapon=currentWeap;
						Py--;
					}
					else if(checkForTreasure(box,Px,tempY-1))
					{
						roomAlgo[Rx][Ry]-=20000000;
						pData.pMoney+=currentTreas.treasVal;
						pData.pExp++;
						Py--;
					}
					else if (checkForNextRoom(box,Px,tempY-1))
					{
						Ry--;
						Py=roomSize-1;
					}
					else if (checkForWall(box,Px,tempY-1))
					{
						box[Px][Py]=' ';
						Py--;
					}break;
			case 's'://south/down//////////////////////////////////////////////////////////////////////////////////
					if (checkForEnem(box,tempX+1,Py))
					{
						dealDamage(&currentEnem,&pData);
						if(currentEnem.enemHP<=0&&pData.pHP>0)
						{
							Px++;
							pData.pHP+=pData.pCon;
							if (playerHP>pData.pMaxHP)
								playerHP=pData.pHP=pData.pMaxHP;
							roomAlgo[Rx][Ry]-=20000;
							pData.pExp++;
							totalEnem++;
						}
					}
					else if(checkForArmor(box,tempX+1,Py))
					{
						roomAlgo[Rx][Ry]-=200000;
						equipArmor(&pData,currentArmor);						
						pData.pArmor=currentArmor;
						Px++;
					}
					else if(checkForWeap(box,tempX+1,Py))
					{
						roomAlgo[Rx][Ry]-=2000000;
						equipWeap(&pData,currentWeap);
						pData.pWeapon=currentWeap;
						Px++;
					}
					else if(checkForTreasure(box,tempX+1,Py))
					{
						roomAlgo[Rx][Ry]-=20000000;
						pData.pMoney+=currentTreas.treasVal;
						pData.pExp++;
						Px++;
					}					
					else if (checkForNextRoom(box,tempX+1,Py))
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
	}while(move!='E'&&pData.pHP>0);
	system("cls");
	if (pData.pHP<=0)	
	{
		box[Px][Py]='X';
		printBoard(box,Px,Py,Rx,Ry,roomAlgo);
		printf("YOU DIED.");
		printf("\nYou have killed a total of %d enemies",totalEnem);
	}
	else printf("Test End.");
}	
