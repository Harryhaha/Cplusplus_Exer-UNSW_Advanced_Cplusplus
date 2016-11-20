#include <iostream>
#include <vector>
#include <list>

#include "EuclideanVector.h"

namespace evec {
    /***************** Six constructors *****************/
    // Second Constructor:
    EuclideanVector::EuclideanVector(unsigned int dim, double mag):
            magnitudes(new std::vector<double>(dim, mag)){ };

    // First Constructor:
    EuclideanVector::EuclideanVector(unsigned int dim):
            EuclideanVector(dim, 0.0) { };

    // Third Constructor:
    template <typename T> EuclideanVector::EuclideanVector(T iter_start, T iter_end):
            magnitudes(new std::vector<double>(iter_start, iter_end)) { };

    // Fourth Constructor:
    EuclideanVector::EuclideanVector(std::initializer_list<double> list):
            magnitudes(new std::vector<double>(list)) { };

    // Fifth Constructor / copy constructor:
    EuclideanVector::EuclideanVector(const EuclideanVector &e):
            magnitudes(new std::vector<double>(*e.magnitudes)) { }

    // Sixth Constructor / move constructor   // change
    EuclideanVector::EuclideanVector(EuclideanVector &&e) noexcept:
        magnitudes(e.magnitudes) {
        e.magnitudes = nullptr;
    }
    /***************** Six constructors *****************/


    /***************** Destructor *****************/
    EuclideanVector::~EuclideanVector() {
//        magnitudes->clear();
        delete magnitudes;
    }
    /***************** Destructor *****************/



    /******************** Member Method Definition ********************/
    // Copy Assignment:
    EuclideanVector& EuclideanVector::operator=(const EuclideanVector &e) {
        auto new_magnitudes = new std::vector<double>(*e.magnitudes);
        delete magnitudes;
        magnitudes = new_magnitudes;
//        dimension = e.dimension;
        return *this;
    }
    // Move Assignment:
    EuclideanVector& EuclideanVector::operator=(EuclideanVector &&e) noexcept {
        if(this != &e){
            delete magnitudes;  // Do I need to delete it here or let it done by destructor
//            dimension = e.dimension;
            magnitudes = e.magnitudes;
            e.magnitudes = nullptr;
        }
        return *this;
    }
    // Returns an unsigned int containing the number of dimensions in a particular vector
    unsigned int EuclideanVector::getNumDimensions() const {
        return magnitudes->size();
    }
    // Returns a double, the value of the magnitude in the dimension given as the function parameter
    double EuclideanVector::get(unsigned int dim) const {
        return (*magnitudes)[dim];
    }
    // Returns the Euclidean norm of the vector as a double
    double EuclideanVector::getEuclideanNorm() {
        if( euclideanNorm == -1.0){
            double euclideanNorm_tmp = 0.0;
            for(auto iter=magnitudes->begin(); iter != magnitudes->end(); iter++){
                euclideanNorm_tmp += pow(*iter, 2);
            }
            euclideanNorm_tmp = sqrt(euclideanNorm_tmp);
            euclideanNorm = euclideanNorm_tmp;
            return euclideanNorm;
        } else {
            return euclideanNorm;
        }
    }
    // Returns an Euclidean vector that is the unit vector of *this vector
    EuclideanVector EuclideanVector::createUnitVector() {
        if(euclideanNorm == -1.0){
            getEuclideanNorm();
        }
        std::vector<double> unit_magnitudes;
        for(auto iter=magnitudes->begin(); iter != magnitudes->end(); iter++){
            unit_magnitudes.push_back((*iter)/euclideanNorm);
        }
        return EuclideanVector(unit_magnitudes.begin(), unit_magnitudes.end());
    }

    // Allows to get and set the value in a given dimension of the Euclidean Vector. Hint: you may need two overloaded functions to achieve this requirement.
    double& EuclideanVector::operator[](std::size_t n) {
        return (*magnitudes)[n];
    }
    const double& EuclideanVector::operator[](std::size_t n) const {
        return (*magnitudes)[n];
    }

    // For adding vectors of the same dimension.
    EuclideanVector& EuclideanVector::operator+=(const EuclideanVector &e) {
        for(unsigned int i=0; i < magnitudes->size(); i++){
            (*this)[i] += e[i];
        }
        return *this;
    }

    // For subtracting vectors of the same dimension.
    EuclideanVector& EuclideanVector::operator-=(const EuclideanVector &e) {
        for(unsigned int i=0; i < magnitudes->size(); i++){
            (*this)[i] -= e[i];
        }
        return *this;
    }

    // For scalar multiplication, e.g. [1 2] * 3 = [3 6]
    EuclideanVector& EuclideanVector::operator*=(const double &mul) {
        for(unsigned int i=0; i < magnitudes->size(); i++){
            (*this)[i] *= mul;
        }
        return *this;
    }

    // For scalar division, e.g. [3 6] / 2 = [1.5 3]
    EuclideanVector& EuclideanVector::operator/=(const double &div) {
        for(unsigned int i=0; i < magnitudes->size(); i++){
            (*this)[i] /= div;
        }
        return *this;
    }

    // Operators for type casting to a std::vector and a std::list
    template <typename T> EuclideanVector::operator T() const {
        return static_cast<T>(*magnitudes);
    }
    /******************** Member Method Definition ********************/



