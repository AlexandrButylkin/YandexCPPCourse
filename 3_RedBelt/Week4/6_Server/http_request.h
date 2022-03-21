#ifndef TASK_6_HTTP_REQUEST_H
#define TASK_6_HTTP_REQUEST_H

#include <string_view>
using namespace std;

struct HttpRequest {
    string_view method, uri, protocol;
};

std::string_view ReadWord(std::string_view& line);
HttpRequest ParseRequest(string_view line);

#endif //TASK_6_HTTP_REQUEST_H
