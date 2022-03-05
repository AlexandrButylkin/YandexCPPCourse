//
// Created by cobak on 12.02.2022.
//

#ifndef PARTA_COORDINATES_H
#define PARTA_COORDINATES_H


class Coordinates {
private:
    constexpr static double PI = 3.1415926535;
    constexpr static double RADIUS = 6371.0;

    double latitude_;
    double longitude_;
public:
    Coordinates(double latitude = 0.0, double longitude = 0.0) : latitude_(latitude), longitude_(longitude) {}

    double GetLatitude();
    double GetLongitude();

    double GetLatitude() const;
    double GetLongitude() const;

    static double Distance(const Coordinates& from, const Coordinates& to);
};


#endif //PARTA_COORDINATES_H
