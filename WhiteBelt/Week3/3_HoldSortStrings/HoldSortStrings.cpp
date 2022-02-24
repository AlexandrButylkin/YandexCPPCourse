#include <iostream>
#include <vector>
#include <algorithm>

class SortedStrings {
private:
    std::vector<std::string> mset;
public:
  void AddString(const std::string& s) {
      mset.push_back(s);
  }
  std::vector<std::string> GetSortedStrings() {
      std::sort(mset.begin(), mset.end());
      return mset;
  }
};

/*void PrintSortedStrings(SortedStrings& strings) {
  for (const std::string& s : strings.GetSortedStrings()) {
    std::cout << s << " ";
  }
  std::cout << std::endl;
}

int main(){
    SortedStrings strings;
  
    strings.AddString("first");
    strings.AddString("third");
    strings.AddString("second");
    PrintSortedStrings(strings);
  
    strings.AddString("second");
    PrintSortedStrings(strings);
    return 0;
}*/