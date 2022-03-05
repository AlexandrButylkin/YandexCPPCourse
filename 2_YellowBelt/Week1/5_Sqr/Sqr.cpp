#include <iostream>
#include <vector>
#include <map>

using namespace std;

template <typename T> T Sqr(const T& x);
template <typename T> std::vector<T> Sqr(const std::vector<T>& vec);
template <typename T, typename  N> std::pair<T, N> Sqr(const std::pair<T, N>& pair);
template <typename T, typename  N> std::map<T, N> Sqr(const std::map<T, N>& map);


template <typename T>
T Sqr(const T& x){
    return x * x;
}

template <typename T>
std::vector<T> Sqr(const std::vector<T>& vec){
    std::vector<T> ans;
    ans.reserve(vec.size());
    for(const T& item : vec)
        ans.emplace_back(Sqr(item));
    return ans;
}

template <typename T, typename N>
std::pair<T, N> Sqr(const std::pair<T, N>& pair){
    return {Sqr(pair.first), Sqr(pair.second)};
}

template <typename T, typename N>
std::map<T, N> Sqr(const std::map<T, N>& map){
    std::map<T, N> ans;
    for(const std::pair<T, N> item : map)
        ans[item.first] = Sqr(item.second);
    return ans;
}

int main(){
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
        cout << ' ' << x;
    }
    cout <<"   " << endl;

    map<int, pair<int, int>> map_of_pairs = {
            {4, {2, 2}},
            {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
    return 0;
}
