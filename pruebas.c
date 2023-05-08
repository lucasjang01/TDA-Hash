#include "src/hash.h"
#include "pa2m.h"
#include <stdlib.h>

void hash_crear_me_devuelve_un_hash()
{
	hash_t *hash = hash_crear(3);
	pa2m_afirmar(hash != NULL, "Se crea el hash");
	hash_destruir(hash);
}

void insertar_y_actualizar_pares_clave_valor()
{
	hash_t *hash = hash_crear(3);

	int elementos[] = {1, 2, 3, 4, 5, 6};

	const char* clave1 = "clave1";
	const char* clave2 = "clave2";
	const char* clave3 = "clave3";

	void *anterior = elementos + 0;

	pa2m_afirmar(hash_insertar(hash, clave1, elementos + 0, &anterior) != NULL, "Inserto el par {clave1: 1}");
	pa2m_afirmar(hash_insertar(hash, clave2, elementos + 1, &anterior) != NULL, "Inserto el par {clave2: 2}");
	pa2m_afirmar(hash_insertar(hash, clave3, elementos + 2, &anterior) != NULL, "Inserto el par {clave3: 3}");
	pa2m_afirmar(anterior == NULL, "Anterior es NULL");
	pa2m_afirmar(hash_cantidad(hash) == 3, "La cantidad de elementos es 3");

	anterior = elementos + 0;

	pa2m_afirmar(hash_insertar(hash, clave1, elementos + 3, &anterior) != NULL, "Inserto el par {clave1: 4}");
	pa2m_afirmar(hash_insertar(hash, clave2, elementos + 4, &anterior) != NULL, "Inserto el par {clave2: 5}");
	pa2m_afirmar(hash_insertar(hash, clave3, elementos + 5, &anterior) != NULL, "Inserto el par {clave3: 6}");
	pa2m_afirmar(anterior == elementos + 2, "Anterior es el elemento reemplazado");
	pa2m_afirmar(hash_cantidad(hash) == 3, "La cantidad de elementos es 3");

	hash_destruir(hash);
}

void insertar_pasando_hash_null_devuelve_null()
{
	int elementos[] = {1};

	const char* clave1 = "clave1";

	void *anterior = NULL;
	pa2m_afirmar(hash_insertar(NULL, clave1, elementos + 0, &anterior) == NULL, "Insertar en hash NULL devuelve NULL");
}

void quitar_claves_que_estan_en_el_hash_devuelve_el_elemento()
{
	hash_t *hash = hash_crear(3);

	int elementos[] = {1, 2, 3};

	const char* clave1 = "clave1";
	const char* clave2 = "clave2";
	const char* clave3 = "clave3";

	void *anterior = NULL;

	pa2m_afirmar(hash_insertar(hash, clave1, elementos + 0, &anterior) != NULL, "Inserto la clave1");
	pa2m_afirmar(hash_insertar(hash, clave2, elementos + 1, &anterior) != NULL, "Inserto la clave2");
	pa2m_afirmar(hash_insertar(hash, clave3, elementos + 2, &anterior) != NULL, "Inserto la clave3");

	pa2m_afirmar(hash_quitar(hash, clave1) == elementos + 0, "Quito la clave1 y me devuelve el elemento");
	pa2m_afirmar(hash_quitar(hash, clave2) == elementos + 1, "Quito la clave2 y me devuelve el elemento");
	pa2m_afirmar(hash_quitar(hash, clave3) == elementos + 2, "Quito la clave3 y me devuelve el elemento");
	pa2m_afirmar(hash_cantidad(hash) == 0, "La cantidad de elementos es 0");

	hash_destruir(hash);
}

void quitar_clave_que_no_esta_en_el_hash_devuelve_null()
{
	hash_t *hash = hash_crear(3);

	int elementos[] = {1, 2};

	const char* clave1 = "clave1";
	const char* clave2 = "clave2";
	const char* clave3 = "clave3";

	void *anterior = NULL;

	hash_insertar(hash, clave1, elementos + 0, &anterior);
	hash_insertar(hash, clave2, elementos + 1, &anterior);

	pa2m_afirmar(hash_quitar(hash, clave3) == NULL, "Quito una clave que no esta en el hash y me devuelve NULL");
	pa2m_afirmar(hash_cantidad(hash) == 2, "La cantidad de elementos es 3");

	hash_destruir(hash);
}

void quitar_pasando_hash_null_devuelve_null()
{
	const char* clave1 = "clave1";

	pa2m_afirmar(hash_quitar(NULL, clave1) == NULL, "Quitar en hash NULL devuelve NULL");
}

