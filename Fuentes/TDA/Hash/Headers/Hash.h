/* 
 * File:   Hash.h
 * Author: Monty
 *
 * Created on 18 de junio de 2016, 17:24
 */

#ifndef HASH_H
#define HASH_H

#include "../../Arbol/Headers/iArbol.h"
#include "Hash.h"

class Hash: public iHash
{
	private:
		iArbolPtr *tabla;
		size_t tamanioTabla;
		size_t cantidadElementos;
		
		virtual ~Hash();
	public:
		Hash();
		virtual void Dispose();

		virtual bool Guardar(iObjectPtr obj, iFeaturePtr clave);
		virtual iObjectPtr Obtener(iFeaturePtr clave);
		virtual iObjectPtr Borrar(iFeaturePtr clave);
		virtual size_t ObtenerCantidad();

	private:
		virtual void Redimensionar(size_t nuevoTamanio);
};

#endif /* HASH_H */
