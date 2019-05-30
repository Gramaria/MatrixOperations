
#include <iostream>
#include <vector>
#include <exception>
#include <fstream>
#include <stdexcept>
using namespace std;

class Matrix {
public:
	Matrix() {
		rows = 0;
		cols = 0;
	}

	Matrix(int new_rows, int new_cols) {
			if (new_rows < 0 || new_cols < 0) {
				throw out_of_range("Out_of_range");
			}
			if (new_rows == 0 || new_cols == 0) {
				new_rows = new_cols = 0;
			}
			rows = new_rows;
			cols = new_cols;
			matrix.resize(rows);
			for (int i = 0; i < rows; i++) {
				matrix[i].resize(cols);
				for (int j = 0; j < cols; j++) {
					matrix[i][j] = 0;
				}
			}
	}

	void Reset(int new_rows, int new_cols) {
		if (new_rows < 0 || new_cols < 0) {
			throw out_of_range("Out_of_range");
		}
		rows = new_rows;
		cols = new_cols;
		matrix.resize(rows);
		for(int i = 0; i < rows; i++){
			matrix[i].assign(cols, 0);
		}
	}

	int At(int row, int col) const {
		if (row < 0 || row >= rows || col < 0 || col >= cols) {
			throw out_of_range("Out_of_range");
		}
		return matrix[row][col];
	}

	int& At(int row, int col) {
		if (row < 0 || row >= rows || col < 0 || col >= cols) {
			throw out_of_range("Out_of_range");
		}
		return matrix[row][col];
	}

	int GetNumRows() const{
		return rows;
	}

	int GetNumColumns() const{
		return cols;
	}

private:
	int rows;
	int cols;
	vector<vector<int>> matrix;
};

istream& operator >>(istream& stream, Matrix& m) {
	int new_rows, new_cols;
	stream >> new_rows >> new_cols;
	m = Matrix(new_rows, new_cols);
	for (int i = 0; i < new_rows; i++) {
		for (int j = 0; j < new_cols; j++) {
			stream >> m.At(i, j);
		}
	}
	return stream;
}

ostream& operator <<(ostream& stream, const Matrix& m) {
	stream << m.GetNumRows() << " " << m.GetNumColumns() << endl;
	for (int i = 0; i < m.GetNumRows(); i++) {
		for (int j = 0; j < m.GetNumColumns(); j++) {
			stream << m.At(i, j) << " ";
		}
		stream << endl;
	}
	return stream;
}

bool operator ==(const Matrix& lhs, const Matrix& rhs) {
	if (lhs.GetNumRows() == rhs.GetNumRows() && lhs.GetNumColumns() == rhs.GetNumColumns()) {
		bool ind = true;
		for (int i = 0; i < lhs.GetNumRows(); i++) {
			for (int j = 0; j < lhs.GetNumColumns(); j++) {
				ind = ind && (rhs.At(i, j) == lhs.At(i, j));
				cout << (rhs.At(i, j) == lhs.At(i, j)) << " ";
			}
		}
		return ind;
	} else {
		return false;
	}
}

Matrix operator +(const Matrix& lhs, const Matrix& rhs) {
	int rows = lhs.GetNumRows();
	int cols = lhs.GetNumColumns();
	if (rows != rhs.GetNumRows() || cols != rhs.GetNumColumns()) {
		throw invalid_argument("Invalid_argument");
	}
	Matrix res(rows, cols);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			res.At(i, j) = lhs.At(i, j) + rhs.At(i, j);
		}
	}
	return res;
}

int main() {
	Matrix one;
	Matrix two;
	try {
		cin >> one >> two;
		cout << (one == two);
	} catch(out_of_range& e) {
		cout << e.what();
		return 0;
	} catch(invalid_argument& e){
		cout << e.what();
		return 0;
	}
	return 0;
}
