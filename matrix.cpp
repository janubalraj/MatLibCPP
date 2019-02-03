#include <matrix.h>
#include <utility>
#include <iostream>
template <typename T>
void matrix<T>::print() {
	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			std::cout << __array[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}


//CONSTRUCTORS
//----------------------------------//
template <typename T>
matrix<T>::matrix() {
	this->size_x = 0;
	this->size_y = 0;
	this->__mod  = 0;
}
template <typename T>
matrix<T>::matrix(const int& n, const T& m) : size_x(n), size_y(m), __mod(0) {
	__array.resize(n);
	for (int i = 0; i < n; i++) {
		__array[i].resize(m);
	}
}
template <typename T>
matrix<T>::matrix(const int& n, const int& m, const T& val) : size_x(n), size_y(m), __mod(0) {
	__array.resize(n);
	for (int i = 0; i < n; i++) {
		__array[i].resize(m,val);
	}
}
//---------------------------------//

	//DESTURCTOR
//------------------//
template <typename T>
matrix<T>:: ~matrix() {}
//-----------------//


	//OPERATOR OVERLOADING
//---------------------------//
//OPERATOR ()
template<typename T>
inline T& matrix<T>::operator ()(const int& i, const int& j) {
	return  this->__array[i][j];
}

//OPERATOR *
template<typename T>
template<typename F>
decltype(auto) matrix<T>::operator * (matrix<F>& other) {
	if (this->size_y != other.dim().first) {
		throw "Dimensions are not valid";
	}
	else {
		int p = this->size_x, q = this->size_y, r = other.dim().second;
		matrix<decltype(this->__array[0][0] * other(0, 0))> temp(p, r);
		if(__mod==0){
			for (int i = 0; i < p; i++) {
				for (int j = 0; j < r; j++) {
					for (int k = 0; k < q; k++) {
						temp(i, j) += this->__array[i][k] * other(k, j);
					}
				}
			}
		}
		else{
			for (int i = 0; i < p; i++) {
				for (int j = 0; j < r; j++) {
					for (int k = 0; k < q; k++) {
						temp(i, j) += ( ( (this->__array[i][k] + __mod) % __mod ) *
									  ( ( (other(k, j)+__mod) + __mod) % __mod) ) % __mod;						
						temp(i,j)  %= __mod;
					}
				}
			}
		}
		return temp;
	}
}
//OPERATOR * for consts
template<typename T>
template<typename F>
decltype(auto) matrix<T>::operator * (const F& val) {
	int p = this->size_x, q = this->size_y;
	matrix<decltype(__array[0][0] * val)> temp(p, q);
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < q; j++) {
			temp(i, j) = this->__array[i][j] * val;
		}
	}
	return temp;
}
//OPERATOR / for consts
template<typename T>
template<typename F>
decltype(auto) matrix<T>::operator / (const F& val) {
	if (val == 0) {
		std::cerr << "In File " << __FILE__ << "\nDivision by zero in / operation in Line " << __LINE__ << std::endl;
		throw val;
	}
	int p = this->size_x, q = this->size_y;
	matrix<decltype(__array[0][0] / val)> temp(p, q);
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < q; j++) {
			temp(i, j) = this->__array[i][j] / val;
		}
	}
	return temp;
}
//OPERATOR +
template<typename T>
template<typename F>
decltype(auto) matrix<T>::operator + (matrix<F>& other) {
	if (this->size_x != other.dim().first && this->size_y != other.dim().second) {
		throw "Dimensions are not valid";
	}
	else {
		int p = this->size_x, q = this->size_y;
		matrix<decltype(this->__array[0][0] + other(0, 0))> temp(p, q);
		for (int i = 0; i < p; i++) {
			for (int j = 0; j < q; j++) {
				temp(i, j) = this->__array[i][j] + other(i, j);
			}
		}
		return temp;
	}
}
//OPERATOR -
template<typename T>
template<typename F>
decltype(auto) matrix<T>::operator - (matrix<F>& other) {
	if (this->size_x != other.dim().first && this->size_y != other.dim().second) {
		throw "Dimensions are not valid";
	}
	else {
		int p = this->size_x, q = this->size_y;
		matrix<decltype(this->__array[0][0] - other(0, 0))> temp(p, q);
		for (int i = 0; i < p; i++) {
			for (int j = 0; j < q; j++) {
				temp(i, j) = this->__array[i][j] - other(i, j);
			}
		}
		return temp;
	}
}
//OPERATOR %
template<typename T>
template<typename F>
matrix<T> matrix<T>::operator % (const F& val) {
	if (val == 0) {
		std::cerr << "In File " << __FILE__ << "\nDivision by zero in % operation in Line " << __LINE__ << std::endl;
		throw val;
	}
	int p = this->size_x, q = this->size_y;
	matrix<T> temp(p, q);
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < q; j++) {
			temp(i, j) = this->__array[i][j] % val;
		}
	}
	return temp;
}


