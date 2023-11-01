#include "pedido.hpp"
int Pedido::npedidos = 0;
//Constructor
Pedido::Pedido(Usuario_Pedido& up, Pedido_Articulo& pa, Usuario& u, const Tarjeta& t, const Fecha& f):id(npedidos + 1), tarjeta_(&t), fPedido(f), imp(0) {
	//Comprobamos que la compra no esté vacía
	if(u.compra().empty()){
		throw Vacio(&u);
	}
	//Comprobamos que el titular de la tarjeta sea el usuario de la compra
	if(tarjeta_->titular() != &u){
		throw Impostor(&u);
	}
	//Comprobamos tanto que la tarjeta no haya caducado como que esté activa
	if(tarjeta_->caducidad() < f){
		throw Tarjeta::Caducada(t.caducidad());
	};
	if(!tarjeta_->activa()){
		throw Tarjeta::Desactivada();
	};
	//Comprobación de la P4
	auto carro = u.compra();
	for(auto& elem:carro){
		if(ArticuloAlmacenable* art = dynamic_cast<ArticuloAlmacenable*>(elem.first)){
			//Comprobamos que haya stock suficiente
			if(art->stock() < elem.second){
				const_cast<Usuario::Articulos&>(u.compra()).clear();
				throw Pedido::SinStock(elem.first);
			}
		}else{
			if(LibroDigital* ld = dynamic_cast<LibroDigital*>(elem.first)){
				//Comprobamos que no haya expirado el libro digital
				if(ld->f_expir() < fPedido){
					u.compra(*elem.first, 0);
				}
			}
		}
	}
	//Se comprueba si se ha quedado vacía la compra
	if(u.n_articulos() == 0){
			throw Vacio(&u);
	}
	//Asociamos el pedido al usuario
	up.asocia(*this, u);
	//Por si se ha modificado la compra, lo volvemos a asignar a carro
	carro = u.compra();
	//Calculamos el importe total de la compra y actualizamos el stock de los artículos
	for(auto& c:carro){
		//Disminuimos el stock en el caso de artículo almacenable
		if(ArticuloAlmacenable *art = dynamic_cast<ArticuloAlmacenable*>(c.first)){
                	art->stock() -= c.second;
                };
                //Actualizamos importe
		imp += c.first->precio() * c.second;
		pa.pedir(*c.first, *this, c.first->precio(), c.second);
		c.first->stock() -= c.second;
	};
	const_cast<Usuario::Articulos&>(u.compra()).clear();
	id = ++ npedidos;

};

//Operador de inserción de flujo
std::ostream& operator <<(std::ostream& os, const Pedido& p){
	os << std::left;
	os << "Núm. pedido: "<<p.numero() << std::endl;
	os << std::setw(13) << "Fecha: " << p.fecha() << std::endl;
	os << std::setw(13) << "Pagado con: " << p.tarjeta()->tipo() << "nº: " << p.tarjeta()->numero() << std::endl;
	os << std::setw(13) << "Importe: " << std::fixed << std::setprecision(2) << p.total() << " €" << std::endl;
	return os;
}
