#include<iostream>
#include<iomanip>
#include"articulo.hpp"

using namespace std;

/*Articulo.cpp*/

/*Autor*/
Autor::Autor(const Cadena& nombre,const Cadena& apellido,const Cadena& direccion):nombre_{nombre},apellido_{apellido},direccion_{direccion}{}

/*Articulo*/
/*Constructores*/
//Constructor de 5 parametros.
Articulo::Articulo(const Autor& autores,const Cadena& ref,const Cadena& titulo,const Fecha& publ,double precio):autores_(autores),ref_(ref),titulo_(titulo),public_(publ),precio_(precio){}

/*Operadores externos*/
//Operador ostream.
ostream& operator<<(std::ostream& os,const Articulo& A) {
	os << "[" << A.referencia() << "] " << "\"" << A.titulo() << "\", de ";

	auto autores=A.autores();
	auto i=A.begin();

	os << (*i)->apellidos();

	while(i++!=A.end()){
		os << ", " << (*i)->apellidos();
	}

	os << ". "  << std::fixed << A.f_publi().anno()
	   << ". " 	<< std::setprecision(2) << A.precio() << " €"
	   << std::endl << "\t";
	  
	A.impresion_especifica(o);

	return os;
}

/*ArticuloAlmacenable*/
/*Constructor*/
ArticuloAlmacenable::ArticuloAlmacenable(const Articulo::Autores& autores,const Cadena& ref,const Cadena& titulo,const Fecha& publ,double precio,size_t stock):Articulo(autores,ref,titulo,publ,precio),
                                                                                                                                                               stock_(stock){}

/*Libro*/
/*Constructor*/
Libro::Libro(const Articulo::Autores& autores,const Cadena& ref,const Cadena& titulo,const Fecha& publ,double precio,size_t pag,size_t stock):ArticuloAlmacenable(autores,ref,titulo,publ,precio,stock),
    																																          pag_(pag){}

/*Metodo Virtual*/																																  
void Libro::impresion_especifica(std::ostream& os)const{
	os << this->pag_ << " págs., " << this->stock_ << " unidades.";
}

/*Cederron*/
/*Constructor*/
Cederron::Cederron(const Articulo::Autores& autores,const Cadena& ref,const Cadena& titulo,const Fecha& publ,double precio,size_t tam,size_t stock):ArticuloAlmacenable(autores,ref,titulo,publ,precio,stock),
                                                                                                                                                    tam_(tam){}

/*Metodo Virtual*/
void Cederron::impresion_especifica(ostream& os)const{
	os << this->tam_ << " MB, " << this->stock_ << " unidades.";
}

/*LibroDigital*/
/*Constructor*/
LibroDigital::LibroDigital(const Articulo::Autores& autores,const Cadena& ref,const Cadena& titulo,const Fecha& publ,double precio,const Fecha& fechaExp):Articulo(autores,ref,titulo,publ,precio),
																																						 fechaExp_(fechaExp_){}

/*Metodo Virtual*/
void LibroDigital::impresion_especifica(ostream& os)const{
	os << "A la venta hasta el " << this->fechaExp_ << ".";
}