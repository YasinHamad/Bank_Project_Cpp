#pragma once

#include <iostream>
#include <string>
using namespace std;

namespace readers
{
	int ReadNumber(string message) {
		int Number;
		cout << message;
		cin >> Number;
		while (cin.fail()) {
			// user didn't input a number    
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid Number, Enter a valid one: ";
			cin >> Number;

		}
		return Number;
	}

	int ReadPositiveNumber(string message) {
		int Number = 0;
		cout << message;
		cin >> Number;
		while (cin.fail() || Number <= 0) {
			// user didn't input a number    
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid Number, Enter a valid one: ";
			cin >> Number;

		}
		return Number;
	}

	int ReadPositiveNumberInRange(string message, int from, int to) {
		int Number = 0;
		cout << message;
		cin >> Number;
		while (cin.fail() || Number < from || Number > to) {
			// user didn't input a number    
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << message;
			cin >> Number;

		}
		return Number;
	}

	double ReadPositiveDoubleNumber(string message) {
		double Number = 0.0;
		cout << message;
		cin >> Number;
		while (cin.fail() || Number <= 0.0) {
			// user didn't input a number    
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Invalid input ";
			cout << message;
			cin >> Number;

		}
		return Number;
	}

	string ReadAWord(string str) {
		string W;
		cout << str;
		cin >> W;
		return W;
	}

	string ReadASentence(string str) {
		string W;
		cout << str;
		getline(cin >> std::ws, W);
		return W;
	}
	float ReadNumInRange(string str, float from, float to) {
		float N;
		do {
			cout << str;
			cin >> N;
		} while (N < from || N > to);

		return N;
	}

	void ReadArrayElements(int arr[], int& size) {
		size = ReadPositiveNumber("Enter array size: ");

		for (int i = 0; i < size; i++) {
			arr[i] = ReadNumber("Element [" + to_string(i + 1) + "] : ");
		}
	}

	void ReadIntVectorElements(vector <int>& vector) {
		char check = 'y';
		int new_element = 0;

		while (check == 'y' || check == 'Y') {
			cout << "Enter the new element: ";
			cin >> new_element;

			vector.push_back(new_element);

			cout << "Do you want to add more elements [y/n]: ";
			cin >> check;
		}
	}

	char ReadChar(string message) {
		char c = 'x';
		cout << message;
		cin >> c;
		return c;
	}



}