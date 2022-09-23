#ifndef PARTA_DATABASE_H
#define PARTA_DATABASE_H

#include <string>
#include <utility>
#include <vector>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <memory>

#include "Coordinates.h"

/**
 @file DataBase.h
 @brief Заголовочный файл для классов необходимых для работы с базой данных

 Исходный код позволяет манипулировать такими сущностями как: остановка и маршрут, управлять их добавлением, созданием, хранением и получением.
 @copyright ОАО "Лаба 2"
 @author Бутылкин А. И.
 @date 12-02-2022
 @version 1.0
 @par Содержит классы:
    @ref Stop
    @ref Route
    @ref CircleRoute
    @ref LinearRoute
    @ref Database
    @ref RouteBuilder
 @par Использует классы:
    @ref Coordinates
*/

/**
 @brief Класс для сущности "Остановка"

 Предназначен для хранения данных об остановке
*/
class Stop {
public:
    /**
     @brief Конструктор по-умолчанию
     @param name Название остановки
    */
    explicit Stop(std::string name) : name_(std::move(name)) {}

    /**
     @brief Конструктор параметров
     @param name Название остановки
     @param coord Координаты остановки
     @param stops Список ближайших остановок
    */

    Stop(std::string name,
                  Coordinates coord,
                  std::unordered_map<std::string, size_t> stops) :
                  name_(std::move(name)),
                  coord_(coord),
                  nearest_stops_(std::move(stops)) {}

    /**
     @brief Getter для координат
     @return Координаты остановки
    */
    Coordinates GetCoordinates() const;
    /**
     @brief Setter для координат
     @param coord Координаты остановки
     @return Указатель на текущую остановку
    */
    Stop* SetCoordinates(Coordinates coord);

    /**
     @brief Getter для названия
     @return Название остановки
    */
    const std::string& GetName() const;
    /**
     @brief Setter для названия копирующий
     @param coord Название остановки
     @return Указатель на текущую остановку
    */
    Stop* SetName(const std::string& name);
    /**
     @brief Setter для названия перемещающий
     @param coord Название остановки
     @return Указатель на текущую остановку
    */
    Stop* SetName(std::string&& name);
    /**
     @brief Setter для списка ближайших остановок перемещающий
     @param stops Список остановок
     @return Указатель на текущую остановку
    */
    Stop* SetNearestStops(std::unordered_map<std::string, size_t> stops);

    /**
     @brief Функция для добавления маршрута

     Добавляет в список маршрутов, в которых содержится остановка, новый маршрут
     @param route Название маршрута
    */
    void AddRoute(const std::string& route);
    /**
     @brief Функция для получения списка маршрутов

     Возвращает список маршрутов, в которых содержится остановка
     @return Отсортированный список маршрутов
    */
    const std::set<std::string>& GetRoutes() const;

    /**
     @brief Функция для вычисления расстояния между остановками

     Получает на вход название другой остановки, по которому получает координаты,
     и вычисляет расстояние от текущей остановки
     @return Расстояние в метрах
    */
    size_t GetDistanceTo(const std::string& name);

private:
    std::string name_; ///< Название остановки
    Coordinates coord_; ///< Координаты остановки
    std::unordered_map<std::string, size_t> nearest_stops_; ///< Список ближайших остановок
    std::set<std::string> routes_; ///< Список маршрутов
};

/**
 @brief Базовый абстрактный класс маршрута

 Абстрактный класс предназначен для реализации полиморфизма: хранения двух основных типов маршрутов: кругового и прямого по указателю на базовый класс
*/
class Route {
public:
    /**
     @brief Тип маршрута
    */
    enum class RouteType {
        LINEAR, ///< Прямой
        CIRCLE ///< Круговой
    };
    /**
     @brief Конструктор
     @param type Тип маршрута
     @param name Название маршрута
     @param unique_stops Список уникальных остановок на маршруте
    */
    explicit Route(RouteType type, std::string name,
                   std::unordered_set<std::string> unique_stops) : type_(type),
                   name_(std::move(name)),
                   unique_stops_(std::move(unique_stops)) {}
    /**
     @brief Длина маршрута

     Метод для расчета длины маршрута, использует для расчета координаты остановок
     @return Длина текущего маршрута
    */
    virtual double GetLength() const = 0;
    /**
     @brief Реальная длина маршрута

     Метод для расчета длины маршрута, использует для расчета расстояния между остановками
     @return Длина текущего маршрута
    */
    virtual size_t GetRealLength() const = 0;

