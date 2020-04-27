#include"tarjeta.hpp"
#include<iostream>
#include"luhn.cpp"

/*Clase Numero*/

/*Tipo Razon*/
typedef typename Numero::Incorrecto::Razon razon;

/*Constructores*/
Numero::Numero(const Cadena& numero):numero(numero){
	int count=0;
	//Comprobamos que sean numeros/espacios.
	for(int i=0;i<numero.length() && numero[i]!='\0';i++){
		if(isalpha(numero[i])){
			throw Incorrecto(razon::DIGITOS);
		}
		if(numero[i]!=' '){
			count++;
		}
	}

	Cadena aux(count);

	count=0;
	for(auto it=numero.begin();it!=numero.end();it++){
		if((*it)!=' '){
			aux[count]=(*it);
			count++;
		}
	}
	aux[count]='\0';

	if(aux.length()<13 || aux.length()>19){
		throw Incorrecto(razon::LONGITUD);
	}

	if(!luhn(numero)){
      throw Incorrecto(razon::NO_VALIDO);
	}
}

/*Operadores externos*/
//Operador <.
bool operator <(const Numero& n1,const Numero n2)noexcept{
	return n1<n2;
}


/*Clase Tarjeta*/

typedef typename Tarjeta::Tipo Tipo;

/*Constructores*/
Tarjeta::Tarjeta(const Numero& numero,Usuario& usuario,const Fecha fecha):numero_(numero),usuario(usuario),fecha(fecha),activa_(true){
	Fecha hoy;
	if(fecha<hoy){
		throw Caducada(fecha);
	}

	pair<set<Numero>::iterator,bool>p=this->numeros.insert(numero);
	if(!p.second){
		throw Num_duplicado(numero);
	}

	switch(numero[0]){
		case '4': this->tipo_=Tipo::VISA;break;
    	case '5': this->tipo_=Tipo::Mastercard;break;
	    case '6': this->tipo_=Tipo::Maestro;break;
	    case '3': 
			switch (numero[1]){
        		case '4' | '7': this->tipo_=Tipo::AmericanExpress;break;
		        default: this->tipo_=Tipo::JCB;break;
        	}
    	default: this->tipo_=Tipo::Otro;break;		
	}
}

/*Destructor*/
Tarjeta::~Tarjeta(){
	if(this->usuario!=nullptr){
        const_cast<Usuario*>(this->usuario)->no_es_titular_de(*this);
	}
    
    numeros.erase(this->numero_);	
}

/*Operadores externos*/
//Operador <.
bool operator<(const Tarjeta& T1,const Tarjeta& T2)noexcept{
	return T1.numero()<T2.numero();
}