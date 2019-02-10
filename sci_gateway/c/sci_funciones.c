/*
 * sci_funciones.c
 *
 * Definicion funciones interfaces a usar por las funciones de scilab
 *
 * Ultima actualizacion: 06/07/2009
 *
 * 06/07/2009: Definicion de sci_es_primo()
 *             Definicion de sci_a_congruente_m_mod_p()
 *
 * 07/07/2009: Borrar sci_a_congruente_m_mod_p()
 *
 * Copyright © Daniel E Rodriguez – UIS.
 */

#include "stack-c.h"
#include "Scierror.h"
#include "localization.h"
#include "../../src/c/include/funciones.h"

int sci_es_primo(char *fname)
{
    static unsigned int l1, m1, n1, l2, m2, n2;
    static int minrhs = 1, maxrhs = 1, minlhs = 1, maxlhs = 1;
    unsigned int p, res;
    
    CheckRhs(minrhs, maxrhs);
    CheckLhs(minlhs, maxlhs);
    
    /* no es necesario validar, las funciones llamantes realizan la labor */
    GetRhsVar(1, "i", &m1, &n1, &l1);
    p = *istk(l1);
    
    res = es_primo(p);
    
    m2 = 1;
    n2 = 1;
    
    CreateVar(2, "i", &m2, &n2, &l2);
    *istk(l2) = res;
    
    LhsVar(1) = 2;
       
    return 0;
}

int sci_congruencia_mod_p(char *fname)
{
    static unsigned int l1, m1, n1, l2, m2, n2, l3, m3, n3;
    static int minrhs = 2, maxrhs = 2, minlhs = 1, maxlhs = 1;
    unsigned int p, res;
    int n;
    
    CheckRhs(minrhs, maxrhs);
    CheckLhs(minlhs, maxlhs);
    
    GetRhsVar(1, "i", &m1, &n1, &l1);
    n = *istk(l1);
    
    GetRhsVar(2, "i", &m2, &n2, &l2);
    p = *istk(l2);
    
    res = congruencia_mod_p(n, p);
    
    m3 = 1;
    n3 = 1;
    
    CreateVar(3, "i", &m3, &n3, &l3);
    *istk(l3) = res;
    
    LhsVar(1) = 3;
    
    return 0;
}
