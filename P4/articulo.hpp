#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_
#include <iostream>
#include <set>
#include "cadena.hpp"
#include "fecha.hpp"

/*Clase Autor*/
class Autor{
public:
	/*Constructor*/
	Autor(const Cadena& nombre,const Cadena& apellido,const Cadena& direccion);

	/*Observadores*/
	inline Cadena nombre()const noexcept{return this->nombre_;}
	inline Cadena apellidos()const noexcept{return this->apellido_;}
	inline Cadena direccion()const noexcept{return this->direccion_;}

private:
	/*Atributos*/
	Cadena nombre_,apellido_,direccion_;
};

/*Clase Articulo*/
class Articulo{
public:
	typedef std::set<Autor*> Autores;

	/*Constructor*/
	explicit Articulo(const Autores& autores,const Cadena& ref,const Cadena& titulo,const Fecha& fecha,double precio);
	virtual ~Articulo()=default;

	class Autores_vacios{};
	
	/*Observadores*/
	inline const Cadena& referencia()const noexcept{return this->ref_;}
	inline const Cadena& titulo()const noexcept{return this->titulo_;}
	inline const Fecha& f_publi()const noexcept{return this->fecha_;}
	inline double precio()const noexcept{return this->precio_;}
	inline double& precio()noexcept{return this->precio_;}
	inline const Autores& autores()const{return this->autores_;}

	/*Metodo Virtual*/
	virtual void impresion_especifica(ostream& os)const=0;
private:
	/*Atributos*/
	Cadena ref_;
	Cadena titulo_;
	Fecha fecha_;
	double precio_;
	const Autores autores_;
};

/*Operador externo*/
ostream& operator<<(ostream& os,const Articulo& A);


/*Clase ArticuloAlmacenable*/
class ArticuloAlmacenable:public Articulo{
public:
	/*Constructor*/
	ArticuloAlmacenable(const Autores& autores,const Cadena& ref,const Cadena& titulo,const Fecha& fecha,double precio,size_t stock=0);

	/*Observador*/
	inline size_t& stock(){return this->stock_;}
	inline size_t stock()const{return this->stock_;}
protected:
	/*Atributos*/
	size_t stock_;
};

/*Clase Libro*/
class Libro:public ArticuloAlmacenable{
public:
	/*Constructor*/
	Libro(const Autores& autores,const Cadena& ref,const Cadena& titulo,const Fecha& fecha,double precio,size_t pag,size_t stock=0);

	/*Observador*/
	inline size_t n_pag()const{return this->pag_;}

	/*Metodo Virtual*/
	void impresion_especifica(ostream& os)const;
private:
	/*Atributos*/
	const size_t pag_;
};

/*Clase Cederron*/
class Cederron:public ArticuloAlmacenable{
public:
	/*Constructor*/
	Cederron(const Autores& autores,const Cadena& ref,const Cadena& titulo,const Fecha& fecha,double precio,size_t pag,size_t stock=0);

	/*Observador*/
	inline unsigned tam() const { return tam_; }

	/*Metodo Virtual*/
	void impresion_especifica(ostream& os)const;
private:
	/*Atributos*/
	unsigned tam_;
};

/*Clase LibroDigital*/
class LibroDigital:public Articulo{
public:
	/*Constructor*/
	LibroDigital(const Autores& autores,const Cadena& ref,const Cadena& titulo,const Fecha& fecha,double precio,const Fecha& fechaExp);

	/*Observador*/
	inline const Fecha& f_expir() const { return fechaExp_; }

	/*Metodo Virtual*/
	void impresion_especifica(std::ostream& o) const;
private:
	/*Atributos*/
	const Fecha fechaExp_;
};

#endif