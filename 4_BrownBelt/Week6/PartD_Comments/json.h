#ifndef PARTD_JSON_H
#define PARTD_JSON_H

#include <istream>
#include <map>
#include <string>
#include <variant>
#include <vector>
#include <iostream>

/**
 @file json.h
 @brief ������������ ���� ��� ������� JSON

 �������� ������ ��� ������� ��������� json, ��������� ������ ����� ���������� ����: std::vector, std::map, double, int, bool. ��� ������������� � std::Variant ����� �������� ����������� ���� ��� ������. ��� ����� ���������� ������� ����� �� ������, � ������
 @copyright ��� "���� 2"
 @author �������� �. �.
 @date 12-02-2022
 @version 1.0
 @par �������� ������:
    @ref Json::Node
    @ref Json::Document
 @par �������� ������:
    @ref Json::Load
    @ref Json::LoadNode
    @ref Json::PrintNode
    @ref Json::PrintValue
*/


/**
 @brief ������������ ���� ������� JSON
*/
namespace Json {
/**
 @brief ���� JSON

 ����� ������������ ��� ������ ����� JSON, �������� ������ ��� ����������� ���� ����, � ����� �� ������.
 ����� ����������� �� ������������ std::variant, ��������������� ������������ ��� ������ ������,
 ��� ������������� ����� �������� �������������� ����
*/
    class Node : std::variant<std::vector<Node>,
            std::map<std::string, Node>,
            double,
            int,
            bool,
            std::string> {
    public:
        using variant::variant;
        /**
         @brief ������� ����

         ���������� ������� ���� ��� ��������������
         @return ������ �� ������� ����
        */
        const variant &GetBase() const { return *this; }
        /**
         @brief ������� ���� (������)

         ���������� ������� ���� ���������� �� � ��� std::vector
         @return ������ �� ������� ����
        */
        const auto &AsArray() const { return std::get<std::vector<Node>>(*this); }
        /**
         @brief ������� ���� (�����)

         ���������� ������� ���� ���������� �� � ��� std::map
         @return ������ �� ������� ����
        */
        const auto &AsMap() const { return std::get<std::map<std::string, Node>>(*this); }
        /**
         @brief ������� ���� (������)

         ���������� ������� ���� ���������� �� � std::string
         @return ������ �� ������� ����
        */
        const auto &AsString() const { return std::get<std::string>(*this); }
        /**
         @brief ������� ���� (����� � ��������� �������)

         ���������� ������� ���� ���������� �� � double
         @return ������ �� ������� ����
        */
        double AsDouble() const {
            if(std::holds_alternative<double>(*this)){
                return std::get<double>(*this);
            } else return std::get<int>(*this);
        }
        /**
         @brief ������� ���� (����� �����)

         ���������� ������� ���� ���������� �� � int
         @return ������ �� ������� ����
        */
        int AsInt() const { return std::get<int>(*this); }
        /**
         @brief ������� ���� (������)

         ���������� ������� ���� ���������� �� � bool
         @return ������ �� ������� ����
        */
        bool AsBool() const { return std::get<bool>(*this); }
    };


    /**
     @brief ��������

     ������� �������� �����
    */
    class Document {
    public:
        /**
         @brief �����������
         @param root �������� ����
        */
        explicit Document(Node root) : root(move(root)) {}
        /**
         @brief Getter ����
         @return �������� ����
        */
        const Node &GetRoot() const { return root; }

    private:
        Node root; ///< ������� ����
    };
    /**
     @brief ��������� ��������

     �������� ��������, � ������� ������ ������ ��������
     @param input ������� �����
     @return ��������� ��������
    */
    Document Load(std::istream &input);
    /**
     @brief ��������� ����

     �������� ��������, � ������� ������ ������ Node
     @param input ������� �����
     @return ��������� ����
    */
    Node LoadNode(std::istream &input);
    /**
     @brief ������� ����

     �������� ���������� ���� � �������� �����
     @param node ����
     @param output �������� �����
    */
    void PrintNode(const Node &node, std::ostream &output);

    /**
     @brief ������ ������ ����

     �������� �������� ���� T � ������� ��� � �������� �����
     @param value ��������
     @param os �������� �����
    */
    template<typename T>
    void PrintValue(const T &value, std::ostream &os) {
        os << value;
    }

    /**
     @brief ����������������� ������ ������ ���� (std::string)
     @param string ������
     @param os �������� �����
    */
    template<>
    void PrintValue<std::string>(const std::string &string, std::ostream &os);
    /**
     @brief ����������������� ������ ������ ���� (std::vector)
     @param nodes ������
     @param os �������� �����
    */
    template<>
    void PrintValue<std::vector<Node>>(const std::vector<Node> &nodes, std::ostream &os);
    /**
     @brief ����������������� ������ ������ ���� (std::map)
     @param nodes �����
     @param os �������� �����
    */
    template<>
    void PrintValue<std::map<std::string, Node>>(const std::map<std::string, Node> &nodes, std::ostream &os);
    /**
     @brief ����������������� ������ ������ ���� (bool)
     @param nodes ������
     @param os �������� �����
    */
    template <>
    void PrintValue<bool>(const bool& value, std::ostream& output);

}
#endif //PARTD_JSON_H