/*
 * sci_campos.c
 *
 * Definicion de funciones interfaces entre Scilab y las rutinas que crean y muestran informacion de los campos.
 *
 * Ultima actualización: 06/10/2009
 *
 * 27/06/2009: Se reemplazo bigint por unsigned int en los tipos de las variables. Para mayor claridad.
 *             Creado un nuevo arreglo de enteros para almacenar los elementos del campo en formato entero.
 *             El puntero *elementos almacena un puntero a ese arreglo.
 *             Se reemplazo todas las llamadas a pow por orden(p,n)
 *             Definición de la función sci_orden()
 *
 * 28/06/2009: Se agrego una condicion para validar que el polinomio_primitivo no sea una matriz
 *             Definición de la función sci_elementos_primitivos()
 *             Definicion de la funcion sci_primo_caracteristico()
 *             Definicion de la funcion sci_grado()
 *
 * 29/06/2009: Validación de la funcion sci_elementos_primitivos()
 *
 * 30/06/2009: Definicion de la funcion sci_grado()
 *             Definición de la función sci_polinomio_primitivo()
 *
 * 06/07/2009: Redefinición de sci_elementos_primitivos() para n > 1 solamente.
 *
 * 13/07/2009: Definicion de sci_polinomio_minimo()
 *
 * 14/07/2009: Definicion de sci_elementos_campos()
 *             PENDIENTE: Revisar el código para localizar posibles bugs y errores de programacion
 *
 * 15/07/2009: Definicion de sci_devolver_polinomio_primitivo_por_defecto()
 *
 * 19/07/2009: Pequeño cambio en sci_elementos_campos() para devolver elementos de campos de extension
 *
 * 26/07/2009: Definicion sci_elementos_primitivos() borrada
 *
 * 29/07/2009: varios cambios
 *
 * 01/08/2009: Cambios varios
 *
 * 22/08/2009: Cambios en las funciones de salida para imprimir mensajes mas descriptivos
 *             Cambios varios
 *             Comentarios extras para hacer el codigo mas legible
 *             Eliminada la interfaz sci_elementos_campos(). Se implementa en un macro
 *             Eliminada la interfaz sci_polinomio_primitivo(). Se implementa en un macro
 *
 * 23/08/2009: Eliminada la interfaz sci_primo_caracteristico(). Se implementa en una macro
 *             Eliminada la interfasz sci_grado(). Se implementa en un macro
 *
 * 01/10/2009: Comentarios de ayuda.
 *
 * 03/10/2009: La variable 'elemento' de sci_polinomio_minimo() es entera con signo.
 *             si n = 1, 'elemento' se valida que esté entre el rango de 0 y p - 1
 *             si n > 1, 'elemento' se valida que esté en el rango de -1 y p^n - 2
 *             Corregido validacion de p.
 *             Corregido validacion de n en sci_es_polinomio_primitivo()
 *
 * 05/10/2009: Arreglar sci_devolver_polinomio_primitivo_por_defecto() para trabajar con n > 1
 *
 * 06/10/2009: Inclusion de polinomios_primitivos.h
 *             Modificado sci_devolver_polinomio_primitivo_por_defecto() para trabajar con n > 1
 *
 * Copyright © Daniel E Rodriguez – UIS.
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "stack-c.h"
#include "Scierror.h"
#include "localization.h"
#include "../../src/c/include/campos.h"
#include "../../src/c/include/funciones.h"
#include "../../src/c/include/polinomios.h"
#include "../../src/c/include/polinomios_primitivos.h"

#define error(msg) Scierror(999,_("%s: Error, %s.\n"), fname, (msg));

/* funcion interfaz de la rutina crear_campo(). 
   Argumentos de entrada: p, n, polinomio_primitivo
   Salida: Lista campo finito */
