
/*
 *
 * Operating System Design / Diseño de Sistemas Operativos
 * (c) ARCOS.INF.UC3M.ES
 *
 * @file 	test.c
 * @brief 	Implementation of the client test routines.
 * @date	01/03/2017
 *
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "filesystem/filesystem.h"


// Color definitions for asserts
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_BLUE "\x1b[34m"

#define N_BLOCKS 25					  // Number of blocks in the device
#define DEV_SIZE N_BLOCKS *BLOCK_SIZE // Device size, in bytes

int main()
{
	int ret;


	/****************************************************************
	*						 TEST F1.1   			 			    *
	****************************************************************/
	/* Prueba basica de creacion de un sistema de ficheros */

	ret = mkFS(DEV_SIZE);
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.1 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.1 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);



	/****************************************************************
	*                                                               *
	*                           TEST F1.2                           *
	*                                                               *
	*****************************************************************
	*						 TEST F1.2.1   			 			    *
	****************************************************************/
	/* Prueba basica para montar un sistema de ficheros */

	ret = mountFS();
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.2.1 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.2.1 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);


	/****************************************************************
	*						 TEST F1.2.2   			 			    *
	****************************************************************/
	/* Prueba para montar un sistema de ficheros sin haber creado el sistema
	de ficheros */

	/*ret = mountFS();
	if (ret != -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.2.2 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.2.2 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

*/


	/****************************************************************
	*                                                               *
	*                           TEST F1.4                           *
	*                                                               *
	*****************************************************************
	*						 TEST F1.4.1 			 			    *
	****************************************************************/
	/* Prueba basica de creacion de 4 archivos, debe de devolver 0 si el fichero
	 ha sido creado correctamente */

	/*int a,b,c,d;

	a = createFile("/test1.txt");
	b = createFile("/test2.txt");
	c = createFile("/test3.txt");
	d = createFile("/test4.txt");

	if ((a + b + c + d ) != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.4.1 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.4.1 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);


	printSystem();
*/
	/****************************************************************
	*						TEST F1.4.2 						    *
	****************************************************************/
	/* Prueba en la cual se repite el nombre de un archivo que se desea crear.
	El int c devolverá -1, ya que el fichero no ha podido ser creado porque ya
	existe en el sistemade ficheros.*/

	/*int a,b,c,d;

	a = createFile("/test1.txt");
	b = createFile("/test2.txt");
	c = createFile("/test2.txt");
	d = createFile("/test3.txt");


	if (a == 0 && b == 0 && c == -1 && d == 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.4.2 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}
	else {
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.4.2 ", ANSI_COLOR_RED, "FAIL\n", ANSI_COLOR_RESET);
		return -1;
	}*/

	/****************************************************************
	*						TEST F1.4.3 						    *
	****************************************************************/
	/* Prueba en la cual no hay inodos disponibles.
	Para ello llenaremos el mapa de inodos, por lo que createFile deberá devolver -2 */

	/*fullInodeMap(); //Pone a 1 a todas las posiciones del mapa de inodos
	int a;
	a = createFile("/test1.txt");


	if (a == -2)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.4.3 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}
	else {
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.4.3 ", ANSI_COLOR_RED, "FAIL\n", ANSI_COLOR_RESET);
		return -1;
	}*/

	/****************************************************************
	*						TEST F1.4.4 						    *
	****************************************************************/
	/* Prueba en la cual no hay bloques disponibles.
	Para ello llenaremos el mapa de bloques, por lo que createFile deberá devolver -2 */

	/*fullBlockMap();
	int a;
	a = createFile("/test1.txt");


	if (a == -2)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.4.4 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}
	else {
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.4.4 ", ANSI_COLOR_RED, "FAIL\n", ANSI_COLOR_RESET);
		return -1;
	}*/

	/****************************************************************
	*                                                               *
	*                           TEST F1.5                           *
	*                                                               *
	*****************************************************************
	*						 TEST F1.5.1 			 			    *
	****************************************************************/
	/* Prueba basica de creacion de 4 archivos y eliminacion del primero de ellos,
	debe de devolver 0 si el fichero ha sido eliminado correctamente */

	/*int a,b,c,d;
	a = createFile("/test1.txt");
	b = createFile("/test2.txt");
	c = createFile("/test3.txt");
	d = createFile("/test4.txt");
	ret = removeFile("/test1.txt");

	if (ret != 0 || a != 0 || b != 0 || c !=0 || d != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.5.1 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.5.1 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	printSystem();*/

	/****************************************************************
	*						 TEST F1.5.2 			 			    *
	****************************************************************/
	/* Prueba basica de creacion de 4 archivos y eliminacion del un archivo inexistente,
	debe de devolver -1 si el fichero no se ha encontrado */

	/*int a,b,c,d;
	a = createFile("/test1.txt");
	b = createFile("/test2.txt");
	c = createFile("/test3.txt");
	d = createFile("/test4.txt");
	ret = removeFile("/test5.txt");

	if (ret != -1 || a != 0 || b != 0 || c !=0 || d != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.5.2 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.5.2 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

*/

	/****************************************************************
	*						TEST F1.5.3						    *
	****************************************************************/
	/* Prueba basica de creacion de 1 archivo y eliminacion de un enlace existente,
	a través de la funcion de eliminar archivos removeFile */
	/*
	int x;
	createFile("/test1.txt");
	createLn("/test1.txt","enlace1");
	printSystem();
	x = removeFile("enlace1");

	if (x != -2)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.5.3 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.5.3 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	*/

	/****************************************************************
	*						 TEST F1.5.4 			 			    *
	****************************************************************/
	/* Prueba basica de creacion de 4 archivos y eliminacion del un archivo existente,
	eliminando tambien los enlaces simbolicos que apuntan al archivo */
	/*
	int a;
	createFile("/test1.txt");
	createFile("/test2.txt");
	createLn("/test1.txt","enlace1");
	createLn("/test1.txt","enlace2");
	printSystem();
	a = removeFile("/test1.txt");
	printSystem();
	if (a != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.5.4 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.5.4 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	
	*/

	/****************************************************************
	*                                                               *
	*                           TEST F1.6                           *
	*                                                               *
	*****************************************************************
	*						  TEST F1.6.1 						    *
	****************************************************************/
    /* Prueba basica para abrir un archivo existente */

	/*int x,y;
	createFile("/test1.txt");
	createFile("/test2.txt");
	x = openFile("/test1.txt");
	y = openFile("/test2.txt");
	printSystem();
	if (x == -1 || x == -2 || y == -1 || y == -2)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.6.1  ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.6.1  ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	*/

	/****************************************************************
	*						  TEST F1.6.2						    *
	****************************************************************/
    /* Prueba basica para abrir un archivo ya abierto anteriormente */

	/*int z;
	createFile("/test1.txt");
	openFile("/test1.txt");
	z = openFile("/test1.txt");
	if (z == -2)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.6.2 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	}
	else {
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.6.2 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}*/

	/****************************************************************
	*						  TEST F1.6.3						    *
	****************************************************************/
    /* Prueba basica para abrir un archivo inexistente */

	/*int p;

	p = openFile("/test7.txt");
	if (p == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.6.3 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	}
	else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.6.3 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}*/

	/****************************************************************
	*						TEST F1.6.4						   		*
	****************************************************************/
	/* Prueba en la cual se abre un archivo a través del enlace simbolico*/
	/*
	int a;
	createFile("/test1.txt");
	createLn("/test1.txt","enlace1");
	a = openFile("enlace1");
	printSystem();

	if (a == -1 || a == -2)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.6.4  ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.6.4  ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	*/

	/****************************************************************
	*                                                               *
	*                           TEST F1.7                           *
	*                                                               *
	*****************************************************************
	*						  TEST F1.7.1 						    *
	****************************************************************/
    /* Prueba basica para cerrar un descriptor de fichero */

	/*int e;
	createFile("/test1.txt");
	openFile("/test1.txt");
	e = closeFile(0);
	if (e == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.7.1  ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.7.1  ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	*/


	/****************************************************************
	*						  TEST F1.7.2 						    *
	****************************************************************/
    /* Prueba basica para cerrar un descriptor de fichero ya cerrado o no inicializado*/

	/*int g;

	g = closeFile(2);
	if (g == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.7.2 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	}
	else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.7.2 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}*/


	/****************************************************************
	*						  TEST F1.7.3 						    *
	****************************************************************/
    /* Prueba basica para cerrar descriptor de fichero fuera de inodo */

	/*int h;

	h = closeFile(60);
	if (h == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.7.3 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	}
	else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.7.3 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}*/

	/****************************************************************
	*						TEST F1.7.4						    	*
	****************************************************************/
	/* Prueba en la cual se cierra un archivo a través del enlace simbolico*/
	/*
	int a;
	createFile("/test1.txt");
	createLn("/test1.txt","enlace1");
	openFile("enlace1");
	printSystem();
	a = closeFile(1);
	printSystem();

	if (a == -1 || a == -2)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.7.4  ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.7.4  ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	*/

	/****************************************************************
	*                                                               *
	*                           TEST F1.8                           *
	*                                                               *
	*****************************************************************
	*						  TEST F1.8.1 						    *
	****************************************************************/
	/* Prueba en la que se intenta leer en un fichero abierto un numero de bytes, 
	para ello se reabre el fichero antes para poner el puntero de lectura a 0*/

	/*ret = createFile("/test1.txt");
	int fd = openFile("/test1.txt");
	char *buffer1 = "esto es una prueba";
	writeFile(fd, buffer1, strlen(buffer1)+1);
	closeFile(fd);
	
	char lectura[4096];
	fd = openFile("/test1.txt");
	ret = readFile(fd, lectura, 18);
	
	printf("El valor leido es: %s\n",lectura);
	

	if (ret == -1)
	{
	   	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.8.1 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	   	return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.8.1 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);


	printSystem();*/


	/****************************************************************
	*						  TEST F1.8.2 						    *
	****************************************************************/
	/* Prueba en la que se intenta leer en un archivo que no ha sido abierto,
	por lo que debería devolver -1 */

	/*ret = createFile("/test1.txt");
	int fd = openFile("/test1.txt");
	char *buffer1 = "esto es una prueba";
	writeFile(fd, buffer1, strlen(buffer1)+1);
	closeFile(fd);
	//No lo he reabierto
	char lectura[4096];
	ret = readFile(fd, lectura, 19);

	printf("El valor leido es: %s\n",lectura);

	if (ret == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.8.2 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}
	else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.8.2 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	printSystem();*/


	/****************************************************************
	*						  TEST F1.8.3 						    *
	****************************************************************/
	/* Prueba en la que se intenta leer en un archivo cuyo inodo no existe,
	por lo que deberá devolver 0 */

	/*char lectura[4096];
	ret = readFile(15, lectura, 19);

	printf("El valor leido es: %s\n",lectura);

	if (ret == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.8.3 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}
	else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.8.3 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	printSystem();*/

	/****************************************************************
	*						  TEST F1.8.4 						    *
	****************************************************************/

	/* Prueba en la que se lee en un fichero abierto una cadena de caracteres
	con el objetivo de que se lea varios bloques */

	ret = createFile("/test1.txt");
	int fd = openFile("/test1.txt");
	char *buffer1 = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111112222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333344444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444445555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555";
	ret = writeFile(fd, buffer1, strlen(buffer1)+1);
	closeFile(fd);

	char lectura[5600];
	fd = openFile("/test1.txt");
	ret = readFile(fd, lectura, 5120);

	printf("El valor leido es: %s\n",lectura);


	if (ret == -1)
	{
   		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.8.4 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
   		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.8.4 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	printSystem();


	/****************************************************************
	*						  TEST F1.8.5 						    *
	****************************************************************/

	/* Prueba en la que se escribe en un fichero abierto varios writes diferentes,
	posteriormente se leeran 3 veces diferentes, guardando en 3 buffers diferentes para 
	comprobar el correcto funcionamiento de los punteros */

	/*ret = createFile("/test1.txt");
	int fd = openFile("/test1.txt");
	char *buffer1 = "Primera Prueba";
	char *buffer2 = "Segunda Prueba";
	char *buffer3 = "Tercera Prueba";

	ret = writeFile(fd, buffer1, strlen(buffer1)+1);
	ret = writeFile(fd, buffer2, strlen(buffer2)+1);
	ret = writeFile(fd, buffer3, strlen(buffer3)+1);
	closeFile(fd);

	char lectura1[4096];
	char lectura2[4096];
	char lectura3[4096];

	fd = openFile("/test1.txt");
	ret = readFile(fd, lectura1, 14);
	ret = readFile(fd, lectura2, 14);
	ret = readFile(fd, lectura3, 14);

	printf("El valor leido de lectura1 es: %s\n",lectura1);
	printf("El valor leido de lectura2 es: %s\n",lectura2);
	printf("El valor leido de lectura3 es: %s\n",lectura3);

	printSystem();

	//closeFile(fd);

	if (ret == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.8.5 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.8.5 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

*/

	/****************************************************************
	*						  TEST F1.8.6 						    *
	****************************************************************/
	/* Prueba en la que se lee en varios ficheros abiertos diferentes cadena de caracteres*/

	/*createFile("/test1.txt");
	createFile("/test2.txt");
	int fd1 = openFile("/test1.txt");
	int fd2 = openFile("/test2.txt");
	char *buffer1 = "Primera Prueba";
	char *buffer2 = "Segunda Prueba";
	
	writeFile(fd1, buffer1, strlen(buffer1)+1);
	writeFile(fd2, buffer2, strlen(buffer2)+1);
	closeFile(fd1);
	closeFile(fd2);
	fd1 = openFile("/test1.txt");
	fd2 = openFile("/test2.txt");

	char lectura1[4096];
	char lectura2[4096];

	int ret1 = readFile(fd1, lectura1, 14);
	int ret2 = readFile(fd2, lectura2, 14);

	printf("El valor leido de lectura1 es: %s\n",lectura1);
	printf("El valor leido de lectura2 es: %s\n",lectura2);

	//closeFile(fd);

	if (ret1 == -1 || ret2 == -1)
	{
	   	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.8.6 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	   	return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.8.6 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);


	printSystem();*/



	/****************************************************************
	*						  TEST F1.8.7 						    *
	****************************************************************/
	/* Prueba en la que se lee en varios ficheros abiertos alternativamente diferentes 
	cadena de caracteres. La primera cadena ocupa todo un bloque*/

/*	createFile("/test1.txt");
	createFile("/test2.txt");
	int fd1 = openFile("/test1.txt");
	int fd2 = openFile("/test2.txt");

	char *buffer1 = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111112222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222";
	char *buffer2 = "Primera Prueba";
	char *buffer3 = "Segunda Prueba";

	writeFile(fd1, buffer1, strlen(buffer1)+1);
	writeFile(fd2, buffer2, strlen(buffer2)+1);
	writeFile(fd1, buffer3, strlen(buffer3)+1);

	closeFile(fd1);
	closeFile(fd2);

	char lectura1[4096];
	char lectura2[4096];

	fd1 = openFile("/test1.txt");
	int ret1 = readFile(fd1, lectura1, 2048+14);

	fd2 = openFile("/test2.txt");
	int ret2 = readFile(fd2, lectura2, 14);

	printf("El valor leido de lectura1 es: %s\n",lectura1);
	printf("El valor leido de lectura2 es: %s\n",lectura2);





	if (ret1 == -1 || ret2 == -1 )
	{
	   	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.8.7 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	   	return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.8.7 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);


	printSystem();


*/







	

	/****************************************************************
	*                                                               *
	*                           TEST F1.9                           *
	*                                                               *
	*****************************************************************
	*						  TEST F1.9.1 						    *
	****************************************************************/
	/* Prueba en la que se escribe en un fichero abierto una cadena de caracteres*/

	/*ret = createFile("/test1.txt");
	createFile("/test2.txt");
	createFile("/test3.txt");
	createFile("/test4.txt");
	int fd = openFile("/test1.txt");
	char *buffer1 = "esto es una prueba";
	ret = writeFile(fd, buffer1, strlen(buffer1)+1);
	//closeFile(fd);

	if (ret == -1)
	{
	   	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.9.1 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	   	return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.9.1 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);


	printSystem();*/


	/****************************************************************
	*						  TEST F1.9.2 						    *
	****************************************************************/
	/* Prueba en la que se intenta escribir en un archivo que no ha sido abierto,
	por lo que debería devolver -1 */

	/*ret = createFile("/test1.txt");
	char *buffer1 = "esto es una prueba";
	ret = writeFile(1, buffer1, strlen(buffer1)+1);
	if (ret == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.9.2 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}
	else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.9.2 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	printSystem();*/


	/****************************************************************
	*						  TEST F1.9.3 						    *
	****************************************************************/
	/* Prueba en la que se intenta escribir en un archivo cuyo inodo no existe,
	por lo que deberá devolver 0 */

	/*char *buffer1 = "esto es una prueba";
	ret = writeFile(13, buffer1, strlen(buffer1)+1);

	if (ret == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.9.3 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}
	else{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.9.3 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	printSystem();*/

	/****************************************************************
	*						  TEST F1.9.4 						    *
	****************************************************************/

	/* Prueba en la que se escribe en un fichero abierto una cadena de caracteres
	con el objetivo de que ocupe varios bloques */

	/*ret = createFile("/test1.txt");
	int fd = openFile("/test1.txt");
	char *buffer1 = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111112222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333333344444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444444445555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555555";
	ret = writeFile(fd, buffer1, strlen(buffer1)+1);

	if (ret == -1)
	{
   		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.9.4 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
   		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.9.4 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	printSystem();*/


	/****************************************************************
	*						  TEST F1.9.5 						    *
	****************************************************************/

	/* Prueba en la que se escribe en un fichero abierto varios writes diferentes */

	/*ret = createFile("/test1.txt");
	int fd = openFile("/test1.txt");
	char *buffer1 = "Primera Prueba";
	char *buffer2 = "Segunda Prueba";
	char *buffer3 = "Tercera Prueba";
	char *buffer4 = "Cuarta Prueba";


	ret = writeFile(fd, buffer1, strlen(buffer1)+1);
	//closeFile(fd);
	//fd = openFile("/test1.txt");
	ret = writeFile(fd, buffer2, strlen(buffer2)+1);
	//closeFile(fd);
	//fd = openFile("/test1.txt");
	ret = writeFile(fd, buffer3, strlen(buffer3)+1);
	//closeFile(fd);
	//fd = openFile("/test1.txt");
	ret = writeFile(fd, buffer4, strlen(buffer4)+1);

	printSystem();

	//closeFile(fd);

	if (ret == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.9.5 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.9.5 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);*/


	/****************************************************************
	*						  TEST F1.9.6 						    *
	****************************************************************/
	/* Prueba en la que se escribe en varios ficheros abiertos diferentes cadena de caracteres*/

	/*createFile("/test1.txt");
	createFile("/test2.txt");
	int fd1 = openFile("/test1.txt");
	int fd2 = openFile("/test2.txt");
	char *buffer1 = "Primera Prueba";
	char *buffer2 = "Segunda Prueba";


	int ret1 = writeFile(fd1, buffer1, strlen(buffer1)+1);
	int ret2 = writeFile(fd2, buffer2, strlen(buffer2)+1);
	//closeFile(fd);

	if (ret1 == -1 || ret2 == -1)
	{
	   	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.9.6 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	   	return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.9.6 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);


	printSystem();*/



	/****************************************************************
	*						  TEST F1.9.7 						    *
	****************************************************************/
	/* Prueba en la que se escribe en varios ficheros abiertos alternativamente diferentes cadena de caracteres. La primera cadena ocupa todo un bloque*/

	/*createFile("/test1.txt");
	createFile("/test2.txt");
	int fd1 = openFile("/test1.txt");
	int fd2 = openFile("/test2.txt");

	char *buffer1 = "11111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111112222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222222";
	char *buffer2 = "Primera Prueba";
	char *buffer3 = "Segunda Prueba";

	int ret1 = writeFile(fd1, buffer1, strlen(buffer1)+1);
	int ret2 = writeFile(fd2, buffer2, strlen(buffer2)+1);
	int ret3 = writeFile(fd1, buffer3, strlen(buffer3)+1);
	//closeFile(fd);

	if (ret1 == -1 || ret2 == -1 || ret3 == -1)
	{
	   	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.9.7 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
	   	return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.9.7 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);


	printSystem();*/

	/****************************************************************
	*                                                               *
	*                           TEST F1.10                           *
	*                                                               *
	*****************************************************************
	*						  TEST F1.10.1 						    *
	****************************************************************/
    /* Prueba basica de lseekFile */
	/*
	createFile("/test1.txt");
	createFile("/test2.txt");
	createFile("/test3.txt");
	createFile("/test4.txt");
	int fd = openFile("/test1.txt");
	char *buffer1 = "esto es una prueba";
	ret = writeFile(fd, buffer1, strlen(buffer1)+1);
	printSystem();
	int a = lseekFile(fd, 3L, FS_SEEK_CUR);
	printSystem();
	//closeFile(fd);

	if (a == -1)
	{
   		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.10.1 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
   		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.10.1 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	*/


	/****************************************************************
	*                                                               *
	*                           TEST F1.15                          *
	*                                                               *
	*****************************************************************
	*						  TEST F1.15.1						    *
	****************************************************************/
	/* Prueba en la que se crea un enlace simbolico de un archivo existente*/

	/*int x;
	createFile("/test1.txt");
	x = createLn("/test1.txt","enlace1");
	printSystem();
	if (x != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.15.1 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.15.1 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	*/

	/****************************************************************
	*						  TEST F1.15.2						    *
	****************************************************************/
	/* Prueba en la que se crea un enlace simbolico de un archivo inexistente*/
	/*
	int x;
	createFile("/test1.txt");
	x = createLn("/test8.txt","enlace1");
	printSystem();
	if (x != -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.15.2 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.15.2 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	*/
	/****************************************************************
	*						TEST F1.15.3 						    *
	****************************************************************/
	/* Prueba en la cual no hay inodos disponibles.
	Para ello llenaremos el mapa de inodos, por lo que createLn deberá devolver -2 */

	/*fullInodeMap(); //Pone a 1 a todas las posiciones del mapa de inodos
	int a;
	createFile("/test1.txt");
	a = createLn("/test1.txt","enlace1");


	if (a == -2)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.15.3 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}
	else {
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.15.3 ", ANSI_COLOR_RED, "FAIL\n", ANSI_COLOR_RESET);
		return -1;
	}*/

	/****************************************************************
	*						TEST F1.15.4						    *
	****************************************************************/
	/* Prueba en la cual no hay bloques disponibles.
	Para ello llenaremos el mapa de bloques, por lo que createLn deberá devolver -2 */

	/*fullBlockMap();
	int a;
	createFile("/test1.txt");
	a = createLn("/test1.txt","enlace1");


	if (a == -2)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.15.4 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}
	else {
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.15.4 ", ANSI_COLOR_RED, "FAIL\n", ANSI_COLOR_RESET);
		return -1;
	}*/

	/****************************************************************
	*						TEST F1.15.5						    *
	****************************************************************/
	/* Prueba en la cual se intenta crear un enlace simbolico apuntando a otro enlace.
	CreateLn deberá devolver -2 */
	/*
	int a;
	createFile("/test1.txt");
	createLn("/test1.txt","enlace1");
	printSystem();
	a = createLn("enlace1","enlace2");
	printSystem();
	if (a == -2)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.15.5 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}
	else {
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.15.5 ", ANSI_COLOR_RED, "FAIL\n", ANSI_COLOR_RESET);
		return -1;
	}
	*/

	/****************************************************************
	*						TEST F1.15.6 						    *
	****************************************************************/
	/* Prueba en la cual se repite el nombre de un enlace que se desea crear.
	C y D devolverán -1, ya que contienen nombres repetidos y no pueden crearse*/
	/*
	int a,b,c,d,e;

	a = createFile("/test1.txt");
	b = createFile("/test2.txt");
	c = createLn("/test2.txt","/test2.txt");
	createLn("/test2.txt","enlace");
	d = createFile("/test3.txt");
	e = createLn("/test2.txt","enlace");

	printSystem();

	if (a == 0 && b == 0 && c == -1 && d == 0 && e == -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.15,6 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	}
	else {
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.15.6 ", ANSI_COLOR_RED, "FAIL\n", ANSI_COLOR_RESET);
		return -1;
	}
	*/
	/****************************************************************
	*                                                               *
	*                           TEST F1.16                          *
	*                                                               *
	*****************************************************************
	*						  TEST F1.16.1						    *
	****************************************************************/
	/* Prueba en la que se elimina un enlace simbolico de un archivo existente*/
	/*
	int x;
	createFile("/test1.txt");
	createLn("/test1.txt","enlace1");
	printSystem();
	x = removeLn("enlace1");
	printSystem();
	if (x != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.16.1 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.16.1 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
	*/

	/****************************************************************
	*						TEST F1.16.2						    *
	****************************************************************/
	/* Prueba basica de creacion de 1 archivo y eliminacion de un enlace inexistente,
	debe de devolver -1 si el fichero no se ha encontrado */
	/*
	int x;
	createFile("/test1.txt");
	createLn("/test1.txt","enlace1");
	printSystem();
	x = removeLn("enlace20");

	if (x != -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.16.2 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.16.2 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	*/

	/****************************************************************
	*						TEST F1.16.3						    *
	****************************************************************/
	/* Prueba basica de creacion de 1 archivo y eliminacion de un archivo existente,
	a través de la funcion de eliminar simbolos removeLn */
	/*
	int x;
	createFile("/test1.txt");
	createLn("/test1.txt","enlace1");
	printSystem();
	x = removeLn("/test1.txt");

	if (x != -2)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.16.3 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.16.3 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	*/


	/****************************************************************
	*                                                               *
	*                           TEST F1.3                           *
	*                                                               *
	*****************************************************************
	*						  TEST F1.3.1 						    *
	****************************************************************/
    /* Prueba basica para desmontar un sistema de ficheros */

	ret = unmountFS();
	if (ret != 0)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.3.1 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.3.1 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	/****************************************************************
	*						  TEST F1.3.2 						    *
	****************************************************************/
	/*Prueba para desmontar un sistema del fichero, el cual no ha sido creado previamente,
	por lo que debería devolver -1 para marcar el error */

	/*ret = unmountFS();
	if (ret != -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.3.2 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.3.2 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);
*/

	/****************************************************************
	*						  TEST F1.3.3						    *
	****************************************************************/
	/*Prueba para desmontar un sistema del fichero, el cual SI ha sido creado previamente,
	pero no ha sido montado, por lo que debería devolver -1 para marcar el error.
	Para realizar esta prueba es necesario comentar todas las pruebas anteriores. */

	/*ret = mkFS(DEV_SIZE);
	ret = unmountFS();
	if (ret != -1)
	{
		fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.3.3 ", ANSI_COLOR_RED, "FAILED\n", ANSI_COLOR_RESET);
		return -1;
	}
	fprintf(stdout, "%s%s%s%s%s", ANSI_COLOR_BLUE, "TEST F1.3.3 ", ANSI_COLOR_GREEN, "SUCCESS\n", ANSI_COLOR_RESET);

	*/

	return 0;
}
