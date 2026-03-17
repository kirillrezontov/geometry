#include "circle.h"
#include <iostream>
#include "mem_manager.h"

circle::circle() {
	radius = 0;
	center = { 0, 0 };
}

circle::circle(double r, double x, double y) {
	if (r < 0) throw neg_value_exception(r);
	radius = r;
	center = { x, y };
}

circle::circle(circle& other) {
	radius = other.radius;
	center = other.center;
}

shape* circle::clone() {
	return new circle(*this);
}

double circle::area() {
	return 3.14159 * radius * radius;
}

double circle::perimeter() {
	return 2 * 3.14159 * radius;
}

std::ostream& operator<<(std::ostream& stream, circle& c) {
	stream << "circle " << c.center.x << " " << c.center.y << " " << c.radius << std::endl;
	return stream;
}

std::istream& operator>>(std::istream& stream, circle& c) {
	stream >> c.center.x >> c.center.y >> c.radius;
	return stream;
}

std::ostream& circle::_export(std::ostream& stream) {
	return stream << (*this);
}

std::istream& circle::_import(std::istream& stream) {
	return stream >> (*this);
}

void circle::print(std::ostream& stream) {
	stream << "center: " << center.x << ", " << center.y << "\nradius: " << radius << std::endl;
}

static int n = 1e7;
mem_manager<circle> cman(n);

void* circle::operator new(size_t len) {
	try {
	return cman.allocate(len / sizeof(circle));
	}
	catch (mem_manager<circle>::out_of_memory_exception& e) {
		std::cout << e.get_message() << std::endl;
		return nullptr;
	}
	catch (neg_value_exception& e) {
		std::cout << "Negative value: " << e.get_value() << std::endl;
		return nullptr;
	}
}

void circle::operator delete(void* ptr) {
	try {
		cman.deallocate((circle*)ptr);
	}
	catch (mem_manager<circle>::del_exception& e) {
		std::cout << e.get_message() << std::endl;
	}
}