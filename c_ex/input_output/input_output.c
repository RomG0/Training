// input_output.c
// Program detects char as input and preforms action accordingly

// imports
#include <stdio.h>
#include <ctype.h>
#include <Windows.h>
#include <conio.h>

INT main() {

    // variable initialization
    INT iLastInt;
    CHAR cInputChar;

    // variable declaration
    iLastInt = 0;
    CONST CHAR cCTRLZ = '\x1a';

    printf("Enter a character (only first char will be aknowledged): ");
    cInputChar = _getche();
    while (cInputChar != cCTRLZ) {

        // Checks if input is digit, if so updates saved int
        if (isdigit(cInputChar)) {
            iLastInt = cInputChar - '0';
            printf_s("\nDetected digit, updated iLastInt to: %d", iLastInt);
        }

        // Checks if input is uppercase letter, if so prints it as lowercase
        else if (isupper(cInputChar)) {
            printf_s("\nUppercase letter, converting to lowercase: %c", tolower(cInputChar));
        }
        else if (islower(cInputChar)) {

            // if saved int is unchanged/ was previously changed to a number divisible by 3,
            // prints the letter 3 steps forward cyclically from input letter
            if (iLastInt % 3 == 0) {

                // detects if character 3 steps forward is out of alphabet ascii range,
                // if so moves it back to range from the beginning
                if (cInputChar + 3 > 'z') {
                    cInputChar -= 26;
                }
                printf_s("\niLastInt is divisible by 3, moving forward 3 steps - %c", cInputChar + 3);
            }

            // if saved int was previously changed to a number not divisible by 3,
            // prints the letter 3 steps backward cyclically from input letter
            else
            {

                // detects if character 3 steps backward is out of alphabet ascii range,
                // if so moves it back to range from the end
                if (cInputChar - 3 < 'a')
                    cInputChar += 26;
                printf_s("\niLastInt is not divisible by 3, moving backward 3 steps - %c", cInputChar - 3);
            }
        }
        printf("\nEnter a character (only first char will be aknowledged): ");
        cInputChar = _getche();
    }
    return 0;
}
