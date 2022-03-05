#ifndef PART1_MY_SEARCH_SERVER_H
#define PART1_MY_SEARCH_SERVER_H

#include <sstream>
#include <string>
#include <list>
#include <unordered_map>
#include <vector>

struct Stats {
    size_t docid_count = 0;
    size_t sort = 0;
    size_t out = 0;
};

class InvertedIndex {
public:
    void Add(std::string document);
    std::vector<std::pair<size_t, size_t>> Lookup(const std::string& word) const;
    const std::string& GetDocument(size_t id) const;

    size_t GetNumDocs() const;

private:
    std::unordered_map<std::string, std::vector<std::pair<size_t, size_t>>> index;
    std::vector<std::string> docs;
};

class SearchServer {
public:
    SearchServer() = default;
    explicit SearchServer(std::istream& document_input);
    void UpdateDocumentBase(std::istream& document_input);
    void AddQueriesStream(std::istream& query_input, std::ostream& search_results_output);

private:
    InvertedIndex index;
};


#endif //PART1_MY_SEARCH_SERVER_H
