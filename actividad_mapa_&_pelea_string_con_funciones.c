#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void leerPosiciones(const char *archivoJugador, const char *archivoEnemigo, int *xJugador, int *yJugador, int *xEnemigo, int *yEnemigo) {
    FILE *archivo;

    archivo = fopen(archivoJugador, "r");
    if (archivo != NULL) {
        fscanf(archivo, "%d %d", xJugador, yJugador);
        fclose(archivo);
    } else {
        printf("No se pudo abrir el archivo %s\n", archivoJugador);
        exit(1);
    }

    archivo = fopen(archivoEnemigo, "r");
    if (archivo != NULL) {
        fscanf(archivo, "%d %d", xEnemigo, yEnemigo);
        fclose(archivo);
    } else {
        printf("No se pudo abrir el archivo %s\n", archivoEnemigo);
        exit(1);
    }
}

char *seleccionarPalabraAleatoria(const char *archivoDiccionario) {
    FILE *archivo = fopen(archivoDiccionario, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo %s\n", archivoDiccionario);
        exit(1);
    }

    char **palabras = NULL;
    char palabra[100];
    int cantidad = 0;

    while (fscanf(archivo, "%s", palabra) != EOF) {
        palabras = realloc(palabras, sizeof(char*) * (cantidad + 1));
        palabras[cantidad] = malloc(strlen(palabra) + 1);
        strcpy(palabras[cantidad], palabra);
        cantidad++;
    }
    fclose(archivo);

    srand(time(NULL));
    char *palabraSeleccionada = palabras[rand() % cantidad];

    for (int i = 0; i < cantidad; i++) {
        if (palabras[i] != palabraSeleccionada) {
            free(palabras[i]);
        }
    }
    free(palabras);

    return palabraSeleccionada;
}

void mostrarMapa(char map[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

int jugarAhorcado(const char *palabraSecreta) {
    int longitud = strlen(palabraSecreta);
    char intento[longitud + 1];
    memset(intento, '-', longitud);
    intento[longitud] = '\0';

    int intentosRestantes = 6;
    char letra;
    int acertado;

    while (intentosRestantes > 0 && strcmp(intento, palabraSecreta) != 0) {
        printf("Palabra: %s\nIntentos restantes: %d\nLetra: ", intento, intentosRestantes);
        scanf(" %c", &letra);

        acertado = 0;
        for (int i = 0; i < longitud; i++) {
            if (palabraSecreta[i] == letra && intento[i] != letra) {
                intento[i] = letra;
                acertado = 1;
            }
        }

        if (!acertado) {
            intentosRestantes--;
        }
    }

    return strcmp(intento, palabraSecreta) == 0;
}

int main() {
    char map[10][10];
    int xJugador, yJugador, xEnemigo, yEnemigo;
    int vidas = 3;

    leerPosiciones("Posicion.txt", "PosicionEnemigo.txt", &xJugador, &yJugador, &xEnemigo, &yEnemigo);

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            map[i][j] = '-';
        }
    }
    map[xJugador][yJugador] = 'X';
    map[xEnemigo][yEnemigo] = 'E';

    while (vidas > 0) {
        mostrarMapa(map);

        char dir;
        printf("Mover (w/a/s/d o s para salir): ");
        scanf(" %c", &dir);

        if (dir == 's') {
            printf("Has salido del juego.\n");
            break;
        }

        map[xJugador][yJugador] = '-';
        if (dir == 'w' && xJugador > 0) xJugador--;
        if (dir == 's' && xJugador < 9) xJugador++;
        if (dir == 'a' && yJugador > 0) yJugador--;
        if (dir == 'd' && yJugador < 9) yJugador++;
        map[xJugador][yJugador] = 'X';

        if (xJugador == xEnemigo && yJugador == yEnemigo) {
            printf("\nHas encontrado al enemigo. Comienza el ahorcado.\n");
            char *palabraSecreta = seleccionarPalabraAleatoria("Diccionario.txt");
            if (jugarAhorcado(palabraSecreta)) {
                printf("\nHas ganado el desafío del ahorcado. Nueva posición generada.\n");
                srand(time(NULL));
                xEnemigo = rand() % 10;
                yEnemigo = rand() % 10;
                map[xEnemigo][yEnemigo] = 'E';
            } else {
                vidas--;
                printf("\nHas perdido el desafío. Vidas restantes: %d\n", vidas);
            }
            free(palabraSecreta);
        }
    }

    if (vidas == 0) printf("\nSin vidas. Fin del juego.\n");
    return 0;
}
