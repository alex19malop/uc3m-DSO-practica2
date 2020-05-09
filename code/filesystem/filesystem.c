
/*
 *
 * Operating System Design / Diseño de Sistemas Operativos
 * (c) ARCOS.INF.UC3M.ES
 *
 * @file 	filesystem.c
 * @brief 	Implementation of the core file system funcionalities and auxiliary functions.
 * @date	Last revision 01/04/2020
 *
 */


#include "filesystem/filesystem.h" // Headers for the core functionality
#include "filesystem/auxiliary.h"  // Headers for auxiliary functions
#include "filesystem/metadata.h"   // Type and structure declaration of the file system
#include "filesystem/blocks_cache.h"
#include <string.h>
#include <math.h>
#include <stdlib.h>
//#include <stdio.h> 

/*Variables globales*/
superbloque sbloque;
mapas mp;
inodo inodos[48];
int mkFS_done = -1;
int mountFS_done = -1;

/*
 * @brief 	Generates the proper file system structure in a storage device, as designed by the student.
 * @return 	0 if success, -1 otherwise.
 */
int mkFS(long deviceSize)
{
	// inicializar a los valores por defecto del superbloque, mapas e i-nodos
	sbloque.numMagico = 12345;
	sbloque.numBloquesMapaBits = 1;
	sbloque.numInodos = 48;
	sbloque.primerInodo = 2;
	sbloque.numBloquesDatos = deviceSize/(BLOCK_SIZE-2-3);				//= device_size / Block_size - 2 - (Lo que ocupe los bloques de inodos = 3)
	sbloque.primerBloqueDatos = 5;
	sbloque.tamDispositivo = deviceSize;

	for (int i = 0; i < 2020; i++)
	{
		sbloque.padding[i] = 0;
	}


	for (int i = 0; i < 48; i++)
	{
		inodos[i].tipo = 1;
		inodos[i].pos = 0;
		inodos[i].open = 0;
		inodos[i].integridad = 0;
		for (int j = 0; j < 5; j++){
			inodos[i].inodosContenidos[j] = -1;
		}
		inodos[i].tamanyo = 0;
		inodos[i].cantidadBloquesOcupados = 0;
		for (int j = 0; j < 47; j++)
		{
			inodos[i].relleno[j] = 0;
		}
	}

	for (int i = 0; i < 2004; i++)
	{
		if(i < 48){
			bitmap_setbit(mp.i_map,i,0);
		}

		if(i < 38){
			bitmap_setbit(mp.d_map,i,0);
		}

		mp.padding[i] = 0;
	}

	for (int i = 0; i < 48; i++)
	{
		// Escribe en esa dir de memoria el valor de en medio en todo ese tamanio
		memset(&(inodos[i].nombre), 0, 32+1);
	}


	//escribir el superbloque
	bwrite(DEVICE_IMAGE,0,(char*)(&sbloque));
	//escribir el bitmap
	bwrite(DEVICE_IMAGE,1,(char*)(&mp));
	//escribir inodos. Ya que los inodos ocupan 3 bloques (48 * 128 / 2048) hay que hacer 3 bwrites
	bwrite(DEVICE_IMAGE,2,(char*)(&inodos));
	bwrite(DEVICE_IMAGE,3,(char*)(&inodos+BLOCK_SIZE));
	bwrite(DEVICE_IMAGE,4,(char*)(&inodos+BLOCK_SIZE*2));
	fprintf(stdout, "tamanio de inodo %li\n",sizeof(inodo));
	fprintf(stdout, "tamanio de superbloque %li\n",sizeof(superbloque));
	fprintf(stdout, "tamanio de mapas %li\n",sizeof(mapas));
	mkFS_done = 0;
 	return 0;
}

/*
 * @brief 	Mounts a file system in the simulated device.
 * @return 	0 if success, -1 otherwise.
 */
int mountFS(void)
{
	if(mkFS_done != 0){
		return -1;
	}
	//escribir el superbloque
	bread(DEVICE_IMAGE,0,(char*)(&sbloque));
	//escribir el bitmap
	bread(DEVICE_IMAGE,1,(char*)(&mp));
	//escribir inodos. Ya que los inodos ocupan 3 bloques (48 * 128 / 2048) hay que hacer 3 bwrites
	bread(DEVICE_IMAGE,2,(char*)(&inodos));
	bread(DEVICE_IMAGE,3,(char*)(&inodos+BLOCK_SIZE));
	bread(DEVICE_IMAGE,4,(char*)(&inodos+BLOCK_SIZE*2));
	mountFS_done = 0;
	return 0;
}

