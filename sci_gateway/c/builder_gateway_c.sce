// ====================================================================
// Allan CORNET
// Simon LIPP
// INRIA 2008
// This file is released into the public domain
// ====================================================================
//
//tbx_build_gateway — Build a gateway (toolbox compilation process)
//
tbx_build_gateway('campos_c', ['cf_crear_campo','sci_crear_campo'; ..
                  'cf_orden', 'sci_orden'; 'cf_polinomio_minimo', 'sci_polinomio_minimo'; ..
                  'cf_devolver_pol_prim_def', 'sci_devolver_polinomio_primitivo_por_defecto'; 'cf_es_pol_primitivo', 'sci_es_polinomio_primitivo'; ..
                  'cf_sumar_elementos', 'sci_sumar_elementos'; ..
                  'cf_restar_elementos','sci_restar_elementos'; 'cf_prod_elem_prim', 'sci_producto_elementos'; ..
                  'cf_div_elem_prim','sci_dividir_elementos'; 'cf_pot_elem_prim', 'sci_potencia_elementos'; ..
                  'cf_restar_polinomios', 'sci_restar_polinomios'; ..
                  'cf_dividir_polinomios', 'sci_dividir_polinomios'; 'cf_es_primo','sci_es_primo'; 'cf_congruencia_mod_p', 'sci_congruencia_mod_p'], ..
                  ['sci_campos.o', 'sci_operaciones.o', 'sci_polinomios.o', 'sci_funciones.o'], get_absolute_file_path('builder_gateway_c.sce'), ['../../src/c/libcg']);

clear tbx_build_gateway;
