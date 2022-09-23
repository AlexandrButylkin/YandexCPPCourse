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
 @brief ������������ ���� ����������� �������

 �������� ��������� ����� ��������, � ����� ������ ��� �� ������������ � ����������
 @copyright ��� "���� 2"
 @author �������� �. �.
 @date 12-02-2022
 @version 1.0
 @par �������� ������:
    @ref Request
    @ref InputRequest
    @ref StopInputRequest
    @ref BusInputRequest
    @ref OutputRequest
    @ref StopData
    @ref BusData
    @ref StopOutputRequest
    @ref BusOutputRequest
 @par ���������� ������ � ������ �� ����������:
    @ref Database.h
    @ref json.h
*/

/**
 @brief ������

 ������� ����� ������������� ��������
*/
class Request {
public:
/**
 @brief InputOutput ���

 ��������� ��� ���������� ������� � ���� ������
*/
    enum class IOType{
        INPUT, ///< ����������
        OUTPUT ///< ���������
    };
/**
 @brief ��� �������
*/
    enum class RequestType{
        STOP, ///< ���������
        BUS ///< �������
    };
/**
 @brief ��������� ���� �������
 @return ��� �������
*/
    RequestType GetRequestType() const {
        return request_type_;
    }

public:
/**
 @brief �����������
 @param io_type ��� (���������� / ���������)
 @param request_type ��� (��������� / �������)
*/
    Request(IOType io_type, RequestType request_type) : io_type_(io_type), request_type_(request_type) {}

/**
 @brief �������� �������

 �������� �� ���� ������� ���������� ��������� �� ��������������� ��� �������
 @param io_type ��� (���������� / ���������)
 @param request_type ��� (��������� / �������)
 @return ��������� �� ������ ���������������� ����
*/
    static std::unique_ptr<Request> Create(IOType io_type, RequestType request_type);

/**
 @brief ��������� ���������� � ������� (������)

 ������� �������� �� ���� ������, ���������� ������, � ������ �� ��� ����������� ����������
 @param str ������ ���������� ������
*/
    virtual void ParseFromString(std::string_view str) = 0;
/**
 @brief ��������� ���������� � ������� (JSON-����)

 ������� �������� �� ���� JSON ����, ���������� ������, � ������ �� ���� ����������� ����������
 @param node ������ �� �������� ���� JSON �����
*/
    virtual void ParseFromJSON(const Json::Node& node) = 0;

/**
 @brief ����������

 ����������� ����������
*/
    virtual ~Request() = default;



private:

    const IOType io_type_;  ///< ��� (���������� / ���������)
    const RequestType request_type_; ///< ��� (��������� / �������)

};

/**
 @brief ������� ������

 ����������� ����� ��� ������������� �������� �������
*/
class InputRequest : public Request {
public:
/**
 @brief �����������
 @param type ��� (��������� / �������)
*/
    InputRequest(RequestType type) : Request(IOType::INPUT, type) {}
    void ParseFromString(std::string_view) override = 0;
    void ParseFromJSON(const Json::Node &node) override = 0;
/**
 @brief ���������� �������

 ������� �� ���������� ������ ��������� ������
 @param db ���� ������
*/
    virtual void Process(Database& db) = 0;

};

/**
 @brief ������� ������ ���������� ���������
*/
class StopInputRequest : public InputRequest {
public:
/**
 @brief �����������

 ��������� ������ �� ���������� ���������
*/
    StopInputRequest() : InputRequest(RequestType::STOP) {}
    void ParseFromString(std::string_view) override;
    void ParseFromJSON(const Json::Node& node) override;
    void Process(Database& db) override;

private:
    std::string name_; ///< �������� ���������
    double latitude_; ///< ������
    double longitude_; ///< �������
    std::unordered_map<std::string, size_t> distance_to_stops_; ///< ������ ��������� ��������� � ���������� �� ���

};

