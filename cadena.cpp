#include "cadena.hpp"
#include "iostream"
#include "locale.h"
#include "cstring"

/*Cadena.cpp*/

/*Constructores*/
//Constructor con 3 elementos.
Cadena::Cadena(size_t tam,char s):tam_(tam){
	this->s_=new char[this->tam_+1];	//+ \o.

	for(int i=0;i<this->tam_;i++){
		this->s_[i]=s;
	}
	this->s_[this->tam_]='\0';
}

//Constructor de copia.
Cadena::Cadena(const Cadena& c){
	this->tam_=c.tam_;

	strcpy(this->s_,c.s_);
}

//Constructor con const char*.
Cadena::Cadena(const char* c){
	this->tam_=strlen(c);
	this->s_=new char[this->tam_+1];

	strcpy(this->s_,c);
	this->s_[this->tam_]='\0';
}

/*Operadores internos*/
//Operador const char*.
Cadena::operator const char*()const noexcept{
	return this->s_;
}

//Operador +=.
Cadena& Cadena::operator+=(const Cadena& c)noexcept{
	this->tam_=this->tam_+c.tam_;
	char* aux=new char[this->tam_];

	strcpy(aux,this->s_);
	strcat(aux,c.s_);
	strcat(aux,"\0");

	delete[] this->s_;

	this->s_=new char[this->tam_];

	strcpy(this->s_, aux);

	delete[] aux;

	return *this;
}

//Operador +.
Cadena& Cadena::operator+(const Cadena& c)noexcept{
	return *this+=c;
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
	if(i<0 || i>=this->tam_){
		throw std::out_of_range("Índice no válido");
	}
	return this->s_[i];
}

//Devuelve iesimo elemento con excepciones.
char& Cadena::at(int i){
	if(i<0 || i>=this->tam_){
		throw std::out_of_range("Índice no válido");
	}
	return this->s_[i];

}

//Metodo substr.
const char* Cadena::substr(int ind,int tam)const{
	if(ind<0 || ind>=this->tam_ || ind+tam>=this->tam_){
		throw std::out_of_range("Índice no válido");
	}

	char* aux=new char[tam+1];
	int j=0;
	for(int i=ind;i<ind+tam;i++){
		aux[j]=this->s_[i];
	}
	aux[tam]='\0';
	
	return aux;
}

/*Operadores externos*/
//Operador ==.
bool operator==(const Cadena& c1,const Cadena& c2)noexcept{
	return strcmp(c1,c2)==0;
}

//Operador !=.
bool operator!=(const Cadena& c1,const Cadena& c2)noexcept{
	return !(c1==c2);
}

//Operador <.
bool operator<(const Cadena& c1,const Cadena& c2)noexcept{
	return strcmp(c1,c2)<0;
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


