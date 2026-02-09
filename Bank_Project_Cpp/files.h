#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include "math.h"
#include "printers.h"

using namespace std;

namespace files
{
	void PrintFileContent(string file_path) {
		fstream my_file;
		my_file.open(file_path, ios::in);

		if (my_file.is_open()) {
			string line = "";
			cout << printers::PrintNameInMiddleOfDashes(20, file_path) << endl;

			while (getline(my_file, line)) {
				cout << line << endl;
			}

			my_file.close();
			cout << printers::PrintDashes(20) << endl;
		}
	}

	void LoadDataFromFileToVector(string file_path, vector<string>& _vector) {
		fstream my_file;
		my_file.open(file_path, ios::in);

		if (my_file.is_open()) {
			string line = "";

			while (getline(my_file, line)) {
				_vector.push_back(line);
			}

			my_file.close();
		}
	}

	void SaveVectorToFile(const string file_path, vector<string>& _vector) {
		fstream my_file;
		my_file.open(file_path, ios::out);

		if (my_file.is_open()) {

			for (string& line : _vector) {
				if (!line.empty()) {
					my_file << line << endl;
				}
			}

			my_file.close();
		}
	}

	void DeleteRecordFromFile(const string file_path, string record) {
		vector<string> _vector;

		files::LoadDataFromFileToVector(file_path, _vector);

		for (string& line : _vector) {
			if (line == record) line = "";
		}

		files::SaveVectorToFile(file_path, _vector);
	}

	void UpdateRecordInFile(const string file_path, string record, string new_record) {
		vector<string> _vector;

		files::LoadDataFromFileToVector(file_path, _vector);

		for (string& line : _vector) {
			if (line == record) line = new_record;
		}

		files::SaveVectorToFile(file_path, _vector);
	}

}