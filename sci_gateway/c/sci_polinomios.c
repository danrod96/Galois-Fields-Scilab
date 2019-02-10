/*
 * sci_polinomios.c
 *
 * Definicion de funciones interfaces entre Scilab y las rutinas de manejo de polinomios
 *
 * Ultima actualización: 25/08/2009
 *
 * 03/07/2009: Definicion de la funcion sci_sumar_polinomios()
 *             Definicion de la funcion sci_restar_polinomios()
 *
 * 05/07/2009: producto_polinomio() eliminada
 *
 * 09/07/2009: Definicion de sci_dividir_polinomios()
 *
 * 23/08/2009: Cambios en las salidas del las funciones. Mas comentarios. Gestion de errores al usar malloc().
 *
 * 25/08/2009: Eliminada la funcion sci_sumar_polinomios(), se define en un macro.
 *
 * Copyright © Daniel E Rodriguez – UIS.
 */

#include <string.h>
#include "stack-c.h"
#include "Scierror.h"
#include "localization.h"
#include "../../src/c/include/polinomios.h"
#include "../../src/c/include/funciones.h"

#define error(msg) Scierror(999,_("%s: Error, %s.\n"), fname, (msg));
#define error2(funcion, msg) Scierror(999,_("%s: Error, %s.\n"), funcion, (msg));

/* funcion interfaz de la rutina restar_polinomios() 
 * Entrada: dos polinomios del mismo tamaño
 * Salida: la resta de los dos polinomios */
int sci_restar_polinomios(char *fname)
{
    static unsigned int l1, m1, n1, l2, m2, n2, l3, m3, n3, l4, m4, n4;
    static int minrhs = 3, maxrhs = 3, minlhs = 1, maxlhs = 1;
    unsigned int p, i, tam, *pol1, *pol2;
    
    CheckRhs(minrhs, maxrhs);
    CheckLhs(minlhs, maxlhs);
    
    /* leer el primer polinomio */
    GetRhsVar(1, "i", &m1, &n1, &l1);
    
    /* validar que los elementos del polinomio no sean negativos */
    for (i = 0; i < n1; i++){
         
         if ((*(istk(l1 + i))) < 0){
            error("los elementos del polinomio primitivo deben ser enteros positivos");
            return 1;
         }
             
    }
    
    pol1 = istk(l1);
    
    if (pol1[n1 - 1] == 0){
       error("el último término del polinomio no puede ser cero");
       return 1;
    }
    
    /* validar que el primer argumento no sea una matriz */
    if ((m1 > 1)){
       error("pol1 debe ser un vector de la forma [0 .. p - 1]");
       return 1;
    }
    
    /* leer el segundo polinomio */
    GetRhsVar(2, "i", &m2, &n2, &l2);

    /* validar que los elementos del polinomio no sean negativos */
    for (i = 0; i < n2; i++){
         
         if ((*(istk(l2 + i))) < 0){
            error("los elementos del polinomio primitivo deben ser enteros positivos");
            return 1;
         }
             
    }
    
    pol2 = istk(l2);
    
    if (pol2[n2 - 1] == 0){
       error("el último término del polinomio no puede ser cero");
       return 1;
    }
    
    /* validar que el segundo argumento no sea una matriz */
    if ((m2 > 1)){
       error("pol2 debe ser un vector de la forma [0 .. p - 1]");
       return 1;
    }
    
    if (n1 != n2){
       error("pol1 y pol2 deben ser del mismo tamaño");
       return 1;
    }
    
    /* leer p */
    GetRhsVar(3, "i", &m3, &n3, &l3);
    
    /* validar que p sea positivo */
    if ((*istk(l3)) < 1){
       error("p debe ser > 1");
       return 1;
    }
    
    p = *istk(l3);
    
    if (!es_primo(p)){
       error("p debe ser un primo > 1");
       return 1;
    }
    
    tam = n1;
    
    /* validar que los elementos de pol1 y pol2 esten entre 0 y p - 1*/
    for (i = 0; i < tam; i++){
    
        if ((pol1[i] >= p)){
           Scierror(999,_("%s: Error, los coeficientes de pol1 deben estar entre 0 y %u.\n"), fname, p - 1);
           return 1;
        }
        
        if ((pol2[i] >= p)){
           Scierror(999,_("%s: Error, los coeficientes de pol2 deben estar entre 0 y %u.\n"), fname, p - 1);
           return 1;
        }
    
    }
    
    m4 = 1;
    n4 = tam;
    
    /* crear una variable en el stack para almacenar el resultado */
    CreateVar(4, "i", &m4, &n4, &l4);
    
    restar_polinomios(pol1, pol2, p, tam, istk(l4));
    
    LhsVar(1) = 4;
    
    return 0;
}

/* funcion interfaz de la rutina dividir_polinomios()
 * Entrada: dividendo y divisor
 * Salida: cociente y residuo */
