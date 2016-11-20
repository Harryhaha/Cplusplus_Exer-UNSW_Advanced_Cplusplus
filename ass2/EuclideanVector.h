//
// Created by harry on 19/08/2016.
//
#ifndef ASS2_EUCLIDEANVECTOR_H
#define ASS2_EUCLIDEANVECTOR_H

#include <vector>
#include <list>
#include <initializer_list>
#include <cmath>

namespace evec {
    /***************************** class declaration *****************************/
    class EuclideanVector {
    /*********************************** Friends ***********************************/
    // True if the two vectors are equal in the number of dimensions and the magnitude in each dimension is equal.
    friend bool operator==(const EuclideanVector &e1, const EuclideanVector &e2);

    // The opposite of ==
    friend bool operator!=(const EuclideanVector &e1, const EuclideanVector &e2);

    // For adding vectors of the same dimension.
    friend EuclideanVector operator+(const EuclideanVector &e1, const EuclideanVector &e2);

    // For substracting vectors of the same dimension.
    friend EuclideanVector operator-(const EuclideanVector &e1, const EuclideanVector &e2);

    // For dot-product multiplication, returns a double. E.g., [1 2] * [3 4] = 1 * 3 + 2 * 4 = 11
    friend double operator*(const EuclideanVector &e1, const EuclideanVector &e2);

    // For scalar multiplication, e.g. [1 2] * 3 = 3 * [1 2] = [3 6].
    // Hint: you'll obviously need two methods, as the scalar can be either side of the vector.
    friend EuclideanVector operator*(const EuclideanVector &e, const double mul);
    friend EuclideanVector operator*(const double mul, const EuclideanVector &e);

    // For scalar division, e.g. [3 6] / 2 = [1.5 3]
    friend EuclideanVector operator/(const EuclideanVector &e, const double div);

    // Prints out the magnitude in each dimension of the Euclidean Vector
    // (surrounded by [ and ]), e.g. for a 3-dimensional vector: [1 2 3]
    friend std::ostream& operator<<(std::ostream &os, const EuclideanVector &v);
    /*********************************** Friends ***********************************/


    public:
        /***************** Six constructors *****************/
        // Second Constructor:
        EuclideanVector(unsigned int dim, double mag);

        // First Constructor:
        EuclideanVector(unsigned int dim = 1);

        // Third Constructor:
        template <typename T> EuclideanVector(T iter_start, T iter_end);
//        EuclideanVector(std::vector::iterator iter_start, std::vector::iterator iter_end);
//        EuclideanVector(std::list::iterator iter_start, std::list::iterator iter_end);

        // Fourth Constructor:
        EuclideanVector(std::initializer_list<double> list);

        // Fifth Constructor / copy constructor:
        EuclideanVector(const EuclideanVector &e);

        // Sixth Constructor / move constructor   // change
        EuclideanVector(EuclideanVector &&e) noexcept;
        /***************** Six constructors *****************/


        /***************** public member operations *****************/
        // Copy Assignment:
        EuclideanVector& operator=(const EuclideanVector &);

        // Move Assignment:
        EuclideanVector& operator=(EuclideanVector &&) noexcept;

        // Returns an unsigned int containing the number of dimensions in a particular vector
        unsigned int getNumDimensions() const;

        // Returns a double, the value of the magnitude in the dimension given as the function parameter
        double get(unsigned int dim) const;

        // Returns the Euclidean norm of the vector as a double
        double getEuclideanNorm();

        // Returns an Euclidean vector that is the unit vector of *this vector
        EuclideanVector createUnitVector();

        // Allows to get and set the value in a given dimension of the Euclidean Vector. Hint: you may need two overloaded functions to achieve this requirement.
        double& operator[](std::size_t n);
        const double& operator[](std::size_t n) const;

        // For adding vectors of the same dimension.
        EuclideanVector& operator+=(const EuclideanVector &e);

        // For subtracting vectors of the same dimension.
        EuclideanVector& operator-=(const EuclideanVector &e);

        // For scalar multiplication, e.g. [1 2] * 3 = [3 6]
        EuclideanVector& operator*=(const double &mul);

        // For scalar division, e.g. [3 6] / 2 = [1.5 3]
        EuclideanVector& operator/=(const double &div);

        // Operators for type casting to a std::vector and a std::list
        template <typename T> operator T() const;
        /***************** public member operations *****************/


        /***************** Destructor *****************/
        ~EuclideanVector();
        /***************** Destructor *****************/

    private:
//        unsigned int dimension = 1;
        std::vector<double> *magnitudes;
        double euclideanNorm = -1.0;

    };
    /***************************** class declaration *****************************/


    /***************************** Friend declarations *****************************/
    // True if the two vectors are equal in the number of dimensions and the magnitude in each dimension is equal.
    bool operator==(const EuclideanVector &e1, const EuclideanVector &e2);

    // The opposite of ==
    bool operator!=(const EuclideanVector &e1, const EuclideanVector &e2);

    // For adding vectors of the same dimension.
    EuclideanVector operator+(const EuclideanVector &e1, const EuclideanVector &e2);

    // For substracting vectors of the same dimension.
    EuclideanVector operator-(const EuclideanVector &e1, const EuclideanVector &e2);

    // For dot-product multiplication, returns a double. E.g., [1 2] * [3 4] = 1 * 3 + 2 * 4 = 11
    double operator*(const EuclideanVector &e1, const EuclideanVector &e2);

    // For scalar multiplication, e.g. [1 2] * 3 = 3 * [1 2] = [3 6].
    // Hint: you'll obviously need two methods, as the scalar can be either side of the vector.
    EuclideanVector operator*(const EuclideanVector &e, const double mul);
    EuclideanVector operator*(const double mul, const EuclideanVector &e);

    // For scalar division, e.g. [3 6] / 2 = [1.5 3]
    EuclideanVector operator/(const EuclideanVector &e, const double div);

    // Prints out the magnitude in each dimension of the Euclidean Vector
    // (surrounded by [ and ]), e.g. for a 3-dimensional vector: [1 2 3]
    std::ostream& operator<<(std::ostream &os, const EuclideanVector &v);
}

#endif //ASS2_EUCLIDEANVECTOR_H
