//
// Created by cobak on 19.01.2022.
//

#include "ini.h"

namespace Ini {

    Section& Document::AddSection(string name){
        return sections.emplace(std::move(name), Section()).first->second;
    }

    const Section& Document::GetSection(const string& name) const {

        if(sections.find(name) == sections.end()) throw std::out_of_range("out of range");
        else return sections.find(name)->second;
    }

    size_t Document::SectionCount() const {
        return sections.size();
    }

    bool IsSection(const string& str){
        if(str[0] == '[' && str[str.size() - 1] == ']'){
            return true;
        } else return false;
    }

    void ParseField(Section* section, istream& is){
        string category;
        string amount;
        std::string str;
        std::getline(is, category, '=');
        std::getline(is, amount);
        section->emplace(category, amount);
    }

    string GetStringSection(const string& section){
        std::string_view str(section);
        str.remove_prefix(1);
        str.remove_suffix(1);
        return string(str);
    }

    Document Load(istream& input){
        Document doc;
        Section* curr;

        for(string line; std::getline(input, line);){
            if(line.empty()) continue;
            if(IsSection(line)) {
                curr = &doc.AddSection(GetStringSection(line));
            } else {
                istringstream is(std::move(line));
                ParseField(curr, is);
            }
        }
        return doc;

        /*string name;
        string field;
        std::getline(input, field);

        while(!input.eof()){
            curr = &doc.AddSection(GetStringSection(field));
            std::getline(input, field);
            while (!IsSection(field) && !input.eof()){
                istringstream is(std::move(field));
                ParseField(curr, is);
                std::getline(input, field);
                if(field.empty()) std::getline(input, field);
            }
            if(field.empty()) break;
        }
        return doc;*/
    }

}