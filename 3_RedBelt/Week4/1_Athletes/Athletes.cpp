#include <iostream>
#include <list>
#include <map>

using ListIterator = std::list<int>::iterator;

void Emplace(const int& curr, const int& before, std::list<int>& lst){
    bool flag = false;

    for(auto it = lst.begin(); it != lst.end(); ++it){//O(N)
        if(*it == before){
            lst.insert(it, curr);//O(1)
            flag = true;
        }
    }

    if(!flag) lst.push_back(curr);//O(1)
}

void Emplace(const int& curr, const int& before, std::list<int>& lst, std::map<int, ListIterator>& map){
    auto it = map.find(before);//O(logN)

    if(it == map.end()){
        lst.push_back(curr);//O(1)
        map.emplace(std::make_pair(curr,std::prev(lst.end())));//O(logN)
    } else{
        map.emplace(curr, lst.insert(it->second, curr));//O(logN)
    }
}

void test1() {
    std::list<int> lst;

    for(int i = 0; i < 100000; ++i){
        Emplace(i, i - 1, lst);
    }


    for(const auto& item : lst){
        std::cout << item << "\n";
    }
}

void test2() {
    std::list<int> lst;
    std::map<int, ListIterator> map;

    for(int i = 0; i < 100000; ++i){
        Emplace(i, i - 1, lst, map);
    }


    for(const auto& item : lst){
        std::cout << item << "\n";
    }
}


int main() {
    std::list<int> lst;
    std::map<int, ListIterator> map;
    size_t count = 0;
    size_t i = 0;
    std::cin >> count;

    while(i < count) {

        int curr = 0, before = 0;
        std::cin >> curr >> before;

        auto it = map.find(before);

        Emplace(curr, before, lst, map);

        ++i;

    }

    for(const auto& item : lst){
        std::cout << item << "\n";
    }
    //test1();
    //test2();


    return 0;
}
