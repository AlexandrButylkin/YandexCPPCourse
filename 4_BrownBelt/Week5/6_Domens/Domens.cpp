#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <memory>

std::vector<std::string> ReadFullDomains(std::istream& stream) {
    int count;
    stream >> count;
    std::vector<std::string> res(count);
    for (auto& s : res) {
        stream >> s;
    }
    return res;
}

class DomainFilter {
public:
    explicit DomainFilter(const std::vector<std::string>& raw_domains) {
        ParseFullDomains(raw_domains);
    }

    // true - можно пропустить
    // false - пропустить нельзя
    bool FilterDomain(const std::string& domain) {
        auto subdomains = SplitBy(domain);

        auto dom_first = subdomains.back();
        auto* curr_line = &bad_domains_.data_;
        if (!curr_line->count(dom_first)) {
            return true;
        }
        curr_line = &curr_line->at(dom_first)->data_;
        if (curr_line->count("")) {
            return false;
        }
        subdomains.pop_back();
        for (auto i = subdomains.rbegin(); i != subdomains.rend(); ++i) {
            if (!curr_line->count(*i)) {
                return true;
            }
            auto b = *i;
            curr_line = &curr_line->at(*i)->data_;
            if (curr_line->count("")) {
                return false;
            }
        }
        return true;
    }

private:
    struct Item {
        std::unordered_map<std::string, std::shared_ptr<Item>> data_;
    };
    Item bad_domains_;

    void ParseFullDomains(const std::vector<std::string>& raw_domains) {
        for (const auto& domain : raw_domains) {
            auto subdomains = SplitBy(domain);
            std::reverse(subdomains.begin(), subdomains.end());
            auto* curr_line = &bad_domains_.data_;
            for (auto& dom : subdomains) {
                curr_line->insert({dom, std::move(std::make_shared<Item>())});
                curr_line = &curr_line->at(dom)->data_;
            }
            curr_line->insert({"", std::make_shared<Item>()});
        }
    }

    static std::vector<std::string> SplitBy(const std::string & s, char split = '.') {
        std::vector<std::string> result;
        auto curr = s.begin();
        while (curr != s.end()) {
            auto space = std::find(curr, s.end(), split);
            result.emplace_back(std::string(curr, space));
            if (space != s.end()) curr = (space + 1);
            else curr = s.end();
        }
        return result;
    }
};

int main() {
    auto bad_domains = ReadFullDomains(std::cin);
    auto domains = ReadFullDomains(std::cin);
    DomainFilter filter(bad_domains);
    for (const auto& d : domains) {
        auto res = filter.FilterDomain(d);
        if (res) {
            std::cout << "Good" << std::endl;
        }
        else {
            std::cout << "Bad" << std::endl;
        }
    }
    return 0;
}



/*#include <algorithm>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <set>

using namespace std;*/

/*std::set<string> GetBannedDomens () {
    int size = 0;
    std::cin >> size;

    std::set<string> banned_domens;
    while(size != 0){
        string str;
        std::cin >> str;

        banned_domens.emplace(str);

        --size;
    }

    return banned_domens;
};

bool IsSubdomain(const std::string& domain, const std::string& subdomain){
    size_t size = domain.size();
    if(size > subdomain.size()) return false;

    std::string_view subdomain_view(subdomain);
    std::string_view res = subdomain_view.substr(subdomain.size() - size);

    return res == domain;

}

bool IsBanned(const std::set<string>& bd, const string& domain){
    for(const auto& item : bd){
        if(domain == item) return true;
        if(IsSubdomain(item, domain)) return true;
    }
    return false;
}

int main(){
    std::set<string> banned_domens = GetBannedDomens();
    int size = 0;
    std::cin >> size;

    while(size != 0){
        string str;
        std::cin >> str;

        if(IsBanned(banned_domens, str)) std::cout << "Bad\n";
        else std::cout << "Good\n";

        --size;
    }
    return 0;
}*/

/*bool IsSubdomain(string_view subdomain, string_view domain) {
  auto i = subdomain.size() - 1;
  auto j = domain.size() - 1;
  while (i >= 0 && j >= 0) {
    if (subdomain[i--] != domain[j--]) {
      return false;
    }
  }
  return (i < 0 && domain[j] == '.')
      || (j < 0 && subdomain[i] == '.');
}


vector<string> ReadDomains() {
  size_t count;
  cin >> count;

  vector<string> domains;
  for (size_t i = 0; i < count; ++i) {
    string domain;
    getline(cin, domain);
    domains.push_back(domain);
  }
  return domains;
}


int main() {
  const vector<string> banned_domains = ReadDomains();
  const vector<string> domains_to_check = ReadDomains();

  for (string_view domain : banned_domains) {
    reverse(begin(domain), end(domain));
  }
  sort(begin(banned_domains), end(banned_domains));

  size_t insert_pos = 0;
  for (string& domain : banned_domains) {
    if (insert_pos == 0 || !IsSubdomain(domain, banned_domains[insert_pos - 1])) {
      swap(banned_domains[insert_pos++], domain);
    }
  }
  banned_domains.resize(insert_pos);

  for (const string_view domain : domains_to_check) {
    if (const auto it = upper_bound(begin(banned_domains), end(banned_domains), domain);
        it != begin(banned_domains) && IsSubdomain(domain, *prev(it))) {
      cout << "Good" << endl;
    } else {
      cout << "Bad" << endl;
    }
  }
  return 0;
}*/




