#include "double_factorial.h"

ULONGLONG CalculateFactorial(ULONGLONG iniInputNumber) {
	if (iniInputNumber == 1)
		return 1;
	return CalculateFactorial(iniInputNumber - 1) * iniInputNumber;
}

ULONGLONG CalculateDoubleFactorial(ULONGLONG iniInputNumber) {
	if (iniInputNumber == 1)
		return 1;
	return CalculateFactorial(iniInputNumber - 1) * CalculateFactorial(iniInputNumber);
}

INT main() {

	printf_s("%llu", CalculateDoubleFactorial(14));

	return 0;
}
