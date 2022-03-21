#ifndef UNTITLED_AIRPORTCOUNTER_H
#define UNTITLED_AIRPORTCOUNTER_H

#include <array>

template <typename TAirport>
class AirportCounter {
public:
    AirportCounter() { airports.fill(0); }

    template <typename TIterator>
    AirportCounter(TIterator begin, TIterator end) : AirportCounter() {
        for(; begin != end; ++begin){
            Insert(*begin);
        }
    }

    size_t Get(TAirport airport) const {
        return airports[static_cast<size_t>(airport)];
    }

    void Insert(TAirport airport) {
        ++GetItem(airport);
    }

    void EraseOne(TAirport airport) {
        auto i = static_cast<uint32_t>(airport);
        if(airports[i] != 0){
            --airports[i];
        }
    }

    void EraseAll(TAirport airport) {
        GetItem(airport) = 0;
    }


    static const size_t SIZE = static_cast<uint32_t>(TAirport::Last_);
    using Item = pair<TAirport, size_t>;
    using Items = std::array<Item, SIZE>;

    Items GetItems() const {
        Items items;
        for(size_t i = 0; i < airports.size(); ++i){
            auto Airport = static_cast<TAirport>(i);
            auto size = static_cast<size_t>(airports[i]);
            items[i] = std::make_pair(Airport, size);
        }
        return items;
    }

private:
    uint32_t& GetItem(TAirport airport) {
        return airports[static_cast<uint32_t>(airport)];
    }

private:
    std::array<uint32_t, SIZE> airports;
};

#endif //UNTITLED_AIRPORTCOUNTER_H
