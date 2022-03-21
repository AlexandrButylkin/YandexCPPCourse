#include "Editor.h"


void Editor::Left(){
    cursor = AdvanceLeft(cursor, 1);
}

void Editor::Right() {
    cursor = AdvanceRight(cursor, 1);
}

void Editor::Insert(char token) {
    editor.insert(cursor, token);
}

void Editor::Cut(size_t tokens) {
    auto cursor2 = AdvanceCopy(tokens);
    cursor = editor.erase(cursor, cursor2);
}

void Editor::Copy(size_t tokens) {
    AdvanceCopy(tokens);
}

void Editor::Paste() {
    editor.insert(cursor, buffer.begin(), buffer.end());
}

std::string Editor::GetText() const {
    return {editor.begin(), editor.end()};
}


using Iterator = std::list<char>::iterator;

Iterator Editor::AdvanceCopy(size_t tokens){
    auto cursor2 = AdvanceRight(cursor, tokens);
    buffer.assign(cursor, cursor2);
    return cursor2;
}

Iterator Editor::AdvanceLeft(Iterator it, size_t n){
    for(; n != 0 && it != editor.begin(); --n){
        --it;
    }
    return it;
}

Iterator Editor::AdvanceRight(Iterator it, size_t n){
    for(; n != 0 && it != editor.end(); --n){
        ++it;
    }
    return it;
}