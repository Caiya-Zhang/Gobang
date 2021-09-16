
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define row 10   
#define col 10   

#define BLANK ' '//32   
#define PL1   'O'//79  
#define PL2   'X'//88  


void init_board(int a[row][col]);
void output_board (int a[row][col]);
void setup_game(int* this_player,int* game_finished);

void this_player_makes_move (int a[row][col],int* this_player,int* game_finished);
int check_row_col_valid(int a[row][col],int validrow,int validcol);
void player_choose_row_col(int a[row][col],int* this_player,int* validrow,int* validcol);

int check_for_full_board(int a[row][col]);
int check_this_player_has_won(int a[row][col],int* this_player, int validrow,int validcol);
int check_row_has_won(int a[row][col],int* this_player,int validrow,int validcol);
int check_col_has_won(int a[row][col],int* this_player,int validrow,int validcol);
int check_main_diagonal_has_won(int a[row][col],int* this_player,int validrow,int validcol);
int check_Paradiagonal_has_won(int a[row][col],int* this_player,int validrow,int validcol);


void swap_this_player(int* this_player);

int main(int argc, char const *argv[])
{
    int board[row][col];   
    int this_player = 0;    
    int game_finished = 0;  

    init_board(board);   
    setup_game(&this_player,&game_finished);  
    output_board(board); 
    while(!game_finished)  
    {
        this_player_makes_move(board,&this_player,&game_finished);   
        swap_this_player(&this_player);  
    }
}

/**
 * init_board      
 * @version  1.0    
 * @param    a    
 */
void init_board(int a[row][col])
{
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
        {
            a[i][j]=BLANK;
        }
}

/**
 * setup_game
 * @version  1.0
 * @param    this_player          
 * @param    game_finished        
 */
void setup_game(int* this_player,int* game_finished)
{
    *this_player=0;
    *game_finished=0;
}

/**
 * output_board
 * @version  1.0
 * @param    a         
 */
void output_board (int a[row][col])
{
    //printf("*1*2*3*4*5*6*7*\n");
    //system("clear");   
    system("cls");
    for(int i=0;i<col;i++)printf("*%d",i);
    printf("**\n");
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            printf("*");
            printf("%c",a[i][j]);
        }
        printf("*%d\n",i);
        //
    }
    //printf("***************\n");
    for(int i=0;i<col;i++)printf("**");
    printf("*\n");
    
}

/**
 * swap the player
 * @version  1.0
 * @param    this_player   
 */
void swap_this_player(int* this_player)
{
    *this_player=*this_player==0?1:0;
}

/**
 * check_for_full_board
 * @version  1.0
 * @param    a                        
 * @return                            
 */
int check_for_full_board(int a[row][col])
{
    int blankfound = 0;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            if(a[i][j]==BLANK)
            {
                blankfound = 1;
                break;
            }
        }
    }
    return blankfound;
}

/**
 * this_player_makes_move
 * @version  1.0
 * @param    a                        
 * @param    this_player              
 * @param    game_finished            
 */
void this_player_makes_move (int a[row][col],int* this_player,int* game_finished)
{
    int validcol=0,validrow=0;  
    if(check_for_full_board(a)){  
        
        player_choose_row_col(a,this_player,&validrow,&validcol); 
        
        a[validrow][validcol] = *this_player==0?PL1:PL2; 

        output_board(a); 
        
        if(check_this_player_has_won(a,this_player,validrow,validcol))
        {
            *game_finished=1;
            printf("��ϲ���%dӮ�ˣ���\n",*this_player+1);
        }
    }
    else {   
        printf("û�п��Եط��������ӣ���Ϸ������\n");
        *game_finished = 1;
    }
}

/**
 * player_choose_row_col
 * @version  1.0
 * @param    a                        
 * @param    this_player              
 * @param    validrow                 
 * @param    validcol                 
 */
void player_choose_row_col(int a[row][col],int* this_player,int* validrow,int* validcol)
{
    printf("�����%d����Ҫѡ����к�(0-%d) �к�(0-%d)\n", *this_player+1,row-1,col-1);
    scanf("%d %d",validrow,validcol);
     
}

/**
 * check_row_col_valid
 * @version  1.0
 * @param    a                        
 * @param    validrow                 
 * @param    validcol                 
 * @return                            
 */
int check_row_col_valid(int a[row][col],int validrow,int validcol)
{
    int valid=0;
    if (validrow<0||validrow>=row||validcol<0||validcol>=col)
    {
    	valid=0;
    }
    else valid=a[validrow][validcol]==BLANK?1:0;
    return valid;
}

/**
 * check_this_player_has_won
 * @version  1.0
 * @param    a                        
 * @param    this_player              
 * @param    validrow                 
 * @param    validcol                 
 * @return                            
 */
int check_this_player_has_won(int a[row][col],int *this_player, int validrow,int validcol)
{
    int win=0;
    if (check_row_has_won(a,this_player,validrow,validcol)||
    	check_col_has_won(a,this_player,validrow,validcol)||
    	check_main_diagonal_has_won(a,this_player,validrow,validcol)||
    	check_Paradiagonal_has_won(a,this_player,validrow,validcol)
    	)
    {
    	win=1;
    }
    return win;
}

/**
 * check_row_has_won
 * @version  1.0
 * @param    a                 		  
 * @param    this_player              
 * @param    validrow                 
 * @param    validcol                 
 * @return                            
 */
int check_row_has_won(int a[row][col],int* this_player,int validrow,int validcol)
{
	int win=0;
    return win;
}

/**
 * check_col_has_won
 * @version  1.0
 * @param    a                 		  
 * @param    this_player              
 * @param    validrow                 
 * @param    validcol                 
 * @return                            
 */
int check_col_has_won(int a[row][col],int* this_player,int validrow,int validcol)
{
	int win=0;
    
	return win;
}

/**
 * check_main_diagonal_has_won
 * @version  1.0
 * @param    a                 		  
 * @param    this_player              
 * @param    validrow                 
 * @param    validcol                 
 * @return                            
 */
int check_main_diagonal_has_won(int a[row][col],int* this_player,int validrow,int validcol)
{
	int win=0;
    
	return win;
}

/**
 * check_Paradiagonal_has_won
 * @version  1.0
 * @param    a                 		  
 * @param    this_player              
 * @param    validrow                 
 * @param    validcol                 
 * @return                            
 */
int check_Paradiagonal_has_won(int a[row][col],int* this_player,int validrow,int validcol)
{
	int win=0;
   
	return win;
}
