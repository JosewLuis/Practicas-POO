#ifndef _ARTICULO_HPP_
#define _ARTICULO_HPP_
#include<iostream>
#include"cadena.hpp"
#include"fecha.hpp"

using namespace std;

/*Clase Autor*/

class Autor{
public:
	/*Constructor*/
	Autor(const Cadena& nombre,const Cadena& apellido,const Cadena& direccion);

	/*Observadores*/
	//Nombre.
	inline Cadena nombre()const noexcept{ return this->nombre_; 	}
	//Apellidos.
	inline Cadena apellidos() const noexcept { return this->apellido_;  }
	//Direccion.
	inline Cadena direccion() 	const noexcept { return this->direccion_; }

private:
	/*Atributos*/
	Cadena nombre_,apellido_,direccion_;
};


/*Clase Articulo*/

class Articulo{
public:
	/*Constructores*/
	//Constructor de 5 parametros.
	Articulo(const Autor& autores,const Cadena& ref,const Cadena& titulo,const Fecha& publ,double precio);

	typedef std::set<Autor*> Autores;

	/*Observadores*/
	//Referencia.
	inline const Cadena& referencia()const noexcept{return this->ref_;}
	//Titulo.
	inline const Cadena& titulo()const noexcept{return this->titulo_;}
	//Fecha.
	inline const Fecha& f_publi()const noexcept{return this->public_;}
	//Precio.
	inline double precio()const noexcept{return this->precio_;}
	//Ref a Precio.
	inline double& precio()noexcept{return this->precio_;}
	//Ejemplares.
	inline unsigned stock()const noexcept{return this->ejemplares_;}
	//Ref a Ejemplares.
	inline unsigned& stock()noexcept{return this->ejemplares_;}

	/*Metodo virtual*/
	virtual void impresion_especifica(ostream& os)const=0;
private:
	/*Atributos*/
	Cadena ref_,titulo_;
	Fecha public_;
	double precio_;
	const Autores autores_;
};


/*Operadores externos*/
//Operador ostream.
ostream& operator<<(ostream& os, const Articulo& A)noexcept;

/*Clase ArticuloAlmacenable*/

class ArticuloAlmacenable:public Articulo{
public:
	/*Constructor*/
	ArticuloAlmacenable(const Autores& autores,const Cadena& ref,const Cadena& titulo,const Fecha& publ,double precio,size_t stock=0);

	/*Observadores*/
	inline size_t& stock(){ return this->stock_; }
	inline size_t stock()const{ return this->stock_; }
protected:
	size_t stock_;
};


/*Clase Libro*/
class Libro:public ArticuloAlmacenable{
public:
	/*Costructor*/
	Libro(const Autores& autores,const Cadena& ref,const Cadena& titulo,const Fecha& publ,double precio,size_t pag,size_t stock=0);

	/*Observador*/
	inline size_t n_pag()const{ return this->pag_; }

	/*Metodo Virtual*/
	void impresion_especifica(ostream& os)const;
private:
	const size_t pag_;
};


/*Cederron*/

class Cederron:public ArticuloAlmacenable{
public:
	/*Constructor*/
	Cederron(const Autores& autores,const Cadena& ref,const Cadena& titulo,const Fecha& publ,double precio,size_t pag,size_t stock=0);

	/*Observador*/
	inline size_t tam()const{ return this->tam_; }

	/*Metodo Virtual*/
	void impresion_especifica(ostream& os)const;
private:
	size_t tam_;
};

/*LibroDigital*/

class LibroDigital:public Articulo{
public:
	/*Constructor*/
	LibroDigital(const Autores& autores,const Cadena& ref,const Cadena& titulo,const Fecha& publ,double precio,const Fecha& fechaExp);

	/*Observador*/
	inline const Fecha& f_expir()const{ return this->fechaExp_; }

	/*Metodo Virtual*/
	void impresion_especifica(ostream& os)const;
private:
	const Fecha fechaExp_;
}

#endif