#include "Database.h"

Coordinates Stop::GetCoordinates() const {
    return coord_;
}

void Stop::SetCoordinates(Coordinates coord) {
    coord_ = coord;
}

void Stop::AddRoute(const std::string& stop) {
    routes_.emplace(stop);
}

const std::set<std::string> &Stop::GetRoutes() const {
    return routes_;
}

void Database::AddStopCoordinates(std::string name, Coordinates coord) {
    if(stops.count(name)){
        stops.at(name)->SetCoordinates(coord);
    } else {
        stops.emplace(std::move(name), std::make_shared<Stop>(coord));
    }
}

void Database::AddRoute(std::string number, std::shared_ptr<Route> route) {
    routes.emplace(std::move(number), std::move(route));
}

std::shared_ptr<Stop> Database::GetStop(const std::string &name) const {
    const auto iter = stops.find(name);
    if(iter == stops.end()){
        return nullptr;
    }
    return iter->second;
}

std::shared_ptr<Route> Database::GetRoute(const std::string& number) const {
    const auto iter = routes.find(number);
    if(iter == routes.end()){
        return nullptr;
    }
    return iter->second;
}

std::shared_ptr<Stop> Database::TakeOrAddEmptyStop(const std::string &name) {
    auto iter = stops.find(name);
    if(iter == stops.end()) iter = stops.emplace(name, std::make_shared<Stop>()).first;
    return iter->second;
}

std::shared_ptr<Route> RouteBuilder::MakeLinearRoute(std::string name, std::vector<std::string> &stops) {
    std::vector<std::shared_ptr<Stop>> result;
    result.reserve(stops.size());
    for(const auto& stop : stops){
        auto curr_stop = db.TakeOrAddEmptyStop(stop);
        curr_stop->AddRoute(name);
        result.emplace_back(std::move(curr_stop));
    }
    return std::make_shared<LinearRoute>(result, std::move(name), MakeUniqueStops(stops));
}

std::shared_ptr<Route> RouteBuilder::MakeCircleRoute(std::string name, std::vector<std::string> &stops) {
    std::vector<std::shared_ptr<Stop>> result;
    result.reserve(stops.size());
    for(const auto& stop : stops){
        auto curr_stop = db.TakeOrAddEmptyStop(stop);
        curr_stop->AddRoute(name);
        result.emplace_back(std::move(curr_stop));
    }
    return std::make_shared<CircleRoute>(result, std::move(name), MakeUniqueStops(stops));
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

/*std::vector<std::shared_ptr<Stop>> &LinearRoute::GetStops() {
    return stops_;
}

std::vector<std::shared_ptr<Stop>> &CircleRoute::GetStops() {
    return stops_;
}*/
/*
size_t LinearRoute::GetUniqueStopsCount() const {
    return stops_.size();
}

size_t CircleRoute::GetUniqueStopsCount() const {
    return stops_.size() - 1;
}*/
