#include "Sistema.h"

Sistema::Sistema()
{

}

void swap(Matriz<nat> &m, int x, int y, int xp, int yp,int dim) {
	int xpa = xp;
	int ypa = yp;
	int posA;
	int posX = xp;
	for (int i = x; i < x+dim; i++) {
		posA = yp;
		for (int j = y; j < y + dim; j++) {
			int temp = m[i][j];
			m[i][j] = m[posX][posA];
			m[posX][posA] = temp;
			posA++;
		}
		posX++;
	}

}

void trasponer(Matriz<nat> &m, int x, int y, int n)
{
	if (n > 1)
	{
		trasponer(m, x, y, n / 2);
		trasponer(m, x + n / 2, y, n / 2);
		trasponer(m, x, y + n / 2, n / 2);
		trasponer(m, x + n / 2, y + n / 2, n / 2);
		swap(m, x, y + n / 2, x + n / 2, y, n / 2);
	}
}

void Sistema::TransponerMatriz(Matriz<nat> matriz)
{
	trasponer(matriz, 0, 0, matriz.Largo);
	return; //retorno por defecto
};


Array<Puntero<ITira>> Sistema::CalcularSiluetaDeLaCiudad(Array<Puntero<IEdificio>> ciudad)
{
	/*
	Codigo de implementacion de la solucion
	*/
	return Array<Puntero<ITira>>(); //retorno por defecto
};

nat calcularCoef(Matriz<nat> memorizacion, Matriz<bool> memorizacionBoolean, nat n, nat k) {
	if (n == 0 && k == 0) {
		return 1;
	}
	else {
		if (memorizacionBoolean[n][k] == true) {
			return memorizacion[n][k];
		}
		else {
			
			if (n - 1 == 0) {
				if (k - 1 == 0) {
					return 1;
				}
				else {
					return 0;
				}
			}
			else if (k - 1 == 0) {
				memorizacionBoolean[n][k] = true;
				nat res = 1 + calcularCoef(memorizacion, memorizacionBoolean, n-1, k);
				memorizacion[n][k] = res;
				return res;
			}
			else {
				memorizacionBoolean[n][k] = true;
				nat res = calcularCoef(memorizacion, memorizacionBoolean, n - 1, k - 1) + calcularCoef(memorizacion, memorizacionBoolean, n-1, k);
				memorizacion[n][k] = res;
				return res;
			}
		}
	}
}
nat Sistema::CalcularCoeficienteBinomial(nat n, nat k)
{
	Matriz<nat> memorizacion(n+1, k+1);
	Matriz<bool> memorizacionBoolean(n+1, k+1);
	nat resultado = calcularCoef(memorizacion, memorizacionBoolean, n, k);
	return resultado;
};


