#ifndef CADENA_HPP_
#define CADENA_HPP_
#include<iostream>
class Cadena{
	public:
	//Constructores
	explicit Cadena(unsigned int n=0, char c=' ');
	Cadena(const Cadena& c);
	Cadena(const char *c);
	Cadena(Cadena&& c);
	//Operadores de asignación
	Cadena operator =(const Cadena &c);
	Cadena operator =(Cadena&& c);
	Cadena operator =(const char *c);
	//Observador
	inline unsigned int length() const noexcept {return tam_;};
	//Operador suma con asignación
	Cadena operator +=(const Cadena);
	//Operador de conversión
	explicit operator const char*() const;
	//Operadores de índice
	char& operator [](unsigned int) const;
	char& operator [](unsigned int);
	//Subcadena
	Cadena substr (unsigned int indice, unsigned int tam) const;
	//Operadores de índice
	char& at(unsigned int);
	char& at(unsigned int) const;
	//Definición de iteradores
	typedef char* iterator;
	typedef const char* const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
	//Funciones iteradoras
	inline iterator begin() noexcept { return s_;};
	inline const_iterator begin() const noexcept { return const_iterator(s_);};
	inline reverse_iterator rbegin() noexcept { return reverse_iterator(end());};
	inline const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end());};
	inline const_iterator cbegin() const noexcept  { return const_iterator(s_);};
	inline const_reverse_iterator crbegin() const noexcept {  return const_reverse_iterator(end());};
	inline iterator end() noexcept { return s_+tam_;};
	inline const_iterator end() const noexcept { return s_+tam_;};
	inline reverse_iterator rend() noexcept { return reverse_iterator(begin());};
	inline const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin());};
	inline const_iterator cend() const noexcept { return const_iterator(end());};
	inline const_reverse_iterator crend() const noexcept { return const_reverse_iterator(begin());};
	//Destructor
	~Cadena();
	private:
	char *s_;
	unsigned int tam_;
};
	//Operador de concatenación
	Cadena operator +(const Cadena &c1, const Cadena &c2);
	//Operadores booleanos
	bool operator >(const Cadena &c1, const Cadena &c2) noexcept;
	bool operator <(const Cadena &c1, const Cadena &c2) noexcept;
	bool operator >=(const Cadena &c1, const Cadena &c2) noexcept;
	bool operator <=(const Cadena &c1, const Cadena &c2) noexcept;
	bool operator ==(const Cadena &c1, const Cadena &c2) noexcept;
	bool operator !=(const Cadena &c1, const Cadena &c2) noexcept;
	//Operadores de inserción y extracción
	std::ostream& operator<<(std::ostream& os, const Cadena& c) noexcept;
	std::istream& operator>>(std::istream& is,Cadena& cadena);
	
	// Para P2 y ss .
	// Especialización de la plantilla std :: hash<Key> para definir la función hash a usar
	// en contenedores desordenados de Cadena, unordered_[set|map|multiset|multimap].
	namespace std { // Estaremos dentro del espacio de nombres std.
		template <> // Es una especializaci ón de una plantilla para Cadena.
		struct hash<Cadena> { // Es una clase con solo un operador público.
			size_t operator() (const Cadena& cad) const // El operador función.
			{
				hash<string> hs; // Creamos un objeto hash de string.
				auto p{(const char*)(cad)}; // Convertimos Cadena a cadena de bajo nivel.
				string s{p}; // Creamos un string desde la cadena de b. nivel .
				size_t res{hs(s)}; // El hash del string . Como hs.operator()(s);
				return res; // Devolvemos el hash del string .
				// En forma abreviada:
				// return hash<string>{}((const char*)(cad));
			}
		};
	}

#endif
