#include "hash.h"
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct par {
	const char *clave;
	void *valor;
} par_t;

struct hash {
	lista_t **tabla;
	size_t capacidad;
	int cantidad;
};

int funcion_hash(const char *clave)
{
	if (!clave) return 0;

    	int hash = 0, i = 0;
	const int p = 31, m = 1e9 + 7;
    	int p_pow = 1;
	while (clave[i] != '\0') {
		hash = (hash + (clave[i] - 'a' + 1) * p_pow) % m;
        	p_pow = (p_pow * p) % m;
		i++;
	}
	return (hash >= 0) ? hash : -hash;
}

int posicion_hash(hash_t *hash, const char *clave)
{
	return funcion_hash(clave) % (int)hash->capacidad;
}

hash_t *hash_crear(size_t capacidad)
{
	hash_t *hash = malloc(sizeof(hash_t));
	if (!hash) return NULL;

	if (capacidad < 3)
		capacidad = 3;
	hash->capacidad = capacidad;
	hash->cantidad = 0;
	hash->tabla = calloc(capacidad, sizeof(lista_t *));

	return hash;
}

par_t *crear_par(const char *clave, void *elemento)
{
	char *clave_copia = malloc(strlen(clave) + 1);
	if (!clave_copia) return NULL;

	strcpy(clave_copia, clave);

	par_t *nuevo_par = malloc(sizeof(par_t));
	if (!nuevo_par) return NULL;

	nuevo_par->clave = clave_copia;
	nuevo_par->valor = elemento;

	return nuevo_par;
}

int *insertar_par_a_lista(lista_t *lista, const char *clave, void *elemento)
{
	par_t *nuevo_par = crear_par(clave, elemento);
	if (!nuevo_par) return NULL;

	lista_insertar(lista, nuevo_par);

	return (int *)1;
}

bool rehash_insertar(const char *clave, void *valor, hash_t *hash)
{
	int posicion = posicion_hash(hash, clave);

	if (!hash->tabla[posicion])
		hash->tabla[posicion] = lista_crear();
	lista_t *lista_actual = hash->tabla[posicion];

	if (!insertar_par_a_lista(lista_actual, clave, valor)) return NULL;
	hash->cantidad++;

	return hash;
}

void rehash(hash_t *hash)
{
	hash_t *nuevo_hash = hash_crear(hash->capacidad * 2);

	int i = 0;

	lista_t *lista_actual;

	while (i < hash->capacidad) {
		lista_actual = hash->tabla[i];
		if (!lista_vacia(lista_actual)) {
			par_t *par_actual = (par_t *)lista_quitar_de_posicion(lista_actual, 0);

			while (par_actual) {
				rehash_insertar(par_actual->clave, par_actual->valor, nuevo_hash);
				free((char *)par_actual->clave);
				free(par_actual);
				par_actual = (par_t *)lista_quitar_de_posicion(lista_actual, 0);
			}
		}
		lista_destruir(lista_actual);
		i++;
	}

	hash_t hash_aux;
	hash_aux = *hash;
	*hash = *nuevo_hash;
	*nuevo_hash = hash_aux;
	
	free(nuevo_hash->tabla);
	free(nuevo_hash);
}

