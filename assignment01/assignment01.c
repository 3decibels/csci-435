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
	printf("Input text: ");
	scanf("%32s", buf);

	for (int i = 48; i <= 122; i++) {
		for (int c = 0; c < strlen(buf); c++) {
			if (i == (int)buf[c]) {
				printf("%c\n", buf[c]);
				break;
			}
		}
	}
}
