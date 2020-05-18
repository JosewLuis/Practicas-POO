#include <iostream>
#include <iomanip>
#include "pedido-articulo.hpp"

/*pedido-articulo.cpp*/
using namespace std;

/*Clase LineaPedido*/

/*Operadores externos*/
//Operador ostream.
ostream& operator<<(ostream& os,const LineaPedido& LP){
	os << std::fixed << std::setprecision(2);
	os << lineaPedido.precio_venta();
	os << " €\t" << lineaPedido.cantidad();

	return os;
}

/*Clase Pedido_Articulo*/

/*Asociadores*/
void Pedido_Articulo::pedir(const Pedido& P,const Articulo& A,double precio,size_t cant){
	PedidoArticulo_[&P].insert(std::make_pair(&A,LineaPedido(precio,cant)));
  	ArticuloPedido_[&A].insert(std::make_pair(&P,LineaPedido(precio,cant)));
}

void Pedido_Articulo::pedir(const Articulo& A,const Pedido& P,double d,size_t cant){
	pedir(P,A,d,cant);
}

/*Observadores*/
const Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(const Pedido& P)const noexcept{
	return this->PedidoArticulo_.find(&P)->second;
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(const Articulo& A)const noexcept{
	if(this->ArticuloPedido_.find(&A)!=this->ArticuloPedido_.end())
    	return this->ArticuloPedido_.find(&A)->second;
  	else {
		Pedido_Articulo::Pedidos vacio;
		return vacio;
  	}
}

/*ostream con detalles*/
ostream& Pedido_Articulo::mostrarDetallePedidos(ostream& os)const noexcept{
	double total=0;

	for(auto i=this->PedidoArticulo_.begin();i!=this->PedidoArticulo_.end();i++){
		os << "Pedido núm. " << i->first->numero() << std::endl;
		os << "Cliente: " << i->first->tarjeta()->titular()->nombre();
		os << "\tFecha: " << i->first->fecha() << std::endl;
		os << i->second << std::endl;

		total+=i->first->total();
	}

	os << "TOTAL VENTAS\t" << std::fixed;
	os << std::setprecision(2);
	os << total << " €" << std::endl;
	
	return o;
}

ostream& Pedido_Articulo::mostrarVentasArticulos(ostream& os)const noexcept{
	for(auto i=this->ArticuloPedido_.begin();i!=this->ArticuloPedido_.end();i++){
		os << "Ventas de " << "[" << i->first->referencia() << "] ";
		os << "\"" << i->first->titulo() << "\"" << std::endl;
		os << i->second << std::endl;
	}

	return os;
}

/*Operadores externos*/
ostream& operator<<(ostream& os,const Pedido_Articulo::ItemsPedido& IP){
	double total=0;

	os << std::endl;
	os << "  PVP\tCantidad\tArticulo" << std::endl;
	os << "==================================================================" << std::endl;

	for(auto i=IP.begin();i!=IP.end();i++){
		os << i->second.precio_venta() << " €\t";
		os << i->second.cantidad() << "\t\t";
		os << "[" << i->first->referencia() << "] ";
		os << "\"" << i->first->titulo() << "\" " << std::endl;

		total+=i->second.precio_venta()*i->second.cantidad();
	}
	os << "==================================================================" << std::endl;
	os << "Total\t" << std::fixed << std::setprecision(2) << total << " €" << std::endl;

 	return os;
}

ostream& operator<<(ostream& os,const Pedido_Articulo::Pedidos& P){
	double precio=0;
	unsigned total=0;

	os << "[Pedidos: " << P.size() << "]" << std::endl;
	os << "==================================================================" << std::endl;
	os << "  PVP\tCantidad\tFecha de venta" << std::endl;
	os << "==================================================================" << std::endl;

	for(auto i:P){
		os << i.second.precio_venta() << " €\t";
		os << i.second.cantidad() << "\t";
		os << i.first->fecha() << std::endl;

		precio+=i.second.precio_venta()*i.second.cantidad();
		total+=i.second.cantidad();
	}

	os << "==================================================================" << std::endl;
	os << std::fixed;
	os << std::setprecision(2) << precio << " €\t" << total << std::endl;

	return os;
}
