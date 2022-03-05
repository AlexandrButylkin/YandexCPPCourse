#include <sstream>
#include <exception>

#include "Parser.h"


using std::string_view;

double DoubleFromString(std::string_view str){
    size_t pos;
    const double result = stod(std::string(str), &pos);
    if (pos != str.length()) {
        std::stringstream error;
        error << "string " << str << " contains " << (str.length() - pos) << " trailing chars(Double)";
        throw std::invalid_argument(error.str());
    }
    return result;
}

size_t IntFromString(std::string_view str){
    size_t pos;
    const size_t result = stoi(std::string(str), &pos);
    if (pos != str.length()) {
        std::stringstream error;
        error << "string " << str << " contains " << (str.length() - pos) << " trailing chars(INT)";
        throw std::invalid_argument(error.str());
    }
    return result;
}

std::pair<string_view, std::optional<string_view>> SplitTwo(string_view str, string_view delimiter){
    const size_t pos = str.find(delimiter);
    if(pos == string_view::npos){
        return {str, std::nullopt};
    } else {
        return {str.substr(0, pos), str.substr(pos + delimiter.length())};
    }
}

size_t ReadCountRequests(std::istream& is){
    size_t res;
    is >> res;
    std::string dummy;
    getline(is, dummy);
    return res;
}


std::string_view ReadWord(std::string_view& str, std::string_view delimiter){
    const auto [left, right] = SplitTwo(str, delimiter);
    if(right){
        str = right.value();
    } else {
        str = "";
    }
    return left;
}

std::string_view InitDelimit(std::string_view& str){
    size_t pos = str.find(' ');
    while(pos != std::string_view::npos){
        if(str[pos + 1] == '>' || str[pos + 1] == '-') return str.substr(pos, 3);
        pos = str.find(' ', pos + 1);
    }
    return " ";
}

std::pair<Route::RouteType, std::vector<std::string>> StopsFromString(std::string_view& str){
    std::vector<std::string> result;
    std::string_view delimiter = InitDelimit(str);
    std::string_view stop = ReadWord(str, delimiter);
    while(!stop.empty()){
        result.emplace_back(std::string(stop));
        stop = ReadWord(str, delimiter);
    }
    return {delimiter == " > " ? Route::RouteType::CIRCLE : Route::RouteType::LINEAR,
            result};
}

std::optional<Request::RequestType> TypeRequestFromString(std::string_view str){
    if(str == "Stop"){
        return Request::RequestType::STOP;
    } else if (str == "Bus"){
        return Request::RequestType::BUS;
    } else return std::nullopt;
}
