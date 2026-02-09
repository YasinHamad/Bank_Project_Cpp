#pragma once

#include <iostream>
#include <string>
using namespace std;

#include "allocators.h"

namespace math
{
	bool IsEven(int number) {
		return (number % 2) == 0;
	}

	bool IsArrayPalindrom(int* source, int size) {
		if (size == 0) return false;

		for (int s = 0, e = size - 1; s < e; s++, e--) {
			if (*(source + s) != *(source + e)) return false;
		}
		return true;
	}

	// returns an array containing specified number of cells of the Febonacci series
	// you should delete the array in main
	int* CalculateFibonacciLoop(int size) {
		if (size == 0) return NULL;

		int* result = new int[size];
		*result = *(result + 1) = 1;

		for (int previous_01 = 1, previous_02 = 0, current = 2; current < size; current++, previous_01++, previous_02++) {
			*(result + current) = *(result + previous_01) + *(result + previous_02);
		}

		return result;
	}

	void CalculateFibonacciRecHelper(int size, int prev01, int prev02, int* cell) {
		if (size == 0) return;
		*cell = prev01 + prev02;
		CalculateFibonacciRecHelper(size - 1, prev02, *cell, cell + 1);
	}

	int* CalculateFibonacciRec(int size) {
		int* result = new int[size];
		CalculateFibonacciRecHelper(size, 1, 0, result);
		return result;
	}

	namespace two_dim_array
	{
		enum enMatrixSum
		{
			rows, columns
		};

		// Goal: sum the ints in some row in a two dim array
		// Inputs: 
		//    - the two dim array in heap
		//    - number of row you want to add
		//    - number of columns in the array	
		// Outputs: the summation
		int SumRows(int** source, int row_number, int columns) {
			int sum = 0;

			for (int j = 0; j < columns; j++) {
				sum += *(*(source + row_number) + j);
			}

			return sum;
		}

		// Goal: sum the ints in some column in a two dim array
		// Inputs: 
		//    - the two dim array in heap
		//    - number of rows in the array
		//    - number of column you want to add	
		// Outputs: the summation
		int SumColumns(int** source, int rows, int column_number) {
			int sum = 0;

			for (int i = 0; i < rows; i++) {
				sum += *(*(source + i) + column_number);
			}

			return sum;
		}

		// Goal: some rows or columns of a two dim array
		// Inputs: 
		//    - the two dim array in heap
		//    - number of rows in the array
		//    - number of columns in the array
		//    - direction: horizontally or vertically
		//    - pointer to an array of ints, to put the results in, you should free it in the main
		//    - int variable to put in the size of the resultant array
		// Outputs: nothing, we fill the resultant array `result` and the size of it `result_size`
		void SumMatrix(int** source, int rows, int columns, enMatrixSum directoin, int*& result, int& result_size) {
			if (enMatrixSum::rows == directoin) {
				result = new int[rows];
				result_size = rows;

				for (int i = 0; i < rows; i++) {
					*(result + i) = SumRows(source, i, columns);
				}
			}
			else {
				result = new int[columns];
				result_size = columns;

				for (int i = 0; i < columns; i++) {
					*(result + i) = SumColumns(source, rows, i);
				}
			}
		}

		// this function transforms rows to columns
		// it returns a new array located in heap, you should delete it in the main
		int** TransposedMatrix(int** source, int rows, int columns) {
			if (rows == 0 || columns == 0) return NULL;
			int** result;

			result = allocators::two_dim_array::AllocateTwoDirArray(columns, rows);

			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					*(*(result + j) + i) = *(*(source + i) + j);
				}
			}

