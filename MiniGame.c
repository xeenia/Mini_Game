s

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


char commands(int **, int, int, int); 
void ham(int **, int, int, int, int, int); 
void bomb(int **, int , int , int , int );
void add(void);                        
void mov(int **, char, int, int);
void dashboard_print(int **, int, int, int); 
void dashboard_break(int **, int, int);
int score(int);
int check(int **, int, int);
void rules(void);
void co(int);
void exitt(void);
void win(void);


int level=1, lol=0, bonus=0; 
int max_col=-1,row_max=-1,min_row=-1,min_col=-1;


#define max 15
#define min 10
#define max_size 15

#define red printf("\033[1;31m")
#define white printf("\033[1;37m")
#define green printf("\033[1;32m")
#define yellow printf("\033[1;33m")
#define blue printf("\033[1;34m")
#define magenta printf("\033[1;35m")
#define cyan printf("\033[1;36m")
#define dark_gray printf("\033[1;30m")
#define gray printf("\033[1;29m")
#define uncolor printf("\033[0m")

#define re printf("\e[1;1H\e[2J")

int main(void)
{

	int end, grammh, sthlh, col, i, j, flag=0;
	int **colors;
	srand(time(0));
	re;
	white;
	printf("\n\n\t\t\t\t       %s\n\t\t\t\t%s\n\n", "WELCOME TO DEMOLITION MAN", "THE BEST GAME FOR CHILDREN AND ADULTS! :)");
	printf("\n\n\tYou are free to make your size that you want but don't exceed the permissible limits :D\n\tAllowed limts:\n\tMIN: %d  MAX: %d\n\n", min, max);
	do
	{
		if(flag++==0)
		{
			printf("\tRow: ");
			scanf("%d", &grammh);
			printf("\tColumn: ");
			scanf("%d", &sthlh);
		}
		else
		{
			printf("\tHeyy!! Don't exceed the allowed limits:(\n");
			printf("\tRow: ");
			scanf("%d", &grammh);
			printf("\tColumn: ");
			scanf("%d", &sthlh);
		}
	}while((grammh<min||grammh>max)||(sthlh<min||sthlh>max));
	flag=0;
	do
	{
		if(flag++!=0)
		{
			printf("Heyy!! Don't exceed the allowed limits:(\n");
			printf("Colors: ");
			scanf("%d", &col);
		}
		else
		{
			printf("\tNow choose with how many colors between [4,9]: ");
			scanf("%d", &col);
		}
	}while(col<4||col>9);
	do
	{
		colors=(int**)malloc(grammh*sizeof(int*));
		if(colors==NULL)
		{
			printf("Oh, out of memory!!");
			return 0;
		}
		for(i=0; i<grammh; i++)
		{
			*(colors+i)=(int*)malloc(sthlh*sizeof(int));
			if((colors+i)==NULL)
			{
				printf("Out of memory\n");
				return 0;
			}
		}
		for(i=0; i<grammh; i++)
			for(j=0; j<sthlh; j++)
				*(*(colors+i)+j)=1+rand()%col;
		if(lol==0)
			lol=max_size/2+1;
		uncolor;
		dashboard_print(colors, grammh, sthlh, col);
		for(i=0; i<grammh; i++)
			free(colors[i]);
		free(colors);
		sthlh++;
		grammh++;
		level++;
		if(level%2!=0)
			lol--;
	}while(level!=max_size+1);
	re;
	win();
	return 0;
}
void dashboard_print(int **colors, int row_dimension, int column_dimension, int col)
{
	int i, j, jj;
	static int for_last_level=1, dashboard_row_max, dashboard_col_max;

	do
	{	
		if(for_last_level==1)
		{
			dashboard_row_max=row_dimension+max_size+1;
			dashboard_col_max=column_dimension+max_size+2;
			for_last_level=2;
		}
		re;
		white;
		printf("\n\n");


		for(i=0; i<dashboard_col_max/2; i++)
			printf((i!=dashboard_col_max/2-1)?"   ":"  %s%d\n", "Level ", level);
		printf("  ");
		for(i=0; i<dashboard_col_max; i++)
			printf((i!=dashboard_col_max-1)?"---":"----\n");
	   uncolor;
		for(i=0; i<dashboard_row_max; i++)
		{
			printf("  ");
			if(i==lol)
			{
				for( jj=0; jj<dashboard_col_max; jj++)
				{
					if(jj==lol)
					{
						printf(" ");
						red;
						printf("## ");
					   uncolor;
					}
					if(jj>=lol&&jj<=lol+column_dimension-1)
						{
							red;
							printf((jj+1-lol<10)?"0%d ":"%d ", jj+1-lol);
							uncolor;
						}
					else
					{
						red;
						printf((jj==dashboard_col_max-1)?"\n":"███");
						uncolor;
					}
				}	
				printf("  ");
			}
			if(i>=lol&&i<=lol+row_dimension-1)
			{
				for(j=0; j<dashboard_col_max; j++)
				{
					
					if(j==lol) 
					{
							printf(" ");
							red;
							printf((i+1-lol<10)?"0%d":"%d", i+1-lol);
					}
					uncolor;
					if(j>=lol&&j<=lol+column_dimension-1)
					{
						if(j==lol)
							printf("  "); 
						if(colors[i-lol][j-lol]==0)
							printf((j-lol!=column_dimension-1)?"%c  ":"%c ", '.');
						else
						{
							co(colors[i-lol][j-lol]);
							printf((j-lol!=column_dimension-1)?"%d  ":"%d ", colors[i-lol][j-lol]);
							uncolor;
						}
					}
					else
					{
						red;
						printf((j!=dashboard_col_max-1)?"███":"\n");
						uncolor;
					}
				}
			}
			else
			{
				red;
				for(j=0; j<dashboard_col_max; j++)
					printf((j!=dashboard_col_max-1)?"███":"████\n"); 
				uncolor;
			}
		}
		red;
		printf("\n\n  Commands: ");
		white;
		printf("h for Hammer ");
		printf("\t\tb for Bomb ");
		printf("\t\t ex. a 4,5 6\n");
		printf("\t    a for add ");
		printf("\t\t\tpl for push left ");
		printf("\t ex. h 4,7\n");
		printf("\t    pr for push right");
		printf("\t\tx for exit ");
		printf("\t\t s for skip\n\n");
		white;
		printf("\n\n  Score %d\n\n\n", score(bonus));
		printf("  Shall I wait more? Make your move: ");
	}while(1!=check(colors, row_dimension, column_dimension)&&'s'!=commands(colors, row_dimension, column_dimension, col));
}

