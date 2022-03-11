#include <iostream>
#include <exception>
#include <system_error>
#include <string>

using namespace std;

string AskTimeServer(int i) {
    if(i == 0) {
        throw system_error(std::error_code(), "System error");
    } else if(i == 1){
        throw runtime_error("Runtime error");
    } else if (i == 2) {
        throw invalid_argument("Invalid argument");
    }
    return "00:00:02";
}

class TimeServer final {
public:

    explicit TimeServer(int code) : code_(code) {}

    string GetCurrentTime() {
        try{
            last_fetched_time = AskTimeServer(code_);
            return last_fetched_time;
        } catch (system_error& ){
            std::cerr << "Exception Handling ... \n";

            return last_fetched_time;
        } catch (...){
            throw;
        }
    }

private:
    int code_;
    string last_fetched_time = "00:00:00";
};

int main() {
    {
        TimeServer ts(0);
        try {
            cout << ts.GetCurrentTime() << " - Current time" << endl;
        } catch (exception &e) {
            cerr << "Exception got: " << e.what() << endl;
        }
    }

    {
        TimeServer ts(1);
        try {
            cout << ts.GetCurrentTime() << " - Current time" << endl;
        } catch (exception& e) {
            cerr << "Exception got: " << e.what() << endl;
        }
    }

    {
        TimeServer ts(2);
        try {
            cout << ts.GetCurrentTime() << " - Current time" << endl;
        } catch (exception& e) {
            cerr << "Exception got: " << e.what() << endl;
        }
    }

    {
        TimeServer ts(3);
        try {
            cout << ts.GetCurrentTime() << " - Current time" << endl;
        } catch (exception &e) {
            cerr << "Exception got: " << e.what() << endl;
        }
    }
    return 0;
}
