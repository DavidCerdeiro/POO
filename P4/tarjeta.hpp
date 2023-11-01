 #ifndef _TARJETA_HPP_
 #define _TARJETA_HPP_
 #include<iostream>
 #include "../P1/fecha.hpp"
 #include "../P1/cadena.hpp"
 #include <set>
 #include<cctype>
 #include<iomanip>
 #include "usuario.hpp"
 
 class Usuario;
 class Numero{
 	public:
 		//Tipo Razon
 		enum Razon {LONGITUD, DIGITOS, NO_VALIDO};
 		//Constructor
 		Numero(const Cadena& n);
 		//Operador de conversión
		operator const char*() const noexcept;
		//Clase Incorrecto	
 		class Incorrecto{
 			public:
 				Incorrecto(Numero::Razon razon):r(razon) {};
 				Numero::Razon razon() const noexcept {return r;};
 			private:
 			Numero::Razon r;
 		};
 	private:
 		Cadena num;
 		
 };
 //Operador de comparación
 bool operator <(const Numero& n1, const Numero& n2);
 
 class Tarjeta{
 	public:
 		//Tipo Tipo
 		enum Tipo{Otro, VISA, MasterCard, Maestro, JCB, AmericanExpress};
 		//Constructor
 		Tarjeta(const Numero& num, Usuario& u,const Fecha& c);
 		//Evitamos la copia y asignación entre tarjetas
 		Tarjeta(const Tarjeta& t) = delete;
 		Tarjeta& operator =(const Tarjeta& t) = delete;
 		//Observadores
 		inline const Numero& numero() const noexcept { return n; };
 		inline const Usuario* titular() const noexcept { return t; };
 		inline const Fecha& caducidad() const noexcept { return cad; };
 		inline bool activa() const noexcept { return estado; };
 		Tipo tipo() const noexcept;
 		//Modificador de estado
 		bool activa(bool valor);
 		//Anular al titular
 		void anula_titular();
 		//Destructor
 		~Tarjeta();
 		//Clase Caducada
 		class Caducada{
 			public:
 				Caducada(const Fecha fecha):f(fecha){};
 				const Fecha cuando() const { return f;};
 			private:
 				Fecha f;
 		};
 		//Clase Num_duplicado
 		class Num_duplicado{
 			public:
 				Num_duplicado(const Numero& n):num(n){};
 				const Numero& que() const {return num;};
 			private:
 				Numero num;
 		};
 		class Desactivada{};
 	private:
 		const Numero n;
 		Usuario* t;
 		const Fecha cad;
 		bool estado;
 		friend class Usuario;
 		static std::set<Numero> tarjetas_;
 
 };
 //Operador de comparación
 bool operator <(const Tarjeta& t1, const Tarjeta& t2) noexcept;
 //Operadores de inserción de flujo
 std::ostream& operator <<(std::ostream& os, const Tarjeta::Tipo& t) noexcept;
 std::ostream& operator <<(std::ostream& os, const Tarjeta& t) noexcept;
 #endif
