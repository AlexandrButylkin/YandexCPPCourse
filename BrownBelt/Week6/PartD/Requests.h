#ifndef PARTA_REQUESTS_H
#define PARTA_REQUESTS_H

#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <iostream>

#include "Database.h"

class Request {
public:
    enum class RequestType{
        STOP,
        BUS
    };
    explicit Request(RequestType type) : type_(type) {}
    static std::unique_ptr<Request> Create(RequestType type, bool is_input = true);

    virtual void Parse(std::string_view) = 0;
    virtual void Process(Database& db) = 0;

    virtual ~Request() = default;
private:
    const RequestType type_;
};

class RequestStop : public Request{
public:
    RequestStop() : Request(RequestType::STOP) {}
protected:
    std::string name_;
};

class StopInput : public RequestStop {
public:
    StopInput() : RequestStop() {}
    void Parse(std::string_view str) override;
    void Process(Database& db) override;
public:
    double latitude_;
    double longitude_;
    std::unordered_map<std::string, size_t> distance_to_stops_;
};

class StopOutput : public RequestStop {
public:
    StopOutput() : RequestStop() {}
    void Parse(std::string_view str) override;
    void Process(Database& db) override;
private:
    void PrintResult(const std::shared_ptr<Stop>& stop, std::ostream& os = std::cout) const;
};

class RequestBus : public Request{
public:
    RequestBus() : Request(RequestType::BUS) {}
protected:
    std::string number_;
};


class BusInput : public RequestBus{
public:
    BusInput() : RequestBus() {}
    void Parse(std::string_view str) override;
    void Process(Database& db) override;

private:
    Route::RouteType route_type_;
    std::vector<std::string> stops_;
};

class BusOutput : public RequestBus{
public:
    BusOutput() : RequestBus() {}
    void Parse(std::string_view str) override;
    void Process(Database& db) override;

private:
    void PrintResult(const std::shared_ptr<Route>& route, std::ostream& os = std::cout) const;
};


#endif //PARTA_REQUESTS_H
