#ifndef _CADENA_HPP_
#define _CADENA_HPP_
#include "iostream"
#include "stdexcept"

/*Cadena.hpp*/

class Cadena{
public:
	/*Constructores*/
	//Constructor con 2 elementos.
	explicit Cadena(size_t tam=0,char s=' ');
	//Constructor de copia.
	Cadena(const Cadena& c);
	//Constructor con const char*.
	Cadena(const char* c);

	/*Operadores internos*/
	//Operador const char*.
	operator const char*()const noexcept;
	//Operador +=.
	Cadena& operator+=(const Cadena& c)noexcept;
	//Operador +.
	Cadena& operator+(const Cadena& c)noexcept;
	//Operador [] const.
	const char operator[](int i)const noexcept;
	//Operador [] no const.
	char& operator[](int i)noexcept;

	/*Observadores*/
	//Devuelve Cadena.
	inline char* cad()const noexcept{return this->s_;}
	//Devuelve tam
	inline size_t length()const noexcept{return this->tam_;}
	//Devuelve iesimo elemento con excepciones.
	const char at(int i)const;
	//Devuelve iesimo elemento con excepciones.
	char& at(int i);
	//Metodo substr.
	const char* substr(int ind,int tam)const;
private:
	//Atributos.
	size_t tam_;
	char *s_;
};

/*Operadores externos*/
//Operador ==.
bool operator==(const Cadena& c1,const Cadena& c2)noexcept;
//Operador !=.
bool operator!=(const Cadena& c1,const Cadena& c2)noexcept;
//Operador <.
bool operator<(const Cadena& c1,const Cadena& c2)noexcept;
//Operador <=.
bool operator<=(const Cadena& c1,const Cadena& c2)noexcept;
//Operador >.
bool operator>(const Cadena& c1,const Cadena& c2)noexcept;
//Operador >=.
bool operator>=(const Cadena& c1,const Cadena& c2)noexcept;

#endif