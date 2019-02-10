//
// cf_dividir_elementos.sci
//
// Macro que implementa la division de elementos para campos de extension
// si el campo es primo, invoca a cf_div_elem_prim()
//
// Ultima actualizacion: 01/10/2009
//
// 24/07/2009: Cambios en la referencia a los arreglos
//
// 01/10/2009: Formateo codigo.
//             creando variables para almacenar los tamaños
//
// Copyright © Daniel E Rodriguez – UIS.
//
function res = cf_dividir_elementos(campo, elemento1, elemento2)
  
  p = campo(1);
  n = campo(2);
  
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
    
   res = cf_div_elem_prim(campo, elemento1, elemento2);
   
  else
  
   elementos_campo = campo(4);
   tam_elementos = size(elementos_campo, 'r');
  
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
 
   if (arreglo_es_cero(elemento2)) then
    disp('Error, elemento2 no puede ser 0');
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
  
  //algoritmo fuerza bruta para hallar la division
  if (arreglos_son_iguales(elemento1, elemento2)) then
    res = zeros(1, n);
    res(1, 1) = 1;
  elseif (arreglo_es_cero(elemento1)) then
    res = zeros(1, n);
  elseif (arreglo_es_uno(elemento2)) then
    res = elemento1;
  else
    for i = 1:tam_elementos
      producto = cf_producto_elementos(campo, elementos_campo(i, :), elemento2);
      if (arreglos_son_iguales(producto, elemento1)) then
        res = elementos_campo(i, :);
        break;
      end
    end
  end
  
 end
  
endfunction

