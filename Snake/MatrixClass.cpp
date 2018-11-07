#include "MatrixClass.h"

MatrixClass::MatrixClass() {}


int MatrixClass::getGreatest1DIndex() const {
	assert(height == 1);
	double test = 0;
	int result = 0;
	for (int i = 0; i < width; i++) {
		if (array[0][i] > test) {
			test = array[0][i];
			result = i;
		}
	}

	return result;
}


int MatrixClass::getStochasticOutput() const {
	assert(height == 1);

	vector<double> probabililties = getSoftmax();

	int result = 0;
	double randVal = rand()/(double)RAND_MAX;
	double sum = 0;
	for (int i = 0; i < width; i++) {
		sum += probabililties[i];
		if (sum < randVal) result++;
	}
	return result;
}

void MatrixClass::isolateNode(int node) {
	assert(height == 1);
	for (int i = 0; i < width; i++) {
		if (i != node) array[0][i] = 0;
		else array[0][i] = 1;
	}
}


MatrixClass::MatrixClass(int inHeight, int inWidth) {
	height = inHeight;
	width = inWidth;
	array = vector< vector<double> >(height, vector<double>(width));
}


vector<double> MatrixClass::getSoftmax() const {
	assert(height == 1);
	vector<double> result(width);
	
	double sum = 0;
	double maxNum = 0;
	int maxIdx = 0;
	for (int i = 0; i < width; i++) {
		if (array[0][i] > maxNum) {
			maxNum = array[0][i];
			maxIdx = i;
		}
		sum += array[0][i];
	}
	
	double expSum = 0;
	for (int i = 0; i < width; i++) {
		double val = array[0][i];
		result[i] = exp(val - maxNum);
		expSum += result[i];
	}

	for (int i = 0; i < width; i++) {
		result[i] /= expSum;
	}
	
	return result;
}


void MatrixClass::clear() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			array[i][j] = 0;
		}
	}
}

MatrixClass::MatrixClass(vector< vector<double> > const &inArray) {
	assert(inArray.size() != 0);
	height = inArray.size();
	width = inArray[0].size();
	array = inArray;
}


MatrixClass MatrixClass::times(double const &value) {
	MatrixClass result(height, width);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			result.array[i][j] = array[i][j] * value;
		}
	}

	return result;
}


MatrixClass MatrixClass::operator*(double const value) {
	return this->times(value);
}


MatrixClass MatrixClass::plus(MatrixClass const &m) const {
	assert(height == m.height && width == m.width);
	MatrixClass result(height, width);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			result.array[i][j] = array[i][j] + m.array[i][j];
		}
	}

	return result;
}


MatrixClass MatrixClass::operator+(MatrixClass const &m) const {
	return this->plus(m);
}


MatrixClass MatrixClass::minus(MatrixClass const &m) const {
	assert(height == m.height && width == m.width);
	MatrixClass result(height, width);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			result.array[i][j] = array[i][j] - m.array[i][j];
		}
	}

	return result;
}


MatrixClass MatrixClass::operator-(MatrixClass const &m) const {
	return this->minus(m);
}


MatrixClass MatrixClass::times(MatrixClass const &m) const {
	assert(height == m.height && width == m.width);
	MatrixClass result(height, width);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			result.array[i][j] = array[i][j] * m.array[i][j];
		}
	}
	return result;
}


MatrixClass MatrixClass::operator*(MatrixClass const &m) const {
	return this->times(m);
}


MatrixClass MatrixClass::dot(MatrixClass const &m) const {
	assert(width == m.height);
	MatrixClass result(height, m.width);
	double w = 0;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < m.width; j++) {
			for (int h = 0; h < width; h++) {
				w += array[i][h] * m.array[h][j];
			}
			result.array[i][j] = w;
			w = 0;
		}
	}

	return result;
}


MatrixClass MatrixClass::transpose() const { // ij element becomes ji element
	MatrixClass result(width, height);

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			result.array[i][j] = array[j][i];
		}
	}
	return result;
}


MatrixClass MatrixClass::applyFunction(double(*function)(double)) const {
	MatrixClass result(height, width);

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			result.array[i][j] = (*function)(array[i][j]);
		}
	}

	return result;
}


void MatrixClass::print(std::ostream &flux) const { // pretty print, taking into account the space between each element of the matrix
	unsigned int *maxLength;
	maxLength = new unsigned int[width];
	std::stringstream ss;

	for (int i = 0; i < width; i++) {
		maxLength[i] = 0;
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			ss << array[i][j];
			if (maxLength[j] < ss.str().size()) {
				maxLength[j] = ss.str().size();
			}
			ss.str(std::string());
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			flux << array[i][j];
			ss << array[i][j];
			for (unsigned int k = 0; k < maxLength[j] - ss.str().size() + 1; k++) {
				flux << " ";
			}
			ss.str(std::string());
		}
		flux << std::endl;
	}

	delete maxLength;
}


std::ostream& operator<<(std::ostream &flux, MatrixClass const &m) {
	m.print(flux);
	return flux;
}
