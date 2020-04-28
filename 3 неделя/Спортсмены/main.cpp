#include <iostream>
#include <list>
#include <algorithm>
#include <map>

using namespace std;

list<int> sportsmen;
map<int, list<int>::iterator> sportsmen_map;

void SetSportsman(int number, int prev_number) {
    list<int>::iterator find_iter;
    try {
        find_iter = sportsmen_map.at(prev_number);
    }
    catch (exception& ex) {
        find_iter = sportsmen.end();
    }
    sportsmen_map[number] = sportsmen.insert(find_iter, number);
}

int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        int number, prev_number;
        cin >> number >> prev_number;
        SetSportsman(number, prev_number);
    }
    for (auto sportsman : sportsmen) {
        cout << sportsman << ' ';
    }
    return 0;
}