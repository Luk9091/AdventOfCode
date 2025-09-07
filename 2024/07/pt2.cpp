#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;
#define uint long long

enum OPERATION{
    ADD,
    MUL,
    CON,
};

vector<vector<uint>> load_file(string path){
    vector<vector<uint>> lines;
    
    ifstream file(path);
    if (!file.good()){
        cerr << "Invalid path!" << endl;
        return lines;
    }

    string line;
    while(getline(file, line)){
        uint index = 0;
        vector<uint> numbers;
        while (index <= line.size()){
            uint value;
            size_t newIndex;
            try{
                value = stol(line.substr(index), &newIndex);
            } catch (...){
                index++;
                continue;
            }


            index += newIndex + 1;
            numbers.push_back(value);
        }
        lines.push_back(numbers);
    }

    
    file.close();
    return lines;
}

void print_line(vector<uint> &line){
    for (auto number : line){
        cout << number << ", ";
    }
}

void print_lines(vector<vector<uint>> &lines){
    for (auto line : lines){
        print_line(line);
        cout << endl;
    }
}

void print_operation(vector<OPERATION> &operations){
    for (auto oper : operations){
        switch (oper){
            case ADD: cout << "+"; break;
            case MUL: cout << "*"; break;
            case CON: cout << "||"; break;
        }
        cout << " ";
    }
}


vector<OPERATION> createOperationList(vector<uint> line){
    uint operationCount = line.size() - 2;
    
    vector<OPERATION> operation;
    for (uint i = 0; i < operationCount; i++){
        operation.push_back(ADD);
    }

    return operation;
}

bool nextOperation(vector<OPERATION> &operations){
    for (uint i = 0; i < operations.size(); i++){
        switch (operations[i]){
            case ADD: operations[i] = MUL; return true;
            case MUL: operations[i] = CON; return true;
            case CON: operations[i] = ADD; break;
        }
    }
    return false;
}

uint valid(vector<uint> &numbers, vector<OPERATION> &operations){
    uint result = numbers[1];

    for (uint i = 2; i < numbers.size(); i++){
        switch (operations[i-2]){
            case ADD: result = result + numbers[i]; break;
            case MUL: result = result * numbers[i]; break;
            case CON: {
                    string r = to_string(result);
                    string n = to_string(numbers[i]);
                    r = r + n;
                    result = stol(r);
            } break;

        }
    }
    
    return result;
}



int main(int argc, char* argv[]){
    vector<string> args(argv, argv + argc);

    auto lines = load_file(args[1]);
    uint sum = 0;
    for (auto line : lines){
        auto operations = createOperationList(line);
        do {
            uint result = valid(line, operations);

            if (result == line[0]){
                print_line(line);
                cout << endl;

                cout << "\t";
                print_operation(operations);
                cout << "\tresult: " << result;
                cout << endl;
                sum += result;
                break;
            }
        } while (nextOperation(operations));
    }

    cout << "Accum: " << sum << endl;

    return 0;
}
