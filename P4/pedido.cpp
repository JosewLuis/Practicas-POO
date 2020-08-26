#include <iostream>
#include <iomanip>
#include "pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario-pedido.hpp"

size_t Pedido::total_ = 0;

using namespace std;

/*Clase Pedido*/

/*Constructor*/
Pedido::Pedido(Usuario_Pedido& up,Pedido_Articulo& pa,Usuario& u,const Tarjeta& t,const Fecha& fecha)
:nPedido_{total_+1},importe_{0.},fecha_{fecha},tarjeta_{&t}{
	if(t.titular()!=&u){
		throw Pedido::Impostor(&u);
	}

	if(t.caducidad()<fecha){
		throw Tarjeta::Caducada(t.caducidad());
	}

	if(t.activa()==false){
		throw Tarjeta::Desactivada();
	}

	auto compra=u.compra();

	for(auto i:compra){
		if(ArticuloAlmacenable* articuloAlmacenable=dynamic_cast<ArticuloAlmacenable*>(i.first)){
			if(i.second>articuloAlmacenable->stock()){
				u.compra(*articuloAlmacenable,0);
				throw SinStock(articuloAlmacenable);
			}
			articuloAlmacenable->stock()-=i.second;
			pa.pedir(*this,*articuloAlmacenable,articuloAlmacenable->precio(),i.second);
			importe_+=articuloAlmacenable->precio()*i.second;
		}else {
			LibroDigital* libroDigital=dynamic_cast<LibroDigital*>(i.first);
			if(libroDigital->f_expir()<fecha){
				u.compra(*libroDigital,0);
			}else{
				pa.pedir(*this,*libroDigital,libroDigital->precio(),i.second);
				importe_+=libroDigital->precio()*i.second;
			}				
		}
	}
	
	if(u.compra().empty()){
		throw Pedido::Vacio(&u);
	}
	up.asocia(*this,u);
	
	nPedido_=++total_;
	const_cast<Usuario::Articulos&>(u.compra()).clear();
}

/*Operador ostream*/
ostream& operator<<(ostream& os, const Pedido& pedido){
	os 	<< "Núm. pedido: " << pedido.numero() << endl
    		<< "Fecha:       " << pedido.fecha() << endl
    		<< "Pagado con:  " << pedido.tarjeta()->tipo()
    		<< " n.º: " << pedido.tarjeta()->numero() << endl
    		<< "Importe:     "  
		<< std::fixed << setprecision(2)
		<< pedido.total() << " €" << std::endl;

	  return os;
}