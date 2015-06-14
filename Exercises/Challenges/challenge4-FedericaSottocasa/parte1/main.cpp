#include "Polynomial.hpp"
#include <iostream>
#include <vector>
#include <exception>
int main()
{

std::vector<double> e={8.1,-4.5,7};
Polynomial p(e);
std::vector<double> f={1.0,2,3.1}; 
Polynomial q(f);
std::vector<double> u={1}; 
std::vector<double> v={0,-2.0,1.8,5,6,8}; 
Polynomial z(u);
Polynomial r(v); 

//Monomio
Polynomial Monomio(-2,4);
std::cout<<"Monomio: "<<Monomio<<std::endl;

//I verify the operator + -
std::cout<<"Polinomio p: "<<p<<std::endl;
std::cout<<"Polinomio q: "<<q<<std::endl;
std::cout<<"Polinomio z: "<<z<<std::endl;
std::cout<<"Polinomio r: "<<r<<std::endl;
std::cout<<"Polinomio p+z: "<<p+z<<std::endl;
std::cout<<"Polinomio q+r: "<<q+r<<std::endl;
std::cout<<"Polinomio p-z: "<<p-z<<std::endl;
std::cout<<"Polinomio q-r: "<<q-r<<std::endl;

//I verify the call operator to evaluate the polynomial
double x=1.65;
std::cout<<"Valutazione di p in "<<x<<" : "<<p(x)<<std::endl;
//result 19.7325

//I verify the operator *
std::vector<double> ee={-1,-4,5,1};
Polynomial t(ee);
std::vector<double> ff={4,-1,2}; 
Polynomial w(ff);
std::cout<<std::endl<<"t: "<<t<<std::endl;
std::cout<<"w: "<<w<<std::endl;
//you can verify *= or *, in fact * derive from *=
std::cout<<"t*w: "<<t*w<<std::endl;
//result  -4-15*x^1+22*x^2-9*x^3+9*x^4+2*x^5

try{
//I verify the division
std::vector<double> vd1={-4,-9,2,1};
Polynomial d1(vd1);
std::vector<double> vd2={-1,-2,1}; 
Polynomial d2(vd2);
std::cout<<std::endl<<"d1: "<<d1<<std::endl;
std::cout<<"d2: "<<d2<<std::endl;
auto div12=d1/d2;
std::cout<<"d1.divis(d2): "<<div12.first<<" resto "<<div12.second<<std::endl;
//result 4+x reminder 0

std::vector<double> vd3={-1,5,0,-4,3};
Polynomial d3(vd3);
std::vector<double> vd4={-1,0,3.0}; 
Polynomial d4(vd4);
std::cout<<std::endl<<"d3: "<<d3<<std::endl;
std::cout<<"d4: "<<d4<<std::endl;
auto div=d3/d4;
std::cout<<"risultato divisione "<<div.first<<std::endl<<"resto "<<div.second<<std::endl;
//result 0.333333-1.33333*x^1+1*x^2  reminder -0.666667+3.66667*x^1

//Read from input and print the polynomial
std::cout<<"Inserisci un polinomio"<<std::endl;
Polynomial a;
std::cin>>a;
std::cout<<"Polinomio inserito: "<<a<<std::endl;

} catch(std::exception & e){ std::cout<<e.what()<<std::endl; }

}

