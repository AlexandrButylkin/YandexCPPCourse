#include "http_request.h"

std::string_view ReadWord(std::string_view& line){
    auto pos = line.find_first_not_of(' ');
    line.remove_prefix(pos != std::string_view::npos ? pos : line.size());

    pos = line.find(' ');
    auto result = line.substr(0, pos);
    line.remove_prefix(pos != std::string_view::npos ? pos : line.size());
    return result;
}

HttpRequest ParseRequest(string_view line){
    auto method = ReadWord(line);
    auto uri = ReadWord(line);
    auto protocol = ReadWord(line);
    return {method, uri, protocol};
}