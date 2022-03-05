#include "Database.h"

Coordinates Stop::GetCoordinates() const {
    return coord_;
}

Stop *Stop::SetCoordinates(Coordinates coord) {
    coord_ = coord;
    return this;
}

const std::string &Stop::GetName() const {
    return name_;
}

Stop *Stop::SetName(const std::string &name) {
    name_ = name;
    return this;
}

Stop *Stop::SetName(std::string &&name) {
    name_ = name;
    return this;
}

Stop *Stop::SetNearestStops(std::unordered_map<std::string, size_t> stops) {
    nearest_stops_ = std::move(stops);
    return this;
}

void Stop::AddRoute(const std::string &stop) {
    routes_.emplace(stop);
}

const std::set<std::string> &Stop::GetRoutes() const {
    return routes_;
}

size_t Stop::GetDistanceTo(const std::string &name) {
    auto iter = nearest_stops_.find(name);
    if (iter == nearest_stops_.end()) {
        return 0.0;
    }
    return iter->second;
}

void Database::AddStop(std::string name, Coordinates coord, std::unordered_map<std::string, size_t> distance_to_stops) {
    if (stops.count(name)) {
        stops.at(name)->
                SetCoordinates(coord)->
                SetName(std::move(name))->
                SetNearestStops(std::move(distance_to_stops));
    } else {
        stops.emplace(name, std::make_shared<Stop>(name, coord, std::move(distance_to_stops)));
    }
}

void Database::AddRoute(std::string number, std::shared_ptr<Route> route) {
    routes.emplace(std::move(number), std::move(route));
}

std::shared_ptr<Stop> Database::GetStop(const std::string &name) const {
    const auto iter = stops.find(name);
    if (iter == stops.end()) {
        return nullptr;
    }
    return iter->second;
}

std::shared_ptr<Route> Database::GetRoute(const std::string &number) const {
    const auto iter = routes.find(number);
    if (iter == routes.end()) {
        return nullptr;
    }
    return iter->second;
}

std::shared_ptr<Stop> Database::TakeOrAddEmptyStop(const std::string &name) {
    auto iter = stops.find(name);
    if (iter == stops.end()) iter = stops.emplace(name, std::make_shared<Stop>(name)).first;
    return iter->second;
}

std::shared_ptr<Route> RouteBuilder::MakeLinearRoute(std::string name, std::vector<std::string> &stops) {
    std::vector<std::shared_ptr<Stop>> result;
    result.reserve(stops.size());
    for (const auto &stop: stops) {
        auto curr_stop = db.TakeOrAddEmptyStop(stop);
        curr_stop->AddRoute(name);
        result.emplace_back(std::move(curr_stop));
    }
    return std::make_shared<LinearRoute>(result, std::move(name), MakeUniqueStops(stops));
}

std::shared_ptr<Route> RouteBuilder::MakeCircleRoute(std::string name, std::vector<std::string> &stops) {
    std::vector<std::shared_ptr<Stop>> result;
    result.reserve(stops.size());
    for (const auto &stop: stops) {
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
    double C = 0.0;
    for (size_t i = 0, size = stops_.size(); i < size - 1; ++i) {
        C += Coordinates::Distance(stops_[i]->GetCoordinates(), stops_[i + 1]->GetCoordinates());
    }
    return C * 2;
}

double CircleRoute::GetLength() const {
    double C = 0.0;
    for (size_t i = 0, size = stops_.size(); i < size - 1; ++i) {
        C += Coordinates::Distance(stops_[i]->GetCoordinates(), stops_[i + 1]->GetCoordinates());
    }
    return C;
}

size_t LinearRoute::GetRealLength() const {
    size_t L = 0;
    for (size_t i = 0, size = stops_.size(); i < size - 1; ++i) {
        size_t dist = 0;
        if (dist = stops_[i]->GetDistanceTo(stops_[i + 1]->GetName()); dist == 0) {
            L += stops_[i + 1]->GetDistanceTo(stops_[i]->GetName());
        } else {
            L += dist;
        }

        if (dist = stops_[i + 1]->GetDistanceTo(stops_[i]->GetName()); dist == 0) {
            L += stops_[i]->GetDistanceTo(stops_[i + 1]->GetName());
        } else {
            L += dist;
        }
    }
    return L;
}

size_t CircleRoute::GetRealLength() const {
    size_t L = 0;
    for (size_t i = 0, size = stops_.size(); i < size - 1; ++i) {
        size_t dist = 0;
        if (dist = stops_[i]->GetDistanceTo(stops_[i + 1]->GetName()); dist == 0) {
            L += stops_[i + 1]->GetDistanceTo(stops_[i]->GetName());
        } else {
            L += dist;
        }
    }
    return L;
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
