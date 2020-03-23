#ifndef _FECHA_HPP_
#define _FECHA_HPP_
#include "iostream"

/*Fecha.cpp*/

class Fecha{
public:
	/*Constructores*/
	//Constructor con 3 elementos.
	explicit Fecha(int dia=0,int mes=0,int ano=0);
	//Constructor de copia.
	explicit Fecha(const Fecha& F);
	//Constructo const char*.
	explicit Fecha(const char* c);

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

	/*Observadores*/
	//Devuelve dia.
	inline int dia()const noexcept{return this->dia_;}
	//Devuelve mes.
	inline int mes()const noexcept{return this->mes_;}
	//Devuelve ano.
	inline int ano()const noexcept{return this->ano_;}
	//Devuelve Fecha
	void mostrar()const noexcept;

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


#endif