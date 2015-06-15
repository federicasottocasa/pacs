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
#include<complex>

template<unsigned D,typename T>
class Polynomial
{
public:
 
  //Default constructor: polynomial is just a sequence of zero.
  Polynomial();

  //This constructor takes the vector of the coefficients
  Polynomial(const std::vector<T>);

  //This constructor takes the vector of the coefficients and the real degree that isn't the template parameter
  Polynomial(const std::vector<T>, const unsigned );

  //copy constructor: I stress that I use the synthetic one
  Polynomial(Polynomial const &)=default;

  //Assignment operator: I stress that I use the synthetic one
   Polynomial & operator=(Polynomial const &)=default;

  //The destructor is again the default one, but this time I don't specify it

  unsigned int const getOrder();
  unsigned int const getOrder() const;

  //To give sense to these operator I think about the template parameter of the class as a maximum degree
  Polynomial & operator+=(Polynomial const &);
  Polynomial & operator-=(Polynomial const &);
  Polynomial & operator*=(Polynomial const &);

  //Overloads of [] such that estracts the coefficient of the i-order
  T operator[](unsigned int i)const;
  T & operator[](unsigned int i);
  
  //call operator returns the evaluation of the polymonial, it returns the most general type and I assume that all the complex are declared as COMPLEX OF DOUBLE
  template<typename TX>
  std::complex<double> operator()(TX const &);
  
  template<unsigned N>
  friend std::complex<double> Evaluation(std::complex<double> const &,Polynomial<N,std::complex<double>>);

  template<unsigned N,typename TX,typename S>
  friend std::complex<double> Evaluation(TX const &,Polynomial<N,S>);

  template<unsigned N,typename S>
  friend std::complex<double> Evaluation(std::complex<double> const &,Polynomial<N,S>);

  template<unsigned N,typename TX>
  friend std::complex<double> Evaluation(TX const & ,Polynomial<N,std::complex<double>> p);

 
//overload of the following operators
  template<unsigned D1, unsigned D2, typename S>
  friend Polynomial<((D1>D2)?D1:D2),S> operator +(Polynomial<D1,S> const &,Polynomial<D2,S> const &);

  template<unsigned D1, unsigned D2, typename S>
  friend Polynomial<(D1>D2)?D1:D2,S> operator -(Polynomial<D1,S> const &, Polynomial<D2,S> const &);

  template<unsigned D1, unsigned D2, typename S>
  friend Polynomial<D1+D2,S> operator *(Polynomial<D1,S> const &, Polynomial<D2,S> const &);

  template<unsigned D1, unsigned D2, typename S>
  friend std::pair<Polynomial<D1-D2,S>, Polynomial<D2-1,S> > operator /(Polynomial<D1,S> const &, Polynomial<D2,S> const &); 

//partial specialization for Polynomials with int coefficients
  template<unsigned D1, unsigned D2> 
  friend std::pair<Polynomial<D1-D2,double>, Polynomial<D2-1,double>> operator /(Polynomial<D1,int> const &, Polynomial<D2,int> const &);

//Streaming operator to write a polynomial as input.
  template <unsigned M,typename N>
  friend std::istream & operator >> (std::istream &, Polynomial<M,N> &);
  
//Streaming operator to output polynomials.
  template <unsigned M,typename N>
  friend std::ostream & operator << (std::ostream &,Polynomial<M,N> const &);

//partial specialization for complex
  template <unsigned M,typename N>
  friend std::ostream & operator << (std::ostream &,Polynomial<M,std::complex<N> > const &);

private:
  //Vector storing the coefficients of the polynomial starting from the one of x^0
  std::vector<T> coeff; 
  //An attribute of the class that indicates the real memory allocated
  unsigned realD;
};

///////////////////////DEFINIZIONI///////////////////////////////////////
////////////////////////////////////////////////////////////////////////

//constructors 
template<unsigned D,typename T> Polynomial<D,T>::Polynomial():realD(D){
for(unsigned int i=0;i<=D;i++)
coeff.emplace_back(0);}; 

template<unsigned D,typename T> Polynomial<D,T>::Polynomial(const std::vector<T> c):coeff(c),realD(D){};

template<unsigned D,typename T> Polynomial<D,T>:: Polynomial(const std::vector<T> c, const unsigned n):coeff(c),realD(n){};

//overload []
template<unsigned D,typename T>
T Polynomial<D,T>::operator[](unsigned int i)const
  {
    return coeff[i];
  }

template<unsigned D,typename T>
T & Polynomial<D,T>::operator[](unsigned int i)
  {
    return coeff[i];
  }

