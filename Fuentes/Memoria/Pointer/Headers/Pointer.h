/* 
 * File:   Pointer.h
 * Author: Monty
 *
 * Created on 20 de marzo de 2016, 17:41
 * 
 * Adaptacion libre de la clase linked_ptr de Yonat's: http://ootips.org/yonat/4dev/linked_ptr.h
 * Repositorio de fuentes: http://ootips.org/yonat/4dev/
 * 
 */

#ifndef POINTER_H
#define	POINTER_H

#include "../../Object/Headers/Object.h"
#include <stddef.h>

typedef class Pointer
{
	private:
		ObjectPtr obj;
		mutable const Pointer *prev;
		mutable const Pointer *next;

	public:
		explicit Pointer(Object *ptr = NULL);
		Pointer(const Pointer &ptr);
		~Pointer();
		
		Object &operator*();
		Object *operator->();

		Pointer &operator=(const Pointer &ptr);

	private:
		void Attach(const Pointer &ptr);
		void Release();

} *Handle;

#endif	/* POINTER_H */
