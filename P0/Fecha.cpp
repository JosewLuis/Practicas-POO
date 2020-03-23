#include "Fecha.hpp"
#include <ctime>
#include "iostream"

/*Fecha.cpp*/

std::time_t tiempo_calendario=std::time(nullptr);
std::tm* tiempo_descompuesto=std::localtime(&tiempo_calendario);
int diaH=tiempo_descompuesto->tm_mday;
int mesH=tiempo_descompuesto->tm_mon+1; 								//tm_mon: 0 (ene)..11 (dic).
int anoH=tiempo_descompuesto->tm_year+1900; 						//tm_year: a~nos desde 1900.

/*Constructores*/
//Constructor con 3 elementos.
Fecha::Fecha(int dia,int mes,int ano):dia_(dia),mes_(mes),ano_(ano){
	FechaValida();
}

//Constructor de copia.
Fecha::Fecha(const Fecha& F){
	this->dia_=F.dia_;
	this->mes_=F.mes_;
	this->ano_=F.ano_;
}

//Constructor const char*.
Fecha::Fecha(const char* c){
	if(sscanf(c,"%d/%d/%d",&dia_,&mes_,&ano_)!=3){
		exit(0);
	}
	FechaValida();
}

/*Observadores*/
//Devuelve Fecha
void Fecha::mostrar()const noexcept{
	std::cout << "Dia: " << this->dia() << " Mes: " << this->mes() << " Ano: " << this->ano() << "." << std::endl;
}


/*Metodos privados*/
//Fecha Valida.
void Fecha::FechaValida(){
	//Asignar valores por defecto.
	if(this->dia_==0){
		this->dia_=diaH;
	}
	if(this->mes_==0){
		this->mes_=mesH;
	}
	if(this->ano_==0){
		this->ano_=anoH;
	}

	//Comprobar que la Fecha sea valida.
	//Comprobamos que no se sale del rango de anos permitodo.
	if(this->ano_>Fecha::AnnoMaximo){
		throw Invalida("Ano mayor que 2037.\n");
	}
	if(this->ano_<Fecha::AnnoMinimo){
		throw Invalida("Ano menor que 1902.\n");
	}

	switch(this->mes_){
		//Dias 30. 
		case 4:
		case 6:
		case 9:
		case 11:
			if(this->dia_>30 || this->dia_<0){
				throw Invalida("Dia introducido invalido.\n");
			}break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if(this->dia_>31 || this->dia_<0){
				throw Invalida("Dia introducido invalido.\n");
			}break;
		case 2:
			//Comprobamos si el ano es bisiesto.
			if(this->ano_%4==0 && (this->ano_%400==0 || this->ano_%100!=0)){
				if(this->dia_>29 || this->dia_<0){
					throw Invalida("Dia introducido invalido.\n");
				}
			}else{
				if(this->dia_>28 || this->dia_<0){
					throw Invalida("Dia introducido invalido.\n");
				}
			}break;
		default:
			throw Invalida("Mes introducido invalido.\n");
	}
}

