#include <stdio.h>
#include <Windows.h>
#include <conio.h>

#define BOARDSIZE 3

// As we talked, can these be dynamic?
// Think scalability, what if the code gets larger? How can we organize this code better?

void PrintBoard(CHAR inarrBoard[BOARDSIZE][BOARDSIZE]) {
  //Why declare variables inside a loop? Does it matter?
	for (INT iRow = 0; iRow < BOARDSIZE; iRow++) {
		for (INT iColumn = 0; iColumn < BOARDSIZE; iColumn++) {
			printf_s(" %c |", inarrBoard[iRow][iColumn]);
		}
		printf_s("\n");
		for (INT iPrintCount = 0; iPrintCount < BOARDSIZE; iPrintCount++) {
			printf_s("---+");
		}
		printf_s("\n");
	}
}

BOOL CheckWin(CHAR inarrBoardContents[BOARDSIZE][BOARDSIZE]) {
// This function is not very readable, make this function better oriented
  // Also, keep the standard on variable declaration
  
	// Checks row wins
	for (INT iRow = 0; iRow < BOARDSIZE; iRow++) {
		BOOL bXWin = TRUE;
		BOOL bOWin = TRUE;
		for (INT iColumn = 0; iColumn < BOARDSIZE; iColumn++) {
			if (inarrBoardContents[iRow][iColumn] != 'X' && bXWin == TRUE) {
				bXWin = FALSE;
			}
			if (inarrBoardContents[iRow][iColumn] != 'O' && bOWin == TRUE) {
				bOWin = FALSE;
			}
		}
		if (bXWin == TRUE || bOWin == TRUE) {
			return 1;
		}
	}

	// Checks column wins
	for (INT iColumn = 0; iColumn < BOARDSIZE; iColumn++) {
		BOOL bXWin = TRUE;
		BOOL bOWin = TRUE;
		for (INT iRow = 0; iRow < BOARDSIZE; iRow++) {
			if (inarrBoardContents[iRow][iColumn] != 'X' && bXWin == TRUE) {
				bXWin = FALSE;
			}
			if (inarrBoardContents[iRow][iColumn] != 'O' && bOWin == TRUE) {
				bOWin = FALSE;
			}
		}
		if (bXWin == TRUE || bOWin == TRUE) {
			return 1;
		}
	}

	// Check main diagonal wins
	INT iXCountMain = 0;
	INT iOCountMain = 0;
	for (INT iColumn = 0; iColumn < BOARDSIZE; iColumn++) {

		if (inarrBoardContents[iColumn][iColumn] == 'X') {
			iXCountMain++;
		}
		if (inarrBoardContents[iColumn][iColumn] == 'O') {
			iOCountMain++;
		}
		if (iXCountMain == BOARDSIZE || iOCountMain == BOARDSIZE) {
			return 1;
		}
	}

	// Check secondary diagonal wins
	INT iXCountSec = 0;
	INT iOCountSec = 0;
	for (INT iColumn = 0; iColumn < BOARDSIZE; iColumn++) {

		if (inarrBoardContents[iColumn][(BOARDSIZE - 1) - iColumn] == 'X') {
			iXCountSec++;
		}
    // Can this be more efficient?
		if (inarrBoardContents[iColumn][(BOARDSIZE - 1) - iColumn] == 'O') {
			iOCountSec++;
		}
		if (iXCountSec == BOARDSIZE || iOCountSec == BOARDSIZE) {
			return 1;
		}
	}

	return FALSE;
}


INT main() {

// change the order of the declaration
// Answer me in person - where are all these variables allocated?
  
	BOOL bNextPlayer;
	INT iChosenSquare;
	INT iTurnsPlayed;

	bNextPlayer = 0;
	iTurnsPlayed = 0;
	CHAR arrBoardContents[BOARDSIZE][BOARDSIZE];

  // Should be separated? 
	// Initializing Board
	for (INT iRow = 0; iRow < BOARDSIZE; iRow++) {
		for (INT iColumn = 0; iColumn < BOARDSIZE; iColumn++) {
			arrBoardContents[iRow][iColumn] = '.';
		}
	}


	while (CheckWin(arrBoardContents) == FALSE && iTurnsPlayed < BOARDSIZE*BOARDSIZE) {
 // I would like to know whose turn it is and print who wins at the end of the game.
		PrintBoard(arrBoardContents);

		printf("\nChoose a square number between 1 and %d: ",BOARDSIZE*BOARDSIZE);
		scanf_s("%d", &iChosenSquare);
		iChosenSquare--;

		if (iChosenSquare >= 0 && iChosenSquare < BOARDSIZE * BOARDSIZE) { 
			if (arrBoardContents[iChosenSquare / BOARDSIZE][iChosenSquare % BOARDSIZE] != 'X' &&
				arrBoardContents[iChosenSquare / BOARDSIZE][iChosenSquare % BOARDSIZE] != 'O') {
				if (bNextPlayer == 0) {
					arrBoardContents[iChosenSquare / BOARDSIZE][iChosenSquare % BOARDSIZE] = 'X';
					bNextPlayer = 1;
					iTurnsPlayed++;
				}
				else {
					arrBoardContents[iChosenSquare / BOARDSIZE][iChosenSquare % BOARDSIZE] = 'O';
					bNextPlayer = 0;
					iTurnsPlayed++;
				}
			}
			else
			{
				printf("\nThis square is already taken, cheater!");
			}
		}
		else
		{
			printf("\nNot a valid square, try again!");
			iChosenSquare = 0;
		}

	}
	return 0;
}
