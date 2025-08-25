#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

vector<string> read_file(string path){
    vector<string> lines;

    ifstream file(path);
    if (!file.good()){
        cerr << "Invalid file name: " << path << endl;
        return lines;
    }
    
    string l;
    while(getline(file, l)){
        lines.push_back(l);
    }

    
    file.close();
    return lines;
}

void separete(vector<string> &lines, map<int, vector<int>> &rules, vector<vector<int>> &check){
    bool toRule = true;
    for (auto line : lines){
        if (line == "") {
            toRule = false;
        } else if (toRule) {
            size_t sepIndex = line.find("|")+1;
            // cout << "Rule: " << line << endl;
            // cout << "\tIndex of sep: " << sepIndex << endl;
            int first = stoi(line);
            int second = stoi(line.substr(sepIndex));
            // cout << "First: " << first << "\tsecond: " << second << endl;

            rules[first].push_back(second);
        } else {
            int index = 0;
            int size = line.length();
            vector<int> values;
            // cout << "Line size: " << size << endl;
            while (1){
                size_t next;
                int value;
                try{
                    value= stoi(line.substr(index), &next);
                } catch(std::out_of_range){
                    break;
                }

                // cout << value << " : " << index << ", ";
                values.push_back(value);
                index += next + 1;
            }
            // cout << endl;
            check.push_back(values);
        }

    }

}

int get_center(vector<int> &in){
    int size = in.size();
    int center = size / 2;
    if (size % 2 == 0) {
        center++;
    }
    return in[center];
}

void print_rules(map<int, vector<int>> &rules){
    cout << "RULES:" << endl;
    for (auto rule : rules) {
        cout << rule.first << ":'\t";
        for (auto value : rule.second) {
            cout << value << ", ";
        }
        cout << endl;
    }
}

void print_line(vector<int> &line){
    for (auto value : line){
        cout << value << ", ";
    }
    cout << "\t:\tcenter: " << get_center(line) << endl;
}
void print_lines(vector<vector<int>> &lines){
    cout << "LINES:" << endl;
    for (auto line : lines){
        print_line(line);
    }
}

bool valid(vector<int> &rules, vector<int> &check, int checkIndex){
    for (int i = 0; i < checkIndex; i++) {
        if (find(rules.begin(), rules.end(), check[i]) != rules.end()){
            return false;
        }
    }
    return true;
}



int main(int argc, char* argv[]){
    vector<string> args(argv, argv+argc);

    if (argc < 2) {
        cerr << "Exept file" << endl;
        return 1;
    }

    auto lines = read_file(args[1]);
    if (lines.size() == 0) {
        return 1;
    }

    map<int, vector<int>> rules;
    vector<vector<int>> test;
    separete(lines, rules, test);

    // print_rules(rules);
    // print_lines(test);

    // cout << "CHECK:" << endl;
    int lines_size = test.size();
    int accum = 0;
    for (int y = 0; y < lines_size; y++){
        int size = test[y].size();
        bool valid_line;

        int i = 0;
        for (i = 1; i < size; i++){
            int value = test[y][i];
            valid_line = valid(rules[value], test[y], i);
            if (!valid_line) {
                break;
            }
        }

        // print_line(test[y]);
        // cout << "Valid: " << valid_line;
        // cout << "\tInvalid index: " << i << endl;
        if (valid_line) {
            accum += get_center(test[y]);
        }
    }
    cout << "Sum of corrent value: " << accum << endl;

    return 0;
}
