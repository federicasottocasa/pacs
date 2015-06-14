#include "Polynomial.hpp"
#include <iostream>
#include <vector>
#include <exception>
int main()
{ 
try{
std::vector<double> a={1,1,1,8,9};  
Polynomial<4> pa(a);
std::cout<<"pa  "<<pa<<std::endl; 

std::vector<double> d={2,3,2};
Polynomial<2> pd(d);
std::cout<<"pd  "<<pd<<std::endl;

//overload *    
auto p=pa*pd;
std::cout<<"prodotto pa*pd  "<<p<<std::endl; 
//result 2+5*x^1+7*x^2+21*x^3+44*x^4+43*x^5+18*x^6

 
//overload + and - 
auto s=pd+pa;   
std::cout<<"somma pa+pd  "<<s<<std::endl;  
auto di=pa-pd; 
std::cout<<"differenza pa-pd  "<<di<<std::endl;

//overload / 
std::vector<double> e={-4,-9,2,1};  
Polynomial<3> pe(e);
std::vector<double> f={-1,-2,1};
Polynomial<2> pf(f); 
auto div=pe/pf; 
std::cout<<std::endl<<"pe "<<pe<<std::endl;  
std::cout<<"pf "<<pf<<std::endl; 
std::cout<<"risultato pe/pf  "<<div.first<<"  resto  "<<div.second<<std::endl;
//result 4+x e reminder 0 

//another test for division
std::vector<double> g={2,-5,1,3};   
Polynomial<3> pg(g);
std::vector<double> h={2,3};    
Polynomial<1> ph(h);   
std::cout<<std::endl<<"ph  "<<ph<<std::endl;
std::cout<<"pg "<<pg<<std::endl;    
auto div2=pg/ph;             
std::cout<<"risultato  pg/ph  "<<div2.first<<"  resto  "<<div2.second<<std::endl;
//result -1.44444-0.333333*x^1+1*x^2  reminder 4.88889

//evaluation
double val=pg(2);
std::cout<<std::endl<<"valutazione pg in 2: "<<val<<std::endl;
//result 20 
 
//+=
std::vector<double> i={2,-5,1,7};    
Polynomial<3> pi(i);  
std::vector<double> l={2,3};
Polynomial<3> pl(l,1); 
std::cout<<std::endl<<"pi  "<<pi<<std::endl; 
std::cout<<"pl "<<pl<<std::endl;
pi+=pl;   
std::cout<<"pi dopo la somma pi+=pl  "<<pi<<std::endl;
pi-=pl; 
std::cout<<"pi dopo la differenza pi-=pl  "<<pi<<std::endl; 
//return pi as the beginning

//*=
std::vector<double> o={-1,-4,5,1};  
Polynomial<5> po(o,3);
std::vector<double> q={4,-1,2};
Polynomial<5> pq(q,2);
std::cout<<std::endl<<"po  "<<po<<std::endl;  
std::cout<<"pq  "<<pq<<std::endl; 
po*=pq;
std::cout<<"po*=pl "<<po<<std::endl; 
//result: -4-15*x^1+22*x^2-9*x^3+9*x^4+2*x^5       

//You must fix before the template parameter. For example -9.03*x^0+2.567*x^1 and then a blank space.
Polynomial<1> in;
std::cout<<std::endl<<"Inserisci Polinomio di grado 1:  "<<std::endl;  
std::cin>>in;
std::cout<<"Polinomio inserito:   "<<in<<std::endl;
}
catch(std::exception & e){ std::cout<<e.what()<<std::endl; }
  
  
}

