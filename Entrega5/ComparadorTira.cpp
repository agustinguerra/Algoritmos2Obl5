#ifndef COMPARADOR_TIRA_CPP
#define COMPARADOR_TIRA_CPP
#include "ComparadorTira.h"



ComparadorTira::ComparadorTira() {}

ComparadorTira::~ComparadorTira() {}

CompRetorno ComparadorTira::Comparar(const Puntero<ITira>& t1, const Puntero<ITira>& t2) const
{
	const nat x1 = t1->ObtenerX();
	const nat x2 = t2->ObtenerX();
	
	if (x1 > x2) {
		return MAYOR;
	} 
	else if (x1 < x2) {
		return MENOR;
	} 
	else if (x1 == x2) {
		return IGUALES;
	} 

	return DISTINTOS;
}
#endif