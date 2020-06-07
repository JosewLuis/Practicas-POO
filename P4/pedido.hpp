#ifndef _PEDIDO_HPP_
#define _PEDIDO_HPP_
#include<iostream>
#include"usuario.hpp"
#include"tarjeta.hpp"
#include"fecha.hpp"
#include"articulo.hpp"
#include"pedido-articulo.hpp"
#include"usuario-pedido.hpp"

class Usuario_Pedido;
class Pedido_Articulo;
class Tarjeta;

/*pedido.hpp*/
using namespace std;

/*Clase Pedido*/
class Pedido{
public:
	/*Constructores*/
	Pedido(Usuario_Pedido& up,Pedido_Articulo& pa,Usuario& u,const Tarjeta& t,const Fecha& f=Fecha());

	/*Clase de excepcion Vacio*/
	class Vacio{
	public:
		/*Constructor*/
		Vacio(Usuario* U):U_(U){}
		/*Observador*/
		Usuario& usuario()const noexcept{return *this->U_;}
	private:
		/*Atributos*/
		Usuario* U_;
	};

	/*Clase de excepcion Impostor*/
	class Impostor{
	public:
		/*Constructor*/
		Impostor(Usuario* U):U_(U){}
		/*Observador*/
		Usuario& usuario()const noexcept{return *this->U_;}
	private:
		/*Atributos*/
		Usuario* U_;
	};

	/*Clase de excepcion SinStock*/
	class SinStock{
	public:
		/*Constructor*/
		SinStock(Articulo* A):A_(A){}
		/*Observador*/
		Articulo& articulo()const noexcept{return *this->A_;}
	private:
		/*Atributos*/
		Articulo* A_;
	};

	/*Observadores*/
	//Devuelve numero.
	inline int numero()const noexcept{return numero_;}
	//Devuelve tarjeta.
	inline Tarjeta const* tarjeta()const noexcept{return this->tarjeta_;}
	//Devuelve fecha.
	inline Fecha fecha()const noexcept{return this->fecha_;}
	//Devuelve total de pedidos.
	inline double total()const noexcept{return this->total_;}
	//Devuelve numero total.
	inline static int n_total_pedidos()noexcept{return numPedido_;}
private:
	/*Atributos*/
	double total_;
	static int numPedido_;
	int numero_;
	Fecha fecha_;
	Tarjeta const* tarjeta_;
};

/*Operadores externos*/
//Operador ostream.
ostream& operator<<(ostream& os,const Pedido& P)noexcept;


#endif
