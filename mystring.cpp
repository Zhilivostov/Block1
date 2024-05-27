//#pragma warning(disable : 4996) // костыль для strcpy и strncpy
//#pragma warning(disable : 6386) // костыль для 33 строки (m_arr[n] = '\0')

#include "mystring.h"
#include <algorithm> //подключает std::min
#include <cstring> //подключает strlen - считает количество символов до детерменированного нуля, strcpy - копирует содержимое второй строки в первую, strncpy
#include <stdexcept>  //исключения

void String::release()//провеерка на нулптр
{
	/*if (_countref == nullptr || _arr == nullptr)
	{
		throw std::invalid_argument("Passing a null pointer!");
	}*/
	if (*_countref > 1)
	{
		--*_countref;
	}
	else
	{
		delete _countref;
		delete[] _arr;
	}
	_countref = nullptr;
	_arr = nullptr;
}

void String::branch(size_t new_capacity)//провеерка на нулптр
{
	if (_countref == nullptr || _arr == nullptr)
	{
		throw std::invalid_argument("Passing a null pointer!");
	}
	if (*_countref > 1)
	{
		--*_countref;
		char* new_arr = new char[std::max(_capacity, new_capacity)];
		memcpy(new_arr, _arr, _len);
		_arr = new_arr;
		_countref = new size_t(1);
		return;
	}
}

void String::initialization(size_t size)
{
	if (_arr == nullptr && _countref == nullptr)
	{
		_len = 0;
		_capacity = 2 * size + 1;
		_arr = new char[_capacity];
		_countref = new size_t(1);
		_arr[0] = '\0';
	}

}

String::String()
{
	initialization(0);
}

String::String(const char* str)
{
	if (str == nullptr)
	{
		throw std::invalid_argument("Passing a null pointer!");
	}
	initialization(strlen(str));
	_len = strlen(str);
	memcpy(_arr, str, _len);
	_arr[_len] = '\0';
}

String::String(const char* str, size_t n)
{
	if (str == nullptr)
	{
		throw std::invalid_argument("Passing a null pointer!");
	}
	initialization(std::min(n, strlen(str)));
	_len = std::min(n, strlen(str));
	memcpy(_arr, str, _len);
	_arr[_len] = '\0';
}

String::String(size_t n, char c)
{
	initialization(n);
	_len = n;
	memset(_arr, c, n);
	_arr[n] = '\0';
}

String::String(const String& str) :
	_len(str._len), _capacity(str._capacity), _arr(str._arr), _countref(str._countref)
{
	if (_countref != nullptr)
		(*_countref)++;
}

String::String(const String& str, size_t pos, size_t len)
{
	if (pos > str._len)
	{
		throw std::out_of_range("Invalid argument : pos > lenght of string!");
	}
	initialization(std::min(str._len - pos, len));
	_len = std::min(str._len - pos, len);
	memcpy(_arr, str._arr + pos, _len);
	_arr[_len] = '\0';
}

String::~String()
{
	release();
}

size_t String::size() const
{
	return _len;
}

size_t String::capacity() const
{
	return _capacity;
}

void String::reserve(size_t n) //!!!!!!не ломается ли здесь count referense?
{
	if (n <= _capacity)
	{
		return;
	}
	branch(n);	
}

void String::clear()
{
	release();
	initialization(0);
}

bool String::empty() const
{
	return _len == 0;
}

char& String::at(size_t pos)
{
	if (pos >= _len)
		throw std::out_of_range("Out of range string");
	branch();
	return _arr[pos];
}

const char& String::at(size_t pos) const
{
	if (pos >= _len)
		throw std::out_of_range("Out of range string");
	return _arr[pos];
}

char& String::operator[](size_t pos)
{
	return at(pos);
}

const char& String::operator[](size_t pos) const
{
	return at(pos);
}

char& String::back()
{
	return at(_len - 1);
}

const char& String::back() const
{
	return at(_len - 1);
}

