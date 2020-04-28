#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>

using namespace std;

class ReadingManager {
public:
    void Read(int user_id, int page_count) {
        if (user_page_counts_[user_id] == 0) {
            users_count_++;
        } else {
            page_users_count_[user_page_counts_[user_id]].erase(user_id);
            if (page_users_count_[user_page_counts_[user_id]].empty())
                page_users_count_.erase(user_page_counts_[user_id]);
        }
        user_page_counts_[user_id] = page_count;
        page_users_count_[page_count].insert(user_id);
    }

    double Cheer(int user_id) const {
        int page_count;
        try {
            page_count = user_page_counts_.at(user_id);
        }
        catch (exception &ex) {
            return 0;
        }
        const int user_count = GetUserCount();
        if (user_count == 1)
            return 1;
        int position = 0;
        for (const auto &it : page_users_count_) {
            if (it.first != page_count)
                position += it.second.size();
            else
                break;
        }
        return position * 1.0 / (user_count - 1);
    }

private:
    map<int, int> user_page_counts_;
    map<int, set<int>> page_users_count_;
    int users_count_ = 0;
    int GetUserCount() const {
        return users_count_;
    }
};

int main() {
    // Для ускорения чтения данных отключается синхронизация
    // cin и cout с stdio,
    // а также выполняется отвязка cin от cout
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ") {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER") {
            cout << setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}