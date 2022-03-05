#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <exception>
#include <iomanip>
using namespace std;

void parse(std::string& str, std::string& command, std::string& date, std::string& event){
  int i = 0, start = 0;
  while(str[i] != ' ' && str[i] != '\000'){
    ++i;
  }
  command = str.substr(start, i - start);
  if(str[i] == ' '){
    start = ++i;
    while(str[i] != '\000' && str[i] != ' ')
      ++i;
    if(str[i] == ' '){
        date = str.substr(start, i - start);
        start = ++i;
        event = str.substr(start, str.size() - start);
    }
    else date = str.substr(start, str.size() - start);
  }
}

class Date {
private:
    int year;
    int month;
    int day;
public:
    Date() : year(0), month(0), day(0){};
    Date(const int& year_, const int& month_, const int& day_) : year(year_), month(month_), day(day_) {}
    Date(const Date& date) : year(date.year), month(date.month), day(date.day) {}
    explicit Date(std::string& date){
        istringstream is(date);
        try{
            is >> *this;
        } catch(runtime_error& msg) {
            std::string str = msg.what();
            if(str == "Wrong date format: "){
                throw runtime_error(msg.what() + date);
            }
            throw runtime_error(msg);
        }
    }
    Date& operator=(const Date& date){
        if(this == &date){
            return *this;
        }
        year = date.year;
        month = date.month;
        day = date.day;
        return *this;
    }
    
    friend std::istream& operator>>(std::istream& is, Date& date){
        int day = 0, month = 0, year;
        std::string str;
        if(is >> year) date.year = year;
        else throw runtime_error("Wrong date format: ");
        if(is.peek() == '-') is.ignore(1);
        else throw runtime_error("Wrong date format: ");
        if(!(is >> month)) throw runtime_error("Wrong date format: ");
        if(is.peek() == '-') is.ignore(1);
        else throw runtime_error("Wrong date format: ");
        if(!(is >> day)) throw runtime_error("Wrong date format: ");
        if(is.eof()){
            if(month > 0 && month < 13) date.month = month;
            else throw runtime_error("Month value is invalid: " + to_string(month));
            if(day > 0 && day < 32) date.day = day;
            else throw runtime_error("Day value is invalid: " + to_string(day));
            return is;
        } else throw runtime_error("Wrong date format: ");
    }
    friend std::ostream& operator<<(std::ostream& os, const Date& date){
        os << std::setw(4) << std::setfill('0') << date.year << "-";
        std::cout << std::setw(2) << std::setfill('0') << date.month << "-";
        std::cout << std::setw(2) << std::setfill('0') << date.day;
        return os;
    }

    friend bool operator==(const Date& lhs, const Date& rhs){
        if(lhs.year == rhs.year){
            if(lhs.month == rhs.month) return lhs.day == rhs.day;
            else return false;
        }
        else return false;
    }
    friend bool operator<(const Date& lhs, const Date& rhs){
        if(lhs.year != rhs.year) return lhs.year < rhs.year;
        else if(lhs.month != rhs.month) return lhs.month < rhs.month;
        else return lhs.day < rhs.day;
    }
};

bool operator<(const Date& lhs, const Date& rhs);

class Database {
private:
    std::map<Date, std::set<std::string>> database;

public:
    void AddEvent(const Date& date, const std::string& event){
        database[date].emplace(event);
    }

    bool DeleteEvent(const Date& date, const std::string& event){
        if(database.count(date) > 0){  
          if(database.find(date)->second.erase(event)){
              return true;
          }
        }
        return false;
    }

    int DeleteDate(const Date& date){
      if(database.find(date) != database.end()){
        int numberOfEvents = database.find(date)->second.size();
        database.erase(date);
        return numberOfEvents; 
      }
      return 0;
    }

    std::set<std::string> Find(const Date& date) const{
        if(database.find(date) != database.end()){
            return database.find(date)->second;
        }
        return {};
    }

    void Print() const{
        for(const std::pair<Date, std::set<std::string>>& item : database){
            for(const std::string& str : item.second){
                std::cout << item.first << " " << str << std::endl;
            }
        }
    }
};