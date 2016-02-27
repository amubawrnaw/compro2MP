#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define player 'P'
#define TRUE 1
#define FALSE 0

// [hospos = row, vertpos = column]

int inputcheck(char moveinput)
{
    if(moveinput=='a'||moveinput=='w'||moveinput=='s'||moveinput=='d')
     return 1;
    else
     return 0;
}

void printmap(char room[][sizeroom],int sizeroom)
{
  int i,j;
     
     for(i=0; i<sizeroom; i++)
       {
       for(j=0; j<sizeroom; j++)
         printf("%c",room[i][j]);
       printf("\n");
       }
}

void changepos(char room[][sizeroom], char moveinput, int hospos, int vertpos, int sizeroom)
{
       room[hospos][vertpos]=' ';
     
     switch(moveinput)
     {
      case 'w': if(hospos!=0)
                 hospos--;
                break;
                
      case 'a': if(vertpos!=0)
                 vertpos--;
                break;
                
      case 's': if(hospos!=sizeroom-1)
                 hospos++;
                break;
                
      case 'd': if(vertpos!=sizeroom-1)
                 vertpos++;
                break;
                
      default:  break;                
     }
     
     room[hospos][vertpos]=player;
}


int main()
{
    
    int i,j,canmove;
    char moveinput;
    int sizeroom;
    
    printf("How large will our room be?");
    scanf("%d",&sizeroom);
    
    char room[sizeroom][sizeroom];
    
    for(i=0; i<sizeroom; i++)
     for(j=0; j<sizeroom; j++)
      room[i][j]='.';
    
    int hospos=sizeroom/2;
    int vertpos=sizeroom/2;
    
    room[hospos][vertpos]=player;
    
    do
    {
      do
      {
        printf("Please enter input:");
        scanf("%c",&moveinput);
        canmove=inputcheck(moveinput);               
      }
      while(canmove=FALSE);
     system("cls");
     changepos(room,moveinput,hospos,vertpos,sizeroom);
     printmap(room,sizeroom);
    }  
    while(1);
    
    getch();
    return 0;
}
