#include "usuario-pedido.hpp"
//Asociaciones
void Usuario_Pedido::asocia(Usuario& u, Pedido& p){
	//Insertamos en el diccionario
	up[&u].insert((Pedido*)&p);
	pu[&p] = (Usuario*)&u;
}
void Usuario_Pedido::asocia(Pedido& p, Usuario& u){
	//Llamamos a la otra función
	asocia(u, p);
};

//Observadores
Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(const Usuario& u) const noexcept{
	auto x = up.find((Usuario*)&u);
	//Buscamos y devolvemos el set si está, si no devolvemos uno vacío
	if( x != up.end()){
		return x->second;
	}else{
		return Pedidos{};
	};
};
const Usuario* Usuario_Pedido::cliente(const Pedido& p) noexcept {
	auto c = pu.find((Pedido*)&p);
	if( c != pu.end()){
		return c->second;
	}else{
 		return nullptr;
	};
};
