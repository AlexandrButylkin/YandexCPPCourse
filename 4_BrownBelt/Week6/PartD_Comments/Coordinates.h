#ifndef PARTA_COORDINATES_H
#define PARTA_COORDINATES_H

/**
 @file Coordinates.h
 @brief ������������ ���� ������ Coordinates

 ����� ������������ ��� ���������� ������������ �� �������������� ����� ����. �������� ����������� ������ ��� �������� ��������� ������ ����������� � �������� ���������� ����� �������
 @copyright ��� "���� 2"
 @author �������� �. �.
 @date 12-02-2022
 @version 1.0
*/

/**
 @brief ����� ���������

 ������������ ��� ������ � ������������, ������� ���������� ����� ����� �������
*/

class Coordinates {
private:
    constexpr static double PI = 3.1415926535; ///< ��������� ��
    constexpr static double RADIUS = 6371.0; ///< ��������� ������

    double latitude_; ///< ������
    double longitude_; ///< �������
public:
    /**
     @brief �����������
     @param latitude ������, �������� ��-��������� 0.0f
     @param longitude �������, �������� ��-��������� 0.0f
    */
    Coordinates(double latitude = 0.0, double longitude = 0.0) : latitude_(latitude), longitude_(longitude) {}

    /**
     @brief Getter ��� ������
     @return �������� ������
    */
    double GetLatitude();
    /**
     @brief Getter ��� �������
     @return �������� �������
    */
    double GetLongitude();

    /**
     @brief Getter ��� ������ �����������
     @return �������� ������
    */
    double GetLatitude() const;
    /**
     @brief Getter ��� ������� �����������
     @return �������� �������
    */
    double GetLongitude() const;


    /**
     @brief ������ ����������

     ���������� ���������� ����� ����� ����������� �������
     @param from ������ ����������
     @param to ������ ����������
     @return �������� ����������
    */
    static double Distance(const Coordinates& from, const Coordinates& to);
};


#endif //PARTA_COORDINATES_H
