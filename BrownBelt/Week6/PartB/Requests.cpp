#include "Requests.h"
#include "Parser.h"

using std::string;
using std::string_view;

std::unique_ptr<Request> Request::Create(Request::RequestType type, bool is_input) {
    if(type == RequestType::STOP){
        if(is_input) return std::make_unique<StopInput>();
        return std::make_unique<StopOutput>();
    } else if(type == RequestType::BUS){
        if (is_input) return std::make_unique<BusInput>();
        return std::make_unique<BusOutput>();
    } else return nullptr;
}

void StopInput::Parse(string_view str) {
    name_ = string(ReadWord(str, ": "));
    latitude_ = DoubleFromString(ReadWord(str, ", "));
    longitude_ = DoubleFromString(ReadWord(str));
}

void StopOutput::Parse(string_view str) {
    name_ = string(ReadWord(str, "\n"));
}

void BusInput::Parse(string_view str) {
    number_ = ReadWord(str, ": ");
    auto [route_type, stops] = StopsFromString(str);
    route_type_ = route_type;
    stops_ = std::move(stops);
}

void BusOutput::Parse(std::string_view str) {
    number_ = ReadWord(str, "\n");
}

void StopInput::Process(Database &db) {
    db.AddStopCoordinates(name_, {latitude_, longitude_});
}

void BusInput::Process(Database &db) {
    switch (route_type_) {
        case Route::RouteType::LINEAR:
            db.AddRoute(number_, RouteBuilder(db).MakeLinearRoute(number_, stops_));
            return;
        case Route::RouteType::CIRCLE:
            db.AddRoute(number_, RouteBuilder(db).MakeCircleRoute(number_, stops_));
            return;
    }
}

void StopOutput::Process(Database &db) {
    PrintResult(db.GetStop(name_));
}

void StopOutput::PrintResult(const std::shared_ptr<Stop>& stop, std::ostream &os) const {
    os.precision(6);
    os << "Stop " << name_ << ": ";
    if(!stop){
        os << "not found\n";
    } else if (stop->GetRoutes().empty()){
        os << "no buses\n";
    } else {
        os << "buses ";
        bool first = true;
        for(const auto& bus : stop->GetRoutes()){
            if(first){
               os << bus;
                first = false;
            } else {
                os << " " << bus;
            }
        }
        os << "\n";
    }
}

void BusOutput::Process(Database &db) {
    PrintResult(db.GetRoute(number_));
}

void BusOutput::PrintResult(const std::shared_ptr<Route>& route, std::ostream &os) const {
    os.precision(6);
    os << "Bus " << number_ << ": ";
    if(!route){
        os << "not found\n";
    } else {
        os << route->GetStopsCount() << " stops on route, " <<
        route->GetUniqueStopsCount() << " unique stops, " <<
        route->GetLength() << " route length\n";
    }
}