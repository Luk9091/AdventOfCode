#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

enum DIRECTION{
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

struct guard_t {
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
    int x = 0;
    int y = 0;
    while(getline(file, line)) {
        vector<char> y_line;
        for (char c : line) {
            if (c == '^') {
                guard.x = x;
                guard.y = y;
                guard.dir = UP;

                y_line.push_back('.');
            } else {
                y_line.push_back(c);
            }
            x++;
        }
        teren.push_back(y_line);
        y++;
    }
}

void print_map(vector<vector<char>> &teren, guard_t guard){
    int x_pos = 0;
    int y_pos = 0;
    for (auto y : teren) {
        for (auto x : y) {
            if (x_pos == guard.x && y_pos == guard.y){
                cout << "^";
            } else {
                cout << x;
            }
            x_pos++;
        }
        cout << endl;
        y_pos++;
    }
    cout << "Guard position: " << guard.x << ", " << guard.y << " dir: " << guard.dir << endl;
}


int main(int argc, char* argv[]){
    vector<string> args(argv, argv+argc);
    vector<vector<char>> teren;
    guard_t guard;


    load_map(teren, guard, args[1]);
    print_map(teren, guard);


    return 0;
}
