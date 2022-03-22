#include "../../Utils/TestRunner.h"
#include "../../Utils/Profiller.h"
#include "Paginator.h"

#include <execution>

#include <map>
#include <functional>
#include <future>
#include <iterator>
using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator+= (const Stats& other){
        for(auto& [word, freq] : other.word_frequences){
            word_frequences[word] += freq;
        }
    }
};

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

    const size_t num_threads = 4;

    std::vector<std::string> strings((
                                             istream_iterator<std::string>(input)),istream_iterator<std::string>());
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
    TestRunner tr;
    RUN_TEST(tr, TestBasic);
    return 0;
}