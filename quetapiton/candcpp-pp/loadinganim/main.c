#include <stdio.h>
#include <windows.h>

int main() {
    int x = 0;

    while (1) {
        system("cls");

        for (int sl = 0; sl < x; sl++ ) {
            printf(" ");
        }

        printf("|\n");

        x++;

        if (x > 100) x = 0;

        Sleep(20);
    }
}