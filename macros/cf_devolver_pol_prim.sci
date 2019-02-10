//
// cf_devolver_pol_prim.sci
//
// Devuelve una lista de polinomios primitivos para un p y n dados.
//
// Ultima actualizacion: 06/10/2009
//
// 14/07/2009: nuevo argumento, opt, para especificar cuantos polinomios primitivos devolver
//
// 01/10/2009: Modificado el programa para aceptar n >= 1.
//             Quitar el argumento opt.
//             Corregir error al llamar a la funcion cf_elementos_primitivos(), hay que construir un campo
//
// 05/10/2009: No voy a usar macros para generar cadenas de polinomios, voy a definir polinomios primitivos por defecto en campos.c, habilitar la funcion devolver_polinomio_primitivo_por_defecto para
//             devolver los polinomios primitivos por defecto dado n y p, generar el campo con base al polinomio devuelto, generar las listas de polinomios con base a los elementos del campo.
//             y finalmente generar la lista.
//
// 06/10/2009: 
//
// Copyright © Daniel E Rodriguez – UIS.
//

function pol_prim = cf_devolver_pol_prim(p, n)
  
   if size(p, '*') > 1 then
    disp('Error, p debe ser un escalar');
    pol_prim = 0;
    return(pol_prim);
   end
 
   if (p < 2) then
    disp('Error, p debe ser un primo mayor o igual a 2');
    pol_prim = 0;
    return(pol_prim);
   end

   if (~cf_es_primo(p)) then
    disp('Error, p debe ser primo');
    pol_prim = 0;
    return(pol_prim);
   end
 
   if size(n, '*') > 1 then
    disp('Error, n debe ser un escalar');
    pol_prim = 0;
    return(pol_prim);
   end

   if (n < 1) then
    disp('Error, n debe ser mayor o igual a 1');
    pol_prim = 0;
    return(pol_prim);
   end
 
   if (n == 1) then  
    
      //construyendo el campo
      pol_prim_def = cf_devolver_pol_prim_def(p, 1);
      elem = 0;
      for i = 0:p - 1;
        elem(1, i + 1) = i;
      end
    
      campo = list(p, 1, pol_prim_def, elem);
    
      tabla_elem_prim = cf_elementos_primitivos(campo);
    
      if (tabla_elem_prim == 0) then
        pol_prim = 0;
        return(pol_prim);
      else
          for i = 1:size(tabla_elem_prim, 'c')
            pol_prim(i, 1) = p - tabla_elem_prim(i);
            pol_prim(i, 2) = 1;
          end
      end

   else
     //algoritmo para hallar la lista de los polinomios primitivos dado p y n > 1
     //la idea es generar la lista de polinomios y probar cada uno con la funcion es_polinomio_primitivo()
     
     pol_prim_por_defecto = cf_devolver_pol_prim_def(p, n);
     
     if (pol_prim_por_defecto == 1) then
      disp('Error, valores de p y n no válidos para esta funcion');
      pol_prim = 0;
      return(pol_prim);
     end
    
     
     //crear el campo
     campo = cf_crear_campo(p, n, pol_prim_por_defecto);
     
     elementos = campo(4);
     clear campo;
     
     elementos2 = zeros(p^n, n + 1);
     elementos2(:, n + 1) = 1;
     elementos2(:, 1:n) = elementos;
     
     clear elementos
     
     //crear matriz para almacenar la lista de polinomios primitivos
     contador = 1;
     
     for i = 1:size(elementos2, 'r')
      if (cf_es_pol_primitivo(elementos2(i, :), p, n)) then
        lista_pols(contador, :) = elementos2(i, :);
        contador = contador + 1;
      end
     end
   
     pol_prim = lista_pols;
   
   end
 
endfunction

