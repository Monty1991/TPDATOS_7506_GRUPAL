/* 
 * File:   Sistema.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 16:21
 */

#ifndef SISTEMA_H
#define	SISTEMA_H

#include "../../../io/Bitacora/Headers/iBitacora.h"
#include "../../StackTrace/Headers/iStackTrace.h"
#include "../../Entorno/Headers/iEntorno.h"

void Sistema_Inicializar();
void Sistema_Finalizar();

const iEntornoPtr Sistema_ObtenerEntorno();

#define Sistema_DebugInfo(x) __FILE__, __LINE__ x, __PRETTY_FUNCTION__

#define Sistema_Execute(closure) Sistema_ObtenerEntorno()->Execute([&](){ closure }, Sistema_DebugInfo(+1));

#define TryBlock(tryClause) try { tryClause }

#define CatchBlock(catchClause) catch (iExceptionPtr e) { catchClause(e); }

#define FinallyBlock(finallyClause) { finallyClause }

#define TryCatchBlock(tryClause, catchClause) TryBlock(tryClause) CatchBlock(catchClause)
#define TryCatchFinallyBlock(tryClause, catchClause, finallyClause) TryCatchBlock(tryClause, catchClause) FinallyBlock(finallyClause)

#endif	/* SISTEMA_H */
