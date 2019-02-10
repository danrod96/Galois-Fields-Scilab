//
// cf_imprimir_formato_exponencial.sci
//
// Devuelve una cadena o cadenas de la forma "x^exp" que representa el formato exponencial asociado al polinomio representado
// por el arreglo de coeficientes "arreglo".
// Tambien puede devolver los valores enteros que representan los exponentes, dependiendo del valor en el argumento tipo_dato
//
// Ultima actualizacion: 02/10/2009
//
// 26/07/2009: Se agrego el argumento tipo_dato, para especificar el tipo de datos que se desea devolver:
//             'c' devuelve una cadena de la forma "x^p"
//             'e' devuelve el entero exp
//
// 02/10/2009: Arreglos en el formato de programa
//
// Copyright © Daniel E Rodriguez – UIS.
//
function formato_exp = cf_formato_exponencial(campo, arreglo, tipo_dato)
  
  p = campo(1)
  n = campo(2)
  
  if (n < 2) then
    disp('Error, n debe ser mayor a 1');
    formato_exp = 0;
    return(formato_exp);
  end

  //primera validacion de arreglo
  if size(arreglo, 'c') ~= n then
    printf('Error, el tamaño de los arreglos de entrada debe ser igual a %d\n', n);
    formato_exp = 0;
    return(formato_exp);
  end

  //leer elementos del campo
  elementos_campo = campo(4);
  
  //generar la lista de exponentes (-1, 0, .., p^n - 2)
  //lista_exponentes estan los exponentes correspondientes a cada elemento de elementos_campo.
  orden = p^n;
  for i = 1:orden
    lista_exponentes(1, i) = i - 2;
  end

  //establecer variables iniciales
  expo = 0;
  cont = 1;

  if size(arreglo, 'r') > 1 then
    //recorrer cada elemento de arreglo, comparar con elementos_campo, y
    //hacer la correspondencia con el elemento de lista_exponentes
    for i = 1:size(arreglo, 'r')
      //validar arreglo(i, :)
      for j = 1:size(arreglo(i, :), 'c')
        if (arreglo(i, j) < 0 | arreglo(i, j) >= p) then
          printf('Error, los elementos de arreglo deben estar entre 0 y %d\n', p - 1);
          formato_exp = 0;
          return(formato_exp);
        end
      end
    
      //si hay coincidencia entre el vector arreglo y el vector de elementos campo, buscar el exponente correspondiente.
      for j = 1:size(elementos_campo, 'r')
        if arreglos_son_iguales(arreglo(i, :), elementos_campo(j, :)) then
          expo(1, cont) = lista_exponentes(1, j);
          cont = cont + 1;
        end
      end
    
    end
  else
    //validar arreglo
    for i = 1:size(arreglo, 'c')
      if (arreglo(1, i) < 0 | arreglo(1, i) >= p) then
        printf('Error, los elementos de arreglo deben estar entre 0 y %d\n', p - 1);
        formato_exp = 0;
        return(formato_exp);
      end
    end
    
    //la misma operacion de correspondencia
    for i = 1:size(elementos_campo, 'r')
      if arreglos_son_iguales(arreglo, elementos_campo(i, :)) then
        expo = lista_exponentes(1, i);
        break;
      end
    end
    
  end
  
  //formatear el vector expo
  if (tipo_dato == 'c') then
    //crear la cadena
    if size(expo, 'c') > 1 then
      for i = 1:size(expo, 'c')
        formato_exp(i, :) = 'x' + '^' + string(expo(1, i));
      end
    else
      formato_exp = 'x' + '^' + string(expo);
    end
  elseif (tipo_dato == 'e') then
    formato_exp = expo;
  else
    disp('Error, valor de tipo_dato incorrecto');
  end

endfunction

