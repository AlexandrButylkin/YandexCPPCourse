#ifndef PARTA_PARSER_H
#define PARTA_PARSER_H

#include <vector>
#include <memory>
#include <optional>

#include "Requests.h"
#include "Database.h"

static const std::string BASE_REQUESTS = "base_requests";
static const std::string STAT_REQUESTS = "stat_requests";


double DoubleFromString(std::string_view str);
size_t IntFromString(std::string_view str);

size_t ReadCountRequests(std::istream &is);

std::pair<std::string_view, std::optional<std::string_view>>
SplitTwo(std::string_view str, std::string_view delimiter = " ");

std::string_view ReadWord(std::string_view &str, std::string_view delimiter = " ");
std::string_view InitDelimit(std::string_view &str);
std::pair<Route::RouteType, std::vector<std::string>> StopsFromString(std::string_view &str);

std::optional<Request::RequestType> GetTypeRequest(std::string_view str);



class Manager {
public:
    explicit Manager(std::istream &is = std::cin, std::ostream& os = std::cout) : is_(is), os_(os), database(Database()) {}

    void ParseAllRequestString();
    void ProcessAllOutputRequestString();
    void ParseAllRequestJSON();
    void ProcessAllOutputRequestJSON();
    void ProcessAllInputRequest();

private:

    static std::unique_ptr<Request> AddCurrentStringRequest(std::string_view request_str, Request::IOType io_type = Request::IOType::INPUT);
    static std::unique_ptr<Request> AddCurrentJSONRequest(const Json::Node & node, Request::IOType io_type = Request::IOType::INPUT);

private:

    std::istream &is_;
    std::ostream &os_;

private:

    Database database;
    std::vector<std::unique_ptr<Request>> requests_input_;
    std::vector<std::unique_ptr<Request>> request_output_;

};





#endif //PARTA_PARSER_H
