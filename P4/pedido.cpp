#include"pedido.hpp"
#include<iostream>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<iomanip>

/*pedido.cpp*/
using namespace std;

/*Inicializamos la variable estatica*/
int Pedido::numPedido_=0;

/*Constructores*/
Pedido::Pedido(Usuario_Pedido& up,Pedido_Articulo& pa,Usuario& u,const Tarjeta& t,const Fecha& f):fecha_{f},tarjeta_{&t}{
	this->numero_=this->numPedido_+1;
	if(t.titular()!=&u){
		throw Pedido::Impostor(&u);
	}
	if(t.caducidad()<f){
		throw Tarjeta::Caducada(t.caducidad());
	}
	if(!t.activa()){
		throw Tarjeta::Desactivada();
	}

	auto compra=u.compra();
	for(auto i:compra){
		if(ArticuloAlmacenable* AA=dynamic_cast<ArticuloAlmacenable*>(i.first)){
			if(i.second>AA->stock()){
				u.compra(*AA,0);
				throw SinStock(AA);
			}
			AA->stock()-=i.second;
			pa.pedir(*this,*AA,AA->precio(),i.second);
			this->total_+=AA->precio()*i.second;
		}else{
			LibroDigital* LD=dynamic_cast<LibroDigital*>(i.first);
			if(LD->f_expir()<f){
				u.compra(*LD,0);
			}else{
				pa.pedir(*this,*LD,LD->precio(),i.second);
				this->total_+=LD->precio()*i.second;
			}
		}
	}

	if(u.compra().empty()){
		throw Pedido::Vacio(&u);
	}
	up.asocia(*this,u);

	this->numPedido_++;	
	const_cast<Usuario::Articulos&>(u.compra()).clear();
}

/*Operadores externos*/

//Operador ostream.

ostream& operator<<(ostream& os, const Pedido& P)noexcept{

	Cadena c;

	switch(P.tarjeta()->tipo()){
		case 0:	c="VISA";break;
		case 1: c="Mastercard";break;
		case 2: c="Maestro";break;
		case 3: c="JCB";break;
		case 4: c="AmericanExpress";break;
		case 5: c="indeterminado";break;
        default: c="Error, ninguna tarjeta conocida";		

	}



	os << "Núm. pedido: " << P.numero() << std::endl
	   << "Fecha:       " << P.fecha() << std::endl
       << "Pagado con: Tipo " << c
       << " n.º: "  << P.tarjeta()->numero() << std::endl
       << "Importe:     "  
	   << std::fixed << std::setprecision(2) 							
	   << P.total()	<< " €" << std::endl;

	return os;
}
