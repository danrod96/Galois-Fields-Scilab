//
// arreglo_es_cero.sci
//
// evalua el arreglo y determina si todos los elementos son cero, si es asi devuelve T, de lo contrario devuelve F
//
// Ultima actualizacion: 24/07/2009
//
// Copyright © Daniel E Rodriguez – UIS.
//
function resp = arreglo_es_cero(arreglo)
  
  tam = size(arreglo, 'c');
  valor = %T;
  
  for i = 1:tam
    if (arreglo(1, i) ~= 0) then
      valor = %F;
      break;
    end
  end
  
  resp = valor;
  
endfunction

