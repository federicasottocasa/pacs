#include "Polynomial.hpp"
#include <iostream>
#include <vector>
#include <exception>
#include<complex> 
  
int main()
{ 
using complesso=std::complex<double>;
 
try{  

//test for the basic operations 
std::vector<complesso> i={complesso(1,9.1),complesso(2,-1)};
Polynomial<1,complesso> pi(i);     
std::cout<<"p1: "<<pi<<std::endl;
std::vector<complesso> j={complesso(-4,3.7),complesso(9,-3),complesso(8.3,2)}; 
Polynomial<2,complesso> pj(j); 
std::cout<<"p2: "<<pj<<std::endl; 

auto sommaCompl=pi+pj;  
std::cout<<"somma tra polinomi complessi p1+p2= "<<sommaCompl<<std::endl;
//result (-3+12.8i)+(11-4i)*x^1+(8.3+2i)*x^2

auto diffCompl=pi-pj;  
std::cout<<"differenza tra polinomi complessi p1-p2= "<<diffCompl<<std::endl;
//result (5+5.4i)+(-7+2i)*x^1+(-8.3-2i)*x^2

auto prodCompl=pi*pj;  
std::cout<<"prodotto tra polinomi complessi p1*p2= "<<prodCompl<<std::endl;
//result  -37.67-32.7i+(32+90.3i)*x^1+(5.1+62.53i)*x^2+(18.6-4.3i)*x^3

auto divCompl=pj/pi;  
std::cout<<"divisione tra polinomi complessi p2/p1=  "<<divCompl.first<<std::endl;
std::cout<<"con resto= "<<divCompl.second<<std::endl; 
//result  17.7928-7.1196i+(2.92+2.46i)*x^1    resto -86.5812-151.095i

std::vector<int> h={1,2,0,0}; 
Polynomial<3,int> ph(h,1);
std::cout<<std::endl<<"p3: "<<ph<<std::endl;       
std::vector<int> l={4,5,7,11,0,0};
Polynomial<5,int> pl(l,3);    
std::cout<<"p4: "<<pl<<std::endl;
 
auto somma=ph+pl;
std::cout<<"somma tra polinomi interi p3+p4= "<<somma<<std::endl;
//result 5+7x^1+7x^2+11x^3  

auto diff=pl-ph;
std::cout<<"differenza tra polinomi interi p4-p3= "<<diff<<std::endl;
//result 3+3x^1+7x^2+11x^3

auto prod=ph*pl;  
std::cout<<"prodotto tra polinomi interi p3*p4= "<<prod<<std::endl;  
//result 4+13x^1+17x^2+25x^3+22x^4 
  
auto div=pl/ph;
std::cout<<"divisione tra polinomi interi p4/p3= "<<div.first<<std::endl;
std::cout<<"con resto: "<<div.second<<std::endl; 
//result 2.125+0.75x^1+5.5x^2 con resto 1.875


//test for the overload *= += -=
std::vector<double> m={9.1,-8,2,14.5,0,0,0};
Polynomial<6,double> pm(m,3); 
std::cout<<std::endl<<"pm: "<<pm<<std::endl; 
std::vector<double> o={9,-3.7,2,1.2,0,0,0,0};
Polynomial<6,double> po(o,3); 
std::cout<<"po: "<<po<<std::endl;

po*=pm;    
std::cout<<"overload *=: po*=pm: "<<po<<std::endl;
//result 81.9-105.67x^1+65.8x^2+118.02x^3-59.25x^4+31.4x^5+17.4x^6

std::vector<complesso> n={complesso(-5.2,6),complesso(0,5),complesso(-8,-2)};
Polynomial<4,complesso> pn(n,2); 
std::vector<complesso> q={complesso(-9,-5),complesso(6,-4.3),complesso(8,2)};
Polynomial<4,complesso> pq(q,2); 
std::cout<<std::endl<<"p7: "<<pn<<std::endl; 
std::cout<<"p8: "<<pq<<std::endl; 
pn+=pq;
std::cout<<"overload +=: p7+=p8: "<<pn<<std::endl; 
pn-=pq;
std::cout<<"overload -=: p7-=p8: "<<pn<<std::endl; 
//return p7 as the beginning


//test for the call operator
int xint=3;
double xdoub=0.5; 
complesso x=complesso(8,3.1);

std::cout<<std::endl<<"Polinomio double "<<pm<<" Valutazione in x intero "<<xint<<" :"<<pm(xint)<<std::endl; 
//result 394.6
std::cout<<"Polinomio double "<<pm<<" Valutazione in x double "<<xdoub<<" :"<<pm(xdoub)<<std::endl; 
//result 7.4125
std::cout<<"Polinomio double "<<pm<<" Valutazione in x complesso double "<<x<<" :"<<pm(x)<<std::endl<<std::endl; 
//result 4133.6+8272.83i

std::cout<<"Polinomio intero "<<pl<<" Valutazione in x intero "<<xint<<" :"<<pl(xint)<<std::endl;
//result 379
std::cout<<"Polinomio intero "<<pl<<" Valutazione in x double  "<<xdoub<<" :"<<pl(xdoub)<<std::endl; 
//result 9.625
std::cout<<"Polinomio intero "<<pl<<" Valutazione in x complesso double  "<<x<<" :"<<pl(x)<<std::endl<<std::endl; 
//result 3519.69+6582.2i   

std::cout<<"Polinomio complesso "<<pn<<" Valutazione in x intero "<<xint<<" :"<<pn(xint)<<std::endl; 
//result -77.2+3i
std::cout<<"Polinomio complesso "<<pn<<" Valutazione in x double "<<xdoub<<" :"<<pn(xdoub)<<std::endl;
//result -7.2+8i
std::cout<<"Polinomio complesso "<<pn<<" Valutazione in x complesso double "<<x<<" :"<<pn(x)<<std::endl<<std::endl;
//result -356.62-459.58i


//test for the input
std::vector<complesso> r={complesso(5,-3.9),complesso(4.6,-9),complesso(2.6,-7.8)};
Polynomial<2,complesso> pr(r); 
std::cout<<std::endl<<"inserisci un polinomio complesso di grado due "<<std::endl;
//for example write '(2,5)*x^0+(-9.2,5)*x^1+(-6.8,-9)*x^2' and to end a blank space ' '.
Polynomial<2,std::complex<double>> in;
std::cin>>in;
std::cout<<"Polinomio immesso: "<<in<<std::endl;
std::cout<<"p8: "<<pr<<std::endl;
in+=pr;
std::cout<<"Somma in+=p8 "<<in<<std::endl;

 }catch(std::exception & e){ std::cout<<e.what()<<std::endl; }  

}
 
