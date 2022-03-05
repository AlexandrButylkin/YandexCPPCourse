#include "Common.h"

#include <list>
#include <unordered_map>
#include <utility>
#include <mutex>

using namespace std;

class LruCache : public ICache {
public:
    LruCache(
            shared_ptr<IBooksUnpacker> books_unpacker,
            const Settings& settings
    ) : unpacker(std::move(books_unpacker)), settings_(settings), curr_size(0) {}

    BookPtr GetBook(const string& book_name) override {

        {
            lock_guard<std::mutex> lg(mtx);
            if(iterators.find(book_name) != iterators.end()) {
                if (std::prev(cache.end())->get()->GetName() == book_name) return *std::prev(cache.end());
                else return PermutationBook(book_name);
            }
        }

        auto book = unpacker->UnpackBook(book_name);
        size_t book_size = book->GetContent().size();

        {
            lock_guard<std::mutex> lg(mtx);
            if(settings_.max_memory < book_size){
                return std::move(book);
            }
        }

        {
            lock_guard<std::mutex> lg(mtx);
            return AddBook(std::move(book), book_size);
        }

    }

private:
    Settings settings_;
    std::shared_ptr<IBooksUnpacker> unpacker;
    size_t curr_size;

    std::list<std::shared_ptr<const IBook>> cache;

    using ListIter = std::list<std::shared_ptr<const IBook>>::iterator;

    std::unordered_map<string, ListIter> iterators;

    std::mutex mtx;

private:

    BookPtr AddBook(BookPtr book, size_t book_size){
        ResizeCache(book_size);

        cache.emplace_back(std::move(book));
        curr_size += book_size;
        iterators[std::prev(cache.end())->get()->GetName()] = std::prev(cache.end());

        return *std::prev(cache.end());
    }

    BookPtr PermutationBook(const string& book_name){
        auto iter = iterators[book_name];
        cache.emplace_back(std::move(*iter));
        cache.erase(iter);

        iterators[book_name] = std::prev(cache.end());

        return *std::prev(cache.end());
    }

    void ResizeCache(size_t new_book_size){
        while(curr_size + new_book_size > settings_.max_memory){
            auto elem = cache.front();
            iterators.erase(elem->GetName());
            cache.pop_front();
            curr_size -= elem->GetContent().size();
        }
    }

};


unique_ptr<ICache> MakeCache(
        shared_ptr<IBooksUnpacker> books_unpacker,
        const ICache::Settings& settings
) {
    return make_unique<LruCache>(books_unpacker, settings);
}
