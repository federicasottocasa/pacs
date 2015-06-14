#include "Polynomial.hpp"
#include <vector>
#include <iterator>
#include <iostream>
#include <ios> 
#include <cstdlib>  
#include <string> 
#include <sstream> 
#include <cmath> 

Polynomial::Polynomial(){coeff.emplace_back(0);}; 

Polynomial::Polynomial(const std::vector<double> c):coeff(c){};

Polynomial::Polynomial(const double c,const unsigned int order){
    for(std::size_t i=0;i<order;i++){
		coeff.emplace_back(0);}
    coeff.emplace_back(c);		
};

unsigned int Polynomial::getOrder(){
unsigned int s=(coeff).size()-1;
return s;};

unsigned int Polynomial::getOrder()const{
unsigned int s=(coeff).size()-1;
return s;};

//call operator returns the evaluation of the polymonial with the horner method
double Polynomial::operator()(double const & x){

 double u=coeff.back();
 for (int i=coeff.size()-2 ; i!=-1;--i) {
  	u=u*x+coeff[i];     
	}
  return u;
} 

 //!Overloads of += such that it sums polynomials
Polynomial & Polynomial::operator+=(Polynomial const & d)
  {  

unsigned int const cs=effectiveOrder()+1;
unsigned int const ds=d.effectiveOrder()+1;

//I have two cases:

if(cs>=ds){

	for(std::size_t i=0;i<ds;i++)
            coeff[i]+=d[i];
	         }	
if(cs<ds){ 
         
	for(std::size_t i=0;i<cs;i++)
            coeff[i]+=d[i];
	for(auto i=cs;i<ds;i++)
	    coeff.push_back(d[i]);   	
    	}

this->erase_last();
return (*this);
  }


double Polynomial::operator[](unsigned int i)const
  {
    return coeff[i];
  }

double & Polynomial::operator[](unsigned int i)
  {
    return coeff[i];
  }


Polynomial operator +(Polynomial const & p, Polynomial const & q)
{
  Polynomial temp(p);
  temp+=q; //I implement the overloading of this operator using the one made for +=
  return temp;
}


Polynomial & Polynomial::operator -=(Polynomial const & d)
{
unsigned int const cs=effectiveOrder()+1;
unsigned int const ds=d.effectiveOrder()+1;

//I have two cases

if(cs>=ds){ 
	
	for(std::size_t i=0;i<ds;i++)
            coeff[i]-=d.coeff[i];
	         }	

if(cs<ds){

	for(std::size_t i=0;i<cs;i++)	
            coeff[i]-=d.coeff[i];
	for(auto i=cs;i<ds;i++)
	    coeff.push_back(-d[i]);   	
	    	}
          
this->erase_last();
return (*this);
}


Polynomial operator -(Polynomial const & p, Polynomial const & q)
{
  Polynomial temp(p);
  temp-=q;
  return temp;
}

Polynomial & Polynomial::erase_last(){

int maxindex=getOrder();

if(coeff[maxindex]==0 && maxindex!=0){ 
	(coeff).erase((coeff).begin()+maxindex);
	(*this).Polynomial::erase_last();
	}
return (*this);
}

Polynomial & Polynomial::operator *=(Polynomial const & d)
{
unsigned int const cs=effectiveOrder()+1;
unsigned int const ds=d.effectiveOrder()+1;
unsigned int products=d.effectiveOrder()+effectiveOrder();
std::vector<double> tmp(products+1,0);  
for(std::size_t i=0;i<cs;i++){
	for(std::size_t j=0;j<ds;j++){		
		tmp[j+i]+=coeff[i]*d[j];
               	}
	}  
   Polynomial product(tmp);
  (*this)=product;
   this->erase_last(); //It shound't be necessary
   return *this;
}

Polynomial operator *(Polynomial const &p, Polynomial const & q)
{
  Polynomial temp(p);
  temp*=q;
  return temp;
}


std::ostream & operator << (std::ostream & str, Polynomial const & p)
{
unsigned int contzero=0;
for(unsigned int i=0;i<=p.effectiveOrder();i++){
	if(i==0 && p[i]!=0) str<<(p[i]);
	else{
   		if(p[i]!=0)  str<<p[i]<<"*x^"<<i;
	}
 
	if(p[i]==0)contzero++;
	if(i!=p.effectiveOrder() && p[i+1]>0 )  str<<"+";
}
  	if(contzero==p.Polynomial::effectiveOrder()+1) str<<" 0";
  	return str;
}



std::istream & operator >> (std::istream & str, Polynomial & r){
//you must write the polynomial in the following form: 1*x^0+1.32*x^1 ecc so you don't have to miss a term even if the coefficient is zero and you have to specify x^0 for the first term. To end writing you must do a blank space. At most you can write a polynomial of 100 degree but you could generalize it.

  std::string tmp;
  // Read from stream up to end of line or space char.
  std::getline(str,tmp,' '); 
  std::string::iterator it=tmp.begin();
  int cont=0;
  std::size_t max=tmp.length();
  std::size_t found=0;
  int quantnum=0;
  std::vector<double> c; 
      
    while(found<(max-1)){
       if(cont<10){
		//I need a small loop to count how many digits compose the coefficients
                quantnum=0;
		if((*it)=='+') 
			{it=it+1;
			 found++;}
                while((*it)!='*') 
				{quantnum++;
				 it=it+1;}
		//I write the coefficients in the vector
                std::istringstream s(tmp.substr(found,found+quantnum));
		c.emplace_back(1.0);
                s>>c[cont];
                //I update parameter e iterator for the next step
                cont++;
                it=it+4; 
                found=found+quantnum+4;
          }

	if(10<=cont && cont<100){ 
		quantnum=0;
		if((*it)=='+') 
			{it=it+1;
			 found++;}
		while((*it)!='*') 
				{quantnum++;
				 it=it+1;}
		std::istringstream s(tmp.substr(found,found+quantnum));
	        c.emplace_back(1.0);
                s>>c[cont];
		cont++;
		it=it+5;
		found=found+quantnum+5;
		} 
}

  r=Polynomial(c); 
  r.erase_last();
  return str;
}


std::pair<Polynomial,Polynomial> operator /(Polynomial const & p,Polynomial const & d){
if(d[0]==0 && d.effectiveOrder()==0) 
	throw std::runtime_error("you can't divide by zero ");
if(p.effectiveOrder()<d.effectiveOrder()) {
	std::pair<Polynomial,Polynomial> out=std::make_pair(Polynomial(0,0),p);
	return out;}

  int divOrder=p.effectiveOrder()-d.effectiveOrder();
  double divcoeff=0;
  Polynomial result;
  Polynomial tmp(p);
  Polynomial diff;
  int const ds=static_cast<int>(d.effectiveOrder());
  int ps=static_cast<int>(p.effectiveOrder());  
  while(ps>=ds){
  	divcoeff=tmp[ps]/d[ds];
	Polynomial a(divcoeff,divOrder);
        result+=a;
        Polynomial prod=a*d; 
        diff=tmp-prod;
	tmp=diff;
	ps--;
        divOrder--;
}
std::pair<Polynomial,Polynomial> out=std::make_pair(result,diff);
return out;
}

unsigned int Polynomial::effectiveOrder()const{
unsigned int cont=getOrder();
for(int i=getOrder();i>0;i--){
	if(coeff[i]==0) cont--;
	else return cont;
}
return cont;
}

