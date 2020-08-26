#include"tarjeta.hpp"
#include<iostream>
#include<iomanip>
#include<string.h>
#include<stdlib.h>
//#include"luhn.cpp"

set<Numero> Tarjeta::numeros{};

/*Clase Numero*/

using namespace std;

/*Tipo Razon*/
typedef typename Numero::Razon razon;

/*Constructores*/
Numero::Numero(const Cadena& numero):numero(numero){
	Cadena aux{numero};

	auto EsBlanco=[&](char c)->bool{
		return std::isspace(c);
	};

	auto iterator=std::remove_if(aux.begin(),aux.end(),EsBlanco);

	aux=aux.substr(0,std::distance(aux.begin(),iterator));

	for(auto i=aux.begin();i!=aux.end();i++){
		if(std::find_if(aux.begin(),aux.end(),not1(EsDigito()))!=aux.end()){
			throw Incorrecto(DIGITOS);
		}
	}

	int tam=aux.length();

	if(tam<13 || tam>19){
		throw Incorrecto(LONGITUD);
	}

	if(!luhn(aux)){
		throw Incorrecto(NO_VALIDO);
	}

	this->numero=aux;
}

/*Operadores externos*/
//Operador <.
bool operator <(const Numero& n1,const Numero n2)noexcept{
	return Cadena{n1}<Cadena{n2};
}


/*Clase Tarjeta*/

/*Constructores*/
Tarjeta::Tarjeta(const Numero& numero,Usuario& usuario,const Fecha fecha):numero_{numero},usuario_{&usuario},fecha_{fecha},activa_{true}{
	if(this->fecha_<=Fecha()){
		throw Caducada(fecha);
	}

	pair<set<Numero>::iterator,bool>p=this->numeros.insert(numero);
	if(!p.second){
		throw Num_duplicado(numero);
	}

	switch(numero[0]){
		case '4': this->tipo_=Tarjeta::VISA;break;
    	case '5': this->tipo_=Tarjeta::Mastercard;break;
	    case '6': this->tipo_=Tarjeta::Maestro;break;
	    case '3':
			if(numero[1]=='4' || numero[1]=='7'){ 
				this->tipo_=Tarjeta::AmericanExpress;
			}else{
				this->tipo_=Tarjeta::JCB;
			}break;
			
    	default: this->tipo_=Tarjeta::Otro;break;
	}

	Cadena tf{usuario.nombre()+" "+usuario.apellidos()};

    for(int i=0;i<tf.length();i++){
        tf[i]=toupper(tf[i]);
	}

    this->titular_facial_=tf;

    usuario_->es_titular_de(*this);
}

/*Destructor*/
Tarjeta::~Tarjeta(){
	if(this->usuario_!=nullptr){
        const_cast<Usuario*>(this->usuario_)->no_es_titular_de(*this);
	}

    this->numeros.erase(this->numero_);
}

/*Operadores externos*/
//Operador <.
bool operator<(const Tarjeta& T1,const Tarjeta& T2)noexcept{
	return T1.numero()<T2.numero();
}

//Operador ostream.
ostream& operator <<(ostream& os,const Tarjeta& T){
	os << " " << T.tipo() << " ";
    os << "\n";
	os << T.numero();
	os << "\n";
	os << T.titular_facial();
    os << "\n";
	os << "Caduca: ";
	os << setprecision(2);
	os << ((T.caducidad().mes()<10)?'0':' ');
	os << T.caducidad().mes();
	os << "/";
	os << (T.caducidad().anno()%100) << endl;

    return os;
}

//Operador ostream.
ostream& operator<<(ostream& os,const Tarjeta::Tipo& T){
	switch(T){
		case 0:	os << "VISA";break;
		case 1: os << "Mastercard";break;
		case 2: os << "Maestro";break;
		case 3: os << "JCB";break;
		case 4: os << "AmericanExpress";break;
		case 5: os << "Tipo indeterminado" << endl;
    }
	return os;
}