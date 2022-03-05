#ifndef TASK_4_ROUTEMANAGER_H
#define TASK_4_ROUTEMANAGER_H

#include <algorithm>
#include <map>
#include <set>
#include <string>

using namespace std;

class RouteManager {
public:
    void AddRoute(int start, int finish) {
        reachable_lists_[start].emplace(finish);
        reachable_lists_[finish].emplace(start);
    }

    [[nodiscard]] int FindNearestFinish(int start, int finish) const {
        int result = abs(start - finish);
        auto iter = reachable_lists_.find(start);
        if (iter == reachable_lists_.end()) {
            return result;
        }

        auto sIter = iter->second.upper_bound(finish);
        if(sIter != iter->second.end()) result = min(result, abs(finish - *(--sIter)));
        else if (sIter == iter->second.begin()) result = min(result, abs(finish - *sIter));
        else result = min(result, min(abs(finish - *sIter), abs(finish - *(--sIter))));

        return result;
    }

private:
    map<int, set<int>> reachable_lists_;
};


#endif //TASK_4_ROUTEMANAGER_H
