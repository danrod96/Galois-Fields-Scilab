//
// cf_potencia_polinomios.sci
//
// Macro que implementa la operacion potencia para polinomios sobre Fp
//
// Ultima actualizacion: 26/07/2009
//
// Copyright © Daniel E Rodriguez – UIS.
//
function res = cf_potencia_polinomios(base, exponente, p)
      
   //validar base y exponente
   if size(base, 'r') > 1 then
    disp('Error, base debe ser un vector');
    res = 0;
    return(res);
   end
  
   if size(exponente, 'r') > 1 then
    disp('Error, exponente debe ser un escalar');
    res = 0;
    return(res);
   end
  
   if size(exponente, 'c') > 1 then
    disp('Error, exponente debe ser un escalar');
    res = 0;
    return(res);
   end
  
   for i = 1:size(base, 'c')
    if (base(1, i) < 0 | base(1, i) >= p) then
      printf('Error, los elementos de base deben estar entre 0 y %d\n', p - 1);
      res = 0
      return(res);
    end
   end
  
   if (exponente < 0) then
    disp('Error, el exponente debe ser mayor que 0');
    res = 0
    return(res);
   end
  
   if ((exponente == 0) & (arreglo_es_cero(base))) then
    disp('Error, base y exponente igual a 0, resultado indeterminado');
    res = 0;
    return(res);
   end
  
   if (exponente == 0) then
     res = 1;
   else
     acum_producto = 1;
     for i = 1:exponente
      acum_producto = cf_producto_polinomios(acum_producto, base, p);
     end
     
     res = acum_producto;
   end
  
endfunction

