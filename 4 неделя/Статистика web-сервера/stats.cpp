#include "stats.h"

array<string, METHODS_COUNT> Stats::methods = {"GET", "POST", "PUT", "DELETE", "UNKNOWN"};
array<string, URLS_COUNT> Stats::urls = {"/", "/order", "/product", "/basket", "/help", "unknown"};

Stats::Stats() {
    for (const auto& method : methods) {
        method_stats[method] = 0;
    }

    for (const auto& url : urls) {
        url_stats[url] = 0;
    }
}

vector<string_view> splitSV(string_view strv, string_view delims = " ") {
    vector<string_view> output;
    size_t first = 0;
    while (first < strv.size()) {
        const auto second = strv.find_first_of(delims, first);
        if (first != second)
            output.emplace_back(strv.substr(first, second - first));
        if (second == string_view::npos)
            break;
        first = second + 1;
    }
    return output;
}

HttpRequest ParseRequest(string_view line) {
    HttpRequest res;
    vector<string_view> words = splitSV(line);
    res.method = words[0];
    res.uri = words[1];
    res.protocol = words[2];
    return res;
}


void Stats::AddMethod(string_view method) {
    auto it = find(methods.begin(), methods.end(), method);
    method = (it == Stats::methods.end()) ? Stats::methods[METHODS_COUNT - 1] : *it;
    ++method_stats[method];
}

void Stats::AddUri(string_view uri) {
    auto it = find(Stats::urls.begin(), Stats::urls.end(), uri);
    uri = (it == Stats::urls.end()) ? Stats::urls[URLS_COUNT - 1] : *it;
    ++url_stats[uri];
}

const map<string_view, int> &Stats::GetMethodStats() const {
    return method_stats;
}

const map<string_view, int> &Stats::GetUriStats() const {
    return url_stats;
}

