#include <algorithm>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <set>


using namespace std;

class Learner {
private:
    set<string> dict;

public:
    int Learn(const vector<string>& words) {
        int oldWords = dict.size();
        for (const auto& word : words) {
                dict.insert(word);
            }
        return dict.size() - oldWords;
    }

    vector<string> KnownWords() {
        vector<string> res;
        res.insert(res.end(), dict.begin(), dict.end());
        return res;
    }
};

//int main() {
//    Learner learner;
//    string line;
//    while (getline(cin, line)) {
//        vector<string> words;
//        stringstream ss(line);
//        string word;
//        while (ss >> word) {
//            words.push_back(word);
//        }
//        cout << learner.Learn(words) << "\n";
//    }
//    cout << "=== known words ===\n";
//    for (auto word : learner.KnownWords()) {
//        cout << word << "\n";
//    }
//}