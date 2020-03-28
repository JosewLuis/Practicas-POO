#ifndef _CADENA_HPP_
#define _CADENA_HPP_
#include "iostream"
#include "functional"
#include "stdexcept"

using namespace std;

/*Cadena.hpp*/

class Cadena{
public:
	/*Constructores*/
	//Constructor con 2 elementos.
	explicit Cadena(size_t tam=0,char s=' ');
	//Constructor de copia.
	Cadena(const Cadena& c);
	//Constructor de movimiento.
	Cadena(const Cadena&& c);
	//Constructor con const char*.
	Cadena(const char* c);
	//Destructor.
	~Cadena();

	/*Operadores internos*/
	//Operador +=.
	Cadena& operator+=(const Cadena& c)noexcept;
	//Operador =.
	Cadena& operator=(const Cadena& c)noexcept;
	Cadena& operator=(const Cadena&& c)noexcept;
	Cadena& operator=(const char* c)noexcept;
	//Operador [] const.
	const char operator[](int i)const noexcept;
	//Operador [] no const.
	char& operator[](int i)noexcept;

	/*Observadores*/
	//Devuelve Cadena.
	inline char* c_str()const noexcept{return this->s_;}
	//Devuelve tam
	inline size_t length()const noexcept{return this->tam_;}
	//Devuelve iesimo elemento con excepciones.
	const char at(int i)const;
	//Devuelve iesimo elemento con excepciones.
	char& at(int i);
	//Metodo substr.
	Cadena substr(int ind,int tam)const;

	/*Iteradores*/
	//No constantes.
	typedef char* iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	//Constantes.
	typedef const char* const_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	//Funciones de los iteradores.
	//No constantes.
	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();
	//Constantes.
	const_iterator begin()const;
	const_iterator end()const;
	const_iterator cbegin()const;
	const_iterator cend()const;
	const_reverse_iterator rbegin()const;
	const_reverse_iterator rend()const;
	const_reverse_iterator crbegin()const;
	const_reverse_iterator crend()const;
private:
	//Atributos.
	size_t tam_;
	char *s_;
};

/*Operadores externos*/
//Concatenacion.
Cadena operator+(const Cadena& c1,const Cadena& c2)noexcept;
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
//Operador de extraccion.
ostream& operator<<(ostream& os,const Cadena& c)noexcept;
//Operador de inserccion.
istream& operator>>(istream& is,Cadena&& c)noexcept;


#endif