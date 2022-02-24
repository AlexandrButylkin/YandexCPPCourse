#ifndef PART2_MY_SYNHRONIZED_H
#define PART2_MY_SYNHRONIZED_H


#include <numeric>
#include <vector>
#include <string>
#include <future>
#include <mutex>
#include <queue>
#include <thread>

template <typename T>
class Synchronized {
public:
    explicit Synchronized(T initial = T()) : value(move(initial)) {}

    struct Access {
        T& ref_to_value;
        std::lock_guard<std::mutex> guard;
    };

    Access GetAccess(){
        return Access{value, std::lock_guard<std::mutex>(mtx)};
    }


private:
    std::mutex mtx;
    T value;
};

#endif //PART2_MY_SYNHRONIZED_H
