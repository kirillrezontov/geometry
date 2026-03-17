#pragma once
#include "shape.h"



class circle : public shape {
protected:
	double radius;
public:
	class neg_radius_exception : public neg_value_exception {
	public:
		neg_radius_exception(double value) : neg_value_exception(value) {}
	};
	circle();
	circle(double r, double x, double y);
	circle(circle& other);
	void* operator new(size_t len);
	void operator delete(void* ptr);
	shape* clone() override;
	double area() override;
	double perimeter() override;
	void print(std::ostream& stream) override;
	friend std::ostream& operator<< (std::ostream& stream, circle& c);
	friend std::istream& operator>> (std::istream& stream, circle& c);
	std::istream& _import(std::istream& stream) override;
	std::ostream& _export(std::ostream& stream) override;
};
