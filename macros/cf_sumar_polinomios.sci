//
// cf_sumar_polinomios.sci
//
// Suma dos polinomios sobre un campo GF(p)
//
// Ultima actualizacion: 02/10/2009
//
// 02/10/2009: Formato del programa
//             Agregado saltos de linea en los mensajes de errores. PENDIENTE: Hacer lo mismo en los otros macros.
//             Agregado la variable tam, corregido posible error al validar si el coeficiente mas significativo es 0.
//
// Copyright © Daniel E Rodriguez – UIS.
//
function res = cf_sumar_polinomios(pol1, pol2, p)
  
  //validar p
  if (size(p, '*') > 1) then
    printf('Error, el argumento p debe ser un escalar\n');
    res = 0;
    return(res);
  end
  
  if (p < 2) then
    printf('Error, p debe ser mayor o igual a 2\n');
    res = 0;
    return(res);
  end
  
  if (~cf_es_primo(p)) then
    printf('Error, p no es primo\n');
    res = 0;
  end
  
  //validar pol1 y pol2
  if (size(pol1, 'r') > 1) then
    printf('Error, pol1 debe ser un vector\n');
    res = 0;
    return(x);
  end
 
  if (size(pol2, 'r') > 1) then
    printf('Error, pol2 debe ser un vector\n');
    res = 0;
    return(x);
  end
 
  if (size(pol1, 'c') ~= size(pol2, 'c')) then
    printf('Error, ambos polinomios de entrada deben tener el mismo tamano\n');
    res = 0;
    return(res);
  end
  
  tam = size(pol1, 'c');
  
  if (pol1(tam) == 0) then
    printf('Error, el coeficiente mas significativo de pol1 no puede ser 0\n');
    res = 0;
    return(res);
  end
 
  if (pol2(tam) == 0) then
    printf('Error, el coeficiente mas significativo de pol2 no puede ser 0\n');
    res = 0;
    return(res);
  end
 
  for i = 1:tam
    
    if ((pol1(i) < 0) | (pol1(i) >= p)) then
      printf('Error, los elementos de pol1 deben estar entre 0 y %d\n', p - 1);
      res = 0;
      return(res);
    end
  
    if ((pol2(i) < 0) | (pol2(i) >= p)) then
      printf('Error, los elementos de pol2 deben estar entre 0 y %d\n', p - 1);
      res = 0;
      return(res);
    end
 
  end
  
  //sumar los dos elementos
  res = modulo(pol1 + pol2, p);
  
endfunction

