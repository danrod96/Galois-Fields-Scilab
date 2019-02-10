//
// cf_potencia_elementos.sci
//
// Macro que implementa la operacion potencia para elementos de campos finitos
//
// Ultima actualizacion: 02/10/2009
//
// 02/10/2009: BUG: Para campos medianamente grandes, como GF(2^5), al hallar la potencia de cualquiera de sus elementos (que es un polinomio de grado 4) elevado a un numero grande
//             el programa falla. Buscar un algoritmo para ir reduciendo el tamaño de la potencia en cada paso.
//
// Copyright © Daniel E Rodriguez – UIS.
//
function res = cf_potencia_elementos(campo, base, exponente)
  p = campo(1);
  n = campo(2);
  pol_primo = campo(3);
  
  if (n == 1) then
    
    //validar base y exponente
   if size(base, 'r') > 1 then
    disp('Error, base debe ser un escalar');
    res = 0;
    return(res);
   end
  
   if size(base, 'c') > 1 then
    disp('Error, base debe ser un escalar');
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
  
   res = cf_pot_elem_prim(campo, base, exponente);
   
  else
    
   //validar base y exponente
   if size(base, 'r') > 1 then
    disp('Error, base debe ser un escalar');
    res = 0;
    return(res);
   end
   
   if size(base, 'c') ~= n then
    printf('Error, el tamaño de la base debe ser igual a %d\n', n);
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
      printf('Error, los elementos de elemento1 deben estar entre 0 y %d\n', p - 1);
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
  
   //reducir exponente si es necesario
   if (exponente >= p^n - 1) then
    tmp = modulo(exponente, p^n - 1);
    exponente = tmp;
   end
  
   if (exponente == 0) then
     res = zeros(1, n);
     res(1, 1) = 1;
   else
     acum_producto = 1;
     
     //debe haber una forma mas optima de hacer la operacion
     for i = 1:exponente
      acum_producto = cf_producto_polinomios(acum_producto, base, p);
     end
    
     [r q] = cf_dividir_polinomios(acum_producto, pol_primo, p);
     
     if size(r, 'c') < n then
      tmp = r;
      r = zeros(1, n);
      
      for i = 1:size(tmp, 'c')
        r(1, i) = tmp(1, i);
      end
     end
     
     res = r;
   end
  end
  
endfunction