/*
 * @brief 	Unmounts the file system from the simulated device.
 * @return 	0 if success, -1 otherwise.
 */
int unmountFS(void)
{
	if(mkFS_done != 0 || mountFS_done!= 0 ){
		return -1;
	}
	//escribir el superbloque
	bwrite(DEVICE_IMAGE,0,(char*)(&sbloque));
	//escribir el bitmap
	bwrite(DEVICE_IMAGE,1,(char*)(&mp));
	//escribir inodos. Ya que los inodos ocupan 3 bloques (48 * 128 / 2048) hay que hacer 3 bwrites
	bwrite(DEVICE_IMAGE,2,(char*)(&inodos));
	bwrite(DEVICE_IMAGE,3,(char*)(&inodos+BLOCK_SIZE));
	bwrite(DEVICE_IMAGE,4,(char*)(&inodos+BLOCK_SIZE*2));

 	return 0;
}

int ifree ( int inodo_id ) {    // comprobar validez de inodo_id
	if (inodo_id > sbloque.numInodos) {
		return -1;    // liberar i-nodo
	}
	bitmap_setbit(mp.i_map,inodo_id,0);
	return -1;
}

int ialloc ( void )
{
 	// buscar un i-nodo libre
 	for (int i=0; i<48; i++)
 	{
 		if (bitmap_getbit(mp.i_map,i) == 0) {
			bitmap_setbit(mp.i_map,i,1);	// inodo ocupado ahora
 			// valores por defecto para i-nodo
 			inodos[i].tipo = 1;
			inodos[i].pos = 0;
			inodos[i].open = 0;
			inodos[i].integridad = 0;
			strcpy(inodos[i].nombre,"");
			for (int j = 0; j < 5; j++){
				inodos[i].inodosContenidos[j] = -1;
			}
			inodos[i].tamanyo = 0;
			inodos[i].cantidadBloquesOcupados = 0;
			for (int j = 0; j < 47; j++)
			{
				inodos[i].relleno[j] = 0;
			}
 			return i; // devolver id. de i-nodo
 		}
 	}
 return -1;
}



int alloc ( void )
{
 	for (int i=0; i < (int)(ceil((double)sbloque.tamDispositivo/BLOCK_SIZE) - 5); i++)
 	{
		if (bitmap_getbit(mp.d_map,i) == 0) {
			bitmap_setbit(mp.d_map,i,1);	// bloque ocupado ahora
            /* No se ponen valores por defecto del bloque */
			char bloque[BLOCK_SIZE];
			memset(bloque, 0, BLOCK_SIZE);
			bwrite(DEVICE_IMAGE, i + sbloque.primerBloqueDatos, bloque);
 			return i ; // devolver id. de bloque
 		}
 	}
 return -1;
}

int fileExist(char *fileName) {
	for (int i = 0; i < 48; i++) {

		if(strcmp(inodos[i].nombre, fileName)==0) {
			return -1;
		}
	}
	return 0;

}

int isInodeFull() {
    for (int i = 0; i < 48; i++){
        if (bitmap_getbit(mp.i_map,i) == 0) {
            return 0;
        }
    }
    return -2;
}

int isBlocksFull() {
    for (int i = 0; i < 38; i++){
        if (bitmap_getbit(mp.d_map,i) == 0) {
            return 0;
        }
    }
    return -2;
}

/*
 * @brief	Creates a new file, provided it it doesn't exist in the file system.
 * @return	0 if success, -1 if the file already exists, -2 in case of error.
 */
int createFile(char *fileName)
{
	if(fileExist(fileName)==-1){
		return -1;
	}
	if (isInodeFull() == -2 || isBlocksFull() == -2) {
        return -2;
    }
	int b_id, inodo_id ;
 	inodo_id = ialloc() ;

 	if (inodo_id < 0) {
		return -2 ;
	}

 	b_id = alloc();

 	if (b_id < 0) {
		ifree(inodo_id);
		return -2 ;
	}
 	inodos[inodo_id].tipo = 1 ; // FICHERO
 	strcpy(inodos[inodo_id].nombre, fileName);
 	inodos[inodo_id].inodosContenidos[0] = b_id ;
	inodos[inodo_id].cantidadBloquesOcupados = 1;
	inodos[inodo_id].open = 0;
	inodos[inodo_id].pos = 0;
	inodos[inodo_id].tamanyo = 0;

 	return 0;
}



int busca_inodo(char *fileName) {
	for (int i = 0; i < 48; i++) {
		if(strcmp(inodos[i].nombre, fileName)==0) {
			return i;
		}
	}
	return -1;

}