//call operator
template<unsigned D,typename T>
template<typename TX>
  std::complex<double> Polynomial<D,T>::operator()(TX const & x){ 
return Evaluation(x,*this);}

//I assume that the allowed template parameter of type COMPLEX is just DOUBLE both for the Polynomial and the x.

//Specialization for TX and T that are complex of double
template<unsigned D>
  std::complex<double> Evaluation(std::complex<double> const & x,Polynomial<D,std::complex<double> > p){
  std::complex<double> u=p.coeff.back();
  for (int i=p.coeff.size()-2;i!=-1;--i) {
  	u=u*x+p.coeff[i];     
	}
  return u;
} 

//function to get the static cast
template<typename T> std::complex<double> SCdouble(T x){
  std::complex<double> xx;
  double xreal=static_cast<double> (x); //It isn't necessary if T=double but I do this to avoid a big number of specialization for Evaluation
  xx=std::complex<double>(xreal,0);
 return xx;
}


template<unsigned D,typename TX,typename T>
  std::complex<double> Evaluation(TX const & x,Polynomial<D,T> p){
  std::complex<double> u=SCdouble(p.coeff.back());
  std::complex<double> xx=SCdouble(x);
  for (int i=p.coeff.size()-2;i!=-1;--i) {
    std::complex<double> pp=SCdouble(p.coeff[i]);
  	u=u*xx+pp;     
	}
  return u;
} 
 

template<unsigned D,typename T>
  std::complex<double> Evaluation(std::complex<double> const & x,Polynomial<D,T> p){
  std::complex<double> u=SCdouble(p.coeff.back()); 
  for (int i=p.coeff.size()-2;i!=-1;--i) {
  std::complex<double> pp=SCdouble(p.coeff[i]); 
  	u=u*x+pp;     
	}
  return u;
} 

template<unsigned D,typename TX>
  std::complex<double> Evaluation(TX const & x,Polynomial<D,std::complex<double>> p){
  std::complex<double> u=p.coeff.back();
  std::complex<double> xx=SCdouble(x);
  for (int i=p.coeff.size()-2;i!=-1;--i) {
  	u=u*xx+p.coeff[i];     
	}
  return u;
} 

//returns the template parameter
template<unsigned D,typename T>
unsigned int const Polynomial<D,T>::getOrder(){
  return D;};

template<unsigned D,typename T>
unsigned int const Polynomial<D,T>::getOrder()const{
  return D;};


// output
template<unsigned S,typename L>
std::ostream & operator << (std::ostream & str, Polynomial<S,L> const & p)
{
  unsigned int contzero=0;
  for(unsigned int i=0;i<=p.realD;i++){
	if(i==0 && p[i]!=0) str<<(p[i]);
	else{
   		if(p[i]!=0)  str<<p[i]<<"*x^"<<i;
	}
 
	if(p[i]==0)contzero++;
	if(i!=p.realD && p[i+1]>0)  str<<"+";
  }
  	if(contzero==p.realD+1) str<<" 0";
  	return str;
}


// output partial specialization for complex
template<unsigned S,typename P>
std::ostream & operator << (std::ostream & str, Polynomial<S,std::complex<P> > const & p)
{
  unsigned int contzero=0;
  for(unsigned int i=0;i<=p.realD;i++){
	if(i==0 && p[i]!=std::complex<P>(0,0)) str<<(p[i]);
	else{
   		if(p[i]!=std::complex<P>(0,0))  str<<p[i]<<"*x^"<<i;
	}
 
	if(p[i]==std::complex<P>(0,0))contzero++;
	if(i!=p.realD && (p[i+1])!=std::complex<P>(0,0) )  str<<"+";
  }
  	if(contzero==p.realD+1) str<<p[0];
  	return str;
}


