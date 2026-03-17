#pragma once
#include "vector.h"
#include "shape.h"
#include "circle.h"
#include "square.h"
#include <string>
#include <map>

using namespace std;
class Interface {
	map<string, vector*> vectors;
	map<string, shape*> shapes;
public:
	Interface();
	void start();
	void end();
	Vector<string> parse_command(string& input);
	void vector_command(const Vector<string>& cmd);
	template <class T> void shape_command(const Vector<string>& cmd);
	void object_call_command(const Vector<string>& cmd);
	void shape_call_command(const Vector<string>& cmd);
	void vector_call_command(const Vector<string>& cmd);
};