/*
 * @brief	Deletes a file, provided it exists in the file system.
 * @return	0 if success, -1 if the file does not exist, -2 in case of error..
 */
int removeFile(char *fileName)
{
	int i = busca_inodo(fileName);
	if(i == -1){
		return -1;
	}

	if (inodos[i].tipo == 0){
		return -2;
	}
	for (int j = 0; j < 48; j++) {
		if(inodos[j].inodosContenidos[0] == i) {
			removeLn(inodos[j].nombre);
		}
	}
	//Bitmap de inodos, el encontrado a 0.
	bitmap_setbit(mp.i_map,i,0);
	//Inodo encontrado vuelva a la normalidad
	inodos[i].tipo = 1;
	for (int j = 0; j < 5; j++){
		bitmap_setbit(mp.d_map,inodos[i].inodosContenidos[j],0);
		inodos[i].inodosContenidos[j] = -1;
	}
	// Escribe en esa dir de memoria el valor de en medio en todo ese tamanio
	memset(&(inodos[i].nombre), 0, 32+1);

	return 0;
}

/*
 * @brief	Opens an existing file.
 * @return	The file descriptor if possible, -1 if file does not exist, -2 in case of error..
 */
int openFile(char *fileName)
{
    if(fileExist(fileName) == 0){
        return -1;
    }
    int inodo_id;
    // buscar el inodo asociado al nombre
    inodo_id = busca_inodo(fileName);
    if (inodo_id < 0){
        return -2;
    }
    // Controlo que no esté ya abierto
    if (inodos[inodo_id].open == 1){
        return -2;
    }
	//Si es enlace simbolico abre tambien el archivo al que referencia
	if (inodos[inodo_id].tipo == 0){
		int indice = inodos[inodo_id].inodosContenidos[0];
		inodos[indice].open = 1;
		inodos[indice].pos = 0;
	}
    // iniciar sesión de trabajo
    inodos[inodo_id].pos = 0;
    inodos[inodo_id].open = 1;
    return inodo_id;
}




/*
 * @brief	Closes a file.
 * @return	0 if success, -1 otherwise.
 */
int closeFile(int fileDescriptor)
{
    // comprobar descriptor válido
    if ((fileDescriptor < 0) || (fileDescriptor > sbloque.numInodos - 1)){
        return -1;
    }
    // comprobar que ya está cerrado
    if (inodos[fileDescriptor].open == 0){
        return -1;
    }
	// Si es enlace simbolico, se cierra tambien el archivo original, pero solo si se ha abierto
	// por el enlace simbolico
	if (inodos[fileDescriptor].tipo == 0){
		int indice = inodos[fileDescriptor].inodosContenidos[0];
		inodos[indice].open = 0;
		inodos[indice].pos = 0;
	}
    // cerrar sesión de trabajo
    inodos[fileDescriptor].pos = 0;
    inodos[fileDescriptor].open = 0;
    return 0;
}


/*
 * @brief	Reads a number of bytes from a file and stores them in a buffer.
 * @return	Number of bytes properly read, -1 in case of error.
 */
