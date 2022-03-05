#include "json.h"

using namespace std;

namespace Json {

    Node LoadArray(istream& input) {
        vector<Node> result;

        for (char c; input >> c && c != ']'; ) {
            if (c != ',') {
                input.putback(c);
            }
            result.push_back(LoadNode(input));
        }

        return Node(move(result));
    }

    Node LoadNumber(istream& input) {
        int i_result = 0;
        while(isdigit(input.peek())){
            i_result *= 10;
            i_result += input.get() - '0';
        }
        if(input.peek() == '.'){
            input.get();
            double d_result = i_result;
            double multiplier = 0.1;
            while(isdigit(input.peek())){
                d_result += multiplier * (input.get() - '0');
                multiplier /= 10;
            }
            return Node(d_result);
        } else return Node(i_result);
    }

    Node LoadBool(istream& input){
        std::string result;
        result.reserve(5);
        while(isalpha(input.peek())){
            result.push_back(input.get());
        }
        return Node(result == "true");
    }

    Node LoadString(istream& input) {
        string line;
        getline(input, line, '"');
        return Node(move(line));
    }

    Node LoadDict(istream& input) {
        map<string, Node> result;

        for (char c; input >> c && c != '}'; ) {
            if (c == ',') {
                input >> c;
            }

            string key = LoadString(input).AsString();
            input >> c;
            result.emplace(move(key), LoadNode(input));
        }

        return Node(move(result));
    }

    Node LoadNode(istream& input) {
        char c;
        input >> c;

        if (c == '[') {
            return LoadArray(input);
        } else if (c == '{') {
            return LoadDict(input);
        } else if (c == '"') {
            return LoadString(input);
        } else if(c == 't' || c == 'f') {
            input.putback(c);
            return LoadBool(input);
        } else {
            input.putback(c);
            return LoadNumber(input);
        }
    }

    Document Load(istream& input) {
        return Document{LoadNode(input)};
    }

    void PrintNode(const Json::Node& node, std::ostream& output) {
        visit([&output](const auto& value) { PrintValue(value, output); },
              node.GetBase());
    }

    template<>
    void PrintValue<std::string>(const std::string& string, std::ostream& os){
        os << '"' << string << '"';
    }

    template<>
    void PrintValue<std::vector<Node>>(const std::vector<Node>& nodes, std::ostream& os){
        os << '[';
        bool first = true;
        for(const Node& node : nodes){
            if(!first) os << ", ";
            first = false;
            PrintNode(node, os);
        }
        os << ']';
    }

    template<>
    void PrintValue<std::map<std::string, Node>>(const std::map<std::string, Node>& nodes, std::ostream& os){
        os << '{';
        bool first = true;
        for (const auto& [key, node]: nodes) {
            if (!first) os << ", ";
            first = false;
            PrintValue(key, os);
            os << ": ";
            PrintNode(node, os);
        }
        os << '}';
    }

    template <>
    void PrintValue<bool>(const bool& value, std::ostream& output) {
        output << std::boolalpha << value;
    }
}

