#include "interface.h"
#include <sstream>
Interface::Interface() {}

void Interface::start() {
	string input;
	while (true) {
		getline(cin, input);
		Vector<string> cmd = parse_command(input);
		if (cmd.empty()) continue;
		string& command = *cmd[0];
		if (command == "exit") break;
		if (command == "vector") vector_command(cmd);
		else if (command == "circle") shape_command<circle>(cmd);
		else if (command == "square") shape_command<square>(cmd);
		else object_call_command(cmd);
	}
}

Vector<string> Interface::parse_command(string& input) {
	
	Vector<string> res;
	string token;
	istringstream iss(input);
	while (iss>>token)
	{
		if (!token.empty()) res.push_back(new string(token));
	}
	return res;
}

void Interface::vector_command(const Vector<string>& cmd) {
	if (cmd.get_size() < 2) { cout << "No name provided" << endl; return; }
	string& name = *cmd[1];
	if (cmd.get_size() == 2) { vectors[name] = new vector(); return; }
	string& next = *cmd[2];
	try {
		int num = stoi(next);
		if (num <= 0) { cout << "Neg size init: " << num << endl; return; }
		vectors[name] = new vector(num);
		return;
	}
	catch (exception& e) {
		if (next == "copy") {
			if (cmd.get_size() == 3) { cout << "No object provided to copy" << endl; return; }
			else {
				string& name2 = *cmd[3];
				try { vectors[name] = new vector(*vectors.at(name2)); return; }
				catch (out_of_range& e) { cout << "No object provided to copy" << endl; return; }
			}
		}
		else { cout << "Unknown syntax" << endl; return; }
	}
}

template <class T> void Interface::shape_command(const Vector<string>& cmd) {
	if (cmd.get_size() < 2) { cout << "No name provided" << endl; return; }
	string& name = *cmd[1];
	if (cmd.get_size() == 2) { shapes[name] = new T(); return; }
	string& next = *cmd[2];
	try {
		int num = stoi(next);
		if (num <= 0) { 
			string value_name = "value";
			if (typeid(T) == typeid(circle)) value_name = "radius";
			else if (typeid(T) == typeid(square)) value_name = "side";
			cout << "Neg " << value_name << " init: " << num << endl; return; 
		}
		int num2 = 0, num3 = 0;
		if (cmd.get_size() > 4) {
			num2 = stoi(*cmd[3]);
			num3 = stoi(*cmd[4]);
		}
		shapes[name] = new T(num, num2, num3);
		return;
	}
	catch (exception& e) {
		if (next == "copy") {
			if (cmd.get_size() == 3) { cout << "No object provided to copy" << endl; return; }
			else {
				string& name2 = *cmd[3];
				try { shapes[name] = shapes.at(name2)->clone(); return; }
				catch (out_of_range& e) { cout << "No object provided to copy" << endl; return; }
			}
		}
		else { cout << "Unknown syntax" << endl; return; }
	}
}

void Interface::shape_call_command(const Vector<string>& cmd) {
	shape* s = shapes.at(*cmd[0]);
	if (cmd.get_size() == 1) { s->print(cout); return; }
	string& action = *cmd[1];
	if (action == "print") s->print(cout);
	else if (action == "area") cout << s->area() << endl;
	else if (action == "perimeter") cout << s->perimeter() << endl;
	else { cout << "Unknown syntax" << endl; return; }
}

int get_index(const string& s) {
	if (s.empty() || s.back() != ']') throw exception();
	int pos = s.find('[');
	string num_str = s.substr(pos + 1, s.size() - pos - 2);
	return stoi(num_str);
}

void Interface::vector_call_command(const Vector<string>& cmd) {
	int n = -1;
	try
	{
		n = get_index(*cmd[0]);
		cmd[0] = new string(cmd[0]->substr(0, cmd[0]->find('[')));
		vector* v = vectors.at(*cmd[0]);
		if (cmd.get_size() == 1) {
			try{
				v->get(n)->print(cout); return;
			}
			catch (uninitialized_data_exception& e) {
				cout << "null shape" << endl; return;
			}
			catch (index_out_of_range_exception& e) {
				cout << "Index out of range: " << e.get_index() << endl; return;
			}
		}
		else if (*cmd[1] == "put") {
			if (cmd.get_size() == 2) { cout << "No shape provided" << endl; return; }
			else {
				string& shape_name = *cmd[2];
				shape* new_s;
				try {
					new_s = shapes.at(shape_name)->clone();
				}
				catch (out_of_range& e) { cout << "No shape provided" << endl; return; }
				try {
					v->put(n, new_s);
				}
				catch (index_out_of_range_exception& e) {
					cout << "Index out of range: " << e.get_index() << endl; return;
				}
			}
			return;

		}
		else if (*cmd[1] == "print") {
			try {
				v->get(n)->print(cout); return;
			}
			catch (uninitialized_data_exception& e) {
				cout << "null shape" << endl; return;
			}
			catch (index_out_of_range_exception& e) {
				cout << "Index out of range: " << e.get_index() << endl; return;
			}
		}
		else if (*cmd[1] == "area") {
			try {
				cout << v->get(n)->area() << endl; return;
			}
			catch (uninitialized_data_exception& e) {
				cout << "null shape" << endl; return;
			}
			catch (index_out_of_range_exception& e) {
				cout << "Index out of range: " << e.get_index() << endl; return;
			}
		}
		else if (*cmd[1] == "perimeter") {
			try {
				cout << v->get(n)->perimeter() << endl; return;
			}
			catch (uninitialized_data_exception& e) {
				cout << "null shape" << endl; return;
			}
			catch (index_out_of_range_exception& e) {
				cout << "Index out of range: " << e.get_index() << endl; return;
			}
		}
		else { cout << "Unknown syntax" << endl; return; }
	}
	catch (const std::exception&){}
	vector* v = vectors.at(*cmd[0]);
	if (cmd.get_size() == 1) { 
		v->output(cout); return; 
	}
	string& action = *cmd[1];
	if (action == "print") v->output(cout);
	else if (action == "save") {
		if (cmd.get_size() == 2) { cout << "No file provided" << endl; return; }
		else {
			string& filename = *cmd[2];
			v->save_to_file(filename.c_str());
		}
	}
	else if (action == "read") {
		if (cmd.get_size() == 2) { cout << "No file provided" << endl; return; }
		else {
			string& filename = *cmd[2];
			v->read_from_file(filename.c_str());
		}
	}
	else if (action == "push_back"){
		if (cmd.get_size() == 2) { cout << "No shape provided" << endl; return; }
		else {
			string& shape_name = *cmd[2];
			shape* new_s;
			try {
				new_s = shapes.at(shape_name)->clone();
			}
			catch (out_of_range& e) { cout << "No shape provided" << endl; return; }
			try {
				v->push_back(new_s);
			}
			catch (index_out_of_range_exception& e) {
				cout << "Index out of range: " << e.get_index() << endl; return;
			}
		}
		return;
	}
	else { cout << "Unknown syntax" << endl; return; }
}

void Interface::object_call_command(const Vector<string>& cmd) {
	string& name = *cmd[0];
	try {
		shape_call_command(cmd);
	}
	catch (out_of_range& e) {
		try {
			vector_call_command(cmd);
		}
		catch (out_of_range& e) { cout << "Unknown object: " << name << endl; return; }
	}
}



void Interface::end() {
	for (auto& pair : vectors) delete pair.second;
	for (auto& pair : shapes) delete pair.second;
}