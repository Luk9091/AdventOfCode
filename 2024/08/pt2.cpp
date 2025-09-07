#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>


using namespace std;

class point_t {
public:
    int x;
    int y;

    point_t(int x, int y){
        this->x = x;
        this->y = y;
    }

    bool operator==(const point_t &right) const {
        return (x == right.x && y == right.y);
    }
};

vector<string> readMap(string path){
    ifstream file(path);

    if (!file.good()){
        cerr << "Missing file" << endl;
        exit(2);
    }

    vector<string> teren;
    string line;
    while(getline(file, line)){
        teren.push_back(line);
    }

    file.close();
    return teren;
}


void print_teren(vector<string> &teren){
    for (auto line : teren){
        cout << line << endl;
    }
}

map<char, vector<point_t>> find_nodes(vector<string> &teren){
    map<char, vector<point_t>> nodes;

    int width = teren[0].size();
    int height = teren.size();
    
    for (int y = 0; y < height; y++){
        for (int x = 0; x < width; x++){
            if (teren[y][x] == '.') continue;
            
            point_t point(x ,y);
            nodes[teren[y][x]].push_back(point);
        }
    }

    return nodes;
}

void print_nodes(map<char, vector<point_t>> &nodes){
    for (const auto &[node, points] : nodes){
        cout << "Node: " << node << ": " << endl;
        for (point_t point : points){
            cout << "\t" << point.x << ", " << point.y << endl;
        }
    }
}


vector<point_t> find_antinodes(vector<string> &teren, map<char, vector<point_t>> &nodes, int width, int height){
    vector<point_t> antinodes;
    
    for (const auto &[node, points]: nodes){
        int numOfPoints = points.size();

        for (int i = 0; i < numOfPoints; i++){
            point_t current = points[i];

            for (int j = 0; j < numOfPoints; j++){
                if (j == i) continue;

                point_t next = points[j];
                int dx = next.x - current.x;
                int dy = next.y - current.y;

                point_t newPoint(current.x + dx, current.y + dy);

                while(!(newPoint.x < 0 || newPoint.y < 0 || newPoint.x >= width || newPoint.y >= height)){
                    if (find(antinodes.begin(), antinodes.end(), newPoint) == antinodes.end()){
                        antinodes.push_back(newPoint);
                    }
                    newPoint.x = newPoint.x + dx;
                    newPoint.y = newPoint.y + dy;
                }
            }
        }

    }


    return antinodes;
}

void print_antinodes(const vector<point_t> &antinodes){
    cout << "Antinodes:" << endl;
    for (point_t point : antinodes){
        cout << "\t" << point.x << ", " << point.y << endl;
    }
}

void add_antinodes(vector<string> &teren, const vector<point_t> &antinodes){
    for (auto point : antinodes){
        teren[point.y][point.x] = '#';
    }
}



int main(int argc, char *argv[]){
    vector<string> args(argv, argv+argc);
    
    auto teren = readMap(args[1]);
    auto nodes = find_nodes(teren);
    print_teren(teren);

    int width = teren[0].size();
    int height = teren.size();
    auto antinodes = find_antinodes(teren, nodes, width, height);



    print_nodes(nodes);
    print_antinodes(antinodes);
    cout << "Antinodes cout: " << antinodes.size() << endl;

    add_antinodes(teren, antinodes);
    print_teren(teren);




    return 0;
}