    /**
     @brief Количество остановок

     Метод для получения количества остановок на текущем маршруте
     @return Количество остановок
    */
    virtual size_t GetStopsCount() const = 0;
    /**
     @brief Количество уникальных остановок

     Метод для получения количества уникальных остановок на текущем маршруте
     @return Количество уникальных остановок
    */
    size_t GetUniqueStopsCount() const;

/**
 @brief Деструктор

 Виртуальный деструктор
*/
    virtual ~Route() = default;

private:
    RouteType type_; ///< Тип маршрута
    std::string name_; ///< Название маршрута
    std::unordered_set<std::string> unique_stops_; ///< Список уникальных остановок
};

/**
 @brief Круговой маршрут

 В классе переопределены методы GetLength(), GetRealLength(), GetStopsCount()
 Добавлено поле stops_
*/
class CircleRoute : public Route {
private:
    std::vector<std::shared_ptr<Stop>> stops_; ///< Все остановки маршрута

public:
    /**
     @brief Конструктор
     @param stops Все остановки маршрута
     @param name Название маршрута
     @param unique_stops Список уникальных остановок на маршруте
    */
    explicit CircleRoute(std::vector<std::shared_ptr<Stop>> stops, std::string name,
                         std::unordered_set<std::string> unique_stops) :
                         Route(RouteType::CIRCLE, std::move(name),
                               std::move(unique_stops)),
                               stops_(std::move(stops)) {}

    double GetLength() const override;
    size_t GetRealLength() const override;

    size_t GetStopsCount() const override;
};

/**
 @brief Прямой маршрут

 В классе переопределены методы GetLength(), GetRealLength(), GetStopsCount()
 Добавлено поле stops_
*/
class LinearRoute : public Route {
private:
    std::vector<std::shared_ptr<Stop>> stops_; ///< Все остановки маршрута

public:
    /**
     @brief Конструктор
     @param stops Все остановки маршрута
     @param name Название маршрута
     @param unique_stops Список уникальных остановок на маршруте
    */
    explicit LinearRoute(std::vector<std::shared_ptr<Stop>> stops, std::string name,
                         std::unordered_set<std::string> unique_stops) :
                         Route(RouteType::LINEAR, std::move(name),
                               std::move(unique_stops)),
                               stops_(std::move(stops)) {}
    double GetLength() const override;
    size_t GetRealLength() const override;

    size_t GetStopsCount() const override;
};

/**
 @brief База данных

 База данных предназначена для управления маршрутами и остановками: их добавлением и получением
*/
class Database {
public:
    /**
     @brief Добавление остановки
     @param name Название остановки
     @param coord Координаты остановки
     @param distance_to_stops Расстояния до ближайших остановок
    */
    void AddStop(std::string name, Coordinates coord, std::unordered_map<std::string, size_t> distance_to_stops);
    /**
     @brief Добавление маршрута
     @param number Номер маршрута
     @param route Маршрут
    */

    void AddRoute(std::string number, std::shared_ptr<Route> route);
    /**
     @brief Получение остановки
     @param name Название остановки
     @return Указатель на остановку
    */
    std::shared_ptr<Stop> GetStop(const std::string& name) const;
    /**
     @brief Получение маршрута
     @param number Номер маршрута
     @return Указатель на маршрут
    */
    std::shared_ptr<Route> GetRoute(const std::string &number) const;

    /**
     @brief Попытка получения остановки

     Если остановки с таким названием нет, функция создаст и вернет остановку по-умолчанию
     @param name Название остановки
     @return Указатель на остановку
    */
    std::shared_ptr<Stop> TakeOrAddEmptyStop(const std::string &name);

private:
    std::unordered_map<std::string, std::shared_ptr<Route>> routes; ///< Список маршрутов
    std::unordered_map<std::string, std::shared_ptr<Stop>> stops; ///< Список остановок
};


/**
 @brief Строитель маршрута

 Класс хранит базу данных и по запросу возвращает построенный маршрут, из исходных данных
*/
class RouteBuilder {
public:
    /**
     @brief Конструктор
     @param database База данных
    */
    explicit RouteBuilder(Database &database) : db(database) {}

    /**
     @brief Построение прямого маршрута
     @param name Название маршрута
     @param stops Список остановок
     @return Указатель на маршрут
    */
    std::shared_ptr<Route> MakeLinearRoute(std::string name, std::vector<std::string> &stops);
    /**
     @brief Построение кругового маршрута
     @param name Название маршрута
     @param stops Список остановок
     @return Указатель на маршрут
    */
    std::shared_ptr<Route> MakeCircleRoute(std::string name, std::vector<std::string> &stops);

private:
    /**
     @brief Уникальные остановки

     Функция получает на вход список остановок и превращает его в список уникальных остановок
     @param stops Список остановок
     @return Список уникальных остановок
    */
    static std::unordered_set<std::string> MakeUniqueStops(std::vector<std::string> &stops);
    Database &db; ///< Ссылка на базу данных
};

#endif //PARTA_DATABASE_H
