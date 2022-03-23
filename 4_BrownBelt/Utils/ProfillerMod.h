#ifndef PROFILER_MYPROFILER_H
#define PROFILER_MYPROFILER_H

#include <string>
#include <chrono>
#include <sstream>
#include <iostream>


struct TotalDuration {
    std::string message;
    std::chrono::steady_clock::duration value;

    explicit TotalDuration(const std::string& msg)
            : message(msg + ": ")
            , value(0) {}

    ~TotalDuration() {
        std::ostringstream os;
        os << message
           << duration_cast<std::chrono::milliseconds>(value).count()
           << " ms" << std::endl;
        std::cerr << os.str();
    }
};

class AddDuration {
public:
    explicit AddDuration(std::chrono::steady_clock::duration& dest)
            : add_to(dest)
            , start(std::chrono::steady_clock::now()) {}

    explicit AddDuration(TotalDuration& dest)
            : AddDuration(dest.value) {}

    ~AddDuration() {
        add_to += std::chrono::steady_clock::now() - start;
    }

private:
    std::chrono::steady_clock::duration& add_to;
    std::chrono::steady_clock::time_point start;
};

#define MY_UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define MY_UNIQ_ID(lineno) MY_UNIQ_ID_IMPL(lineno)

#define ADD_DURATION(value) \
  AddDuration MY_UNIQ_ID(__LINE__){value};

#endif //PROFILER_MYPROFILER_H
