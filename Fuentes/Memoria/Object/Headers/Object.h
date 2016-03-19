/* 
 * File:   Object.h
 * Author: Monty
 *
 * Created on 19 de marzo de 2016, 17:36
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include <stddef.h>

class Object
{
	private:
		size_t refCount;
		
	public:
		Object(): refCount(1) {}
		Object(const Object &) {}
		~Object() {}

		void Attach();
		void Dettach();
		Object *UnAlias();

	private:
};

#endif	/* OBJECT_H */
