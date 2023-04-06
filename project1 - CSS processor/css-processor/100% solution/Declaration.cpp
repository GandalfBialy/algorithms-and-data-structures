#include "Declaration.h"


Declaration::Declaration() :
	property(String()),
	value(String()) {
}


Declaration::Declaration(String property, String value) :
	property(property),
	value(value) {
}


void Declaration::setProperty(String property) {
	this->property = property;
}


void Declaration::setValue(String value) {
	this->value = value;
}


String Declaration::getProperty() const {
	return property;
}


String Declaration::getValue() const {
	return value;
}


Declaration::operator String() const {
	return property;
}
