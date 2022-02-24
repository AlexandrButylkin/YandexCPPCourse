#include "Requests.h"
#include "Parser.h"

using std::string;
using std::string_view;

std::unique_ptr<Request> Request::Create(Request::RequestType type, bool is_input) {
    if(type == RequestType::STOP){
        return std::make_unique<RequestInputStop>();
    } else if(type == RequestType::BUS){
        if (is_input) return std::make_unique<BusInput>();
        else return std::make_unique<BusOutput>();
    } else return nullptr;
}

void RequestInputStop::Parse(string_view str) {
    name_ = string(ReadWord(str, ": "));
    latitude_ = DoubleFromString(ReadWord(str, ", "));
    longitude_ = DoubleFromString(ReadWord(str));
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

void RequestInputStop::Process(Database &db) {
    db.AddStop(name_, Stop(latitude_, longitude_));
}

void BusInput::Process(Database &db) {
    switch (route_type_) {
        case Route::RouteType::LINEAR:
            db.AddRoute(number_, RouteBuilder(db).MakeLinearRoute(stops_));
            return;
        case Route::RouteType::CIRCLE:
            db.AddRoute(number_, RouteBuilder(db).MakeCircleRoute(stops_));
            return;
    }
}

void BusOutput::Process(Database &db) {
    PrintResult(db.GetRoute(number_));
}

void BusOutput::PrintResult(std::shared_ptr<Route> route, std::ostream &os) {
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