char& String::front()
{
	return at(0);
}

const char& String::front() const
{
	return at(0);
}

String& String::operator+=(const String& str)
{
	return insert(_len, _arr);
}

String& String::operator+=(const char* str)
{
	return insert(_len, str);
}

String& String::operator+=(char c)
{
	char str[] = { c, '\0' };
	return insert(_len, str);
}


String& String::operator=(const String& str)
{
	if (this == &str)
		return *this;
	release();
	_len = str._len;
	_capacity = str._capacity;
	_arr = str._arr;
	_countref = str._countref;
	++*_countref;
	return *this;
}

String& String::operator=(const char* str)  /// 
{
	if (str == nullptr)
	{
		throw std::invalid_argument("Passing a null pointer!");
	}
	*this = String(str);
	return *this;
}

String& String::insert(size_t pos, const String& str) ////////
{
	if (str.empty())
		return *this;
	if (pos > _len)
		throw std::out_of_range("Out of range string");
	return insert(pos, str._arr);
}

String& String::insert(size_t pos, const char* str) ///////////
{
	if (str == nullptr)
		throw std::invalid_argument("passing a null pointer");
	if (pos > _len)
		throw std::out_of_range("Out of range string");
	branch();
	String str_shift = this->substr(pos, _len - pos);
	reserve(_len + strlen(str));
	memcpy(_arr + pos, str, strlen(str));
	memcpy(_arr + pos + strlen(str), str_shift._arr, str_shift._len);
	_len += strlen(str);
	_arr[_len] = '\0';
	return *this;
}

String& String::erase(size_t pos, size_t len) ///////////
{
	replace(pos, len, "");
	return *this;
}

String& String::replace(size_t pos, size_t len, const String& str) //////////////
{
	if (pos > _len)
		throw std::out_of_range("Out of range string");
	return replace(pos, len, str._arr);
}

String& String::replace(size_t pos, size_t len, const char* str) ////////////
{
	if (str == nullptr)
		throw std::invalid_argument("passing a null pointer");
	if (pos > _len)
		throw std::out_of_range("Out of range string");
	branch();
	size_t replacableLen = std::min(_len - pos, len);
	String str_shift = substr(pos + replacableLen, _len - pos - replacableLen);
	_len = pos;
	_arr[_len] = '\0';
	reserve(_len - replacableLen + strlen(str));
	insert(pos, str);
	insert(_len, str_shift);
	return *this;
}

String& String::replace(size_t pos, size_t len, size_t n, char c) //////////////
{
	if (pos > _len)
		throw std::out_of_range("Out of range string");
	return replace(pos, len, String(n, c));
}

void String::swap(String& str)
{
	if (this != &str)
	{
		std::swap(_len, str._len);
		std::swap(_capacity, str._capacity);
		std::swap(_arr, str._arr);
		std::swap(_countref, str._countref);
	}
	else
		throw std::invalid_argument("It`s this!");
}

const char* String::data() const
{
	return _arr;
}

size_t String::find(const String& str, size_t pos) const
{
	return find(str.data(), pos);
}

size_t String::find(const char* str, size_t pos) const
{
	if (str == nullptr)
	{
		throw std::invalid_argument("Passing a null pointer!");
	}
	if (pos > _len)
		return npos;
	for (size_t i = pos; i <= _len - strlen(str); i++)
		if (memcmp(_arr + i, str, strlen(str)) == 0)
		{
			return i;
		}
	return npos;
}

size_t String::find(char c, size_t pos) const
{
	char str[] = { c, '\0' };
	return find(str, pos);
}

String String::substr(size_t pos, size_t len) const
{
	if (pos > _len)
	{
		throw std::out_of_range("Out of range string!");
	}
	return String(*this, pos, len);
}

int String::compare(const String& str) const
{
	return strcmp(_arr, str.data()); //сравнивает посимвольно строки
}

size_t String::countRef() const
{
	return *_countref;
}
