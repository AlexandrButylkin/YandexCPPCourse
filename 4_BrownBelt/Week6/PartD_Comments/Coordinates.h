#ifndef PARTA_COORDINATES_H
#define PARTA_COORDINATES_H

/**
 @file Coordinates.h
 @brief Заголовочный файл класса Coordinates

 Класс предназначен для управления координатами на географической карте мира. Содержит необходимые методы для хранения координат Земной поверхности и рассчёта расстояния между точками
 @copyright ОАО "Лаба 2"
 @author Бутылкин А. И.
 @date 12-02-2022
 @version 1.0
*/

/**
 @brief Класс координат

 Предназначен для работы с координатами, расчета расстояния между двумя точками
*/

class Coordinates {
private:
    constexpr static double PI = 3.1415926535; ///< Константа ПИ
    constexpr static double RADIUS = 6371.0; ///< Константа Радиус

    double latitude_; ///< Широта
    double longitude_; ///< Долгота
public:
    /**
     @brief Конструктор
     @param latitude Широта, значение по-умолчанию 0.0f
     @param longitude Долгота, значение по-умолчанию 0.0f
    */
    Coordinates(double latitude = 0.0, double longitude = 0.0) : latitude_(latitude), longitude_(longitude) {}

    /**
     @brief Getter для широты
     @return Значение широты
    */
    double GetLatitude();
    /**
     @brief Getter для долготы
     @return Значение долготы
    */
    double GetLongitude();

    /**
     @brief Getter для широты константный
     @return Значение широты
    */
    double GetLatitude() const;
    /**
     @brief Getter для долготы константный
     @return Значение долготы
    */
    double GetLongitude() const;


    /**
     @brief Расчет расстояния

     Возвращает расстояние между двумя полученными точками
     @param from Первая координата
     @param to Вторая координата
     @return Значение расстояния
    */
    static double Distance(const Coordinates& from, const Coordinates& to);
};


#endif //PARTA_COORDINATES_H
