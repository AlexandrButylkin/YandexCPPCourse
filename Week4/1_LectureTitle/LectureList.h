#ifndef LECTURELIST_H_
#define LECTURELIST_H_

#include <iostream>

struct Specialization{
    std::string val;
    explicit Specialization(const std::string& val_) : val(val_){}
};

struct Course{
    std::string val;
    explicit Course(const std::string& val_) : val(val_){}
};

struct Week{
    std::string val;
    explicit Week(const std::string& val_) : val(val_){}
};

class LectureTitle{
public:
    std::string specialization;
    std::string course;
    std::string week;
    LectureTitle() : 
    specialization(""),
    course(""),
    week("") {}
    LectureTitle(const Specialization& specialization_, const Course& course_, const Week& week_) : 
    specialization(specialization_.val),
    course(course_.val),
    week(week_.val) {}


};

#endif