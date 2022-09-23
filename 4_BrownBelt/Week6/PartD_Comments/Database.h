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
 @brief ������������ ���� ��� ������� ����������� ��� ������ � ����� ������

 �������� ��� ��������� �������������� ������ ���������� ���: ��������� � �������, ��������� �� �����������, ���������, ��������� � ����������.
 @copyright ��� "���� 2"
 @author �������� �. �.
 @date 12-02-2022
 @version 1.0
 @par �������� ������:
    @ref Stop
    @ref Route
    @ref CircleRoute
    @ref LinearRoute
    @ref Database
    @ref RouteBuilder
 @par ���������� ������:
    @ref Coordinates
*/

/**
 @brief ����� ��� �������� "���������"

 ������������ ��� �������� ������ �� ���������
*/
class Stop {
public:
    /**
     @brief ����������� ��-���������
     @param name �������� ���������
    */
    explicit Stop(std::string name) : name_(std::move(name)) {}

    /**
     @brief ����������� ����������
     @param name �������� ���������
     @param coord ���������� ���������
     @param stops ������ ��������� ���������
    */

    Stop(std::string name,
                  Coordinates coord,
                  std::unordered_map<std::string, size_t> stops) :
                  name_(std::move(name)),
                  coord_(coord),
                  nearest_stops_(std::move(stops)) {}

    /**
     @brief Getter ��� ���������
     @return ���������� ���������
    */
    Coordinates GetCoordinates() const;
    /**
     @brief Setter ��� ���������
     @param coord ���������� ���������
     @return ��������� �� ������� ���������
    */
    Stop* SetCoordinates(Coordinates coord);

    /**
     @brief Getter ��� ��������
     @return �������� ���������
    */
    const std::string& GetName() const;
    /**
     @brief Setter ��� �������� ����������
     @param coord �������� ���������
     @return ��������� �� ������� ���������
    */
    Stop* SetName(const std::string& name);
    /**
     @brief Setter ��� �������� ������������
     @param coord �������� ���������
     @return ��������� �� ������� ���������
    */
    Stop* SetName(std::string&& name);
    /**
     @brief Setter ��� ������ ��������� ��������� ������������
     @param stops ������ ���������
     @return ��������� �� ������� ���������
    */
    Stop* SetNearestStops(std::unordered_map<std::string, size_t> stops);

    /**
     @brief ������� ��� ���������� ��������

     ��������� � ������ ���������, � ������� ���������� ���������, ����� �������
     @param route �������� ��������
    */
    void AddRoute(const std::string& route);
    /**
     @brief ������� ��� ��������� ������ ���������

     ���������� ������ ���������, � ������� ���������� ���������
     @return ��������������� ������ ���������
    */
    const std::set<std::string>& GetRoutes() const;

    /**
     @brief ������� ��� ���������� ���������� ����� �����������

     �������� �� ���� �������� ������ ���������, �� �������� �������� ����������,
     � ��������� ���������� �� ������� ���������
     @return ���������� � ������
    */
    size_t GetDistanceTo(const std::string& name);

private:
    std::string name_; ///< �������� ���������
    Coordinates coord_; ///< ���������� ���������
    std::unordered_map<std::string, size_t> nearest_stops_; ///< ������ ��������� ���������
    std::set<std::string> routes_; ///< ������ ���������
};

/**
 @brief ������� ����������� ����� ��������

 ����������� ����� ������������ ��� ���������� ������������: �������� ���� �������� ����� ���������: ��������� � ������� �� ��������� �� ������� �����
*/
class Route {
public:
    /**
     @brief ��� ��������
    */
    enum class RouteType {
        LINEAR, ///< ������
        CIRCLE ///< ��������
    };
    /**
     @brief �����������
     @param type ��� ��������
     @param name �������� ��������
     @param unique_stops ������ ���������� ��������� �� ��������
    */
    explicit Route(RouteType type, std::string name,
                   std::unordered_set<std::string> unique_stops) : type_(type),
                   name_(std::move(name)),
                   unique_stops_(std::move(unique_stops)) {}
    /**
     @brief ����� ��������

     ����� ��� ������� ����� ��������, ���������� ��� ������� ���������� ���������
     @return ����� �������� ��������
    */
    virtual double GetLength() const = 0;
    /**
     @brief �������� ����� ��������

     ����� ��� ������� ����� ��������, ���������� ��� ������� ���������� ����� �����������
     @return ����� �������� ��������
    */
    virtual size_t GetRealLength() const = 0;

