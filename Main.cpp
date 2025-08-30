#include <iostream>
#include <Windows.h>
#include <stdlib.h>
#include <time.h> 
#include <conio.h>

#define OFFSET_X 3
#define OFFSET_Y 3
#define HELP_TIME 100
#define DEPTH 5

using namespace std;

enum class  GameState {
    menu,
    play,
    ended
};

enum class  Key {
    up,left,right,down,menu,help,place,undo,redo,quit,end,none,shoot
};

struct Pos {
    int x;
    int y;

    bool operator != (Pos temp) {
        return this->x != temp.x || this->y != temp.y;
    }

    bool operator == (Pos temp) {
        return this->x == temp.x && this->y == temp.y;
    }

    Pos& operator+=(const Pos& other) {
        this->x += other.x;
        this->y += other.y;
        return *this;
    }

    Pos operator+(const Pos& other) {
        Pos result;
        result.x = this->x + other.x;
        result.y = this->y + other.y;
        return result;
    }

};

struct Board {
    int size;
    int atoms_num;
    int** board;
    int** guess;
};

void set_cursor(int x = 0, int y = 0)
{
    HANDLE handle;
    COORD coordinates;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = x;
    coordinates.Y = y;
    SetConsoleCursorPosition(handle, coordinates);
}
void set_cursor(Pos pos)
{
    HANDLE handle;
    COORD coordinates;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    coordinates.X = pos.x;
    coordinates.Y = pos.y;
    SetConsoleCursorPosition(handle, coordinates);
}

void movecursor(Pos* player,int size,Key Dir) {
    Pos temp = *player;

    switch (Dir)
    {
    case Key::up:
        temp.y--;
        break;
    case Key::left:
        temp.x--;
        break;
    case Key::down:
        temp.y++;
        break;
    case Key::right:
        temp.x++;
        break;
    default:
        break;
    }

    if (temp.x >= OFFSET_X - 1 && temp.x <= OFFSET_X + size && temp.y >= OFFSET_Y - 1 && temp.y <= OFFSET_Y + size) {
        Pos tab[4] = { {OFFSET_X - 1,OFFSET_Y - 1},{OFFSET_X  + size,OFFSET_Y - 1},{OFFSET_X + size,OFFSET_Y + size},{OFFSET_X - 1,OFFSET_Y + size} };
        if (temp != tab[0] && temp != tab[1] && temp != tab[2] && temp != tab[3]) {
            set_cursor(temp);
            *player = temp;
        }
    }
}

Pos randomPos(int size) {
    Pos temp = { rand() % size, rand() % size };
    return temp;
}

Board* initBoard(int size,int atoms_number) {
    Board* board = new Board;
    board->size = size;
    board->atoms_num = atoms_number;
    board->board = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        board->board[i] = (int*)malloc(size * sizeof(int));
        for (int j = 0; j < size; j++) {
            board->board[i][j] = 0;
        }
    }
   
    for (int i = 0; i < atoms_number; i++) {
        Pos temp = randomPos(size);
        if (board->board[temp.x][temp.y] == 1) {
            do {
                temp = randomPos(size);
            } while (board->board[temp.x][temp.y] != 0);
        }
        board->board[temp.x][temp.y] = 1;
    }

    return board;
}

void drawBoard(Board* board,int visability) {
    int size = board->size;
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            set_cursor(x + OFFSET_X, y + OFFSET_Y);
            if (visability == 1){
                if (board->board[x][y]%2 == 1)
                    cout << "*";
            }
            else if(visability == 2){
                if (board->board[x][y] == 2) {
                    cout << "X";
                }
                else if (board->board[x][y] == 3) {
                    cout << "O";
                }
                else if (board->board[x][y] == 1) {
                    cout << "*";
                }
                else
                cout << " ";
            }
            else {
                if (board->board[x][y] >= 2) {
                    cout << "o";
                }
                else
                    cout << " ";
            }
            
        }
    }

    set_cursor(OFFSET_X-1, OFFSET_Y-1);
    cout << (char)188;
    set_cursor(OFFSET_X + size, OFFSET_Y-1);
    cout << (char)200;
    set_cursor(OFFSET_X-1, OFFSET_Y + size);
    cout << (char)187;
    set_cursor(OFFSET_X + size, OFFSET_Y + size);
    cout << (char)201;
    set_cursor(OFFSET_X - 2, OFFSET_Y - 1);
    cout << (char)201;
    set_cursor(OFFSET_X - 1, OFFSET_Y - 2);
    cout << (char)201;
    set_cursor(OFFSET_X + size+1, OFFSET_Y - 1);
    cout << (char)187;
    set_cursor(OFFSET_X + size, OFFSET_Y-2);
    cout << (char)187;
    set_cursor(OFFSET_X - 2, OFFSET_Y + size);
    cout << (char)200;
    set_cursor(OFFSET_X - 1, OFFSET_Y + size+1);
    cout << (char)200;
    set_cursor(OFFSET_X + size+1, OFFSET_Y + size);
    cout << (char)188;
    set_cursor(OFFSET_X + size, OFFSET_Y + size+1);
    cout << (char)188;

    for (int i = 0; i < size; i++) {
        set_cursor(OFFSET_X +i, OFFSET_Y - 2);
        cout << (char)205;
        set_cursor(OFFSET_X +i, OFFSET_Y +size +1);
        cout << (char)205;
        set_cursor(OFFSET_X -2, OFFSET_Y +i);
        cout << (char)186;
        set_cursor(OFFSET_X +size+1, OFFSET_Y + i);
        cout << (char)186;

    }
}

