#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    char escolha[256];
    printf("Escolha um ponto de entrada:\n");
    printf("1. Beep\n2. mouse test\n");
    fgets(escolha, sizeof(escolha), stdin);

    if (escolha[0] == '1') {
        Beep(750, 500);
    } else if (escolha[0] == '2') {
        while (1) {
            if (GetAsyncKeyState(VK_LBUTTON) & 1) {
                Beep(750, 500);
            }

            Sleep(2000);
        }
    } else {
        Beep(750, 2000);
        printf("comando invalido, tente novamente reiniciando o aplicativo");
    }
}