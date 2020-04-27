#include<iostream>
#include"articulo.hpp"
#define EURO char(128)

using namespace std;

/*Articulo.cpp*/

/*Constructores*/
//Constructor de 5 parametros.
Articulo::Articulo(const Cadena& ref,const Cadena& titulo,const Fecha& publ,double precio,size_t ejemplares):ref_(ref),titulo_(titulo),public_(publ),
	                                                                                                         precio_(precio),ejemplares_(ejemplares){}

/*Operadores externos*/
//Operador ostream.
ostream& operator <<(ostream& os, const Articulo& A)noexcept{
	os << "[";
	os << A.referencia();
	os << "] \"";
	os << A.titulo();
	os << "\", ";
	os << A.f_publi().anno();
	os << ", ";
	os << A.precio();
	os << " " << EURO;

	return os;
}