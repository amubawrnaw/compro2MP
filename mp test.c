#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

#define playerSymbol 'P'
#define roomSize 11
#define roomLimit 100

struct treasureTag{
	char treasName[51];
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
	int boss;
};

typedef struct enemyTag enemy;
typedef struct armorTag armor;
typedef struct weaponTag weapon;
typedef struct playerTag player;
typedef struct treasureTag treasure;
typedef struct roomTag room;
typedef struct invTag inv;
struct  roomTag{
	int roomCode;//code used to generate rooms
	int mLocX //Monster X coordinate
		,mLocY //Monster Y coordinate
		,aLocX //Armor X coordinate
		,aLocY //Armor Y coordinate
		,wLocX //Weapon X coordinate
		,wLocY //Weapon Y coordinate
		,tLocX //Treasure X coordinate
		,tLocY; //Treasure Y coordinate
	room *northRoom;//Node to north room
	room *eastRoom;//Node to east room
	room *westRoom;//Node to west room
	room *southRoom;//Node to south room
	weapon roomWeapon;//struct containing the room's weapon stats
	armor roomArmor;//struct containing the room's armor stats
	treasure roomTreasure;//struct containing the room's treasure stats
	enemy roomEnem;//struct containing the room's enemy stats
};
struct invTag{
	char itemName[101];
	char itemType[21];
	char ptr;
	int val;
	int dmg;
	int def;
	int hp;
	inv *invNext;
	inv *invPrev; 
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
	char input;
	do{
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
		input=getch();
	}while(input!='\b');
	
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
void treasureData(room *currentRoom,player pData,FILE *treasureNames,int treasureNum)
{
	char chosen[101];
	int i;
	for (i=0;i<returnRand(treasureNum);i++)
		fscanf(treasureNames,"%s",chosen);
	for(i=0;i<strlen(chosen);i++)
		if(chosen[i]==',')
			chosen[i]=' ';
	strcpy(currentRoom->roomEnem.enemName,chosen);
	currentRoom->roomTreasure.treasVal=(getRange(pData.pLvl,pData.pLvl+5))*10;
}
void weaponData(room *currentRoom, player pData,FILE *weaponNames,int weaponNum)
{
	int i,max=pData.pLvl-3;
	char chosen[101];
	if (max<0)
		max=0;
	for (i=0;i<returnRand(weaponNum);i++)
		fscanf(weaponNames,"%s",chosen);
	for(i=0;i<strlen(chosen);i++)
		if(chosen[i]==',')
			chosen[i]=' ';
	printf("%s",chosen);
	getch();
	strcpy(currentRoom->roomWeapon.weapName,chosen);	
	currentRoom->roomWeapon.weapVal=(getRange(max,pData.pLvl))*10;
	currentRoom->roomWeapon.weapDmg=getRange(pData.pLvl*0.1,pData.pLvl*0.5);
	currentRoom->roomWeapon.weapHP=getRange(1,5);	
}
void armorData(room *currentRoom, player pData, FILE *armorNames,int armorNum)
{	
	int i,max=pData.pLvl-3;
	char chosen[101];
	for(i=0;i<returnRand(armorNum);i++)
		fscanf(armorNames,"%s",chosen);
	for(i=0;i<strlen(chosen);i++)
	{
		if(chosen[i]==',')
			chosen[i]=' ';
		else if(chosen[i]=='.')
			chosen[i]='\b';
	}	

	getch();
	strcpy(currentRoom->roomArmor.armorName,chosen);
	if (max<0)
		max=0;	
	currentRoom->roomArmor.armorVal=(getRange(max,pData.pLvl+1))*10;
	currentRoom->roomArmor.armorDef=getRange(pData.pLvl*0.1,pData.pLvl*0.7);
	currentRoom->roomArmor.armorHp=getRange(1,5);
}
void enemData(room *currentRoom, player pData,FILE *enemyNames,int enemNum)
{
	int max=pData.pLvl-3,maxHP=pData.pLvl-5,i;
	char chosen[101];
	for(i=0;i<returnRand(enemNum);i++)
		fscanf(enemyNames,"%s",chosen);
	for(i=0;i<strlen(chosen);i++)
		if(chosen[i]==',')
			chosen[i]=' ';
	strcpy(currentRoom->roomEnem.enemName,chosen);
	if (max<0)
		max=0;
	if (maxHP<0)
		maxHP=0;
	currentRoom->roomEnem.enemDmg=(getRange(max,pData.pLvl+1))*.3;
	currentRoom->roomEnem.boss=1;
	if (currentRoom->roomEnem.boss==1)
	{
		currentRoom->roomEnem.enemHP=(getRange(maxHP,pData.pLvl))*3;
		currentRoom->roomCode+=10000000;
	}
	else currentRoom->roomEnem.enemHP=getRange(maxHP,pData.pLvl);
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
	if (box[x][y]=='M'||box[x][y]=='B')
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
	int i,j,yes=currentRoom->roomCode;
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
	if (yes/1000000000==2)
		printf("\n\nDont forget to equip your armor and weapon!");
} 
void  generateRoom (char box[][roomSize],int a,int b,player pData, room *currentRoom,FILE *bossNames, FILE *enemNames,FILE *armorNames,FILE *weaponNames,FILE *treasureNames, FILE *fTitle,int enemNum,int bossNum,int armorNum,int weaponNum,int treasureNum)
{
	int x,y,roomGate=currentRoom->roomCode;
	for(x=0;x<roomSize;x++)
		{
			for(y=0;y<roomSize;y++)
			{
				if (x==roomSize-1&&y==roomSize-1&&roomGate%1000000000/100000000==0)
					box[x][y]=188;//lower right
				else if(x==0&&y==roomSize-1&&roomGate%1000000000/100000000==0)
					box[x][y]=187;//upper right
				else if(x==0&&y==0&&roomGate%1000000000/100000000==0)
					box[x][y]=201;//upper left
				else if(x==roomSize-1&&y==0&&roomGate%1000000000/100000000==0)
					box[x][y]=200;//lower left			
				else if (x==0||x==roomSize-1)
					box[x][y]=205;//horizontal wall
				else if (y==0||y==roomSize-1)
					box[x][y]=186;//vertical wall
				else box[x][y]=' ';
			}
		}	
	if (roomGate%1000000000/100000000)//Surface Link 
	{	
		box[getRange(1,roomSize-2)][getRange(1,roomSize-2)]='S';
		box[0][0]=box[0][roomSize-1]=box[roomSize-1][0]=box[roomSize-1][roomSize-1]='O';
	}
	if (roomGate%100000000/10000000)//Treasure
	{	
		if (roomGate%100000000/10000000==1)
		{
			currentRoom->tLocX=getRange(1,roomSize-2);		
			currentRoom->tLocY=getRange(1,roomSize-2);		
			treasureData(currentRoom,pData,treasureNames,treasureNum);
			if (currentRoom->roomEnem.boss==1)
			{
				currentRoom->tLocX=currentRoom->mLocX;
				currentRoom->tLocY=currentRoom->mLocY;
			}
			else
			{
				currentRoom->tLocX=getRange(1,roomSize-2);		
				currentRoom->tLocY=getRange(1,roomSize-2);
			}
			roomGate+=10000000;
		}
		box[currentRoom->tLocX][currentRoom->tLocY]='T';
	}
	if (roomGate%10000000/1000000)//Weapon	
	{
		if (roomGate%10000000/1000000==1)
		{
			currentRoom->wLocX=getRange(1,roomSize-2);
			currentRoom->wLocY=getRange(1,roomSize-2);
			weaponData(currentRoom,pData,weaponNames,weaponNum);
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
			armorData(currentRoom,pData,armorNames,armorNum);	
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
			enemData(currentRoom,pData,enemNames,enemNum);
			roomGate+=10000;
		}
		if (currentRoom->roomEnem.boss!=1)
			box[currentRoom->mLocX][currentRoom->mLocY]='M';	
		else	
		{
			box[currentRoom->mLocX][currentRoom->mLocY]='B'; 
			if (roomGate%100000000/10000000==0)
				roomGate+=10000000;
		}


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
int isWithinAlphabet(int x)
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
	alphabet[26]='_';
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
					if (isWithinAlphabet(tempX-7))
					{
						ptr[PtrX]=' ';	
						PtrX-=7;
					}break;
			case 'a':
					if (isWithinAlphabet(tempX-1))
					{
						ptr[PtrX]=' ';	
						PtrX--;
					}break;
			case 's':
					if (isWithinAlphabet(tempX+7))
					{
						ptr[PtrX]=' ';	
						PtrX+=7;
					}break;
			case 'd':
					if (isWithinAlphabet(tempX+1))
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
	code=code*10+returnRand(5);//20% chance for treasure to appear
	if (code%10!=1)
		code-=code%10;
	code=code*10+returnRand(1);//20% chance for weapon to appear
	if (code%10!=1)
		code-=code%10;
	code=code*10+returnRand(5);//20% chance for armor to appear
	if (code%10!=1)
		code-=code%10;
	code=code*10+returnRand(2);//50% chance for enemy to appear

	for(i=0;i<4;i++)//for loop for gates
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
FILE fileChecker(FILE *boss, FILE *monster,FILE *armor,FILE *weapon,FILE *treasure, FILE *fTitle,FILE *saveN)
{
	system("cls");
	if (boss==NULL||monster==NULL||armor==NULL||weapon==NULL||treasure==NULL||fTitle==NULL)
	{
		printf("\n\n\tERROR! MISSING FILES:\n\n\t");	
		if (boss==NULL)
			printf("-bossNames.txt\n\t");
		if (monster==NULL)
			printf("-monsterNames.txt\n\t");
		if (armor==NULL)
			printf("-armorNames.txt\n\t");
		if (weapon==NULL)
			printf("-weaponNames.txt\n\t");
		if (treasure==NULL)
			printf("-treasureNames.txt\n\t");
		if (fTitle==NULL)
			printf("-titleScreen.txt\n\t");
		if (saveN==NULL)
			printf("-saveNames.txt\n\t");
		fclose(boss);
		fclose(monster);
		fclose(armor);
		fclose(weapon);
		fclose(treasure);
		fclose(saveN);
		fclose(fTitle);
		exit(1);
	}
}
int titleScreen(char titleS[][56], int select)
{
	int i,x=0,tempX;
	char ptr[2]={'>'},input;
	if(select!=0)
		ptr[1]=' ';
	do{
		system("cls");
		printf("\n\n");
		for (i=0;i<17;i++)
			printf("\t     %s\n",titleS[i]);
		printf("\n\t\t%c New Game",ptr[0]);
		if(select!=0)
			printf("\n\t\t%c Continue Game",ptr[1]);
		
		
		do{
			input=getch();
		}while(input!='w'&&input!='s'&&input!='\r');
		tempX=x;
		switch(input)
		{
			case 'w':if (ptr[tempX-1]==' ')
					{
						ptr[x]=' ';
						x--;
					}break;
			case 's':if (ptr[tempX+1]==' ')
					{
						ptr[x]=' ';	
						x++;
					}
		}
		ptr[x]='>';
	}while(input!='\r');
	return x;
}
int isWithinRange(int x, char base[])
{
	if (base[x]==' ')
		return 1;
	else return 0;
}
int contGame(char nameArray[][40],int saveNum)
{
	int i,x=0,tempX;
	char ptr[saveNum],input;
	ptr[0]='>';
	for(i=1;i<saveNum;i++)
		ptr[i]=' ';

	do{
		system("cls");
		printf("\n");
		for(i=0;i<saveNum;i++)
			printf(" \t\t%c%s\n",ptr[i],nameArray[i]);
		do{
			input=getch();
		}while(input!='w'&&input!='s'&&input!='\r'&&input!='\b');
		tempX=x;
		switch(input)
		{
			case 'w':
					if (isWithinRange(tempX-1,ptr))
					{
						ptr[x]=' ';
						x--;
					}break;
			case 's':
					if (isWithinRange(tempX+1,ptr))
					{
						ptr[x]=' ';
						x++;
					}break;
			case '\r':return x;break;
			case '\b':return -1;
		}
		ptr[x]='>';
	}while(1);
}
int countFiles(FILE *source)
{
	int x=0;
	char symbol=' ';
	for (;symbol!='#';)
	{
		fscanf(source," %c",&symbol);
		if (symbol=='.')
			x++;
	}
	fclose(source);
	return x;
}
void viewInv(char weapInv[][51],char armorInv[][51],char treasInv[][51],int weapBase,int armorBase,int treasBase,char input)
{
	int x,tempX,start=0,i;
	do{
		x=0;
		
		do{
		}while(input!='t'&&input!='y'&&input!='u'&&input!='\r');
		
	}while(input!='\r');
}
void playerInventory(inv **baseWep,inv **baseTreas,inv **baseArmor,player *pData)
{
	int i,x,tempX;
	char input;
	do{
		
	}while(input!='\r');
}
void createFiles(char playerName[101],FILE **mapcodes, FILE **mapdir,FILE **pstats,FILE **weapinv,FILE **weapstats,FILE **armorstats,FILE **armorinv,FILE **treasinv,FILE **treasstats,FILE **tempmap, FILE **tempdir)
{
	char saveFileName[101],createFolder[101]="mkdir ",folderDIR[101]="./",mapCodes[51],mapDir[51],pStats[51],tempMap[51],tempDir[51];
	char weapInv[51],armorInv[51],treasInv[51],weapStats[51],armorStats[51],treasStats[51];
	FILE *saveNames;

	strcat(createFolder,playerName);
	strcat(createFolder,"Save");
	
	system(createFolder);
	
	strcat(folderDIR,playerName);
	strcat(folderDIR,"Save");
	strcat(folderDIR,"/");
	
	strcpy(mapCodes,folderDIR);
	strcat(mapCodes,"mapCodes.txt");
	
	strcpy(mapDir,folderDIR);
	strcat(mapDir,"mapDir.txt");
	
	strcpy(pStats,folderDIR);
	strcat(pStats,"pStats.txt");
	
	strcpy(saveFileName,folderDIR);
	strcat(saveFileName,playerName);
	strcat(saveFileName,".txt");	
	
	strcpy(weapInv,folderDIR);
	strcat(weapInv,"weapInv.txt");
	
	strcpy(weapStats,folderDIR);
	strcat(weapStats,"weapStats.txt");
	
	strcpy(armorInv,folderDIR);
	strcat(armorInv,"armorInv.txt");
	
	strcpy(armorStats,folderDIR);
	strcat(armorStats,"armorStats.txt");
	
	strcpy(treasInv,folderDIR);
	strcat(treasInv,"treasInv.txt");
	
	strcpy(treasStats,folderDIR);
	strcat(treasStats,"treasStats.txt");
	
	strcpy(tempMap,folderDIR);
	strcat(tempMap,"tempMap.txt");
	
	strcpy(tempDir,folderDIR);
	strcat(tempDir,"tempDir.txt");
	
	*mapcodes=fopen(mapCodes,"w");
	*mapdir=fopen(mapDir,"w");
	*pstats=fopen(pStats,"w");
	*weapinv=fopen(weapInv,"w");
	*weapstats=fopen(weapStats,"w");
	*armorstats=fopen(armorStats,"w");
	*armorinv=fopen(armorInv,"w");
	*treasinv=fopen(treasInv,"w");
	*treasstats=fopen(treasStats,"w");
	*tempmap=fopen(tempMap,"w");
	*tempdir=fopen(tempDir,"w");
	
	saveNames=fopen("saveNames.txt","a");
	fprintf(saveNames,"\n%s",playerName);
	fclose(saveNames);
}
int loadGame(char array[][101],int base)
{
	int x=0,tempX,i,start=0,max=base;
	char ptr[base],input;
	ptr[0]='>';
	for(i=1;i<base;i++)
		ptr[i]=' ';
	if (max>10)
		max=10;
	do{
		system("cls");
		printf("\n\n\tChoose a Save file:\n\n");
		for(i=0;i<start+max;i++)
			printf("\t %c %s\n\n ",ptr[i],array[i]);
		do{
			input=getch();
		}while(input!='w'&&input!='s'&&input!='\r');
		tempX=x;
		switch(input)
		{
			case 'w':if(checkLimit(ptr,tempX-1)&&x!=start)
					{
						ptr[x]=' ';
						x--;
					}
					else if(x==start&&start!=0)
						start--;
					break;
			case 's':if(checkLimit(ptr,tempX+1)&&x!=start+max)
					{
						ptr[x]=' ';
						x++;
					}
					else if(x==start+max&&start!=base)
						start++;
					break;
		}
		ptr[x]='>';
	}while(input!='\r');
	return x;
}
int main()
{
	int	i//loop
		,j//loop
		,Px=roomSize/2//player start
		,Py=roomSize/2//player start
		,tempX //contains the destination of X
		,tempY //contains the destination of Y
		,Rx=1//x location of the center room
		,Ry=1//y location of the center room
		,data[7]={7,0,1,0,0,0,0}//starting skill distribution
        ,randNum//contains the random number
        ,killedEnem=0//counts the number of enemy kills to level up
        ,totalEnem=0//counts how many enemies you've killed so far
		,playerHP//player HP 
		,totalRooms=1//counts the total number of rooms explored
		,gameSelect
		,saveNum=0
		,saveFile=0
		,enemNum=0
		,armorNum=0
		,weaponNum=0
		,treasureNum=0
		,bossNum=0
		,loadNum;
		
	char move//user input for player interaction
		,box[roomSize][roomSize]//room array
		,playerName[101]=""//player's name
		,dataName[9][30]={"","SP   ","exp  ","Level","dmg  ","def  ","hp   ","con  ","Money"}//starting skill names
		,temp[51]//temporary player name holder
		,title[17][56]	
		,mapCodesN[51]
		,mapDirN[51]
		,pStatsN[51]
		,weapInvN[51]
		,weapStatsN[51]
		,armorStatsN[51]
		,armorInvN[51]
		,treasInvN[51]
		,treasStatsN[51]
		,tempMapN[51]
		,tempDirN[51]
		,folderDIR[51]="./"
		,scanned;
		
	srand(time(NULL));
	struct playerTag pData;
	struct roomTag *currentRoom, *newRoom, spawnRoom;
	
	spawnRoom.roomCode=2000001111;
	currentRoom=&spawnRoom;
	spawnRoom.eastRoom=NULL;
	spawnRoom.northRoom=NULL;
	spawnRoom.southRoom=NULL;
	spawnRoom.westRoom=NULL;
	
	inv *baseWeap,*baseArmor,*baseTreas;
	inv *newWeap,*newArmor,*newTreas;
	inv *lastWeap,*lastArmor,*lastTreas;
	baseWeap=malloc(sizeof(inv));
	baseArmor=malloc(sizeof(inv));
	baseTreas=malloc(sizeof(inv));
	
	FILE *boss,*monster,*armor,*weapon,*treasure,*fTitle,*saveNames,*currentSave;
	
	FILE *mapCodes, *mapDir,*pStats,*weapInv,*weapStats,*armorStats,*armorInv,*treasInv,*treasStats,*tempMap,*tempDir;


	boss=fopen("bossNames.txt","r");
	monster=fopen("monsterNames.txt","r");
	armor=fopen("armorNames.txt","r");
	weapon=fopen("weaponNames.txt","r");
	treasure=fopen("treasureNames.txt","r");
	fTitle=fopen("titleScreen.txt","r");
	saveNames=fopen("saveNames.txt","r");	
	
	////////////////////////////////////////declarations////////////////////////////////////////////////
	
	fileChecker(boss,monster,armor,weapon,treasure,fTitle,saveNames);
	

	enemNum=countFiles(monster);
	bossNum=countFiles(boss);
	armorNum=countFiles(armor);
	weaponNum=countFiles(weapon);
	treasureNum=countFiles(treasure);
	saveNum=countFiles(saveNames);
	
	boss=fopen("bossNames.txt","r");
	monster=fopen("monsterNames.txt","r");
	armor=fopen("armorNames.txt","r");
	weapon=fopen("weaponNames.txt","r");
	treasure=fopen("treasureNames.txt","r");
	fTitle=fopen("titleScreen.txt","r");
	saveNames=fopen("saveNames.txt","r");	

	char pNames[saveNum+1][101];
	
	for (i=0;i<saveNum;i++)
		fscanf(saveNames,"%s",pNames[i]);

	for (i=0;i<saveNum;i++)
	{
		for(j=0;j<strlen(pNames[i]);j++)
		{
			if (pNames[i][j]=='.')
				pNames[i][j]='\b';
			else if (pNames[i][j]==',')
				pNames[i][j]=' ';
		}
	}
	fclose(saveNames);
	for(i=0;i<17;i++)
		fscanf(fTitle,"%s",title[i]);
	for(i=0;i<17;i++)
		for(j=0;j<56;j++)
			if(title[i][j]=='.')
				title[i][j]=' ';

	do{
		gameSelect=titleScreen(title,saveNum);
		if (gameSelect==1)
		{
			loadNum=loadGame(pNames,saveNum);
			strcpy(playerName,pNames[loadNum]);
			strcat(folderDIR,playerName);
			strcat(folderDIR,"Save");
			strcat(folderDIR,"/");
			strcpy(mapCodesN,folderDIR);
			strcat(mapCodesN,"mapCodes.txt");
			strcpy(mapDirN,folderDIR);
			strcat(mapDirN,"mapDir.txt");
			strcpy(pStatsN,folderDIR);
			strcat(pStatsN,"pStats.txt");	
			strcpy(weapInvN,folderDIR);
			strcat(weapInvN,"weapInv.txt");
			strcpy(weapStatsN,folderDIR);
			strcat(weapStatsN,"weapStats.txt");
			strcpy(armorInvN,folderDIR);
			strcat(armorInvN,"armorInv.txt");
			strcpy(armorStatsN,folderDIR);
			strcat(armorStatsN,"armorStats.txt");
			strcpy(treasInvN,folderDIR);
			strcat(treasInvN,"treasInv.txt");
			strcpy(treasStatsN,folderDIR);
			strcat(treasStatsN,"treasStats.txt");
			strcpy(tempMapN,folderDIR);
			strcat(tempMapN,"tempMap.txt");
			strcpy(tempDirN,folderDIR);
			strcat(tempDirN,"tempDir.txt");
			
			mapCodes=fopen(mapCodesN,"a");
			mapDir=fopen(mapDirN,"a");
			pStats=fopen(pStatsN,"r");
			weapInv=fopen(weapInvN,"r");
			weapStats=fopen(weapStatsN,"r");
			armorStats=fopen(armorStatsN,"r");
			armorInv=fopen(armorInvN,"r");
			treasInv=fopen(treasInvN,"r");
			treasStats=fopen(treasStatsN,"r");
			tempMap=fopen(tempMapN,"w");
			tempDir=fopen(tempDirN,"w");
			for(i=1;i<=6;i++)
				fscanf(pStats,"%d",data[i]);
			transSkills(data,&pData);
			fscanf(pStats,"%d",pData.pMoney);
			fscanf(pStats,"%d",pData.pMaxHP);
		}
		
	}while(saveFile==-1&&gameSelect==1);
	fclose(saveNames);
	if (gameSelect==0)
	{
		
		nameGen(playerName);
		
		strcat(dataName[0],"Name : ");
		strcat(dataName[0],playerName);
		strcpy(pData.pName,dataName[0]);
		
		createFiles(playerName,&mapCodes, &mapDir,&pStats,&weapInv,&weapStats,&armorStats,&armorInv,&treasInv,&treasStats,&tempMap,&tempDir);
		
		playerData(dataName,data);
		transSkills(data,&pData);
		defaultGear(&pData);
		calcStats(&pData);
		playerHP=pData.pHP;
		for(i=1;i<=6;i++)
			fprintf(pStats,"%d\n",data[i]);
		fprintf(pStats,"%d\n",pData.pMoney);
		fprintf(pStats,"%d\n",pData.pHP);
		fprintf(pStats,"%d",playerHP);
		
		saveNames=fopen("saveNames.txt","w");
		for(i=0;i<saveNum;i++)
		{
			for(j=0;pNames[i][j]=='\n';j++)
			{
				if(j==0)
					fprintf(saveNames,".");
				
			}
		}
	}
	
	do{/////////////////////////////////////////GAME START/////////////////////////////////////////////////////////
		if (pData.pExp==getRoundedVal(pData.pLvl*0.3))
		{
			pData.pLvl++;
			pData.pExp=0;
		}
	
		pClear(&pData);
		calcStats(&pData);
		pData.pHP=playerHP;	

		generateRoom(box,Rx,Ry,pData,currentRoom,boss,monster,armor,weapon,treasure,fTitle,enemNum,bossNum,armorNum,weaponNum,treasureNum);
		box[Px][Py]=playerSymbol;
		printBoard(box,totalRooms,currentRoom,Px,Py);
		do{
			move=getch();
		}while(move!='W'&&move!='A'&&move!='S'&&move!='D'&&move!='w'&&move!='a'&&move!='s'&&move!='d'&&move!='E'&&move!='d'&&move!='p'&&move!='i');
		tempX=Px;
		tempY=Py;
		if (move=='p')
			playerStats(dataName,pData);
		else if (move=='i')
			{
			playerInventory(&baseWeap,&baseTreas,&baseArmor,&pData);
			}
		else if (move=='E')
			{
				system("cls");
				printf("\n\n\n\t\tAre you sure you want to exit the game ?\n\n\t\t   Any unsaved progress will be lost!\n\n\t\t\t\t (Y/N)");
				do{
					move=getch();
				}while(move!='Y'&&move!='y'&&move!='N'&&move!='n');
			}
		else switch(move)
		{
			case 'w'://north/up//////////////////////////////////////////////////////////////////////////////////
					if (checkForEnem(box,tempX-1,Py))
					{
						dealDamage(currentRoom,&pData);
						playerHP=pData.pHP;
						if(currentRoom->roomEnem.enemHP<=0&&pData.pHP>0)
						{
							if (currentRoom->roomEnem.boss!=1)
								Px--;
							playerHP+=pData.pCon;
							if (playerHP>pData.pMaxHP)
								playerHP=pData.pHP=pData.pMaxHP;
							currentRoom->roomCode-=20000;
							fprintf(tempMap,"%d\n",currentRoom->roomCode);
							fprintf(tempDir,"x\n");	
							pData.pExp++;
							totalEnem++;
						}
					}
					else if(checkForArmor(box,tempX-1,Py))
					{
						currentRoom->roomCode-=200000;
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"x\n");
						equipArmor(&pData,currentRoom->roomArmor);
						pData.pArmor=currentRoom->roomArmor;
						Px--;
					}
					else if(checkForWeap(box,tempX-1,Py))
					{
						currentRoom->roomCode-=2000000;
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"x\n");
						equipWeap(&pData,currentRoom->roomWeapon);
						pData.pWeapon=currentRoom->roomWeapon;
						Px--;
					}
					else if(checkForTreasure(box,tempX-1,Py))
					{
						currentRoom->roomCode-=20000000;
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"x\n");
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
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"w\n");						
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
							fprintf(tempMap,"%d\n",currentRoom->roomCode);
							fprintf(tempDir,"x\n");
							pData.pExp++;
							totalEnem++;
						}
					}
					else if(checkForArmor(box,Px,tempY+1))
					{
						currentRoom->roomCode-=200000;
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"x\n");
						equipArmor(&pData,currentRoom->roomArmor);
						pData.pArmor=currentRoom->roomArmor;
						Py++;
					}
					else if(checkForWeap(box,Px,tempY+1))
					{
						currentRoom->roomCode-=2000000;
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"x\n");
						equipWeap(&pData,currentRoom->roomWeapon);
						pData.pWeapon=currentRoom->roomWeapon;
						Py++;
					}
					else if(checkForTreasure(box,Px,tempY+1))
					{
						currentRoom->roomCode-=20000000;
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"x\n");
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
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"d\n");	
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
							fprintf(tempMap,"%d\n",currentRoom->roomCode);
							fprintf(tempDir,"x\n");
							pData.pExp++;
							totalEnem++;
						}
					}
					else if(checkForArmor(box,Px,tempY-1))
					{
						currentRoom->roomCode-=200000;
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"x\n");
						equipArmor(&pData,currentRoom->roomArmor);
						pData.pArmor=currentRoom->roomArmor;
						Py--;
					}
					else if(checkForWeap(box,Px,tempY-1))
					{
						currentRoom->roomCode-=2000000;
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"x\n");
						equipWeap(&pData,currentRoom->roomWeapon);
						pData.pWeapon=currentRoom->roomWeapon;
						Py--;
					}
					else if(checkForTreasure(box,Px,tempY-1))
					{
						currentRoom->roomCode-=20000000;
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"x\n");
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
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"a\n");	
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
							fprintf(tempMap,"%d\n",currentRoom->roomCode);
							fprintf(tempDir,"x\n");
							pData.pExp++;
							totalEnem++;
						}
					}
					else if(checkForArmor(box,tempX+1,Py))
					{
						currentRoom->roomCode-=200000;
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"x\n");
						equipArmor(&pData,currentRoom->roomArmor);
						pData.pArmor=currentRoom->roomArmor;
						Px++;
					}
					else if(checkForWeap(box,tempX+1,Py))
					{
						currentRoom->roomCode-=2000000;
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"x\n");
						equipWeap(&pData,currentRoom->roomWeapon);
						pData.pWeapon=currentRoom->roomWeapon;
						Px++;
					}
					else if(checkForTreasure(box,tempX+1,Py))
					{
						currentRoom->roomCode-=20000000;
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"x\n");
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
							totalRooms++;
						}
						Px=0;
						Py=roomSize/2;
						fprintf(tempMap,"%d\n",currentRoom->roomCode);
						fprintf(tempDir,"s\n");	
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
		
	}while(move!='Y'&&move!='y'&&pData.pHP>0&&totalRooms!=roomLimit);
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
	else printf("Goodbye.");
}
