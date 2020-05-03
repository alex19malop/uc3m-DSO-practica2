
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
	
	for (int i = 0; i < 505; i++)
	{
		sbloque.padding[i] = 0; 
	}
  

	for (int i = 0; i < 48; i++)
	{
		inodos[i].tipo = 1;
		inodos[i].pos = 0;
		inodos[i].open = 0;
		inodos[i].integridad = 0;
		strcpy(inodos[i].nombre,"");
		for (int j = 0; j < 5; j++){
			inodos[i].inodosContenidos[j] = 0;
		}
		inodos[i].tamanyo = 0;
		inodos[i].cantidadBloquesOcupados = 0;
		for (int j = 0; j < 52; j++)
		{  
			inodos[i].relleno[j] = 0;
		}
	} 

	for (int i = 0; i < 2037; i++)  
	{
		if(i < 48){
			bitmap_setbit(mp.i_map,i,0);
		}

		if(i < 38){
			bitmap_setbit(mp.d_map,i,0);
		}
		if(i==39 || i==38 ||i==0 || i==1 || i==2){
			bitmap_setbit(mp.d_map,i,1);
		}

		mp.padding[i] = 0;
	}

	//escribir el superbloque
	bwrite(DEVICE_IMAGE,0,(char*)(&sbloque));
	//escribir el bitmap
	bwrite(DEVICE_IMAGE,1,(char*)(&mp));
	//escribir inodos. Ya que los inodos ocupan 3 bloques (48 * 128 / 2048) hay que hacer 3 bwrites
	bwrite(DEVICE_IMAGE,2,(char*)(&inodos));
	bwrite(DEVICE_IMAGE,3,(char*)(&inodos+BLOCK_SIZE));
	bwrite(DEVICE_IMAGE,4,(char*)(&inodos+BLOCK_SIZE*2));
	printf("tamanio de inodo %li\n",sizeof(inodo));
	printf("tamanio de superbloque %li\n",sizeof(superbloque));
	printf("tamanio de mapas %li\n",sizeof(mapas));
 	return 0;
}

/*
 * @brief 	Mounts a file system in the simulated device.
 * @return 	0 if success, -1 otherwise.
 */
int mountFS(void)
{
	//escribir el superbloque
	bread(DEVICE_IMAGE,0,(char*)(&sbloque));
	//escribir el bitmap
	bread(DEVICE_IMAGE,1,(char*)(&mp));
	//escribir inodos. Ya que los inodos ocupan 3 bloques (48 * 128 / 2048) hay que hacer 3 bwrites
	bread(DEVICE_IMAGE,2,(char*)(&inodos));
	bread(DEVICE_IMAGE,3,(char*)(&inodos+BLOCK_SIZE));
	bread(DEVICE_IMAGE,4,(char*)(&inodos+BLOCK_SIZE*2));
	printf("magic number %d\n",sbloque.numMagico);
	return 0; 
	
}

/*
 * @brief 	Unmounts the file system from the simulated device.
 * @return 	0 if success, -1 otherwise.
 */ 
int unmountFS(void)
{
	//escribir el superbloque
	bwrite(DEVICE_IMAGE,0,(char*)(&sbloque));
	//escribir el bitmap
	bwrite(DEVICE_IMAGE,1,(char*)(&mp));
	//escribir inodos. Ya que los inodos ocupan 3 bloques (48 * 128 / 2048) hay que hacer 3 bwrites
	bwrite(DEVICE_IMAGE,2,(char*)(&inodos));
	bwrite(DEVICE_IMAGE,3,(char*)(&inodos+BLOCK_SIZE));
	bwrite(DEVICE_IMAGE,4,(char*)(&inodos+BLOCK_SIZE*2));
	printf("magic number %d\n",sbloque.numMagico);
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
				inodos[i].inodosContenidos[j] = 0;
			}
			inodos[i].tamanyo = 0;
			inodos[i].cantidadBloquesOcupados = 0;
			for (int j = 0; j < 52; j++)
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
 	for (int i=0; i<(ceil(sbloque.tamDispositivo/BLOCK_SIZE) - 5); i++)
 	{
		if (bitmap_getbit(mp.d_map,i) == 0) {
			bitmap_setbit(mp.d_map,i,1);	// bloque ocupado ahora
            /* No se ponen valores por defecto del bloque */
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
	printf("El inodo_i es: %d\n",inodo_id);

 	if (inodo_id < 0) {
		return -2 ;
	}
	
 	b_id = alloc();
	printf("El b_id es: %d\n",b_id);

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

/*void cleanName(int i) {
	for (int j = 0; j < 32; j++)
	{
		charcpy(inodos[i].nombre[j],'');
	}
	
}*/

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
	inodos[i].pos = 0;
	inodos[i].open = 0; 
	inodos[i].integridad = 0;
	printf("mi nombre es: %s \n", inodos[i].nombre);
	strncpy(inodos[i].nombre,"",32);
	//cleanName(i);
	printf("mi nombre es: %s \n", inodos[i].nombre);
	for (int j = 0; j < 5; j++){
		if(inodos[i].inodosContenidos[j]!=0){
			bitmap_setbit(mp.d_map,inodos[i].inodosContenidos[j],0);
		}
		inodos[i].inodosContenidos[j] = 0;
	}
	inodos[i].tamanyo = 0;
	inodos[i].cantidadBloquesOcupados = 0;
	for (int j = 0; j < 52; j++)
	{  
		inodos[i].relleno[j] = 0;
	}

	return	0;
}

/*
 * @brief	Opens an existing file.
 * @return	The file descriptor if possible, -1 if file does not exist, -2 in case of error..
 */
int openFile(char *fileName)
{
    if(fileExist(fileName)==0){
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
int writeFile(int fileDescriptor, void *buffer, int numBytes)
{
	return -1;
}

/*
 * @brief	Modifies the position of the seek pointer of a file.
 * @return	0 if succes, -1 otherwise.
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
	printf("Superbloque:\nNumero magico:%i\nNumBloquesMapaBits:%i\nNumInodos:%i\nPrimerInodo:%i\nNumBloquesDatos:%i\nPrimerBloqueDatos:%i\nTamDispositivo:%i\n\n\n", sbloque.numMagico, sbloque.numBloquesMapaBits, sbloque.numInodos, sbloque.primerInodo, sbloque.numBloquesDatos, sbloque.primerBloqueDatos, sbloque.tamDispositivo);

	printf("Mapa de bits de inodos\n");
	for (int i = 0; i < 48; i++){
		if (bitmap_getbit(mp.i_map,i) == 0) {
			printf("%d",0);
		}
		else{
			printf("%d",1);
		}
	}

	printf("\n\nMapa de bits de bloques\n");
	for (int i = 0; i < 38; i++){
		if (bitmap_getbit(mp.d_map,i) == 0) {
			printf("%d",0);
		}
		else{
			printf("%d",1);
		}
	}

	printf("\n\n");

	for (int i = 0; i < 48; i++){
		printf("Inodo %i: tipo %i, pos %i, open %i, integridad %i, nombre %s, inodos Contenidos [%i,%i,%i,%i,%i], tamaño %i, bloques ocupados %i\n", i, inodos[i].tipo, inodos[i].pos, inodos[i].open, inodos[i].integridad, inodos[i].nombre, inodos[i].inodosContenidos[0], inodos[i].inodosContenidos[1], inodos[i].inodosContenidos[2], inodos[i].inodosContenidos[3], inodos[i].inodosContenidos[4], inodos[i].tamanyo, inodos[i].cantidadBloquesOcupados);
	}
	
}