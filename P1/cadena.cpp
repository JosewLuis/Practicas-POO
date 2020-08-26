#include "cadena.hpp"
#include "iostream"
#include "locale.h"
#include "cstring"
#include "iomanip"

/*Cadena.cpp*/

/*Constructores*/
//Constructor con 2 elementos.
Cadena::Cadena(size_t tam,char s):tam_{tam},s_{new char[tam+1]}{
	memset(this->s_,s,this->tam_);
	this->s_[tam]='\0';
}

//Constructor de copia.
Cadena::Cadena(const Cadena& c):tam_{c.tam_},s_{new char[c.tam_+1]}{
	memcpy(this->s_,c.s_,c.tam_+1);
}

//Constructor de movimiento.
Cadena::Cadena(Cadena&& c):tam_{0},s_{nullptr}{
	*this=move(c);
}

//Constructor con const char*.
Cadena::Cadena(const char* c):tam_{strlen(c)},s_{new char[strlen(c)+1]}{
	memcpy(this->s_,c,this->tam_);
	this->s_[this->tam_]='\0';
}

//Destructor.
Cadena::~Cadena(){
	delete[] s_;
	this->s_=nullptr;
	this->tam_=0;
}

/*Operadores internos*/
//Operador +=.
Cadena& Cadena::operator+=(const Cadena& c)noexcept{
	this->tam_+=c.tam_;

	char* aux=new char[this->tam_+1];

	strcpy(aux,this->s_);
	strcat(aux,c.s_);
	aux[this->tam_]='\0';
	delete[] this->s_;

	this->s_=new char[this->tam_+1];
	memcpy(this->s_,aux,this->tam_+1);

	return *this;
}

//Operador =.
Cadena& Cadena::operator=(const Cadena& c)noexcept{
	//Evitamos autoasignacion.
	if(this!=&c){
		delete[] this->s_;
		this->tam_=c.tam_;
		this->s_=new char[this->tam_+1];
		memcpy(this->s_,c.s_,this->tam_+1);
	}

	return *this;
}

Cadena& Cadena::operator=(Cadena&& c)noexcept{
	//Evitamos autoasignacion.
	if(this!=&c){
		delete[] this->s_;
		this->tam_=c.tam_;
		this->s_=new char[this->tam_+1];
		memcpy(this->s_,c.s_,this->tam_+1);
		c.tam_=0;
		c.s_=nullptr;
	}

	return *this;
}

Cadena& Cadena::operator=(const char* c)noexcept{
	delete[] this->s_;
	this->tam_=strlen(c);
	this->s_=new char[this->tam_+1];
	memcpy(this->s_,c,this->tam_+1);

	return *this;
}

//Operador [] const.
const char Cadena::operator[](int i)const noexcept{
	return this->s_[i];
}

//Operador [] no const.
char& Cadena::operator[](int i)noexcept{
	return this->s_[i];
}

/*Observadores*/
//Devuelve iesimo elemento con excepciones.
const char Cadena::at(int i)const{
	if(i>=this->tam_){
		throw std::out_of_range("Índice no válido");
	}
	return this->s_[i];
}

//Devuelve iesimo elemento con excepciones.
char& Cadena::at(int i){
	if(i>=this->tam_){
		throw std::out_of_range("Índice no válido");
	}
	return this->s_[i];

}

//Metodo substr.
Cadena Cadena::substr(int ind,int tam)const{
	if(ind>this->tam_ || tam>this->tam_-ind){
		throw std::out_of_range("Índice no válido");
	}

	char* aux=new char[tam+1];
	int j=0;
	for(int i=ind;i<=ind+tam;i++){
		aux[j]=this->s_[i];
		j++;
	}
	aux[tam]='\0';

	Cadena c(aux);
	
	return c;
}

/*Iteradores*/
//No constantes.
Cadena::iterator Cadena::begin(){
	return this->s_;
}

Cadena::iterator Cadena::end(){
	return this->s_+this->tam_;
}

Cadena::reverse_iterator Cadena::rbegin(){
	return reverse_iterator(end());
}

Cadena::reverse_iterator Cadena::rend(){
	return reverse_iterator(begin());
}

//Constantes.
Cadena::const_iterator Cadena::begin()const{
	return this->s_;
}

Cadena::const_iterator Cadena::end()const{
	return this->s_+this->tam_;
}

Cadena::const_iterator Cadena::cbegin()const{
	return begin();
}

Cadena::const_iterator Cadena::cend()const{
	return end();
}

Cadena::const_reverse_iterator Cadena::rbegin()const{
	return const_reverse_iterator(cend());
}

Cadena::const_reverse_iterator Cadena::rend()const{
	return const_reverse_iterator(cbegin());
}

Cadena::const_reverse_iterator Cadena::crbegin()const{
	return const_reverse_iterator(end());
}

Cadena::const_reverse_iterator Cadena::crend()const{
	return const_reverse_iterator(begin());
}

/*Operadores externos*/
//Concatenacion.
Cadena operator+(const Cadena& c1,const Cadena& c2)noexcept{
	Cadena aux=c1;
	aux+=c2;

	return aux;
}

//Operador ==.
bool operator==(const Cadena& c1,const Cadena& c2)noexcept{
	return strcmp(c1.c_str(),c2.c_str())==0;
}

//Operador !=.
bool operator!=(const Cadena& c1,const Cadena& c2)noexcept{
	return !(c1==c2);
}

//Operador <.
bool operator<(const Cadena& c1,const Cadena& c2)noexcept{
	return strcmp(c1.c_str(),c2.c_str())<0;
}

//Operador <=.
bool operator<=(const Cadena& c1,const Cadena& c2)noexcept{
	return c1==c2 || c1<c2;
}

//Operador >.
bool operator>(const Cadena& c1,const Cadena& c2)noexcept{
	return !(c1<=c2);
}

//Operador >=.
bool operator>=(const Cadena& c1,const Cadena& c2)noexcept{
	return !(c1<c2);
}

//Operador de extraccion.
ostream& operator<<(ostream& os,const Cadena& c)noexcept{
	os << c.c_str();
	return os;
}

//Operador de inserccion.
istream& operator>>(istream& is,Cadena& c)noexcept{
    char string[33]{"\0"}; 
    is.width(33);
    is >> string;
    
    c=Cadena(string);

    return is;
}