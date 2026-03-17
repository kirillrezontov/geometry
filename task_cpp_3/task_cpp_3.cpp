#include "shape.h"
#include "circle.h"
#include "square.h"
#include "mem_manager.h"
#include <iostream>
#include "vector.h"
#include "string"
#include "map"
#include <sstream>
#include "interface.h"
#include <typeinfo>
using namespace std;

void caller();

void test_vector() {
	try {
		vector v;
		v.push_back(new circle(-1, 0, 0));
	}
	catch (circle::neg_radius_exception& e) {
		cout << "Negative radius init: " << e.get_value() << endl;
	}
	catch (square::neg_side_exception& e) {
		cout << "Negutive side init: " << e.get_value() << endl;
	}
	try {
		vector v;
		v[1] = new square(1, 0, 0);
	}
	catch (index_out_of_range_exception& e) {
		cout << "Out of range: " << e.get_index() << endl;
	}
	try {
		vector v;
		v.push_back(NULL);
		shape* s = v.get(v.get_size() - 1);
	}
	catch (uninitialized_data_exception& e){
		cout << "Getting uninitialized element" << endl;
	}
}
int main()
{
	/*
	shape** arr = (shape**)malloc(sizeof(shape*) * 10);
	for (int i = 0; i < 10; i++) {
		try {
			arr[i] = (i % 2) ? (shape*)new circle(i - 2, 0, 0) : (shape*)new square(i - 2, 0, 0);
		}
		catch (neg_value_exception& e) {
			cout << e.get_message() << endl;
			arr[i] = nullptr;
			continue;
		}
		arr[i]->print();
		cout << arr[i]->area() << endl;
		cout << arr[i]->perimeter() << endl;
		delete arr[i];
	}
	free(arr);
	return 0;*/
	/*int n = 1e7;
	circle** arr = new circle*[n];
	circle2** arr2 = new circle2*[n];
	clock_t start = clock();
	for(int i = 0; i < n; i++) {
		arr[i] = new circle;
	}
	clock_t end = clock();
	cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
	for(int i = 0; i < n; i++) {
		delete arr[i];
	}
	start = clock();
	for (int i = 0; i < n; i++) {
		arr2[i] = new circle2;
	}
	end = clock();
	cout << "Time taken: " << (double)(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
	for (int i = 0; i < n+1; i++) {
		delete arr2[i];
	}
	delete[] arr;
	delete[] arr2;*/
	/*int n = 100;
	try { 
		vector v; 
		for (int i = 0; i < n; i++) {
			try {
				v.push_back((i % 2) ? (shape*)new circle(i - 2, i, 0) : (shape*)new square(i - 2, i, 0));
			}
			catch (neg_value_exception& e) {
				cout << "Negative value init: " << e.get_value() << endl;
				continue;
			}
			catch (memory_allocation_exception& e) {
				cout << "Memory allocation failed" << endl;
				return 0;
			}
		}
		v.output(cout);
		v.save_file("shapes.txt");
	}
	catch (memory_allocation_exception& e) {
		cout << "Memory allocation failed" << endl;
	}

	try {
		vector v1(n);
		for ( int i = 0; i < n; i++) {
			try {
				v1[i] = ((i % 2) ? (shape*)new circle(i - 2, i, 0) : (shape*)new square(i - 2, i, 0));
			}
			catch (neg_value_exception& e) {
				cout << "Negative value init: " << e.get_value() << endl;
				v1[i] = NULL;
				continue;
			}
			catch (memory_allocation_exception& e) {
				cout << "Memory allocation failed" << endl;
				return 0;
			}
		}
		vector v2(v1);
		v2.output(cout);
		v2.save_file("shapes.txt");
	}
	catch (memory_allocation_exception& e) {
		cout << "Memory allocation failed" << endl;
	}
	return 0;*/
	/*int n = 100;
	try {
		vector v;
		for (int i = 0; i < n; i++) {
			try {
				v.push_back((i % 2) ? (shape*)new circle(i - 2, i, 0) : (shape*)new square(i - 2, i, 0));
			}
			catch (neg_value_exception& e) {
				cout << "Negative value init: " << e.get_value() << endl;
				continue;
			}
			catch (memory_allocation_exception& e) {
				cout << "Memory allocation failed" << endl;
				return 0;
			}
		}
		v.output(cout);
		v.save_to_file("shapes.txt");
	}
	catch (memory_allocation_exception& e) {
		cout << "Memory allocation failed" << endl;
	}*/


	/*vector v;
	v.read_from_file("shapes.txt");
	v.output(cout);*/
	Interface i;
	i.start();
	return 0;
}

