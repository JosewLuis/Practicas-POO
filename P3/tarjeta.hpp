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

class EsDigito:public std::unary_function<char,bool>{
	public:
		inline bool operator()(char c)const{return isdigit(c);}
};

/*Clase Numero*/
class Numero{
public:
	Numero(const Cadena& numero);
	enum Razon{LONGITUD,DIGITOS,NO_VALIDO};

	/*Clase Invalido*/
	class Incorrecto{
	public:
		Incorrecto(const Razon& razon):razon_(razon){}
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
	enum Tipo{VISA,Mastercard,Maestro,JCB,AmericanExpress,Otro};
	typedef set<Numero> Numeros;

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
    inline const Numero numero()const noexcept{return this->numero_;}
    //Titular.
    inline const Usuario* titular()const noexcept{return this->usuario_;}
    //Caducidad.
    inline const Fecha caducidad()const noexcept{return this->fecha_;}
    //Activa.
    inline const bool activa()const noexcept{return this->activa_;}
    //Tipo.
    inline const Tipo tipo()const{return this->tipo_;}
		//Titular facial
		inline const Cadena titular_facial()const{return this->titular_facial_;}

    inline bool activa(bool b=true)noexcept{this->activa_=b; return this->activa_;}
    inline void anula_titular(){this->usuario_=nullptr; activa(false);}

private:
	/*Atributos*/
	static Numeros numeros;

	Tipo tipo_;
	Numero numero_;
	Usuario* usuario_;
	Fecha fecha_;
	bool activa_;
	Cadena titular_facial_;

	/*Metodos*/
	void anula_titular()const noexcept;
};

/*Operadores externos*/
//Operador <.
bool operator<(const Tarjeta& T1,const Tarjeta& T2)noexcept;
//Operador ostream.
ostream& operator <<(ostream& os,const Tarjeta& T);

#endif
