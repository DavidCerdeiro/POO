#include "tarjeta.hpp"

bool luhn(const Cadena&);
std::set<Numero> Tarjeta::tarjetas_;
//Métodos de Numero
//Constructor
Numero::Numero(const Cadena& c){
	Cadena aux;
	for(auto x:c){
		if(!isspace(x)){
			//Miramos solo aquellos que no sean espacios y comprobamos que sean números, si no lanza error
			if(!isdigit(x)){
				throw Incorrecto(Razon::DIGITOS);
			}else{
				//Vamos añadiendo los dígitos
				aux += Cadena(1,x);
			};
		};
	};
	//Comparamos que sea del tamaño correcto y que sea correcto el algoritmo de luhn
	if(aux.length() < 13 || aux.length() > 19){
		throw Incorrecto(Razon::LONGITUD);
	}else{
		if(!luhn(aux)){
			throw Incorrecto(Razon::NO_VALIDO);
		}else{
		//Copiamos la cadena y destruimos la auxiliar
		num = aux;
		};
	};	

};

//Conversor a const char*
Numero::operator const char*()const noexcept{
	return static_cast<const char*>(num);
};

//Operador de comparación
bool operator <(const Numero& n1, const Numero& n2){
	return static_cast<Cadena>(n1) < static_cast<Cadena>(n2);
}

//Métodos de Tarjeta
//Constructor
Tarjeta::Tarjeta(const Numero& num, Usuario& u,const Fecha& c):n(num), t(&u), cad(c), estado(true){
	Fecha hoy;
	//Comprobamos que la fecha de caducidad sea superior a la de hoy
	if( cad < hoy){
		throw Tarjeta::Caducada(cad);
	}else{
		//Comprobamos que sea duplicada
		if(!tarjetas_.insert(n).second){
			throw Tarjeta::Num_duplicado(n);
		}else{
			//Le asignamos la tarjeta al usuario titular
			t->es_titular_de(*this);
		};	
	};
};

//Observador que devuelve el tipo
Tarjeta::Tipo Tarjeta::tipo() const noexcept{
	Cadena digitos(2);
	digitos[0] = n[0];
	digitos[1] = n[1];
	if(digitos == "34" || digitos=="37"){
		return Tarjeta::AmericanExpress;
	}else{
		if(digitos[0]=='3'){
			return Tarjeta::JCB;
		}else{
			if(digitos[0] == '4'){
				return Tarjeta::VISA;
			}else{
				if(digitos[0]=='5'){
					return Tarjeta::MasterCard;
				}else{
					if(digitos[0]=='6'){
						return Maestro;
					}else{
						return Tarjeta::Otro;
					};
				};
			};
		};
	};
};

//Modificador
bool Tarjeta::activa(bool valor){
	estado = valor;
	return estado;
};

//Anular titular
void Tarjeta::anula_titular(){
	estado = false;
	(Usuario*&)t = nullptr;
}

//Operador de comparacion
bool operator <(const Tarjeta& t1, const Tarjeta& t2) noexcept{
	return t1.numero() < t2.numero();
}

//Destructor
Tarjeta::~Tarjeta(){
	//Si no hemos desvinculado la tarjeta de su titular aun, lo hacemos
	if(t){
		t->no_es_titular_de(*this);
	};
	tarjetas_.erase(n);

};

//Operadores de inserción
std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& t) noexcept{
	switch(t){
		case Tarjeta::VISA: 
			os << "VISA";
			break;
		case Tarjeta::JCB: 
			os << "JCB";
			break;
		case Tarjeta::Maestro: 
			os << " Maestro";
			break;
		case Tarjeta::MasterCard: 
			os << "MasterCard";
			break;
		case Tarjeta::AmericanExpress: 
			os << "AmericanExpress";
			break;
		case Tarjeta::Otro: 
			os << "Tipo indeterminado";
			break;
		default:
			os<<"Error en el tipo de tarjeta";
	}
	return os;
};
std::ostream& operator <<(std::ostream& os, const Tarjeta& t) noexcept{
	os<<t.tipo()<<std::endl;
	os<<t.numero()<<std::endl;
	//Vamos a pasar todo el nombre a mayúsculas mediante una cadena auxilar
	Cadena aux = t.titular()->nombre() + " " + t.titular()->apellidos();
	for(auto& x:aux){
		if(islower(x)){
			x = toupper(x);
		};
	};
	os<<aux<<std::endl;
	os<<"Caduca: "<<std::setfill('0')<<std::setw(2)<<(t.caducidad().mes())<<"/"<<std::setw(2)<<(t.caducidad().anno()%100)<<std::endl;
	return os;
}

