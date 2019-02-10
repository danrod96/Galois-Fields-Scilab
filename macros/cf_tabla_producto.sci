//
// cf_tabla_producto.sci
//
// Produce la tabla de producto asociada a campo.
// campo: lista obtenida por cf_crear_campo()
//
// Ultima actualizacion: 26/07/2009
//
// Copyright © Daniel E Rodriguez – UIS.
//
function tabla = cf_tabla_producto(campo);
  
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

  printf('Tabla de producto para GF(%d)\n\n', p);

  for i = 1:p
    for j = 1:p
      tabla(i, j) = cf_producto_elementos(campo, tabla(i, j), (j - 1));
    end
  end
  
endfunction
