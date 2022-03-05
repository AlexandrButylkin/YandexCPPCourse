#include <string>
#include <vector>
#include <list>
#include "test_runner.h"
//#include "C:\Users\cobak\CLionProjects\red_belt\profiler\MyProfiler.h"
using namespace std;

class Editor {
public:
  // Реализуйте конструктор по умолчанию и объявленные методы
    Editor() : cursor(editor.end()) {}

    void Left(){ if(cursor != editor.begin()) --cursor; }

    void Right() { if (cursor != editor.end()) ++cursor; }

    void Insert(char token) {
        cursor = editor.insert(cursor, token);
        ++cursor;
    }

    void Cut(size_t tokens = 1) {
        buffer.clear();
        auto it_end = std::next(cursor, tokens);
        if(std::distance(cursor, editor.end()) < tokens){
            buffer.splice(buffer.begin(), editor, cursor, editor.end());
        } else {
            buffer.splice(buffer.begin(), editor, cursor, it_end);
        }
        cursor = it_end;
    }

    void Copy(size_t tokens = 1) {
        buffer.clear();
        buffer = std::list(cursor, std::next(cursor, tokens));
    }

    void Paste() { editor.insert(cursor, buffer.begin(), buffer.end()); }

    string GetText() const {
        std::string str(editor.begin(), editor.end());
        return str;
    }

private:
    std::list<char> editor;
    std::list<char>::iterator cursor;
    std::list<char> buffer;

};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");
    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }
    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);

    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;

    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }

  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");

  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();

  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  return 0;
}