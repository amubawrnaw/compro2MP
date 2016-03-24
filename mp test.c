#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define playerSymbol 'P'
#define roomSize 7
#define roomLimit 100

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
typedef struct roomTag room;

struct  roomTag{
	int roomCode;//code used to generate rooms
	int mLocX //Monster X coordinate
		,mLocY //Monster Y coordinate
		,aLocX //Armor X coordinate
		,aLocY //Armor Y coordinate
		,wLocX //Weapon X coordinate
		,wLocY //Weapon Y coordinate
		,tLocX //Treasure X coordinate
		,tLocY //Treasure Y coordinate
		,sLocX //Surface Link X coordinate
		,sLocY; //Surface Link Y coordinate
	room *northRoom;//Node to north room
	room *eastRoom;//Node to east room
	room *westRoom;//Node to west room
	room *southRoom;//Node to south room
	weapon roomWeapon;//struct containing the room's weapon stats
	armor roomArmor;//struct containing the room's armor stats
	treasure roomTreasure;//struct containing the room's treasure stats
	enemy roomEnem;//struct containing the room's enemy stats
};
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
	printf("\n\t\t %s\n\n",dataName[0]);
	for (i=1;i<3;i++)
		printf("\t\t %s: %d\n\n",dataName[i],data[i-1]);
	printf("\t\t --------\n");
	for (i=3;i<8;i++)
		printf("\t\t%c%s: %d%c\n\n",ptr[i-3],dataName[i],data[i-1],ptr2[i-3  ]);
	printf("\n\n\t\t W-S  to select\t\n\t\t ENTER to upgrade");
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
	printf("\n\n \t\tPress any key to start...");
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
void treasureData(room *currentRoom,player pData)
{
	currentRoom->roomTreasure.treasVal=(getRange(pData.pLvl,pData.pLvl+5))*10;
}
void weaponData(room *currentRoom, player pData)
{
	int max=pData.pLvl-3;
	char weaponName[10][101]={"Sword","Shield","Water Bottle","Pencil","Balloon","All nighter","Booster C","Chair","Stick","Spoon"};
	strcpy(currentRoom->roomWeapon.weapName,weaponName[returnRand(10)]);//weapon Name
	if (max<0)
		max=0;
	currentRoom->roomWeapon.weapVal=(getRange(max,pData.pLvl))*10;
	currentRoom->roomWeapon.weapDmg=getRange(pData.pLvl*0.1,pData.pLvl*0.5);
	currentRoom->roomWeapon.weapHP=getRange(1,5);	
}
void armorData(room *currentRoom, player pData)
{	
	int max=pData.pLvl-3;
	char armorName[10][101]={"T-Shirt","Polo-Shirt","Polo","Shorts","Yes","Jacket","Sweater","Steel Armor","Dress","Suit"};
	strcpy(currentRoom->roomArmor.armorName,armorName[returnRand(10)]);//Armor name
	if (max<0)
		max=0;	
	currentRoom->roomArmor.armorVal=(getRange(max,pData.pLvl+1))*10;
	currentRoom->roomArmor.armorDef=getRange(pData.pLvl*0.1,pData.pLvl*0.7);
	currentRoom->roomArmor.armorHp=getRange(1,5);
}
void enemData(room *currentRoom, player pData)
{
	int max=pData.pLvl-3,maxHP=pData.pLvl-5;
	char monsterName[10][41]={"COMPRO2","DISCTRU","GOBLIN","ORC","DLSU","SOCTEC1","CCSTRIG","DEADLINE","MP","SLEEP" };
	strcpy(currentRoom->roomEnem.enemName,monsterName[returnRand(10)]);//Enem Name
	if (max<0)
		max=0;
	if (maxHP<0)
		maxHP=0;
	currentRoom->roomEnem.enemDmg=(getRange(max,pData.pLvl+1))*.3;
	currentRoom->roomEnem.enemHP=getRange(maxHP,pData.pLvl);
}
void dealDamage(room *currentRoom, player *pData)
{
	int max=currentRoom->roomEnem.enemDmg-pData->pDef;
	currentRoom->roomEnem.enemHP-=pData->pDmg;
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
void printBoard(char box[][roomSize],int totalRooms, room *currentRoom,int x,int y)
{
	int i,j;
	system("cls");
	printf(" W-A-S-D to move:\n P to Check Self\n\n Room Code: %d\n\n Px: %d\n\n Py: %d\n\n Total Rooms explored: %d/%d\n\n\n\t\t",currentRoom->roomCode,x,y,totalRooms,roomLimit);
	for(i=0;i<roomSize;i++)
		{
			for(j=0;j<roomSize;j++)
			{
				printf("%c",box[i][j]);
			}
			printf("\n\t\t");
		}
	} 
void  generateRoom (char box[][roomSize],int roomAlgo[][3],int a,int b,player pData, room *currentRoom)
{
	int x,y,roomGate=currentRoom->roomCode;
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
		box[getRange(1,roomSize-2)][getRange(1,roomSize-2)]='S';
	}
	if (roomGate%100000000/10000000)//Treasure
	{	
		if (roomGate%100000000/10000000==1)
		{
			currentRoom->tLocX=getRange(1,roomSize-2);		
			currentRoom->tLocY=getRange(1,roomSize-2);
			roomGate+=10000000;		
			treasureData(currentRoom,pData);
		}
		box[currentRoom->tLocX][currentRoom->tLocY]='T';
	}
	if (roomGate%10000000/1000000)//Weapon	
	{
		if (roomGate%10000000/1000000==1)
		{
			currentRoom->wLocX=getRange(1,roomSize-2);
			currentRoom->wLocY=getRange(1,roomSize-2);
			weaponData(currentRoom,pData);
			roomGate+=1000000;
		}
		box[currentRoom->wLocX][currentRoom->wLocY]='W';			
	}
	if (roomGate%1000000/100000)//Armor
	{
		if (roomGate%1000000/100000==1)
		{
			currentRoom->aLocX=getRange(1,roomSize-2);
			currentRoom->aLocY=getRange(1,roomSize-2);				
			armorData(currentRoom,pData);	
			roomGate+=100000;
		}
		box[currentRoom->aLocX][currentRoom->aLocY]='A';	
	}
	if (roomGate%100000/10000)//Monster
	{
		if (roomGate%100000/10000==1)
		{
			currentRoom->mLocX=getRange(1,roomSize-2);
			currentRoom->mLocY=getRange(1,roomSize-2);	
			enemData(currentRoom,pData);
			roomGate+=10000;
		}
		box[currentRoom->mLocX][currentRoom->mLocY]='M';	
	}
//////////////////////////////////////////yes///////////////////////////////////////////////////////
	if (roomGate%10000/1000)//North gate
		box[0][roomSize/2]=' ';
	if (roomGate%1000/100)//East gate
		box[roomSize/2][roomSize-1]=' ';
	if (roomGate%100/10)//West gate
		box[roomSize/2][0]=' ';
	if (roomGate%10)//South gate
		box[roomSize-1][roomSize/2]=' ';
	currentRoom->roomCode=roomGate;
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
    return rand()%choices;
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
	printf("\n\n\t Name : %s",currentName);
	for (i=0;i<26;i++)
	{
		if (i%7==0)
			printf("\n\n\n\t");
		printf("%c%c  ",ptr[i],alphabet[i]);	
	}
	printf(" %cSpace",ptr[i]);
	printf("\n\n\n\n\t G\t   - Accept name\n\n\t Backspace - erase letter \n\n\t \\\t   - Go uppercase\n\n\t ENTER\t   - select letter");
}
void nameGen(char currentName[])
{
	int i,j,tempX,PtrX=0,letter=0,min=65,max=90,upperCase=1;
	char alphabet[27], ptr[27]={'>',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},input;
	alphabet[26]=' ';
	do{
		if (upperCase||!letter)
		{
			min=65;
			max=90;			
		}
		else
		{
			min=97;
			max=122;
		}
		for (i=min,j=0;i<=max;i++,j++)
			alphabet[j]=i;	
		system("cls");
		printSelection(alphabet,ptr,currentName);
		do{
			input=getch();		
		}while(input!='w'&&input!='a'&&input!='s'&&input!='d'&&input!='\r'&&input!='\b'&&input!='g'&&input!='\\'&&input!='G');
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
					upperCase=0;
					if (PtrX==26)
						upperCase=1;
					break;
			case '\b':
					if (letter>0)
					{
						currentName[letter-1]=' ';
						letter--;break;
					}
			case '\\':upperCase=1;break;
		}
		ptr[PtrX]='>';	
	}while(input!='g'&&input!='G');
}
////////////////////////////////////////////////////////////////////////////////////////
int genRoomCode(int source)
{
	int i,code=10;
	for(i=0;i<4;i++)
		code=code*10+returnRand(2);
	for(i=0;i<4;i++)
	{
		code=code*10+returnRand(4);
		if(code%10!=0)
		{
			code-=code%10;
			code+=1;
		}
	}
	if(code%(source*10)/source==0)
		code+=source;
	return code;
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
		,playerHP//player HP 
		,totalRooms=1;//counts the total number of rooms explored
	char move//user input for player interaction
		,box[roomSize][roomSize]//room array
		,playerName[101]=""//player's name
		,dataName[9][30]={"","SP   ","exp  ","Level","dmg  ","def  ","hp   ","con  ","Money"}//starting skill names
		,temp[51];//temporary player name holder
	
	
	srand(time(NULL));
	struct playerTag pData;
	struct roomTag *currentRoom, *newRoom, spawnRoom;
	
	spawnRoom.roomCode=1000001111;
	currentRoom=&spawnRoom;
	spawnRoom.eastRoom=NULL;
	spawnRoom.northRoom=NULL;
	spawnRoom.southRoom=NULL;
	spawnRoom.westRoom=NULL;
	
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

		generateRoom(box,roomAlgo,Rx,Ry,pData,currentRoom);
		box[Px][Py]=playerSymbol;
		printBoard(box,totalRooms,currentRoom,Px,Py);
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
						dealDamage(currentRoom,&pData);
						playerHP=pData.pHP;
						if(currentRoom->roomEnem.enemHP<=0&&pData.pHP>0)
						{
							Px--;
							playerHP+=pData.pCon;
							if (playerHP>pData.pMaxHP)
								playerHP=pData.pHP=pData.pMaxHP;
							currentRoom->roomCode-=20000;
							pData.pExp++;
							totalEnem++;
						}
					}
					else if(checkForArmor(box,tempX-1,Py))
					{
						currentRoom->roomCode-=200000;
						equipArmor(&pData,currentRoom->roomArmor);
						pData.pArmor=currentRoom->roomArmor;
						Px--;
					}
					else if(checkForWeap(box,tempX-1,Py))
					{
						currentRoom->roomCode-=2000000;
						equipWeap(&pData,currentRoom->roomWeapon);
						pData.pWeapon=currentRoom->roomWeapon;
						Px--;
					}
					else if(checkForTreasure(box,tempX-1,Py))
					{
						currentRoom->roomCode-=20000000;
						pData.pMoney+=currentRoom->roomTreasure.treasVal;
						Px--;
						pData.pExp++;
						
					}
					else if (checkForNextRoom(box,tempX-1,Py))
					{
						if (currentRoom->northRoom!=NULL)
							currentRoom=currentRoom->northRoom;
						else 
						{
							newRoom=malloc(sizeof(room));
							newRoom->roomCode=genRoomCode(1);
							newRoom->northRoom=NULL;
							newRoom->eastRoom=NULL;	
							newRoom->westRoom=NULL;
							newRoom->southRoom=currentRoom;
							currentRoom->northRoom=newRoom;			
							newRoom=NULL;
							currentRoom=currentRoom->northRoom;	
							totalRooms++;										
						}
						Px=roomSize-1;
						Py=roomSize/2;						
					}
					else if (checkForWall(box,tempX-1,Py))
					{
						box[Px][Py]=' ';
						Px--;
					}break;
			case 'd'://east/right//////////////////////////////////////////////////////////////////////////////////
					if (checkForEnem(box,Px,tempY+1))
					{
						dealDamage(currentRoom,&pData);
						playerHP=pData.pHP;
						if(currentRoom->roomEnem.enemHP<=0&&pData.pHP>0)
						{
							Py++;
							pData.pHP+=pData.pCon;
							if (playerHP>pData.pMaxHP)
								playerHP=pData.pHP=pData.pMaxHP;
							currentRoom->roomCode-=20000;
							pData.pExp++;
							totalEnem++;
						}
					}
					else if(checkForArmor(box,Px,tempY+1))
					{
						currentRoom->roomCode-=200000;
						equipArmor(&pData,currentRoom->roomArmor);
						pData.pArmor=currentRoom->roomArmor;
						Py++;
					}
					else if(checkForWeap(box,Px,tempY+1))
					{
						currentRoom->roomCode-=2000000;
						equipWeap(&pData,currentRoom->roomWeapon);
						pData.pWeapon=currentRoom->roomWeapon;
						Py++;
					}
					else if(checkForTreasure(box,Px,tempY+1))
					{
						currentRoom->roomCode-=20000000;
						pData.pMoney+=currentRoom->roomTreasure.treasVal;
						pData.pExp++;
						Py++;
					}
					else if (checkForNextRoom(box,Px,tempY+1))
					{
						if (currentRoom->eastRoom!=NULL)
							currentRoom=currentRoom->eastRoom;
						else
						{
							newRoom=malloc(sizeof(room));
							newRoom->roomCode=genRoomCode(10);
							newRoom->northRoom=NULL;
							newRoom->eastRoom=NULL;
							newRoom->westRoom=currentRoom;
							newRoom->southRoom=NULL;
							currentRoom->eastRoom=newRoom;
							currentRoom=currentRoom->eastRoom;
							newRoom=NULL;
							totalRooms++;
						}
						Py=0;
						Px=roomSize/2;
					}
					else if (checkForWall(box,Px,tempY+1))
					{
						box[Px][Py]=' ';
						Py++;
					}break;		
			case 'a'://west/left//////////////////////////////////////////////////////////////////////////////////
					if (checkForEnem(box,Px,tempY-1))
					{
						dealDamage(currentRoom,&pData);
						playerHP=pData.pHP;
						if(currentRoom->roomEnem.enemHP<=0&&pData.pHP>0)
						{
							Py--;
							pData.pHP+=pData.pCon;
							if (playerHP>pData.pMaxHP)
								playerHP=pData.pHP=pData.pMaxHP;
							currentRoom->roomCode-=20000;
							pData.pExp++;
							totalEnem++;
						}
					}
					else if(checkForArmor(box,Px,tempY-1))
					{
						currentRoom->roomCode-=200000;
						equipArmor(&pData,currentRoom->roomArmor);
						pData.pArmor=currentRoom->roomArmor;
						Py--;
					}
					else if(checkForWeap(box,Px,tempY-1))
					{
						currentRoom->roomCode-=2000000;
						equipWeap(&pData,currentRoom->roomWeapon);
						pData.pWeapon=currentRoom->roomWeapon;
						Py--;
					}
					else if(checkForTreasure(box,Px,tempY-1))
					{
						currentRoom->roomCode-=20000000;
						pData.pMoney+=currentRoom->roomTreasure.treasVal;
						pData.pExp++;
						Py--;
					}
					else if (checkForNextRoom(box,Px,tempY-1))
					{
						if (currentRoom->westRoom!=NULL)
							currentRoom=currentRoom->westRoom;
						else
						{
							newRoom=malloc(sizeof(room));
							newRoom->roomCode=genRoomCode(100);
							newRoom->northRoom=NULL;
							newRoom->eastRoom=currentRoom;	
							newRoom->westRoom=NULL;
							newRoom->southRoom=NULL;
							currentRoom->westRoom=newRoom;
							currentRoom=currentRoom->westRoom;
							newRoom=NULL;
							totalRooms++;
						}
						Py=roomSize-1;
						Px=roomSize/2;
					}
					else if (checkForWall(box,Px,tempY-1))
					{
						box[Px][Py]=' ';
						Py--;
					}break;
			case 's'://south/down//////////////////////////////////////////////////////////////////////////////////
					if (checkForEnem(box,tempX+1,Py))
					{
						dealDamage(currentRoom,&pData);
						playerHP=pData.pHP;
						if(currentRoom->roomEnem.enemHP<=0&&pData.pHP>0)
						{
							Px++;
							pData.pHP+=pData.pCon;
							if (playerHP>pData.pMaxHP)
								playerHP=pData.pHP=pData.pMaxHP;
							currentRoom->roomCode-=20000;
							pData.pExp++;
							totalEnem++;
						}
					}
					else if(checkForArmor(box,tempX+1,Py))
					{
						currentRoom->roomCode-=200000;
						equipArmor(&pData,currentRoom->roomArmor);
						pData.pArmor=currentRoom->roomArmor;
						Px++;
					}
					else if(checkForWeap(box,tempX+1,Py))
					{
						currentRoom->roomCode-=2000000;
						equipWeap(&pData,currentRoom->roomWeapon);
						pData.pWeapon=currentRoom->roomWeapon;
						Px++;
					}
					else if(checkForTreasure(box,tempX+1,Py))
					{
						currentRoom->roomCode-=20000000;
						pData.pMoney+=currentRoom->roomTreasure.treasVal;
						pData.pExp++;
						Px++;
					}					
					else if (checkForNextRoom(box,tempX+1,Py))
					{
						if (currentRoom->southRoom!=NULL)
							currentRoom=currentRoom->southRoom;
						else
						{
							newRoom=malloc(sizeof(room));
							newRoom->roomCode=genRoomCode(1000);
							newRoom->northRoom=currentRoom;
							newRoom->eastRoom=NULL;	
							newRoom->westRoom=NULL;
							newRoom->southRoom=NULL;
							currentRoom->southRoom=newRoom;
							currentRoom=currentRoom->southRoom;
							newRoom=NULL;
						}
						Px=0;
						Py=roomSize/2;
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
	}while(move!='E'&&pData.pHP>0&&totalRooms!=roomLimit);
	system("cls");
	if (pData.pHP<=0)	
	{
		box[Px][Py]='X';
		printBoard(box,totalRooms,currentRoom,Px,Py);
		printf("YOU DIED.");
		printf("\nYou have killed a total of %d enemies",totalEnem);
	}
	else if(totalRooms>=roomLimit)
	{
		printBoard(box,totalRooms,currentRoom,Px,Py);
		printf("hoy cheater you cant win the game yet hoy");
	}
	else printf("Test End.");
}	
