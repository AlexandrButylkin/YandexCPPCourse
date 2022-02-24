#include "Coordinates.h"

#include <cmath>

double Coordinates::GetLatitude() {
    return latitude_;
}

double Coordinates::GetLatitude() const {
    return latitude_;
}

double Coordinates::GetLongitude() {
    return longitude_;
}

double Coordinates::GetLongitude() const {
    return longitude_;
}

double Coordinates::Distance(const Coordinates& from, const Coordinates& to) {
    double lat_1 = from.latitude_ * PI/180.0;
    double long_1 = from.longitude_ * PI/180.0;
    double lat_2 = to.latitude_ * PI/180.0;
    double long_2 = to.longitude_ * PI/180.0;

    /*double delta = std::abs(long_1 - long_2);
    double cos_delta = std::cos(delta);
    double sin_delta = std::sin(delta);

    double cos_lat_1 = std::cos(lat_1);
    double sin_lat_1 = std::sin(lat_1);
    double cos_lat_2 = std::cos(lat_2);
    double sin_lat_2 = std::sin(lat_2);*/

    return std::acos(std::sin(lat_1) * std::sin(lat_2) +
                     std::cos(lat_1) * std::cos(lat_2) *
                     std::cos(std::abs(long_1 - long_2))) * RADIUS * 1000;
}