int sci_dividir_polinomios(char *fname)
{
    static unsigned int l1, m1, n1, l2, m2, n2, l3, m3, n3, l4, m4, n4, l5, m5, n5;
    static int minrhs = 3, maxrhs = 3, minlhs = 2, maxlhs = 2;
    unsigned int p, i, grado_dividendo, grado_divisor, *pdividendo, *pdivisor, *cociente, *residuo;
    unsigned int tam_cociente = 0, tam_residuo = 0;
    
    CheckRhs(minrhs, maxrhs);
    CheckLhs(minlhs, maxlhs);
    
    /* leer el primer polinomio */
    GetRhsVar(1, "i", &m1, &n1, &l1);
    
    /* validar que los elementos del polinomio no sean negativos */
    for (i = 0; i < n1; i++){
         
         if ((*(istk(l1 + i))) < 0){
            error("los elementos del polinomio primitivo deben ser enteros positivos");
            return 1;
         }
               
    }
    
    pdividendo = istk(l1);
    
    /* validar que el primer argumento no sea una matriz */
    if ((m1 > 1)){
       error("pol1 debe ser un vector de la forma [0 .. p - 1]");
       return 1;
    }
    
    /* el coeficiente mas significativo no puede ser cero */
    if (pdividendo[n1 - 1] == 0){
       error("el último término del polinomio dividendo no puede ser cero");
       return 1;
    }
    
    /* leer el segundo polinomio */
    GetRhsVar(2, "i", &m2, &n2, &l2);
    
    /* validar que los elementos del polinomio no sean negativos */
    for (i = 0; i < n2; i++){
         
         if ((*(istk(l2 + i))) < 0){
            error("los elementos del polinomio primitivo deben ser enteros positivos");
            return 1;
         }
             
    }
    
    pdivisor = istk(l2);
    
    /* validar que el segundo argumento no sea una matriz */
    if ((m2 > 1)){
       error("pol2 debe ser un vector de la forma [0 .. p - 1]");
       return 1;
    }
    
    /* el coeficiente mas significativo no puede ser cero */
    if (pdivisor[n2 - 1] == 0){
       error("el último término del polinomio divisor no puede ser cero");
       return 1;
    }
    
    /* leer p */
    GetRhsVar(3, "i", &m3, &n3, &l3);
    
    /* validar que p sea positivo */
    if ((*istk(l3)) < 1){
       error("p debe ser > 1");
       return 1;
    }
    
    p = *istk(l3);
    
    if (!es_primo(p)){
       error("p debe ser un primo > 1");
       return 1;
    }
    
    /* validar que los elementos de pdividendo esten entre 0 y p - 1*/
    for (i = 0; i < n1; i++){
    
        if ((pdividendo[i] >= p)){
           Scierror(999,_("%s: Error, los coeficientes de pdividendo deben estar entre 0 y %u.\n"), fname, p - 1);
           return 1;
        }
    
    }
    
    /* validar que los elementos de pdivisor esten entre 0 y p - 1*/
    for (i = 0; i < n2; i++){
    
        if ((pdivisor[i] >= p)){
           Scierror(999,_("%s: Error, los coeficientes de pdivisor deben estar entre 0 y %u.\n"), fname, p - 1);
           return 1;
        }
    
    }
    
    /* determinar el grado de cada polinomio */
    grado_dividendo = n1 - 1;
    grado_divisor = n2 - 1;
    
    /* validar si es un caso trivial o no */
    if (grado_dividendo < grado_divisor){
    
       /* caso trivial: El grado de dividendo es menor que el grado de divisor */
       
       m4 = 1;
       n4 = 1;
       
       /* cociente */
       CreateVar(4, "i", &m4, &n4, &l4);
       cociente = istk(l4);
       *cociente = 0;
       
       m5 = 1;
       n5 = n1;
       
       /* residuo: dividendo */
       CreateVar(5, "i", &m5, &n5, &l5);
       residuo = istk(l5);
       memcpy(residuo, pdividendo, n5 * sizeof(unsigned int));
       
       LhsVar(1) = 5;
       LhsVar(2) = 4;
       
       return 0;
           
    } else {
       /* ordenar los monomios de forma descendente para aplicar el algoritmo */
	   invertir_polinomio(pdividendo, n1);
       invertir_polinomio(pdivisor, n2);

	   /* crear memoria para guardar cociente y residuo */
	   cociente = (unsigned int *) malloc(n1 * sizeof(unsigned int));
	   
	   if (cociente == NULL){
          error("sci_dividir_polinomios()", "No hay memoria suficiente para cociente = malloc()");
          return 1;
       }
       
       /* tamaño cociente (por defecto el mismo tamaño del dividendo, asi creamos el mayor tamaño posible para evitar problemas con realloc()) */
	   tam_cociente = n1;

	   residuo = (unsigned int *) malloc(n1 * sizeof(unsigned int));
	   
	   if (residuo == NULL){
          error("sci_dividir_polinomios()", "No hay memoria suficiente para residuo = malloc()");
          return 1;
       }
	   
	   tam_residuo = n1;

       dividir_polinomios(pdividendo, n1, pdivisor, n2, cociente, &tam_cociente, residuo, &tam_residuo, p);
       
       m4 = 1;
       n4 = tam_cociente;
    
       /* crear un arreglo en el stack para almacenar el cociente */
       CreateVar(4, "i", &m4, &n4, &l4);
       memcpy(istk(l4), cociente, tam_cociente * sizeof(unsigned int));
       
       m5 = 1;
       n5 = tam_residuo;
       
       /* crear un arreglo en el stack para almacenar el residuo */
       CreateVar(5, "i", &m5, &n5, &l5);
       memcpy(istk(l5), residuo, tam_residuo * sizeof(unsigned int));
       
       free(cociente);
       free(residuo);
       
       LhsVar(1) = 5;
       LhsVar(2) = 4;
            
       return 0;
    }

}