void score(Board* board) {
    int score = 0;
    for (int i = 0; i < board->size; i++) {
        for (int j = 0; j < board->size; j++) {
            if (board->board[i][j] == 3) {
                score++;
            }
        }
    }
    set_cursor(0, 0);
    cout << "Liczba znalezionych atomow = " << score;
}

void drawMenu() {
    system("CLS");
    cout << "Black Box" << endl;
    cout << "1) nowy poziom (5x5 3 atomow)" << endl;
    cout << "2) nowy poziom (5x5 5 atomow)" << endl;
    cout << "3) nowy poziom (5x5 7 atomow)" << endl;
    cout << "4) nowy poziom (8x8 5 atomow)" << endl;
    cout << "5) nowy poziom (10x10 8 atomow)" << endl;
    cout << "6) wyjscie z gry" << endl;
    
}

Key detect() {
    char temp = _getch();
    char ch = temp;
    while (temp != 13) 
    {
        ch = temp;
        temp = _getch();
    }

    if (ch == 'W' || ch == 'w') {
        return Key::up;
    }
    if (ch == 'A' || ch == 'a') {
        return Key::left;
    }
    if (ch == 'S' || ch == 's') {
        return Key::down;
    }
    if (ch == 'D' || ch == 'd') {
        return Key::right;
    }
    if (ch == 'Q' || ch == 'q') {
        return Key::menu;
    }
    if (ch == 'K' || ch == 'k') {
        return Key::end;
    }
    if (ch == 'H' || ch == 'h') {
        return Key::help;
    }
    if (ch == 'U' || ch == 'u') {
        return Key::undo;
    }
    if (ch == 'R' || ch == 'r') {
        return Key::redo;
    }
    if (ch == 'O' || ch == 'o') {
        return Key::place;
    }if (ch == ' ') {
        return Key::shoot;
    }
    return Key::none;
}