void obtener_claves_que_estan_en_el_hash_devuelve_el_elemento()
{
	hash_t *hash = hash_crear(3);

	int elementos[] = {1, 2, 3};

	const char* clave1 = "clave1";
	const char* clave2 = "clave2";
	const char* clave3 = "clave3";

	void *anterior = NULL;

	pa2m_afirmar(hash_insertar(hash, clave1, elementos + 0, &anterior) != NULL, "Inserto la clave1");
	pa2m_afirmar(hash_insertar(hash, clave2, elementos + 1, &anterior) != NULL, "Inserto la clave2");
	pa2m_afirmar(hash_insertar(hash, clave3, elementos + 2, &anterior) != NULL, "Inserto la clave3");

	pa2m_afirmar(hash_obtener(hash, clave1) == elementos + 0, "Obtengo la clave1 y me devuelve el elemento");
	pa2m_afirmar(hash_obtener(hash, clave2) == elementos + 1, "Obtengo la clave2 y me devuelve el elemento");
	pa2m_afirmar(hash_obtener(hash, clave3) == elementos + 2, "Obtengo la clave3 y me devuelve el elemento");

	hash_destruir(hash);
}

void obtener_clave_que_no_esta_en_el_hash_devuelve_null()
{
	hash_t *hash = hash_crear(3);

	int elementos[] = {1, 2, 3};

	const char* clave1 = "clave1";
	const char* clave2 = "clave2";
	const char* clave3 = "clave3";

	void *anterior = NULL;

	hash_insertar(hash, clave1, elementos + 0, &anterior);
	hash_insertar(hash, clave2, elementos + 1, &anterior);

	pa2m_afirmar(hash_obtener(hash, clave3) == NULL, "Obtengo una clave que no esta en el hash y me devuelve NULL");

	hash_destruir(hash);
}

void obtener_pasando_hash_null_devuelve_null()
{
	const char* clave1 = "clave1";

	pa2m_afirmar(hash_obtener(NULL, clave1) == NULL, "Obtener en hash NULL devuelve NULL");
}

void contiene_devuelve_true_si_la_clave_esta_en_el_hash()
{
	hash_t *hash = hash_crear(3);

	int elementos[] = {1, 2};

	const char* clave1 = "clave1";
	const char* clave2 = "clave2";

	void *anterior = NULL;

	hash_insertar(hash, clave1, elementos + 0, &anterior);
	hash_insertar(hash, clave2, elementos + 1, &anterior);

	pa2m_afirmar(hash_contiene(hash, clave2) == true, "El hash contiene la clave");

	hash_destruir(hash);
}

void contiene_devuelve_false_si_la_clave_no_esta_en_el_hash()
{
	hash_t *hash = hash_crear(3);

	int elementos[] = {1, 2};

	const char* clave1 = "clave1";
	const char* clave2 = "clave2";
	const char* clave3 = "clave3";

	void *anterior = NULL;

	hash_insertar(hash, clave1, elementos + 0, &anterior);
	hash_insertar(hash, clave2, elementos + 1, &anterior);

	pa2m_afirmar(hash_contiene(hash, clave3) == false, "El hash no contiene la clave");

	hash_destruir(hash);
}

void contiene_devuelve_false_pasando_hash_null()
{
	const char* clave1 = "clave1";

	pa2m_afirmar(hash_contiene(NULL, clave1) == false, "Devuelve NULL pasando hash NULL");
}

void la_cantidad_se_actualiza_correctamente()
{
	hash_t *hash = hash_crear(3);

	int elementos[] = {1, 2, 3, 4, 5, 6};

	const char* clave1 = "clave1";
	const char* clave2 = "clave2";
	const char* clave3 = "clave3";

	void *anterior = NULL;

	hash_insertar(hash, clave1, elementos + 0, &anterior);
	hash_insertar(hash, clave2, elementos + 1, &anterior);
	pa2m_afirmar(hash_insertar(hash, clave3, elementos + 2, &anterior) != NULL, "Inserto 3 elementos");
	pa2m_afirmar(hash_cantidad(hash) == 3, "La cantidad de elementos es 3");

	hash_insertar(hash, clave1, elementos + 3, &anterior);
	hash_insertar(hash, clave2, elementos + 4, &anterior);
	pa2m_afirmar(hash_insertar(hash, clave3, elementos + 5, &anterior) != NULL, "Actualizo 3 elementos");
	pa2m_afirmar(hash_cantidad(hash) == 3, "La cantidad de elementos sigue siendo 3");

	hash_quitar(hash, clave1);
	hash_quitar(hash, clave2);
	pa2m_afirmar(hash_quitar(hash, clave3) != NULL, "Quito 3 elementos");
	pa2m_afirmar(hash_cantidad(hash) == 0, "La cantidad de elementos es 0");

	pa2m_afirmar(hash_insertar(hash, clave3, elementos + 2, &anterior) != NULL, "Inserto devuelta un elemento");
	pa2m_afirmar(hash_cantidad(hash) == 1, "La cantidad de elementos es 1");

	hash_destruir(hash);
}

void cantidad_devuelve_cero_pasando_hash_null()
{
	pa2m_afirmar(hash_cantidad(NULL) == 0, "Devuelve 0 pasando hash NULL");
}

