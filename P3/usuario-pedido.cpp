#include "usuario-pedido.hpp"
#include "pedido.hpp"

/*usuario-pedido.cpp*/
using namespace std;

/*Asociadores*/
void Usuario_Pedido::asocia(const Usuario& U,const Pedido& P){
	this->UsuarioPedido_[&U].insert(&P);
	this->PedidoUsuario_[&P]=&U;
}

void Usuario_Pedido::asocia(const Pedido& P,const Usuario& U){
	asocia(U,P);
}

/*Observadores*/
//Devuelve pedidos.
const Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(const Usuario& U)noexcept{ 
	return this->UsuarioPedido_.find(&U)->second; 
}

//Devuelve usuario.
const Usuario* Usuario_Pedido::cliente(const Pedido& P)noexcept{
	return this->PedidoUsuario_.find(&P)->second;
}