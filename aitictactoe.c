#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define COMPUTER 1
#define HUMAN 2

#define COMPMOVE 'O'
#define HUMANMOVE 'X'

typedef struct move
{
	int row;
	int col;
}Move;

void showboard(char board[3][3])
{
	printf("\n\n");

    printf("\t\t\t  %c | %c  | %c  \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t  %c | %c  | %c  \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t--------------\n");
    printf("\t\t\t  %c | %c  | %c  \n\n", board[2][0], board[2][1], board[2][2]);

}

void showinstructions()
{
	printf("\t\tA GAME OF TIC TAC TOE!!\n\n");
	printf("The board is as shown:\n");
	printf("\t\t\t  1 | 2  | 3  \n");
    printf("\t\t\t--------------\n");
	printf("\t\t\t  4 | 5  | 6  \n");
	printf("\t\t\t--------------\n");
    printf("\t\t\t  7 | 8  | 9  \n\n");
    printf("Pick the number of the cell to play that move!\n");
}

void init_board(char board[3][3])
{
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			board[i][j] = '_';
		}
	}
}

//checking conditions for win
int evAL(char board[3][3])
{
	// Checking for Rows for X or O victory.
    for (int row = 0; row<3; row++)
    {
        if (board[row][0]==board[row][1] && board[row][1]==board[row][2])
        {
            if (board[row][0]==COMPMOVE)
                return +10;
            else if (board[row][0]==HUMANMOVE)
                return -10;
        }
    }

    // Checking for Columns for X or O victory.
    for (int col = 0; col<3; col++)
    {
        if (board[0][col]==board[1][col] && board[1][col]==board[2][col])
        {
            if (board[0][col]==COMPMOVE)
                return +10;

            else if (board[0][col]==HUMANMOVE)
                return -10;
        }
    }

    // Checking for Diagonals for X or O victory.
    if (board[0][0]==board[1][1] && board[1][1]==board[2][2])
    {
        if (board[0][0]==COMPMOVE)
            return +10;
        else if (board[0][0]==HUMANMOVE)
            return -10;
    }

    if (board[0][2]==board[1][1] && board[1][1]==board[2][0])
    {
        if (board[0][2]==COMPMOVE)
            return +10;
        else if (board[0][2]==HUMANMOVE)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}

int isWinner(char board[3][3], char let)
{
	int x = evAL(board);
	if(x == 10 && let == COMPMOVE)
		return 1;
	else if(x == 10 && let == HUMANMOVE)
		return 0;
	if(x == -10 && let == COMPMOVE)
		return 0;
	else if(x == -10 && let == HUMANMOVE)
		return 1;
}
int isBoardFull(char board[3][3])
{
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(board[i][j] == '_')
				return 0;
		}
	}
	return 1;
}

int isBoardEmpty(char board[3][3])
{
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(board[i][j] == HUMANMOVE || board[i][j] == COMPMOVE)
				return 0;
		}
	}
	return 1;	//board is empty
}


int spaceIsFree(char board[3][3], int i, int j)
{
    return (board[i][j] == '_');
}


int minimax(char board[3][3], int isMax)
{
	int score = evAL(board);
	if(score == 10)
		return score;

	if(score == -10)
		return score;

	if (isBoardFull(board)==1)
		return 0;

	if (isMax == 1) {
		//printf("in ai\n");
        int best = -1000;

        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]=='_')
                {
                    // Make the move
                    board[i][j] = COMPMOVE;
                    // Calling minimax recursively and choose the maximum value
                    best = fmax(best, minimax(board, 0) );

                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }

    // If this minimizer's move
    else
    {
    	//printf("In human\n");
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if cell is empty
                if (board[i][j]=='_')
                {
                    // Make the move
                    board[i][j] = HUMANMOVE;
                    // Call minimax recursively and chooses the minimum value
                    best = fmin(best, minimax(board, 1));

                    // Undo the move
                    board[i][j] = '_';
                }
            }
        }
		return best;
    }
}
Move findBestMove(char board[3][3])
{
	int bestVal = -1000;
    Move bestMove;

    //initialising the bestmove
    bestMove.row = -1;
    bestMove.col = -1;

    for(int i=0; i<3; i++){
    	for(int j=0; j<3; j++){
    		if(board[i][j] == '_'){
    			//selecting a empty cell
    			board[i][j] = COMPMOVE;

    			//applying the minimax func to this move
    			int moveVal = minimax(board, 0);
    			//undo the move
    			board[i][j] = '_';

    			if(moveVal > bestVal){
    				bestMove.row = i;
    				bestMove.col = j;
    				bestVal = moveVal;
    			}
    		}
    	}
    }
    return bestMove;
}

void playerMove(char board[3][3])
{
    while(1){
		int move;
        printf("Please select a position to place an \'%c\'' (1-9): ", HUMANMOVE);
        scanf("%d", &move);
        move -= 1;	//for index
        int i = move/3;
        int j = move % 3;
        if(move >= 0 && move < 9){
            if (spaceIsFree(board, i, j)){
                board[i][j] = HUMANMOVE;
            	break;
            }
            else
                printf("Sorry, this space is occupied!");
        }
        else
            printf("Please type a number within the range!");
        }
}

int compMove(char board[3][3])
{
	Move bestMove = findBestMove(board);
	return (bestMove.row*3 + bestMove.col);
}

int main()
{
	char board[3][3];
	init_board(board);
    showinstructions();
    showboard(board);

    while(!(isBoardFull(board)))
    {
        if (!(isWinner(board, 'O'))){
            playerMove(board);
        }
        else{
            printf("Sorry, O\'s won this time!");
            break;
        }
        if (!(isWinner(board, 'X'))){
            int move = compMove(board);
			printf("Computer placed an \'%c\'", COMPMOVE);
            int i = move/3;
    		int j = move % 3;
            board[i][j] = COMPMOVE;
            system("clear"); system("CLS"); //the former is for linux systems while the latter is windows.
	        showboard(board);
        }
        else{
            printf("X\'s won this time! Good Job!");
            break;
        }
    }
    if(isBoardFull(board))
        printf("Tie Game!");

    return 0;
}
