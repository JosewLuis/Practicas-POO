#include<iostream>
#include<iomanip>
#include"articulo.hpp"

using namespace std;

/*Articulo.cpp*/

/*Constructores*/
//Constructor de 5 parametros.
Articulo::Articulo(const Cadena& ref,const Cadena& titulo,const Fecha& publ,double precio,unsigned ejemplares):ref_(ref),titulo_(titulo),public_(publ),
	                                                                                                         precio_(precio),ejemplares_(ejemplares){}

/*Operadores externos*/
//Operador ostream.
ostream& operator<<(ostream& os, const Articulo& A)noexcept{
	os << "[" << A.referencia() << "] ''" << A.titulo() << "'', " << A.f_publi().anno() << ". " << fixed << setprecision(2) << A.precio() << " €";
	return os;
}