par_t *buscar_par_en_lista(lista_t *lista, const char *clave, size_t *posicion_par)
{
	size_t j = 0;
	lista_iterador_t *iterador_actual;

	if (!lista_vacia(lista)) {
		for (iterador_actual = lista_iterador_crear(lista); lista_iterador_tiene_siguiente(iterador_actual); lista_iterador_avanzar(iterador_actual)) {
			par_t *par_actual = (par_t *)lista_iterador_elemento_actual(iterador_actual);

			if (strcmp(par_actual->clave, clave) == 0) {
				lista_iterador_destruir(iterador_actual);
				*posicion_par = j;
				return par_actual;
			}
				
			j++;
		}
		lista_iterador_destruir(iterador_actual);
	}

	return NULL;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (!hash || !clave) return NULL;

	if (hash->cantidad + 1 >= (int)hash->capacidad * 0.75)
		rehash(hash);

	int posicion = posicion_hash(hash, clave);

	if (!hash->tabla[posicion])
		hash->tabla[posicion] = lista_crear();
	if (!hash->tabla[posicion]) return NULL;

	lista_t *lista_actual = hash->tabla[posicion];

	size_t posicion_par = 0;

	par_t *par_encontrado = buscar_par_en_lista(lista_actual, clave, &posicion_par);

	if (par_encontrado) {
		if (anterior)
			*anterior = par_encontrado->valor;
		par_encontrado->valor = elemento;
	} else {
		if (anterior)
			*anterior = NULL;
		if (!insertar_par_a_lista(lista_actual, clave, elemento)) return NULL;
		hash->cantidad++;
	}

	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash || !clave) return NULL;

	void *elemento_quitado = NULL;

	int posicion = posicion_hash(hash, clave);

	if (!hash->tabla[posicion])
		return elemento_quitado;
	lista_t *lista_actual = hash->tabla[posicion];

	size_t posicion_par = 0;

	par_t *par_encontrado = buscar_par_en_lista(lista_actual, clave, &posicion_par);

	if (par_encontrado) {
		par_t *par_quitado = (par_t *)lista_quitar_de_posicion(lista_actual, posicion_par);
		elemento_quitado = par_quitado->valor;
		free((char *)par_quitado->clave);
		free(par_quitado);
		hash->cantidad--;
	}

	return elemento_quitado;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash || !clave) return NULL;

	void *elemento_buscado = NULL;

	int posicion = posicion_hash(hash, clave);

	if (!hash->tabla[posicion])
		return elemento_buscado;
	lista_t *lista_actual = hash->tabla[posicion];

	size_t posicion_par = 0;

	par_t *par_encontrado = buscar_par_en_lista(lista_actual, clave, &posicion_par);

	if (par_encontrado) {
		elemento_buscado = par_encontrado->valor;
	}

	return elemento_buscado;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash || !clave) return NULL;

	int posicion = posicion_hash(hash, clave);

	if (!hash->tabla[posicion])
		return false;
	lista_t *lista_actual = hash->tabla[posicion];

	size_t posicion_par = 0;

	par_t *par_encontrado = buscar_par_en_lista(lista_actual, clave, &posicion_par);

	return (par_encontrado) ? true : false;
}

size_t hash_cantidad(hash_t *hash)
{
	return (!hash) ? 0 : (size_t)hash->cantidad;
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash) return;

	int i = 0;

	lista_t *lista_actual;

	while (i < hash->capacidad) {
		lista_actual = hash->tabla[i];

		if (!lista_vacia(lista_actual)) {
			par_t *par_actual = (par_t *)lista_quitar_de_posicion(lista_actual, 0);

			while (par_actual) {
				if (destructor)
					destructor(par_actual->valor);
				free((char *)par_actual->clave);
				free(par_actual);
				par_actual = (par_t *)lista_quitar_de_posicion(lista_actual, 0);
			}
		}

		lista_destruir(lista_actual);
		i++;
	}

	free(hash->tabla);
	free(hash);
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	if (!hash || !f) return 0;

	size_t cant_recorridos = 0;
	int i = 0;

	lista_t *lista_actual;
	lista_iterador_t *iterador_actual;
	
	while (i < hash->capacidad) {
		lista_actual = hash->tabla[i];

		if (!lista_vacia(lista_actual)) {
			for (iterador_actual = lista_iterador_crear(lista_actual); lista_iterador_tiene_siguiente(iterador_actual); lista_iterador_avanzar(iterador_actual)) {
				par_t *par_actual = (par_t *)lista_iterador_elemento_actual(iterador_actual);

				cant_recorridos++;
				if (!f(par_actual->clave, par_actual->valor, aux)) {
					lista_iterador_destruir(iterador_actual);
					return cant_recorridos;
				}
			}
			lista_iterador_destruir(iterador_actual);
		}
		i++;
	}

	return cant_recorridos;
}