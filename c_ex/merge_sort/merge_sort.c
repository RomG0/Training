#include "merge_sort.h"

INT* SeperateArray(INT* inarrUnsortedArr, INT iniArrLen) {

	INT iArrMid;
	INT iArrLenRight;
	INT* iarrSortedLeft;
	INT* iarrSortedRight;
	
	if (iniArrLen == 1)
		return inarrUnsortedArr;

	iArrMid = iniArrLen / 2;
	iArrLenRight = iniArrLen - iArrMid;

	INT* iarrLeft = (INT*)malloc(iArrMid*sizeof(INT));
	INT* iarrRight = (INT*)malloc(iArrLenRight * sizeof(INT));


	if (iarrLeft && iarrRight) {


		for (INT iCount = 0; iCount < iniArrLen; iCount++) {
			printf_s("value %d is %d\n",iCount, inarrUnsortedArr[iCount]);
			if (iCount < iArrMid) {
				iarrLeft[iCount] = inarrUnsortedArr[iCount];
			}
			else
			{
				iarrRight[iCount - iArrMid] = inarrUnsortedArr[iCount];
			}
		}
		iarrSortedLeft = SeperateArray(iarrLeft,iArrMid);
		iarrSortedRight = SeperateArray(iarrRight,iArrLenRight);

		return MergeArray(iarrSortedLeft, iarrSortedRight, iArrMid, iArrLenRight);
	}
	else {
		return 1;
	}
}

INT* MergeArray(INT* inarrLeft, INT* inarrRight, INT iniArrLenLeft, INT iniArrLenRight) {

	INT iLeftCounter;
	INT iRightCounter;
	INT iArrLenMerged;
	INT iMergedCounter;

	iLeftCounter = 0;
	iRightCounter = 0;
	iMergedCounter = 0;

	iArrLenMerged = iniArrLenLeft + iniArrLenRight;

	INT* iarrSortedArr = (INT*)malloc(iArrLenMerged * sizeof(INT));

	if (iarrSortedArr) {


		while (iLeftCounter < iniArrLenLeft && iRightCounter < iniArrLenRight) {
			if (inarrLeft[iLeftCounter] >= inarrRight[iRightCounter]) {
				iarrSortedArr[iMergedCounter] = inarrRight[iRightCounter];
				iRightCounter++;
			}
			else if (inarrRight[iRightCounter] > inarrLeft[iLeftCounter]){
				iarrSortedArr[iMergedCounter] = inarrLeft[iLeftCounter];
				iLeftCounter++;
			}
			iMergedCounter++;
		}
		if (iLeftCounter == iniArrLenLeft) {
			while (iRightCounter < iniArrLenRight) {
				iarrSortedArr[iMergedCounter] = inarrRight[iRightCounter];
				iRightCounter++;
				iMergedCounter++;
			}
		}
		else if (iRightCounter == iniArrLenRight) {
			while (iLeftCounter < iniArrLenLeft) {
				iarrSortedArr[iMergedCounter] = inarrLeft[iLeftCounter];
				iLeftCounter++;
				iMergedCounter++;
			}
		}
		return iarrSortedArr;
	}
	else {
		return 1;
	}
}

INT main() {
	INT* arrSortedArr;

	INT arrUnsortedArr[] = {3,9,8,1,4,3,9,-1};
	INT iArrLen;

	iArrLen = sizeof(arrUnsortedArr) / sizeof(arrUnsortedArr[0]);

	arrSortedArr = SeperateArray(arrUnsortedArr,iArrLen);

	for (INT i = 0; i < iArrLen; i++) {
		printf("%d, ", arrSortedArr[i]);
	}

	return 0;
}