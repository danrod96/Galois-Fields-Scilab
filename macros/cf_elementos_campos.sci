//
// cf_elementos_campos.sci
//
// Muestra los elementos de un campo
//
// Ultima actualizacion: 02/10/2009
//
// 02/10/2009: agregado variable tam_tmp
//
// Copyright © Daniel E Rodriguez – UIS.
//
function elem = cf_elementos_campos(campo);
  
  p = campo(1);
  n = campo(2);
  
  printf('Elementos del campo GF(%d)\n', p^n);
  
  tmp = campo(4);
  tam_tmp = size(tmp, 'r');
  
  for i = 1:tam_tmp
    elem(i, 1) = poly(tmp(i, :), 'x', 'coeff');
  end
  
endfunction
