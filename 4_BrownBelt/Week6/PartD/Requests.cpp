#include "Requests.h"
#include "Parser.h"

std::unique_ptr<Request> Request::Create(IOType io_type, RequestType request_type) {
    switch (io_type) {
        case IOType::INPUT:
            switch (request_type) {
                case RequestType::STOP: return std::make_unique<StopInputRequest>();
                case RequestType::BUS: return std::make_unique<BusInputRequest>();
            }
        case IOType::OUTPUT:
            switch (request_type) {
                case RequestType::STOP: return std::make_unique<StopOutputRequest>();
                case RequestType::BUS: return std::make_unique<BusOutputRequest>();
            }
    }
    return nullptr;
}

void StopInputRequest::ParseFromString(std::string_view str) {
    name_ = std::string(ReadWord(str, ": "));
    latitude_ = DoubleFromString(ReadWord(str, ", "));
    longitude_ = DoubleFromString(ReadWord(str, ", "));

    while(!str.empty()){
        size_t distance = IntFromString(ReadWord(str, "m to "));
        std::string stop = std::string(ReadWord(str, ", "));
        distance_to_stops_.emplace(std::move(stop), distance);
    }
}

void StopOutputRequest::ParseFromString(std::string_view str) {
    name_ = std::string(ReadWord(str, "\n"));
}

void BusInputRequest::ParseFromString(std::string_view str) {
    number_ = ReadWord(str, ": ");
    auto [route_type, stops] = StopsFromString(str);
    route_type_ = route_type;
    stops_ = std::move(stops);
}

void BusOutputRequest::ParseFromString(std::string_view str) {
    number_ = ReadWord(str, "\n");
}

void StopInputRequest::ParseFromJSON(const Json::Node &node) {
    name_ = node.AsMap().at("name").AsString();
    latitude_ = node.AsMap().at("latitude").AsDouble();
    longitude_ = node.AsMap().at("longitude").AsDouble();

    if(node.AsMap().count("road_distances")) {
        for (const auto &item: node.AsMap().at("road_distances").AsMap()) {
            //std::cerr << "ParseFromJSONStopInputIteration\n";
            distance_to_stops_.emplace(item.first, item.second.AsInt());
        }
    }
}

void StopOutputRequest::ParseFromJSON(const Json::Node &node) {
    name_ = node.AsMap().at("name").AsString();
    request_id_ = node.AsMap().at("id").AsInt();
}

void BusInputRequest::ParseFromJSON(const Json::Node &node) {
    number_ = node.AsMap().at("name").AsString();
    if(node.AsMap().at("is_roundtrip").AsBool()){
        route_type_ = Route::RouteType::CIRCLE;
    } else {
        route_type_ = Route::RouteType::LINEAR;
    }
    for(auto& item : node.AsMap().at("stops").AsArray()){
        stops_.emplace_back(item.AsString());
    }
}

void BusOutputRequest::ParseFromJSON(const Json::Node &node) {
    number_ = node.AsMap().at("name").AsString();
    request_id_ = node.AsMap().at("id").AsInt();
}

void StopInputRequest::Process(Database &db) {
    db.AddStop(std::move(name_), {latitude_, longitude_}, std::move(distance_to_stops_));
}

StopData StopOutputRequest::Process(Database &db) {
    auto data = db.GetStop(name_);
    if(data){
        return {request_id_, name_, false,
            std::vector<std::string>(data->GetRoutes().begin(), data->GetRoutes().end())};
    } else return {request_id_};
}

void BusInputRequest::Process(Database &db) {
    switch (route_type_) {
        case Route::RouteType::LINEAR:
            db.AddRoute(number_, RouteBuilder(db).MakeLinearRoute(number_, stops_));
            return;
        case Route::RouteType::CIRCLE:
            db.AddRoute(number_, RouteBuilder(db).MakeCircleRoute(number_, stops_));
            return;
    }
}

BusData BusOutputRequest::Process(Database &db) {
    auto data = db.GetRoute(number_);
    if(data){
        return {request_id_, number_, false, data->GetLength(), static_cast<double>(data->GetRealLength()),
                data->GetStopsCount(), data->GetUniqueStopsCount()};
    } else return {request_id_};
}

std::string StopData::ToString() const {
    std::stringstream os;
    os.precision(6);
    os << "Stop " << name << ": ";
    if(is_error){
        os << "not found\n";
    } else if (routes.empty()){
        os << "no buses\n";
    } else {
        os << "buses ";
        bool first = true;
        for(const auto& bus : routes){
            if(first){
                os << bus;
                first = false;
            } else {
                os << " " << bus;
            }
        }
        os << "\n";
    }
    return os.str();
}

std::string BusData::ToString() const {
    std::stringstream os;
    os.precision(6);
    os << "Bus " << number << ": ";
    if(is_error){
        os << "not found\n";
    } else {
        os << stops_count << " stops on route, " <<
           unique_stops_count << " unique stops, " <<
           real_length << " route length, " <<
           static_cast<double>(real_length) / length << " curvature\n";
    }
    return os.str();
}

Json::Node StopData::ToJSON() const {
    std::map<std::string, Json::Node> result;
    result["request_id"] = Json::Node(request_id);
    if(is_error){
        result["error_message"] = "not found";
    } else if (routes.empty()) {
        result["buses"] = Json::Node(std::vector<Json::Node>());
    } else {
        result["buses"] = Json::Node(std::vector<Json::Node>(routes.begin(), routes.end()));
    }
    return result;
}

Json::Node BusData::ToJSON() const {
    std::map<std::string, Json::Node> result;
    result["request_id"] = Json::Node(request_id);
    if(is_error){
        result["error_message"] = "not found";
    } else {
        result["stop_count"] = Json::Node(static_cast<int>(stops_count));
        result["unique_stop_count"] = Json::Node(static_cast<int>(unique_stops_count));
        result["route_length"] = Json::Node(real_length);
        result["curvature"] = Json::Node(static_cast<double>(real_length) / length);
    }
    return result;
}