int readFile(int fileDescriptor, void *buff, int numBytes)
{
	memset(buff, '\0', numBytes);
	/* Si está cerrado no se puede hacer un read */
    if(inodos[fileDescriptor].open == 0) {
        return -1;
    }
	//Si el inodo donde se quiere escribir no tiene fichero
	if (bitmap_getbit(mp.i_map,fileDescriptor) == 0) {
		return -1;
	}
	/* Ajustar numBytes al tamaño máximo del fichero */
	if ((inodos[fileDescriptor].pos + numBytes) > MAX_FILE_SIZE) {
		numBytes = MAX_FILE_SIZE - inodos[fileDescriptor].pos;
	}

	if (numBytes <= 0) {
		return -1;
	}

	// Calcular numero de bloques que se van leer
	int bloques_leer = (numBytes + BLOCK_SIZE - 1) / BLOCK_SIZE;

	char block[BLOCK_SIZE];
	int restante = numBytes;

	int posicion = inodos[fileDescriptor].pos;
	int aux_bloque = floor(posicion/BLOCK_SIZE);

	for (int i = aux_bloque; i < aux_bloque + bloques_leer; i++)
	{
		//memset(block, '\0', BLOCK_SIZE);
		int bloque_id = inodos[fileDescriptor].inodosContenidos[i] + sbloque.primerBloqueDatos;
		printf("Bloque %i en la posición %i\n", bloque_id, i);

		if (bread(DEVICE_IMAGE, bloque_id, block) < 0) {
        	return -1;
      	}

		if (i == aux_bloque) {
			//printf("Primero\n");
			int l = BLOCK_SIZE - (posicion % BLOCK_SIZE); // Longitud a escribir con memmove
			if(posicion % BLOCK_SIZE == 0) {
				l = BLOCK_SIZE;
			} 
			
			if (l > numBytes) {
				l = numBytes;
			}

			restante -= l;

			printf("[%i] OFFSET BLOQUE: %i, LONGITUD: %i OK\n", i, (posicion % BLOCK_SIZE), l);
			memcpy(buff, (posicion % BLOCK_SIZE) + block, l);
		} else if (restante > BLOCK_SIZE) {
			printf("[%i] OFFSET BUFF: %i, LONGITUD: %i OK\n", i, (numBytes - restante), BLOCK_SIZE);
			memcpy((numBytes - restante) + &(buff), block, BLOCK_SIZE);
			restante -= BLOCK_SIZE;
		} else {
			printf("[%i] OFFSET BUFF: %i, LONGITUD: %i OK\n", i, (numBytes - restante), restante);
			memcpy((numBytes - restante) + buff, block, restante);
			restante = 0;
		}
					printf("%s\n", block);
			printf("%s\n", (char *)buff);
	}

	// for (int i = aux_bloque; i < aux_bloque + bloques_leer; i++)
	// {
	// 	memset(block, 0, BLOCK_SIZE);
	// 	int bloque_id;
	// 	printf("La i es: %d\n",i);
	// 	printf("inodos[fileDescriptor].inodosContenidos[i] = %d\n",inodos[fileDescriptor].inodosContenidos[i]);
	// 	printf("sbloque.primerBloqueDatos = %d\n",sbloque.primerBloqueDatos);
	// 	printf("El bloque_id del for es %d\n",bloque_id);
	// 	printf("inodos[fileDescriptor].cantidadBloquesOcupados %d\n",inodos[fileDescriptor].cantidadBloquesOcupados);

  	// 	if (i >= inodos[fileDescriptor].cantidadBloquesOcupados) {
	// 		bloque_id = alloc() + sbloque.primerBloqueDatos;
	// 		if(bloque_id < -1) {
	// 			return -1;
	// 		}
			
	// 		printf("El bloque_id del for_aux es %d\n",bloque_id);
	// 		//inodos[fileDescriptor].inodosContenidos[i] = bloque_id-sbloque.primerBloqueDatos;
	// 		//inodos[fileDescriptor].cantidadBloquesOcupados++;
  	// 	}
	// 	else
	// 	{
	// 	 	bloque_id = inodos[fileDescriptor].inodosContenidos[i] + sbloque.primerBloqueDatos;
	// 	}

		  

	// 	//printf("Bloque %i en la posición %i\n", bloque_id, i);

	// 	if (i == aux_bloque) {
	// 		//printf("Primero\n");
	// 		int l = BLOCK_SIZE - (posicion % BLOCK_SIZE); // Longitud a leer con memmove
	// 		if(posicion % BLOCK_SIZE == 0) {
	// 			l = BLOCK_SIZE;
	// 		} else if (l > numBytes) {
	// 			l = numBytes;
	// 		}

	// 		restante -= l;

    //   		if (bread(DEVICE_IMAGE, bloque_id, block) < 0) {
    //     		bitmap_setbit(mp.d_map,bloque_id,0);
	// 			inodos[fileDescriptor].inodosContenidos[i] = -1;
    //     		return -1;
    //   		}
			
	// 		/*printf("Bloque leido %s\n",block);
	// 		printf("La posicion es %d\n",posicion);
	// 		printf("El buff es %s\n",(char*)buff);
	// 		printf("lo que se le suma a block en memove es: %d\n",((posicion % BLOCK_SIZE)));*/

	// 		/*char hola[100] = "hola";
	// 		char como[100] = "como estas";
	// 		memcpy(hola + 4, como, strlen(como)); //sin el +4 "como estas",con +3holcomoestas
	// 		printf("result de prueba %s\n",hola);*/


	// 		if(strlen((block)) > l){
	// 			/*printf("Entra al if\n");
	// 			printf("l es: %d\n",l);*/

	// 			char *aux0 = malloc(sizeof(char)*l);
	//  			strncpy(aux0,(char*)block,l);

	// 			/*printf("aux0 %s\n",aux0);
	// 			printf("La longitud de block es: %ld\n",strlen(block));*/
	// 			int tam = (posicion % BLOCK_SIZE);
	// 			//printf("Tam es: %d\n",tam);

	// 			memcpy(buff, block + tam, fmin(numBytes,l));

	// 			/*printf("El memove es %s\n",(block +(posicion % BLOCK_SIZE)));
	// 			printf("El block es %s\n", block);*/
	// 			/*char *aux = malloc(sizeof(char)*sizeof(block));
	//  			strcpy(aux,block);*/
	// 		}
	// 		else
	// 		{
	// 			/*printf("Entra al else\n");
	// 			printf("l es: %d\n",l);
	// 			printf("La longitud de block es: %ld\n",strlen(block));*/
	// 			int tam = (posicion % BLOCK_SIZE);
	// 			//printf("Tam es: %d\n",tam);
	// 			memcpy(buff, block + tam, fmin(numBytes,l));


	// 			/*printf("El memove es %s\n",(block +(posicion % BLOCK_SIZE)));
	// 			printf("El block es %s\n", block);*/

	// 		}
	// 		/*char *aux = malloc(sizeof(char)*sizeof(block));
	//  		strcpy(aux,block);
			

	// 		printf("El bloque_id del if es %d\n",bloque_id);
    //   		if (bread(DEVICE_IMAGE, bloque_id, aux) < 0) {
    //     		bitmap_setbit(mp.d_map,bloque_id,0);
	// 			inodos[fileDescriptor].inodosContenidos[i] = -1;
	// 			printf("bwrite fallo\n");
    //     		return -1;
    //   		}*/

			

	// 	} else if (restante > BLOCK_SIZE) {
	// 		//printf("Medio\n");
	// 		if (bread(DEVICE_IMAGE, bloque_id, block) < 0) {
    //     		bitmap_setbit(mp.d_map,bloque_id,0);
	// 			inodos[fileDescriptor].inodosContenidos[i] = -1;
    //     		return -1;
    //   		}
	// 		printf("El bloque_id del else if es %d\n",bloque_id);
	// 		printf("buff es  %s\n",(char*)buff);
	// 		printf("Expresion es  %s\n",(char*)((numBytes - restante) + buff));
	// 		printf("block es  %s\n",(char*)block);
			
	// 		memcpy(buff + (numBytes - restante), block, BLOCK_SIZE);

	// 		printf("El numBytes del else if es %d\n",numBytes);			
	// 		printf("El restante del else if es %d\n",restante);
	// 		/*   (5121 - 3073) +     */

	// 		/*char *aux = malloc(sizeof(char)*sizeof(block));
	//  		strcpy(aux,block);

    //   		if (bwrite(DEVICE_IMAGE, bloque_id, aux) < 0) {
    //     		bitmap_setbit(mp.d_map,bloque_id,0);
	// 			inodos[fileDescriptor].inodosContenidos[i] = -1;
    //     		return -1;
    //   		}*/

	// 		restante -= BLOCK_SIZE;
	// 	} else {
	// 		if (bread(DEVICE_IMAGE, bloque_id, block) < 0) {
    //     		bitmap_setbit(mp.d_map,bloque_id,0);
	// 			inodos[fileDescriptor].inodosContenidos[i] = -1;
    //     		return -1;
    //   		}
	// 		printf("El bloque_id del else if es %d\n",bloque_id);
	// 		printf("buff es  %s\n",(char*)buff);
	// 		printf("Expresion es  %s\n",(char*)((numBytes - restante) + buff));
	// 		printf("block es  %s\n",(char*)block);

	// 		memcpy(buff + (numBytes - restante), block, restante);
			
			
	// 		printf("El numBytes del else if es %d\n",numBytes);			
	// 		printf("El restante del else if es %d\n",restante);;


	// 		restante = 0;
	// 	}
	// }
	inodos[fileDescriptor].pos += numBytes;
	//inodos[fileDescriptor].tamanyo = inodos[fileDescriptor].pos;
	printf("\n");
	return numBytes;
}

