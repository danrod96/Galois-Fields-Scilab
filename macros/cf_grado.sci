//
// cf_grado.sci
//
// Muestra el grado de un campo
//
// Ultima actualizacion: 23/08/2009
//
// Copyright © Daniel E Rodriguez – UIS.
//
function grado = cf_grado(campo);
  
  //validar campo
  
  p = campo(1);
  n = campo(2);
  
  printf('Grado del campo GF(%d)\n', p^n);
  
  grado = n;
  
endfunction
