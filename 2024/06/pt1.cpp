#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <thread>

#define DELTA_TIME (200ms)


int teren_width;
int teren_height;


using namespace std;

enum DIRECTION{
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

struct guard_t {
    char c;
    int x;
    int y;
    DIRECTION dir;
};

void load_map(vector<vector<char>> &teren, guard_t &guard , string path){
    ifstream file(path);

    if (!file.good()){
        throw "Invalid file";
    }

    string line;
    int y = 0;
    while(getline(file, line)) {
        int x = 0;
        vector<char> y_line;
        for (char c : line) {
            if (c == '^') {
                guard.x = x;
                guard.y = y;
                guard.dir = UP;
                guard.c = '^';

                y_line.push_back('.');
            } else {
                y_line.push_back(c);
            }
            x++;
        }
        teren.push_back(y_line);
        y++;
    }
    teren_width  = teren[0].size();
    teren_height = teren.size();
}

void print_map(vector<vector<char>> &teren, guard_t &guard){
    int y_pos = 0;
    for (auto y : teren) {
        int x_pos = 0;
        for (auto x : y) {
            if (x_pos == guard.x && y_pos == guard.y){
                cout << guard.c;
            } else {
                cout << x;
            }
            x_pos++;
        }
        cout << endl;
        y_pos++;
    }
    cout << "Guard position: " << guard.x << ", " << guard.y << " dir: " << guard.dir << endl;
    cout << "Teren size: " << teren_width << ", " << teren_height << endl;
}

void print_mapAndVisit(vector<vector<char>> &teren, guard_t &guard, vector<vector<bool>> &visited){
    int y_pos = 0;
    for (auto y : teren) {
        int x_pos = 0;
        for (auto x : y) {
            if (x_pos == guard.x && y_pos == guard.y){
                cout << guard.c;
            } else {
                if (visited[y_pos][x_pos]){
                    cout << 'X';
                } else {
                    cout << x;
                }
            }
            x_pos++;
        }
        cout << endl;
        y_pos++;
    }
    cout << "Guard position: " << guard.x << ", " << guard.y << " dir: " << guard.dir << endl;
    cout << "Teren size: " << teren_width << ", " << teren_height << endl;
}

void clear_console(){
    cout << "\e[1;1H\e[2J" << endl;
}

bool isLeftTeren(guard_t &guard){
    return (
        guard.x < 0 || guard.x >= teren_width ||
        guard.y < 0 || guard.y >= teren_height
    );
}


void move(guard_t &guard){
    switch (guard.dir){
        case UP:{
            guard.y--;
        }break;
        case RIGHT:{
            guard.x++;
        }break;
        case DOWN:{
            guard.y++;
        }break;
        case LEFT:{
            guard.x--;
        }break;
    }
}

void backwordAndRotate(guard_t &guard){
    switch (guard.dir){
        case UP:{
            guard.y++;
            guard.dir = RIGHT;
            guard.c='>';
        }break;
        case RIGHT:{
            guard.x--;
            guard.dir = DOWN;
            guard.c='v';
        }break;
        case DOWN:{
            guard.y--;
            guard.dir = LEFT;
            guard.c='<';
        }break;
        case LEFT:{
            guard.x++;
            guard.dir = UP;
            guard.c='^';
        }break;
    }
}

bool colision(vector<vector<char>> &teren, guard_t &guard) {
    return teren[guard.y][guard.x] == '#';
}

int countVisited(vector<vector<bool>> &visited) {
    int count = 0;

    for (auto y: visited) {
        for (auto x: y) {
            if (x) {
                count++;
            }
        }
    }

    return count;
}

void initVisitedGrid(vector<vector<bool>> &visited){
    vector<bool> line;

    for (int i = 0; i < teren_width; i++){
        line.push_back(false);
    }
    for (int i = 0; i < teren_height; i++){
        visited.push_back(line);
    }
}



int main(int argc, char* argv[]){
    bool DEBUG=false;
    vector<string> args(argv, argv+argc);
    vector<vector<char>> teren;
    guard_t guard;

    
    if (argc > 2) {
        if (args[2] == "-d")
            DEBUG = true;
    }


    load_map(teren, guard, args[1]);

    vector<vector<bool>> visited;
    initVisitedGrid(visited);

    while(1){
        visited[guard.y][guard.x] = true;
        move(guard);
        if (isLeftTeren(guard)){
            cout << "Left!" << endl;
            break;
        }

        if (colision(teren, guard)){
            backwordAndRotate(guard);
        }


        if (DEBUG){
            clear_console();
            print_map(teren, guard);
            std::this_thread::sleep_for(DELTA_TIME);
        }
    }

    print_mapAndVisit(teren, guard, visited);
    cout << "Visited: " << countVisited(visited) << endl;

    return 0;
}
