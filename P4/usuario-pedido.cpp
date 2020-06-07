#include "usuario-pedido.hpp"
#include "pedido.hpp"

/*usuario-pedido.cpp*/
using namespace std;

/*Asociadores*/
void Usuario_Pedido::asocia(Usuario& U,Pedido& P){
	this->UsuarioPedido_[&U].insert(&P);
	this->PedidoUsuario_[&P]=&U;
}

void Usuario_Pedido::asocia(Pedido& P,Usuario& U){
	asocia(U,P);
}

/*Observadores*/
//Devuelve pedidos.
const Usuario_Pedido::Pedidos& Usuario_Pedido::pedidos(Usuario& U)const noexcept{
	return this->UsuarioPedido_.find(&U)->second;
}

//Devuelve usuario.
const Usuario* Usuario_Pedido::cliente(Pedido& P)const noexcept{
	return this->PedidoUsuario_.find(&P)->second;
}
