#ifndef _USUARIO_HPP_
#define _USUARIO_HPP_
#include"unistd.h"
#include"articulo.hpp"
#include"tarjeta.hpp"
#include"cadena.hpp"
#include<map>
#include<utility>
#include<unordered_map>
#include<unordered_set>
#include<random>

using namespace std;

class Tarjeta;
class Numero;

/*usuario.cpp*/

//Clase Clave.
class Clave{
public:
	/*Constructores*/
	//Constructor.
	Clave(const char* texto);
	enum Razon{CORTA,ERROR_CRYPT};

	/*Clase Incorrecta*/
	class Incorrecta{
	public:
		Incorrecta(Razon razon):razon_(razon){}
		inline Razon razon()const noexcept{return this->razon_;}
	private:
		/*Atributos*/
		Razon razon_;
	};

	/*Observadores*/
	//Devuelve Cadena.
	inline Cadena clave()const noexcept{return this->cifrada_;}
	//Verifica.
	bool verifica(const char* texto)const;
private:
	/*Atributos*/
	Cadena cifrada_;
};


//Clase Usuario.
class Usuario{
public:
	/*Tipo para la Clase*/
	typedef map<Numero,Tarjeta*> Tarjetas;
	typedef	unordered_map<Articulo*,unsigned int> Articulos;

	/*Constructores*/
	explicit Usuario(const Cadena& id,const Cadena& nombre,const Cadena& apell,const Cadena& direccion,const Clave& clave);
	Usuario(const Usuario& U)=delete;
	Usuario& operator=(const Usuario& U)=delete;

	/*Destructor*/
	~Usuario();

	/*Clase Id_duplicado*/
	class Id_duplicado{
    public:
        Id_duplicado(const Cadena& c):id(c){}
        Cadena idd()const noexcept{return this->id;}
    private:
        Cadena id;
    };

    /*Metodos asociativos*/
    //Asocia tarjeta.
    void es_titular_de(const Tarjeta& t)noexcept;
    //Desasocia.
    void no_es_titular_de(const Tarjeta& t)noexcept;
    //Asocia articulo.
    void compra(const Articulo& a,int cantidad=1)noexcept;


    /*Observadores*/
    //Id.
    inline Cadena id()const noexcept{return this->id_;}
    //Nombre.
    inline Cadena nombre()const noexcept{return this->nombre_;}
    //Apellido.
    inline Cadena apellidos()const noexcept{return this->apell_;}
    //Direccion.
    inline Cadena direccion()const noexcept{return this->direccion_;}
    //Tarjetas.
    inline const Tarjetas& tarjetas()const noexcept{return this->Ts;}
    //Compra.
    inline const Articulos& compra()const noexcept{return this->As;}
    //Numero de articulos.
    inline int n_articulos()const noexcept{return this->As.size();}
	//Clave.
	inline Clave contrasena()const noexcept{return this->contrasena_;}

private:
	/*Atributos*/
	Cadena id_,nombre_,apell_,direccion_;
	Clave contrasena_;
	Tarjetas Ts;
	Articulos As;

	static unordered_set<Cadena> usuarios;
};

/*Operadores Externos*/
//Operador ostream
ostream& operator <<(ostream& os,const Usuario& U);
//Mostrar carro.
void mostrar_carro(ostream& os,const Usuario& U);

#endif