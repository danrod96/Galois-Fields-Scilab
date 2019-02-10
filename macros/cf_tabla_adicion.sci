//
// cf_tabla_adicion.sci
//
// Produce la tabla de adicion asociada a campo.
// campo: lista obtenida por cf_crear_campo()
//
// Ultima actualizacion: 26/07/2009
//
// Copyright © Daniel E Rodriguez – UIS.
//
function tabla = cf_tabla_adicion(campo);
  
  p = campo(1);
  n = campo(2);
  tabla = 0;
  
  if (n > 1) then
    disp('Error, funcion sólo disponible para campos primos');
    tabla = 0;
    return(tabla);
  end
  
  for i = 1:p
    tabla(i, 1:p) = ones(1, p) * (i - 1);
  end

  printf('Tabla de adicion para GF(%d)\n\n', p);

  for i = 1:p
    for j = 1:p
      tabla(i, j) = cf_sumar_elementos(campo, tabla(i, j), (j - 1));
    end
  end
  
endfunction