			return result;
		}

		// this function multiplies two matrices
		// it returns the resultant array allocated in heap, you should delete it later
		int** MuliplyTwoMatrices(int** matrix_01, int rows, int columns, int** matrix_02) {
			int** result = NULL;

			result = allocators::two_dim_array::AllocateTwoDirArray(rows, columns);

			for (short i = 0; i < rows; i++) {
				for (short j = 0; j < columns; j++) {
					*(*(result + i) + j) = (*(*(matrix_01 + i) + j)) * (*(*(matrix_02 + i) + j));
				}
			}

			return result;
		}

		// this function returns a specific column in a matrix
		int* GetColumn(int** matrix, int rows, int columns, int column_number) {
			if (column_number > columns) return NULL;

			int* result = NULL;
			result = new int[rows];

			for (int i = 0; i < rows; i++) {
				*(result + i) = *(*(matrix + i) + column_number);
			}

			return result;
		}

		// this function returns a specific row in a matrix
		int* GetRow(int** matrix, int rows, int columns, int row_number) {
			if (row_number > rows) return NULL;

			int* result = NULL;
			result = new int[columns];

			for (int i = 0; i < columns; i++) {
				*(result + i) = *(*(matrix + row_number) + i);
			}

			return result;
		}

		// returs the summation of a matrix cells
		int SumMatrix(int** matrix, int rows, int columns) {
			int result = 0;

			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					result += *(*(matrix + i) + j);
				}
			}

			return result;
		}

		// this function returns weither the summation of two matrices are equal or not
		bool EqualMatrices(int** matrix_01, int** matrix_02, int rows, int columns) {
			return (SumMatrix(matrix_01, rows, columns) == SumMatrix(matrix_02, rows, columns));
		}

		// this fuctions checks if the two matrices are typically equal
		bool MatricesTypicallyEqual(int** matrix_01, int** matrix_02, int rows, int columns) {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					if ((*(*(matrix_01 + i) + j)) != (*(*(matrix_02 + i) + j))) return false;
				}
			}
			return true;
		}

		// does the diagonal cells all equal to 1. Does other cells equal to 0
		bool IsMatrixIdentity(int** matrix, int rows, int columns) {
			int temp = 0;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					temp = *(*(matrix + i) + j);
					if (i == j && temp != 1) return false;
					else if (i != j && temp != 0) return false;
				}
			}
			return true;
		}

		// does the diagonal cells all equal to some_number. Does other cells equal to 0
		bool IsMatrixScalar(int** matrix, int rows, int columns) {
			int temp = 0;
			int diagonal = *(*matrix);

			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {

					temp = *(*(matrix + i) + j);

					if (i == j && temp != diagonal) return false;
					else if (i != j && temp != 0) return false;
				}
			}
			return true;
		}

		// count the occuranse of specific number in matrix
		int CountNumberInMatrix(int** matrix, int rows, int columns, int number) {
			int counter = 0;

			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					if ((*(*(matrix + i) + j)) == number) counter++;
				}
			}

			return counter;
		}

		// Is the number of cells containing zeros the biggest number in the matrix
		// does the majority of cells contain zero
		bool IsSparceMatrix(int** matrix, int rows, int columns) {
			int zeros = math::two_dim_array::CountNumberInMatrix(matrix, rows, columns, 0);
			int cells = rows * columns - zeros;

			return (zeros > cells);
		}

		bool DoesNumberExistInMatrix(int** matrix, int rows, int columns, int number) {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					if ((*(*(matrix + i) + j)) == number) return true;
				}
			}
			return false;
		}

		// returns the numbers occurs in the two matrix
		vector<int> IntersectedNumbers(int** matrix_01, int rows_01, int columns_01, int** matrix_02, int rows_02, int columns_02) {
			vector<int> result;
			int temp = 0;

			for (int i = 0; i < rows_01; i++) {
				for (int j = 0; j < columns_01; j++) {
					temp = *(*(matrix_01 + i) + j);
					if (math::two_dim_array::DoesNumberExistInMatrix(matrix_02, rows_02, columns_02, temp))
						result.push_back(temp);
				}
			}
			return result;
		}

		int MinNumberInMatrix(int** matrix, int rows, int columns) {
			int number = *(*matrix);
			int temp = *(*matrix);
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					temp = *(*(matrix + i) + j);
					number = temp > number ? number : temp;
				}
			}
			return number;
		}
		int MaxNumberInMatrix(int** matrix, int rows, int columns) {
			int number = 0;
			int temp = 0;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					temp = *(*(matrix + i) + j);
					number = temp < number ? number : temp;
				}
			}
			return number;
		}

		// is each row in the matrix palindrom
		bool IsMatrixPalindrom(int** matrix, int rows, int columns) {
			for (int i = 0; i < rows; i++) {
				if (!IsArrayPalindrom(*(matrix + i), columns)) return false;
			}
			return true;
		}


	}
}