//OPERATOR *=
template<typename T>
template<typename F>
void matrix<T>::operator *= (matrix<F>& other) {
	if (this->size_y != other.dim().first) {
		throw "Dimensions are not valid";
	}
	else {
		int p = this->size_x, q = this->size_y, r = other.dim().second;
		matrix<T> temp(p, r);
		if(__mod==0){
			for (int i = 0; i < p; i++) {
				for (int j = 0; j < r; j++) {
					for (int k = 0; k < q; k++) {
						temp(i, j) += this->__array[i][k] * other(k, j);
					}
				}
			}
		}
		else{
			for (int i = 0; i < p; i++) {
				for (int j = 0; j < r; j++) {
					for (int k = 0; k < q; k++) {
						temp(i, j) += ( ( (this->__array[i][k] + __mod) % __mod ) *
									  ( ( (other(k, j)+__mod) + __mod) % __mod) ) % __mod;
						temp(i,j)  %= __mod;
					}
				}
			}
		}
		*this=temp;
	}
}
//OPERATOR *= for constsṭ
template<typename T>
template<typename F>
void matrix<T>::operator *= (const F& val) {
	for (int i = 0; i < this->size_x; i++) {
		for (int j = 0; j < this->size_y; j++)
		{
			this->__array[i][j] *= val;
		}
	}
}
//OPERATOR *= for consts
template<typename T>
template<typename F>
void matrix<T>::operator /= (const F& val) {
	if (val == 0) {
		std::cerr << "In File " << __FILE__ << "\nDivision by zero in /= operation in Line " << __LINE__ << std::endl;
		throw val;
	}
	for (int i = 0; i < this->size_x; i++) {
		for (int j = 0; j < this->size_y; j++)
		{
			this->__array[i][j] /= val;
		}
	}
}
//OPERATOR +=
template<typename T>
template<typename F>
void matrix<T>::operator += (matrix<F>& other) {
	if (this->size_x != other.dim().first && this->size_y != other.dim().second) {
		throw "Dimensions are not valid";
	}
	else {
		int p = this->size_x, q = this->size_y;
		for (int i = 0; i < p; i++) {
			for (int j = 0; j < q; j++) {
				this->__array[i][j] += other(i, j);
			}
		}
	}
}
//OPERATOR -=
template<typename T>
template<typename F>
void matrix<T>::operator -= (matrix<F>& other) {
	if (this->size_x != other.dim().first && this->size_y != other.dim().second) {
		throw "Dimensions are not valid";
	}
	else {
		int p = this->size_x, q = this->size_y;
		for (int i = 0; i < p; i++) {
			for (int j = 0; j < q; j++) {
				this->__array[i][j] -= other(i, j);
			}
		}
	}
}
//OPERATOR %=
template<typename T>
template<typename F>
void matrix<T>::operator %= (const F& val) {
	if (val == 0) {
		std::cerr << "In File " << __FILE__ << "\nDivision by zero in %= operation in Line " << __LINE__ << std::endl;
		throw val;
	}
	for (int i = 0; i < this->size_x; i++) {
		for (int j = 0; j < this->size_y; j++)
		{
			this->__array[i][j] %= val;
		}
	}
}
//--------------------------//


	//OTHER FUNCTIONS//
//--------------------------//

//FUNCTION FOR GETTING DIMENSIONS
template<typename T>
const std::pair<int, int> matrix<T>::dim() {
	return std::make_pair(size_x, size_y);
	//
}
//EXPONENTIATION WITH OR WITHOUT MODULO
template<typename T>
template<typename F>
matrix<T> matrix<T>::exp(F n, long long int MOD) {
	if (MOD == 0) throw "Division by zero";
	else if (MOD!=-1) this->__mod=MOD;
	matrix<T> ans(this->size_x, this->size_y);
	matrix<T> temp = *this;
	for (int i = 0; i < this->size_x; i++) {
		ans(i, i) = 1LL;
	}
	while (n) {
		if (n & 1) ans *= temp;
		temp *= temp;
		n>>=1LL;
	}
	this->__mod=0;
	return ans;
}