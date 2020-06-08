#ifndef _USUARIO_PEDIDO_HPP_
#define _USUARIO_PEDIDO_HPP_
#include<map>
#include<set>
#include"usuario.hpp"
#include"pedido.hpp"

class Pedido;
class Usuario;

/*usuario-pedido.hpp*/
using namespace std;

class Usuario_Pedido{
public:
	/*Declaracion de contenedores*/
	typedef set<Pedido*> Pedidos;
	typedef map<Usuario*,Pedidos> UsuarioPedido;
	typedef map<Pedido*,Usuario*> PedidoUsuario;

	/*Asociadores*/
	void asocia(Usuario& U,Pedido& P);
	void asocia(Pedido& P,Usuario& U);

	/*Observadores*/
	//Devuelve Pedidos.
	const Pedidos& pedidos(Usuario& U)const noexcept;
	//Devuelve usuarios.
	const Usuario* cliente(Pedido& P)const noexcept;
private:
	/*Atributos*/
	UsuarioPedido UsuarioPedido_;
	PedidoUsuario PedidoUsuario_;
};

#endif
