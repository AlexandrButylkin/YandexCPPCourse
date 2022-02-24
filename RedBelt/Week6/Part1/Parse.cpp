#include "parse.h"

using std::string_view;
using std::vector;

string_view Strip(string_view s) {
    while (!s.empty() && isspace(s.front())) {
        s.remove_prefix(1);
    }
    while (!s.empty() && isspace(s.back())) {
        s.remove_suffix(1);
    }
    return s;
}

vector<string_view> SplitBy(string_view s, char sep) {
    vector<string_view> result;
    while (!s.empty()) {
        size_t pos = s.find(sep);
        result.push_back(s.substr(0, pos));

        if(pos != std::string_view::npos){
            s.remove_prefix(pos + 1);
        } else s.remove_prefix(s.size());
    }
    return result;
}
