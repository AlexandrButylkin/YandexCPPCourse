//
// Created by cobak on 11.01.2022.
//

#include "stats.h"

void Stats::AddMethod(string_view method){
    if(method == "GET") ++methods["GET"];
    else if(method == "PUT") ++methods["PUT"];
    else if(method == "POST") ++methods["POST"];
    else if(method == "DELETE")++methods["DELETE"];
    else ++methods["UNKNOWN"];
}

void Stats::AddUri(string_view uri) {
    if(uri == "/") ++URLs["/"];
    else if(uri == "/order") ++URLs["/order"];
    else if(uri == "/product") ++URLs["/product"];
    else if(uri == "/basket") ++URLs["/basket"];
    else if(uri == "/help") ++URLs["/help"];
    else ++URLs["unknown"];
}

HttpRequest ParseRequest(string_view line){
    line.remove_prefix(std::min(line.find_first_not_of(' '), line.size()));
    HttpRequest req;

    auto space = line.find(' ', 0);
    req.method = line.substr(0, space);
    line.remove_prefix(space + 1);

    space = line.find(' ', 0);
    req.uri = line.substr(0, space);
    line.remove_prefix(space + 1);

    space = line.find(' ', 0);
    req.protocol = line.substr(0, space);
    line.remove_prefix(space + 1);

    return req;
}