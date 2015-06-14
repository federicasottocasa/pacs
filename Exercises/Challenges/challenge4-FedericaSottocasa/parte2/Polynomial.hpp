#ifndef HH__Polynomial_HPP
#define HH__Polynomial_HPP
#include <vector>
#include <iostream>
#include <utility>
#include <stdexcept>
#include <string> 
#include <sstream> 
#include <iterator>
#include <ios> 
#include <cstdlib>  
#include <sstream> 

template<unsigned D>
class Polynomial
{
public:

  //Default constructor: polynomial is just a sequence of zero.
  Polynomial();

  //This constructor takes the vector of the coefficients
  Polynomial(const std::vector<double>);

  //This constructor takes the vector of the coefficients and the real degree that isn't the template parameter
  Polynomial(const std::vector<double>, const unsigned);

  //copy constructor: I stress that I use the synthetic one
  Polynomial(Polynomial const &)=default;

  //Assignment operator: I stress that I use the synthetic one
   Polynomial & operator=(Polynomial const &)=default;

  //The destructor is again the default one, but this time I don't specify it
  
  //they return the template parameter
  unsigned int const getOrder();
  unsigned int const getOrder() const;

  //returns the effective degree of Polynomial
  unsigned int effectiveOrder() const;

  //To give sense to these operator I think to the template parameter of the class as a maximum degree
  Polynomial & operator+=(Polynomial const &);
  Polynomial & operator-=(Polynomial const &);
  Polynomial & operator*=(Polynomial const &);

  //Overloads of [] such that estracts the coefficient of the i-order
  double operator[](unsigned int i)const;
  double & operator[](unsigned int i);
  
  //call operator returns the evaluation of the polymonial
  double operator()(double const &);

  //overload of the following operator
  template<unsigned D1, unsigned D2>
  friend Polynomial<(D1>D2)?D1:D2> operator +(Polynomial<D1> const &,Polynomial<D2> const &);

  template<unsigned D1, unsigned D2>
  friend Polynomial<(D1>D2)?D1:D2> operator-(Polynomial<D1> const &, Polynomial<D2> const &);

  template<unsigned D1, unsigned D2>
  friend Polynomial<D1+D2> operator*(Polynomial<D1> const &, Polynomial<D2> const &);

  template<unsigned D1, unsigned D2>
  friend std::pair<Polynomial<D1-D2>,Polynomial<D2-1>> operator /(Polynomial<D1> const &,Polynomial<D2> const &); 

  template <unsigned T>
  friend std::istream & operator >> (std::istream &, Polynomial<T> &);

  //Streaming operator to output polynomials.
  template <unsigned T>
  friend std::ostream & operator << (std::ostream &,Polynomial<T> const &);

private:
  //Vector storing the coefficients of the polynomial starting from the one of x^0
  std::vector<double> coeff; 
  //A new attribute of the class that store the real degree
  unsigned realD;
};

///////////////////////DEFINIZIONI///////////////////////////////////////
////////////////////////////////////////////////////////////////////////

//constructors 
template<unsigned D> Polynomial<D>::Polynomial():realD(D){
for(unsigned int i=0;i<=D;i++)
coeff.emplace_back(0);}; 

template<unsigned D> Polynomial<D>::Polynomial(const std::vector<double> c):coeff(c),realD(D){};

//with this constructor I allocate the memory that I need
template<unsigned D> Polynomial<D>:: Polynomial(const std::vector<double> c, const unsigned n):coeff(c),realD(n){};

//overload []
template<unsigned D>
double Polynomial<D>::operator[](unsigned int i)const
  {
    return coeff[i];
  }

template<unsigned D>
double & Polynomial<D>::operator[](unsigned int i)
  {
    return coeff[i];
  }


//call operator that uses the Horner method
template<unsigned D>
double Polynomial<D>::operator()(double const & x){
  double u=coeff.back();
  for (int i=coeff.size()-2;i!=-1;--i){
  	u=u*x+coeff[i];     
	}
  return u;
} 

