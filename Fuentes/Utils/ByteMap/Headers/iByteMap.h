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

	virtual ~iByteMap() {
	}

	virtual iByteMap* clone() const = 0;

	virtual eConfiguracion getConfiguracion() const = 0;

	virtual unsigned getTamanio() const = 0;

	virtual void reduce() = 0; /*Elimina la última referencia del mapa*/

	/**
	 * Este método debe ser invocado en las siguientes situaciones:
	 * 1)_cuando se agrega un bloque nuevo a un archivo de bloques
	 * 2)_cuando se borra un registro en un archivo de rrlv
	 */
	virtual void enlarge(unsigned long _referencia,
			unsigned _cantBytesLibres)=0;

	/*
	 * Este método debe ser invocado en las siguientes situaciones:
	 * 1)_alta de registro en un archivo de bloques
	 * 2)_baja de registro en un archivo de bloques
	 * 3)_alta de registro en un archivo de rrlv reutilizando espacio libre
	 *
	 * _cantBytesModificados debe ser positivo cuando se trate de bytes escritos
	 * _cantBytesModificados debe ser negativo cuando se trate de bytes borrados
	 */
	virtual void upDate(unsigned long _referencia, int _cantBytesModificados)=0;

	virtual unsigned getCantBytesLibres(unsigned long _referencia)=0;

	virtual long getReferencia(unsigned _cantBytesNecesarios) const=0; /**Devuelve -1 si no tiene éxito.**/

}*iByteMapPtr;

#endif /* IBYTEMAP_H_ */
