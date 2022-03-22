#include "search_server.h"
#include "../../Utils/ProfillerMod.h"

#include <iterator>
#include <algorithm>
#include <set>
#include <mutex>

using std::istream;
using std::string;
using std::move;
using std::vector;
using std::istringstream;
using std::set;


vector<string> SplitToWords(const string &doc) {
    istringstream is(doc);
    return {std::istream_iterator<string>(is), std::istream_iterator<string>()};
}

void InvertedIndex::Add(std::string document) {
    docs.emplace_back(std::move(document));

    const auto docid = docs.size() - 1;
    for (const auto &item: SplitToWords(docs.back())) {
        auto &vec_pair = index[item];
        if (!vec_pair.empty() && vec_pair.back().first == docid) {
            ++vec_pair.back().second;
        } else {
            index[item].emplace_back(docid, 1);
        }
    }
}

std::vector<std::pair<size_t, size_t>> InvertedIndex::Lookup(const std::string &word) const {
    auto iter = index.find(word);
    if (iter != index.end()) {
        return iter->second;
    } else return {};
}

const std::string &InvertedIndex::GetDocument(size_t id) const {
    return docs[id];
}

size_t InvertedIndex::GetNumDocs() const {
    return docs.size();
}


SearchServer::SearchServer(istream &document_input) {
    UpdateDocumentBase(document_input);
}

void SearchServer::UpdateDocumentBase(istream &document_input) {
    InvertedIndex new_index;

    for (string current_document; getline(document_input, current_document);) {
        new_index.Add(move(current_document));
    }

    std::lock_guard<std::mutex> lg(std::mutex);
    index = move(new_index);
}

void SearchServer::AddQueriesStream(std::istream &query_input, std::ostream &search_results_output) {
    TotalDuration words_split("  Words split");
    TotalDuration lookup("  Lookup");
    TotalDuration sorting("  Sort");
    TotalDuration build_results("  Build results");
    TotalDuration total_iteration("  Total loop iteration");

    const size_t MAX_COUNT = 5;
    std::vector<size_t> docids(50000);
    std::vector<size_t> indexes(50000);

    ADD_DURATION(total_iteration);
    for (string current_query; std::getline(query_input, current_query);) {

        size_t curr_index = 0;
        {
            ADD_DURATION(words_split);
            for (const auto &word: SplitToWords(current_query)) {
                {
                    for (auto[docid, count]: index.Lookup(word)) {
                        if (docids[docid] == 0) {
                            indexes[curr_index++] = docid;
                        }
                        docids[docid] += count;
                    }
                }
            }
        }
        std::vector<std::pair<size_t, size_t>> docid_count;
        docid_count.reserve(curr_index);
        {
            ADD_DURATION(lookup);

            for (size_t i = 0; i < curr_index; ++i) {
                size_t count = 0;
                size_t id = 0;
                std::swap(count, docids[indexes[i]]);
                std::swap(id, indexes[i]);
                docid_count.emplace_back(id, count);
            }
        }

        {
            ADD_DURATION(sorting);
            std::partial_sort(
                    docid_count.begin(),
                    docid_count.begin() + std::min<size_t>(MAX_COUNT, docid_count.size()),
                    docid_count.end(),
                    [](std::pair<size_t, size_t> lhs, std::pair<size_t, size_t> rhs) {
                        int64_t lhs_docid = lhs.first;
                        auto lhs_hit_count = lhs.second;
                        int64_t rhs_docid = rhs.first;
                        auto rhs_hit_count = rhs.second;
                        return std::make_pair(lhs_hit_count, -lhs_docid) > std::make_pair(rhs_hit_count, -rhs_docid);
                    });
        }

        {
            ADD_DURATION(build_results);
            search_results_output << current_query << ":";

            for (size_t i = 0, size = docid_count.size(); i != size && i != 5 && docid_count[i].second != 0; ++i) {
                search_results_output << " {"
                                      << "docid: " << docid_count[i].first << ", "
                                      << "hitcount: " << docid_count[i].second << '}';
            }

            search_results_output << std::endl;
        }
    }
}