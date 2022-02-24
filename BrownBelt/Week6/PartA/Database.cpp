#include "Database.h"

#include <iterator>

Coordinates Stop::GetCoordinates() const {
    return coord;
}

void Database::AddStop(std::string name, Stop stop) {
    if(stops.count(name)){
        *stops.at(name) = stop;
    } else {
        stops.emplace(std::move(name), std::make_shared<Stop>(stop));
    }
}

void Database::AddRoute(std::string number, std::shared_ptr<Route> route) {
    routes.emplace(std::move(number), std::move(route));
}

std::shared_ptr<Stop> Database::GetStop(const std::string &name) {
    auto iter = stops.find(name);
    if(iter == stops.end()) iter = stops.emplace(name, std::make_shared<Stop>()).first;
    return iter->second;
}

std::shared_ptr<Route> Database::GetRoute(const std::string& number) {
    const auto iter = routes.find(number);
    if(iter == routes.end()){
        return nullptr;
    }
    return iter->second;
}

std::shared_ptr<Route> RouteBuilder::MakeLinearRoute(std::vector<std::string> &stops) {
    std::vector<std::shared_ptr<Stop>> result;
    result.reserve(stops.size());
    for(const auto& stop : stops){
        result.emplace_back(db.GetStop(stop));
    }
    return std::make_shared<LinearRoute>(result, MakeUniqueStops(stops));
}

std::shared_ptr<Route> RouteBuilder::MakeCircleRoute(std::vector<std::string> &stops) {
    std::vector<std::shared_ptr<Stop>> result;
    result.reserve(stops.size());
    for(const auto& stop : stops){
        result.emplace_back(db.GetStop(stop));
    }
    return std::make_shared<CircleRoute>(result, MakeUniqueStops(stops));
}

std::unordered_set<std::string> RouteBuilder::MakeUniqueStops(std::vector<std::string> &stops) {
    return {std::make_move_iterator(stops.begin()), std::make_move_iterator(stops.end())};
}

double LinearRoute::GetLength() const {
    double result = 0.0;
    for(size_t i = 0, size = stops_.size(); i < size - 1; ++i){
        result += Coordinates::Distance(stops_[i]->GetCoordinates(), stops_[i + 1]->GetCoordinates());
    }
    return result * 2;
}

double CircleRoute::GetLength() const {
    double result = 0.0;
    for(size_t i = 0, size = stops_.size(); i < size - 1; ++i){
        result += Coordinates::Distance(stops_[i]->GetCoordinates(), stops_[i + 1]->GetCoordinates());
    }
    return result;
}

size_t Route::GetUniqueStopsCount() const {
    return unique_stops_.size();
}

size_t LinearRoute::GetStopsCount() const {
    return stops_.size() * 2 - 1;
}

size_t CircleRoute::GetStopsCount() const {
    return stops_.size();
}

/*
size_t LinearRoute::GetUniqueStopsCount() const {
    return stops_.size();
}

size_t CircleRoute::GetUniqueStopsCount() const {
    return stops_.size() - 1;
}*/