void caller() {
	string input, cmd, name, name2;
	map<string, vector*> vectors;
	map<string, shape*> shapes;
	string next; int num1, num2, num3;
	while (true) {
		getline(cin, input);
		istringstream iss(input);
		iss >> cmd;
		iss >> ws;
		switch (cmd[0]) {
		case 'v':
			if (cmd == "vector") {
				iss >> name;
				iss >> ws;
				if (iss.eof()) { vectors[name] = new vector(); continue; }
				iss >> next;
				iss >> ws;
				try {
					num1 = stoi(next);
					if (num1 <= 0) { cout << "Neg size init: " << num1 << endl; continue; }
					vectors[name] = new vector(num1);
					continue;
				}
				catch (exception& e) {
					if (next == "copy") {
						if (iss.eof()) { cout << "No object provided to copy" << endl; continue; }
						else {
							iss >> name2;
							try { vectors[name] = new vector(*vectors.at(name2)); continue; }
							catch (out_of_range& e) { cout << "No object provided to copy" << endl; continue; }
						}
					}
					else { cout << "Unknown syntax" << endl; continue; }
				}
			}
			break;
		case 'c':
			if (cmd == "circle") {
				iss >> name;
				iss >> ws;
				if (iss.eof()) { shapes[name] = new circle(); continue; }
				iss >> next;
				iss >> ws;
				try {
					num1 = stoi(next);
					if (num1 <= 0) { cout << "Neg radius init: " << num1 << endl; continue; }
					num2 = 0, num3 = 0;
					iss >> num2 >> num3;
					shapes[name] = new circle(num1, num2, num3);
					continue;
				}
				catch (exception& e) {
					if (next == "copy") {
						if (iss.eof()) { cout << "No object provided to copy" << endl; continue; }
						else {
							iss >> name2;
							try { shapes[name] = shapes.at(name2)->clone(); continue; }
							catch (out_of_range& e) { cout << "No object provided to copy" << endl; continue; }
						}
					}
					else { cout << "Unknown syntax" << endl; continue; }
				}
			}
			break;
		case 's':
			if (cmd == "square") {
				iss >> name;
				iss >> ws;
				if (iss.eof()) { shapes[name] = new square(); continue; }
				iss >> next;
				iss >> ws;
				try {
					num1 = stoi(next);
					if (num1 <= 0) { cout << "Neg side init: " << num1 << endl; continue; }
					num2 = 0, num3 = 0;
					iss >> num2 >> num3;
					shapes[name] = new square(num1, num2, num3);
					continue;
				}
				catch (exception& e) {
					if (next == "copy") {
						if (iss.eof()) { cout << "No object provided to copy" << endl; continue; }
						else {
							iss >> name2;
							try { shapes[name] = shapes.at(name2)->clone(); continue; }
							catch (out_of_range& e) { cout << "No object provided to copy" << endl; continue; }
						}
					}
					else { cout << "Unknown syntax" << endl; continue; }
				}
			}
			break;
		default: break;
		}
		name = cmd;
		try {
			shape* s = shapes.at(name);
			if (!iss.eof()) { cout << "Unknown syntax" << endl; continue; }
			s->print(cout);
		}
		catch (out_of_range& e) {
			try {
				vector* v = vectors.at(name);
				if (iss.eof()) v->output(cout);
				else {
					iss >> cmd;
					iss >> ws;
					switch (cmd[0])
					{
					case 'o':
						if (cmd == "output") {
							if (iss.eof()) v->output(cout);
							else {
								iss >> next;
								if (next == "console") v->output(cout);
								else if (next == "file") {
									if (iss.eof()) { cout << "No file provided" << endl; continue; }
									else {
										iss >> name2;
										v->output_to_file(name2.c_str());
									}
								}
								else { cout << "Unknown syntax" << endl; continue; }
							}
						}
						break;
					case 's':
						if (cmd == "save") {
							if (iss.eof()) { cout << "No file provided" << endl; continue; }
							else {
								iss >> next;
								if (next == "console") { cout << "Cannot save to console" << endl; continue; }
								else if (next == "file") {
									if (iss.eof()) { cout << "No file provided" << endl; continue; }
									else {
										iss >> name2;
										v->save_to_file(name2.c_str());
									}
								}
								else { cout << "Unknown syntax" << endl; continue; }
							}
						}
						break;
					case 'r':
						if (cmd == "read") {
							if (iss.eof()) { cout << "No file provided" << endl; continue; }
							else {
								iss >> next;
								if (next == "console") { cout << "Cannot read from console" << endl; continue; }
								else if (next == "file") {
									if (iss.eof()) { cout << "No file provided" << endl; continue; }
									else {
										iss >> name2;
										v->read_from_file(name2.c_str());
									}
								}
								else { cout << "Unknown syntax" << endl; continue; }
							}
						}
						break;
					case 'c':
						if (cmd == "copy") {
							if (iss.eof()) { cout << "No object provided to copy" << endl; continue; }
							else {
								iss >> name2;
								try {
									v = new vector(*vectors.at(name2));
								}
								catch (out_of_range& e) { cout << "No object provided to copy" << endl; continue; }
							}
						}
						break;
					case 'd':
						if (cmd == "delete") {
							delete v;
							vectors.erase(name);
						}
						break;
					case '[':
						if (cmd == "[]") { cout << "No index provided" << endl; continue; }
						else {
							try {
								num1 = stoi(cmd.substr(1, cmd.size() - 2));
							}
							catch (exception& e) {
								cout << "Unknown syntax" << endl;
								continue;
							}
							try {
								if (iss.eof()) { v->get(num1)->print(cout); continue; }
								iss >> cmd;
								iss >> ws;
								if (cmd == "print") v->get(num1)->print(cout);
								else if (cmd == "area") cout << v->get(num1)->area() << endl;
								else if (cmd == "perimeter") cout << v->get(num1)->perimeter() << endl;
								else if (cmd == "put") {
									if (iss.eof()) { cout << "No shape provided" << endl; continue; }
									else {
										iss >> next;
										shape* new_s;
										try {
											new_s = shapes.at(next)->clone();
										}
										catch (out_of_range& e) { cout << "No shape provided" << endl; continue; }
										v->put(num1, new_s);
									}
								}
								else { cout << "Unknown syntax" << endl; continue; }

							}
							catch (uninitialized_data_exception& e) {
								cout << "Getting uninitialized element" << endl;
								continue;
							}
							catch (index_out_of_range_exception& e) {
								cout << "Index out of range: " << e.get_index() << endl;
								continue;
							}
						}
						break;
					case 'p':
						if (cmd == "push_back") {
							if (iss.eof()) { cout << "No shape provided" << endl; continue; }
							else {
								iss >> next;
								shape* new_s;
								try {
									new_s = shapes.at(next)->clone();
								}
								catch (out_of_range& e) { cout << "No shape provided" << endl; continue; }
								v->push_back(new_s);
							}
						}
					default:
						break;
					}

				}
			}
			catch (out_of_range& e) {
				cout << "Unknown object" << endl;
				continue;
			}
		}
	}
}
