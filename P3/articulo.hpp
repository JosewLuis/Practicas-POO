#ifndef _ARTICULO_HPP_
#define _ARTICULO_HPP_
#include<iostream>
#include"cadena.hpp"
#include"fecha.hpp"

using namespace std;

/*Clase Articulo*/

class Articulo{
public:
	/*Constructores*/
	//Constructor de 5 parametros.
	Articulo(const Cadena& ref,const Cadena& titulo,const Fecha& publ,double precio,size_t ejemplares=0);

	/*Observadores*/
	//Referencia.
	inline const Cadena referencia()const noexcept{return this->ref_;}
	//Titulo.
	inline const Cadena titulo()const noexcept{return this->titulo_;}
	//Fecha.
	inline const Fecha f_publi()const noexcept{return this->public_;}
	//Precio.
	inline double precio()const noexcept{return this->precio_;}
	//Ref a Precio.
	inline double& precio()noexcept{return this->precio_;}
	//Ejemplares.
	inline size_t stock()const noexcept{return this->ejemplares_;}
	//Ref a Ejemplares.
	inline size_t& stock()noexcept{return this->ejemplares_;}

private:
	/*Atributos*/
	Cadena ref_,titulo_;
	Fecha public_; 
	double precio_;
	size_t ejemplares_;
};


/*Operadores externos*/
//Operador ostream.
ostream& operator <<(ostream& os, const Articulo& A)noexcept;

#endif