char commands(int **colors, int row_dimension, int column_dimension, int commanders_col) 
{
	char com, com2='a';
	int commander_row=1, commander_column=1, col, k=0, colr, truee=1;
	int i,j,temp;
	static int tries=0;


	do
	{
		if(k++!=0)
			printf("\n\n  Heyy, you made a mistake. Correct it :D\n  I choose: ");
		getchar();
		scanf("%c", &com);
		if(com=='x'||com=='s')
		{
			
			truee=0;
			printf("%d\n", truee);
		}
		else if(com=='a')
		{
			scanf(" %d,%d %d", &commander_row, &commander_column, &colr);
			truee=(commander_row<1||commander_row>row_dimension)||(commander_column<1||commander_column>column_dimension);
			if(!truee)
				if(colors[commander_row-1][commander_column-1]!=0)
						truee=1;
			truee+=(colr<1)||(colr>commanders_col);
		}
		else if(com=='h'||com=='b')
		{
			scanf(" %d,%d", &commander_row, &commander_column);
			truee=(commander_row<1||commander_row>row_dimension)||(commander_column<1||commander_column>column_dimension);
		}
		else if(com=='p')
		{
			scanf("%c", &com2);
			truee=!(com2=='r'||com2=='l');
		} 
		else
			truee=1;
	}while(truee); 
	if(com=='x')
	{
		exitt();
		white;
		printf("\n\n\t\t\t\t\t ~~Oh, why are you leaving us?~~\n\n\n\n");
		exit(0);
	}
	else if(com=='s')
		return 's';
	if(com=='h')
	{
		bonus=0;
		col=colors[commander_row-1][commander_column-1];
		max_col=row_max=min_row=min_col=-1;
		ham(colors, commander_row-1, commander_column-1, col, row_dimension, column_dimension); 
	}
	else if(com=='b')
		bomb(colors, commander_row-1, commander_column-1, row_dimension, column_dimension); 
	else if(com=='a')
	{
		if(colors[commander_row-1][commander_column-1]==0)
		{
			colors[commander_row-1][commander_column-1]=colr;
			for(j=0; j<row_dimension; j++)
				if(colors[j][commander_column-1]==0)
					for(i=j; i>0; i--)
					{
						temp=colors[i][commander_column-1];
						colors[i][commander_column-1]=colors[i-1][commander_column-1];
						colors[i-1][commander_column-1]=temp;
					}
		}
	}
	else if(com=='p') // PROSOXH SEGMETASION FAULT
		mov(colors, com2, row_dimension, column_dimension);
}
void ham(int **colors, int row, int column, int col, int row_dimension, int column_dimension) //check
{
	if(row_max==-1)
		row_max=row;
	else if(row_max<row)
		row_max=row;
		
	if(min_row==-1)
		min_row=row;
	else if(min_row>row)
		min_row=row;


	if(max_col==-1)
		max_col=column;
	else if(max_col<column)
		max_col=column;

	if(min_col==-1)
		min_col=column;
	else if(min_col>column)
		min_col=column;

	if(row<row_dimension-1)
		if(colors[row+1][column]==col)
		{
			colors[row+1][column]=0;
			bonus++;
			ham(colors, row+1, column, col, row_dimension, column_dimension);
		}
	if(row>0)
		if(colors[row-1][column]==col)
		{
			
			colors[row-1][column]=0;
			bonus++;
			ham(colors, row-1, column, col, row_dimension, column_dimension);
		}
   if(column<column_dimension-1)
		if(colors[row][column+1]==col)
		{
			colors[row][column+1]=0;
			bonus++;
			ham(colors, row, column+1, col, row_dimension, column_dimension);
		}
	if(column>0)
		if(colors[row][column-1]==col)
		{
			colors[row][column-1]=0;
			bonus++;
			ham(colors, row, column-1, col, row_dimension, column_dimension);
		}
	dashboard_break(colors, row_dimension, column_dimension);
}
void bomb(int **colors, int commander_row, int commander_column, int row, int column)
{
	int i,j;

	if(commander_row==row-1)
		row_max=commander_row;
	else 
		row_max=commander_row+1;
	if(commander_row==0)
		min_row=commander_row;
	else
		min_row=commander_row-1;
	if(commander_column==0)	
		min_col=commander_column;
	else
		min_col=commander_column-1;
	if(commander_column==column-1)
		max_col=commander_column;
	else
		max_col=commander_column+1;

	for(i=min_row; i<=row_max; i++)
		for(j=min_col; j<=max_col; j++)
			colors[i][j]=0;
	dashboard_break(colors, commander_row, commander_column);
}
void mov(int **colors, char com, int grammes, int sthles) 
{
	int i, j, jj;
	if(com=='l')
	{
		for(j=0; j<sthles; j++)
			if(colors[grammes-1][j]==0)
				for(jj=j; jj<sthles; jj++)
				{
					if(colors[grammes-1][jj]!=0)
						for(i=0; i<grammes; i++)
							if(colors[i][jj]!=0)
							{
								colors[i][j]=colors[i][jj];
								colors[i][jj]=0;
							}
					if(colors[grammes-1][j]!=0) //check
						break;
				}
	}		
	else
	{
		for(j=sthles-1; j>-1; j--)
		{
			if(colors[grammes-1][j]==0)
				for(jj=j; jj>-1; jj--)
				{
					if(colors[grammes-1][jj]!=0)
						for(i=0; i<grammes; i++)
							if(colors[i][jj]!=0)
							{
								colors[i][j]=colors[i][jj];
								colors[i][jj]=0;
							}
					if(colors[grammes-1][j]!=0)	
						break;
				}
		}
	}
	dashboard_break(colors, grammes, sthles);	
}
void dashboard_break(int **colors, int row, int column)
{
	int i, j, ii, temp;
	for(j=min_col; j<=max_col; j++)
		for(i=min_row; i<=row_max; i++)
			if(colors[i][j]==0)
				for(ii=i; ii>0; ii--)
				{
					temp=colors[ii][j];
					colors[ii][j]=colors[ii-1][j];
					colors[ii-1][j]=temp;
		   	}
}
int score(int bonus)
{   
	static int sc=0;                                  

	if(bonus>3&&bonus<13)
		sc+=bonus*7;
	else if(bonus>0&&bonus<3)
		;
	else if(bonus!=0)
	{
		red;
		printf("  You got extra bonus!! ;)\n\n");
		sc+=bonus*7+100;
	}
	red;
	if(bonus!=0)
		printf("\n\n  WOW! Congrats you broke %d blocks\n\n", bonus);
	return sc;
}
int check(int **colors, int grammes, int sthles)
{
	int i, j;
	for(i=0; i<grammes; i++)
		for(j=0; j<sthles; j++)
			if(colors[i][j]!=0)
				return 0;
	return 1;
}
void co(int c)
{
	if(c==1)
		green;
	else if(c==2)
		yellow;
	else if(c==3)
		blue;
	else if(c==4)
		magenta;
	else if(c==5)
		cyan;
	else if(c==6)
		white;
	else if(c==7)
		red;
	else if(c==8)
		dark_gray;
	else if(c==9)
		gray;                     
}
void exitt(void)
{
	re;
	yellow;
	printf("\n\n"); 
	printf("\t\t\t                           ░            \n");
   printf("\t\t\t                       ▞░   ▞    ░     \n");
   printf("\t\t\t                    ░▚  ░░▒▒▒░░▞      \n");
	printf("\t\t\t                       ▚░▒▓▓▓▒░    ▞░        \n"); 
	printf("\t\t\t                   ▚    ░▒▓███▒░ ░ ▞        \n");
	printf("\t\t\t                   ░ ▞   ░░░███░        \n");
   printf("\t\t\t                         ▞    ████\n");
   printf("\t\t\t                               ████\n");
   printf("\t\t\t                                ████\n");
   printf("\t\t\t                                 ████\n");
   printf("\t\t\t                                 ████                     \n");
   printf("\t\t\t                       ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n");
   printf("\t\t\t                       ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒\n");
	printf("\t\t\t                    00000000000000000000000000000\n");
	printf("\t\t\t                0000000000000000000000000000000000000\n");
	printf("\t\t\t            000000000000000000000000000000000000000000000\n");
   printf("\t\t\t        00000000000000000000000000000000000000000000000000000\n");
	printf("\t\t\t      000000000000000000000000000000000000000000000000000000000\n");
	printf("\t\t\t     00000000000000000000000000000000000000000000000000000000000\n");
	printf("\t\t\t    0000000000000000000000000000000000000000000000000000000000000\n");
   printf("\t\t\t    0000000000000000000000000000000000000000000000000000000000000\n");
	printf("\t\t\t    0000000000        0000000000000000000000        0000000000000\n");
	printf("\t\t\t    000000000          00000000000000000000          000000000000\n");
	printf("\t\t\t    00000000            000000000000000000            00000000000\n");
   printf("\t\t\t    0000000              0000000000000000              0000000000\n");
	printf("\t\t\t    00000000            000000000000000000            00000000000\n");
	printf("\t\t\t    000000000          00000000000000000000          000000000000\n");
	printf("\t\t\t    0000000000        0000000000000000000000        0000000000000\n");
   printf("\t\t\t    0000000000000000000000000000000000000000000000000000000000000\n");
  	printf("\t\t\t     00000000000000000000000000000000000000000000000000000000000\n");
   printf("\t\t\t      00000000000000                             00000000000000\n");
	printf("\t\t\t       000000000000      0000000000000000000      000000000000\n");
	printf("\t\t\t        0000000000      000000000000000000000      0000000000\n");
	printf("\t\t\t          00000000000000000000000000000000000000000000000000\n");
	printf("\t\t\t            0000000000000000000000000000000000000000000000\n");
	printf("\t\t\t             0000000000000000000000000000000000000000000\n");
	printf("\t\t\t               000000000000000000000000000000000000000\n");
	printf("\t\t\t                 00000000000000000000000000000000000\n");
	printf("\t\t\t                     000000000000000000000000000\n");
	printf("\t\t\t                         0000000000000000000\n");
	printf("\t\t\t                             00000000000\n");
}
void win(void)
{
  white;       printf("\n\n");                                                                                                 
	printf("\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░                                                ░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░                                                ░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░               YOUR TOTAL SCORE IS              ░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░                                                ░░░░░░░░░░░░░░░░░░\n");
   printf("\t\t░░░░░░░░░░░░░░░░                         %d                      ░░░░░░░░░░░░░░░░░░\n", score(bonus));
	printf("\t\t░░░░░░░░░░░░░░░░                                                ░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░                                                ░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░                                                ░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("\t\t░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░░\n");
	printf("\n\n\n");
	uncolor;
}


	




































































