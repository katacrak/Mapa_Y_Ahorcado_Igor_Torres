#include <iostream>
#include <string>

using namespace std;

int main() {
    char map[10][10];
    int x = 0, y = 0, vidas = 3;
    string palabra;

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            map[i][j] = '-';
    map[x][y] = 'X';

    while (vidas > 0) {
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) cout << map[i][j] << ' ';
            cout << endl;
        }

        char dir;
        cout << "Mover (w/a/s/d): ";
        cin >> dir;
        map[x][y] = '-';
        if (dir == 'w' && x > 0) x--;
        if (dir == 's' && x < 9) x++;
        if (dir == 'a' && y > 0) y--;
        if (dir == 'd' && y < 9) y++;
        map[x][y] = 'X';

        if (x == 4 && y == 4) {
            cout << "Adivina la palabra secreta: ";
            cin >> palabra;
            if (palabra == "patata") {
                cout << "¡Correcto! Has ganado." << endl;
                break;
            } else {
                vidas--;
                cout << "Incorrecto. Vidas restantes: " << vidas << endl;
            }
        }
    }

    if (vidas == 0) cout << "Sin vidas. Fin del juego." << endl;
    return 0;
}
