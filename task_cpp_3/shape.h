#pragma once
#include <string>
#include <iostream>

struct point{
	double x, y;
};



class shape {
protected:
	point center;
public:
	class neg_value_exception {
	protected:
		int neg_value;
	public:
		neg_value_exception(double value);
		double get_value();
	};
	virtual double area() = 0;
	virtual double perimeter() = 0;
	virtual ~shape(){}
	void* operator new(size_t len) {}
	void operator delete(void* ptr) {}
	friend std::ostream& operator<< (std::ostream& stream, shape& s);
	friend std::istream& operator>> (std::istream& stream, shape& s);
	virtual std::istream& _import(std::istream& stream);
	virtual std::ostream& _export(std::ostream& stream);
	virtual void print(std::ostream& stream);
	virtual shape* clone() = 0;
};
