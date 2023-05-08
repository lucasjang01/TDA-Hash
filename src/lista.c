#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

lista_t *lista_crear()
{
	return calloc(1, sizeof(lista_t));
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista)
		return NULL;

	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (!nodo)
		return NULL;

	nodo->elemento = elemento;
	nodo->siguiente = NULL;

	if (!lista->nodo_inicio)
		lista->nodo_inicio = nodo;
	else
		lista->nodo_fin->siguiente = nodo;

	lista->nodo_fin = nodo;
	lista->cantidad++;
	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (!lista)
		return NULL;

	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (!nodo)
		return NULL;

	nodo->elemento = elemento;
	int posicion_aux = 0;
	
	if ((int)posicion < 0 || posicion >= lista->cantidad)
		posicion_aux = (int)lista->cantidad;
	else if (posicion < lista->cantidad || posicion == 0)
		posicion_aux = (int)posicion;
	
	nodo_t *actual = lista->nodo_inicio;

	if (posicion_aux == 0) {
		nodo->siguiente = actual;
		lista->nodo_inicio = nodo;

		if (!lista->nodo_fin)
			lista->nodo_fin = nodo;
	} else {
		for (int i = 0; i < posicion_aux - 1; i++)
			actual = actual->siguiente;

		nodo->siguiente = actual->siguiente;
		actual->siguiente = nodo;

		if (posicion_aux == lista->cantidad)
			lista->nodo_fin = nodo;
	}

	lista->cantidad++;
	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (!lista || !lista->nodo_inicio)
		return NULL;

	nodo_t *actual = lista->nodo_inicio;
	void *elemento;
	
	if (lista->cantidad == 1) {
		elemento = actual->elemento;
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
		free(actual);
	} else {
		while (actual->siguiente->siguiente)
			actual = actual->siguiente;

		elemento = actual->siguiente->elemento;
		lista->nodo_fin = actual;
		free(actual->siguiente);
		actual->siguiente = NULL;
	}

	lista->cantidad--;
	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || !lista->nodo_inicio)
		return NULL;
	
	void *elemento;
	int posicion_aux = 0;

	if ((int)posicion < 0 || posicion >= lista->cantidad)
		posicion_aux = (int)lista->cantidad - 1;
	else if (posicion < lista->cantidad || posicion == 0)
		posicion_aux = (int)posicion;

	nodo_t *actual = lista->nodo_inicio;

	if (posicion_aux == 0) {
		elemento = actual->elemento;
		lista->nodo_inicio = actual->siguiente;

		if (lista->cantidad == 1)
			lista->nodo_fin = NULL;

		free(actual);
	} else {
		for (int i = 0; i < posicion_aux - 1; i++)
			actual = actual->siguiente;

		elemento = actual->siguiente->elemento;
		nodo_t *nodo_aux = actual->siguiente;
		actual->siguiente = actual->siguiente->siguiente;

		free(nodo_aux);

		if (posicion_aux + 1 == lista->cantidad)
			lista->nodo_fin = actual;
	}

	lista->cantidad--;
	return elemento;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || !lista->nodo_inicio)
		return NULL;
	if ((int)posicion < 0 || posicion >= lista->cantidad)
		return NULL;

	nodo_t *actual = lista->nodo_inicio;

	for (int i = 0; i < posicion; i++)
			actual = actual->siguiente;
	
	return actual->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (!lista || !comparador)
		return NULL;

	nodo_t *actual = lista->nodo_inicio;

	while (actual) {
		if (comparador(actual->elemento, contexto) == 0)
			return actual->elemento;
		actual = actual->siguiente;
	}

	return NULL;
}

void *lista_primero(lista_t *lista)
{
	return (!lista || !lista->nodo_inicio) ? NULL : lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	return (!lista || !lista->nodo_inicio) ? NULL : lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista)
{
	return (!lista || !lista->nodo_inicio) ? true : false;
}

size_t lista_tamanio(lista_t *lista)
{
	return (!lista) ? 0 : lista->cantidad;
}

void lista_destruir(lista_t *lista)
{
	if (!lista)
		return;

	nodo_t *aux = lista->nodo_inicio;

	while (!lista_vacia(lista)) {
		lista->nodo_inicio = aux->siguiente;
		free(aux);
		aux = lista->nodo_inicio;
	}

	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (!lista)
		return;

	nodo_t *aux = lista->nodo_inicio;

	while (!lista_vacia(lista)) {
		lista->nodo_inicio = aux->siguiente;

		if (funcion)
			funcion(aux->elemento);
		
		free(aux);
		aux = lista->nodo_inicio;
	}

	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista)
		return NULL;

	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if (!iterador)
		return NULL;
	
	iterador->lista = lista;
	iterador->corriente = lista->nodo_inicio;
	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->corriente)
		return false;

	return (iterador->corriente) ? true : false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->corriente)
		return false;
	
	iterador->corriente = iterador->corriente->siguiente;

	return (iterador->corriente) ? true : false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->corriente)
		return NULL;

	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (!lista || !funcion)
		return 0;
	
	nodo_t *actual = lista->nodo_inicio;
	size_t cantidad = 0;

	while (actual) {
		cantidad++;
		
		if (!funcion(actual->elemento, contexto))
			return cantidad;

		actual = actual->siguiente;
	}

	return cantidad;
}
