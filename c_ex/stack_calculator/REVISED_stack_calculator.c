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

	INT iCount;
	INT iNumber;
	INT iArraySize;
	CHAR cAction;
	CHAR cLastAction;

	iNumber = iniOriginalNumber;
	iArraySize = 16;
	iCount = 0;

	INT* arrNumberHistory = (INT*)malloc(iArraySize * sizeof(INT));

	if (arrNumberHistory) {

		arrNumberHistory[0] = iniOriginalNumber;
		printf_s("Enter Action: ");
		cAction = _getche();
		cLastAction = cAction;
	
		while (cAction != 'e') {
	
			if (iArraySize == iCount) {
				iArraySize *= 2;
				INT* temparrCheckRealloc = (INT*)realloc(arrNumberHistory, iArraySize * sizeof(INT));
				if (temparrCheckRealloc) {
					arrNumberHistory = temparrCheckRealloc;
					free(temparrCheckRealloc);
				}
				else {
					printf_s("Error reallocating memory to array");
				}
			}

			switch (cAction) {
			case '+':
				arrNumberHistory[iCount] = iNumber;
				iNumber += 1;
				printf_s("\n%d", iNumber);
				cLastAction = cAction;
				iCount++;
				break;
			case '-':
				arrNumberHistory[iCount] = iNumber;
				iNumber -= 1;
				printf_s("\n%d", iNumber);
				cLastAction = cAction;
				iCount++;
				break;
			case '*':
				arrNumberHistory[iCount] = iNumber;
				iNumber *= 2;
				printf_s("\n%d", iNumber);
				cLastAction = cAction;
				iCount++;
				break;
			case '/':
				arrNumberHistory[iCount] = iNumber;
				iNumber /= 2;
				printf_s("\n%d", iNumber);
				cLastAction = cAction;
				iCount++;
				break;
			case 'u':
				if (iCount > 0) {
					iCount--;
					printf("\n%d", arrNumberHistory[iCount]);
					cLastAction = cAction;
					iNumber = arrNumberHistory[iCount];
				}
				else {
					printf("You have reached the beggining of the calculator history.");
					cLastAction = cAction;
				}
				break;
			case 'r':
				printf("\n%c", cLastAction);
				cLastAction = cAction;
				break;
			case 'c':
				printf_s("\n%d", iniOriginalNumber);
				cLastAction = cAction;
				iNumber = iniOriginalNumber;
				iCount = 1;
				break;
				
			default:
				printf_s("\nInvalid inputted action");
			}
			printf_s("\nEnter action: ");
			cAction = _getche();
		}
	}
	else {
		printf_s("Error aloccating memory to array");
	}
}

INT main() {

	INT iOriginalNumber;

	iOriginalNumber = GetStartingNumber();
	StackCalculator(iOriginalNumber);

	return 0;
}