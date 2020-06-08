#include <iostream>
#include <iomanip>
#include "articulo.hpp"
#include "cadena.hpp"
#include "fecha.hpp"

using namespace std;

/*Clase Autor*/
/*Constructor*/
Autor::Autor(const Cadena& nombre, const Cadena& apellido, const Cadena& direccion):nombre_{nombre},apellido_{apellido},direccion_{direccion}{}

/*Clase Articulo*/
/*Constructor*/
Articulo::Articulo(const Articulo::Autores& autores,const Cadena& referencia,const Cadena& titulo,const Fecha& fecha,double precio):ref_{referencia},titulo_{titulo},fecha_{fecha},precio_{precio},autores_{autores}{
	if(autores.empty()){
		throw Autores_vacios();
	}
}

/*Operador ostream*/
ostream& operator<<(ostream& os,const Articulo& A){
	os << "[" << A.referencia() << "] " << "\"" << A.titulo() << "\", de ";

	auto autores=A.autores();
	auto i=autores.begin();

	os << (*i)->apellidos();

	while( ++i != autores.end()){
		os << ", " << (*i)->apellidos();
	}
	os << ". " << std::fixed << A.f_publi().anno()
	   << ". " << std::setprecision(2) << A.precio() << " €"
	   << std::endl << "\t";
	  
	A.impresion_especifica(os);

	return os;
}

/*Clase ArticuloAlmacenable*/
/*Constructor*/
ArticuloAlmacenable::ArticuloAlmacenable(const Articulo::Autores& autores,const Cadena& referencia,const Cadena& titulo,const Fecha& fecha,double precio,size_t stock):Articulo(autores,referencia,titulo,fecha,precio),stock_(stock){}

/*Clase LibroDigital*/
/*Constructor*/
LibroDigital::LibroDigital(const Articulo::Autores& autores,const Cadena& referencia,const Cadena& titulo,const Fecha& fecha,double precio,const Fecha& fechaExp):Articulo(autores,referencia,titulo,fecha,precio),fechaExp_(fechaExp){}

/*Metodo Virtual*/
void LibroDigital::impresion_especifica(ostream& os)const{
	os << "A la venta hasta el " << this->fechaExp_ << ".";
}

/*Clase Libro*/
/*Constructor*/
Libro::Libro(const Articulo::Autores& autores,const Cadena& referencia,const Cadena& titulo,const Fecha& fecha,double precio,size_t pag,size_t stock) : ArticuloAlmacenable(autores,referencia,titulo,fecha,precio,stock),pag_(pag){}

/*Metodo Virtual*/
void Libro::impresion_especifica(ostream& os)const{
	os << pag_ << " págs., " << this->stock_ << " unidades.";
}

/*Clase Cederron*/
/*Constructor*/
Cederron::Cederron(const Articulo::Autores& autores,const Cadena& referencia,const Cadena& titulo,const Fecha& fecha,double precio,size_t tam,size_t stock):ArticuloAlmacenable(autores,referencia,titulo,fecha,precio,stock),tam_(tam){}

/*Metodo Virtual*/
void Cederron::impresion_especifica(ostream& os)const{
	os << tam_ << " MB, " << this->stock_ << " unidades.";
}