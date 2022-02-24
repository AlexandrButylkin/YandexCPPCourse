//
// Created by cobak on 19.01.2022.
//

#ifndef TASK_1_INI__INI_H
#define TASK_1_INI__INI_H

#include <string>
#include <unordered_map>
#include <sstream>
#include <exception>

using std::string;
using std::string_view;
using std::unordered_map;
using std::istream;
using std::istringstream;

namespace Ini {

    using Section = unordered_map<string, string>;

    class Document {
    public:
        Section& AddSection(string name);
        const Section& GetSection(const string& name) const;
        size_t SectionCount() const;

    private:
        unordered_map<string, Section> sections;
    };

    Document Load(istream& input);

}


#endif //TASK_1_INI__INI_H
