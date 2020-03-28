#include "fecha.hpp"
#include "ctime"
#include "iostream"
#include "locale.h"
#include "iomanip"

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

const char* Fecha::cadena()const noexcept{
	static char* fecha=new char[50];
	time_t tiempo=time(nullptr);
	tm* fechaTiempo=localtime(&tiempo);
	std::locale::global(std::locale(""));

	fechaTiempo->tm_mday=this->dia_;
	fechaTiempo->tm_mon=this->mes_-1;
	fechaTiempo->tm_year=this->ano_-1900;

	mktime(fechaTiempo);
	strftime(fecha,50,"%A %e de %B de %Y",fechaTiempo);

	return fecha;
}


/*Operadores internos*/
//Operador +=.
Fecha& Fecha::operator+=(int dia){
	time_t tiempo=time(nullptr);
	tm* fechaS=localtime(&tiempo);

	fechaS->tm_mday=this->dia_+dia;
	fechaS->tm_mon=this->mes_-1;
	fechaS->tm_year=this->ano_-1900;
	fechaS->tm_hour=12;

	mktime(fechaS);
	this->dia_=fechaS->tm_mday;
	this->mes_=fechaS->tm_mon+1;
	this->ano_=fechaS->tm_year+1900;

	FechaValida();

	return *this;
}

//Operador -=.
Fecha& Fecha::operator-=(int dia){
	return *this+=-dia;
}

//Operador +.
Fecha& Fecha::operator+(int dia){
	return *this+=dia;
}

//Operador -.
Fecha& Fecha::operator-(int dia){
	return *this-=dia;
}

//Operador preincremento ++.
Fecha& Fecha::operator++(){
	return *this+=1;
}

//Operador preincremento --.
Fecha& Fecha::operator--(){
	return *this-=1;
}

//Operador postincremento ++.
Fecha Fecha::operator++(int dia){
	Fecha aux(*this);
	*this+=1;

	return aux;
}

//Operador postincremento --.
Fecha Fecha::operator--(int dia){
	Fecha aux(*this);
	*this-=1;

	return aux;
}


/*Metodos privados*/
//Fecha Valida.
void Fecha::FechaValida(){
	std::locale::global(std::locale());
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
		throw Invalida("Año mayor que 2037.\n");
	}
	if(this->ano_<Fecha::AnnoMinimo){
		throw Invalida("Año menor que 1902.\n");
	}

	switch(this->mes_){
		//Dias 30. 
		case 4:
		case 6:
		case 9:
		case 11:
			if(this->dia_>30 || this->dia_<0){
				throw Invalida("Día introducido inválido.\n");
			}break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			if(this->dia_>31 || this->dia_<0){
				throw Invalida("Día introducido inválido.\n");
			}break;
		case 2:
			//Comprobamos si el ano es bisiesto.
			if(this->ano_%4==0 && (this->ano_%400==0 || this->ano_%100!=0)){
				if(this->dia_>29 || this->dia_<0){
					throw Invalida("Día introducido inválido.\n");
				}
			}else{
				if(this->dia_>28 || this->dia_<0){
					throw Invalida("Día introducido inválido.\n");
				}
			}break;
		default:
			throw Invalida("Mes introducido inválido.\n");
	}
}

/*Operadores externos*/
//Operador ==.
bool operator==(const Fecha& f1,const Fecha& f2)noexcept{
	//Comparamos ano.
	if(f1.anno()!=f2.anno()){
		return false;
	}
	if(f1.mes()!=f2.mes()){
		return false;
	}
	if(f1.dia()!=f2.dia()){
		return false;
	}
	return true;
}

//Operador !=.
bool operator!=(const Fecha& f1,const Fecha& f2)noexcept{
	return !(f1==f2);
}

//Operador <.
bool operator<(const Fecha& f1,const Fecha& f2)noexcept{
	if(f1.anno()<f2.anno()){
		return true;
	}
	if(f1.anno()==f2.anno() && f1.mes()<f2.mes()){
		return true;
	}
	if(f1.anno()==f2.anno() && f1.mes()==f2.mes() && f1.dia()<f2.dia()){
		return true;
	}
	return false;
}

//Operador <=.
bool operator<=(const Fecha& f1,const Fecha& f2)noexcept{
	return (f1<f2 || f1==f2);
}

//Operador >.
bool operator>(const Fecha& f1,const Fecha& f2)noexcept{
	return !(f1<=f2);
}

//Operador >=.
bool operator>=(const Fecha& f1,const Fecha& f2)noexcept{
	return !(f1<f2);
}

//Operador de extraccion.
ostream& operator<<(ostream& os,const Fecha& f)noexcept{
	os << f.cadena();
	return os;
}

//Operador de inserccion.
istream& operator>>(istream& is,const Fecha& f)noexcept{
	//Tamano correcto de las entradas.
	char fech[11];

	is >> setw(11) >> fech;

	try{
		Fecha f(fech);
	}
	catch(const Fecha::Invalida& e){
		is.setstate(std::ios_base::failbit);
	}

	return is;
}