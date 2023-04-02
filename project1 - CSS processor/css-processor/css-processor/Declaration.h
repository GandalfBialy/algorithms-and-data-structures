#pragma once


#include "String.h"


class Declaration
{
private:
	String property;
	String value;

public:
	void setProperty(String property);
	void setValue(String value);
};

