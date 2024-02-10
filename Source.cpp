#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void printMatrix(bool**, int, int);

int countLights(bool**, int, int);

void invertRowAndColumn(bool**, int, int, int, int);

int main() {
	ifstream ifs;
	string filename;
	cout << "Enter filename : ";
	cin >> filename;
	ifs.open(filename);
	if (ifs.fail()) {
		cout << "Could not open " << filename;
		exit(1);
	}

	// Declare array
	int rowCount, columnCount;
	ifs >> rowCount >> columnCount;
	bool** A = new bool*[rowCount];
	for (int i = 0; i < rowCount; i++)
		A[i] = new bool[columnCount];

	// Initialize array
	for (int i = 0; i < rowCount; i++)
		for (int j = 0; j < columnCount; j++)
			ifs >> A[i][j];

	// Print original
	cout << "< Original matrix>" << endl;
	printMatrix(A, rowCount, columnCount);

	// Calculate which row and column to invert
	int inversionRow = 0, inversionColumn = 0, maxLightsOn = 0;

	int i, j, tempLightCount;
	for (i = 0; i < rowCount; i++) {
		for (j = 0; j < columnCount; j++) {
			invertRowAndColumn(A, rowCount, columnCount, i, j);

			tempLightCount = countLights(A, rowCount, columnCount);
			if (tempLightCount > maxLightsOn) {
				maxLightsOn = tempLightCount;
				inversionRow = i;
				inversionColumn = j;
			}

			invertRowAndColumn(A, rowCount, columnCount, i, j);
		}
	}

	// Print result
	cout << "\n< Result matrix>" << endl;
	invertRowAndColumn(A, rowCount, columnCount, inversionRow, inversionColumn);
	printMatrix(A, rowCount, columnCount);
	cout << "row : " << inversionRow << endl;
	cout << "column : " << inversionColumn << endl;
	cout << "number of lights : " << maxLightsOn;

	return 0;
}

void printMatrix(bool** arr, int rows, int columns) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			cout << arr[i][j] << " ";
		cout << endl;
	}
}

int countLights(bool** arr, int rows, int columns) {
	int lights = 0;
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (arr[i][j] == 1) lights++;

	return lights;
}

void invertRowAndColumn(bool** arr, int rows, int columns, int invRow, int invCol) {
	// Invert row
	for (int i = 0; i < columns; i++)
		arr[invRow][i] = !arr[invRow][i];

	// Invert column
	for (int i = 0; i < rows; i++)
		arr[i][invCol] = !arr[i][invCol];
}