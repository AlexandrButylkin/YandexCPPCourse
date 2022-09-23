#ifndef PARTA_REQUESTS_H
#define PARTA_REQUESTS_H

#include <string>
#include <memory>
#include <vector>
#include <sstream>
#include <iostream>

#include "Database.h"
#include "json.h"


/**
 @file Requests.h
 @brief Заголовочный файл описывающий запросы

 Содержит несколько видов запросов, а также методы для их формирования и выполнения
 @copyright ОАО "Лаба 2"
 @author Бутылкин А. И.
 @date 12-02-2022
 @version 1.0
 @par Содержит классы:
    @ref Request
    @ref InputRequest
    @ref StopInputRequest
    @ref BusInputRequest
    @ref OutputRequest
    @ref StopData
    @ref BusData
    @ref StopOutputRequest
    @ref BusOutputRequest
 @par Использует классы и методы из документов:
    @ref Database.h
    @ref json.h
*/

/**
 @brief Запрос

 Базовый класс представления запросов
*/
class Request {
public:
/**
 @brief InputOutput Тип

 Получение или добавление объекта в базу данных
*/
    enum class IOType{
        INPUT, ///< Добавление
        OUTPUT ///< Получение
    };
/**
 @brief Тип запроса
*/
    enum class RequestType{
        STOP, ///< Остановка
        BUS ///< Маршрут
    };
/**
 @brief Получение типа запроса
 @return Тип запроса
*/
    RequestType GetRequestType() const {
        return request_type_;
    }

public:
/**
 @brief Конструктор
 @param io_type Тип (добавление / получение)
 @param request_type Тип (остановка / маршрут)
*/
    Request(IOType io_type, RequestType request_type) : io_type_(io_type), request_type_(request_type) {}

/**
 @brief Создание запроса

 Опираясь на типы функция возвращает указатель на удовлетворяющий тип запроса
 @param io_type Тип (добавление / получение)
 @param request_type Тип (остановка / маршрут)
 @return Указатель на запрос соответствующего типа
*/
    static std::unique_ptr<Request> Create(IOType io_type, RequestType request_type);

/**
 @brief Получение информации о запросе (строка)

 Функция получает на вход строку, содержащую запрос, и достаёт из нее необходимую информацию
 @param str Строка содержащая запрос
*/
    virtual void ParseFromString(std::string_view str) = 0;
/**
 @brief Получение информации о запросе (JSON-файл)

 Функция получает на вход JSON файл, содержащий запрос, и достаёт из него необходимую информацию
 @param node Ссылка на основную ноду JSON файла
*/
    virtual void ParseFromJSON(const Json::Node& node) = 0;

/**
 @brief Деструктор

 Виртуальный деструктор
*/
    virtual ~Request() = default;



private:

    const IOType io_type_;  ///< Тип (добавление / получение)
    const RequestType request_type_; ///< Тип (остановка / маршрут)

};

/**
 @brief Входной запрос

 Абстрактный класс для представления входного запроса
*/
class InputRequest : public Request {
public:
/**
 @brief Конструктор
 @param type Тип (остановка / маршрут)
*/
    InputRequest(RequestType type) : Request(IOType::INPUT, type) {}
    void ParseFromString(std::string_view) override = 0;
    void ParseFromJSON(const Json::Node &node) override = 0;
/**
 @brief Выполнение запроса

 Функция по полученным данным выполняет запрос
 @param db База данных
*/
    virtual void Process(Database& db) = 0;

};

/**
 @brief Входной запрос добавления остановки
*/
class StopInputRequest : public InputRequest {
public:
/**
 @brief Конструктор

 Формирует запрос на добавление остановки
*/
    StopInputRequest() : InputRequest(RequestType::STOP) {}
    void ParseFromString(std::string_view) override;
    void ParseFromJSON(const Json::Node& node) override;
    void Process(Database& db) override;

private:
    std::string name_; ///< Название остановки
    double latitude_; ///< Широта
    double longitude_; ///< Долгота
    std::unordered_map<std::string, size_t> distance_to_stops_; ///< Список ближайших остановок и расстояний до них

};

