#pragma once
#include <iostream>

class String {
private:
    size_t* _countref = nullptr;
    char* _arr = nullptr;
    size_t _len = 0;
    size_t _capacity = 0;

    void release(); //полностью освобождает и ресурсы после релиза можно переписывать
    void branch(size_t new_capacity = 0);// копирует старое значение в новую память и коунтреф
    void initialization(size_t size);//инициализация

public:
    String();
    String(const char* str);
    String(const char* str, size_t n);
    String(size_t n, char c);
    String(const String& str);
    String(const String& str, size_t pos, size_t len = npos);
    virtual ~String() noexcept;

    size_t size() const; //размер, поставил конст
    size_t capacity() const; //вместимость(2*размер+1), поставил конст
    void reserve(size_t n = 0);
    void clear();
    bool empty() const;

    char& at(size_t pos);
    const char& at(size_t pos) const;

    char& operator[](size_t pos);
    const char& operator[](size_t pos) const;

    char& back();
    const char& back() const;

    char& front();
    const char& front() const;

    String& operator+=(const String& str);
    String& operator+=(const char* str);
    String& operator+=(char c);

    String& operator=(const String& str);
    String& operator=(const char* str);

    //выполняет вставку строки str в позицию pos.
    //Если pos больше размера строки, то выбрасывается исключение throw std::out_of_range("message");.
    String& insert(size_t pos, const String& str);
    String& insert(size_t pos, const char* str);

    //выполняет удаление подстроки в строке начиная с позиции pos и охватывая len символов.
    //Если len равняется npos, то удаление происходит с позиции pos до конца строки. Если pos больше размера строки, то выбрасывается исключение throw    . 
    //std::out_of_range("message");.
    String& erase(size_t pos = 0, size_t len = npos);

    //выполняет замену подстроки в строке начиная с позиции pos и охватывая len символов.
    //Если len равняется npos, то удаление происходит с позиции pos до конца строки.
    //Если pos больше размера строки, то выбрасывается исключение throw std::out_of_range("message");.
    String& replace(size_t pos, size_t len, const String& str);
    String& replace(size_t pos, size_t len, const char* str);
    String& replace(size_t pos, size_t len, size_t n, char c);

    void swap(String& str);
    const char* data() const;

    //возвращает индекс подстроки str (или символа c) в строке. pos - задает позицию с которой начинать поиск.
    //Если подстроку не нашли или pos больше размера строки, метод возращает npos.
    size_t find(const String& str, size_t pos = 0) const;
    size_t find(const char* str, size_t pos = 0) const;
    size_t find(char c, size_t pos = 0) const;

    String substr(size_t pos = 0, size_t len = npos) const;

    int compare(const String& str) const;
    //статическая константа с максимальным значением size_t.
    // Это значением может быть использовано в методах для параметра len, что означает "до конца строки".
    //Также эта константа может быть использована в качестве возвращаемого значения для указания отсутствия совпадений.
    static const size_t npos = -1;

    //Возвращает текущее количество ссылок на строку.
    //Т.е. количество объектов, которые ссылаются на данную строку. (Этот метод нужен для unit test'ов.?)
    size_t countRef() const; //число ссылок
};