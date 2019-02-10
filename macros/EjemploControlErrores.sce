//
// EjemploControlErrores.sci
//
// Un ejemplo de una aplicacion de campos finitos, control de codigo de errores. En este caso se va a usar un codigo de Hamming.
//
// Un codigo de control de errores funciona al agregar bits redundantes a los bits de informacion.
//
// En este caso, generamos con otro programa un codigo de errores de 7*4, que mapea 4 bits de informacion a codigos de 7 bits
// posteriormente se genera un campo GF(2^4), se toma un elemento de ese campo (que va a representar los bits de informacion) y
// se hacen operaciones con las matrices de Hamming y se determina si ha habido un error en la transmision
//
// Ultima actualizacion: 02/10/2009
//
// Copyright © Daniel E Rodriguez – UIS.
//

//H: matriz de chequeo de paridad
disp('H: matriz de chequeo de paridad:');
H =[ 1     0     0     1     0     1     1;
     0     1     0     1     1     1     0;
     0     0     1     0     1     1     1];
disp(H);

disp('G: matriz generadora:');
//G: matriz generadora
G=[  1     1     0     1     0     0     0;
     0     1     1     0     1     0     0;
     1     1     1     0     0     1     0;
     1     0     1     0     0     0     1];
disp(G);
        
//creando el campo
disp('creado un campo GF(2^4)');
campo = cf_crear_campo(2, 4, [1 0 0 1 1])
elementos = campo(4);
primo_car = campo(1);
informacion = elementos(6, :);
disp('Informacion a codificar');
disp(informacion);

//codificando la informacion, multiplicando el vector informacion por la matriz generadora G
tmp = informacion * G;

//informacion codificada, esto es lo que se va a transmitir
codigo = modulo(tmp, primo_car);
disp('informacion codificada:');
disp(codigo);

bit_error = input('\nEn que bit desea poner el error? (1-4):');

if ((bit_error < 1) | (bit_error > 4)) then
  disp('Error, el bit del error debe estar entre 1 y 4');
  return;
end

//suponiendo que en algun punto de la transmision, un error ocurre en la informacion codificada
printf('\nPoniendo un error en el bit %d de la informacion codificada (simulando un error de transmision)', bit_error);
informacion_transmitida = codigo;
informacion_transmitida(bit_error) = 0;
disp('\nInformacion transmitida:');
disp(informacion_transmitida);

disp('Usando la matriz de chequeo de paridad donde ocurrio el error, multiplicando H * informacion transmitida');
tmp = H * informacion_transmitida';

disp('Error:');
codigo = modulo(tmp, primo_car);
disp(codigo);

printf('\ncomparando codigo con H, se puede ver que el error ocurrio en el bit %d, como efectivamente ocurrio\n', bit_error);
disp(H);
