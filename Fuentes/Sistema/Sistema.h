/* 
 * File:   Sistema.h
 * Author: Monty
 *
 * Created on 17 de marzo de 2016, 16:21
 */

#ifndef SISTEMA_H
#define	SISTEMA_H

#include "../io/Bitacora/Headers/iBitacora.h"
#include "StackTrace/Headers/iStackTrace.h"

void Sistema_Inicializar();

const iBitacoraPtr Sistema_ObtenerBitacora();

void Sistema_Finalizar();

iStackTrace *Sistema_GetStackTraceCopy();
void Sistema_PushEntry(const char *file, int line, const char *functionName);
void Sistema_PopEntry();

#define Sistema_DebugInfo(x) __FILE__, __LINE__ x, __PRETTY_FUNCTION__
#define Sistema_EnterFunction(stmt) {Sistema_PushEntry(Sistema_DebugInfo(+1)); \
																			{stmt}}

#define TryBlock(tryClause) try { tryClause }

#define CatchBlock(catchClause) catch (Exception *e) { catchClause(e); }

#define FinallyBlock(finallyClause) { finallyClause }

#define TryCatchBlock(tryClause, catchClause) TryBlock(tryClause) CatchBlock(catchClause)
#define TryCatchFinallyBlock(tryClause, catchClause, finallyClause) TryCatchBlock(tryClause, catchClause) FinallyBlock(finallyClause)

#endif	/* SISTEMA_H */
