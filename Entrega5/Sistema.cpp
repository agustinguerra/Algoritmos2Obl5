#include "Sistema.h"
#define DEBUG

Sistema::Sistema()
{

}

//Pre: -
//Pos: Hace el swapeo para trasponer la matriz dentro de las coordenadas indicadas
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

//Pre: -
//Pos: taspone la matriz que se le paso por parametro
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
	return; 
};

//Pre: -
//Pos: Hace el merge de dos listas

Puntero<ListaOrd<Puntero<ITira>>> MergeSK(Puntero<ListaOrd<Puntero<ITira>>> izq, Puntero<ListaOrd<Puntero<ITira>>> der)
{
	if (izq == nullptr && der)
		return der;

	if (izq && der == nullptr)
		return izq;
	
	if (izq == nullptr && der == nullptr)
		return nullptr;
#ifdef DEBUG

	Iterador<Puntero<ITira>> it = izq->ObtenerIterador();

	Iterador<Puntero<ITira>> itDerT = der->ObtenerIterador();

	cout << "Esta es la izquierda ";
	while (it.HayElemento()) {
		cout << it.ElementoActual()->ObtenerX() << " , " << it.ElementoActual()->ObtenerAltura() << " - ";
		it.Avanzar();
	}
	cout << "Esta es la derecha ";
	while (itDerT.HayElemento()) {
		cout << itDerT.ElementoActual()->ObtenerX() << " , " << itDerT.ElementoActual()->ObtenerAltura() << " - ";
		itDerT.Avanzar();
	}
#endif // DEBUG

	Iterador<Puntero<ITira>> itIzq = izq->ObtenerIterador();
	Iterador<Puntero<ITira>> itDer = der->ObtenerIterador();

	Puntero<Comparacion<Puntero<ITira>>> pComp = new ComparadorTira();

	Puntero<ListaOrd<Puntero<ITira>>> listaMerge = new ListaOrdImp<Puntero<ITira>>(pComp);

	int altIzq = 0;
	int altDer = 0;
	Puntero<ITira> tira;
	while (itIzq.HayElemento() && itDer.HayElemento())
	{
		Puntero<ITira> puntDer = itDer.ElementoActual();
		Puntero<ITira> puntIzq = itIzq.ElementoActual();
		int x = 0;

		if (puntDer->ObtenerX() < puntIzq->ObtenerX())
		{
			altDer = puntDer->ObtenerAltura();
			
			x = puntDer->ObtenerX();

			itDer.Avanzar();
		}
		else if (puntDer->ObtenerX() > puntIzq->ObtenerX())
		{
			altIzq = puntIzq->ObtenerAltura();
			
			x = puntIzq->ObtenerX();

			itIzq.Avanzar();
		}
		else
		{

			if (puntIzq->ObtenerAltura() > puntDer->ObtenerAltura())
				altIzq = puntIzq->ObtenerAltura();
			else
				altDer = puntDer->ObtenerAltura();

			itDer.Avanzar();
			itIzq.Avanzar();
		}

		int altH;

		if (altIzq > altDer)
			altH = altIzq;
		else
			altH = altDer;

		if (!(tira != nullptr && tira->ObtenerAltura() == altH)) {
			tira = new Tira(x, altH);
			listaMerge->InsertarOrdenado(tira);
		}
		else {
			continue;
		}
	}

	int alturaAnt = -1;
	Puntero<ITira> tiraX;
	if (itIzq.HayElemento())
	{
		while (itIzq.HayElemento())
		{

			tiraX = itIzq.ElementoActual();
			itIzq.Avanzar();

			if (alturaAnt != tiraX->ObtenerAltura())
			{
				listaMerge->InsertarOrdenado(tiraX);
				alturaAnt = tiraX->ObtenerAltura();
			}
		}
	}
	else if (itDer.HayElemento())
	{
		while (itDer.HayElemento())
		{

			tiraX = itDer.ElementoActual();
			itDer.Avanzar();

			if (alturaAnt != tiraX->ObtenerAltura())
			{
				listaMerge->InsertarOrdenado(tiraX);
				alturaAnt = tiraX->ObtenerAltura();
			}
		}
	}

#ifdef DEBUG
	Iterador<Puntero<ITira>> itDerTM = listaMerge->ObtenerIterador();

	cout << "Esta es la merge ";
	while (itDerTM.HayElemento()) {
		cout << itDerTM.ElementoActual()->ObtenerX() << " , " << itDerTM.ElementoActual()->ObtenerAltura() << " - ";
		itDerTM.Avanzar();
	}
#endif // DEBUG

	return listaMerge;
}

//Pre - 
//Pos: devuelve un puntero a una lista de ITiras

