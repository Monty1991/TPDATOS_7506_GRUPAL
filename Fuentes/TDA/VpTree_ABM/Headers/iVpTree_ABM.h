/*
 * iVpTree_ABM.h
 *
 *  Created on: 25/05/2016
 *      Author: cristian
 */

#ifndef IVPTREE_ABM_H_
#define IVPTREE_ABM_H_

#include "../../../Memoria/Registro/Headers/iRegistro.h"

enum eResultadoABM
{
	eResultadoABM_NoErr,
	eResultadoABM_ClaveDuplicada,
	eResultadoABM_ClaveNoEncontrada,
};

typedef class iVpTree_ABM
{
	public:

		virtual eResultadoABM Alta(const  iRegistroPtr registro, bool comprobarUnicidad) = 0;

		virtual eResultadoABM Baja(const iFeaturePtr clave) = 0;

		virtual eResultadoABM Modificacion(const iRegistroPtr registro) = 0;

		virtual eResultadoABM Buscar(const iFeaturePtr clave, iRegistroPtr *registro) = 0;

		virtual void Dispose() = 0;

} *iVpTree_ABMPtr;

#endif /* IVPTREE_ABM_H_ */
