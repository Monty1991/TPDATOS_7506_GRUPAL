/*
 * iTTDispersion.h
 *
 *  Created on: 26/03/2016
 *      Author: cristian
 */

#ifndef ITTDISPERSION_H_
#define ITTDISPERSION_H_

typedef class iTTDispersion {

public:
	iTTDispersion() {
	}

	virtual ~iTTDispersion() {
	}

	virtual unsigned getTamanio() const = 0;

	//Recuerda la última posición accedida.
	virtual unsigned remember() const = 0;

	virtual void duplicar() = 0;

	virtual bool duplicada() const = 0;

	virtual void truncar() = 0;

	virtual void replaceElement(unsigned _pos, unsigned _elem) = 0;

	virtual unsigned getElement(unsigned _pos) = 0;

	//Retorna un elemento y no una posición.
	virtual unsigned dispersar(unsigned long _key) = 0;

}*iTTDispersionPtr;

#endif /* ITTDISPERSION_H_ */
