#pragma once


#include <iostream>
#include <cstring>


class String
{
private:
	char* string;
	int length;

	void copy(const String& string);
	void copy(const char* cString);
	void clear();
	
public:
	String();
	String(const String& string);
	String(const char* cString);
	String(int number);
	~String();

	void trimWhitespace();
	void trimPrecedingWhitespace();
	void trimTrailingWhitespace();

	bool hasCharacter(char character);
	bool hasCharacter(char character, int startIndex);

	int countCharacter(char character);
	int countCharacter(char character, int startIndex);

	String substring(int startIndex);
	String substring(int startIndex, int endIndex);

	int findCharacter(char character);
	int findCharacter(char character, int startIndex);
	int findSubstring(const String& substring);
	int findSubstring(const String& substring, int startIndex);

	bool isNumber();
	int parseToInt();
	
	String& operator=(const String& string);
	String& operator=(const char* cString);
	String& operator=(const int number);

	String& operator+=(const String& string);
	String& operator+=(const char* cString);
	String& operator+=(const int number);

	String operator+(const String& string);
	String operator+(const char* cString);

	bool operator==(const String& string);
	bool operator==(const char* cString);

	bool operator!=(const String& string);
	bool operator!=(const char* cString);

	char& operator[](int index);

	int getLength() const;
	const char* getCString() const;

	friend std::ostream& operator<<(std::ostream& os, const String& string);
	
	friend std::istream& operator>>(std::istream& is, String& string);
};

