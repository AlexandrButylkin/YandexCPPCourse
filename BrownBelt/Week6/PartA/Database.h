//
// Created by cobak on 12.02.2022.
//

#ifndef PARTA_DATABASE_H
#define PARTA_DATABASE_H

#include <string>
#include <vector>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <memory>

#include "Coordinates.h"

class Stop{
public:
    explicit Stop(double latitude = 0.0, double longitude = 0.0) : coord(latitude, longitude) {}
    Coordinates GetCoordinates() const;

private:
    Coordinates coord;

};

class Route {
public:
    enum class RouteType{
        LINEAR,
        CIRCLE
    };

    explicit Route(RouteType type, std::unordered_set<std::string> unique_stops) : type_(type), unique_stops_(std::move(unique_stops)) {}
    size_t GetUniqueStopsCount() const;
    virtual double GetLength() const = 0;
    virtual size_t GetStopsCount() const = 0;
    virtual ~Route() {}

private:
    RouteType type_;
    std::unordered_set<std::string> unique_stops_;
};

class CircleRoute : public Route {
private:
    std::vector<std::shared_ptr<Stop>> stops_;
public:
    explicit CircleRoute(std::vector<std::shared_ptr<Stop>> stops, std::unordered_set<std::string> unique_stops) : Route(RouteType::CIRCLE, std::move(unique_stops)) , stops_(std::move(stops)) {}
    double GetLength() const override;
    size_t GetStopsCount() const override;
};

class LinearRoute : public Route {
private:
    std::vector<std::shared_ptr<Stop>> stops_;
public:
    explicit LinearRoute(std::vector<std::shared_ptr<Stop>> stops, std::unordered_set<std::string> unique_stops) : Route(RouteType::LINEAR, std::move(unique_stops)) , stops_(std::move(stops)) {}
    double GetLength() const override;
    size_t GetStopsCount() const override;
};



class Database {
public:

    void AddStop(std::string name, Stop stop);
    void AddRoute(std::string number, std::shared_ptr<Route> route);

    using AddStop_ptr  = void (Database::*)(std::string, Stop);

    std::shared_ptr<Stop> GetStop(const std::string& name);
    std::shared_ptr<Route> GetRoute(const std::string& number);
private:
    std::unordered_map<std::string, std::shared_ptr<Route>> routes;
    std::unordered_map<std::string, std::shared_ptr<Stop>> stops;
};

class RouteBuilder{
public:
    explicit RouteBuilder(Database& database) : db(database) {}

    std::shared_ptr<Route> MakeLinearRoute(std::vector<std::string>& stops);
    std::shared_ptr<Route> MakeCircleRoute(std::vector<std::string>& stops);

private:
    static std::unordered_set<std::string> MakeUniqueStops(std::vector<std::string>& stops);
    Database& db;
};

#endif //PARTA_DATABASE_H
