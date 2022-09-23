#include <sstream>
#include <exception>

#include "Parser.h"
#include "json.h"


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

std::optional<Request::RequestType> GetTypeRequest(std::string_view str){
    if(str == "Stop"){
        return Request::RequestType::STOP;
    } else if (str == "Bus"){
        return Request::RequestType::BUS;
    } else return std::nullopt;
}

std::unique_ptr<Request> Manager::AddCurrentStringRequest(std::string_view request_str, Request::IOType io_type) {
    const auto type_request = GetTypeRequest(ReadWord(request_str));

    if (!type_request) {
        return nullptr;
    }
    auto request = Request::Create(io_type, type_request.value());

    if(request){
        request->ParseFromString(request_str);
    }
    return request;
}

std::unique_ptr<Request> Manager::AddCurrentJSONRequest(const Json::Node &node, Request::IOType io_type) {
    const auto type_request = GetTypeRequest(node.AsMap().at("type").AsString());
    if(!type_request){
        return nullptr;
    }
    auto request = Request::Create(io_type, type_request.value());

    if(request){
        request->ParseFromJSON(node);
    }
    return request;
}

void Manager::ParseAllRequestString() {
    const auto num_request_input = ReadCountRequests(is_);
    requests_input_.reserve(num_request_input);

    for (size_t i = 0; i < num_request_input; ++i) {
        std::string request_str;
        std::getline(is_, request_str);
        requests_input_.emplace_back(AddCurrentStringRequest(request_str));
    }

    const auto num_request_output = ReadCountRequests(is_);
    request_output_.reserve(num_request_output);

    for(size_t i = 0; i < num_request_output; ++i){
        std::string request_str;
        std::getline(is_, request_str);
        request_output_.emplace_back(AddCurrentStringRequest(request_str, Request::IOType::OUTPUT));
    }
}

void Manager::ParseAllRequestJSON() {
    auto document = Json::Load(is_);

    auto base_requests = document.GetRoot().AsMap().at(BASE_REQUESTS);
    for(auto& item : base_requests.AsArray()){
        requests_input_.push_back(AddCurrentJSONRequest(item));
    }
    auto stat_requests = document.GetRoot().AsMap().at(STAT_REQUESTS);
    for(auto& item : stat_requests.AsArray()){
        request_output_.push_back(AddCurrentJSONRequest(item, Request::IOType::OUTPUT));
    }
}

void Manager::ProcessAllInputRequest() {
    for(auto& item : requests_input_){
        dynamic_cast<InputRequest&>(*item).Process(database);
    }
}

void Manager::ProcessAllOutputRequestString() {
    for(auto& item : request_output_){

        if(item->GetRequestType() == Request::RequestType::STOP){
            auto& OutputRequestItem = dynamic_cast<OutputRequest<StopData>&>(*item);
            const auto data = OutputRequestItem.Process(database);
            os_ << data.ToString();
        } else {
            auto& OutputRequestItem = dynamic_cast<OutputRequest<BusData>&>(*item);
            const auto data = OutputRequestItem.Process(database);
            os_ << data.ToString();
        }
    }
}

void Manager::ProcessAllOutputRequestJSON() {
    std::vector<Json::Node> result;
    for(auto& item : request_output_){
        if(item->GetRequestType() == Request::RequestType::STOP){
            auto& OutputRequestItem = dynamic_cast<OutputRequest<StopData>&>(*item);
            auto data = OutputRequestItem.Process(database);
            result.push_back(data.ToJSON());
        } else {
            auto& OutputRequestItem = dynamic_cast<OutputRequest<BusData>&>(*item);
            auto data = OutputRequestItem.Process(database);
            result.push_back(data.ToJSON());
        }
    }
    Json::PrintNode(Json::Node(result), os_);
}


