#pragma once
#include "shape.h"

class index_out_of_range_exception {
protected:
	int index;
public:
	index_out_of_range_exception(int i) { index = i; }
	int get_index() { return index; }
};
class memory_allocation_exception {};
class uninitialized_data_exception {};

template<class T> class Vector{
protected:
	T** data;
	int size;
	int capacity;
public:
	Vector() {
		size = 0; capacity = 1;
		data = (T**)malloc(sizeof(T*)*capacity);
		if (!data) throw memory_allocation_exception();
	}
	virtual ~Vector() {
		if(data) free(data);
	}
	Vector(int size) {
		size = size; capacity = size << 1;
		if (data) free(data);
		data = (T**)malloc(capacity*sizeof(T*));
		if (!data) throw memory_allocation_exception();
	}
	void push_back(T* s) {
		if (size == capacity) {
			capacity <<= 1;
			T** tmp = (T**)realloc(data, sizeof(T*) * capacity);
			if (!tmp)
			{
				throw memory_allocation_exception();
			}
			data = tmp;
		}
		data[size++] = s;
	}
	T*& operator[](int index) const{
		if (index < 0 || index >= size) throw index_out_of_range_exception(index);
		return data[index];
	}
	int reserve(int size) {
		if (size < this->size) return -1;
		T** tmp = (T**)realloc(data, sizeof(T*) * size);
		if (tmp) data = tmp;
	}
	int get_size() { return size; }
	int get_capacity() { return capacity; }
	T* get(int index) const {
		T* i = (*this)[index];
		if (!i) throw uninitialized_data_exception();
		return i;
	}
	void put(int index, T* s) {
		(*this)[index] = s;
	}
	T* front() { return (*this)[0]; }
	T* back() { return (*this)[size - 1]; }
};

class vector : public Vector<shape> {
public:
	vector();
	vector(int size);
	vector(const vector& v);
	~vector();
	friend std::ostream& operator<<(std::ostream& stream, vector& v);
	friend std::istream& operator>>(std::istream& stream, vector& v);
	void output(std::ostream& stream) const;
	void output_to_file(const char* path) const;
	void save_to_file(const char* path);
	void read_from_file(const char* path);
	friend void test_vector();
};
