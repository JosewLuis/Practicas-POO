#ifndef _TARJETA_HPP_
#define _TARJETA_HPP_
#include<cctype>
#include<algorithm>
#include<set>
#include"fecha.hpp"
#include"cadena.hpp"
#include"usuario.hpp"

using namespace std;

bool luhn(const Cadena& numero);
class Usuario;

/*Clase Numero*/
class Numero{
public:
	Numero(const Cadena& numero);

	/*Clase Invalido*/
	class Incorrecto{
	public:
		enum Razon{LONGITUD,DIGITOS,NO_VALIDO};
		Incorrecto(Razon razon):razon_(razon){}
		inline Razon razon()const noexcept{return this->razon_;}	
	private:
		/*Atributos*/
		Razon razon_;
	};

	/*Operadores internos*/
	//Operador const char*.
	inline operator const char*()const noexcept{return this->numero.c_str();}

private:
	/*Atributos*/
	Cadena numero;
};

/*Operadores externos*/
//Operador <.
bool operator <(const Numero& n1,const Numero n2)noexcept;

/*Clase Trajeta*/
class Tarjeta{
public:
	enum Tipo{Otro,VISA,Mastercard,Maestro,JCB,AmericanExpress};

	/*Constructores*/
	explicit Tarjeta(const Numero& numero,Usuario& usuario,const Fecha fecha);
	Tarjeta(const Tarjeta& T)=delete;
	Tarjeta& operator=(const Tarjeta& T)=delete;

	/*Destructor*/
	~Tarjeta();

	/*Clase Caducada*/
	class Caducada{
	public:
		Caducada(const Fecha& caducada):caducada_(caducada){}
		Fecha cuando()const noexcept{return this->caducada_;}
	private:
		/*Atributos*/
		Fecha caducada_;
	};

	/*Clase Num_duplicado*/
	class Num_duplicado{
    public:
        Num_duplicado(const Numero& N):n(N){}
        Numero que()const noexcept{return this->n;}
    private:
    	/*Atributos*/
        Numero n;
    };

    /*Clase Desactivada*/
    class Desactivada{
    public:

    private:
    	/*Atributos*/
    };

    /*Observadores*/
    //Numero.
    const Numero numero()const noexcept{return this->numero_;}
    //Titular.
    const Usuario* titular()const noexcept{return this->usuario;}
    //Caducidad.
    const Fecha caducidad()const noexcept{return this->fecha;}
    //Activa.
    bool activa()const noexcept{return this->activa_;}
    //Tipo.
    Tipo tipo(){return this->tipo_;}

    inline void activa(bool b=true)noexcept{this->activa_=b;}
    inline void anula_titular(){this->usuario=nullptr; activa(false);}

private:
	/*Atributos*/
	Tipo tipo_;
	const Numero numero_;
	const Usuario* usuario;
	const Fecha fecha;
	bool activa_;
	static set<Numero> numeros;

	/*Metodos*/
	void anula_titular()const noexcept;
};

/*Operadores externos*/
//Operador <.
bool operator<(const Tarjeta& T1,const Tarjeta& T2)noexcept;

#endif