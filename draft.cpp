#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

const int WIDTH = 30;
const int HEIGHT = 15;

struct Car {
    int x, y;
};

int playerX = WIDTH / 2;
int playerY = HEIGHT - 1;

vector<Car> cars;

bool gameOver = false;
bool win = false;

void draw() {
    clear();

    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {

            if (x == playerX && y == playerY) {
                mvprintw(y, x, "C"); // chicken
            } else {
                bool printed = false;

                for (auto &car : cars) {
                    if (car.x == x && car.y == y) {
                        mvprintw(y, x, "=");
                        printed = true;
                        break;
                    }
                }

                if (!printed)
                    mvprintw(y, x, ".");
            }
        }
    }

    mvprintw(HEIGHT + 1, 0, "W/A/D to move, Q to quit");
    refresh();
}

void updateCars() {
    for (auto &car : cars) {
        car.x++;

        if (car.x >= WIDTH) {
            car.x = 0;
            car.y = rand() % (HEIGHT - 1);
        }
    }
}

void checkCollision() {
    for (auto &car : cars) {
        if (car.x == playerX && car.y == playerY) {
            gameOver = true;
        }
    }
}

int main() {
    srand(time(0));

    // ncurses setup
    initscr();
    noecho();
    curs_set(0);
    nodelay(stdscr, TRUE); // non-blocking input

    // create cars
    for (int i = 0; i < 6; i++) {
        cars.push_back({rand() % WIDTH, rand() % (HEIGHT - 1)});
    }

    while (!gameOver && !win) {
        draw();

        int ch = getch();

        if (ch == 'w' || ch == 'W') playerY--;
        else if (ch == 'a' || ch == 'A') playerX--;
        else if (ch == 'd' || ch == 'D') playerX++;
        else if (ch == 'q' || ch == 'Q') break;

        // boundaries
        if (playerX < 0) playerX = 0;
        if (playerX >= WIDTH) playerX = WIDTH - 1;

        if (playerY < 0) win = true;

        updateCars();
        checkCollision();

        usleep(100000); // game speed (0.1 sec)
    }

    endwin(); // exit ncurses mode

    if (win)
        printf("YOU WIN! 🐔\n");
    else if (gameOver)
        printf("GAME OVER 💥\n");
    else
        printf("EXITED\n");

    return 0;
}
