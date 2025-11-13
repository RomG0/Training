#include <stdio.h>
#include <Windows.h>
#include <conio.h>

VOID PrintBoard(CHAR **inarrBoard,INT iniBoardSize) {

	for (INT iRow = 0; iRow < iniBoardSize; iRow++) {

		for (INT iColumn = 0; iColumn < iniBoardSize; iColumn++) {
			printf_s(" %c |", inarrBoard[iRow][iColumn]);
		}

		printf_s("\n");

		for (INT iPrintCount = 0; iPrintCount < iniBoardSize; iPrintCount++) {
			printf_s("---+");
		}

		printf_s("\n");

	}
}

INT CheckRowWin(CHAR **inarrBoardContents,INT iniBoardSize) {

	BOOL bXWin;
	BOOL bOWin;

	for (INT iRow = 0; iRow < iniBoardSize; iRow++) {

		bXWin = TRUE;
		bOWin = TRUE;

		for (INT iColumn = 0; iColumn < iniBoardSize; iColumn++) {

			if (inarrBoardContents[iRow][iColumn] != 'X' && bXWin == TRUE) {
				bXWin = FALSE;
			}

			if (inarrBoardContents[iRow][iColumn] != 'O' && bOWin == TRUE) {
				bOWin = FALSE;
			}
		}

		if (bXWin == TRUE) {
			return 1;
		}
		else if (bOWin == TRUE) {
			return 2;
		}
	}

	return 0;
}

INT CheckColumnWin(CHAR **inarrBoardContents, INT iniBoardSize) {

	BOOL bXWin;
	BOOL bOWin;

	for (INT iColumn = 0; iColumn < iniBoardSize; iColumn++) {

		bXWin = TRUE;
		bOWin = TRUE;

		for (INT iRow = 0; iRow < iniBoardSize; iRow++) {

			if (inarrBoardContents[iRow][iColumn] != 'X' && bXWin == TRUE) {
				bXWin = FALSE;
			}

			if (inarrBoardContents[iRow][iColumn] != 'O' && bOWin == TRUE) {
				bOWin = FALSE;
			}
		}

		if (bXWin == TRUE) {
			return 1;
		}
		else if (bOWin == TRUE) {
			return 2;
		}
	}

	return 0;
}

INT CheckMDiagonalWin(CHAR **inarrBoardContents, INT iniBoardSize) {

	INT iXCountMain;
	INT iOCountMain;

	iXCountMain = 0;
	iOCountMain = 0;

	for (INT iColumn = 0; iColumn < iniBoardSize; iColumn++) {

		if (inarrBoardContents[iColumn][iColumn] == 'X') {
			iXCountMain++;
		}

		if (inarrBoardContents[iColumn][iColumn] == 'O') {
			iOCountMain++;
		}
	}

	if (iXCountMain == iniBoardSize) {
		return 1;
	}

	else if (iOCountMain == iniBoardSize) {
		return 2;
	}

	return 0;
}

INT CheckSDiagonalWin(CHAR **inarrBoardContents, INT iniBoardSize) {

	INT iXCountMain;
	INT iOCountMain;

	iXCountMain = 0;
	iOCountMain = 0;

	for (INT iColumn = 0; iColumn < iniBoardSize; iColumn++) {

		if (inarrBoardContents[iColumn][(iniBoardSize - 1) - iColumn] == 'X') {
			iXCountMain++;
		}

		if (inarrBoardContents[iColumn][(iniBoardSize - 1) - iColumn] == 'O') {
			iOCountMain++;
		}
	}

	if (iXCountMain == iniBoardSize) {
		return 1;
	}

	else if (iOCountMain == iniBoardSize) {
		return 2;
	}

	return 0;
}

