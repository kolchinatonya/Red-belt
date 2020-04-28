#include <iostream>
#include <iomanip>
#include <vector>
#include <utility>
#include <map>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

int64_t CURRENT_TIME;

struct Reservation {
    int64_t time_;
    int client_id_;
};

class HotelInfo {
public:
    void BookRoom(int client_id, int room_count) {
        UpdateQueue();
        reservations_.push({CURRENT_TIME, client_id});
        clients_room_count_[client_id] += room_count;
        room_count_ += room_count;
    }

    void UpdateQueue() {
        if (!reservations_.empty()) {
            int64_t time = reservations_.front().time_;
            while (!((CURRENT_TIME - 86400 < time) && (time <= CURRENT_TIME)) && (!reservations_.empty())) {
                int client_id = reservations_.front().client_id_;
                room_count_ -= clients_room_count_[client_id];
                clients_room_count_.erase(client_id);
                reservations_.pop();
                time = reservations_.front().time_;
            }
        }
    };

    int GetRoomsCount() {
        UpdateQueue();
        return room_count_;
    }

    int GetClientsCount() {
        UpdateQueue();
        return clients_room_count_.size();
    }

private:
    queue<Reservation> reservations_;
    int room_count_;
    map<int,int> clients_room_count_;
};

class BookingManager {
public:
    void Book(string hotel_name, int client_id, int room_count) {
        hotel_info_[hotel_name].BookRoom(client_id, room_count);
    }
    int GetClientsCount(string hotel_name) {
        return hotel_info_[hotel_name].GetClientsCount();
    };
    int GetRoomsCount(string hotel_name) {
        return hotel_info_[hotel_name].GetRoomsCount();
    };

private:
    map<string, HotelInfo> hotel_info_;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    BookingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) {
        string query_type, hotel_name;
        cin >> query_type;

        if (query_type == "BOOK") {
            int client_id, room_count;
            cin >> CURRENT_TIME >> hotel_name >> client_id >> room_count;
            manager.Book(hotel_name, client_id, room_count);
        } else if (query_type == "CLIENTS") {
            cin >> hotel_name;
            cout << manager.GetClientsCount(hotel_name) << '\n';
        } else if (query_type == "ROOMS") {
            cin >> hotel_name;
            cout << manager.GetRoomsCount(hotel_name) << '\n';
        }
    }

    return 0;
}
