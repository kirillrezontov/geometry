#include "square.h"
#include "mem_manager.h"
#include <iostream>

square::square() {
	side = 0;
	center = { 0, 0 };
}

square::square(double s, double x, double y) {
	if (s < 0) throw neg_value_exception(s);
	side = s;
	center = { x, y };
}

square::square(square& other) {
	side = other.side;
	center = other.center;
}

shape* square::clone() {
	return new square(*this);
}

double square::area() {
	return side * side;
}

double square::perimeter() {
	return 4 * side;
}

std::ostream& operator<<(std::ostream& stream, square& s) {
	stream << "square " << s.center.x << " " << s.center.y << " " << s.side << std::endl;
	return stream;
}

std::istream& operator>>(std::istream& stream, square& s) {
	stream >> s.center.x >> s.center.y >> s.side;
	return stream;
}

std::ostream& square::_export(std::ostream& stream) {
	return stream << (*this);
}

std::istream& square::_import(std::istream& stream) {
	return stream >> (*this);
}

void square::print(std::ostream& stream) {
	stream << "center: " << center.x << ", " << center.y << "\nside: " << side<<std::endl;
}

static int n = 1e7;
mem_manager<square> sman(n);


void* square::operator new(size_t len) {
	try {
		return sman.allocate(len / sizeof(square));
	}
	catch (mem_manager<square>::out_of_memory_exception& e) {
		std::cout << e.get_message() << std::endl;
		return nullptr;
	}
	catch (neg_value_exception& e) {
		std::cout << "Negative value: " << e.get_value() << std::endl;
		return nullptr;
	}
}

void square::operator delete(void* ptr) {
	try {
		sman.deallocate((square*)ptr);
	}
	catch (mem_manager<square>::del_exception& e) {
		std::cout << e.get_message() << std::endl;
	}
}