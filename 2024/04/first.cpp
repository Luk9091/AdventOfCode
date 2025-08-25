#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>
#include <array>

class Position{
public:
    int x;
    int y;

    Position operator+(const Position& other) const {
        Position result;
        result.x = this->x + other.x;
        result.y = this->y + other.y;
        return result;
    }

    Position operator-(const Position& other) const {
        Position result;
        result.x = this->x - other.x;
        result.y = this->y - other.y;
        return result;
    }

    bool operator == (const Position& other) const {
        return (
            this->x == other.x &&
            this->y == other.y
        );
    }
};

static Position limit;

std::ostream& operator<< (std::ostream& out, const Position& pos){
    return out << "x: " << pos.x << ", y: " << pos.y;
}

std::array<Position, 8> near = {
    Position { 1,  0},
    Position { 1, -1},
    Position { 0, -1},
    Position {-1, -1},
    Position {-1,  0},
    Position {-1,  1},
    Position { 0,  1},
    Position { 1,  1},
};

std::array<char, 4> nextLetter = {
    'X',
    'M',
    'A',
    'S',
};


std::vector<std::string> readFile(std::ifstream &file){
    std::vector<std::string> lines;
    std::string line;

    
    while(std::getline(file, line)){
        lines.push_back(line);
        // std::cout << line << std::endl;
    }

    return lines;
}

static inline char getLetter(std::vector<std::string> &lines, Position pos){
    if (pos.x >= 0 && pos.y >= 0 && pos.x < limit.x && pos.y < limit.y)
        return lines[pos.y][pos.x];

    return '\x00';
}

static inline char getLetter(std::vector<std::string> &lines, int x, int y){
    return lines[y][x];
}

static inline bool findLetter(std::vector<std::string> &lines, char letter, Position pos){
    return getLetter(lines, pos) == letter;
}

static inline bool findLetter(std::vector<std::string> &lines, char letter, int x, int y){
    return getLetter(lines, x, y) == letter;
}


int findNextLetter(std::vector<std::string> &lines, Position direction, Position position, int letterIndex = 1){
    if (letterIndex == nextLetter.size())
        return 1;
    for(int i = 0; i < letterIndex; i++){
        std::cout << "\t";
    }
    std::cout << nextLetter[letterIndex] << std::endl;
    
    if (findLetter(lines, nextLetter[letterIndex], position)){
        return findNextLetter(lines, direction, position + direction, letterIndex + 1);
    }
    
    return 0;
}

static std::vector<std::string> loadFile(std::string _path){
    std::string path = "../" + _path;
    std::vector<std::string> lines;
    if (!std::filesystem::exists(path)){
        throw "File dont exist";
    }


    std::ifstream file(path);
    if (!file.good()){
        file.close();
        throw "File issue";
    }

    lines = readFile(file);
    file.close();

    if (lines.size() == 0 || lines[0].length() == 0){
        throw "Empty file";
    }



    return lines;
}



int main(){
    std::vector<std::string> lines;
    try {
        lines = loadFile("input.txt");
    } catch (const char* out){
        std::cerr << out << std::endl;
        return -1;
    }

    limit = {
    .x = (int)lines[0].length(),
    .y = (int)lines.size(),
    };


    std::cout << "Read file dim: x: " << limit.x << ", y: " << limit.y << std::endl;

    Position start;
    int sum = 0;
    for (start.y = 0; start.y < limit.y; start.y++){
        for (start.x = 0; start.x < limit.x; start.x++){
            if (findLetter(lines, nextLetter[0], start)){
                std::cout << "X pos: " << start << std::endl;
                int count = 0;
                for(int i = 0; i < 8; i++){
                    count += findNextLetter(lines, near[i], start + near[i]);
                }
                sum += count;

                std::cout << "Find new:  " << count << std::endl;
                std::cout << "Sum until: " << sum << std::endl;

            }
        }
    }

    std::cout << "Find words: " << sum << std::endl;
    


    return 0;
}