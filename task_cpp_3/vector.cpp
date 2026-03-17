#include "vector.h"
#include "circle.h"
#include "square.h"
#include <cstdlib> 
#include <fstream>
#include <string>
vector::vector() {};

vector::vector(int size) {
	this->size = size; capacity = size<<1;
	if(data) free(data);
	data = (shape**)malloc(sizeof(shape*)*capacity);
	if (!data) throw memory_allocation_exception();
}

vector::vector(const vector& v) {
	this->size = v.size; capacity = v.capacity;
	if (data) free(data);
	this->data = (shape**)malloc(sizeof(shape*) * capacity);
	if (!data) throw memory_allocation_exception();
	for(int i = 0; i<size; i++) 
	{
		if (!v.data[i]) data[i] = NULL;
		else {
			data[i] = v.data[i]->clone();
		}
	}
}

vector::~vector() {
	for (int i = 0; i < size; i++) {
		delete (*this)[i];
	}
}

void vector::output(std::ostream& stream) const {
	stream << size << std::endl;
	for (int i = 0; i < size; i++) {
		try {
			shape* a = (*this)[i];
			if (!a) throw uninitialized_data_exception();
			(*this)[i]->print(stream);
		}
		catch (uninitialized_data_exception& e) {
			stream << "null shape" << std::endl;
			continue;
		}
	}
}

std::ostream& operator<<(std::ostream& stream, vector& v) {
	stream << v.get_size() << std::endl;
	for (int i = 0; i < v.get_size(); i++) {
		try{
			v[i]->_export(stream);
		}
		catch (uninitialized_data_exception& e) {
			stream << "NULL\n";
		}
	}
	return stream;
}

std::istream& operator>>(std::istream& stream, vector& v) {
	int size; std::string buf;
	buf.reserve(15); 
	stream >> size;
	int olds = v.get_size();
	v.reserve(size + olds);
	for (int i = olds; i < size+olds; i++) {
		stream >> buf;
		if (buf == "circle") 
		{
			v.push_back((shape*)new circle);
			v[i]->_import(stream);
			continue;
		}
		if (buf == "square")
		{
			v.push_back((shape*)new square);
			v[i]->_import(stream);
			continue;
		}
		if (buf == "NULL")
		{
			v.push_back(NULL);
			continue;
		}
		else continue;
	}
	return stream;
}

void vector::output_to_file(const char *path) const{
	std::ofstream f(path);
	this->output(f);
	f.close();
}

void vector::save_to_file(const char* path) {
	std::ofstream f(path);
	f << (*this);
	f.close();
}

void vector::read_from_file(const char* path) {
	std::ifstream f(path);
	f >> (*this);
	f.close();
}