void shoot(Pos* player, Board* board,bool visability,char* sign) {
    Pos current = { player->x - OFFSET_X , player->y -OFFSET_Y};
    Pos curPos = current;
    Pos nextPos;
    Pos vec[4] = { {0,-1},{1,0},{0,1},{-1,0} }; 
    int dir;
    
    if (player->x == OFFSET_X - 1 || player->x == OFFSET_X + board->size || player->y == OFFSET_Y-1 || player->y == OFFSET_Y+board->size) {
        if (current.x == -1) {
            dir = 1; 
        }
        else if(current.x == board->size) {
            dir = 3; 
        }
        else if (current.y == -1) {
            dir = 2; 
        }
        else if (current.y == board->size) {
            dir = 0; 
        }
        
        curPos += vec[dir];
        nextPos = curPos + vec[dir];

        if (board->board[curPos.x][curPos.y] == 1) {
            set_cursor(player->x, player->y);
            if(visability)
            cout << "H";
            else {
                cout << " ";
            }
            return;
        }

        switch (dir)
        {
        case 0:
            if (curPos.x + 1 != board->size && board->board[curPos.x + 1][curPos.y] == 1) {
                set_cursor(player->x, player->y);
                if (visability)
                    cout << "R";
                else {
                    cout << " ";
                }
                return;
            }
            else if(curPos.x != 0 && board->board[curPos.x - 1][curPos.y] == 1) {
                set_cursor(player->x, player->y);
                if (visability)
                    cout << "R";
                else {
                    cout << " ";
                }
                return;
            }
            break;
        case 1:
            if (curPos.y+1 != board->size && board->board[curPos.x][curPos.y + 1] == 1) {
                set_cursor(player->x, player->y);
                if (visability)
                    cout << "R";
                else {
                    cout << " ";
                }
                return;
            }
            else if (curPos.y != 0 && board->board[curPos.x][curPos.y - 1] == 1) {
                set_cursor(player->x, player->y);
                if (visability)
                    cout << "R";
                else {
                    cout << " ";
                }
                return;
            }
            break;
        case 2:
            if (curPos.x + 1 != board->size && board->board[curPos.x + 1][curPos.y] == 1) {
                set_cursor(player->x, player->y);
                if (visability)
                    cout << "R";
                else {
                    cout << " ";
                }
                return;
            }
            else if (curPos.x != 0 && board->board[curPos.x - 1][curPos.y] == 1) {
                set_cursor(player->x, player->y);
                if (visability)
                    cout << "R";
                else {
                    cout << " ";
                }
                return;
            }
            break;
        case 3:
            if (curPos.y + 1 != board->size && board->board[curPos.x][curPos.y + 1] == 1 ) {
                set_cursor(player->x, player->y);
                if (visability)
                    cout << "R";
                else {
                    cout << " ";
                }
                return;
            }
            else if (curPos.y != 0 && board->board[curPos.x][curPos.y - 1] == 1) {
                set_cursor(player->x, player->y);
                if (visability)
                    cout << "R";
                else {
                    cout << " ";
                }
                return;
            }
            break;
        default:
            break;
        }


        while (!(curPos.x <= -1 || curPos.y <= -1 || curPos.x >= board->size || curPos.y >= board->size)) {
           
            if (nextPos.x != board->size && nextPos.y != board->size && nextPos.x != -1 && nextPos.y != -1 && board->board[nextPos.x][nextPos.y] == 1) {
                set_cursor(player->x, player->y);
                if (visability) {
                    cout << "H";
                }
                else {
                    cout << " ";
                }
                return;
            }

            switch (dir)
            {
            case 1:
                if (curPos.x +1 != board->size) {
                    if (curPos.y + 1 != board->size && board->board[curPos.x+1 ][curPos.y + 1] == 1) {
                        dir--;
                        dir = dir % 4;
                    }
                    if (curPos.y - 1 != -1 && board->board[curPos.x +1][curPos.y - 1] == 1) {
                        if (dir != 1) {
                            dir--;
                            dir = dir % 4;
                        }
                        else {
                            dir++;
                            dir = dir % 4;
                        }
                    }
                }
                break;
            case 2:
                if (curPos.y + 1 != board->size) {
                    if (curPos.x + 1 != board->size && board->board[curPos.x + 1][curPos.y + 1] == 1) {
                        dir++;
                        dir = dir % 4;
                    }
                    if (curPos.x - 1 != -1 && board->board[curPos.x - 1][curPos.y + 1] == 1) {
                        if (dir != 2) {
                            dir++;
                            dir = dir % 4;
                        }
                        else {
                            dir--;
                            dir = dir % 4;
                        }
                    }
                }
                break;
            case 3:
                if (curPos.x - 1 != -1) {
                    if (curPos.y + 1 != board->size && board->board[curPos.x - 1][curPos.y + 1] == 1) {
                        dir++;
                        dir = dir % 4;
                    }
                    if (curPos.y - 1 != -1 && board->board[curPos.x -1][curPos.y - 1] == 1) {
                        if (dir != 3) {
                            dir++;
                            dir = dir % 4;
                        }
                        else {
                            dir--;
                            dir = dir % 4;
                        }
                    }
                }
                break;
            case 0:
                if (curPos.y - 1 != -1) {
                    if (curPos.x + 1 != board->size && board->board[curPos.x + 1][curPos.y - 1] == 1) {
                        dir=3;
                        dir = dir % 4;
                    }
                    if (curPos.x - 1 != -1 && board->board[curPos.x - 1][curPos.y - 1] == 1) {
                        if (dir != 0) {
                            dir--;
                            dir = dir % 4;
                        }
                        else {
                            dir = 1;
                            dir = dir % 4;
                        }
                    }
                }
                break;

            default:
                break;
            }
            curPos += vec[dir];
            nextPos = curPos + vec[dir];
        }

        set_cursor(curPos.x + OFFSET_X, curPos.y + OFFSET_Y);
        if (visability) {
            cout << *sign;
         
        }
        else {
            cout << " ";
        
        }
        set_cursor(player->x, player->y);
        if (visability) {
            cout << *sign;
            *sign = *sign+1;
        }
        else {
            cout << " ";
            *sign = *sign - 1;
        }
    }
}