/*
 * @brief	Writes a number of bytes from a buffer and into a file.
 * @return	Number of bytes properly written, -1 in case of error.
 */
//Escribe a partir del punterp de posición interno
int writeFile(int fileDescriptor, void *buff, int numBytes)
{
    /* Si está cerrado no se puede hacer un write */
    if(inodos[fileDescriptor].open == 0) {
        return -1;
    }

	//Si el inodo donde se quiere escribir no tiene fichero
	if (bitmap_getbit(mp.i_map,fileDescriptor) == 0) {
		return -1;
	}
	/* Ajustar numBytes al tamaño máximo del fichero */
	if ((inodos[fileDescriptor].pos + numBytes) > MAX_FILE_SIZE) {
		numBytes = MAX_FILE_SIZE - inodos[fileDescriptor].pos;
	}

	if (numBytes <= 0) {
		return -1;
	}

	//fprintf(stdout, "[WF] numBytes: %i\n", numBytes);
	// Calcular numero de bloques que se van escribir
	int bloques_escribir = (numBytes + BLOCK_SIZE - 1) / BLOCK_SIZE;

	// Eliminar bloques que ya no van a ser usados, cuando escribes sobreescribes lo que esta despues de la posicion
	int posicion = inodos[fileDescriptor].pos;
	int aux_bloque = floor(posicion/BLOCK_SIZE);
	for (int i = aux_bloque + 1; inodos[fileDescriptor].tamanyo > 0 && i < inodos[fileDescriptor].cantidadBloquesOcupados; i++)
	{
		bitmap_setbit(mp.d_map,inodos[fileDescriptor].inodosContenidos[i], 0);
		char bloque[BLOCK_SIZE];
		memset(bloque, 0, BLOCK_SIZE);
		bwrite(DEVICE_IMAGE, i + sbloque.primerBloqueDatos, bloque);
	}


	// Comenzando desde el bloque de la posición actual hasta el último bloque se va a escribir
		// Obtener el bloque asociado a la posición actual del fichero
		// Si no tiene bloque asociado, asignar uno nuevo
	char block[BLOCK_SIZE];
	int restante = numBytes;
	for (int i = aux_bloque; i < aux_bloque + bloques_escribir; i++)
	{
		memset(block, 0, BLOCK_SIZE);
		int bloque_id;
		/*printf("La i es: %d\n",i);
		printf("inodos[fileDescriptor].inodosContenidos[i] = %d\n",inodos[fileDescriptor].inodosContenidos[i]);
		printf("sbloque.primerBloqueDatos = %d\n",sbloque.primerBloqueDatos);
		printf("El bloque_id del for es %d\n",bloque_id);
		printf("inodos[fileDescriptor].cantidadBloquesOcupados %d\n",inodos[fileDescriptor].cantidadBloquesOcupados);*/
  		if (i >= inodos[fileDescriptor].cantidadBloquesOcupados) {
			bloque_id = alloc() + sbloque.primerBloqueDatos;
			if(bloque_id < -1) {
				return -1;
			}
			
			printf("El bloque_id del for_aux es %d\n",bloque_id);
			inodos[fileDescriptor].inodosContenidos[i] = bloque_id-sbloque.primerBloqueDatos;
			inodos[fileDescriptor].cantidadBloquesOcupados++;
  		}
		else
		{
		 	bloque_id = inodos[fileDescriptor].inodosContenidos[i] + sbloque.primerBloqueDatos;
		}
		  

		//printf("Bloque %i en la posición %i\n", bloque_id, i);

		if (i == aux_bloque) {
			//printf("Primero\n");
			int l = BLOCK_SIZE - (posicion % BLOCK_SIZE); // Longitud a escribir con memmove
			if(posicion % BLOCK_SIZE == 0) {
				l = BLOCK_SIZE;
			} 
			
			if (l > numBytes) {
				l = numBytes;
			}

			restante -= l;

      		if (bread(DEVICE_IMAGE, bloque_id, block) < 0) {
        		bitmap_setbit(mp.d_map,bloque_id,0);
				inodos[fileDescriptor].inodosContenidos[i] = -1;
        		return -1;
      		}
			
			/*printf("Bloque leido %s\n",block);
			printf("La posicion es %d\n",posicion);
			printf("El buff es %s\n",(char*)buff);
			printf("lo que se le suma a block en memove es: %d\n",((posicion % BLOCK_SIZE)));*/

			/*char hola[100] = "hola";
			char como[100] = "como estas";
			memcpy(hola + 4, como, strlen(como)); //sin el +4 "como estas",con +3holcomoestas
			printf("result de prueba %s\n",hola);*/


			if(strlen((char*)buff) > l){
				/*printf("Entra al if\n");
				printf("l es: %d\n",l);*/
				char *aux0 = malloc(sizeof(char)*l);
	 			strncpy(aux0,(char*)buff,l);
				/*printf("aux0 %s\n",aux0);
				printf("La longitud de block es: %ld\n",strlen(block));*/
				int tam = (posicion % BLOCK_SIZE);
				//printf("Tam es: %d\n",tam);
				memcpy(block + tam, buff, fmin(strlen(aux0),l));

				/*printf("El memove es %s\n",(block +(posicion % BLOCK_SIZE)));
				printf("El block es %s\n", block);*/
				/*char *aux = malloc(sizeof(char)*sizeof(block));
	 			strcpy(aux,block);*/
			}
			else
			{
				/*printf("Entra al else\n");
				printf("l es: %d\n",l);
				printf("La longitud de block es: %ld\n",strlen(block));*/
				int tam = (posicion % BLOCK_SIZE);
				//printf("Tam es: %d\n",tam);
				memcpy(block + tam, (char*)buff, fmin(strlen((char*)buff),l));

				/*printf("El memove es %s\n",(block +(posicion % BLOCK_SIZE)));
				printf("El block es %s\n", block);*/

			}
			char *aux = malloc(sizeof(char)*sizeof(block));
	 		strcpy(aux,block);
			

			//printf("El bloque_id del if es %d\n",bloque_id);
      		if (bwrite(DEVICE_IMAGE, bloque_id, aux) < 0) {
        		bitmap_setbit(mp.d_map,bloque_id,0);
				inodos[fileDescriptor].inodosContenidos[i] = -1;
				printf("bwrite fallo\n");
        		return -1;
      		}

			

		} else if (restante > BLOCK_SIZE) {
			//printf("Medio\n");
			//printf("El bloque_id del else if es %d\n",bloque_id);
			memmove(block, (numBytes - restante) + buff, BLOCK_SIZE);

			char *aux = malloc(sizeof(char)*sizeof(block));
	 		strcpy(aux,block);

      		if (bwrite(DEVICE_IMAGE, bloque_id, aux) < 0) {
        		bitmap_setbit(mp.d_map,bloque_id,0);
				inodos[fileDescriptor].inodosContenidos[i] = -1;
        		return -1;
      		}

			restante -= BLOCK_SIZE;
		} else {
			//printf("Ultimo\n");
			//printf("El bloque_id del else es %d\n",bloque_id);
			//printf("Escribiendo %i bytes desde la posición %i en buffer\n", restante, (numBytes - restante));
			memmove(block, (numBytes - restante) + buff, restante);

			char *aux = malloc(sizeof(char)*sizeof(block));
	 		strcpy(aux,block);

      		if (bwrite(DEVICE_IMAGE, bloque_id, aux) < 0) {
        		bitmap_setbit(mp.d_map,bloque_id,0);
				inodos[fileDescriptor].inodosContenidos[i] = -1;
        		return -1;
      		}

			restante = 0;
		}
	}
	inodos[fileDescriptor].pos += numBytes-1;
	inodos[fileDescriptor].tamanyo = inodos[fileDescriptor].pos+1;
	//printf("\n");
	return numBytes;
}

