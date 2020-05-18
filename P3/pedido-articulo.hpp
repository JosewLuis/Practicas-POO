#ifndef _PEDIDO_ARTICULO_HPP_
#define _PEDIDO_ARTICULO_HPP_
#include<algorithm>
#include<map>
#include"articulo.hpp"
#include"pedido.hpp"

class Pedido;
class Articulo;

/*pedido-articulo.hpp*/

/*Clase LineaPedido*/
class LineaPedido{
public:
	/*Constructores*/
	explicit inline LineaPedido(double pv,size_t cv):precioVenta_(pv),cantidadVendida_(cv){}

	/*Observadores*/
	//Devuelve precio de venta.
	inline double precio_venta()const noexcept{return this->precioVenta_;}
	//Devuelve cantidad vendida.
	inline size_t cantidad()const noexcept{return this->cantidadVendida_;}
private:
	/*Atributos*/
	double precioVenta_;
	size_t cantidadVendida_;
};

/*Operadores externos*/
//Operador ostream.
ostream& operator<<(ostream& os,const LineaPedido& LP);

/*Clase OrdenaArticulos*/
class OrdenaArticulos:public std::binary_function<Articulo*,Articulo*,bool>{
public:
  	inline bool operator()(const Articulo* A1,const Articulo* A2)const noexcept{return(A1->referencia()<A2->referencia());}
};

/*Clase OrdenaPedidos*/
class OrdenaPedidos:public std::binary_function<Pedido*,Pedido*,bool> {
public:
	bool operator()(const Pedido* P1,const Pedido* P2)const noexcept{return P1->numero()<P2->numero();}
};


/*Clase Pedido_Articulo*/
class Pedido_Articulo{
public:
	/*Contenedores*/
	typedef map<Articulo*,LineaPedido,OrdenaArticulos> ItemsPedido;
	typedef map<Pedido*,ItemsPedido,OrdenaPedidos> PedidoArticulo;
	typedef map<Pedido*,LineaPedido,OrdenaPedidos> Pedidos;
	typedef map<Articulo*,Pedidos,OrdenaArticulos> ArticuloPedido;

	/*Asociadores*/
	void pedir(const Pedido& P,const Articulo& A,double precio,size_t cant=1);
	void pedir(const Articulo& A,const Pedido& P,double precio,size_t cant=1);

	/*Observadores*/
	const ItemsPedido& detalle(const Pedido& P)const noexcept;
	Pedidos ventas(const Articulo& A)const noexcept;

	/*ostream con detalles*/
	ostream& mostrarDetallePedidos(ostream& os)const noexcept;
	ostream& mostrarVentasArticulos(ostream& os)const noexcept;
private:
	/*Atributos*/
	PedidoArticulo PedidoArticulo_;
	ArticuloPedido ArticuloPedido_;
};

/*Operadores externos*/
ostream& operator<<(ostream& os,const Pedido_Articulo::ItemsPedido& IP);
ostream& operator<<(ostream& os,const Pedido_Articulo::Pedidos& P);

#endif