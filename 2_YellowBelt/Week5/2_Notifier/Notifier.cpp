#include <iostream>

using namespace std;

void SendSms(const string& number, const string& message) {
    cout << "Send '" << message << "' to number " << number << endl;
}

void SendEmail(const string& email, const string& message) {
    cout << "Send '" << message << "' to e-mail "  << email << endl;
}

class INotifier {
public:
    virtual void Notify(const string& message) const = 0;
    virtual ~INotifier() = default;
};

class SmsNotifier : public INotifier {
public:
    explicit SmsNotifier(std::string  number_) : number(std::move(number_)) {}
    void Notify(const std::string& message)const override;
private:
    std::string number;
};

class EmailNotifier : public INotifier {
public:
    explicit EmailNotifier(std::string email_) : email(std::move(email_)) {}
    void Notify(const std::string& message) const override;
private:
    std::string email;
};

void Notify(INotifier& notifier, const string& message) {
    notifier.Notify(message);
}

int main(){
    SmsNotifier sms{"+7-495-777-77-77"};
    EmailNotifier email{"na-derevnyu@dedushke.ru"};

    Notify(sms, "I have White belt in C++");
    Notify(email, "And want a Yellow one");
}

void SmsNotifier::Notify(const std::string &message) const {
    SendSms(number, message);
}

void EmailNotifier::Notify(const std::string &message) const {
    SendEmail(email, message);
}