int sci_crear_campo(char *fname)
{
    static unsigned int l1, m1, n1, l2, m2, n2, l3, m3, n3, l4, m4, n4, l5, m5, n5; /* variables para almacenar argumentos de entrada */
    static unsigned int l51, l52, l53, l54; /* variables para almacenar la lista */
    static int minrhs = 2, maxrhs = 3, minlhs = 1, maxlhs = 1;
    unsigned int p, n, *p_prim = NULL, *elementos = NULL, maxpn = MAX_P_N; /* variables temporales */
    int resultado, i;
    
    CheckRhs(minrhs, maxrhs);
    CheckLhs(minlhs, maxlhs);
    
    /* leer p */
    GetRhsVar(1, "i", &m1, &n1, &l1);
    
    /* validar que p sea positivo */
    if ((*istk(l1)) < 2){
       error("p debe ser > 1");
       return 1;
    }
    
    p = *istk(l1);
    
    if ((m1 > 1) || (n1 > 1)){
       error("p debe ser un escalar");
       return 1;
    }
    
    /* p debe ser primo */
    if (!es_primo(p)){
       error("p debe ser un primo > 1");
       return 1;
    }
    
    /* Se limita que p no sea mayor a MAX_P. Esta limitación es necesaria para efectos de evitar desbordamiento de memoria y de calcular el polinomio primitivo para n = 1*/
    if (p > MAX_P){
       Scierror(999,_("%s: Error, p es mayor que el valor maximo permitido: %lu.\n"), fname, MAX_P);
       return 1;
    }
    
    /* leer n */
    GetRhsVar(2, "i", &m2, &n2, &l2);
    
    /* validar que n sea positivo */
    if ((*istk(l2)) < 1){
       error("n debe ser >= 1");
       return 1;
    }
    
    n = *istk(l2);
    
    if ((m2 > 1) || (n2 > 1)){
      error("n debe ser un escalar");
      return 1;
    }
    
    /* validar que n sea menor que MAX_N */
    if (n > MAX_N){
      Scierror(999,_("%s: Error, n es mayor que el valor maximo permitido: %lu.\n"), fname, MAX_N);
      return 1;
    }
    
    /* no olvidarse de validar el tamaño de p^n, debe ser menor que maxpn */
   if ((n * log((double) p)) > log((double) maxpn)){
      Scierror(999,_("%s: Error, p^n es mayor que el valor maximo permitido: %lu.\n"), fname, maxpn);
      return 1;
   }
    
    /* polinomio primitivo especificado en la lista de argumentos de entrada */
    if (Rhs == 3){
            
       /* Se va a usar un polinomio por defecto para n = 1 */
       if (n == 1){
         error("No puede especificar un polinomio, se va a usar un polinomio primitivo por defecto para n = 1");
         return 1;
       } else {
         /* se introdujo el argumento opcional, leer el polinomio primitivo */
         GetRhsVar(3, "i", &m3, &n3, &l3);
         
         /* validar que los elementos del polinomio no sean negativos */
         for (i = 0; i < n3; i++){
         
             if ((*(istk(l3 + i))) < 0){
                error("los elementos del polinomio primitivo deben ser enteros positivos");
                return 1;
             }
             
         }
         
         /* validar que no se haya introducido una matriz */
         if (m3 > 1){
            error("el argumento pol_prim no debe ser una matriz");
            return 1;
         }
       
         /* validar el grado del polinomio primitivo */
         if ((n3 - 1) != n){
            Scierror(999,_("%s: Error, el grado del polinomio debe ser %u.\n"), fname, n);
            return 1;
         }
         
         /* copias el puntero */
         p_prim = istk(l3);
         
         /* el coeficiente mas significativo no puede ser cero*/
         if (p_prim[n3 - 1] == 0){
            error("el último término del polinomio primitivo no puede ser cero");
            return 1;
         }
         
         /* validar que los elementos esten dentro del rango */
         for (i = 0; i < n3; i++){
             
             if (p_prim[i] >= p){
              Scierror(999,_("%s: Error, los coeficientes de pol_prim deben estar entre 0 y %u.\n"), fname, p - 1);
              return 1;
             }
             
         }
       
         /* validar si el polinomio es primitivo, si no lo es, marcar error y salir */
         es_polinomio_primitivo(p_prim, p, n, &resultado);
         
         if (resultado == NO){
            error("pol_prim no es polinomio primitivo");
            return 1;
         }

       }
       
    } else {
  
      /* no se especifico un polinomio primitivo, se debe especificar uno */
      if (n > 1){
         error("Se debe especificar un polinomio primitivo");
         return 1;
	  } else {
		  /* crear un arreglo en el stack de memoria para pol_prim para n = 1*/
		  m3 = 1;
		  n3 = 2;
		  CreateVar(3, "i", &m3, &n3, &l3);
		  p_prim = istk(l3);
	  }
          
   }
    
    /* crear un arreglo de enteros en el stack de scilab para almacenar los elementos del campo */
    if (n == 1){
          
      /* creando un vector que almacena los enteros */
      m4 = 1;
      n4 = orden(p, n);
      CreateVar(4, "i", &m4, &n4, &l4);
      elementos = istk(l4);
      
    } else {
          
      /* creando una matriz, en cada fila se almacena la tupla */ 
      m4 = orden(p, n);
      n4 = n;
      CreateVar(4, "i", &m4, &n4, &l4);
      elementos = istk(l4);
      
    }
    
    crear_campo(p, n, p_prim, elementos);
    
    /* elementos de la lista */
    m5 = 4;
    n5 = 1;
    
    /* creando la lista */
    /* hay que crear la lista de elementos */
    CreateVar(5, "l", &m5, &n5, &l5);
    CreateListVarFrom(5, 1, "i", &m1, &n1, &l51, &l1);
    CreateListVarFrom(5, 2, "i", &m2, &n2, &l52, &l2);
    CreateListVarFrom(5, 3, "i", &m3, &n3, &l53, &l3);
    CreateListVarFrom(5, 4, "i", &m4, &n4, &l54, &l4);
    
    /* imprimir salida */
    sciprint("Campo de Galois GF(%u) creado.\n", orden(p, n));
    sciprint("Primo caracteristico: %u\n", p);
    sciprint("Grado: %u\n", n);
    sciprint("Polinomio primitivo: ");
    sciprint("[ ");
    
    for (i = 0; i < n3; i++)
        sciprint("%d ", p_prim[i]);
        
    sciprint("]\n\n");
    
    LhsVar(1) = 5;
    
    return 0;
}

