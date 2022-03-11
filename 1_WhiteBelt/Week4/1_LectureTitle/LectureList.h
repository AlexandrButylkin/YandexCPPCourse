#ifndef LECTURELIST_H_
#define LECTURELIST_H_

struct Specialization{
    std::string val;
    explicit Specialization(std::string  val_) : val(std::move(val_)){}
};

struct Course{
    std::string val;
    explicit Course(std::string  val_) : val(std::move(val_)){}
};

struct Week{
    std::string val;
    explicit Week(std::string  val_) : val(std::move(val_)){}
};

class LectureTitle{
public:
    LectureTitle() :
            specialization(),
            course(),
            week() {}
    LectureTitle(const Specialization& specialization_, const Course& course_, const Week& week_) :
            specialization(specialization_.val),
            course(course_.val),
            week(week_.val) {}

private:
    std::string specialization;
    std::string course;
    std::string week;


#endif