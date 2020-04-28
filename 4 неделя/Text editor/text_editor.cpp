#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
public:
    // Реализуйте конструктор по умолчанию и объявленные методы
    Editor() {
        cursor_position = data.end();
    }

    void Left() {
        if (cursor_position != data.begin())
            --cursor_position;
    }

    void Right() {
        if (cursor_position != data.end())
            ++cursor_position;
    }

    void Insert(char token) {
        data.insert(cursor_position, token);
    }

    void PutInBuffer(list<char>::iterator begin, list<char>::iterator end) {
        buffer.erase(buffer.begin(), buffer.end());
        for (auto it = begin; it != end ; ++it) {
            buffer.insert(buffer.end(), *it);
        }
    }

    void Cut(size_t tokens = 1) {
        size_t shift = 0;
        auto cut_end = cursor_position;
        while (cut_end != data.end() && shift < tokens) {
            ++shift;
            ++cut_end;
        }
        PutInBuffer(cursor_position, cut_end);
        cursor_position = data.erase(cursor_position, cut_end);
    }

    void Copy(size_t tokens = 1) {
        size_t shift = 0;
        auto copy_end = cursor_position;
        while (copy_end != data.end() && shift < tokens) {
            ++shift;
            ++copy_end;
        }
        PutInBuffer(cursor_position, copy_end);
    }

    void Paste() {
        data.insert(cursor_position, buffer.begin(), buffer.end());
    }

    string GetText() const {
        return string(data.begin(), data.end());
    }

    string GetBuffer() const {
        return string(buffer.begin(), buffer.end());
    }
private:
    list<char> data;
    list<char> buffer;
    list<char>::iterator cursor_position;
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


void TestInsert() {
        Editor editor;
        const size_t text_len = 12;
        TypeText(editor, "hello, world");
        ASSERT_EQUAL(editor.GetText(), "hello, world");
}

void TestCopy() {
    Editor editor;
    const size_t text_len = 12;
    TypeText(editor, "hello, world");
    ASSERT_EQUAL(editor.GetText(), "hello, world");
    for(size_t i = 0; i < 3; ++i) {
        editor.Left();
    }
    editor.Copy(4);
    ASSERT_EQUAL(editor.GetBuffer(), "rld");
}

void TestPaste() {
    Editor editor;
    const size_t text_len = 12;
    TypeText(editor, "hello, world");
    ASSERT_EQUAL(editor.GetText(), "hello, world");
    for(size_t i = 0; i < 3; ++i) {
        editor.Left();
    }
    editor.Copy(4);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "hello, worldrld");
}



int main() {
    TestRunner tr;
    RUN_TEST(tr, TestInsert);
    RUN_TEST(tr, TestCopy);
    RUN_TEST(tr, TestPaste);
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    return 0;
}