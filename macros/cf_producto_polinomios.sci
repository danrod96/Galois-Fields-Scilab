//
// cf_producto_polinomios.sci
//
// Convolucion de polinomios sobre campos finitos
//
// Ultima actualizacion: 02/10/2009
//
// 19/07/2009: Corregido un error en la validacion de tamaños para pol1 y pol2.
//
// 23/07/2009: CAMBIO IMPORTANTE: convol() arroja errores al aplicar la funcion modulo (como no me habia dado cuenta antes :S)
//                                el procedimiento de multiplicacion es ahora: transformar los coeficientes en polinomios, hacer la multiplicacion polinomica
//                                extraer los coeficientes del resultado, y aplicar la funcion modulo.
//
//             Se cambio la forma como se accede a los vectores, se referencia de la forma vector(1, i) en vez de vector(i), para evitar errores innecesarios
//
// 02/10/2009: Formato del programa
//
// Copyright © Daniel E Rodriguez – UIS.
//
function res = cf_producto_polinomios(pol1, pol2, p)
  
  if size(pol1, 'r') > 1 then
    disp('Error, pol1 debe ser un vector');
    res = 0;
    return(res);
  end
  
  if size(pol2, 'r') > 1 then
    disp('Error, pol1 debe ser un vector');
    res = 0;
    return(res);
  end

  if size(p, '*') > 1 then
    disp('Error, p debe ser un escalar');
    res = 0;
    return(res);
  end

  //no hay limite en el tamaño de p diferente al tamño maximo para las variables en scilab.
  if (p < 2) then
    disp('Error, p debe ser un primo mayor o igual a 2');
    res = 0;
    return(res);
  end

  if (~cf_es_primo(p)) then
    disp('Error, p debe ser primo');
    res = 0;
    return(res);
  end
  
  tam1 = size(pol1, 'c');
  tam2 = size(pol2, 'c');
  
  for i = 1:tam1
    if (pol1(1, i) < 0 | pol1(1, i) >= p) then
      printf('Error, los elementos de pol1 deben estar entre 0 y %d\n', p - 1);
      res = 0
      return(res);
    end
  end
 
  for i = 1:tam2
   if (pol2(1, i) < 0 | pol2(1, i) >= p) then
      printf('Error, los elementos de pol2 deben estar entre 0 y %d\n', p - 1);
      res = 0;
      return(res);
   end
  end
  
  //convertir pol1 y pol2 al formato polinomial de scilab, hacer la operacion '*', extraer los coeficientes del polinomio resultante y finalmente aplicar modulo
  tmpa = poly(pol1, 'x', 'coeff');
  tmpb = poly(pol2, 'x', 'coeff');
  tmpres = tmpa * tmpb;
  tmp = coeff(tmpres);
  tmp2 = modulo(tmp, p);
  pos = size(tmp, 'c');
  
  //eliminar los 0's redundantes de la derecha
  for i = size(tmp2, 'c'):-1:1
   if (tmp2(1, i) == 0) then
      pos = pos - 1;
    else
      break;
    end
  end

  if (pos == 0) then
    res = 0;
  else
    for i = 1:pos
      res(1, i) = tmp2(1, i);
    end
  end
  
endfunction
