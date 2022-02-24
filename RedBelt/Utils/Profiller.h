#ifndef PROFILER_MYPROFILER_H
#define PROFILER_MYPROFILER_H

#include <iostream>
#include <chrono>

#define UNIQUE_ID_IMPL(lineno) _a_local_var##lineno
#define UNIQUE_ID(lineno) UNIQUE_ID_IMPL(lineno)


#define LOG_DURATION(message) \
    LogDuration UNIQUE_ID(__LINE__)(message);

class LogDuration{
private:
    std::chrono::steady_clock::time_point start;
    std::string message;

public:
    explicit LogDuration(const std::string& str = "") :
    start(std::chrono::steady_clock::now()),
    message(str + ": "){}

    size_t GetTime(){
        auto finish = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count();
    }

    ~LogDuration(){
        auto finish = std::chrono::steady_clock::now();
        //std::cerr << message
        //<< std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << std::endl;
    }
};

#endif //PROFILER_MYPROFILER_H
