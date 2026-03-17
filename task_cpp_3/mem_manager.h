#pragma once
#include <cstdlib>
#include <string>
#include "shape.h"


template<class T> class mem_manager {
	struct hole {
		hole* next;
	};
	T* ptr;
	int capacity;
	int max;
	hole* last_hole;
public:
	class out_of_memory_exception {
		int size;
	public:
		out_of_memory_exception(int s) : size(s) {}
		std::string get_message() { return "Unable to allocate: " + std::to_string(size); }
	};
	class del_exception {
	public:
		std::string get_message() { return "Unable to deallocate, nothing is allocated"; }
	};
	mem_manager(int cap) : capacity(cap) {
		max = 0;
		ptr = (T*)malloc(sizeof(T) * cap);
		if (ptr == nullptr) throw out_of_memory_exception(cap);
		last_hole = NULL;
	}
	~mem_manager() {
		free(ptr);
	}
	T* allocate(int size) {
		if (size < 0 || size > capacity - max) return NULL;
		if (last_hole) {
			T* ptr = (T*)last_hole;
			last_hole = last_hole->next;
		}
		T* p = ptr + max;
		max += size;
		return p;
	}
	void deallocate(T* p) {
		if (max == 0) throw del_exception();
		hole* head = (hole*)p;
		head->next = last_hole;
		last_hole = head;
		max--;
	}
};
