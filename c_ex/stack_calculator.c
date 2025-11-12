#include <stdio.h>
#include <Windows.h>

INT GetStartingNumber() {
	INT iScanfStatus;
	INT iOriginalNumber;

	iScanfStatus = 0;

	while (iScanfStatus == 0) {
		printf_s("Enter starting number: ");
		iScanfStatus = scanf_s("%d", &iOriginalNumber);
		if (iScanfStatus == 0) {
			printf("Not a number!! Clearing stdin buffer\n");
			while (getchar() != '\n');
		}
	}
	return iOriginalNumber;
}

VOID StackCalculator(INT iniOriginalNumber) {
// I'm giving you a chance to look for what you did wrong.
// A clue - Does this function work for any sequence of inputs?
	
	INT iNumber;
	INT iLastNumber;
	CHAR cAction;
	CHAR cLastAction;

	iNumber = iniOriginalNumber;
	iLastNumber = iniOriginalNumber;

	printf_s("Enter Action: ");
	cAction = _getche();
	cLastAction = cAction;

	while (cAction != 'e') {

		switch (cAction) {
		case '+':
			iLastNumber = iNumber;
			iNumber += 1;
			printf_s("\n%d", iNumber);
			cLastAction = cAction;
			break;
		case '-':
			iLastNumber = iNumber;
			iNumber -= 1;
			printf_s("\n%d", iNumber);
			cLastAction = cAction;
			break;
		case '*':
			iLastNumber = iNumber;
			iNumber *= 2;
			printf_s("\n%d", iNumber);
			cLastAction = cAction;
			break;
		case '/':
			iLastNumber = iNumber;
			iNumber /= 2;
			printf_s("\n%d", iNumber);
			cLastAction = cAction;
			break;
		case 'u':
			printf("\n%d", iLastNumber);
			cLastAction = cAction;
			break;
		case 'r':
			printf("\n%c", cLastAction);
			cLastAction = cAction;
			break;
		case 'c':
			printf_s("\n%d", iniOriginalNumber);
			cLastAction = cAction;
			break;

		default:
			printf_s("\nInvalid inputted action");
		}
		printf_s("\nEnter action: ");
		cAction = _getche();
	}
}

INT main() {

	INT iOriginalNumber;

	iOriginalNumber = GetStartingNumber();
	StackCalculator(iOriginalNumber);

	return 0;
}
