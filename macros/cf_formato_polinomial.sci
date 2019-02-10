//
// cf_arreglo_a_polinomio.sci
//
// Imprime el polinomio relacionado con arreglo de coeficientes del argumento.
//
// Ultima actualizacion: 02/10/2009
//
// 24/07/2009: Actualizada la funcion para soportar arreglos de coeficientes de polinomios.
//             por ejemplo, para convertir las tuplas de un campo de extension a polinomios
//
// 02/10/2009: Formateo del programa
//
// Copyright © Daniel E Rodriguez – UIS.
//
function polim = cf_formato_polinomial(vector)
  
  if size(vector, 'r') > 1 then
    
    for i = 1:size(vector, 'r')
      polim(i, 1) = poly(vector(i, :), 'x', 'coeff');
    end
  
  else 
    polim = poly(vector, 'x', 'coeff');
  end

endfunction

