#pragma once
#include "shape.h"

class square : public shape {
	double side;
public:
	class neg_side_exception : public shape::neg_value_exception {
	public:
		neg_side_exception(double side):shape::neg_value_exception(side){}
	};
	square();
	square(double s, double x, double y);
	square(square& other);
	void* operator new(size_t len);
	void operator delete(void* ptr);
	shape* clone() override;
	double area() override;
	double perimeter() override;
	void print(std::ostream& stream) override;
	friend std::ostream& operator<< (std::ostream& stream, square& s);
	friend std::istream& operator>> (std::istream& stream, square& s);
	std::istream& _import(std::istream& stream) override;
	std::ostream& _export(std::ostream& stream) override;
};