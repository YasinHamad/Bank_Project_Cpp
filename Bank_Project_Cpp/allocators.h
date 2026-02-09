#pragma once

namespace allocators
{
	namespace two_dim_array
	{
		// this function allocate two dim array in the heap
		// you should use `DeleteTwoDimArray` after using this function
		int** AllocateTwoDirArray(int rows, int columns) {
			int** arr = new int* [rows];

			for (int i = 0; i < rows; i++) {
				*(arr + i) = new int[columns];
			}

			return arr;
		}

		// this function delete/free a two dim array from the heap
		void DeleteTwoDimArray(int** arr, int rows) {
			for (int i = 0; i < rows; i++) {
				delete[] * (arr + i);
			}

			delete[] arr;
		}
	}


}