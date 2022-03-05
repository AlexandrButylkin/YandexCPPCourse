//
// Created by cobak on 26.01.2022.
//

#ifndef TASK_4_RAII_BOOKING__BOOKING_H
#define TASK_4_RAII_BOOKING__BOOKING_H

namespace RAII{
    template<typename T>
    class Booking {
    private:
        T* provider_;
        int id_;

    public:
        Booking(T* provider, int id) : provider_(provider),id_(id){}
        Booking(const Booking&) = delete;

        Booking(Booking&& other) noexcept : provider_(other.provider_), id_(other.id_) {
            other.provider_ = nullptr;
        }

        Booking& operator=(const Booking&) = delete;

        Booking& operator=(Booking&& other) {
            if(provider_ != other.provider_){
                delete provider_;
            }
            provider_ = other.provider_;
            id_ = other.id_;
            other.provider_ = nullptr;
            return *this;
        }

        ~Booking() {
            if(provider_){
                provider_->CancelOrComplete(*this);
            }
        }
    };
}

#endif //TASK_4_RAII_BOOKING__BOOKING_H
