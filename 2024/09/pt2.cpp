#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<long long> readFile(string path){
    ifstream file(path);

    if(!file.good()){
        cerr << "Invalid file name" << endl;
        exit(2);
    }

    string line;
    getline(file, line);

    vector<long long> disk_map;
    for (char c : line){
        disk_map.push_back(c -'0');
    }

    return disk_map;
}

void print_disk_map(vector<long long> &disk_map){
    for (long long value : disk_map){
        cout << value;
    }
    cout << endl;
}

vector<long long> decode_map(vector<long long> &disk_map){
    vector<long long> decoded;

    long long sector = 0;
    for (long long i = 0; i < disk_map.size(); i++){
        for (long long j = 0; j < disk_map[i]; j++){
            if (i%2 == 0) {
                decoded.push_back(sector);
            } else {
                decoded.push_back(-1);
            }
        }

        if (i%2 == 0) sector++;
    }

    return decoded;
}

void print_decode_disk(vector<long long> &decoded){
    for (long long value : decoded){
        if (value >= 0){
            cout << value;
        } else {
            cout << ".";
        }
    }
    cout << endl;

}

int find_block_begin(vector<long long> &decoded, long long index){
    int size = 0;
    long long element = decoded[index];

    for (int i = index; i > 0; i--){
        if (element != decoded[i]) break;
        size++;
    }

    return size;
}

int find_block_end(vector<long long> &decoded, long long index){
    int size = 0;
    long long element = decoded[index];

    for (int i = index; i < decoded.size(); i++){
        if (element != decoded[i]) break;
        size++;
    }
    return size;
}

void compres(vector<long long> &decoded){
    long long last = decoded.size() - 1;

    while (last > 1){
//        print_decode_disk(decoded);
        long long tail_size = find_block_begin(decoded, last);
        if (decoded[last] == -1){
            last -= tail_size;
            continue;
        }

        long long i = 0;
        while (i < last - tail_size){
            long long head_size = find_block_end(decoded, i);
            if (decoded[i] >= 0) {
                i += head_size;
                continue;
            }

            if (head_size >= tail_size){
                for (long long j = 0; j < tail_size; j++){
                    decoded[i+j] = decoded[last-j];
                    decoded[last-j] = -1;
                }
                break;
            }
            i += head_size;
        }

        last -= tail_size;
    }

}

long long checkSum(vector<long long> &decoded){
    long long sum = 0;

    for (long long i = 0; i < decoded.size(); i++){
        if (decoded[i] != -1)
            sum += i*decoded[i];
    }

    return sum;
}

int main(int argc, char *argv[]){
    vector<string> args(argv, argv+argc);

    vector<long long> disk_map = readFile(args[1]);
    print_disk_map(disk_map);

    vector<long long> decoded = decode_map(disk_map);
    print_decode_disk(decoded);
    
    compres(decoded);
    print_decode_disk(decoded);
    cout << "Check sum: " << checkSum(decoded) << endl;

    return 0;
}
