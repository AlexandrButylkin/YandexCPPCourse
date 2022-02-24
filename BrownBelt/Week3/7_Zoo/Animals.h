//
// Created by cobak on 22.01.2022.
//

#ifndef TASK_7_ANIMALS_H
#define TASK_7_ANIMALS_H

#include <string>

class Animal {
public:
    virtual std::string Voice() const {
        return "Not implemented yet";
    }
    virtual ~Animal() {
    }
};


class Tiger: public Animal {
    std::string Voice() const override {
        return "Rrrr";
    }
};


class Wolf: public Animal {
    std::string Voice() const override {
        return "Wooo";
    }
};


class Fox: public Animal {
    std::string Voice() const override {
        return "Tyaf";
    }
};



#endif //TASK_7_ANIMALS_H
