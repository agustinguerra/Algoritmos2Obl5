#pragma once

#include "Comparacion.h"
#include "ITira.h"
#include "Puntero.h"

class ComparadorTira : public Comparacion<Puntero<ITira>>
{
public:
	ComparadorTira();
	~ComparadorTira();

	CompRetorno Comparar(const Puntero<ITira>& t1, const Puntero<ITira>& t2) const override;
};