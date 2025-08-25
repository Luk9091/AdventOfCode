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
    Position { 1, -1},
    Position {-1, -1},
    Position {-1,  1},
    Position { 1,  1},
};

std::array<char, 4> nextLetter = {
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


int findCross(std::vector<std::string> &lines, Position center){
    int correct = 0;

    for (int i = 0; i < near.size() / 2; i++){
        if (findLetter(lines, 'M', center + near[i])){
            if (findLetter(lines, 'S', center + near[i+2])){
                correct++;
            }
        } else if (findLetter(lines, 'S', center + near[i])){
            if (findLetter(lines, 'M', center + near[i+2])){
                correct++;
            }
        }
    }

    if (correct == 2){
        return 1;
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
    for (start.y = 1; start.y < limit.y - 1; start.y++){
        for (start.x = 1; start.x < limit.x - 1; start.x++){
            if (findLetter(lines, 'A', start)){
                std::cout << "X pos: " << start << std::endl;
                int count = 0;
                count += findCross(lines, start);
                sum += count;

                std::cout << "Find new:  " << count << std::endl;
                std::cout << "Sum until: " << sum << std::endl;

            }
        }
    }

    std::cout << "Find words: " << sum << std::endl;
    


    return 0;
}