/*
 * @brief	Modifies the position of the seek pointer of a file.
 * @return	0 if success, -1 otherwise.
 */
int lseekFile(int fileDescriptor, long offset, int whence)
{
	if ((fileDescriptor < 0) || (fileDescriptor > sbloque.numInodos - 1)){
        return -1;
    }
	if ((whence < 0) || (whence > 2)){
        return -1;
    }
	if (inodos[fileDescriptor].tipo == 0){
		int indice = inodos[fileDescriptor].inodosContenidos[0];
		fileDescriptor = indice;
	}
	//caso SEEK_CUR
	if (whence == 0){
		if (inodos[fileDescriptor].pos + offset < 0 || inodos[fileDescriptor].pos + offset > 2048){
			return -1;
		}

		else {
			inodos[fileDescriptor].pos = inodos[fileDescriptor].pos + offset;
			return 0;
		}
	}
	//caso SEEK_END
	if (whence == 1){
		inodos[fileDescriptor].pos = inodos[fileDescriptor].tamanyo;
		return 0;
	}
	//caso SEEK_BEGIN
	if (whence == 2){	
		inodos[fileDescriptor].pos = 0;
		return 0;
	}
	return -1;
}

/*
 * @brief	Checks the integrity of the file.
 * @return	0 if success, -1 if the file is corrupted, -2 in case of error.
 */

