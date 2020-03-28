#ifndef _FECHA_HPP_
#define _FECHA_HPP_
#include "iostream"

using namespace std;

/*Fecha.cpp*/

class Fecha{
public:
	/*Constructores*/
	//Constructor con 3 elementos.
	explicit Fecha(int dia=0,int mes=0,int ano=0);
	//Constructor de copia.
	Fecha(const Fecha& F);
	//Constructo const char*.
	Fecha(const char* c);

	/*Clase Invalida*/
	class Invalida{
	public:
		Invalida(const char* error){
			this->error_=error;
		}
		const char* por_que()const{
			return this->error_;	
		}
	private:
		const char* error_;
	};

	//Conversor a const char*.
	const char* cadena()const noexcept;

	/*Operadores internos*/
	//Operador +=.
	Fecha& operator+=(int dia);
	//Operador -=.
	Fecha& operator-=(int dia);
	//Operador +.
	Fecha operator+(int dia)const;
	//Operador -.
	Fecha operator-(int dia)const;
	//Operador preincremento ++.
	Fecha& operator++();
	//Operador preincremento --.
	Fecha& operator--();
	//Operador postincremento ++.
	Fecha operator++(int dia);
	//Operador postincremento --.
	Fecha operator--(int dia);

	/*Observadores*/
	//Devuelve dia.
	inline int dia()const noexcept{return this->dia_;}
	//Devuelve mes.
	inline int mes()const noexcept{return this->mes_;}
	//Devuelve ano.
	inline int anno()const noexcept{return this->ano_;}
	//Devuelve fecha.
	inline void mostrar()const noexcept{std::cout << "Dia: " << this->dia() << " Mes: " << this->mes()  << " Ano: " << this->anno() << ".\n";}

	/*Variables estaticas*/
	//Ano minimo.
	static const int AnnoMinimo=1902;
	//Ano maximo.
	static const int AnnoMaximo=2037;
private:
	/*Atributos*/
	int dia_,mes_,ano_;
	void FechaValida();
};

/*Operadores externos*/
//Operador ==.
bool operator==(const Fecha& f1,const Fecha& f2)noexcept;
//Operador !=.
bool operator!=(const Fecha& f1,const Fecha& f2)noexcept;
//Operador <.
bool operator<(const Fecha& f1,const Fecha& f2)noexcept;
//Operador <=.
bool operator<=(const Fecha& f1,const Fecha& f2)noexcept;
//Operador >.
bool operator>(const Fecha& f1,const Fecha& f2)noexcept;
//Operador >=.
bool operator>=(const Fecha& f1,const Fecha& f2)noexcept;
//Operador de extraccion.
ostream& operator<<(ostream& os,const Fecha& f)noexcept;
//Operador de inserccion.
istream& operator>>(istream& is,Fecha& f)noexcept;


#endif