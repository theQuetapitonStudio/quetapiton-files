#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <windows.h>

void createFile(const char *conteudo, const char *nome) {
    FILE *f = fopen(nome, "w");
    if (!f) {
        printf("erro ao criar arquivo");
    }
    fprintf(f, "%s", conteudo);
    fclose(f);
}

void sistemaComandos() {
    system("cls");
    _chdir(getenv("USERPROFILE"));
    _chdir("desktop");
    _chdir("ErromadeiteAbbys");
    _mkdir("mainuser");
    char comando[256];
    while (1) {
        printf("> ");
        fgets(comando, sizeof(comando), stdin);
        if (comando == "execute erromadeitepack") {
            printf("Verschwinde, verschwinde aus meinem Leben, ich habe das Paket noch nicht fertiggestellt HAHAHAHAHA, hier spricht Quetapiton, ich plane noch einige Apps für das Paket, also keine Sorge, warte einfach ab, Prinz. \n");
        } else if (comando == "exit"){
            exit(0);
        }
    }
}


int main() {
    _chdir(getenv("USERPROFILE"));
    _chdir("desktop");
    char escolha[256];

    printf("                            #$$@#@$@\n");
    printf("ErromadeiteAbbys [SETUP]   #    $   # \n");
    printf("                            #$##$@$#  \n");
    printf("\n\n\n1. Start setup\n");
    printf("2. Exit\n");

    fgets(escolha, sizeof(escolha), stdin);

    if (escolha[0] == '1') {
        system("cls");
        _mkdir("ErromadeiteAbbys");
        _chdir("ErromadeiteAbbys");
        _mkdir("keys");
        _chdir("keys");
        createFile("13r7438578357389738495fj849ujfr9ej8r3", "key");
        Sleep(1500);
        printf("Installing and starting dependencies [on the desktop]\n");
        _chdir("..");
        _mkdir("configs");
        _chdir("configs");
        Sleep(3000);
        printf("Ready! \n");
        Sleep(100);
        sistemaComandos();
    } else if (escolha[0] == '2') {
        exit(0);
    }

    system("pause >nul");
}