void add(Pos list[DEPTH],Pos pos) {
    for (int i = DEPTH - 1; i > 0; i--) {
        list[i] = list[i - 1];
    }
    list[0] = pos;
}

Pos pop(Pos list[DEPTH]) {
    Pos temp = list[0];
    for (int i = 0; i < DEPTH-1; i++) {
        list[i] = list[i + 1];
    }
    list[DEPTH - 1] = { -1,-1 };
    return temp;
}

void init(Pos list[DEPTH]) {
    Pos err{ -1,-1 };
    for (int i = 0; i < DEPTH; i++) {
        list[i] = err;
    }
}


int main() {
    srand(time(NULL));
    GameState stanGry = GameState::menu;
    Pos Undo[DEPTH];
    init(Undo);
    Pos Redo[DEPTH];
    init(Redo);
    int option = 0;
    Board* board = initBoard(5, 5);
    Pos player = { OFFSET_X,OFFSET_Y };
    Key Action = Key::none;
    Pos temp;
    Pos err = { -1,-1 };
    char sign = 'a';
    drawMenu();
    while (true) {
        switch (stanGry)
        {
        case GameState::play:
            Action = detect();
            switch (Action)
            {
            case Key::up:
                movecursor(&player, board->size, Action);
                break;
            case Key::left:
                movecursor(&player, board->size, Action);
                break;
            case Key::right:
                movecursor(&player, board->size, Action);
                break;
            case Key::down:
                movecursor(&player, board->size, Action);
                break;
            case Key::menu:
                stanGry = GameState::menu;
                system("cls");
                drawMenu();
                break;
            case Key::help:
                drawBoard(board, true);
                Sleep(HELP_TIME);
                drawBoard(board, false);
                set_cursor(player);
                break;
            case Key::place:
                if (player.x - OFFSET_X >= 0 && player.y - OFFSET_Y >= 0) {
                    if (board->board[player.x - OFFSET_X][player.y - OFFSET_Y] < 2) {
                        board->board[player.x - OFFSET_X][player.y - OFFSET_Y] += 2;
                    }
                    else {
                        board->board[player.x - OFFSET_X][player.y - OFFSET_Y] -= 2;
                    }
                    drawBoard(board, false);
                }
                break;
            case Key::undo:
                temp = pop(Undo);
                if (temp != err) {
                    shoot(&temp, board, false,&sign);
                    add(Redo, temp);
                }
                break;
            case Key::redo:
                temp = pop(Redo);
                if (temp != err) {
                    shoot(&temp, board, true,&sign);
                    add(Undo, temp);
                }
                break;
            case Key::quit:
                return 1;
                break;
            case Key::end:
                stanGry = GameState::ended;
                break;
            case Key::shoot:
                shoot(&player,board,true,&sign);
                add(Undo, player);
                break;
            case Key::none:
                break;
            }
            Sleep(50);
            break;
        case GameState::menu:
            cin >> option;
            switch (option)
            {
            case 1:
                system("cls");
                board = initBoard(5, 3);
                drawBoard(board,false);
                stanGry = GameState::play;
                player = { OFFSET_X,OFFSET_Y };
                movecursor(&player, board->size, Key::none);
                break;
            case 2:
                system("cls");
                board = initBoard(5, 5);
                drawBoard(board, false);
                stanGry = GameState::play;
                player = { OFFSET_X,OFFSET_Y };
                movecursor(&player, board->size, Key::none);
                break;
            case 3:
                system("cls");
                board = initBoard(5, 7);
                drawBoard(board, false);
                stanGry = GameState::play;
                player = { OFFSET_X,OFFSET_Y };
                movecursor(&player, board->size, Key::none);
                break;
            case 4:
                system("cls");
                board = initBoard(8, 5);
                drawBoard(board, false);
                stanGry = GameState::play;
                player = { OFFSET_X,OFFSET_Y };
                movecursor(&player, board->size, Key::none);
                break;
            case 5:
                system("cls");
                board = initBoard(10, 8);
                drawBoard(board, false);
                stanGry = GameState::play;
                player = { OFFSET_X,OFFSET_Y };
                movecursor(&player, board->size, Key::none);
                break;
            case 6:
                return 0;
                break;
            default:
                break;
            }
            break;
        case GameState::ended:
            drawBoard(board, 2);
            score(board);
            Sleep(1000);
            system("cls");
            drawMenu();
            stanGry = GameState::menu;
            break;
        default:
            break;
        }

    }
        return 0;
}
