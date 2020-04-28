#pragma once

#include "http_request.h"

#include <string_view>
#include <vector>
#include <string>
#include <map>
#include <array>
#include <algorithm>

#define METHODS_COUNT 5
#define URLS_COUNT 6
#define PROTOCOLS_COUNT 2

using namespace std;

class Stats {
public:
    Stats();

    void AddMethod(string_view method);
    void AddUri(string_view uri);
    const map<string_view, int>& GetMethodStats() const;
    const map<string_view, int>& GetUriStats() const;

private:
    static array<string, METHODS_COUNT> methods;
    static array<string, URLS_COUNT> urls;
    map<string_view, int> method_stats;
    map<string_view, int> url_stats;

};


HttpRequest ParseRequest(string_view line);