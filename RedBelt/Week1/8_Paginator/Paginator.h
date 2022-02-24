#ifndef TASK7_PAGINATOR_H
#define TASK7_PAGINATOR_H
#include <vector>
#include <algorithm>

template <typename T>
class Page{
private:
    T begin_;
    T end_;
public:
    Page(T vBegin, T vEnd) : begin_(std::move(vBegin)), end_(std::move(vEnd)) {}

    T begin() const {return  begin_;}
    T end() const {return end_;}

    [[nodiscard]] size_t size() const {return std::distance(begin_, end_);}

};

template <typename Iterator>
class Paginator {
private:
    std::vector<Page<Iterator>> pages;
public:
    Paginator(Iterator begin, Iterator end, size_t page_size) {
        while(begin != end){
            pages.emplace_back(begin, std::next(begin, std::min(page_size, static_cast<size_t>(std::distance(begin, end)))));
            begin = std::next(begin, std::min(page_size, static_cast<size_t>(std::distance(begin, end))));
        }
    }

    auto begin() const {return pages.begin();}
    auto end() const {return pages.end();}

    [[nodiscard]] size_t size() const {return pages.size();}
};

template <typename C>
auto Paginate(C& c, size_t page_size){
    return Paginator(c.begin(), c.end(), page_size);
}

#endif //TASK7_PAGINATOR_H