int checkFile (char * fileName)
{
    return -2;
}

/*
 * @brief	Include integrity on a file.
 * @return	0 if success, -1 if the file does not exists, -2 in case of error.
 */

int includeIntegrity (char * fileName)
{
    return -2;
}

/*
 * @brief	Opens an existing file and checks its integrity
 * @return	The file descriptor if possible, -1 if file does not exist, -2 if the file is corrupted, -3 in case of error
 */
int openFileIntegrity(char *fileName)
{

    return -2;
}

/*
 * @brief	Closes a file and updates its integrity.
 * @return	0 if success, -1 otherwise.
 */
int closeFileIntegrity(int fileDescriptor)
{
    return -1;
}

/*
 * @brief	Creates a symbolic link to an existing file in the file system.
 * @return	0 if success, -1 if file does not exist, -2 in case of error.
 */
int createLn(char *fileName, char *linkName)
{
    if(fileExist(fileName)==0){
		return -1;
	}

	if(fileExist(linkName)==-1){
		return -1;
	}

	if (isInodeFull() == -2 || isBlocksFull() == -2) {
        return -2;
    }

	int b_id, inodo_id;
 	inodo_id = ialloc();

 	if (inodo_id < 0) {
		return -2 ;
	}

 	b_id = alloc();

 	if (b_id < 0) {
		ifree(inodo_id);
		return -2 ;
	}

	int indice = busca_inodo(fileName);

	//Si el enlace a crear apunta a otro enlace, error
	if (inodos[indice].tipo == 0){
		return -2;
	}

 	inodos[inodo_id].tipo = 0; // ENLACE
 	strcpy(inodos[inodo_id].nombre, linkName);
 	inodos[inodo_id].inodosContenidos[0] = indice;
	inodos[inodo_id].cantidadBloquesOcupados = 0;
	inodos[inodo_id].open = inodos[indice].open;
	inodos[inodo_id].pos = 0;
	inodos[inodo_id].tamanyo = 0;

 	return 0;
}

