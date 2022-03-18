#ifndef TASK_4_ROUTEMANAGER_H
#define TASK_4_ROUTEMANAGER_H

#include <map>
#include <set>
#include <string>


class RouteManager {
public:

    void AddRoute(int start, int finish) {
        reachable_lists_[start].emplace(finish);
        reachable_lists_[finish].emplace(start);
    }

    int FindNearestFinish(int start, int finish) const {
        int result = abs(start - finish);
        auto iter = reachable_lists_.find(start);
        if (iter == reachable_lists_.end()) {
            return result;
        }

        auto sIter = iter->second.upper_bound(finish);

        if (sIter != iter->second.end()) {
            result = std::min(result, abs(finish - *sIter));
        }

        if (sIter != iter->second.begin()) {
            result = std::min(result, abs(finish - *(std::prev(sIter))));
        }

        return result;
    }

private:
    std::map<int, std::set<int>> reachable_lists_;
};


#endif //TASK_4_ROUTEMANAGER_H
