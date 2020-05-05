
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

	///////

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
	*                                                               *
	*                           TEST F1.9                           *
	*                                                               *
	*****************************************************************
	*						  TEST F1.9.1 						    *
	****************************************************************/

		ret = createFile("/test1.txt");
		createFile("/test1.txt");
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

		//printSystem();




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