/*
 * @brief 	Deletes an existing symbolic link
 * @return 	0 if the file is correct, -1 if the symbolic link does not exist, -2 in case of error.
 */
int removeLn(char *linkName)
{
	int i = busca_inodo(linkName);
	if(i == -1){
		return -1;
	}

	if (inodos[i].tipo == 1){
		return -2;
	}

	//Bitmap de inodos, el encontrado a 0.
	bitmap_setbit(mp.i_map,i,0);
	//Inodo encontrado vuelva a la normalidad
	inodos[i].tipo = 1;
	for (int j = 0; j < 5; j++){
		bitmap_setbit(mp.d_map,inodos[i].inodosContenidos[j],0);
		inodos[i].inodosContenidos[j] = -1;
	}
	// Escribe en esa dir de memoria el valor de en medio en todo ese tamanio
	memset(&(inodos[i].nombre), 0, 32+1);

	return	0;
}

void fullInodeMap() {
    for (int i = 0; i < 48; i++)
    {
        bitmap_setbit(mp.i_map,i,1);
    }
}

void fullBlockMap() {
    for (int i = 0; i < 38; i++){
        bitmap_setbit(mp.d_map,i,1);
    }
}


void printSystem() {
	fprintf(stdout, "Superbloque:\nNumero magico:%i\nNumBloquesMapaBits:%i\nNumInodos:%i\nPrimerInodo:%i\nNumBloquesDatos:%i\nPrimerBloqueDatos:%i\nTamDispositivo:%i\n\n\n", sbloque.numMagico, sbloque.numBloquesMapaBits, sbloque.numInodos, sbloque.primerInodo, sbloque.numBloquesDatos, sbloque.primerBloqueDatos, sbloque.tamDispositivo);

	fprintf(stdout, "Mapa de bits de inodos\n");
	for (int i = 0; i < 48; i++){
		if (bitmap_getbit(mp.i_map,i) == 0) {
			fprintf(stdout, "%d",0);
		}
		else{
			fprintf(stdout, "%d",1);
		}
	}

	fprintf(stdout, "\n\nMapa de bits de bloques\n");
	for (int i = 0; i < 300; i++){
		if (bitmap_getbit(mp.d_map,i) == 0) {
			fprintf(stdout, "%d",0);
		}
		else{
			fprintf(stdout, "%d",1);
		}
	}

	fprintf(stdout, "\n\n");

	for (int i = 0; i < 48; i++){
		fprintf(stdout, "Inodo %i: tipo %i, pos %i, open %i, integridad %i, nombre %s, inodos Contenidos [%i,%i,%i,%i,%i], tamaño %i, bloques ocupados %i\n", i, inodos[i].tipo, inodos[i].pos, inodos[i].open, inodos[i].integridad, inodos[i].nombre, inodos[i].inodosContenidos[0], inodos[i].inodosContenidos[1], inodos[i].inodosContenidos[2], inodos[i].inodosContenidos[3], inodos[i].inodosContenidos[4], inodos[i].tamanyo, inodos[i].cantidadBloquesOcupados);
	}


}