    /******************* Friend Function Definition *******************/
    // True if the two vectors are equal in the number of dimensions and the magnitude in each dimension is equal.
    bool operator==(const EuclideanVector &e1, const EuclideanVector &e2) {
        if( e1.magnitudes->size() != e2.magnitudes->size() ){
            return false;
        }
        for( int i=0; i < e1.magnitudes->size(); i++ ){
            if( e1[i] != e2[i] ){
                return false;
            }
        }
        return true;
    }

    // The opposite of ==
    bool operator!=(const EuclideanVector &e1, const EuclideanVector &e2) {
        return !(e1 == e2);
    }

    // For adding vectors of the same dimension.
    EuclideanVector operator+(const EuclideanVector &e1, const EuclideanVector &e2) {
        EuclideanVector sum = e1;
        sum += e2;
        return sum;
    }

    // For substracting vectors of the same dimension.
    EuclideanVector operator-(const EuclideanVector &e1, const EuclideanVector &e2) {
        EuclideanVector sub = e1;
        sub -= e2;
        return sub;
    }

    // For dot-product multiplication, returns a double. E.g., [1 2] * [3 4] = 1 * 3 + 2 * 4 = 11
    double operator*(const EuclideanVector &e1, const EuclideanVector &e2) {
        double dot_product_result = 0.0;
        for(int i=0; i<e1.magnitudes->size(); i++){
            dot_product_result += (*e1.magnitudes)[i] * (*e2.magnitudes)[i];
        }
        return dot_product_result;
    }

    // For scalar multiplication, e.g. [1 2] * 3 = 3 * [1 2] = [3 6].
    // Hint: you'll obviously need two methods, as the scalar can be either side of the vector.
    EuclideanVector operator*(const EuclideanVector &e, const double mul) {
        EuclideanVector new_e = e;
        for(unsigned int i=0; i < e.magnitudes->size(); i++){
            (*new_e.magnitudes)[i] *= mul;
        }
        return new_e;
    }
    EuclideanVector operator*(const double mul, const EuclideanVector &e) {
        EuclideanVector new_e = e;
        for(unsigned int i=0; i < e.magnitudes->size(); i++){
            (*new_e.magnitudes)[i] *= mul;
        }
        return new_e;
    }

    // For scalar division, e.g. [3 6] / 2 = [1.5 3]
    EuclideanVector operator/(const EuclideanVector &e, const double div) {
        EuclideanVector new_e = e;
        for(unsigned int i=0; i < e.magnitudes->size(); i++){
            (*new_e.magnitudes)[i] /= div;
        }
        return new_e;
    }

    // Prints out the magnitude in each dimension of the Euclidean Vector
    // (surrounded by [ and ]), e.g. for a 3-dimensional vector: [1 2 3]
    std::ostream& operator<<(std::ostream &os, const EuclideanVector &v) {
        if( v.magnitudes == nullptr ){
            os << "[]";
            return os;
        }
        os << "[";
        for(int i=0; i<v.magnitudes->size()-1; i++) {
            os << (*v.magnitudes)[i] << " ";
        }
        os << (*v.magnitudes)[v.magnitudes->size()-1] << "]";
        return os;
    }
}




int main() {
    evec::EuclideanVector a(2);

    std::list<double> l {1,2,3};
    evec::EuclideanVector b{l.begin(),l.end()};

    std::vector<double> v2 {4,5,6,7};
    evec::EuclideanVector c{v2.begin(),v2.end()};

    std::vector<double> a1 {5,4,3,2,1};
    evec::EuclideanVector d{a1.begin(),a1.end()};

    std::list<double> a2 {9,0,8,6,7};
    evec::EuclideanVector e{a2.begin(),a2.end()};

    // use the copy constructor
    evec::EuclideanVector f{e};
    std::cout << a.getNumDimensions() << ": " << a << std::endl;
    std::cout << "D1:" << b.get(1) << " " << b << std::endl;
    std::cout << c << " Euclidean Norm = " << c.getEuclideanNorm() << std::endl;
    std::cout << d << " Unit Vector: " << d.createUnitVector() << " L = " << d.createUnitVector().getEuclideanNorm() << std::endl;
    std::cout << e << std::endl;
    std::cout << f << std::endl;

    // test the move constructor
    evec::EuclideanVector g = std::move(f);
//    std::cout << std::endl;
    std::cout << g << std::endl;
    std::cout << f << std::endl;




    // try operator overloading
    e += d;
    std::cout << e << std::endl;

    evec::EuclideanVector h = e - g;
    std::cout << h << std::endl;

    // test scalar multiplication
    h *= 2;
    std::cout << h << std::endl;

    evec::EuclideanVector j = b / 2;
    std::cout << j << std::endl;

    std::cout << "dot product = " << j * b << std::endl;

    if (g == (e - d)) std::cout << "true" << std::endl;
    if (j != b ) std::cout << "false" << std::endl;

    j[0] = 1;
    std::cout << j << std::endl;

    // type cast from EuclideanVector to a std::vector
    std::vector<double> vj = j;

    // type cast from EuclideanVector to a std::vector
    std::list<double> lj = j;

    for (auto d : lj) {
        std::cout << d << std::endl;
    }

    // list initialisation
    evec::EuclideanVector k {1, 2, 3};
    std::cout << k << std::endl;

    return 0;
}