//return the template parameter
template<unsigned D>
unsigned int const Polynomial<D>::getOrder(){
  return D;};

template<unsigned D>
unsigned int const Polynomial<D>::getOrder()const{
  return D;};

//output
template<unsigned S>
std::ostream & operator << (std::ostream & str, Polynomial<S> const & p)
{
  unsigned int contzero=0;
  for(unsigned int i=0;i<=p.realD;i++){
	if(i==0 && p[i]!=0) str<<(p[i]);
	else{
   		if(p[i]!=0)  str<<p[i]<<"*x^"<<i;
	}
 
	if(p[i]==0)contzero++;
	if(i!=p.realD && p[i+1]>0 )  str<<"+";
       
  }
  	if(contzero==p.realD+1) str<<" 0";
  	return str;
}


//return the effective order of the polynomial, if the coeff of max order is 0 the polynomial will have an inferior order
template<unsigned D>
unsigned int Polynomial<D>::effectiveOrder()const{
  unsigned int cont=realD;
  for(int i=realD;i>0;i--){
	if(coeff[i]==0) cont--;
	else return cont;
  }
  return cont;
}


//Overloads of += such that it sums polynomials that belongs to the same template class
template<unsigned D>
Polynomial<D> & Polynomial<D>::operator+=(Polynomial<D> const & d)
{  
  unsigned int const cs=realD+1;
  unsigned int const ds=d.realD+1;

  if(cs>=ds){
	for(std::size_t i=0;i<ds;i++)
            coeff[i]+=d[i];
  }

  if(cs<ds){
	for(std::size_t i=0;i<cs;i++)
            coeff[i]+=d[i];
	for(std::size_t i=cs;i<ds;i++)
            coeff.push_back(d[i]);

  }
  realD=std::max(cs-1,ds-1);
  return (*this);
}


//Overloads -=
template<unsigned D>
Polynomial<D> & Polynomial<D>::operator-=(Polynomial<D> const & d)
{  
  unsigned int const cs=realD+1;
  unsigned int const ds=d.realD+1;

  if(cs>=ds){
	for(std::size_t i=0;i<ds;i++)
            coeff[i]-=d[i];
  }

  if(cs<ds){
	for(std::size_t i=0;i<cs;i++)
            coeff[i]-=d[i];
	for(std::size_t i=cs;i<ds;i++)
            coeff.push_back(-d[i]);

  }
  realD=std::max(cs-1,ds-1);
  return *this;
}


//Overload *=
template<unsigned D>
Polynomial<D> & Polynomial<D>::operator *=(Polynomial<D> const & d)
{
  unsigned int const cs=realD;
  unsigned int const ds=d.realD;
  if(cs+ds>D) throw std::runtime_error("you can't store completely the result vector");

  std::vector<double> tmp(D+1,0);  
  for(std::size_t i=0;i<=cs;i++){  
	for(std::size_t j=0;j<=ds;j++){		
		tmp[j+i]+=coeff[i]*d[j];
		               	}
	  }  
  for(unsigned int i=cs+1;i<=D;i++){
		coeff.push_back(0); 
		          }
 coeff=tmp;
 realD=cs+ds;
 return *this;
}


//Overload of +
template<unsigned D1, unsigned D2>
Polynomial<(D1>D2)?D1:D2> operator +(Polynomial<D1> const & d1,Polynomial<D2> const & d2)
{  
  Polynomial<(D1>D2)?D1:D2> result;
  //I have two cases:
  if(d1.realD>=d2.realD){
	for(std::size_t i=0;i<=d2.realD;i++)
            result[i]=d1[i]+d2[i];
	for(std::size_t i=d2.realD+1;i<=d1.realD;i++)
	    result[i]=d1[i];  
	         }	
  if(d1.realD<d2.realD){ 
       	for(std::size_t i=0;i<=d1.realD;i++)
            result[i]=d1[i]+d2[i];
	for(std::size_t i=d1.realD+1;i<=d2.realD;i++)
	    result[i]=d2[i];   	
    	}
  result.realD=result.effectiveOrder();
  return result;
}


