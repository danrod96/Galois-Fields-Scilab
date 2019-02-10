//
// cf_producto_elementos.sce
//
// Implementa el producto de elementos para campos de extension, si el campo es primo, invoca a cf_prod_elem_prim()
//
// Ultima actualizacion: 02/10/2009
//
// 23/07/2009: Correccion de la salida de cf_dividir_polinomios(), cuando el tamaño de r sea menor que n, agregar los 0's a la derecha faltantes.
//
// 24/07/2009: Cambio de la forma como se acceden a los arreglos
//             se usa la funcion arreglo_es_cero() para determinar si todos los elementos de un vector estar en cero
//
// 25/07/2009: Error cuando se multiplican escalares (por ejemplo 2 * 1) o elementos con grado mucho menor a n, corregido.
//
// 02/10/2009: Formato del programa.
//
// Copyright © Daniel E Rodriguez – UIS.
//
function res = cf_producto_elementos(campo, elemento1, elemento2)
  
  p = campo(1);
  n = campo(2);
  polinomio_primitivo = campo(3);
  
  if (n == 1) then
    
   //validar elemento1 y elemento2
   if size(elemento1, 'r') > 1 then
    disp('Error, elemento1 debe ser un escalar');
    res = 0;
    return(res);
   end
 
   if size(elemento1, 'c') > 1 then
    disp('Error, elemento1 debe ser un escalar');
    res = 0;
    return(res);
   end

   if size(elemento2, 'r') > 1 then
    disp('Error, elemento2 debe ser un escalar');
    res = 0;
    return(res);
   end

   if size(elemento2, 'c') > 1 then
    disp('Error, elemento2 debe ser un escalar');
    res = 0;
    return(res);
   end
    
   res = cf_prod_elem_prim(campo, elemento1, elemento2);
   
  else
  
   //validar elemento1 y elemento2
   if size(elemento1, 'r') > 1 then
    disp('Error, elemento1 debe ser un vector');
    res = 0;
    return(res);
   end
 
   if size(elemento1, 'c') ~= n then
    printf('Error, el tamaño de elemento1 debe ser igual a %d', n);
    res = 0;
    return(res);
   end

   if size(elemento2, 'r') > 1 then
    disp('Error, elemento2 debe ser un vector');
    res = 0;
    return(res);
   end

   if size(elemento2, 'c') ~= n then
    printf('Error, el tamaño de elemento1 debe ser igual a %d', n);
    res = 0;
    return(res);
   end
 
   tam1 = size(elemento1, 'c');
   tam2 = size(elemento2, 'c');
 
   for i = 1:tam1
    if (elemento1(1, i) < 0 | elemento1(1, i) >= p) then
      printf('Error, los elementos de elemento1 deben estar entre 0 y %d\n', p - 1);
      res = 0
      return(res);
    end
   end
 
   for i = 1:tam2
    if (elemento2(1, i) < 0 | elemento2(1, i) >= p) then
      printf('Error, los elementos de elemento2 deben estar entre 0 y %d\n', p - 1);
      res = 0;
      return(res);
    end
   end
  
   //se hace el producto polinomial entre elemento1 y elemento2
   tmp = cf_producto_polinomios(elemento1, elemento2, p);
    
   //si el tamaño de tmp es menor que pol_prim, devolver tmp, de lo contrario hacer la llamada a cf_dividir_polinomios para reducir tmp
   if size(tmp, 'c') < size(polinomio_primitivo, 'c') then
    
     if (arreglo_es_cero(tmp)) then
       r = zeros(1, n);
     else
       r = zeros(1, n);
       
       for i = 1:size(tmp, 'c')
        r(1, i) = tmp(1, i);
       end
     
     end
   
   else
     //en caso de que r tenga menor tamaño que n, agregar 0's a la derecha
     [r q] = cf_dividir_polinomios(tmp, polinomio_primitivo, p);
     
     if size(r, 'c') < n then
       tmp2 = r;
       r = zeros(1, n);
      
       for i = 1:size(tmp2, 'c')
         r(1, i) = tmp2(1, i);
       end
     end
   
   end
  
   res = r;
 
 end
  
endfunction

