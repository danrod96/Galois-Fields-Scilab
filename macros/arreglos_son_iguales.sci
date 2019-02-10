//
// arreglos_son_iguales.sci
// 
// compara dos arreglos y determina si son identicas (tienen los mismos elementos en la misma posicion)
//
// Ultima actualizacion: 01/10/2009
//
// 01/10/2009: Agregado break en el bucle de comprobacion de elementos.
//             Agregado indentacion en el programa.
//
// Copyright © Daniel E Rodriguez – UIS.
//
function resp = arreglos_son_iguales(arreglo1, arreglo2)
  
  tam_1 = size(arreglo1, 'c');
  tam_2 = size(arreglo2, 'c');
  val = %T;
  
  if (tam_1 ~= tam_2) then
    disp('Error, deben tener el mismo tamaño');
    resp = %F;
    return(resp);
  end

  for i = 1:tam_1
    if (arreglo1(1, i) ~= arreglo2(1, i)) then
      val = %F;
      break;
    end
  end
  
  resp = val;
  
endfunction