INT CheckWin(CHAR **inarrBoardContents, INT iniBoardSize) {
// not very efficient
	
	if (CheckRowWin(inarrBoardContents, iniBoardSize) == 1 || CheckColumnWin(inarrBoardContents, iniBoardSize) == 1 ||
		CheckMDiagonalWin(inarrBoardContents, iniBoardSize) == 1 || CheckSDiagonalWin(inarrBoardContents, iniBoardSize) == 1) {

		return 1;
	}
	else if (CheckRowWin(inarrBoardContents ,iniBoardSize) == 2 || CheckColumnWin(inarrBoardContents, iniBoardSize) == 2 ||
			CheckMDiagonalWin(inarrBoardContents, iniBoardSize) == 2 || CheckSDiagonalWin(inarrBoardContents, iniBoardSize) == 2) {

		return 2;
	}
	return 0;
}

INT FillSqaure(CHAR **inarrBoardContents, INT iniBoardSize, INT iniTurnsPlayed, BOOL *inbNextPlayer) {

	INT iStdinResult;
	INT iChosenSquare;
	INT iChosenSquareRow;
	INT iChosenSquareColumn;

	if (*inbNextPlayer == 0) {
		printf_s("X turn to play\n");
	}
	else
	{
		printf_s("O turn to play\n");
	}

	printf("\nChoose a square number between 1 and %d: ", iniBoardSize * iniBoardSize);
	iStdinResult = scanf_s("%d", &iChosenSquare);

	if (iStdinResult == 0) {
		while (getchar() != '\n');
	}

	iChosenSquare--;

	iChosenSquareRow = iChosenSquare / iniBoardSize;
	iChosenSquareColumn = iChosenSquare % iniBoardSize;

	if (iChosenSquare >= 0 && iChosenSquare < iniBoardSize * iniBoardSize) {

		// Check if square is free
		if (inarrBoardContents[iChosenSquare / iniBoardSize][iChosenSquare % iniBoardSize] == '.') {

			if (*inbNextPlayer == 0) {

				inarrBoardContents[iChosenSquare / iniBoardSize][iChosenSquare % iniBoardSize] = 'X';
				*inbNextPlayer = 1;
				iniTurnsPlayed++;
			}
			else {

				inarrBoardContents[iChosenSquare / iniBoardSize][iChosenSquare % iniBoardSize] = 'O';
				*inbNextPlayer = 0;
				iniTurnsPlayed++;
			}
		}
		else
		{
			printf("\nThis square is already taken, cheater!\n");
		}
	}
	else
	{
		printf("\nNot a valid square, try again!\n");
	}
	return iniTurnsPlayed;
}

INT main() {

	INT iBoardSize;
	INT iTurnsPlayed; 
	BOOL bNextPlayer;

	iTurnsPlayed = 0;
	bNextPlayer = 0;

	printf_s("Enter board size: ");
	scanf_s("%d", &iBoardSize);

	CHAR** arrBoardContents = (CHAR**)malloc(iBoardSize * sizeof(CHAR*));

	// Initializing Board
	// explain to me the initialization process!
	if (arrBoardContents) {
		for (INT iRow = 0; iRow < iBoardSize; iRow++) {
			arrBoardContents[iRow] = (CHAR*)malloc(iBoardSize * sizeof(CHAR));
			if (arrBoardContents[iRow]) {
				for (INT iColumn = 0; iColumn < iBoardSize; iColumn++) {
					arrBoardContents[iRow][iColumn] = '.';
				}
			}
		}
	}

	while (CheckWin(arrBoardContents, iBoardSize) == 0 && iTurnsPlayed < iBoardSize*iBoardSize) {
	// looks so much better, isn't it?
		PrintBoard(arrBoardContents, iBoardSize);
		
		iTurnsPlayed = FillSqaure(arrBoardContents, iBoardSize, iTurnsPlayed, &bNextPlayer);

	}

	PrintBoard(arrBoardContents, iBoardSize);

	// also here - is it efficient?
	if (CheckWin(arrBoardContents, iBoardSize) == 1) {
		printf_s("X Won!");
	}
	else if (CheckWin(arrBoardContents, iBoardSize) == 2) {
		printf_s("O Won!");
	}
	else {
		printf_s("Game over - tie!");
	}

	// what heppaned to arrBoardContents and arrBoardContents[i]
	
	return 0;
}
