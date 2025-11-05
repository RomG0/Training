#include <stdio.h>
#include <ctype.h>
#include <Windows.h>

int main() {
    CHAR input_char;
    INT last_int = 0;
    while (1) {
        printf("Enter a character (only first char will be aknowledged): ");
        int x = scanf_s("%c", &input_char, 1);
        if (x == EOF) {
            exit(0);
        }
        if (isdigit(input_char)) {
            int last_int = input_char - 48;
            printf_s("Detected digit, updated last_int to: %d\n", last_int);
        }
        else if (isupper(input_char)) {
            printf_s("Uppercase letter, converting to lowercase: %c\n", tolower(input_char));
        }
        else if (islower(input_char)) {
            if (last_int % 3 == 0) {
                if (input_char + 3 > 122) {
                    input_char -= 26;
                }
                printf_s("%c\n", input_char + 3);
            }
            else
            {
                if (input_char - 3 < 97)
                    input_char += 26;
                printf_s("%c\n", input_char - 3);
            }

        }
    }

    return 0;
}
