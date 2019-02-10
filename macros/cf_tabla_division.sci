//
// cf_tabla_division.sci
//
// Produce la tabla de adicion asociada a campo.
// campo: lista obtenida por cf_crear_campo()
//
// Ultima actualizacion: 02/10/2009
//
// Copyright © Daniel E Rodriguez – UIS.
//
function tabla = cf_tabla_division(campo);
  
  p = campo(1);
  n = campo(2);
  tabla = 0;
  
  if (n > 1) then
    disp('Error, funcion sólo disponible para campos primos');
    tabla = 0;
    return(tabla);
  end

  for i = 1:(p - 1)
    tabla(i, 1:p - 1) = ones(1, p - 1) * (i);
  end

  printf('Tabla de division para GF(%d)\n\n', p);

  for i = 1:(p - 1)
    for j = 1:(p - 1)
      tabla(i, j) = cf_dividir_elementos(campo, tabla(i, j), j);
    end
  end
  
endfunction