void destruir_todo_libera_la_memoria_de_los_elementos()
{
	hash_t *hash = hash_crear(3);

	const char* clave1 = "clave1";
	const char* clave2 = "clave2";
	const char* clave3 = "clave3";
	const char* clave4 = "clave4";
	const char* clave5 = "clave5";

	void *anterior = NULL;

	hash_insertar(hash, clave1, malloc(sizeof(int)), &anterior);
	hash_insertar(hash, clave2, malloc(sizeof(int)), &anterior);
	hash_insertar(hash, clave3, malloc(sizeof(int)), &anterior);
	hash_insertar(hash, clave4, malloc(sizeof(int)), &anterior);
	hash_insertar(hash, clave5, malloc(sizeof(int)), &anterior);

	hash_destruir_todo(hash, free);
}

bool sumar_contador(const char *clave, void *valor, void *contador)
{
	(*(int *)contador)++;
  	return true;
}

bool sumar_hasta_3(const char *clave, void *valor, void *contador)
{
	(*(int *)contador)++;
  	return ((*(int *)contador) == 3) ? false : true;
}

void itera_por_todos_los_elementos_y_devuelve_la_cantidad_de_elementos_iterados()
{
	hash_t *hash = hash_crear(3);

	int elementos[] = {1, 2, 3, 4, 5, 6};

	const char* clave1 = "clave1";
	const char* clave2 = "clave2";
	const char* clave3 = "clave3";
	const char* clave4 = "clave4";
	const char* clave5 = "clave5";
	const char* clave6 = "clave6";

	void *anterior = NULL;

	hash_insertar(hash, clave1, elementos + 0, &anterior);
	hash_insertar(hash, clave2, elementos + 1, &anterior);
	hash_insertar(hash, clave3, elementos + 2, &anterior);
	hash_insertar(hash, clave4, elementos + 3, &anterior);
	hash_insertar(hash, clave5, elementos + 4, &anterior);
	pa2m_afirmar(hash_insertar(hash, clave6, elementos + 5, &anterior) != NULL, "Inserto 6 elementos");

	int contador = 0;

	pa2m_afirmar(hash_con_cada_clave(hash, sumar_contador, (void *)&contador) == 6, "Se iteran todos los elementos");
	pa2m_afirmar(contador == 6, "La funcion de iteracion fue llamada 6 veces");

	contador = 0;

	pa2m_afirmar(hash_con_cada_clave(hash, sumar_hasta_3, (void *)&contador) == 3, "Se iteran los primeros 3 elementos");
	pa2m_afirmar(contador == 3, "La funcion de iteracion fue llamada 3 veces");

	hash_destruir(hash);
}

void iterador_interno_devuelve_cero_pasando_funcion_de_iteracion_null()
{
	hash_t *hash = hash_crear(3);

	int elementos[] = {1};

	const char* clave1 = "clave1";

	void *anterior = NULL;

	hash_insertar(hash, clave1, elementos + 0, &anterior);

	int contador = 0;

	pa2m_afirmar(hash_con_cada_clave(hash, NULL, (void *)&contador) == 0, "Devuelve 0 pasando funcion de iteracion NULL");

	hash_destruir(hash);
}

void iterador_interno_devuelve_cero_pasando_hash_null()
{
	int contador = 0;

	pa2m_afirmar(hash_con_cada_clave(NULL, sumar_contador, (void *)&contador) == 0, "Devuelve 0 pasando hash NULL");
}

int main()
{
	pa2m_nuevo_grupo("Hash crear");

	hash_crear_me_devuelve_un_hash();

	pa2m_nuevo_grupo("Hash insertar");

	insertar_y_actualizar_pares_clave_valor();
	insertar_pasando_hash_null_devuelve_null();

	pa2m_nuevo_grupo("Hash quitar");

	quitar_claves_que_estan_en_el_hash_devuelve_el_elemento();
	quitar_clave_que_no_esta_en_el_hash_devuelve_null();
	quitar_pasando_hash_null_devuelve_null();

	pa2m_nuevo_grupo("Hash obtener");

	obtener_claves_que_estan_en_el_hash_devuelve_el_elemento();
	obtener_clave_que_no_esta_en_el_hash_devuelve_null();
	obtener_pasando_hash_null_devuelve_null();

	pa2m_nuevo_grupo("Hash contiene");

	contiene_devuelve_true_si_la_clave_esta_en_el_hash();
	contiene_devuelve_false_si_la_clave_no_esta_en_el_hash();
	contiene_devuelve_false_pasando_hash_null();

	pa2m_nuevo_grupo("Hash cantidad");

	la_cantidad_se_actualiza_correctamente();
	cantidad_devuelve_cero_pasando_hash_null();

	pa2m_nuevo_grupo("Hash destruir todo (no debería perder memoria)");

	pa2m_nuevo_grupo("Hash con cada clave");

	itera_por_todos_los_elementos_y_devuelve_la_cantidad_de_elementos_iterados();
	iterador_interno_devuelve_cero_pasando_funcion_de_iteracion_null();
	iterador_interno_devuelve_cero_pasando_hash_null();

	return pa2m_mostrar_reporte();
}
