#pragma once

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

namespace converters
{
	string ConvertAddressToString(void* address) {
		ostringstream oss;
		string address_st = "";

		oss << address;
		address_st += oss.str();
		oss.str("");
		oss.clear();

		return address_st;
	}
	string NumberToText(int number) {
		if (number >= 0 && number <= 19) {
			string numbers[] = {
				"",
				"One", "Two", "Three", "Four", "Five",
				"Six", "Seven", "Eight", "Nine", "Ten",
				"Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen",
				"Sixteen", "Seventeen", "Eighteen", "Nineteen"
			};
			return numbers[number];
		}

		else if (number >= 20 && number <= 99) {
			string numbers[] = {
				"", "", "Twenty", "Thirty", "Forty",
				"Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
			};
			return numbers[number / 10] + " " + NumberToText(number % 10);
		}

		else if (number <= 999) {
			if (number / 100 == 1) return NumberToText(number / 100) + " Hundred " + NumberToText(number % 100);
			return NumberToText(number / 100) + " Hundreds " + NumberToText(number % 100);
		}

		else if (number <= 999999) {
			if (number / 1000 == 1) return NumberToText(number / 1000) + " Thousand " + NumberToText(number % 1000);
			return NumberToText(number / 1000) + " Thousands " + NumberToText(number % 1000);
		}

		else if (number <= 999999999) {
			if (number / 1000000 == 1) return NumberToText(number / 1000000) + " Million " + NumberToText(number % 1000000);
			return NumberToText(number / 1000000) + " Millions " + NumberToText(number % 1000000);
		}

		else {
			if (number / 1000000000 == 1) return NumberToText(number / 1000000000) + " Billion " + NumberToText(number % 1000000000);
			return NumberToText(number / 1000000000) + " Billions " + NumberToText(number % 1000000000);
		}

		return "null";
	}
}