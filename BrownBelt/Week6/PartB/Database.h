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
#include <set>
#include <memory>

#include "Coordinates.h"

class Stop {
public:
    explicit Stop(double latitude = 0.0, double longitude = 0.0) : coord_(latitude, longitude) {}
    explicit Stop(Coordinates coord) : coord_(coord) {}

    Coordinates GetCoordinates() const;
    void SetCoordinates(Coordinates coord);

    void AddRoute(const std::string& stop);
    const std::set<std::string>& GetRoutes() const;

private:
    Coordinates coord_;
    std::set<std::string> routes_;
};

class Route {
public:
    enum class RouteType {
        LINEAR,
        CIRCLE
    };

    explicit Route(RouteType type, std::string name,
                   std::unordered_set<std::string> unique_stops) : type_(type),
                   name_(std::move(name)),
                   unique_stops_(std::move(unique_stops)) {}

    size_t GetUniqueStopsCount() const;
    virtual double GetLength() const = 0;
    virtual size_t GetStopsCount() const = 0;
    virtual ~Route() = default;

private:
    RouteType type_;
    std::string name_;
    std::unordered_set<std::string> unique_stops_;
};

class CircleRoute : public Route {
private:
    std::vector<std::shared_ptr<Stop>> stops_;
    //std::vector<std::shared_ptr<Stop>> &GetStops();

public:
    explicit CircleRoute(std::vector<std::shared_ptr<Stop>> stops, std::string name,
                         std::unordered_set<std::string> unique_stops) :
                         Route(RouteType::CIRCLE, std::move(name),
                               std::move(unique_stops)),
                               stops_(std::move(stops)) {}

    double GetLength() const override;
    size_t GetStopsCount() const override;
};

class LinearRoute : public Route {
private:
    std::vector<std::shared_ptr<Stop>> stops_;
    //std::vector<std::shared_ptr<Stop>> &GetStops();

public:
    explicit LinearRoute(std::vector<std::shared_ptr<Stop>> stops, std::string name,
                         std::unordered_set<std::string> unique_stops) :
                         Route(RouteType::LINEAR, std::move(name),
                               std::move(unique_stops)),
                               stops_(std::move(stops)) {}

    double GetLength() const override;
    size_t GetStopsCount() const override;
};


class Database {
public:

    void AddStopCoordinates(std::string name, Coordinates coord);
    void AddRoute(std::string number, std::shared_ptr<Route> route);

    using AddStop_ptr = void (Database::*)(std::string, Stop);

    std::shared_ptr<Stop> GetStop(const std::string& name) const;
    std::shared_ptr<Route> GetRoute(const std::string &number) const;

    std::shared_ptr<Stop> TakeOrAddEmptyStop(const std::string &name);

private:
    std::unordered_map<std::string, std::shared_ptr<Route>> routes;
    std::unordered_map<std::string, std::shared_ptr<Stop>> stops;
};

class RouteBuilder {
public:
    explicit RouteBuilder(Database &database) : db(database) {}

    std::shared_ptr<Route> MakeLinearRoute(std::string name, std::vector<std::string> &stops);
    std::shared_ptr<Route> MakeCircleRoute(std::string name, std::vector<std::string> &stops);

private:
    static std::unordered_set<std::string> MakeUniqueStops(std::vector<std::string> &stops);
    Database &db;
};

#endif //PARTA_DATABASE_H