    /**
     @brief ���������� ���������

     ����� ��� ��������� ���������� ��������� �� ������� ��������
     @return ���������� ���������
    */
    virtual size_t GetStopsCount() const = 0;
    /**
     @brief ���������� ���������� ���������

     ����� ��� ��������� ���������� ���������� ��������� �� ������� ��������
     @return ���������� ���������� ���������
    */
    size_t GetUniqueStopsCount() const;

/**
 @brief ����������

 ����������� ����������
*/
    virtual ~Route() = default;

private:
    RouteType type_; ///< ��� ��������
    std::string name_; ///< �������� ��������
    std::unordered_set<std::string> unique_stops_; ///< ������ ���������� ���������
};

/**
 @brief �������� �������

 � ������ �������������� ������ GetLength(), GetRealLength(), GetStopsCount()
 ��������� ���� stops_
*/
class CircleRoute : public Route {
private:
    std::vector<std::shared_ptr<Stop>> stops_; ///< ��� ��������� ��������

public:
    /**
     @brief �����������
     @param stops ��� ��������� ��������
     @param name �������� ��������
     @param unique_stops ������ ���������� ��������� �� ��������
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
 @brief ������ �������

 � ������ �������������� ������ GetLength(), GetRealLength(), GetStopsCount()
 ��������� ���� stops_
*/
class LinearRoute : public Route {
private:
    std::vector<std::shared_ptr<Stop>> stops_; ///< ��� ��������� ��������

public:
    /**
     @brief �����������
     @param stops ��� ��������� ��������
     @param name �������� ��������
     @param unique_stops ������ ���������� ��������� �� ��������
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
 @brief ���� ������

 ���� ������ ������������� ��� ���������� ���������� � �����������: �� ����������� � ����������
*/
class Database {
public:
    /**
     @brief ���������� ���������
     @param name �������� ���������
     @param coord ���������� ���������
     @param distance_to_stops ���������� �� ��������� ���������
    */
    void AddStop(std::string name, Coordinates coord, std::unordered_map<std::string, size_t> distance_to_stops);
    /**
     @brief ���������� ��������
     @param number ����� ��������
     @param route �������
    */

    void AddRoute(std::string number, std::shared_ptr<Route> route);
    /**
     @brief ��������� ���������
     @param name �������� ���������
     @return ��������� �� ���������
    */
    std::shared_ptr<Stop> GetStop(const std::string& name) const;
    /**
     @brief ��������� ��������
     @param number ����� ��������
     @return ��������� �� �������
    */
    std::shared_ptr<Route> GetRoute(const std::string &number) const;

    /**
     @brief ������� ��������� ���������

     ���� ��������� � ����� ��������� ���, ������� ������� � ������ ��������� ��-���������
     @param name �������� ���������
     @return ��������� �� ���������
    */
    std::shared_ptr<Stop> TakeOrAddEmptyStop(const std::string &name);

private:
    std::unordered_map<std::string, std::shared_ptr<Route>> routes; ///< ������ ���������
    std::unordered_map<std::string, std::shared_ptr<Stop>> stops; ///< ������ ���������
};


/**
 @brief ��������� ��������

 ����� ������ ���� ������ � �� ������� ���������� ����������� �������, �� �������� ������
*/
class RouteBuilder {
public:
    /**
     @brief �����������
     @param database ���� ������
    */
    explicit RouteBuilder(Database &database) : db(database) {}

    /**
     @brief ���������� ������� ��������
     @param name �������� ��������
     @param stops ������ ���������
     @return ��������� �� �������
    */
    std::shared_ptr<Route> MakeLinearRoute(std::string name, std::vector<std::string> &stops);
    /**
     @brief ���������� ��������� ��������
     @param name �������� ��������
     @param stops ������ ���������
     @return ��������� �� �������
    */
    std::shared_ptr<Route> MakeCircleRoute(std::string name, std::vector<std::string> &stops);

private:
    /**
     @brief ���������� ���������

     ������� �������� �� ���� ������ ��������� � ���������� ��� � ������ ���������� ���������
     @param stops ������ ���������
     @return ������ ���������� ���������
    */
    static std::unordered_set<std::string> MakeUniqueStops(std::vector<std::string> &stops);
    Database &db; ///< ������ �� ���� ������
};

#endif //PARTA_DATABASE_H
