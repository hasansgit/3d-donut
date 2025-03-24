#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <algorithm>

const int WIDTH = 80;
const int HEIGHT = 20;
const float aspect = (float)WIDTH / HEIGHT;
const float pixelAspect = 11.0f / 24.0f;

const char gradient[] = "  .:!/r0@  ";
const int gradientSize = sizeof(gradient) - 1;

char screen[HEIGHT][WIDTH];

void gotoxy(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}

void print_screen() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            std::cout << screen[i][j];
        }
        std::cout << '\n';
    }
    gotoxy(0, 0);
    usleep(0.0005 * 1e6);
}

int main() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif

    for (int t = 0;; t++) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                float x = (float)j / WIDTH * 2.0f - 1.0f;
                float y = (float)i / HEIGHT * 2.0f - 1.0f;
                
                x *= aspect * pixelAspect;
                x += sin(t * 0.001);

                screen[i][j] = ' ';

                float dist = (x * x + y * y);
                int color = 1.0f / dist;
                color = std::max(color, 0);
                color = std::min(color, gradientSize - 1);

                screen[i][j] = gradient[color];
            }
        }
    
        print_screen();

    }

    return 0;
}