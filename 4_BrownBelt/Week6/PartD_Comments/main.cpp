#include <iostream>
#include <fstream>


#include "Parser.h"

/**
  @mainpage Проект BasesStops предназначен для выполнения лабораторной работы 2 по курсу "Технология разработки программного обеспечения"
  @copyright OAO "Лаба 2"
  @author Бутылкин А. И.
  @date 12-02-2022
  @par Содержит файлы:
    @ref Coordinates.h
    @ref Database.h
    @ref json.h
    @ref Parser.h
    @ref Requests.h
  @par Основные классы:
    @ref Manager
    @ref Database
    @ref Stop
    @ref Route
    @ref Json::Node
    @ref Request
    @ref Coordinates
*/

template <typename T>
void PrintVector(const std::vector<T>& vec){
    for(const auto& item : vec){
        std::cout << item << "\n";
    }
    std::cout << std::endl;
}

void TestSplit(){
    std::cout << "....................... Test Split ......................." << std::endl;
    const std::string str = "word1 word2 word3 word4 word5";
    std::string_view word1(str);
    std::cout << ReadWord(word1) << std::endl;
    std::string_view word2(word1);
    std::cout << ReadWord(word2) << std::endl;
    std::string_view word3(word2);
    std::cout << ReadWord(word3) << std::endl;
    std::string_view word4(word3);
    std::cout << ReadWord(word4) << std::endl;
    std::string_view word5(word4);
    std::cout << ReadWord(word5) << std::endl;
}

void TestDoubleFromString() {
    std::cout << "................. Test DoubleFrom String ................." << std::endl;
    const std::string str = "1.1, 1.222, 3.44444, 5.12312";
    std::string_view num1(str);
    std::cout << DoubleFromString(ReadWord(num1, ", ")) << std::endl;
    std::string_view num2(num1);
    std::cout << DoubleFromString(ReadWord(num2, ", ")) << std::endl;
    std::string_view num3(num2);
    std::cout << DoubleFromString(ReadWord(num3, ", ")) << std::endl;
    std::string_view num4(num3);
    std::cout << DoubleFromString(ReadWord(num4, ", ")) << std::endl;
}


void TestStopsFromString() {
    std::cout << "................. Test Stops From String ................." << std::endl;
    const std::string str1 = "Biryulyovo Zapadnoye > Biryusinka > Universam > Biryulyovo Tovarnaya > Biryulyovo Passazhirskaya > Biryulyovo Zapadnoye";
    const std::string str2 = "stop11 - stop12 - stop13 - stop14 - stop15";

    std::string_view stops1(str1);
    std::string_view stops2(str2);

    auto [delimiter1, stops_circle] = StopsFromString(stops1);
    auto [delimiter2, stops_linear] = StopsFromString(stops2);

    PrintVector(stops_circle);
    PrintVector(stops_linear);
}

void TestParse(){
    std::cout << "................. Test Parse Input Stop .................." << std::endl;
    std::string str = "Biryulyovo Zapadnoye: 55.574371, 37.6517, 7500m to Rossoshanskaya ulitsa, 1800m to Biryusinka, 2400m to Universam";
    std::string_view stringView(str);
    //const auto type_request = RequestFromString(ReadWord(stringView));
    auto request = Request::Create(type_request.value(), true);
    if(request){
        request->Parse(stringView);
    }
}

void TestAll(){
    Manager manager;
    manager.ParseAllRequestJSON();
    manager.ProcessAllInputRequest();
    manager.ProcessAllOutputRequestJSON();
}

int main() {
    TestAll();
    return 0;
}
