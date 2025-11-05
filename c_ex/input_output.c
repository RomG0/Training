#include <stdio.h>
#include <ctype.h>
#include <Windows.h>
#include <conio.h>
int main() {
    char input_char;
    int last_int = 0;
    printf("Enter a character (only first char will be aknowledged): ");
    input_char = _getche();
    while (input_char != '\x1a') {
        if (isdigit(input_char)) {
            last_int = input_char - 48;
            printf_s("\nDetected digit, updated last_int to: %d\n", last_int);
        }
        else if (isupper(input_char)) {
            printf_s("\nUppercase letter, converting to lowercase: %c\n", tolower(input_char));
        }
        else if (islower(input_char)) {
            if (last_int % 3 == 0) {
                if (input_char + 3 > 122) {
                    input_char -= 26;
                }
                printf_s("\nlast_int is divisible by 3, moving forward 3 steps - %c\n", input_char + 3);
            }
            else
            {
                if (input_char - 3 < 97)
                    input_char += 26;
                printf_s("\nlast_int is not divisible by 3, moving backward 3 steps - %c\n", input_char - 3);
            }
        }
        printf("Enter a character (only first char will be aknowledged): ");
        input_char = _getche();      
    }
    return 0;
}
