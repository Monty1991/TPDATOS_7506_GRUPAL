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

	virtual ~iTTDispersion() {
	}

	virtual iTTDispersion& operator=(const iTTDispersion& _tabla) = 0;

	virtual unsigned getTamanio() const = 0;

	virtual void duplicar() = 0;

	virtual bool duplicada() const = 0;

	virtual void truncar() = 0;

	virtual void setElement(unsigned _pos, int _elem) = 0;

	virtual int getElement(unsigned _pos) const = 0;

}*iTTDispersionPtr;

#endif /* ITTDISPERSION_H_ */
