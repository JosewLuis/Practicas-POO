#include"usuario.hpp"

#include<iostream>
#include<unistd.h>

using namespace std;

/*usuario.cpp*/

/*Tipo Razon*/
typedef  typename Clave::Incorrecta::Razon razon;


/*Clase Clave.*/

/*Constructores*/
//Constructor.
Clave::Clave(const char* texto){
	if(strlen(texto)<5){
		throw Incorrecta(razon::CORTA);
	}

    char* salt=new char[2];
    int r_number;
    const char *const seedchars{"./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"};

    random_device r;

    default_random_engine el{r()};

    uniform_int_distribution<int>u_dist{0,(int)(strlen(seedchars))-1};

    for(int i=0;i<2;i++){
     	r_number=u_dist(el);
      	salt[i]=seedchars[r_number];
    }

    char* encrypted=crypt(texto, salt);

    if(texto==encrypted){
      throw Incorrecta(razon::ERROR_CRYPT);
    }

    this->cifrada_=encrypted;
}

/*Observadores*/
//Verifica.
bool Clave::verifica(const char* texto)const{
	bool v;

    if(const char* const checker=crypt(texto,this->cifrada_.c_str())){
        v=checker==this->cifrada_;
    }
    else{
        throw Incorrecta(razon::ERROR_CRYPT);
    }

    return v;
}

/*Clase Usuario.*/

/*Constructores*/
Usuario::Usuario(const Cadena& id,const Cadena& nombre,const Cadena& apell,const Cadena& direccion,const Clave& clave):id_(id),nombre_(nombre),apell_(apell),
                                                                                                                       direccion_(direccion),contrasena_(clave){
    //Insertamos y comprobamos que no este en el set.                                                                                                                    
    pair<unordered_set<Cadena>::iterator,bool>p=usuarios.insert(id);
    if(!p.second()){
        throw Id_duplicado(id);
    }
}

/*Destructor*/
Usuario::~Usuario(){
    usuarios.erase(this->id);

    for(auto it=this->Ts.begin();it!=this->Ts.end();it++){
        it.second->anula_titular();
    }
}

/*Metodos asociativos*/
//Asocia tarjeta.
void Usuario::es_titula_de(const Tarjeta& t)noexcept{
    if(this->id==t.titular()->id() || t.titular()==nullptr){
        pair<Tarjetas::iterator,bool>p=this->Ts.insert(t);
        if(p.second()==false){
            cout << "No se ha insertado la tarjeta con numero: " << t.numero() << endl;
        }
    }else{
        cout << "Algo fallo..." << endl;
    }
}

//Desasocia.
void Usuario::no_es_titular_de(const Tarjeta& t)noexcept{
    Ts.erase(t.numero());
}

//Asocia articulo.
void Usuario::compra(const Articulo& a,int cantidad=1)noexcept{
    if(cantidad==0){
        As.erase(&a);
    }else{
        As[&a]=cantidad;
    }
}