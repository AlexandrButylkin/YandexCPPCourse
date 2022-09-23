#ifndef PARTA_PARSER_H
#define PARTA_PARSER_H

#include <vector>
#include <memory>
#include <optional>

#include "Requests.h"
#include "Database.h"

static const std::string BASE_REQUESTS = "base_requests";
static const std::string STAT_REQUESTS = "stat_requests";

/**
 @page Какая-то_страница
 @brief Тут можно что то написать, но я не знаю что.

 Напишу что есть класс Manager, и что можно его посмотреть)))
 @par Вот этот класс:
    @ref Manager
*/

double DoubleFromString(std::string_view str);

size_t IntFromString(std::string_view str);

size_t ReadCountRequests(std::istream &is);

std::pair<std::string_view, std::optional<std::string_view>>
SplitTwo(std::string_view str, std::string_view delimiter = " ");

std::string_view ReadWord(std::string_view &str, std::string_view delimiter = " ");

std::string_view InitDelimit(std::string_view &str);

std::pair<Route::RouteType, std::vector<std::string>> StopsFromString(std::string_view &str);

std::optional<Request::RequestType> GetTypeRequest(std::string_view str);

/**
 @file Parser.h
 @brief Заголовочный файл класса Manager

 Cодержит методы, необходимые пользователю для работы с базой данных. Менеджер способен выполнять запросы как на добавление, так и на получение, а также использовать два вида запросов: строковые запросы и Json запросы
 @copyright ОАО "Лаба 2"
 @author Бутылкин А. И.
 @date 12-02-2022
 @version 1.0
 @par Содержит классы:
    @ref Manager
 @par Использует классы и методы из документов:
    @ref Requests.h
    @ref Database.h
*/

/**
 @brief Менеджер

 Класс, с которым взаимодействует пользователь, добавляет запросы и выполняет их.
 Также менеджер владеет базой данных
*/
class Manager {
public:
    /**
     @brief Менеджер

     Менеджер сам создает пустую базу данных, а также записывает ссылки на входной и выходной потоки
     @param is Ссылка на входной поток
     @param os Ссылка на выходной поток
    */
    explicit Manager(std::istream &is = std::cin, std::ostream& os = std::cout) : is_(is), os_(os), database(Database()) {}

    /**
     @brief Анализ запросов (строка)

     Чтение запросов и изъятие необходимой информации
    */
    void ParseAllRequestString();
    /**
     @brief Выполнение запросов на получение (строка)

     Выполнение всех полученных запросов на получение
    */
    void ProcessAllOutputRequestString();
    /**
     @brief Анализ запросов (JSON)

     Чтение запросов и изъятие необходимой информации
    */
    void ParseAllRequestJSON();
    /**
     @brief Выполнение запросов на получение (JSON)

     Выполнение всех полученных запросов на получение
    */
    void ProcessAllOutputRequestJSON();
    /**
     @brief Выполнение всех запросов
    */
    void ProcessAllInputRequest();

private:
    /**
     @brief Добавление текущего запроса (строка)
     @param request_str Строка с запросом
     @param io_type Тип запроса (добавление / получение)
     @return Указатель на объект запроса
    */
    static std::unique_ptr<Request> AddCurrentStringRequest(std::string_view request_str, Request::IOType io_type = Request::IOType::INPUT);
    /**
     @brief Добавление текущего запроса (JSON)
     @param node Нода с запросом
     @param io_type Тип запроса (добавление / получение)
     @return Указатель на объект запроса
    */
    static std::unique_ptr<Request> AddCurrentJSONRequest(const Json::Node & node, Request::IOType io_type = Request::IOType::INPUT);

private:

    std::istream &is_; ///< Входной поток
    std::ostream &os_; ///< Выходной поток

private:

    Database database; ///< База данных
    std::vector<std::unique_ptr<Request>> requests_input_; ///< Список запросов на добавление
    std::vector<std::unique_ptr<Request>> request_output_; ///< Список запросов на получение

};





#endif //PARTA_PARSER_H
