#include <iostream>
#include <iomanip>
#include <time.h>

using namespace std;

void Print(int** a, const int rowCount, const int colCount, int i, int j)
{
	cout << setw(4) << a[i][j];
	if (j < colCount - 1)
		Print(a, rowCount, colCount, i, j + 1);
	else
		if (i < rowCount - 1)
		{
			cout << endl;
			Print(a, rowCount, colCount, i + 1, 0);
		}
		else
			cout << endl << endl;
}

void Input(int** a, const int rowCount, const int colCount, int i, int j)
{
	cout << "a[" << i << "][" << j << "] = ";
	cin >> a[i][j];
	if (j < colCount - 1)
		Input(a, rowCount, colCount, i, j + 1);
	else
		if (i < rowCount - 1)
		{
			cout << endl;
			Input(a, rowCount, colCount, i + 1, 0);
		}
		else
			cout << endl;
}

void Create(int** a, const int rowCount, const int colCount,
	const int Low, const int High, int i, int j)
{
	a[i][j] = Low + rand() % (High - Low + 1);
	if (j < colCount - 1)
		Create(a, rowCount, colCount, Low, High, i, j + 1);
	else
		if (i < rowCount - 1)
			Create(a, rowCount, colCount, Low, High, i + 1, 0);
}

bool Part1_Count(int** a, const int rowCount, const int colCount, int& count, int i = 0, int j = 0)
{
	if (j >= colCount)
		return count > 0;

	if (i < rowCount) {
		if (a[i][j] == 0) {
			count--;
			return true;
		}
		return Part1_Count(a, rowCount, colCount, count, i + 1, j);
	}
	else {
		return Part1_Count(a, rowCount, colCount, count, 0, j + 1);
	}
}

int rowCharacteristic(int* row, int cols, int i = 0, int sum = 0) {
	if (i >= cols) // Base case: if index reaches cols, return the sum.
		return sum;

	if (row[i] > 0 && row[i] % 2 == 0) {
		sum += row[i];
	}
	return rowCharacteristic(row, cols, i + 1, sum); // Move to the next element.
}

void swapRows(int** a, int row1, int row2, int colCount, int col = 0) {
	if (col >= colCount)
		return;
	int temp = a[row1][col];
	a[row1][col] = a[row2][col];
	a[row2][col] = temp;
	swapRows(a, row1, row2, colCount, col + 1);
}

void Part2_sortRowsByCharacteristic(int** a, const int rowCount, const int colCount, int i = 0, int j = 0)
{
	if (i >= rowCount - 1)
		return;

	if (j < rowCount - i - 1) {
		if (rowCharacteristic(a[j], colCount) > rowCharacteristic(a[j + 1], colCount)) {
			swapRows(a, j, j + 1, colCount);
		}
		Part2_sortRowsByCharacteristic(a, rowCount, colCount, i, j + 1);
	}
	else {
		Part2_sortRowsByCharacteristic(a, rowCount, colCount, i + 1, 0);
	}
}


int main()
{
	srand((unsigned)time(NULL));
	int Low = -7;
	int High = 7;
	int rowCount, colCount;
	cout << "rowCount = "; cin >> rowCount;
	cout << "colCount = "; cin >> colCount;
	int** a = new int* [rowCount];
	for (int i = 0; i < rowCount; i++)
		a[i] = new int[colCount];

	Create(a, rowCount, colCount, Low, High, 0, 0);
	//Input(a, rowCount, colCount, 0, 0);
	Print(a, rowCount, colCount, 0, 0);
	int count = colCount;
	if (Part1_Count(a, rowCount, colCount, count, 0, 0))
		cout << "count = " << count << endl;
	else
		cout << "there are no zero elements" << endl;
	cout << endl;

	Part2_sortRowsByCharacteristic(a, rowCount, colCount, 0, 0);
	Print(a, rowCount, colCount, 0, 0);

	for (int i = 0; i < rowCount; i++)
		delete[] a[i];
	delete[] a;
}
