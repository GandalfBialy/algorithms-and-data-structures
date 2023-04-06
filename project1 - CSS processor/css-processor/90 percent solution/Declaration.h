#pragma once


#include "String.h"


class Declaration
{
private:
	String property;
	String value;

public:
	Declaration();
	Declaration(String property, String value);

	void setProperty(String property);
	void setValue(String value);

	String getProperty() const;
	String getValue() const;

	operator String() const;
};

