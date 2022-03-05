//
// Created by cobak on 11.01.2022.
//

#ifndef TASK_6_HTTP_REQUEST_H
#define TASK_6_HTTP_REQUEST_H

#include <string_view>
using namespace std;

struct HttpRequest {
    string_view method, uri, protocol;
};

#endif //TASK_6_HTTP_REQUEST_H