//Overload -
template<unsigned D1, unsigned D2>
Polynomial<(D1>D2)?D1:D2> operator -(Polynomial<D1> const & d1,Polynomial<D2> const & d2)
{  
  Polynomial<(D1>D2)?D1:D2> result;
  //I have two cases:
  if(d1.realD>=d2.realD){
	for(std::size_t i=0;i<=d2.realD;i++)
            result[i]=d1[i]-d2[i];
	for(auto i=d2.realD+1;i<=d1.realD;i++)
	    result[i]=d1[i];  
	         }	
  if(d1.realD<d2.realD){ 
      	for(std::size_t i=0;i<=d1.realD;i++)
            result[i]=d1[i]-d2[i];
	for(auto i=d1.realD+1;i<=d2.realD;i++)
	    result[i]=-d2[i];   	
    	}
  result.realD=result.effectiveOrder();
  return result;
}


//overload *
template<unsigned D1,unsigned D2> Polynomial<D1+D2> operator *(Polynomial<D1> const & p1,Polynomial <D2> const & p2)
{
  std::vector<double> tmp(D1+D2+1,0);  

  for(std::size_t i=0;i<=p1.realD;i++){ 
	for(std::size_t j=0;j<=p2.realD;j++){		
		tmp[j+i]+=p1[i]*p2[j];
	  	               	}
	}  
  Polynomial<D1+D2> product(tmp);
  product.realD=p1.realD+p2.realD;  
  return product;
}


//overload /
template<unsigned D1,unsigned D2>
std::pair<Polynomial<D1-D2>,Polynomial<D2-1>> operator /(Polynomial<D1> const & p,Polynomial<D2> const & d)
{ 
  if(d.realD>p.realD) 
	throw std::runtime_error("you can't divide by zero ");
  if(static_cast<int>(D1-D2)<0)
	throw std::runtime_error("you can't create a result Polynomial of negative degree ");
  if(static_cast<int>(D1-D2)<(p.realD-d.realD))
	throw std::runtime_error("The difference of the template parameters should be like al least like the one beetwen the real degree");

  int divOrder=p.realD-d.realD;
  Polynomial<D1-D2> result;
  Polynomial<D1> tmp(p);
  Polynomial<D2-1> diff;
  int const ds=static_cast<int>(d.realD); 
  int ps=static_cast<int>(p.realD);
  while(ps>=ds){
	result[divOrder]=tmp[ps]/d[ds];
	std::vector<double> prod(divOrder+d.realD+1,0);
  	for(std::size_t j=0;j<=d.realD;j++){	
		prod[j+divOrder]=prod[j+divOrder]+result[divOrder]*d[j]; 
	  	               	}
  	for(std::size_t i=0;i<prod.size();i++) 
        	tmp[i]=tmp.coeff[i]-prod[i];
	ps--;
        divOrder--;
  	if(divOrder<0){
		for(std::size_t i=0;i<=d.realD-1;i++){	
			diff[i]=tmp[i];
        		       }
  			}
	}
 result.realD=p.realD-d.realD;
 diff.realD=diff.effectiveOrder(); //about the module of the division the degree isn't known before, at most it is D2-1.
 std::pair<Polynomial<D1-D2>,Polynomial<D2-1> > out=std::make_pair(result,diff);
 return out;
}


template <unsigned S>
std::istream & operator >> (std::istream & str, Polynomial<S> & r){
//you must write the polynomial in the following form: 1*x^0+1.32*x^1 ecc so you don't have to miss a term even if the coefficient is zero and you have to specify x^0 for the first term. To end writing you must do a blank space. At most you can write a Polynomial of 100 degree but it is easy to generalize the code.

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

  r=Polynomial<S>(c); 
  r.realD=r.effectiveOrder();
  return str;
}

#endif