/**
 @brief ������� ������ ���������� ��������
*/
class BusInputRequest : public InputRequest {
public:
/**
 @brief �����������

 ��������� ������ �� ���������� ��������
*/
    BusInputRequest() : InputRequest(RequestType::BUS) {}
    void ParseFromString(std::string_view) override;
    void ParseFromJSON(const Json::Node& node) override;
    void Process(Database& db) override;

private:
    std::string number_; ///< ����� ��������
    Route::RouteType route_type_; ///< ��� ��������
    std::vector<std::string> stops_; ///< ������ ���������
};

/**
 @brief �������� ������

 ����������� ��������� ����� ��� ������������� ��������� �������
*/
template<typename T>
class OutputRequest : public Request {
public:
/**
 @brief �����������

 ��������� ������ �� ��������� ������ � �������� ��� ���������
 @param type ��� (��������� / �������)
*/
    OutputRequest(RequestType type) : Request(IOType::INPUT, type) {}
    virtual T Process(Database& db) = 0;
    void ParseFromString(std::string_view) override = 0;
    void ParseFromJSON(const Json::Node &node) override = 0;

/*    virtual std::string PrintString(std::ostream& os) = 0;
    virtual Json::Node PrintJSON() = 0;*/

protected:
    int request_id_; ///< ID �������
};

/**
 @brief ������ �� ���������

 �������� ��� ����������� ������ �� ���������, � ����� ������ ��� ������������� ������ � ���� ������, ��� ���� JSON
*/
struct StopData{
    int request_id = -1; ///< ID �������
    std::string name; ///< �������� ���������
    bool is_error = true; ///< ���� ������� ������
    std::vector<std::string> routes; ///< ������ ���������, ������� ����������� ���������
/**
 @brief ������������� ������ � ������
 @return ������ �������������� � ���� ������
*/
    std::string ToString() const;
/**
 @brief ������������� ������ � ���� JSON
 @return ������ �������������� � ���� ���� JSON
*/
    Json::Node ToJSON() const;
};


/**
 @brief ������ � ��������

 �������� ��� ����������� ������ � ��������, � ����� ������ ��� ������������� ������ � ���� ������, ��� ���� JSON
*/
struct BusData{
    int request_id = -1; ///< ID �������
    std::string number; ///< ����� ��������
    bool is_error = true; ///< ���� ������� ������
    double length = 0.0; ///< ����� ��������
    double real_length = 0.0; ///< �������� ����� ��������
    size_t stops_count = 0; ///< ���������� ��������� �� ��������
    size_t unique_stops_count = 0; ///< ���������� ���������� ��������� �� ��������
/**
 @brief ������������� ������ � ������
 @return ������ �������������� � ���� ������
*/
    std::string ToString() const;
/**
 @brief ������������� ������ � ���� JSON
 @return ������ �������������� � ���� ���� JSON
*/
    Json::Node ToJSON() const;
};

/**
 @brief �������� ������ ��������� ���������
*/
class StopOutputRequest : public OutputRequest<StopData> {
public:
/**
 @brief �����������

 ��������� ������ �� ��������� ���������
*/
    StopOutputRequest() : OutputRequest(RequestType::STOP) {}
    void ParseFromString(std::string_view) override;
    void ParseFromJSON(const Json::Node& node) override;
    StopData Process(Database& db) override;

private:
    std::string name_; ///< �������� ���������
};

/**
 @brief �������� ������ ��������� ��������
*/
class BusOutputRequest : public OutputRequest<BusData> {
public:
/**
 @brief �����������

 ��������� ������ �� ��������� ��������
*/
    BusOutputRequest() : OutputRequest(RequestType::BUS) {}
    void ParseFromString(std::string_view) override;
    void ParseFromJSON(const Json::Node& node) override;
    BusData Process(Database& db) override;

private:

    std::string number_; ///< ����� ��������

};


#endif //PARTA_REQUESTS_H