/**
 @brief Входной запрос добавления маршрута
*/
class BusInputRequest : public InputRequest {
public:
/**
 @brief Конструктор

 Формирует запрос на добавление маршрута
*/
    BusInputRequest() : InputRequest(RequestType::BUS) {}
    void ParseFromString(std::string_view) override;
    void ParseFromJSON(const Json::Node& node) override;
    void Process(Database& db) override;

private:
    std::string number_; ///< Номер маршрута
    Route::RouteType route_type_; ///< Тип маршрута
    std::vector<std::string> stops_; ///< Список остановок
};

/**
 @brief Выходной запрос

 Абстрактный шаблонный класс для представления выходного запроса
*/
template<typename T>
class OutputRequest : public Request {
public:
/**
 @brief Конструктор

 Формирует запрос на получение данных о маршруте или остановке
 @param type Тип (остановка / маршрут)
*/
    OutputRequest(RequestType type) : Request(IOType::INPUT, type) {}
    virtual T Process(Database& db) = 0;
    void ParseFromString(std::string_view) override = 0;
    void ParseFromJSON(const Json::Node &node) override = 0;

/*    virtual std::string PrintString(std::ostream& os) = 0;
    virtual Json::Node PrintJSON() = 0;*/

protected:
    int request_id_; ///< ID запроса
};

/**
 @brief Данные об остановке

 Содержит все необходимые данные об остановке, а также методы для представления данных в виде строки, или ноды JSON
*/
struct StopData{
    int request_id = -1; ///< ID запроса
    std::string name; ///< Название остановки
    bool is_error = true; ///< Флаг наличия ошибки
    std::vector<std::string> routes; ///< Список маршрутов, которым принадлежит остановка
/**
 @brief Преобразовать данные в строку
 @return Данные представленные в виде строки
*/
    std::string ToString() const;
/**
 @brief Преобразовать данные в ноду JSON
 @return Данные представленные в виде ноды JSON
*/
    Json::Node ToJSON() const;
};


/**
 @brief Данные о маршруте

 Содержит все необходимые данные о маршруте, а также методы для представления данных в виде строки, или ноды JSON
*/
struct BusData{
    int request_id = -1; ///< ID запроса
    std::string number; ///< Номер маршрута
    bool is_error = true; ///< Флаг наличия ошибки
    double length = 0.0; ///< Длина маршрута
    double real_length = 0.0; ///< Реальная длина маршрута
    size_t stops_count = 0; ///< Количество остановок на маршруте
    size_t unique_stops_count = 0; ///< Количество уникальных остановок на маршруте
/**
 @brief Преобразовать данные в строку
 @return Данные представленные в виде строки
*/
    std::string ToString() const;
/**
 @brief Преобразовать данные в ноду JSON
 @return Данные представленные в виде ноды JSON
*/
    Json::Node ToJSON() const;
};

/**
 @brief Выходной запрос получения остановки
*/
class StopOutputRequest : public OutputRequest<StopData> {
public:
/**
 @brief Конструктор

 Формирует запрос на получение остановки
*/
    StopOutputRequest() : OutputRequest(RequestType::STOP) {}
    void ParseFromString(std::string_view) override;
    void ParseFromJSON(const Json::Node& node) override;
    StopData Process(Database& db) override;

private:
    std::string name_; ///< Название остановки
};

/**
 @brief Выходной запрос получения маршрута
*/
class BusOutputRequest : public OutputRequest<BusData> {
public:
/**
 @brief Конструктор

 Формирует запрос на получение маршрута
*/
    BusOutputRequest() : OutputRequest(RequestType::BUS) {}
    void ParseFromString(std::string_view) override;
    void ParseFromJSON(const Json::Node& node) override;
    BusData Process(Database& db) override;

private:

    std::string number_; ///< Номер маршрута

};


#endif //PARTA_REQUESTS_H
