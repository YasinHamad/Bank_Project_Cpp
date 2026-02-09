#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include "math.h"

using namespace std;

namespace printers
{
	enum enPosition { left, center, right };



	string PrintSpaces(int number) {
		string result = "";
		for (int i = 0; i < number; i++) result += " ";
		return result;
	}

	string PrintDashes(int number, string dashes = "-") {
		string result = "";
		for (int i = 0; i < number; i++) result += dashes;
		return result;
	}

	string FormatedCout(int number, string sentence, enPosition position) {
		int length = sentence.length();
		int padding_summation = length - number;

		string result = "";

		int left_padding = 0;
		int right_padding = 0;

		switch (position)
		{
		case(enPosition::center):
		{
			if ((math::IsEven(length) && math::IsEven(number)) || (!math::IsEven(length) && !math::IsEven(number))) {
				left_padding = right_padding = (number - length) / 2;
			}
			else {
				left_padding = (number - length) / 2;
				right_padding = (number - length) / 2;
				right_padding++;
			}

			result += PrintSpaces(left_padding);
			result += sentence;
			result += PrintSpaces(right_padding);
			break;
		}
		case(enPosition::left):
		{
			result += sentence;
			result += PrintSpaces(number - length);
			break;
		}
		default:
		{
			result += PrintSpaces(number - length);
			result += sentence;
			break;
		}
		}
		return result;
	}

	void PrintIntVectorElements(vector <int>& vector) {
		for (const int& element : vector) {
			cout << element << " ";
		}
		cout << endl;
	}

	void Print(string ms) {
		cout << ms << endl;
	}

	string PrintNameInMiddleOfDashes(int dashes_number, string name, string dashes = "-") {
		int length = name.length();
		string result = "";
		int left_padding = 0;
		int right_padding = 0;

		if ((math::IsEven(length) && math::IsEven(dashes_number)) || (!math::IsEven(length) && !math::IsEven(dashes_number))) {
			left_padding = right_padding = (dashes_number - length) / 2;
		}
		else {
			left_padding = (dashes_number - length) / 2;
			right_padding = (dashes_number - length) / 2;
			right_padding++;
		}

		result += printers::PrintDashes(left_padding, dashes);
		result += name;
		result += printers::PrintDashes(right_padding, dashes);

		return result;
	}

	void PrintTableBorder(vector<int>& _cell_widths, int padding)
	{
		string result = "";

		for (int& item : _cell_widths) {
			for (int j = 0; j < item + (padding * 2); j++) {
				result += "-";
			}
			result += "|";
		}

		cout << result << endl;
	}

	void PrintTableRow(vector<string>& row, vector<int>& widths, int padding, printers::enPosition _position) {
		int iterator = 0;
		for (string& item : row) {
			cout <<
				printers::FormatedCout(widths[iterator] + padding * 2, item, _position) <<
				"|";
			iterator++;
		}
		cout << endl;
	}

	void ConvertHeaderToCapital(vector<vector<string>>& _data) {
		for (string& item : _data[0]) {
			for (char& ch : item) {
				ch = toupper(ch);
			}
		}
	}

	void MakeTable(vector<vector<string>>& _data, printers::enPosition _position, bool line_btw) {
		int number_of_columns = _data[0].size();
		int number_of_rows = _data.size();
		int iterator = 0;
		int padding = 5;

		vector<int> num_of_spaces_for_each_column;

		// initialize the vector num_of_spaces_for_each_column
		for (int i = 0; i < number_of_columns; i++) num_of_spaces_for_each_column.push_back(0);

		for (vector<string>& vec : _data) {
			for (string& item : vec) {
				num_of_spaces_for_each_column[iterator] =
					(item.length() > num_of_spaces_for_each_column[iterator]) ? item.length() : num_of_spaces_for_each_column[iterator];
				iterator++;
			}
			iterator = 0;
		}

		PrintTableBorder(num_of_spaces_for_each_column, padding);

		ConvertHeaderToCapital(_data);

		iterator = 0;
		for (vector<string>& vec : _data) {
			PrintTableRow(vec, num_of_spaces_for_each_column, padding, _position);

			if (iterator == 0) PrintTableBorder(num_of_spaces_for_each_column, padding);

			if (line_btw && iterator != 0) PrintTableBorder(num_of_spaces_for_each_column, padding);

			iterator++;
		}

		if (!line_btw) PrintTableBorder(num_of_spaces_for_each_column, padding);
	}

	// this function prints an array
	void PrintArray(int* arr, int size, string message) {
		cout << message << endl;

		for (int i = 0; i < size; i++) {
			cout << *(arr + i) << " ";
		}
		cout << endl;
	}

	namespace two_dim_array
	{
		// this function prints two dim array(in heap) to the screen
		void PrintTwoDimArray(int** arr, int rows, int columns, int cell_width, enPosition position) {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					string cell_data = to_string(*(*(arr + i) + j));
					cout << FormatedCout(cell_width, cell_data, position) << "\t";
				}
				cout << endl;
			}
		}

		// this function is similar to the above function, but it prints zeros in the spaces
		// for example if you say the cell_width is 3, you gonna see 001 002 etc
		void PrintTwoDimArray(int** arr, int rows, int columns, int cell_width) {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					int cell_data = *(*(arr + i) + j);

					printf("%0*d ", cell_width, cell_data);

				}
				cout << endl;
			}
		}

	}

	namespace vector_utilities
	{
		void PrintVector(vector<int>& source) {
			for (const int& e : source) {
				printf("%d ", e);
			}
			cout << endl;
		}

		void PrintVectorOfChars(vector<char>& source) {
			for (const char& e : source) {
				printf("%c ", e);
			}
			cout << endl;
		}

		void PrintVectorOfStrings(vector<string>& source) {
			for (const string& s : source) {
				cout << s << "\n";
			}
			cout << endl;
		}
	}
	void PrintChar(char c, int times) {
		for (int i = 1; i <= times; i++) cout << c;
	}
}