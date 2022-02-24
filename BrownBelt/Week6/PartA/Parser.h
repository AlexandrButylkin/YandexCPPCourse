#ifndef PARTA_PARSER_H
#define PARTA_PARSER_H

#include <vector>
#include <memory>
#include <optional>

#include "Requests.h"
#include "Database.h"

double DoubleFromString(std::string_view str);
size_t IntFromString(std::string_view str);
std::optional<Request::RequestType> TypeRequestFromString(std::string_view str);

size_t ReadCountRequests(std::istream &is);

std::pair<std::string_view, std::optional<std::string_view>>
SplitTwo(std::string_view str, std::string_view delimiter = " ");

std::string_view ReadWord(std::string_view &str, std::string_view delimiter = " ");
std::string_view InitDelimit(std::string_view &str);
std::pair<Route::RouteType, std::vector<std::string>> StopsFromString(std::string_view &str);


//template<typename PTR, typename DB>
class Manager {
public:
    explicit Manager(std::istream &is = std::cin) : is_(is), database(Database()) {}

    void AddRequests() {
        //bool flag = false;
        //std::cerr << "AddRequest" << std::endl;
        const auto num_request_input = ReadCountRequests(is_);
        //if(num_request_input == 5) flag = true;
        requests_input_.reserve(num_request_input);
        //std::cerr << num_request_input << std::endl;

        for (size_t i = 0; i < num_request_input; ++i) {
            std::string request_str;
            std::getline(is_, request_str);
            //std ::cerr << request_str << std:: endl;
            requests_input_.emplace_back(AddCurrentRequest(request_str));
        }

        const auto num_request_output = ReadCountRequests(is_);
        request_output_.reserve(num_request_output);
        //std::cerr << num_request_output << std::endl;

        for(size_t i = 0; i < num_request_output; ++i){
            std::string request_str;
            std::getline(is_, request_str);
            //std ::cerr << request_str << std:: endl;
            request_output_.emplace_back(AddCurrentRequest(request_str, false));
        }
        /*if(flag) {
            throw std::invalid_argument("kee");
        }*/
    }

    void ProcessRequests(){
        for(auto& item : requests_input_){
            item->Process(database);
        }
        for(auto& item : request_output_){
            item->Process(database);
        }
    }

private:
    static std::unique_ptr<Request> AddCurrentRequest(std::string_view request_str, bool is_input = true) {
        const auto type_request = TypeRequestFromString(ReadWord(request_str));
        if (!type_request) {
            return nullptr;
        }
        auto request = Request::Create(type_request.value(), is_input);
        if(request){
            request->Parse(request_str);
        }
        return request;
    }


    std::istream &is_;
    Database database;
    std::vector<std::unique_ptr<Request>> requests_input_;
    std::vector<std::unique_ptr<Request>> request_output_;
};





#endif //PARTA_PARSER_H
