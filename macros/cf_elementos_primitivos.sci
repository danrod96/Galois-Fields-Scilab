//
// cf_elementos_primitivos.sci
//
// Halla elementos primitivos del campo GF(p^n)
//
// Ultima actualizacion: 03/10/2009
//
// 14/07/2009: verificar otra condicion de tmp
//
// 26/07/2009: Se define codigo para hallar los elementos primos de un campo de extension
//
// 24/08/2009: Agregar mas elementos en tabla_primos y tabla_elem_prim_min
//
// 02/10/2009: PENDIENTE: para campos grandes, el algoritmo que genera los elementos primitivos falla (en productos grandes de polinomios el programa se cae)
//             cambiar el algoritmo.
//
// 03/10/2009: Nuevo algoritmo para generar los elementos primitivos de campos de extension.
//
// Copyright © Daniel E Rodriguez – UIS.
//
function x = cf_elementos_primitivos(campo)

   p = campo(1);
   n = campo(2);
  
   //tabla de primos y sus correspondientes elementos primitivos minimos
   tabla_primos = [5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 101, 103, 107];
   
   tabla_elem_prim_min = [2, 3, 2, 2, 3, 2, 5, 2, 3, 2, 6, 3, 5, 2, 2, 2, 2, 7, 5, 3, 2, 3, 5, 2, 5, 2];
   
   max_prim = tabla_primos(size(tabla_primos, 'c'));
   
   if (p > max_prim) then
    printf('Error, p es mayor que el maximo valor permitido, %d\n', max_prim);
    x = 0;
    return(x);
   end
 
   if (n == 1) then
    
    //algoritmo elementos primitivos para campos primos GF(p)
    if (p == 2) then
      x = 1;
      return(x);
    end
    
    if (p == 3) then
      x = 2;
      return(x);
    end
    
    pos_primo = 0;
    min_elem_prim = 0;
    x = 0;
    cont = 1;
    
    //hallar el minimo elemento primitivo asociado a p
    for i = 1:size(tabla_primos, 'c')
      if (tabla_primos(i) == p) then
        pos_primo = i;
        break;
      end
    end
    
    min_elem_prim = tabla_elem_prim_min(pos_primo);
      
    //no es el algoritmo mas optimo, ya que para potencias grandes falla.
    for i = 1:p - 1
      
      if (gcd(int32([p - 1, i])) == 1) then
        //tambien hay problemas con numeros grandes en la funcion modulo
        tmp = modulo(min_elem_prim^i, p);
        
        if ((tmp > 0) & (tmp < p)) then
          x(:, cont) = tmp;
          cont = cont + 1;
        end
      
      end
    
    end
    
    //ordenar x de mayor a menor
    x = gsort(x, 'g', 'i');
    
   else
    
    elementos_campo = campo(4);
    cont = 1;
    
    //generar la lista de exponentes (-1, 0, .., p^n - 2)
    //lista_exponentes estan los exponentes correspondientes a cada elemento de elementos_campo.
    orden = p^n;
    for i = 1:orden
      lista_exponentes(1, i) = i - 2;
    end
    
    //no es necesario hacer el producto, sabiendo que 'x' es un elemento primitivo, aplicamos gcd para determinar si el valor exponencial es elemento primitivo, de acuerdo con eso
    //se halla el polinomio correspondiente
    for i = 1:p^n - 2
      if (gcd(int32([i, p^n - 1])) == 1) then
        lista_elem_prims(cont, :) = elementos_campo(2 + i, :);
        cont = cont + 1;
      end
    end
    
    x = lista_elem_prims;
    
 end
 
endfunction

