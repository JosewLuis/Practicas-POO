#ifndef _PEDIDO_HPP_
#define _PEDIDO_HPP_
#include"tarjeta.hpp"
#include"usuario.hpp"

/*pedido.hpp*/
using namespace std;

/*Clase Pedido*/
class Pedido{
public:
	/*Constructores*/
	Pedido(const Usuario_Pedido& up,const Pedido_Articulo& pa,const Usuario& u,const Tarjeta& t,const Fecha& f=Fecha());

	/*Clase de excepcion Vacio*/
	class Vacio{
	public:
		/*Constructor*/
		Vacio(Usuario* U)U_(U){}
		/*Observador*/
		Usuario& usuario()const noexcept{return *this->U_;}
	private:
		/*Atributos*/
		Usuario* U_;
	}

	/*Clase de excepcion Impostor*/
	class Impostor{
	public:
		/*Constructor*/
		Impostor(Usuario* U)U_(U){}
		/*Observador*/
		Usuario& usuario()const noexcept{return *this->U_;}
	private:
		/*Atributos*/
		Usuario* U_;
	}

	/*Clase de excepcion SinStock*/
	class SinStock{
	public:
		/*Constructor*/
		SinStock(Articulo* A)A_(A){}
		/*Observador*/
		Articulo& usuario()const noexcept{return *this->A_;}
	private:
		/*Atributos*/
		Articulo* A_;
	}

	/*Observadores*/
	//Devuelve numero.
	inline int numero()const noexcept{return this->numPedido_;}
	//Devuelve tarjeta.
	inline Tarjeta const* tarjeta()const noexcept{return this->tarjeta_;}
	//Devuelve fecha.
	inline Fecha& fecha()const noexcept{return this->fecha_;}
	//Devuelve total.
	inline int total()const noexcept{return this->importe_;}
	//Devuelve total de pedidos.
	inline int n_total_pedidos()const noexcept{return this->total_;}
private:
	/*Atributos*/
	static int total_;
	int numPedido_;
	double importe_;
	Fecha fecha_;
	Tarjeta const* tarjeta_;
};

/*Operadores externos*/
//Operador ostream.
ostream& operator<<(ostream& os,const Pedido& P)noexcept;


#endif