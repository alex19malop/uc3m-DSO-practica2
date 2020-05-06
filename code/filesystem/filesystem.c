
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
	sbloque.primerBloqueDatos = 4;
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
			bwrite(DEVICE_IMAGE, i + 5, bloque);
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
    // cerrar sesión de trabajo
    inodos[fileDescriptor].pos = 0;
    inodos[fileDescriptor].open = 0;
    return 0;
}


/*
 * @brief	Reads a number of bytes from a file and stores them in a buffer.
 * @return	Number of bytes properly read, -1 in case of error.
 */
int readFile(int fileDescriptor, void *buffer, int numBytes)
{
	return -1;
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

	fprintf(stdout, "[WF] numBytes: %i\n", numBytes);
	// Calcular numero de bloques que se van escribir
	int bloques_escribir = (int) ceil(((double)numBytes/BLOCK_SIZE));

	// Eliminar bloques que ya no van a ser usados, cuando escribes sobreescribes lo que esta despues de la posicion
	int posicion = inodos[fileDescriptor].pos;
	int aux_bloque = floor(posicion/BLOCK_SIZE);
	for (int i = aux_bloque + 1; inodos[fileDescriptor].tamanyo > 0 && i < inodos[fileDescriptor].cantidadBloquesOcupados; i++)
	{
		bitmap_setbit(mp.d_map,inodos[fileDescriptor].inodosContenidos[i], 0);
	}


	// Comenzando desde el bloque de la posición actual hasta el último bloque se va a escribir
		// Obtener el bloque asociado a la posición actual del fichero
		// Si no tiene bloque asociado, asignar uno nuevo
	char block[BLOCK_SIZE];
	int restante = numBytes;
	fprintf(stdout, "[WF] Iniciando en %i durante %i bloques\n", aux_bloque, bloques_escribir);
	for (int i = aux_bloque; i < aux_bloque + bloques_escribir; i++)
	{
		memset(block, 0, BLOCK_SIZE);
		int bloque = inodos[fileDescriptor].inodosContenidos[i] + 5;
		if(i >= inodos[fileDescriptor].cantidadBloquesOcupados) {
			bloque = alloc();
			if(bloque < -1) {
				return -1;
			}
			inodos[fileDescriptor].inodosContenidos[i] = bloque;
			inodos[fileDescriptor].cantidadBloquesOcupados++;
		}
		// Si es el primer bloque a escribir, escribir teniendo en cuenta la posición actual
		if(i == aux_bloque){
			fprintf(stdout, "[IF] Escribiendo bloque en posición %i\n", i);
			if(bread(DEVICE_IMAGE, bloque, block) < 0) {
				return -1;
			}
			int offset = posicion % BLOCK_SIZE;
			int length = BLOCK_SIZE - offset;
			fprintf(stdout, "[IF] Escribiendo desde offset %i con longitud %i\n", offset, length);
			memmove(offset + block, buff, length);
			fprintf(stdout,"El block que escribimos es : %s \n",block);
			fprintf(stdout,"El bloque que escribimos es : %d \n",bloque);
			char *aux = malloc(sizeof(char)*sizeof(block));
			strcpy(aux,block);
			if(bwrite(DEVICE_IMAGE, bloque, aux) == -1) {
				return -1;
			}
			char b[BLOCK_SIZE + 1];
			memset(b, 0, BLOCK_SIZE + 1);
			fprintf(stdout, "Contenido b: %s\n", b);
			bread(DEVICE_IMAGE, bloque, b);
			fprintf(stdout, "Contenido b: %s\n", b);
			restante = restante - length;
		}
		// Si es el último bloque a escribir, escribir teniendo el cuenta hasta donde se escribe
		/*else if (restante > BLOCK_SIZE) {
			fprintf(stdout, "[ELSE IF] Escribiendo bloque en posición %i\n", i);
			memmove(block, ((i - aux_bloque) * BLOCK_SIZE) + buff, BLOCK_SIZE);
			if(bwrite(DEVICE_IMAGE, bloque, block) == -1) {
				return -1;
			}
			restante = restante - BLOCK_SIZE;
		}
		// Si es un bloque cualquiera, escribir por completo
		else {
			fprintf(stdout, "[ELSE] Escribiendo bloque en posición %i\n", i);
			memmove(block, ((i - aux_bloque) * BLOCK_SIZE) + buff, restante);
			bwrite(DEVICE_IMAGE, bloque, block);
		}*/
	}
	// Actualizar inodos[fd].posición a posición inicial más bytes escritos

	inodos[fileDescriptor].pos += numBytes;
	inodos[fileDescriptor].tamanyo = inodos[fileDescriptor].pos;
	return numBytes;
}

/*
 * @brief	Modifies the position of the seek pointer of a file.
 * @return	0 if success, -1 otherwise.
 */
int lseekFile(int fileDescriptor, long offset, int whence)
{
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
    return -1;
}

/*
 * @brief 	Deletes an existing symbolic link
 * @return 	0 if the file is correct, -1 if the symbolic link does not exist, -2 in case of error.
 */
int removeLn(char *linkName)
{
    return -2;
}

void fullInodeMap() {
    for (int i = 0; i < 48; i++)
    {
        bitmap_setbit(mp.i_map,i,1);
    }
}

void fullBlockMap() {
    for (int i = 0; i < 38; i++)
    {
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
