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
	this->s_=new char[this->tam_+1];

	strcpy(this->s_,c.s_);
}

//Constructor con const char*.
Cadena::Cadena(const char* c){
	this->tam_=strlen(c);
	this->s_=new char[this->tam_+1];

	strcpy(this->s_,c);
	this->s_[this->tam_]='\0';
}

//Destructor.
Cadena::~Cadena(){
	delete[] s_;
	tam_=0;
}

/*Operadores internos*/
//Operador const char*.
Cadena::operator const char*()const noexcept{
	return this->s_;
}

//Operador +=.
Cadena& Cadena::operator+=(const Cadena& c)noexcept{
	int tam=this->tam_+c.tam_+1;
	char* buff=new char[tam];

	strcpy(buff,this->s_);
	strcat(buff,c.s_);
	strcat(buff,"\0");

	delete[] this->s_;

	this->tam_=tam;
	this->s_=new char[tam];

	strcpy(this->s_,buff);

	delete[] buff;

	return *this;
}

//Operador =.
Cadena& Cadena::operator=(const Cadena& c)noexcept{
	if(this!=&c){
		delete[] this->s_;
		this->tam_=c.tam_;
		this->s_=new char[this->tam_+1];
		strcpy(this->s_,c.s_);
	}

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
Cadena Cadena::substr(int ind,int tam)const{
	if(ind<0 || ind>=this->tam_ || ind+tam>=this->tam_ || tam<0){
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

/*Operadores externos*/
//Concatenacion.
Cadena operator+(const Cadena& c1,const Cadena& c2)noexcept{
	Cadena aux=c1;
	aux+=c2;

	return aux;
}

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


