#ifndef HH__Polynomial_HPP
#define HH__Polynomial_HPP
#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>

class Polynomial
{
public:

  //Default constructor: polynomial is just a number equal to zero.
  Polynomial();

  //This constructor takes the vector of the coefficients
  Polynomial(const std::vector<double> );

  //This is a constructor for a monomial, so I don't want to give the all vector but just the coefficient and the order
  Polynomial(const double ,const unsigned int );

  //copy constructor: I stress that I use the synthetic one
  Polynomial(Polynomial const &)=default;

  //Assignment operator: I stress that I use the synthetic one
  Polynomial & operator=(Polynomial const &)=default;

  //The destructor is again the default one, but this time I don't specify it

 //Overloads of += -= and *=
  Polynomial & operator+=(Polynomial const &);
  Polynomial & operator-=(Polynomial const &);
  Polynomial & operator*=(Polynomial const &);

  //Overloads of [] such that estracts the coefficient of the i-order
  double operator[](unsigned int i)const;
  double & operator[](unsigned int i);
  
  //call operator returns the evaluation of the polymonial
  double operator()(double const &);
  
 Polynomial & erase_last();
 unsigned int getOrder();
 unsigned int getOrder() const;
 unsigned int effectiveOrder()const;

 //I did them but I don't use them
 std::vector<double>::iterator begin(){return coeff.begin();}
 std::vector<double>::const_iterator begin()const {return coeff.cbegin();}

 std::vector<double>::iterator end(){return coeff.end();}
 std::vector<double>::const_iterator end() const{return coeff.cend();}

 //overload operator
 friend Polynomial operator+(Polynomial const &, Polynomial const &);
 friend Polynomial operator-(Polynomial const &, Polynomial const &);
 friend Polynomial operator*(Polynomial const &, Polynomial const &);
 friend std::pair<Polynomial,Polynomial> operator /(Polynomial const &,Polynomial const &); 

 //Streaming operator to output polynomials.
 friend std::ostream & operator << (std::ostream &,Polynomial const &);

 //Streaming operator to input polynomials.
 friend std::istream & operator >> (std::istream &,Polynomial &);

 private:
  //! Vector storing the coefficients of the polynomial starting from the one of x^0
  std::vector<double> coeff; 

};



#endif
