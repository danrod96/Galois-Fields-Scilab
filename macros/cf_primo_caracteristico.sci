//
// cf_primo_caracteristico.sci
//
// Muestra el primo caracteristico de un campo
//
// Ultima actualizacion: 23/08/2009
//
// Copyright © Daniel E Rodriguez – UIS.
//
function prim_car = cf_primo_caracteristico(campo);
  
  //validar campo
  
  p = campo(1);
  n = campo(2);
  
  printf('Primo caracteristico del campo GF(%d)\n', p^n);
  
  prim_car = p;
  
endfunction
