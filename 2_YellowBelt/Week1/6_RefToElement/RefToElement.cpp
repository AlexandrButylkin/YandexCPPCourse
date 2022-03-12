#include <iostream>
#include <vector>
#include <map>
#include <exception>

using namespace std;

template <typename T, typename  N> N& GetRefStrict(const std::map<T, N>& map, const T& key);

template <typename T, typename N>
N& GetRefStrict(std::map<T, N>& map, const T& key){
    const auto iter = map.find(key);
    if(iter != map.end()){
        return iter->second;
    } else throw runtime_error("Key not found");
}

int main(){
    try {
        map<int, string> m = {{0, "value"}};
        string &item = GetRefStrict(m, 0);
        item = "newvalue";
        cout << m[0] << endl; // выведет newvalue
        string &item1 = GetRefStrict(m, 1);
    } catch (runtime_error& msg){
        std::cout << msg.what() << std::endl;
    }
    return 0;
}

