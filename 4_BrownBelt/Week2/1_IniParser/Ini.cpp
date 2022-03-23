#include "ini.h"
using namespace std;

namespace Ini {

    Section& Document::AddSection(string name){
        return sections[std::move(name)];
    }

    const Section& Document::GetSection(const string& name) const {
        return sections.at(name);
    }

    size_t Document::SectionCount() const {
        return sections.size();
    }

    Document Load(istream& input){
        Document doc;
        Section* curr = nullptr;

        for(string line; std::getline(input, line);){

            if(line.empty()) {
                continue;
            }

            if(line[0] == '[') {
                curr = &doc.AddSection(line.substr(1, line.size() - 2));
            } else {
                auto pos = line.find('=');
                auto key = line.substr(0, pos);
                auto value = line.substr(pos + 1, line.size() - 1);
                curr->emplace(std::move(key), std::move(value));
            }
        }
        return doc;
    }

}