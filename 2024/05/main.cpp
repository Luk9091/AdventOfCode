#include <iostream>
#include <fstream>
#include <filesystem>
#include <map>
#include <vector>



std::map<int, std::vector<int>> rules;
std::vector<std::vector<int>> lines;


void addRule(std::string& line){
    int first, second;

    int splitIndex = line.find('|');
    first = std::stoi(line);
    second = std::stoi(line.substr(splitIndex+1));

    rules[first].push_back(second);
}

void addLine(std::string& line){
    std::vector<int> numbers;

    int commaIndex = -1;
    do{
        int value = std::stoi(line.substr(commaIndex + 1));
        numbers.push_back(value);
        commaIndex = line.find_first_of(',', commaIndex + 1);
    }while(commaIndex > 0);

    lines.push_back(numbers);
}

void readFile(std::string path){
    path = "../" + path;
    if(!std::filesystem::exists(path)){
        throw "File dont exist";
    }

    std::ifstream file(path);
    if (!file.good()){
        file.close();
        throw "File issue";
    }
    
    std::string line;

    bool rules = true;
    while (std::getline(file, line)){
        if (line == "") {
            rules = false;
            continue;
        }

        if (rules){
            addRule(line);
        } else {
            addLine(line);
        }
    }

}

void displayRules(){
    for (auto key : rules){
        std::cout << key.first << " : ";
        for (auto value : rules[key.first]) {
            std::cout << value << ", ";
        }
        std::cout << std::endl;
    }
}
void displayNumbers(){
    for (auto numbers : lines){
        for (auto value : numbers){
            std::cout << value <<", ";
        }
        std::cout << std::endl;
    }
}

void displayLine(std::vector<int> &line){
    for (auto value : line){
        std::cout << value << ", ";
    };
    std::cout << std::endl;
}

int findInVec(std::vector<int>& vec, int value, int end = 0, int start = 0){
    for (int i = start; i < end ; i++){
        if (vec[i] == value){
            return i;
        }
    }
    return -1;
}


bool findIssue(int lineNumber){
    auto line = lines[lineNumber];

    for (int i = 0; i < line.size(); i++){
        int test = line[i];
        for (auto rule : rules[test]){
            if(findInVec(line, rule, i) >= 0){
                return true;
            }
        }
    }
    return false;
}


int getCenter(std::vector<int>& line){
    int centerIndex = line.size() / 2;
    return line[centerIndex];
}


std::vector<int> sort(int index){
}





int main(){
    std::cout << "Hello world!" << std::endl;

    try {
        readFile("example.txt");
    } catch (const char *out){
        std::cerr << out << std::endl;
        return 1;
    }

    
    // for (auto key : rules){
    //     std::sort(rules[key.first].begin(), rules[key.first].end());
    // }

    int correctSum = 0;
    int issueSum = 0;
    for (int i = 0; i < lines.size(); i++){
        if(findIssue(i)){
            // TASK 2:
            auto sortLine = sort(i);
            std::cout << "Issue in line: " << i << std::endl;
            displayLine(lines[i]);
            displayLine(sortLine);

        } 
        // else { /* TASK 1: */
        //     int center = getCenter(lines[i]);
        //     std::cout << "Line: " << i << "\tcenter: " << center << std::endl;;
        //     correctSum += center;
        // }
    }





    // std::cout << "Correct sum: " << correctSum << std::endl;;
    std::cout << "Issue   sum: " << issueSum << std::endl;;
    // displayRules();
    // displayNumbers();

    return 0;
}