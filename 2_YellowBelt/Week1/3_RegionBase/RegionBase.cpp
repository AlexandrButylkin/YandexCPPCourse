#include <iostream>
#include <vector>
#include <map>
#include <tuple>

enum class Lang {
    DE = 0,
    FR = 1,
    IT = 2
};

struct Region final {
    std::string std_name;
    std::string parent_std_name;
    std::map<Lang, std::string> names;
    int64_t population;
};

bool operator==(const Region &lhs, const Region &rhs) {
    return std::tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) ==
           std::tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

bool operator<(const Region &lhs, const Region &rhs) {
    return std::tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
           std::tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

using RegionBase = std::map<Region, int>;

int FindMaxRepetitionCount(const std::vector<Region> &region) {
    int count = 0;
    RegionBase base;
    for (const auto &item: region) {
        count = std::max(count, ++base[item]);
    }

    return count;
}

int main() {
    std::cout << FindMaxRepetitionCount(
            {
                    {
                            "Moscow",
                            "Russia",
                            {
                                    {Lang::DE, "Moskau"},
                                    {Lang::FR, "Moscou"},
                                    {Lang::IT, "Mosca"}
                            },
                            89
                    },
                    {
                            "Russia",
                            "Eurasia",
                            {
                                    {Lang::DE, "Russland"},
                                    {Lang::FR, "Russie"},
                                    {Lang::IT, "Russia"}
                            },
                            89
                    },
                    {
                            "Moscow",
                            "Russia",
                            {
                                    {Lang::DE, "Moskau"},
                                    {Lang::FR, "Moscou"},
                                    {Lang::IT, "Mosca"}
                            },
                            89
                    },
                    {
                            "Moscow",
                            "Russia",
                            {
                                    {Lang::DE, "Moskau"},
                                    {Lang::FR, "Moscou"},
                                    {Lang::IT, "Mosca"}
                            },
                            89
                    },
                    {
                            "Russia",
                            "Eurasia",
                            {
                                    {Lang::DE, "Russland"},
                                    {Lang::FR, "Russie"},
                                    {Lang::IT, "Russia"}
                            },
                            89
                    },
            })
              << std::endl;

    std::cout << FindMaxRepetitionCount(
            {
                    {
                            "Moscow",
                            "Russia",
                            {
                                    {Lang::DE, "Moskau"},
                                    {Lang::FR, "Moscou"},
                                    {Lang::IT, "Mosca"}
                            },
                            89
                    },
                    {
                            "Russia",
                            "Eurasia",
                            {
                                    {Lang::DE, "Russland"},
                                    {Lang::FR, "Russie"},
                                    {Lang::IT, "Russia"}
                            },
                            89
                    },
                    {
                            "Moscow",
                            "Russia",
                            {
                                    {Lang::DE, "Moskau"},
                                    {Lang::FR, "Moscou deux"},
                                    {Lang::IT, "Mosca"}
                            },
                            89
                    },
                    {
                            "Moscow",
                            "Toulouse",
                            {
                                    {Lang::DE, "Moskau"},
                                    {Lang::FR, "Moscou"},
                                    {Lang::IT, "Mosca"}
                            },
                            89
                    },
                    {
                            "Moscow",
                            "Russia",
                            {
                                    {Lang::DE, "Moskau"},
                                    {Lang::FR, "Moscou"},
                                    {Lang::IT, "Mosca"}
                            },
                            31
                    },
            })
              << std::endl;

    return 0;
}
