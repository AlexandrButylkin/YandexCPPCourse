#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Person {
public:
    explicit Person(std::string name, std::string type = "Human") : Name(std::move(name)), Type(std::move(type)) {}

    virtual void Walk(const std::string& destination) const = 0;

    std::string TypeWithName () const {
        return Type + ": " + Name;
    }

    std::string GetName() const { return Name; }
    std::string GetType() const { return Type; }

protected:
    const std::string Name;
    const std::string Type;
};

class Student : public Person{
public:
    Student(string name, string favouriteSong) :
        Person(std::move(name), "Student"),
        FavouriteSong(std::move(favouriteSong)) {}

    void SingSong() const {
        cout << TypeWithName() << " sings a song: " << FavouriteSong << endl;
    }

    void Walk(const std::string &destination) const override {
        cout << TypeWithName() << " walks to: " << destination << endl;
        SingSong();
    }

    void Learn() const {
        cout << TypeWithName() << " learns" << endl;
    }

private:
    const std::string FavouriteSong;
};

class Teacher : public Person {
public:
    Teacher(string name, string subject) : Person(std::move(name), "Teacher"), Subject(std::move(subject)) {}

    void Walk(const std::string &destination) const override{
        cout << TypeWithName() << " walks to: " << destination << endl;
    }

    void Teach() const {
        cout << TypeWithName() << " teaches: " << Subject << endl;
    }

private:
    const std::string Subject;
};

class Policeman : public Person {
public:
    explicit Policeman(std::string name) : Person(std::move(name), "Policeman") {}

    void Walk(const std::string &destination) const override{
        cout <<  TypeWithName() << " walks to: " << destination << endl;
    }

    void Check(const Person& person) const {
        std::cout <<  TypeWithName() << " checks " << person.GetType() <<
        ". " << person.GetType() << "'s name is: " <<
        person.GetName() << std::endl;
    }
};

void VisitPlaces(const Person& person, const vector<string>& places) {
    for (const auto& p : places) {
        person.Walk(p);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");


    t.Teach();

    s.SingSong();
    s.Learn();

    p.Check(s);
    p.Check(t);
    p.Check(p);

    VisitPlaces(t, {"Moscow", "London"});
    VisitPlaces(s, {"Moscow", "London"});
    VisitPlaces(p, {"Moscow", "London"});

    return 0;
}
