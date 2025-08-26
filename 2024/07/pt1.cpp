#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<vector<int>> load_file(string path){
    vector<vector<int>> lines;
    
    ifstream file(path);
    if (!file.good()){
        cerr << "Invalid path!" << endl;
        return lines;
    }

    
    file.close();
    return lines;
}


int main(int argc, char* argv[]){
    vector<string> args(argv, argv + argc);

    auto lines = load_file(args[1]);

    return 0;
}