/* funcion interfaz que imprime el orden (numero de elementos) de un campo
   Entrada: Lista campo
   Salida: Orden */
int sci_orden(char *fname)
{
    static unsigned int l0, m0, n0;
    static unsigned int l1, m1, n1, l2, m2, n2, l3, m3, n3;
    static int minrhs = 1, maxrhs = 1, minlhs = 1, maxlhs = 1;
    static unsigned int p, n;
    
    /* longitud de la lista */
    m0 = 0;
    n0 = 0;
    
    CheckRhs(minrhs, maxrhs);
    CheckLhs(minlhs, maxlhs);
    
    GetRhsVar(1, "l", &m0, &n0, &l0);
    
    /* validar el tamaño de la lista */
    CheckLength(4, m0, 4);
    
    /* la idea es validar toda la lista */
    
    /* leer p y n */
    GetListRhsVar(1, 1, "i", &m1, &n1, &l1);
    p = *istk(l1);
    
    GetListRhsVar(1, 2, "i", &m2, &n2, &l2);
    n = *istk(l2);
    
    m3 = 1;
    n3 = 1;
    
    CreateVar(2, "i", &m3, &n3, &l3);
    
    *istk(l3) = orden(p, n);
    
    LhsVar(1) = 2;
    
    return 0;
}

/* Devuelve el polinomio primitivo asociado a un elemento del campo dado p y n 
   Entrada: p, n y elemento 
   Salida: polinomio minimo */
