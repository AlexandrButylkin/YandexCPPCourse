#ifndef TASK7_PAGINATOR_H
#define TASK7_PAGINATOR_H
#include <vector>
#include <algorithm>

template <typename T>
class Page {
private:
    T begin_;
    T end_;
    size_t size_;
public:
    Page(T vBegin, T vEnd) :
            begin_(vBegin),
            end_(vEnd),
            size_(std::distance(begin_, end_)) {}

    T begin() const {return  begin_;}
    T end() const {return end_;}

    size_t size() const {return size_;}

};

template <typename Iterator>
class Paginator {
private:
    std::vector<Page<Iterator>> pages;

public:
    Paginator(Iterator begin, Iterator end, size_t page_size);

    auto begin() const {return pages.begin();}
    auto end() const {return pages.end();}

    size_t size() const {return pages.size();}
};

template <typename Iterator>
Paginator<Iterator>::Paginator(Iterator begin, Iterator end, size_t page_size) {

    for(size_t size_ = std::distance(begin, end); size_ > 0; ){
        size_t distance_to_next = std::min(page_size, size_);
        Iterator next = std::next(begin, distance_to_next);
        pages.emplace_back(begin, next);

        size_ -= distance_to_next;
        begin = next;
    }
}

template <typename C>
auto Paginate(C& c, size_t page_size){
    return Paginator(c.begin(), c.end(), page_size);
}



#endif //TASK7_PAGINATOR_H
