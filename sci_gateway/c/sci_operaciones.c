/*
 * sci_operaciones.c
 *
 * Definicion de funciones interfaces entre Scilab y las rutinas que gestionan operaciones basicas entre
 * elementos de campos.
 *
 * Ultima actualización: 19/07/2009
 *
 * 01/07/2009: Definicion de sci_sumar_elementos()
 *             Definicion de sci_restar_elementos()
 *
 * 02/07/2009: Definicion de sci_producto_elementos()
 *             Definicion de sci_dividir_elementos()
 *             Definicion de sci_potencia_elementos()
 *
 * 17/07/2009: En la funcion sci_potencia_elementos() exp puede ser mayor que p
 *
 * 19/07/2009: Modificado sci_sumar_elementos() para operar elementos de campos de extension
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
#include "../../src/c/include/operaciones.h"
#include "../../src/c/include/funciones.h"

#define error(msg) Scierror(999,_("%s: Error, %s.\n"), fname, (msg));

int sci_sumar_elementos(char *fname)
{
    static unsigned int l0, m0, n0;
    static unsigned int l1, m1, n1, l2, m2, n2;
    static unsigned int l3, m3, n3, l4, m4, n4;
    static unsigned int l5, m5, n5;
    static int minrhs = 3, maxrhs = 3, minlhs = 1, maxlhs = 1;
    static unsigned int p, n, *elem1, *elem2, i;
    
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
    
    /* leer elem1 */
    GetRhsVar(2, "i", &m3, &n3, &l3);
    
    if (m3 > 1){
       error("elemento1 no debe ser una matriz");
       return 1;
    }  
    
    if (n == 1){
          
       elem1 = istk(l3);
    
       if ((*elem1 < 0) || (*elem1 >= p)){
          Scierror(999,_("%s: Error, elemento1 debe estar entre 0 y %d.\n"), fname, (p - 1));
          return 1;
       }
    
    } else {
       
       if (n3 != n){
          Scierror(999,_("%s: Error, elemento1 debe ser un arreglo de tamaño %d.\n"), fname, n);
          return 1;
       }
       
       elem1 = istk(l3);
       
       for (i = 0; i < n; i++){
           
           if (elem1[i] >= p){
              Scierror(999,_("%s: Error, los elementos de elemento1 deben estar entre 0 y %d.\n"), fname, p - 1);
              return 1;
           }
           
       }
       
    }
    
    /* Leer elem2 */
    GetRhsVar(3, "i", &m4, &n4, &l4);
    
    if (m4 > 1){
       error("elemento2 no debe ser una matriz");
       return 1;
    } 
    
    if (n == 1){
          
       elem2 = istk(l4);
    
       if ((*elem2 < 0) || (*elem2 >= p)){
          Scierror(999,_("%s: Error, elemento2 debe estar entre 0 y %d.\n"), fname, (p - 1));
          return 1;
       }
       
    } else {

       if (n4 != n){
          Scierror(999,_("%s: Error, elemento2 debe ser un arreglo de tamaño %d.\n"), fname, n);
          return 1;
       }
       
       elem2 = istk(l4);
       
       for (i = 0; i < n; i++){
           
           if (elem2[i] >= p){
              Scierror(999,_("%s: Error, los elementos de elemento2 deben estar entre 0 y %d.\n"), fname, p - 1);
              return 1;
           }
           
       }
           
    }
    
    if (n == 1){
       m5 = 1;
       n5 = 1;
    } else {
       m5 = 1;
       n5 = n;
    }
    
    /* crear una variable en el stack para almacenar el resultado */
    CreateVar(4, "i", &m5, &n5, &l5);
    
    sumar_elementos(p, n, elem1, elem2, istk(l5));
    
    LhsVar(1) = 4;
    
    return 0;
}

int sci_restar_elementos(char *fname)
{
    static unsigned int l0, m0, n0;
    static unsigned int l1, m1, n1, l2, m2, n2;
    static unsigned int l3, m3, n3, l4, m4, n4;
    static unsigned int l5, m5, n5;
    static int minrhs = 3, maxrhs = 3, minlhs = 1, maxlhs = 1;
    static unsigned int p, n, *elem1, *elem2, i;
    
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
    
    /* leer los elementos a operar */
    GetRhsVar(2, "i", &m3, &n3, &l3);

    if (m3 > 1){
       error("elemento1 no debe ser una matriz");
       return 1;
    }  
    
    if (n == 1){
          
       elem1 = istk(l3);
    
       if ((*elem1 < 0) || (*elem1 >= p)){
          Scierror(999,_("%s: Error, elemento1 debe estar entre 0 y %d.\n"), fname, (p - 1));
          return 1;
       }
    
    } else {
       
       if (n3 != n){
          Scierror(999,_("%s: Error, elemento1 debe ser un arreglo de tamaño %d.\n"), fname, n);
          return 1;
       }
       
       elem1 = istk(l3);
       
       for (i = 0; i < n; i++){
           
           if (elem1[i] >= p){
              Scierror(999,_("%s: Error, los elementos de elemento1 deben estar entre 0 y %d.\n"), fname, p - 1);
              return 1;
           }
           
       }
       
    }
    
    /* Leer elem2 */
    GetRhsVar(3, "i", &m4, &n4, &l4);
    
    if (m4 > 1){
       error("elemento2 no debe ser una matriz");
       return 1;
    } 
    
    if (n == 1){
          
       elem2 = istk(l4);
    
       if ((*elem2 < 0) || (*elem2 >= p)){
          Scierror(999,_("%s: Error, elemento2 debe estar entre 0 y %d.\n"), fname, (p - 1));
          return 1;
       }
       
    } else {

       if (n4 != n){
          Scierror(999,_("%s: Error, elemento2 debe ser un arreglo de tamaño %d.\n"), fname, n);
          return 1;
       }
       
       elem2 = istk(l4);
       
       for (i = 0; i < n; i++){
           
           if (elem2[i] >= p){
              Scierror(999,_("%s: Error, los elementos de elemento2 deben estar entre 0 y %d.\n"), fname, p - 1);
              return 1;
           }
           
       }
           
    }
    
    if (n == 1){
       m5 = 1;
       n5 = 1;
    } else {
       m5 = 1;
       n5 = n;
    }
    
    /* crear una variable en el stack para almacenar el resultado */
    CreateVar(4, "i", &m5, &n5, &l5);
    
    restar_elementos(p, n, elem1, elem2, istk(l5));
    
    LhsVar(1) = 4;
    
    return 0;
}

