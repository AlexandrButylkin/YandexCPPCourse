#ifndef PARTD_JSON_H
#define PARTD_JSON_H

#include <istream>
#include <map>
#include <string>
#include <variant>
#include <vector>
#include <iostream>

namespace Json {

    class Node : std::variant<std::vector<Node>,
            std::map<std::string, Node>,
            double,
            int,
            bool,
            std::string> {
    public:
        using variant::variant;
        const variant &GetBase() const { return *this; }
        const auto &AsArray() const { return std::get<std::vector<Node>>(*this); }
        const auto &AsMap() const { return std::get<std::map<std::string, Node>>(*this); }
        const auto &AsString() const { return std::get<std::string>(*this); }
        double AsDouble() const {
            if(std::holds_alternative<double>(*this)){
                return std::get<double>(*this);
            } else return std::get<int>(*this);
        }
        int AsInt() const { return std::get<int>(*this); }
        bool AsBool() const { return std::get<bool>(*this); }
    };

    class Document {
    public:
        explicit Document(Node root) : root(move(root)) {}

        const Node &GetRoot() const { return root; }

    private:
        Node root;
    };

    Document Load(std::istream &input);
    Node LoadNode(std::istream &input);

    void PrintNode(const Node &node, std::ostream &output);

    template<typename T>
    void PrintValue(const T &value, std::ostream &os) {
        os << value;
    }

    template<>
    void PrintValue<std::string>(const std::string &string, std::ostream &os);

    template<>
    void PrintValue<std::vector<Node>>(const std::vector<Node> &nodes, std::ostream &os);

    template<>
    void PrintValue<std::map<std::string, Node>>(const std::map<std::string, Node> &nodes, std::ostream &os);

    template <>
    void PrintValue<bool>(const bool& value, std::ostream& output);

}
#endif //PARTD_JSON_H