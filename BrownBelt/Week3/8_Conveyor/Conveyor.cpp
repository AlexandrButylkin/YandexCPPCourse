#include "test_runner.h"
#include <functional>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include <queue>
#include <list>

using namespace std;


struct Email {
    string from;
    string to;
    string body;
};


class Worker {
public:
    virtual ~Worker() = default;

    virtual void Process(unique_ptr<Email> email) = 0;

    virtual void Run() {
        // только первому worker-у в пайплайне нужно это имплементировать
        throw logic_error("Unimplemented");
    }

protected:
    // реализации должны вызывать PassOn, чтобы передать объект дальше
    // по цепочке обработчиков
    void PassOn(unique_ptr<Email> email) const{
        if(next_worker){
            next_worker->Process(std::move(email));
        }
    }

public:
    void SetNext(unique_ptr<Worker> next){
        next_worker = std::move(next);
    }

private:
    unique_ptr<Worker> next_worker;
};


class Reader : public Worker {
public:
    explicit Reader(istream &input) : is(input) {}

    void Process(unique_ptr<Email> email) override {
            Run();
    };

    void Run() final{
        while(is){
            Email email;
            getline(is, email.from);
            getline(is, email.to);
            getline(is, email.body);
            if(is)
                PassOn(make_unique<Email>(email));
        }
    }

private:
    istream &is;
};


class Filter : public Worker {
public:
    using Function = function<bool(const Email &)>;

public:
    explicit Filter(Function  func) : function(std::move(func)) {}

    void Process(unique_ptr<Email> email) override{
        if(function(*email)) {
            PassOn(move(email));
        }
    }


private:
    Function function;
};


class Copier : public Worker {
public:
    // реализуйте класс
    explicit Copier(string str) : address(std::move(str)) {}

    void Process(unique_ptr<Email> email) override{
        if(email->to != address){
            string from = email->from, body = email->body;
            PassOn(move(email));
            Email new_email{from, address, body};
            PassOn(make_unique<Email>(new_email));
        } else PassOn(move(email));
    }


private:
    string address;
};


class Sender : public Worker {
public:
    // реализуйте класс
    explicit Sender(ostream& output) : os(output) {}
    void Process(unique_ptr<Email> email) override{
        os << email->from << '\n' << email->to << '\n' << email->body << '\n';
        PassOn(move(email));
    }

private:
    ostream& os;
};


// реализуйте класс
class PipelineBuilder {
public:
    // добавляет в качестве первого обработчика Reader
    explicit PipelineBuilder(istream &in) {
        pipeline.push_back(make_unique<Reader>(in));
    }

    // добавляет новый обработчик Filter
    PipelineBuilder &FilterBy(Filter::Function filter) {
        pipeline.push_back(make_unique<Filter>(filter));
        return *this;
    }

    // добавляет новый обработчик Copier
    PipelineBuilder &CopyTo(const string& recipient){
        pipeline.push_back(make_unique<Copier>(recipient));
        return *this;
    }

    // добавляет новый обработчик Sender
    PipelineBuilder &Send(ostream &out){
        pipeline.push_back(make_unique<Sender>(out));
        return *this;
    }

    // возвращает готовую цепочку обработчиков
    unique_ptr<Worker> Build(){
        for(size_t i = pipeline.size() - 1; i > 0; --i){
            pipeline[i - 1]->SetNext(std::move(pipeline[i]));
        }
        return move(pipeline[0]);
    }

private:

    std::vector<unique_ptr<Worker>> pipeline;

};


void TestSanity() {
    string input = (
            "erich@example.com\n"
            "richard@example.com\n"
            "Hello there\n"

            "erich@example.com\n"
            "ralph@example.com\n"
            "Are you sure you pressed the right button?\n"

            "ralph@example.com\n"
            "erich@example.com\n"
            "I do not make mistakes of that kind\n"
    );
    istringstream inStream(input);
    ostringstream outStream;

    PipelineBuilder builder(inStream);
    builder.FilterBy([](const Email &email) {
        return email.from == "erich@example.com";
    });
    builder.CopyTo("richard@example.com");
    builder.Send(outStream);
    auto pipeline = builder.Build();

    pipeline->Run();

    string expectedOutput = (
            "erich@example.com\n"
            "richard@example.com\n"
            "Hello there\n"

            "erich@example.com\n"
            "ralph@example.com\n"
            "Are you sure you pressed the right button?\n"

            "erich@example.com\n"
            "richard@example.com\n"
            "Are you sure you pressed the right button?\n"
    );

    ASSERT_EQUAL(expectedOutput, outStream.str());
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestSanity);
    return 0;
}
