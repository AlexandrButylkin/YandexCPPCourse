#include <iostream>
using namespace std;

class Animal {
public:
    explicit Animal(const std::string& name) : Name(name){}
    virtual ~Animal() = default;
private:
    const string Name;
};


class Dog : public Animal{
public:
    explicit Dog(const std::string& name) : Animal(name){};

    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

int main() {
    Dog dog("Bobik");
    dog.Bark();
    return 0;
}
