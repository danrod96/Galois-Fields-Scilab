//
// arreglo_es_uno.sci
//
// Pequeña funcion que si un elemento del campo representa 1
//
// Ultima actualizacion: 01/10/2009
//
// 01/10/2009: Agregado break
//             Agregado la variable tam que almacena el tamaño del arreglo
//             Mejor presentacion del programa.
//
// Copyright © Daniel E Rodriguez – UIS.
//
function resp = arreglo_es_uno(arreglo)
  
  tam = size(arreglo, 'c');
  val = %T;
  
  if (arreglo(1, 1) ~= 1) then
    val = %F;
  else
    //verificar que el resto de elementos sean 0s
    for i = 2:tam
      if (arreglo(1, i) ~= 0) then
        val = %F;
        break;
      end
    end
  end
  
  resp = val;
  
endfunction

