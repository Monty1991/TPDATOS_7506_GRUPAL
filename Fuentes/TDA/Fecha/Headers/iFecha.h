/*
 * iFecha.h
 *
 *  Created on: 27/03/2016
 *      Author: cristian
 */

#ifndef IFECHA_H_
#define IFECHA_H_

typedef class iFecha {

public:
	iFecha() {
	}

	virtual ~iFecha() {
	}

	virtual bool isValid() const=0;

	virtual int compare(const iFecha& _f) const=0;

	virtual unsigned int getAnio() const=0;
	virtual void setAnio(unsigned int _anio)=0;

	virtual unsigned char getDia() const=0;
	virtual void setDia(unsigned char _dia)=0;

	virtual unsigned char getHora() const=0;
	virtual void setHora(unsigned char _hora)=0;

	virtual unsigned char getMes() const=0;
	virtual void setMes(unsigned char _mes)=0;

	virtual unsigned char getMinuto() const=0;
	virtual void setMinuto(unsigned char _minuto)=0;

	virtual unsigned char getSegundo() const=0;
	virtual void setSegundo(unsigned char _segundo)=0;

}*iFechaPtr;

#endif /* IFECHA_H_ */
