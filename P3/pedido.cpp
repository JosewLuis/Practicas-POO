#include"pedido.hpp"
#include<iostream>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip>

/*pedido.cpp*/
using namespace std;

/*Constructores*/
Pedido::Pedido(const Usuario_Pedido& up,const Pedido_Articulo& pa,const Usuario& u,const Tarjeta& t,const Fecha& f):fecha_{f},tarjeta_{&t}{
	if(u.compra().empty()){
		throw Pedido::Vacio(&u);
	}
	if(t.titular()!=&u){
		throw Pedido::Impostor(&u);
	}
	if(t.caducidad()<Fecha()){
		throw Tarjeta::Caducada(t.caducidad());
	}
	if(!tarjeta.activa()){
		throw Tarjeta::Desactivada();
	}

	//Primero comprobar que haya stock para comprarlo todo.
	for(auto i=u.compra().begin();i!=u.compra().end();i++){
		if(i->second>i->first->stock()){
			const_cast<Usuario::Articulos&>(u.compra()).clear();
			throw Pedido::SinStock(i->first);
		}else{

		}
	}

	up.asocia(*this,u);
	this->importe_=0;

	for(auto i=u.compra().begin();i!=u.compra().end();i++){
		this->importe_+=i->second*i->first->precio();
		pa.pedir(*i->first,*this,i->first->precio(),i->second);
		i->first->stock()-=i->second;
	}

	this->nPedido_=++this->total_;
	const_cast<Usuario::Articulos&>(u.compra()).clear();
}

/*Operadores externos*/
//Operador ostream.
ostream& operator<<(ostream& os,const Pedido& P)noexcept{
	os << "Núm. pedido: " << P.numero() << std::endl;
   	os << "Fecha:       " << P.fecha() << std::endl;
   	os << "Pagado con:  " << P.tarjeta()->tipo();
   	os << " n.º: " << P.tarjeta()->numero() << std::endl;
   	os << "Importe:     ";
	os << std::fixed << std::setprecision(2);
	os << pedido.total() << " €" << std::endl;
	return os;
}