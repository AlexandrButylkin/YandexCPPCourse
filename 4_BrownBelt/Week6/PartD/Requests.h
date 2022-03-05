#ifndef PARTA_REQUESTS_H
#define PARTA_REQUESTS_H

#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <iostream>

#include "Database.h"
#include "json.h"

class Request {
public:

    enum class IOType{
        INPUT,
        OUTPUT
    };

    enum class RequestType{
        STOP,
        BUS
    };

    RequestType GetRequestType() const {
        return request_type_;
    }

public:

    Request(IOType io_type, RequestType request_type) : io_type_(io_type), request_type_(request_type) {}
    static std::unique_ptr<Request> Create(IOType io_type, RequestType request_type);

    virtual void ParseFromString(std::string_view) = 0;
    virtual void ParseFromJSON(const Json::Node& node) = 0;

    virtual ~Request() = default;



private:

    const IOType io_type_;
    const RequestType request_type_;

};

class InputRequest : public Request {
public:

    InputRequest(RequestType type) : Request(IOType::INPUT, type) {}
    void ParseFromString(std::string_view) override = 0;
    void ParseFromJSON(const Json::Node &node) override = 0;
    virtual void Process(Database& db) = 0;

};

class StopInputRequest : public InputRequest {
public:

    StopInputRequest() : InputRequest(RequestType::STOP) {}
    void ParseFromString(std::string_view) override;
    void ParseFromJSON(const Json::Node& node) override;
    void Process(Database& db) override;

private:
    std::string name_;
    double latitude_;
    double longitude_;
    std::unordered_map<std::string, size_t> distance_to_stops_;

};

class BusInputRequest : public InputRequest {
public:

    BusInputRequest() : InputRequest(RequestType::BUS) {}
    void ParseFromString(std::string_view) override;
    void ParseFromJSON(const Json::Node& node) override;
    void Process(Database& db) override;

private:
    std::string number_;
    Route::RouteType route_type_;
    std::vector<std::string> stops_;
};

template<typename T>
class OutputRequest : public Request {
public:

    OutputRequest(RequestType type) : Request(IOType::INPUT, type) {}
    virtual T Process(Database& db) = 0;
    void ParseFromString(std::string_view) override = 0;
    void ParseFromJSON(const Json::Node &node) override = 0;

/*    virtual std::string PrintString(std::ostream& os) = 0;
    virtual Json::Node PrintJSON() = 0;*/

protected:
    int request_id_;
};

struct StopData{
    int request_id = -1;
    std::string name;
    bool is_error = true;
    std::vector<std::string> routes;

    std::string ToString() const;
    Json::Node ToJSON() const;
};



struct BusData{
    int request_id = -1;
    std::string number;
    bool is_error = true;
    double length = 0.0;
    double real_length = 0.0;
    size_t stops_count = 0;
    size_t unique_stops_count = 0;

    std::string ToString() const;
    Json::Node ToJSON() const;
};

class StopOutputRequest : public OutputRequest<StopData> {
public:

    StopOutputRequest() : OutputRequest(RequestType::STOP) {}
    void ParseFromString(std::string_view) override;
    void ParseFromJSON(const Json::Node& node) override;
    StopData Process(Database& db) override;

/*    std::string PrintString(std::ostream& os) override;
    Json::Node PrintJSON() override;*/

private:
    std::string name_;
};


class BusOutputRequest : public OutputRequest<BusData> {
public:

    BusOutputRequest() : OutputRequest(RequestType::BUS) {}
    void ParseFromString(std::string_view) override;
    void ParseFromJSON(const Json::Node& node) override;
    BusData Process(Database& db) override;

    /*std::string PrintString(std::ostream& os) override;
    Json::Node PrintJSON() override;*/

private:

    std::string number_;

};


#endif //PARTA_REQUESTS_H
