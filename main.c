#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>


char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);
int findBestMove(char board[3][3]);
int minimax(char board[3][3],int depth, bool isMaximizing);


int main()
{
   char winner = ' ';
   char response = ' ';

      winner = ' ';
      response = ' ';
      resetBoard();

      while(winner == ' ' && checkFreeSpaces() != 0)
      {
         printBoard();

         playerMove();
         winner = checkWinner();
         if(winner != ' ' || checkFreeSpaces() == 0)
         {
            break;
         }

         computerMove();
         winner = checkWinner();
         if(winner != ' ' || checkFreeSpaces() == 0)
         {
            break;
         }
      }

      printBoard();
      printWinner(winner);


   return 0;
}

void resetBoard()
{
   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         board[i][j] = ' ';
      }
   }
}
void printBoard()
{
   printf(" %c | %c | %c ", board[0][0], board[0][1], board[0][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", board[1][0], board[1][1], board[1][2]);
   printf("\n---|---|---\n");
   printf(" %c | %c | %c ", board[2][0], board[2][1], board[2][2]);
   printf("\n");
}
int checkFreeSpaces()
{
   int freeSpaces = 9;

   for(int i = 0; i < 3; i++)
   {
      for(int j = 0; j < 3; j++)
      {
         if(board[i][j] != ' ')
         {
            freeSpaces--;
         }
      }
   }
   return freeSpaces;
}
void playerMove()
{
   int x;
   int y;

   do
   {
      printf("Enter row #(1-3): ");
      scanf("%d", &x);
      x--;
      printf("Enter column #(1-3): ");
      scanf("%d", &y);
      y--;

      if(board[x][y] != ' ')
      {
         printf("Invalid move!\n");
      }
      else
      {
         board[x][y] = PLAYER;
         break;
      }
   } while (board[x][y] != ' ');

}
void computerMove()
{
   srand(time(0));
   int x;
   int y;
   int bestMove = findBestMove(board);
   if(checkFreeSpaces() > 0)
   {
        x = bestMove / 3;
        y = bestMove % 3;
        while(board[x][y] != ' '){
            bestMove = findBestMove(board);
            x = bestMove / 3;
            y = bestMove % 3;
        }
        board[x][y] = COMPUTER;

   }
   else
   {
      printWinner(' ');
   }
}
char checkWinner()
{
   for(int i = 0; i < 3; i++)
   {
      if(board[i][0] == board[i][1] && board[i][0] == board[i][2])
      {
         return board[i][0];
      }
   }
   for(int i = 0; i < 3; i++)
   {
      if(board[0][i] == board[1][i] && board[0][i] == board[2][i])
      {
         return board[0][i];
      }
   }
   if(board[0][0] == board[1][1] && board[0][0] == board[2][2])
   {
      return board[0][0];
   }
   if(board[0][2] == board[1][1] && board[0][2] == board[2][0])
   {
      return board[0][2];
   }

   return ' ';
}
void printWinner(char winner)
{
   if(winner == PLAYER)
   {
      printf("YOU WIN!");
   }
   else if(winner == COMPUTER)
   {
      printf("YOU LOSE!");
   }
   else{
      printf("IT'S A TIE!");
   }
}


int findBestMove(char board[3][3]){
    int bestMove = -1;
    int bestScore = -1000;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == ' '){
                board[i][j] = COMPUTER;

                int score = minimax(board, 0, false);

                board[i][j] = ' ';

                if(score > bestScore){
                    bestScore = score;
                    bestMove = 3 * i + j;
                }
            }
        }
    }
    return bestMove;
}


int minimax(char board[3][3],int depth, bool isMaximizing){

    char winner = checkWinner();

    if(winner == COMPUTER){
        return 1;
    }
    else if (winner == PLAYER) {
        return -1;
    }
    else if (checkFreeSpaces() == 0){
        return 0;
    }


    if(isMaximizing){
        int bestScore = -1000;

        for(int i = 0; i<3;i++){
            for (int j =0; j<3;j++) {
                if(board[i][j] == ' '){
                    board[i][j] = COMPUTER;

                int score = minimax(board, depth+1,!isMaximizing);

                board[i][j] = ' ';

                bestScore = fmax(bestScore, score);
                }
            }
        }
        return bestScore;
    }
    else{
        int bestScore = -1000;

        for(int i =0; i<3;i++){
            for(int j = 0;j<3;j++){
                if(board[i][j] == ' '){
                    board[i][j] = PLAYER;

                    int score = minimax(board,depth+1,!isMaximizing);

                    board[i][j] = ' ';

                    bestScore = fmax(bestScore,score);
                }
            }
        }
        return bestScore;
    }
}

