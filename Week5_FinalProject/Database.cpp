// Реализуйте функции и методы классов и при необходимости добавьте свои
//#include "DataBase.h"
#include "DataBase.h"
using namespace std;


int main() {
  Database db;
  
  string str;
  while (getline(cin, str)) {
    string command, date, event;
    parse(str, command, date, event);
    try{
      if(command == "Add"){
          db.AddEvent(Date(date), event);
      } 
      else if(command == "Del"){
        if(event != ""){
          if(db.DeleteEvent(Date(date), event)){
            std::cout << "Deleted successfully" << std::endl;
          } else {
            std::cout << "Event not found" << std::endl;
          } 
        } else {
          int numbers = db.DeleteDate(Date(date));
          std::cout << "Deleted " << numbers << " events" << std::endl;
        }
      }
      else if(command == "Find"){
        std::set<std::string> events = db.Find(Date(date));
        for(const std::string& str : events){
          std::cout << str << std::endl;
        }
      }
      else if(command == "Print"){
        db.Print();
      }
      else if(command == ""){
        continue;
      } else{
        std::cout << "Unknown command: " << command << std::endl;
      }
    } catch (runtime_error& msg){
      std::cout << msg.what() << std::endl;
    }
  }

  return 0;
}