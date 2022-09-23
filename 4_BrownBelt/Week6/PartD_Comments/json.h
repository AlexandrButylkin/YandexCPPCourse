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
 @brief Заголовочный файл для парсера JSON

 Содержит методы для разбора документа json, Позволяет читать файлы содержащие типы: std::vector, std::map, double, int, bool. При необходимости в std::Variant можно добавить собственные типы для чтения. Для этого необходимо описать метод их чтения, и записи
 @copyright ОАО "Лаба 2"
 @author Бутылкин А. И.
 @date 12-02-2022
 @version 1.0
 @par Содержит классы:
    @ref Json::Node
    @ref Json::Document
 @par Содержит методы:
    @ref Json::Load
    @ref Json::LoadNode
    @ref Json::PrintNode
    @ref Json::PrintValue
*/


/**
 @brief Пространство имен парсера JSON
*/
namespace Json {
/**
 @brief Нода JSON

 Класс предназначен для чтения файла JSON, содержит методы для определения типа ноды, а также ее чтения.
 Класс унаследован от стандартного std::variant, типизированного необходимыми для чтения типами,
 при необходимости можно добавить дополнительные типы
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
         @brief Текущая нода

         Возвращает текущую ноду без преобразований
         @return Ссылка на текущую ноду
        */
        const variant &GetBase() const { return *this; }
        /**
         @brief Текущая нода (Массив)

         Возвращает текущую ноду преобразуя ее в тип std::vector
         @return Ссылка на текущую ноду
        */
        const auto &AsArray() const { return std::get<std::vector<Node>>(*this); }
        /**
         @brief Текущая нода (Карта)

         Возвращает текущую ноду преобразуя ее в тип std::map
         @return Ссылка на текущую ноду
        */
        const auto &AsMap() const { return std::get<std::map<std::string, Node>>(*this); }
        /**
         @brief Текущая нода (Строка)

         Возвращает текущую ноду преобразуя ее в std::string
         @return Ссылка на текущую ноду
        */
        const auto &AsString() const { return std::get<std::string>(*this); }
        /**
         @brief Текущая нода (Число с плавающей запятой)

         Возвращает текущую ноду преобразуя ее в double
         @return Ссылка на текущую ноду
        */
        double AsDouble() const {
            if(std::holds_alternative<double>(*this)){
                return std::get<double>(*this);
            } else return std::get<int>(*this);
        }
        /**
         @brief Текущая нода (Целое число)

         Возвращает текущую ноду преобразуя ее в int
         @return Ссылка на текущую ноду
        */
        int AsInt() const { return std::get<int>(*this); }
        /**
         @brief Текущая нода (Булева)

         Возвращает текущую ноду преобразуя ее в bool
         @return Ссылка на текущую ноду
        */
        bool AsBool() const { return std::get<bool>(*this); }
    };


    /**
     @brief Документ

     Владеет корневой нодой
    */
    class Document {
    public:
        /**
         @brief Конструктор
         @param root Корневая Нода
        */
        explicit Document(Node root) : root(move(root)) {}
        /**
         @brief Getter ноды
         @return Корневая нода
        */
        const Node &GetRoot() const { return root; }

    private:
        Node root; ///< Коневая нода
    };
    /**
     @brief Загрузить документ

     Получает документ, и создает объект класса Документ
     @param input Входной поток
     @return Созданный документ
    */
    Document Load(std::istream &input);
    /**
     @brief Загрузить ноду

     Получает документ, и создает объект класса Node
     @param input Входной поток
     @return Созданная нода
    */
    Node LoadNode(std::istream &input);
    /**
     @brief Вывести ноду

     Печатает полученную ноду в выходной поток
     @param node Нода
     @param output Выходной поток
    */
    void PrintNode(const Node &node, std::ostream &output);

    /**
     @brief Шаблон печати типа

     Получает значение типа T и выводит его в выходной поток
     @param value Значение
     @param os Выходной поток
    */
    template<typename T>
    void PrintValue(const T &value, std::ostream &os) {
        os << value;
    }

    /**
     @brief Параметризованный шаблон печати типа (std::string)
     @param string Строка
     @param os Выходной поток
    */
    template<>
    void PrintValue<std::string>(const std::string &string, std::ostream &os);
    /**
     @brief Параметризованный шаблон печати типа (std::vector)
     @param nodes Массив
     @param os Выходной поток
    */
    template<>
    void PrintValue<std::vector<Node>>(const std::vector<Node> &nodes, std::ostream &os);
    /**
     @brief Параметризованный шаблон печати типа (std::map)
     @param nodes Карта
     @param os Выходной поток
    */
    template<>
    void PrintValue<std::map<std::string, Node>>(const std::map<std::string, Node> &nodes, std::ostream &os);
    /**
     @brief Параметризованный шаблон печати типа (bool)
     @param nodes Булева
     @param os Выходной поток
    */
    template <>
    void PrintValue<bool>(const bool& value, std::ostream& output);

}
#endif //PARTD_JSON_H