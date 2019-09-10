/******************
 * assignment01.c
 * Author: Adam Sebzda
 * Class:  CSCI-435
 *****************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char buf[32] = "";
    int charInt = 0;
    int charOffset = 97;

    printf("Input text: ");
    scanf("%32s", buf);

    // Search for ASCII chars in the buffer
    for (int c = 0; c <= strlen(buf); c++) {
        for (int i = 0; i <= 25; i++) {
            if ((int)buf[c] == i + charOffset) {
                // Store discovered chars into charInt
                charInt = charInt | (0x01 << i);
                break;
            }
        }
    }

    // Write out the chars stored into charInt
    for (int i = 0; i <= 25; i++) {
        if (charInt & (0x01 << i)) {
            printf("%c\n", i + charOffset);
        }
    }
}