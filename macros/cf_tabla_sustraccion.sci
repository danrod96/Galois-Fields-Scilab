//
// cf_tabla_sustraccion.sci
//
// Produce la tabla de sustraccion asociada a campo.
// campo: lista obtenida por cf_crear_campo()
//
// Ultima actualizacion: 26/07/2009
//
// Copyright © Daniel E Rodriguez – UIS.
//
function tabla = cf_tabla_sustraccion(campo);
  
  p = campo(1);
  n = campo(2);
  
  if (n > 1) then
    disp('Error, funcion sólo disponible para campos primos');
    tabla = 0;
    return(tabla);
  end
  
  tabla = 0;
  
  for i = 1:p
    tabla(i, 1:p) = ones(1, p) * (i - 1);
  end

  printf('Tabla de sustraccion para GF(%d)\n\n', p);

  for i = 1:p
    for j = 1:p
      tabla(i, j) = cf_restar_elementos(campo, tabla(i, j), (j - 1));
    end
  end
  
endfunction
