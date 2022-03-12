#ifndef WEEK3_PHONE_NUMBER_H
#define WEEK3_PHONE_NUMBER_H

#include <string>

using namespace std;

class PhoneNumber final {
public:
    explicit PhoneNumber(const string &international_number);

    string GetCountryCode() const;
    string GetCityCode() const;
    string GetLocalNumber() const;
    string GetInternationalNumber() const;

private:
    string country_code_;
    string city_code_;
    string local_number_;
};


#endif //WEEK3_PHONE_NUMBER_H
