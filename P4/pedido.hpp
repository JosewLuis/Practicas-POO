#ifndef PEDIDO_HPP
#define PEDIDO_HPP
#include <iostream>
#include "usuario.hpp"
#include "tarjeta.hpp"
#include "fecha.hpp"
#include "articulo.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

class Usuario_Pedido;
class Pedido_Articulo;
class Tarjeta;

using namespace std;

/*Clase Pedido*/
class Pedido {
public:
	/*Constructor*/
	Pedido(Usuario_Pedido& up,Pedido_Articulo& pa,Usuario& u,const Tarjeta& t,const Fecha& fecha=Fecha());

	/*Clase excepcion Vacio*/
	class Vacio{
	public:
		/*Constructor*/
		Vacio(Usuario* usuario):usuario_(usuario){}
		/*Observador*/
		const Usuario& usuario()const{return *usuario_;}
	private:
		/*Atributos*/
		Usuario* usuario_;
	};
		
	/*Clase excepcion Impostor*/
	class Impostor{
	public:
		/*Constructor*/
		Impostor(Usuario* usuario):usuario_(usuario){}
		/*Observador*/
		const Usuario& usuario()const{return *usuario_;}
	private:
		/*Atributos*/
		Usuario* usuario_;
	};

	/*Clase excepcion SinStock*/
	class SinStock{
	public:
		/*Constructor*/
		SinStock(Articulo* articulo):articulo_(articulo){}
		/*Observador*/
		const Articulo& articulo()const{return *articulo_;}
	private:
		/*Atributos*/
		Articulo* articulo_;
	};

	/*Observadores*/
	//Devuelve numero.
	inline size_t numero()const{return this->nPedido_;}
	//Devuelve la tarjeta.
	inline Tarjeta const* tarjeta()const{return this->tarjeta_;}
	//Devuelve fecha.
	inline const Fecha& fecha()const{return this->fecha_;}
	//Devuelve total.
	inline double total()const{return this->importe_;}
	//Devuelve total de pedidos.
	inline static size_t n_total_pedidos(){return total_;}
private:
	/*Atributos*/
	size_t nPedido_;
	double importe_;
	static size_t total_;
	Fecha fecha_;
	Tarjeta const* tarjeta_;
};

/*Operadores externos*/
//Operador ostream.
ostream& operator<<(ostream& os,const Pedido&);

#endif