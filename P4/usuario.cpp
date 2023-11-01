#include "usuario.hpp"

//Declaración adelantada
std::unordered_set<Cadena> Usuario::usuarios_;


//Métodos de la clase Clave
//Constructor
Clave::Clave(const char*  cad){
	//Comprobamos la longitud
	if(strlen(cad)<5){
		throw Clave::Incorrecta(Clave::CORTA);
	}
	//Encriptacion
	std::random_device r;
	std::uniform_int_distribution<size_t> dist(0, 63);
	char const chars[] = "./ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	char salt[2] = {chars[dist(r)],chars[dist(r)]};
	//Encriptamos la clave
	char* aux = crypt(cad, salt);
	//En caso de no se haya realizado correctamente, lanzamos la excepción
	if(aux == nullptr){
  		throw Incorrecta(Razon::ERROR_CRYPT);
	};
	//Asignamos la auxilar a la contraseña
	contra = aux;
};

//Comparador
bool Clave::verifica(const char* c) const{
	return !strcmp(crypt(c, static_cast<const char*>(contra)), static_cast<const char*>(contra));
};

//Métodos de la clase Usuario
//Constructor
Usuario::Usuario(const Cadena& i, const Cadena& n, const Cadena& a, const Cadena& d, const Clave& c):identificador(i), nom(n), apell(a), direc(d), contra(c){
	if(!usuarios_.insert(identificador).second){
		throw Usuario::Id_duplicado(i);
	};
};

//Vincular y desvincular usuarios de tarjetas
void Usuario::es_titular_de(const Tarjeta& t){
	//Comprobamos que el titular de la tarjeta sea el usuario
	if(t.titular()==this){
		ts[t.numero()] = const_cast<Tarjeta*>(&t);
	};
};

void Usuario::no_es_titular_de(Tarjeta& t){
	//Comprobamos que el titular de la tarjeta sea el usuario
	if(t.titular()==this){
		ts.erase(t.numero());
		t.anula_titular();	
	};
};

//Añadir o eliminar artículos de la compra
void Usuario::compra(const Articulo& art, size_t cantidad){
	//Buscamos si el articulo está en el carrito, si no, lo añadimos
	auto en_cesta = arts.find(const_cast<Articulo*>(&art));
	if(en_cesta == arts.end()){
		//Comprobamos que la cantidad no sea 0, si es mayor se añade
		if(cantidad > 0){
			arts[const_cast<Articulo*>(&art)] = cantidad;
		}
	}else{
		//Si el articulo ya está en cesta, le asignamos la nueva cantidad o lo borramos si este es 0
		if(cantidad == 0){
			arts.erase(en_cesta);
		}else{
			arts[const_cast<Articulo*>(&art)] = cantidad;
		}
	}
};

//Vaciamos el carro al completo
void Usuario::vaciar_carro(){
	arts.clear();
};

//Destructor
Usuario::~Usuario(){
	//Anulamos las tarjetas
	for(auto& t:ts){
		t.second->anula_titular();
	}
	//Borramos el usuario de la lista de usuarios
	usuarios_.erase(identificador);
};

//Operador de inserción de flujo
std::ostream& operator <<(std::ostream& os, const Usuario& u) noexcept{
	os << u.id() << " [" << u.contra.clave() << "] " << u.nombre() << " " << u.apellidos() << std::endl;
	os << u.direccion();
	os << "Tarjetas: " << std::endl;
	for(auto& t:u.ts){
		os << *t.second << std::endl;
	};
	return os;
};

//Función mostrar carro
void mostrar_carro(std::ostream& os, const Usuario& u) noexcept {

	os << "Carrito de la compra de " << u.id() << " [Artículos: " << u.n_articulos() << "]" << std::endl;
	os << "Cant.\tArt." <<std::endl;
	os << "======================================="<<std::endl;
	for(auto& art:u.compra()){
		os << art.second << "\t";
		os << "[" << art.first->referencia() << "] " << "\"" << art.first->titulo() << "\", " << art.first->f_publi().anno() << ". " << std::fixed << std::setprecision(2) << art.first->precio() << " €" << std::endl;
	};
	os<< std::endl;
};

