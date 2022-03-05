//
// Created by cobak on 11.01.2022.
//

#ifndef TASK_5_EDITOR_H
#define TASK_5_EDITOR_H


class Editor {
public:
    // Реализуйте конструктор по умолчанию и объявленные методы
    Editor() : editor(""), buffer(""), cursor(0) {}

    void Left(){ if(cursor > 0) --cursor; }

    void Right() { if (cursor < editor.size()) ++cursor; }

    void Insert(char token) {
        editor.insert(cursor, 1, token);
        ++cursor;
    }

    void Cut(size_t tokens = 1) {
        buffer = editor.substr(cursor, tokens);
        editor.erase(cursor, tokens);
    }

    void Copy(size_t tokens = 1) { buffer = editor.substr(cursor, tokens); }

    void Paste() {
        editor.insert(cursor, buffer);
        cursor += buffer.size();
    }

    string GetText() const { return editor; }

private:

    std::string editor;
    std::string buffer;

    size_t cursor;
};

#endif //TASK_5_EDITOR_H
