#include "String.h"


String::String() {
	length = 0;
	
	string = new char[1];
	string[0] = '\0';
}


String::String(const String& string) {
	this->copy(string);
}


String::String(const char* cString) {
	this->copy(cString);
}


String::~String() {
	delete[] string;
}


String& String::operator=(const String& string) {
	if (this != &string) {
		delete[] this->string;

		this->copy(string);
	}

	return *this;
}


String& String::operator=(const char* cString) {
	delete[] this->string;

	this->copy(cString);

	return *this;
}


String& String::operator+=(const String& string) {
	length += string.length;

	char* temp = new char[length + 1];
	strcpy_s(temp, length + 1, this->string);
	strcat_s(temp, length + 1, string.string);

	delete[] this->string;
	this->string = temp;

	return *this;
}


String& String::operator+=(const char* cString) {
	length += strlen(cString);

	char* temp = new char[length + 1];
	strcpy_s(temp, length + 1, this->string);
	strcat_s(temp, length + 1, cString);

	delete[] this->string;
	this->string = temp;

	return *this;
}


String String::operator+(const String& string) {
	String temp(*this);
	temp += string;

	return temp;
}


String String::operator+(const char* cString) {
	String temp(*this);
	temp += cString;

	return temp;
}


bool String::operator==(const String& string) {
	return strcmp(this->string, string.string) == 0;
}


bool String::operator==(const char* cString) {
	return strcmp(this->string, cString) == 0;
}


bool String::operator!=(const String& string) {
	return strcmp(this->string, string.string) != 0;
}


bool String::operator!=(const char* cString) {
	return strcmp(this->string, cString) != 0;
}


char& String::operator[](int index) {
	return string[index];
}


int String::getLength() const {
	return length;
}


const char* String::getCString() const {
	return string;
}


std::ostream& operator<<(std::ostream& os, const String& string) {
	os << string.string;

	return os;
}


std::istream& operator>>(std::istream& is, String& string) {
	char buffer[1024];
	is >> buffer;

	string = buffer;

	return is;
}


void String::copy(const String& string) {
	length = string.length;

	this->string = new char[length + 1];
	strcpy_s(this->string, length + 1, string.string);
}


void String::copy(const char* cString) {
	length = strlen(cString);

	this->string = new char[length + 1];
	strcpy_s(this->string, length + 1, cString);
}


void String::clear() {
	delete[] string;
}
