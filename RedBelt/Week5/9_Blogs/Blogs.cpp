#include "test_runner.h"
#include "C:\Users\cobak\CLionProjects\red_belt\profiler\MyProfiler.h"
#include <execution>

#include <map>
#include <string>
#include <functional>
#include <future>
#include <iterator>
using namespace std;

template <typename T>
class Page{
private:
    T begin_;
    T end_;
public:
    Page(T vBegin, T vEnd) : begin_(std::move(vBegin)), end_(std::move(vEnd)) {}

    T begin() const {return  begin_;}
    T end() const {return end_;}

    [[nodiscard]] size_t size() const {return std::distance(begin_, end_);}

};

template <typename Iterator>
class Paginator {
private:
    std::vector<Page<Iterator>> pages;
public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        while(begin != end){
            pages.emplace_back(begin, std::next(begin, std::min(page_size, static_cast<size_t>(std::distance(begin, end)))));
            begin = std::next(begin, std::min(page_size, static_cast<size_t>(std::distance(begin, end))));
        }
    }

    auto begin() const {return pages.begin();}
    auto end() const {return pages.end();}

    [[nodiscard]] size_t size() const {return pages.size();}
};

template <typename C>
auto Paginate(C& c, size_t page_size){
    return Paginator(c.begin(), c.end(), page_size);
}


struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other){
        for(auto& item : other.word_frequences){
            word_frequences[item.first] += item.second;
        }
    }
};

std::vector<std::string> Split(istream& input){

}

using Iterator = std::vector<std::string>::iterator;
template <typename T>
Stats ExploreKeyWordSingleThread(const set<string>& key_words, T& container){
    Stats res;
    for(auto& item : container){
        if(key_words.find(item) != key_words.end()){
            ++res.word_frequences[item];
        }
    }

    return res;

}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {

    const size_t num_threads = 1;

    std::vector<std::string> strings((
            istream_iterator<std::string>(input)),istream_iterator<std::string>()
                                             );
    Stats res;
    std::vector<std::future<Stats>> futures;
    futures.reserve(num_threads);

    for(auto& item : Paginate(strings, strings.size() / num_threads)){
        futures.push_back(async([&key_words, item] {return ExploreKeyWordSingleThread(key_words, item); }));
    }

    for(auto& item : futures){
        res += item.get();
    }
    return  res;
}

void TestBasic() {
    const set<string> key_words = {"yangle", "rocks", "sucks", "all"};

    stringstream ss;
    ss << "this new yangle service really rocks\n";
    ss << "It sucks when yangle isn't available\n";
    ss << "10 reasons why yangle is the best IT company\n";
    ss << "yangle rocks others suck\n";
    ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

    const auto stats = ExploreKeyWords(key_words, ss);
    const map<string, int> expected = {
            {"yangle", 6},
            {"rocks", 2},
            {"sucks", 1}
    };
    ASSERT_EQUAL(stats.word_frequences, expected);
}

void f(std::vector<int>::iterator a, int i){
    *a = i;
}

int main() {
    //TestRunner tr;
    //RUN_TEST(tr, TestBasic);
    {LOG_DURATION("Test Single");
        std::vector<int> a(10000000);
        int i = 0;
        for_each(std::execution::seq, a.begin(), a.end(), [&i](int& n){
            n = i;
            ++i; });
        sort(std::execution::seq, a.rbegin(), a.rend());
    }
    {LOG_DURATION("Test Multi");
        std::vector<int> a(10000000);
        int i = 0;
        for_each(std::execution::par, a.begin(), a.end(), [&i](int& n){
            n = i;
            ++i; });
        sort(std::execution::par, a.rbegin(), a.rend());
    }

    return 0;
}