Puntero<ListaOrd<Puntero<ITira>>> Siluetas(Array<Puntero<ListaOrd<Puntero<ITira>>>> tr, int desde, int hasta)
{
	if (desde == hasta) {

		Puntero<Comparacion<Puntero<ITira>>> pComp = new ComparadorTira();

		Puntero<ListaOrd<Puntero<ITira>>> lista = new ListaOrdImp<Puntero<ITira>>(Comparador<Puntero<ITira>>(pComp));

		for (int i = desde; i <= hasta; i++)
		{
			Puntero<ListaOrd<Puntero<ITira>>> listatiras = tr[i];
			Iterador<Puntero<ITira>> iteradorLTira = listatiras->ObtenerIterador();

			while (iteradorLTira.HayElemento())
			{
				lista->InsertarOrdenado(iteradorLTira.ElementoActual());
				iteradorLTira.Avanzar();
			}

		}
		return lista;

	}
	else if (desde < hasta) {
		int mid = (desde + hasta) / 2;

		Puntero<ListaOrd<Puntero<ITira>>> lIzq = Siluetas(tr, desde, mid);
		      
		Puntero<ListaOrd<Puntero<ITira>>> lDer = Siluetas(tr, mid + 1, hasta);

		return MergeSK(lIzq, lDer);
	}
	else {
		return nullptr;
	}
}

//Pre: -
//Pos: Devuelve la silueta de la ciudad como un array de punteros de ITira

Array<Puntero<ITira>> Sistema::CalcularSiluetaDeLaCiudad(Array<Puntero<IEdificio>> ciudad)
{
	
	//Primero transformo la entrada
	Array<Puntero<ListaOrd<Puntero<ITira>>>> sil(ciudad.Largo);
	
	Puntero<Comparacion<Puntero<ITira>>> comp = new ComparadorTira();
	
	Comparador<Puntero<ITira>> compT(comp);

	int cLargo = ciudad.Largo;

	for (int i = 0; i < cLargo; i++)
	{
		Puntero<IEdificio> edificio = ciudad[i];
		Puntero<ListaOrd<Puntero<ITira>>> tr = new ListaOrdImp<Puntero<ITira>>(compT);

		Puntero<ITira> tiraI = new Tira(ciudad[i]->ObtenerXInicial(), ciudad[i]->ObtenerAltura());
		tr->InsertarOrdenado(tiraI);

		Puntero<ITira> tiraF = new Tira(ciudad[i]->ObtenerXFinal(), 0);
		tr->InsertarOrdenado(tiraF);

		sil[i] = tr;
	}
	//Aqui tengo pronto el array con las tiras procesadas

	int silLargo = sil.Largo;
	//Llamo al metodo que inicia la solucion
	Puntero<ListaOrd<Puntero<ITira>>> lista = Siluetas(sil, 0, silLargo - 1);

	int largoSolucion = lista->Largo();

	Array<Puntero<ITira>> solucion(largoSolucion);

	Iterador<Puntero<ITira>> itSol = lista->ObtenerIterador();
	int contador = 0;
	while (itSol.HayElemento()) {
		solucion[contador] = itSol.ElementoActual();
		contador++;
		itSol.Avanzar();
	}
	return solucion; 
};


//Metodo para hacerlo con matriz siguiendo el caso exacto presentado en la letra
//Funcional pero no cumple con la premisa de la memoria levantada por ser una matriz

//nat calcularCoef(Matriz<nat> memorizacion, Matriz<bool> memorizacionBoolean, nat n, nat k) {
//	if (n == 0 && k == 0) {
//		return 1;
//	}
//	else {
//		if (memorizacionBoolean[n][k] == true) {
//			return memorizacion[n][k];
//		}
//		else {
//			
//			if (n - 1 == 0) {
//				if (k - 1 == 0) {
//					return 1;
//				}
//				else {
//					return 0;
//				}
//			}
//			else if (k - 1 == 0) {
//				memorizacionBoolean[n][k] = true;
//				nat res = 1 + calcularCoef(memorizacion, memorizacionBoolean, n-1, k);
//				memorizacion[n][k] = res;
//				return res;
//			}
//			else {
//				memorizacionBoolean[n][k] = true;
//				nat res = calcularCoef(memorizacion, memorizacionBoolean, n - 1, k - 1) + calcularCoef(memorizacion, memorizacionBoolean, n-1, k);
//				memorizacion[n][k] = res;
//				return res;
//			}
//		}
//	}
//}
//
//nat Sistema::CalcularCoeficienteBinomial(nat n, nat k)
//{
//	Matriz<nat> memorizacion(n + 1, k + 1);
//	Matriz<bool> memorizacionBoolean(n + 1, k + 1);
//	nat resultado = calcularCoef(memorizacion, memorizacionBoolean, n, k);
//	return resultado;
//};


//Pre: -
//Pos: devuelve el coedificiente binomial
nat Sistema::CalcularCoeficienteBinomial(nat n, nat k)
{
	//No hay ninguna posibilidad si hay menos elementos que los contenedores
	if (k > n) {
		return 0;
	} 
	//Combinaciones en 0 siempre dan 1
	if (n < 1) {
		return 1;
	} 

	Array<int> memorizacion(n + 1, 0);
	
	//Caso base
	memorizacion[0] = 1;
	int nInt = n;
	//Metodo standard para hacerlo con memorizacion usando un array.
	for (int i = 1; i <= nInt; i++)
	{
		for (int j = i; j > 0; j--)
			memorizacion[j] = memorizacion[j] + memorizacion[j - 1];
	}
	return memorizacion[k];
};


