#include "PhoneNumber.h"
#include <sstream>

PhoneNumber::PhoneNumber(const string &international_number) {
    std::istringstream is(international_number);
    if(international_number[0] == '+'){
        is.ignore(1);
    } else throw invalid_argument("Invalid argument: " + international_number);

    if(!getline(is, country_code_, '-'))
        throw invalid_argument("Invalid argument: " + international_number);

    if(!getline(is, city_code_, '-'))
        throw invalid_argument("Invalid argument: " + international_number);

    if(!getline(is, local_number_))
        throw invalid_argument("Invalid argument: " + international_number);
}

std::string PhoneNumber::GetCountryCode() const {return country_code_;}
std::string PhoneNumber::GetCityCode() const {return city_code_;}
std::string PhoneNumber::GetLocalNumber() const {return local_number_;}
std::string PhoneNumber::GetInternationalNumber() const {
    std::ostringstream os;
    os << "+" << country_code_ << "-" << city_code_ << "-" << local_number_;
    return std::move(os.str());
}


