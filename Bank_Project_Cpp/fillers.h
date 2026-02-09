#pragma once

#include "generators.h"

namespace fillers
{
	namespace two_dim_array
	{
		// this function fills two dim array(in heap) with random numbers
		void FillTwoDimArrayWithRandomNumbers(int** arr, int rows, int columns, int from, int to) {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					*(*(arr + i) + j) = generators::RandomNumber(from, to);
				}
			}
		}

		// this fills two dim array(in heap) with orderd number
		void FillTwoDimArrayWithOrderdNumbers(int** arr, int rows, int columns) {
			int counter = 1;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					*(*(arr + i) + j) = counter++;
				}
			}
		}

		// the diagonal will be 1, and other cells will be 0
		void FillIdentityMatrix(int** matrix, int rows, int columns) {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					if (i == j) *(*(matrix + i) + j) = 1;
					else *(*(matrix + i) + j) = 0;
				}
			}
		}

		// every thing is 0
		// you decide the diagonal equals to what
		void FillScalarMatrix(int** matrix, int rows, int columns, int diagonal) {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					if (i == j) *(*(matrix + i) + j) = diagonal;
					else *(*(matrix + i) + j) = 0;
				}
			}
		}

		// after calling this function, each row in the matrix will be palidrom
		void FillPalindromMatrix(int** matrix, int rows, int columns, int random_numbers_start, int random_numbers_end) {
			int temp = 0;
			for (int i = 0; i < rows; i++) {
				for (int s = 0, e = columns - 1; s <= e; s++, e--) {
					temp = generators::RandomNumber(random_numbers_start, random_numbers_end);
					*(*(matrix + i) + s) = *(*(matrix + i) + e) = temp;
				}
			}
		}
	}
}