#ifndef WEEK6_TEST_RUNNER_H
#define WEEK6_TEST_RUNNER_H
#include <iostream>
#include <functional>
#include <string>
#include <exception>
#include <sstream>

#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"


template <typename T>
bool MyAssert(const T& first, const T& second, const std::string& hint){
    if(first != second){
        std::ostringstream os;
        os << "Assertion failed " << first << " != " << second << " " << hint;
        throw std::runtime_error(os.str());
    }
}


class test_runner {
public:
    template <typename TestFunc>
    void run(TestFunc& func, const std::string& name){
        try {
            func();
            std::cerr << "Test: " << name << " DONE" << std::endl;
        } catch (std::runtime_error& msg){
            ++fail_count;
            std::cerr << "Test: " << name << " FAIL: " << msg.what() << std::endl;
        }
    }

    ~test_runner(){
        if(fail_count > 0){
            std::cerr << fail_count << " unit tests failed. Terminate" << std::endl;
            exit(1);
        }
    }

private:
    int fail_count = 0;
};


#endif //WEEK6_TEST_RUNNER_H
