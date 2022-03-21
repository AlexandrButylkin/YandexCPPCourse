#ifndef TASK_5_EDITOR_H
#define TASK_5_EDITOR_H

#include <string>
#include <list>

class Editor {
public:
    Editor() : cursor(editor.end()) {}

    void Left();
    void Right();
    void Insert(char token);
    void Cut(size_t tokens = 1);
    void Copy(size_t tokens = 1);
    void Paste();
    std::string GetText() const;

private:
    using Iterator = std::list<char>::iterator;
    std::list<char> editor;
    std::list<char> buffer;
    Iterator cursor;

    Iterator AdvanceCopy(size_t tokens);
    Iterator AdvanceLeft(Iterator it, size_t n);
    Iterator AdvanceRight(Iterator it, size_t n);

};

#endif //TASK_5_EDITOR_H
