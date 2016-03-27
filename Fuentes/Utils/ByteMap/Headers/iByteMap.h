/*
 * iByteMap.h
 *
 *  Created on: 26/03/2016
 *      Author: cristian
 */

#ifndef IBYTEMAP_H_
#define IBYTEMAP_H_

enum eConfiguracion {
	eConfiguracion_file_rrlv, eConfiguracion_file_blocks
};

typedef class iByteMap {

public:
	iByteMap() {
	}

	virtual ~iByteMap() {
	}

	virtual eConfiguracion getConfiguracion() const = 0;

	virtual unsigned getTamanio() const = 0;

	virtual void addGap(unsigned long _ref, unsigned _cantBytes)=0;

	/*
	 * _cantBytes es la cantidad de bytes escritos o borrados en el archivo.
	 * _cantBytes debe ser positivo cuando se trate de bytes escritos.
	 * _cantBytes debe ser negativo cuando se trate de bytes borrados.
	 */
	virtual void upDateGap(unsigned long _ref, int _cantBytes)=0;

	virtual long getCantBytes(unsigned long ref)=0;

	virtual long getGap(unsigned _cantBytes) const=0; /**Devuelve -1 si no tiene éxito.**/

}*iByteMapPtr;

#endif /* IBYTEMAP_H_ */