int sci_polinomio_minimo(char *fname)
{
    unsigned int l1, m1, n1, l2, m2, n2, l3, m3, n3, l4, m4, n4;
    static int minrhs = 3, maxrhs = 3, minlhs = 1, maxlhs = 1;
    unsigned int p, n, *pol_minimo;
    int elemento;
    
    CheckRhs(minrhs, maxrhs);
    CheckLhs(minlhs, maxlhs);

    GetRhsVar(1, "i", &m1, &n1, &l1);
    
    /* validar que p sea positivo */
    if ((*istk(l1)) < 2){
       error("p debe ser > 1");
       return 1;
    }
    
    p = *istk(l1);
    
    if ((n1 > 1) || (m1 > 1)){
       error("p debe ser un escalar");
       return 1;
    }
    
    if (!es_primo(p)){
       error("p debe ser un primo > 1");
       return 1;
    }
    
    if (p > MAX_P){
       Scierror(999,_("%s: Error, p es mayor que el valor maximo permitido: %lu.\n"), fname, MAX_P);
       return 1;
    }
   
    GetRhsVar(2, "i", &m2, &n2, &l2);
    
    if ((*istk(l2)) < 1){
       error("n debe ser >= 1");
       return 1;
    }
    
    n = *istk(l2);
    
    if ((n2 > 1) || (m2 > 1)){
       error("n debe ser un escalar");
       return 1;
    }
    
    GetRhsVar(3, "i", &m3, &n3, &l3);
    elemento = *istk(l3);
    
    if (n == 1){
    
       if ((elemento < 0) || (elemento >= p)){
           Scierror(999,_("%s: Error, elemento debe estar entre 0 y %lu para los campos primos\n"), fname, p - 1);
           return 1;
       }
    
    } else {
           
       if ((elemento < -1) || (elemento >= (orden(p, n) - 1))){
           Scierror(999,_("%s: Error, elemento debe estar entre 0 y %lu para los campos de extension\n"), fname, orden(p,n) - 2);
           return 1;
       }
      
    }
    
    m4 = 1;
    n4 = n + 1;
    
    CreateVar(4, "i", &m4, &n4, &l4);
    
    pol_minimo = istk(l4);
    
    polinomio_minimo(p, n, elemento, pol_minimo);
    
    LhsVar(1) = 4;
    
    return 0;
}

/* Devuelve el polinomio primitivo por defecto para p > 2 y n >= 1. Esta interface es usada por algunos macros.
 * Entrada: p, n 
 * Salida: arreglo de enteros que representa el polinomio primitivo para el campo primo o de extension */
int sci_devolver_polinomio_primitivo_por_defecto(char *fname)
{
    static unsigned int l1, m1, n1, l2, m2, n2, l3, m3, n3;
    static int minrhs = 2, maxrhs = 2, minlhs = 1, maxlhs = 1;
    static unsigned int n, p, pol_prim_def, index_p;
    
    CheckRhs(minrhs, maxrhs);
    CheckLhs(minlhs, maxlhs);
    
    GetRhsVar(1, "i", &m1, &n1, &l1);
    
    /* validar que p sea positivo */
    if ((*istk(l1)) < 2){
       error("p debe ser > 1");
       return 1;
    }
    
    p = *istk(l1);
    
    if ((n1 > 1) || (m1 > 1)){
       error("p debe ser un escalar");
       return 1;
    }
    
    if (!es_primo(p)){
       error("p debe ser un primo > 1");
       return 1;
    }
    
    if (p > MAX_P){
       Scierror(999,_("%s: Error, p es mayor que el valor maximo permitido: %lu.\n"), fname, MAX_P);
       return 1;
    }
    
    if (p > MAX_P_TABLA_GRADOS){
       Scierror(999,_("%s: Error, p es mayor que el valor maximo permitido para esta funcion: %lu.\n"), fname, MAX_P_TABLA_GRADOS);
       return 1;
    }
   
    GetRhsVar(2, "i", &m2, &n2, &l2);
    
    if ((*istk(l2)) < 1){
       error("n debe ser >= 1");
       return 1;
    }
    
    n = *istk(l2);
    
    if ((n2 > 1) || (m2 > 1)){
       error("n debe ser un escalar");
       return 1;
    }
    
    if (n < 1){
       error("n debe ser >= 1");
       return 1;
    }
    
    /* hay que validar n de acuerdo con el p dado */
    index_p = devolver_index_primo_caracteristico(p);
    
    if (n > tabla_grados_max_pol_prim[index_p]){
       Scierror(999,_("%s: Error, %lu es un valor muy grande para el primo %lu, posibles desbordes de memoria.\n"), fname, n, p);
       return 1; 
    } 
    
    m3 = 1;
    n3 = n + 1;
    
    CreateVar(3, "i", &m3, &n3, &l3);
    pol_prim_def = istk(l3);
    
    devolver_polinomio_primitivo_por_defecto(p, n, pol_prim_def);
    
    LhsVar(1) = 3;
    
    return 0;
}

