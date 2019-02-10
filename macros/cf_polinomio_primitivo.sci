//
// cf_elementos_campos.sci
//
// Muestra los elementos de un campo
//
// Ultima actualizacion: 22/08/2009
//
// Copyright © Daniel E Rodriguez – UIS.
//
function pol_prim = cf_polinomio_primitivo(campo);
  
  //validar campo
  
  p = campo(1);
  n = campo(2);
  
  printf('Polinomio primitivo del campo GF(%d)\n', p^n);
  
  tmp = campo(3);
  
  pol_prim = poly(tmp, 'x', 'coeff');
  
endfunction
