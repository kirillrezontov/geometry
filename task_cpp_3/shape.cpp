#include "shape.h"
#include <iostream>

std::ostream& operator<<(std::ostream& stream, shape& s) {
	stream << "shape " << s.center.x << " " << s.center.y << std::endl;
	return stream;
}

std::istream& operator>>(std::istream& stream, shape& s) {
	stream >> s.center.x >> s.center.y;
	return stream;
}

std::ostream& shape::_export(std::ostream& stream) {
	return stream << (*this);
}

std::istream& shape::_import(std::istream& stream) {
	return stream >> (*this);
}

void shape::print(std::ostream& stream) {
	stream << "center: " << center.x << ", " << center.y <<std::endl;
}

shape::neg_value_exception::neg_value_exception(double value){
	neg_value = value;
}

double shape::neg_value_exception::get_value() { return neg_value; }