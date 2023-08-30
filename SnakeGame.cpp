#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

bool gameover;
const int width = 40;
const int height = 20;
int x, y, fruit_x, fruit_y, score;
int tail_x[100], tail_y[100];
int length_tail = 0;

// User defined variable is created by using 'enum'
enum command {STOP = 0, LEFT, RIGHT, UP, DOWN};
command direc;

void start_setup(){
    gameover = false;
    direc = STOP;
    x = width / 2;
    y = height / 2;
    fruit_x = rand() % (width);  // range[0, width-1]
    fruit_y = rand() % (height); // range[0, height-1]
    score = 0;
}
void draw(){
    // system ("cls");
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0}); // To decrease flickering
    
    cout << "\nW(up) A(left) S(down) D(right) || Arrow keys (Up, Down, Left, Right)" << endl;
    cout << "Press 'X' to exit" << endl;
    for (int i = 0; i <= height; i++){
        for (int j = 0; j <= width; j++){
            if ( i == 0 || j == 0 || i == height || j == width) {
                cout << "#";
            }
            else if (i == y && j == x){
                cout << "O";
            }
            else if (i == fruit_y && j == fruit_x){
                cout << "@";
            }
            else {
                bool print = false;
                for (int k = 0; k < length_tail; k++){
                    if (tail_x[k] == j && tail_y[k] == i){
                        cout << "o";
                        print = true;
                    }
                }
                if (!print){
                    cout << " ";
                }
            }
        }
        cout << endl;
    }
    cout << "Score = " << score << endl;
}
void input(){
    if (kbhit() == true){ // It is present in conio.h and used to determine if a key has been pressed or not
        switch (getch()){ // Reads the key pressed by the user
            case 'a':
                direc = LEFT;
                break;
            case 'd':
                direc = RIGHT;
                break;
            case 'w':
                direc = UP;
                break;
            case 's':
                direc = DOWN;
                break;
            case 'A':
                direc = LEFT;
                break;
            case 'D':
                direc = RIGHT;
                break;
            case 'W':
                direc = UP;
                break;
            case 'S':
                direc = DOWN;
                break;
            case KEY_UP:
                direc = UP;
                break;
            case KEY_DOWN:
                direc = DOWN;
                break;
            case KEY_LEFT:
                direc = LEFT;
                break;
            case KEY_RIGHT:
                direc = RIGHT;
                break;
            case 'x':
                gameover = true;
                break;
            case 'X':
                gameover = true;
                break;
        }
    }
}
void logic(){
    int prevX = tail_x[0];
    int prevY = tail_y[0];
    int prev2X, prev2Y;
    tail_x[0] = x;
    tail_y[0] = y;
    for (int i = 1; i < length_tail; i++){
        prev2X = tail_x[i];
        prev2Y = tail_y[i];
        tail_x[i] = prevX;
        tail_y[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (direc){
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
    }
    
    if (x >= width){
        x = 0;
    }
    else if (x <= 0){
        x = width - 1;
    }
    if (y >= height){
        y = 0;
    }
    else if (y <= 0){
        y = height - 1;
    }
    for (int i = 0; i < length_tail; i++){
        if (tail_x[i] == x && tail_y[i] == y){
            gameover = true;
        }
    }
    if (x == fruit_x && y == fruit_y){
        score += 100;
        fruit_x = (rand() % (width-1)) + 1;  // range[1, width-1]
        fruit_y = (rand() % (height-1)) + 1;  // range[1, width-1]
        length_tail++;
    }
}
int main(){
    start_setup();
    while (!gameover){
        Sleep(50);
        draw();
        input();
        logic();
    }
    Sleep(500);
    cout << "\n**** G A M E O V E R ****" << endl;
    
    Sleep(1000);
    cout << "\npress any key to exit" << endl;
    getch();

    return 0;
}