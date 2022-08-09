// INCLUDE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

// DEFINE

#define intentos 6
#define palabras 5
#define partis 8
#define pun1 5000
#define pun2 100
#define pun3 50
#define pun4 2000
#define pun5 10000
#define pun6 500
#define pun7 0
#define maxpalabras 48
#define archivo "azar.txt"
#define MAXIMO_PALABRAS 30
#define verde  "\x1b[32m"
#define amarillo  "\x1b[33m"
#define rojo "\x1b[31m"
#define RESET "\x1B[0m"

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
static HANDLE stdoutHandle;
static DWORD outModeInit;

// ESTRUCTURAS

struct jugadorp{
    char respuesta[5];
};
struct lista{
    char palabra[6];
};

// FUNCIONES

void bienvenida();
void menu(int *);
void alazar();
void finalizar_p(char *);
void setupConsole();
void restoreConsole();

// COMIENZO

int main(){

    setupConsole();
    struct jugadorp jugador[6];
    int num, po, palabra, j, q, sd, puntajes, puntos3, pos;
    int k = 0;
    int respuesta = 0;
    int partida_actual = 0;
    char arrpalabras[maxpalabras][palabras];
    char nada[palabras] = "";
    clock_t inicio, fin;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for(j = 0; j < maxpalabras; j++){
        strcpy(arrpalabras[j], nada);
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bienvenida();
    menu(&k);
    int total_de_puntos[k];

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// JUEGO

    for(j = 0; j < k; j++){
        respuesta = respuesta + 1;                                                        // CONTADOR DE PARTIDAS
        printf("El numero de partidas que lleva jugadas son: %d de %d\n", respuesta, k);  // CONTADOR DE PARTIDAS

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ARCHIVOS

        struct lista words[MAXIMO_PALABRAS];
        char palabraMisteriosa[6];
        int contadorPalabras = 0;

        FILE* f = fopen("azar.txt", "r");
        while (fscanf(f, "%s", palabraMisteriosa) != EOF && contadorPalabras < MAXIMO_PALABRAS){
            strcpy(words[contadorPalabras].palabra, palabraMisteriosa); // SE COPIA PALABRAMISTERIOSA A LISTAPALABRAS
            contadorPalabras++;
        }
        fclose(f);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// PALABRA AL AZAR

        srand(time(NULL));
        char arr[6];
        strcpy(arr, words[rand()%contadorPalabras].palabra);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//JUEGO

        int r, car;
        char car1;
        int puntos2 = pun1;
        char flag1 = 'N';
        char flag2 = 'N';
        int arrpuntos[palabras] = {0, 0, 0, 0, 0};

        for(r = 1; r <= intentos; r++){
            int cont1 = 0, cont2 = 0;
            printf("\n\n--------------------------------------------------------------\n");
            printf("\nIntento numero %d de %d\n\n", r, intentos);
            inicio = clock();
            printf("Ingrese una palabra de 5 letras\n\n");
            printf("> ");
            fflush(stdin);
            scanf("%s", jugador[r].respuesta);

            strcpy(arrpalabras[(j * intentos) + r - 1], jugador[r].respuesta);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//COMPARAR

            int i, l;
            int w = 0;

            for(i = 0; i < palabras; i++){
                if (arr[i] == jugador[r].respuesta[i]){
                    printf(RESET);
                    printf("%s %c ", verde, jugador[r].respuesta[i]);
                    printf(RESET);
                    flag1 = 'S';
                    cont1++;
                    w = w + 1;
                }
                else if(arr[i] != jugador[r].respuesta[i]){
                    for(l = 0; l < palabras; l++){
                        if((arr[l] == jugador[r].respuesta[i]) && (i != l)){
                            printf("%s", amarillo " - ");
                            printf(RESET);
                            flag2 = 'S';
                            cont2++;
                            w = w + 1;
                        }
                    }
                }
                if (w == 0){
                    printf("%s", rojo " * ");
                    printf(RESET);
                }
                w = 0;
            }
            printf("\n");

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ACERTADA

            char genio = 'N';
            int g;
            int w1 = 0;

            for(g = 0; g < palabras; g++){
                if(arr[g] == jugador[r].respuesta[g]){
                    w1 = w1 + 1;
                }
                if(w1 == palabras){
                    printf("\n\nAdivinaste la palabra!\n");
                    genio = 'S';
                }
            }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// PUNTOS

                if (genio == 'S'){
                    if (r == 1){
                        puntos2 = pun5;
                        total_de_puntos[j] = puntos2;
                        printf("Tus puntos son: %d\n", total_de_puntos[j]);
                    }
                    else if (r != 1){
                        puntos2 = puntos2 + pun4;
                        total_de_puntos[j] = puntos2;
                        printf("Tus puntos son: %d\n", total_de_puntos[j]);
                    }
                    break;
                }

                if (genio == 'N'){

                int n, m;

                for(n = 0; n < palabras; n++){
                    if((arr[n] == jugador[r].respuesta[n]) && (arrpuntos[n] != pun2)){
                        arrpuntos[n] = pun2;
                        puntos2 = puntos2 + arrpuntos[n];
                    }
                    if(arr[n] != jugador[r].respuesta[n]){
                        for(m = 0; m < palabras; m++){
                            if((arr[n] == jugador[r].respuesta[m]) && (arrpuntos[n] != pun2 && arrpuntos[n] != pun3)){
                                arrpuntos[n] = pun3;
                                puntos2 = puntos2 + arrpuntos[n];
                            }
                        }
                    }
                }
                puntos2 = puntos2 - pun6;
            }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//JUEGO

            if(r != palabras - (-2)){
                printf("\n\nPuntos actuales: %d\n\n", puntos2);
            }

            if (r == intentos){
                puntos2 = pun7;
                total_de_puntos[j] = puntos2;
                printf("No acertaste!\n\n");
            }

            printf("Tus puntos fueron: %d", puntos2);
        }
        fin = clock();

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// FINALIZACION

            char fin = 'N';

            if((j + 1) < k){
            finalizar_p(&fin);
                if (fin == 'N'){
                    k = j + 1;
                }
            }

        printf("\nLa palabra era: %s\n", arr);
    }

    printf("\t\t\t\t\n\nGAME END\n\n");

    int time = (fin - inicio) / CLOCKS_PER_SEC;
    printf("Tu tiempo fue de: %d segundos.\n\n", time);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// PUNTOS FINALES

    int b;
    int bandera1 = 0;
    int suma = 0;
    int imayor = 0, imenor = 0;
    int pmayor = pun7;
    int pmenor = pun5;

    printf("Puntos de las partidas: \n\n");

    for(b = 0; b < k; b++){
        printf("Partida %d - Puntos: %d\n", b + 1, total_de_puntos[b]);

        if(total_de_puntos[b] > pmayor){
            pmayor = total_de_puntos[b] - time;
            imayor = b;
        }

        if(total_de_puntos[b] < pmenor){
            pmenor = total_de_puntos[b] - time;
            imenor = b;
        }

        if(total_de_puntos[b] != pun7){
            suma = suma + total_de_puntos[b] - time;
            bandera1 = b;
        }
    }
    printf("\nLos puntos mayores fueron: %d de la partida %d", pmayor, imayor + 1);
    printf("\nLos puntos menores fueron: %d de la partida %d", pmenor, imenor + 1);
    printf("\nLos puntos promedios fueron: %d\n", suma / (bandera1 + 1));

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// VER PALABRAS

    char rta4;
    int c, cc, ccc;

    printf("\nDeseas ver las palabras que usaste? (S/N)\n");
    printf("> ");
    fflush(stdin);
    scanf("%c", &rta4);
    while(rta4 != 'S' && rta4 != 'N'){
        printf("Respuesta invalida, intente de nuevo. (S/N)\n");
        printf("> ");
        fflush(stdin);
        scanf("%c", &rta4);
    }
    if(rta4 == 'S'){
        for(c = 0; c < j; c++){
            printf("\nPalabras de la partida %d: \n\n", c + 1);
            for(cc = 0; cc < intentos; cc++){
                if(strcmp(arrpalabras[(c * intentos) + cc], nada) != 0){
                    printf("Palabra %d es: ", cc + 1);
                    for(ccc = 0; ccc < palabras; ccc++){
                        printf("\t%c", arrpalabras[(c * intentos) + cc][ccc]);
                    }
                    printf("\n");
                }
                printf("\n");
            }
        }
        printf("\nGracias por jugar!\n");
    }
    else if(rta4 == 'N'){
        printf("\nGracias por jugar!\n");
    }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// FIN

    restoreConsole();

    system("pause");

    return 0;
}

// FUNCIONES

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void bienvenida(){
    printf("\t\t\t\t\t\tSesion de juego \n");
    printf("\t\t\t\t\tBienvenido al Wordle de FRANCO y JULIA\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void menu(int *respuesta){
    printf("\nIngrese las partidas quiera jugar (de 1 a 8 partidas)\n");
    printf("> ");
    fflush(stdin);
    scanf("%d", respuesta);
    while(!(*respuesta >= 1 && *respuesta <= 8)){
        printf("Respuesta invalida, intente de nuevo. (de 1 a 8 partidas)\n");
        printf("> ");
        fflush(stdin);
        scanf("%d", respuesta);
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void finalizar_p(char *rta){
    printf("\n\n--------------------------------------------------------------\n");
    printf("\nDesea seguir jugando S/N\n");
    printf("> ");
    fflush(stdin);
    scanf("%c", rta);
    while(*rta != 'S' && *rta != 'N'){
        printf("\nRespuesta incorrecta, responda con S/N\n");
        printf("> ");
        fflush(stdin);
        scanf("%c", rta);
    }
    printf("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setupConsole(void){
    DWORD outMode = 0;
    stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    if(stdoutHandle == INVALID_HANDLE_VALUE){
        exit(GetLastError());
    }

    if(!GetConsoleMode(stdoutHandle, &outMode)){
        exit(GetLastError());
    }

    outModeInit = outMode;

    // Enable ANSI escape codes
    outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

    if(!SetConsoleMode(stdoutHandle, outMode)){
        exit(GetLastError());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

restoreConsole(void){
    // Reset de colores
    printf("\x1b[0m");

    // Reset modo de consolas
    if(!SetConsoleMode(stdoutHandle, outModeInit)){
        exit(GetLastError());
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