/* funcion interfaz que imprime si un polinomio es primitivo o no
   Entrada: Polinomio (arreglo coeficientes), p, n
   Salida: 0 (no es polinomio primitivo)
           1 (es polinomio primitivo) */
int sci_es_polinomio_primitivo(char *fname)
{
    static unsigned int l1, m1, n1, l2, m2, n2, l3, m3, n3, l4, m4, n4;
    static int minrhs = 3, maxrhs = 3, minlhs = 1, maxlhs = 1;
    unsigned int p, n, *res = NULL, maxpn = MAX_P_N, i;
    unsigned int *pol_prim;

    CheckRhs(minrhs, maxrhs);
    CheckLhs(minlhs, maxlhs);
    
    /* leer el polinomio */
    GetRhsVar(1, "i", &m1, &n1, &l1);

    /* validar que los elementos del polinomio no sean negativos */
    for (i = 0; i < n1; i++){
         
         if ((*(istk(l1 + i))) < 0){
            error("los elementos del polinomio primitivo deben ser enteros positivos");
            return 1;
         }
             
    }

    /* copiar puntero polinomio */
    pol_prim = istk(l1);

    /* validar que no se haya introducido una matriz */
    if (m1 > 1){
       error("el argumento pol_prim no debe ser una matriz");
       return 1;
    }

    /* leer p */
    GetRhsVar(2, "i", &m2, &n2, &l2);
    
    /* validar que p sea positivo */
    if ((*istk(l2)) < 2){
       error("p debe ser > 1");
       return 1;
    }
    
    p = *istk(l2);
    
    if ((m2 > 1) || (n2 > 1)){
       error("p debe ser un escalar");
       return 1;
    }
    
    if (!es_primo(p)){
       error("p debe ser un primo > 1");
       return 1;
    }
    
    if (p > MAX_P){
       Scierror(999,_("%s: Error, p es mayor que el valor maximo permitido: %lu.\n"), fname, MAX_P);
       return 1;
    }

     /* validar que los elementos del polinomio esten dentro del rango */
    for (i = 0; i < n1; i++){
             
       if ((pol_prim[i] >= p)){
          Scierror(999, _("%s: Error, Los coeficientes de p_prim deben estar en el rango entre 0 y %d\n"), fname, (p - 1));
          return 1;
       }
             
    }
    
    /* el coeficiente mas significativo no puede ser 0 */
    if (pol_prim[n1 - 1] == 0){
       error("el último término del polinomio primitivo no puede ser cero");
       return 1;
    }
    
    /* leer n */
    GetRhsVar(3, "i", &m3, &n3, &l3);
    
    /* n debe ser mayor que 1 */
    if ((*istk(l3)) < 2){
       error("n debe ser > 1");
       return 1;
    }
    
    n = *istk(l3);
    
    if ((m3 > 1) || (n3 > 1)){
      error("n debe ser un escalar");
      return 1;
    }
    
    /* validar el grado del polinomio primitivo */
    if ((n1 - 1) != n){
       error("el grado del pol_prim debe ser igual a n");
       return 1;
    }
    
    /* validar que n sea menor que MAX_N */
    if (n > MAX_N){
      Scierror(999,_("%s: Error, n es mayor que el valor maximo permitido: %lu.\n"), fname, MAX_N);
      return 1;
    }
    
    /* no olvidarse de validar el tamaño de p^n */
    if ((n * log((double) p)) > log((double) maxpn)){
       Scierror(999,_("%s: Error, p^n es mayor que el valor maximo permitido: %lu.\n"), fname, MAX_P_N);
       return 1;
    }
    
    m4 = 1;
    n4 = 1;
    
    CreateVar(4, "i", &m4, &n4, &l4);
    
    /* siempre hay que inicializar variables*/
    res = istk(l4);
    
    /* llamar a la funcion que determina la primivicidad del polinomio */
    es_polinomio_primitivo(pol_prim, p, n, res);
    
    /* no imprimir salida, para poder ser usada por los macros */
    
    LhsVar(1) = 4;
    
    return 0;
}
