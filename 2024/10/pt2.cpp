#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Point{
public:
    int x;
    int y;

    Point(int x, int y){
        this->x = x;
        this->y = y;
    }

    bool operator==(const Point &right) const {
        return (x == right.x && y == right.y);
    }

};

vector<vector<int>> readFile(string path){
    ifstream file(path);

    if(!file.good()){
        cerr << "Invalid file name" << endl;
        exit(2);
    }

    vector<vector<int>> teren;
    string line;
    while (getline(file, line)){
        vector<int> y;
        for (char c : line){
            if (c == '.')
                y.push_back(-1);
            else
                y.push_back(c-'0');
        }
        teren.push_back(y);
    }

    return teren;
}

vector<Point> findStartPosition(vector<vector<int>> &teren){
    vector<Point> start;
    for (int y = 0; y < teren.size(); y++){
        for (int x = 0; x < teren.size(); x++){
            if (teren[y][x] == 0)
                start.push_back(Point(x, y));
        }
    }

    return start;
}

int gotoNext(const vector<vector<int>> &teren, int x, int y, vector<Point> &visit){
    int currentPosition = teren[y][x];
    if (currentPosition == 9) {
        Point point(x, y);
        if (find(visit.begin(), visit.end(), point) == visit.end()){
            visit.push_back(point);
        }

        return 1;
    }
    int score = 0;

    int next;

    if (y+1 < teren.size()){
        next = teren[y+1][x];
        if (next == currentPosition + 1) score += gotoNext(teren, x, y+1, visit);
    }

    if (y-1 >= 0){
        next = teren[y-1][x];
        if (next == currentPosition + 1) score += gotoNext(teren, x, y-1, visit);
    }

    if (x+1 < teren[0].size()){
        next = teren[y][x+1];
        if (next == currentPosition + 1) score += gotoNext(teren, x+1, y, visit);
    }

    if (x-1 >= 0){
        next = teren[y][x-1];
        if (next == currentPosition + 1) score += gotoNext(teren, x-1, y, visit);
    }
    // cout << "Current check: x: " << x << ", y: " << y << " : " << currentPosition << "\tscore: " << score << endl;

    return score;
}

void print_teren(vector<vector<int>> &teren){
    for (auto y: teren){
        for (auto x: y){
            if (x == -1)
                cout << '.';
            else
                cout << x;
        }
        cout << endl;
    }
}
void print_points(vector<Point> &points){
    cout << "Start pos" << endl;
    for (auto point : points){
        cout << "\tx: " << point.x << ", y: " << point.y << endl;
    }
}

int main(int argc, char *argv[]){
    vector<string> args(argv, argv+argc);
    auto teren = readFile(args[1]);
    auto starts = findStartPosition(teren);

    print_teren(teren);

    int score = 0;
    int pathScore = 0;
    vector<Point> visit;
    for (Point start : starts){
        pathScore += gotoNext(teren, start.x, start.y, visit);
        score += visit.size();

    
        cout << "x: " << start.x << ", y: " << start.y << endl;
        print_points(visit);
        visit.clear();
    }
    cout << "Score: " << score << endl;
    cout << "Paths: " << pathScore << endl;

    return 0;
}