//Overloads of += such that it sums polynomials that belongs to the same template class
template<unsigned D,typename T>
Polynomial<D,T> & Polynomial<D,T>::operator+=(Polynomial<D,T> const & d)
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
template<unsigned D,typename T>
Polynomial<D,T> & Polynomial<D,T>::operator-=(Polynomial<D,T> const & d)
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
template<unsigned D,typename T>
Polynomial<D,T> & Polynomial<D,T>::operator *=(Polynomial<D,T> const & d)
{
  unsigned int const cs=realD;
  unsigned int const ds=d.realD;
  if(cs+ds>D) throw std::runtime_error("you can't store completely the result vector");

  T prod;
  std::vector<T> tmp(D+1,0);  
  for(std::size_t i=0;i<=cs;i++){  
	for(std::size_t j=0;j<=ds;j++){	
		prod=coeff[i]*d[j];	
		tmp[j+i]+=prod; 
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
template<unsigned D1, unsigned D2, typename T>
Polynomial<((D1>D2)?D1:D2),T> operator +(Polynomial<D1,T> const & d1,Polynomial<D2,T> const & d2)
{  
  Polynomial<(D1>D2)?D1:D2,T> result;
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
  return result;
}


//Overload -
template<unsigned D1, unsigned D2,typename T>
Polynomial<(D1>D2)?D1:D2,T> operator -(Polynomial<D1,T> const & d1,Polynomial<D2,T> const & d2)
{  
  Polynomial<(D1>D2)?D1:D2,T> result;
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
  return result;
}


//overload *
template<unsigned D1, unsigned D2,typename T>
 Polynomial<D1+D2,T> operator *(Polynomial<D1,T> const & p1,Polynomial <D2,T> const & p2)
{
  T prod;
  std::vector<T> tmp(D1+D2+1,0);  

  for(std::size_t i=0;i<=p1.realD;i++){ 
	for(std::size_t j=0;j<=p2.realD;j++){	
		prod=p1[i]*p2[j];	
		tmp[j+i]+=prod; 
	  	               	}
	}  

  Polynomial<D1+D2,T> product(tmp);
  return product;
}


//overload /
template<unsigned D1, unsigned D2, typename T>
std::pair<Polynomial<D1-D2,T>, Polynomial<D2-1,T> > operator /(Polynomial<D1,T> const & p, Polynomial<D2,T> const & d)
{ 
  if(d.realD>p.realD) 
	throw std::runtime_error("you can't divide by zero ");
  if(static_cast<int>(D1-D2)<0)
	throw std::runtime_error("you can't create a result Polynomial of negative degree ");
    if(static_cast<int>(D1-D2)<(p.realD-d.realD))
	throw std::runtime_error("The difference of the template parameters should be at least like the one beetwen the real degree");

  int divOrder=p.realD-d.realD;
  Polynomial<D1-D2,T> result;
  Polynomial<D1,T> tmp(p); 
  Polynomial<D2-1,T> diff;
  int const ds=static_cast<int>(d.realD);
  int ps=static_cast<int>(p.realD); 

  while(ps>=ds){
	result[divOrder]=tmp[ps]/d[ds];
	std::vector<T> prod(divOrder+d.realD+1,0);
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

std::pair<Polynomial<D1-D2,T>, Polynomial<D2-1,T> > out=std::make_pair(result,diff);

return out;
}

//partial specialization for division of Polynomials with integer coefficients that can give a Polynomial with double coefficients.
template<unsigned D1, unsigned D2>
std::pair<Polynomial<D1-D2,double>, Polynomial<D2-1,double> > operator /(Polynomial<D1,int> const & p, Polynomial<D2,int> const & d)
{ if(d.realD>p.realD) 
	throw std::runtime_error("you can't divide by zero ");
  if(static_cast<int>(D1-D2)<0)
	throw std::runtime_error("you can't create a result Polynomial of negative degree ");
    if(static_cast<int>(D1-D2)<(p.realD-d.realD))
	throw std::runtime_error("The difference of the template parameters should be like al least like the one beetwen the real degree");

  int divOrder=p.realD-d.realD;
  Polynomial<D1-D2,double> result;
  Polynomial<D1,double> tmp;
  for(std::size_t i=0;i<=D1;i++)
  tmp[i]=static_cast<double>(p.coeff[i]); 
  Polynomial<D2-1,double> diff;
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
std::pair<Polynomial<D1-D2,double>, Polynomial<D2-1,double> > out=std::make_pair(result,diff);

 return out;
}

template <unsigned S,typename L>
std::istream & operator >> (std::istream & str, Polynomial<S,L> & r){
//you must write the polynomial in the following form: 1*x^0+1.32*x^1 ecc so you don't have to miss a term even if the coefficient is zero and you have to specify x^0 for the first term. To end writing you must do a blank space.
//At most you can write a Polynomial of degree 100 but you could generalize it.
//you have to write for example for a double Polynomial of degree2: -0.56*x^0+5.987*x^1+987.4*x^2 and to end writing just a space  

  std::string tmp;
  // Read from stream up to end of line or space char.
  std::getline(str,tmp,' '); 
  std::string::iterator it=tmp.begin();
  int cont=0;
  std::size_t max=tmp.length();
  std::size_t found=0;
  int quantnum=0;
  std::vector<L> c; 
      
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

  r=Polynomial<S,L>(c); 
  return str;
}





 
#endif
