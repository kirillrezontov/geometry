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
	Vector<string> parse_command(const string& input);
	
};