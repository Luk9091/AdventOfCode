#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void readFile(string path){
    ifstream file(path);

    if(!file.good()){
        cerr << "Invalid file name" << endl;
        exit(2);
    }
}

int main(int argc, char *argv[]){
    vector<string> args(argv, argv+argc);


    return 0;
}
