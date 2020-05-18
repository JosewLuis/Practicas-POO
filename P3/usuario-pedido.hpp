#ifndef _USUARIO_PEDIDO_HPP_
#define _USUARIO_PEDIDO_HPP_
#include<map>
#include<set>
#include"usuario.hpp"
#include"pedido.hpp"

/*usuario-pedido.hpp*/
using namespace std;

class Usuario_Pedido{
public:
	/*Declaracion de contenedores*/
	typedef set<Pedido*> Pedidos;
	typedef map<Usuario*,Pedidos> UsuarioPedido;
	typedef map<Pedido*,Usuario*> PedidoUsuario;

	/*Asociadores*/
	void asocia(const Usuario& U,const Pedido& P);
	void asocia(const Pedido& P,const Usuario& U);

	/*Observadores*/
	//Devuelve Pedidos.
	const Pedidos& pedidos(const Usuario& U)noexcept;
	//Devuelve usuarios.
	const Usuario* cliente(const Pedido& P)noexcept;
private:
	/*Atributos*/
	UsuarioPedido usuarioPedido_;
	PedidoUsuario pedidoUsuario_;
};

#endif