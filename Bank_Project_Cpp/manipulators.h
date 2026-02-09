#pragma once

//#include <iostream>
#include <string>
#include <vector>

namespace manipulators
{
	namespace string_utilities
	{
		enum enLetterType { LowerLetter, CapitalLetter, All };

		vector<char> FirstLetterOfEachWord(string source) {
			vector<char> result;

			bool is_first_letter = true;

			for (int i = 0; i < source.length(); i++) {
				if (source[i] != ' ' && is_first_letter) result.push_back(source[i]);
				is_first_letter = source[i] == ' ' ? true : false;
			}

			return result;
		}

		void UpperFirstLetterOfEachWord(string& source) {
			bool is_first_letter = true;

			for (int i = 0; i < source.length(); i++) {
				if (source[i] != ' ' && is_first_letter) source[i] = toupper(source[i]);
				is_first_letter = source[i] == ' ' ? true : false;
			}
		}

		void LowerFirstLetterOfEachWord(string& source) {
			bool is_first_letter = true;

			for (int i = 0; i < source.length(); i++) {
				if (source[i] != ' ' && is_first_letter) source[i] = tolower(source[i]);
				is_first_letter = source[i] == ' ' ? true : false;
			}
		}

		string LowerString(string source) {
			for (int i = 0; i < source.length(); i++) {
				source[i] = tolower(source[i]);
			}
			return source;
		}

		string UpperString(string source) {
			for (int i = 0; i < source.length(); i++) {
				source[i] = toupper(source[i]);
			}
			return source;
		}

		void InvertChar(char& c) {
			if (isupper(c)) c = tolower(c);
			else c = toupper(c);
		}

		void InvertStringChars(string& source) {
			for (int i = 0; i < source.length(); i++) InvertChar(source[i]);
		}

		int CountCapitalLetters(string source) {
			int count = 0;
			for (int i = 0; i < source.length(); i++) if (isupper(source[i])) count++;
			return count;
		}

		int CountLowerLetters(string source) {
			int count = 0;
			for (int i = 0; i < source.length(); i++) if (islower(source[i])) count++;
			return count;
		}

		int CountLetters(string source, enLetterType letter_type = enLetterType::All) {

			if (letter_type == enLetterType::All) return source.length();

			int count = 0;

			if (enLetterType::CapitalLetter == letter_type) {
				for (int i = 0; i < source.length(); i++) if (isupper(source[i])) count++;
			}
			else {
				for (int i = 0; i < source.length(); i++) if (islower(source[i])) count++;
			}

			return count;
		}

		int CountLetterInString(string source, char c, bool match_case = true) {
			int counter = 0;
			if (match_case) { for (int i = 0; i < source.length(); i++) if (c == source[i]) counter++; }
			else { for (int i = 0; i < source.length(); i++) if (tolower(c) == tolower(source[i])) counter++; }

			return counter;
		}

		bool isVowel(char c) {
			c = tolower(c);
			return (c == 'a' || c == 'o' || c == 'u' || c == 'i' || c == 'e');
		}

		int CountVowels(string source) {
			int count = 0;
			for (int i = 0; i < source.length(); i++) {
				if (isVowel(source[i])) count++;
			}

			return count;
		}

		vector<char> GetVowels(string source) {
			vector<char> vowels;

			for (int i = 0; i < source.length(); i++) {
				if (isVowel(source[i])) vowels.push_back(source[i]);
			}

			return vowels;
		}

		vector<string> SplitString(string source, string split_str) {
			vector<string> strings;
			int pos = 0;
			string word = "";

			while ((pos = source.find(split_str)) != std::string::npos) {
				word = source.substr(0, pos);

				if (word != "") strings.push_back(word);

				source.erase(0, pos + split_str.length());
			}

			if (source != "") {
				strings.push_back(source);
			}
			return strings;
		}

		int CountWords(string source, string word_spliter) {
			int pos = 0;
			int counter = 0;

			while ((pos = source.find(word_spliter)) != std::string::npos) {
				if (pos != 0) counter++;
				source.erase(0, pos + word_spliter.length());
			}
			if (source.length() != 0) counter++;

			return counter;
		}

		// this is exactly similar to SplitString
		vector<string> Split(string source, string delimiter) {
			vector<string> strings;
			int pos = 0;
			string word;

			while ((pos = source.find(delimiter)) != std::string::npos) {
				word = source.substr(0, pos);
				if (word != "") {
					strings.push_back(word);
				}
				source.erase(0, pos + delimiter.length());
			}
			if (source.length() != 0) strings.push_back(source);

			return strings;
		}

		string TrimLeft(string source) {
			for (int i = 0; i < source.length(); i++) {
				if (source[i] != ' ') return source.substr(i, source.length() - i);
			}
			return "";
		}
		string TrimRight(string source) {
			for (int i = source.length() - 1; i >= 0; i--) {
				if (source[i] != ' ') {
					return source.substr(0, i + 1);
				}
			}
			return "";
		}

		string Trim(string source) {
			return TrimLeft(TrimRight(source));
		}

		string JoinString(vector<string> strings, string separator) {
			string result = "";

			if (strings.empty()) return result;

			result += strings.at(0);

			for (int i = 1; i < strings.size(); i++) {
				result += separator;
				result += strings.at(i);
			}

			return result;
		}

		// same as above
		// one with array, and the other with vector
		string JoinString(string* strings, int size, string separator) {
			string result = "";

			if (size == 0) return result;

			result += *strings;

			for (int i = 1; i < size; i++) {
				result += separator;
				result += *(strings + i);
			}

			return result;
		}

		// "yasin hamad" => "hamad yasin"
		string ReversStringWords(string source, string separator) {
			vector<string> strings = SplitString(source, separator);
			string result = "";

			vector<string>::iterator itor = strings.end();

			while (itor != strings.begin()) {
				itor--;
				result += *itor;
				result += separator;
			}

			return result.substr(0, result.length() - separator.length());
		}



		string ReplaceWordInStringWithBuiltInFunction(string source, string old_word, string new_word) {
			int pos = 0;

			pos = source.find(old_word);

			while (pos != std::string::npos) {
				source.replace(pos, old_word.length(), new_word);
				pos = source.find(old_word);
			}

			return source;
		}

		string ReplaceWordInString(string source, string old_word, string new_word, bool case_sensetive = true) {
			vector<string> strings = SplitString(source, " ");

			string old_word_small = LowerString(old_word);

			if (case_sensetive) {
				for (string& str : strings) {
					if (str == old_word) {
						str = new_word;
					}
				}
			}
			else {
				for (string& str : strings) {
					if (LowerString(str) == old_word_small) str = new_word;
				}
			}



			return JoinString(strings, " ");
		}

		string RemovePunctuations(string source) {
			string result = "";
			for (int i = 0; i < source.length(); i++) {
				if (!ispunct(source[i])) result += source[i];
			}

			return result;
		}
	}
}
