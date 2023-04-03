#pragma once


#include "String.h"


class Declaration
{
private:
	String property;
	String value;

public:
	Declaration();

	void setProperty(String property);
	void setValue(String value);

	String getProperty();
	String getValue();
};