int sci_producto_elementos(char *fname)
{
    static unsigned int l0, m0, n0;
    static unsigned int l1, m1, n1, l2, m2, n2;
    static unsigned int l3, m3, n3, l4, m4, n4;
    static unsigned int l5, m5, n5;
    static int minrhs = 3, maxrhs = 3, minlhs = 1, maxlhs = 1;
    static unsigned int p, n, elem1, elem2;
    
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
    
    /* leer los elementos a operar */
    GetRhsVar(2, "i", &m3, &n3, &l3);
    elem1 = *istk(l3);
    
    if ((elem1 < 0) || (elem1 >= p)){
       Scierror(999,_("%s: Error, elem1 debe estar entre 0 y %d.\n"), fname, p);
       return 1;
    }
    
    GetRhsVar(3, "i", &m4, &n4, &l4);
    elem2 = *istk(l4);
    
    if ((elem2 < 0) || (elem2 >= p)){
       Scierror(999,_("%s: Error, elem1 debe estar entre 0 y %d.\n"), fname, p);
       return 1;
    }
    
    m5 = 1;
    n5 = 1;
    
    /* crear una variable en el stack para almacenar el resultado */
    CreateVar(4, "i", &m5, &n5, &l5);
    
    producto_elementos(p, n, elem1, elem2, istk(l5));
    
    LhsVar(1) = 4;
    
    return 0;
}

int sci_dividir_elementos(char *fname)
{
    static unsigned int l0, m0, n0;
    static unsigned int l1, m1, n1, l2, m2, n2;
    static unsigned int l3, m3, n3, l4, m4, n4;
    static unsigned int l5, m5, n5;
    static int minrhs = 3, maxrhs = 3, minlhs = 1, maxlhs = 1;
    static unsigned int p, n, elem1, elem2;
    
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
    
    /* leer los elementos a operar */
    GetRhsVar(2, "i", &m3, &n3, &l3);
    elem1 = *istk(l3);
    
    if ((elem1 < 0) || (elem1 >= orden(p, n))){
       Scierror(999,_("%s: Error, elem1 debe estar entre 0 y %d.\n"), fname, (orden(p, n) - 1));
       return 1;
    }
    
    GetRhsVar(3, "i", &m4, &n4, &l4);
    elem2 = *istk(l4);
    
    /* elem2 no puede ser 0 */
    if ((elem2 <= 0) || (elem2 >= orden(p, n))){
       Scierror(999,_("%s: Error, elem1 debe estar entre 0 y %d.\n"), fname, (orden(p, n) - 1));
       return 1;
    }
    
    m5 = 1;
    n5 = 1;
    
    /* crear una variable en el stack para almacenar el resultado */
    CreateVar(4, "i", &m5, &n5, &l5);
    
    dividir_elementos(p, n, elem1, elem2, istk(l5));
    
    LhsVar(1) = 4;
    
    return 0;
}

int sci_potencia_elementos(char *fname)
{
    static unsigned int l0, m0, n0;
    static unsigned int l1, m1, n1, l2, m2, n2;
    static unsigned int l3, m3, n3, l4, m4, n4;
    static unsigned int l5, m5, n5;
    static int minrhs = 3, maxrhs = 3, minlhs = 1, maxlhs = 1;
    static unsigned int p, n, base, exp;
    
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
    
    /* leer los elementos a operar */
    GetRhsVar(2, "i", &m3, &n3, &l3);
    base = *istk(l3);
    
    if ((base < 0) || (base >= orden(p, n))){
       Scierror(999,_("%s: Error, elem1 debe estar entre 0 y %d.\n"), fname, (orden(p, n) - 1));
       return 1;
    }
    
    GetRhsVar(3, "i", &m4, &n4, &l4);
    exp = *istk(l4);
    
    /* exponente puede ser mayor que orden(p, n) */
    if (exp < 0){
       Scierror(999,_("%s: Error, elem1 debe ser mayor que 0\n"), fname);
       return 1;
    }
    
    if ((base == 0) && (exp == 0)){
       error("base y expo = 0, resultado indeterminado");
       return 1;
    }
    
    m5 = 1;
    n5 = 1;
    
    /* crear una variable en el stack para almacenar el resultado */
    CreateVar(4, "i", &m5, &n5, &l5);
    
    potencia_elementos(p, n, base, exp, istk(l5));
    
    LhsVar(1) = 4;  
    
    return 0;
}
