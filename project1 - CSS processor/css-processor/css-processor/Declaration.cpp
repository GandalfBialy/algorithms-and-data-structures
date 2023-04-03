#include "Declaration.h"


Declaration::Declaration() {
	property = "";
	value = "";
}


void Declaration::setProperty(String property) {
	this->property = property;
}


void Declaration::setValue(String value) {
	this->value = value;
}


String Declaration::getProperty() {
	return property;
}


String Declaration::getValue() {
	return value;
}
