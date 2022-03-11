#include "DataBase.h"

void ADD(std::istream& is, Database& db){
    std::string event, date;
    is >> date >> event;

    db.AddEvent(StringToDate(date), event);
}

void DEL(std::istream& is, Database& db){
    std::string event, date;
    is >> date >> event;

    if(!event.empty()){
        if(db.DeleteEvent(StringToDate(date), event)){
            std::cout << "Deleted successfully" << std::endl;
        } else {
            std::cout << "Event not found" << std::endl;
        }
    } else {
        size_t count = db.DeleteDate(StringToDate(date));
        std::cout << "Deleted " << count << " events" << std::endl;
    }
}

void FIND(std::istream& is, Database& db){
    std::string date;
    is >> date;

    for(const std::string& str : db.Find(StringToDate(date))){
        std::cout << str << std::endl;
    }
}

void PRINT(Database& db){
    db.Print();
}


int main() {
    Database db;
    std::string str;
    while (getline(std::cin, str)) {
        std::istringstream is(str);
        std::string command;
        is >> command;
        try{
            if(command == "Add"){
                ADD(is, db);
            }
            else if(command == "Del"){
                DEL(is, db);
            }
            else if(command == "Find"){
                FIND(is, db);
            }
            else if(command == "Print"){
                PRINT(db);
            } else if (command.empty()) {
                continue;
            } else {
                std::cout << "Unknown command: " << command << std::endl;
            }
        } catch (std::runtime_error& msg){
            std::cout << msg.what() << std::endl;
        }
    }

    return 0;
}

