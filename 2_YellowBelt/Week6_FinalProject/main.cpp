#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"


#include <iostream>
#include <stdexcept>
#include <sstream>

template <typename T, typename N>
std::ostream& operator<<(std::ostream& os,const std::pair<T, N>& pair){
    os << pair.first << " " << pair.second;
    return os;
}

using namespace std;
string ParseEvent(istream& is) {
    is >> ws;
    std::string event;
    getline(is, event);
    return event;
}

int main() {
    Database db;

    for (string line; getline(cin, line); ) {
        std::istringstream is(line);
        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}


/*#include <iostream>
#include <stdexcept>
#include <sstream>

std::string ParseEvent(std::istream& is) {
    is >> std::ws;
    std::string event;
    getline(is, event);
    return event;
}

#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "database.h"
#include "token.h"
#include "test_runner.h"
#include "MyTests.h"



int main(){
    TEST_PARSE_CONDITION();
    return 0;
}*/
