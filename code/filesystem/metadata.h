
/*
 *
 * Operating System Design / Diseño de Sistemas Operativos
 * (c) ARCOS.INF.UC3M.ES
 *
 * @file 	metadata.h
 * @brief 	Definition of the structures and data types of the file system.
 * @date	Last revision 01/04/2020
 *
 */ 
 
#define bitmap_getbit(bitmap_, i_) (bitmap_[i_ >> 3] & (1 << (i_ & 0x07)))
static inline void bitmap_setbit(char *bitmap_, int i_, int val_) {
  if (val_)
    bitmap_[(i_ >> 3)] |= (1 << (i_ & 0x07));
  else
    bitmap_[(i_ >> 3)] &= ~(1 << (i_ & 0x07));
}


typedef struct superbloque
{
  /* Número mágico del superbloque: 0x000D5500 */
  int numMagico;

  /* Número de bloques del mapa inodos */
  int numBloquesMapaBits;               //= 1

  /* Número de inodos en el dispositivo */
  int numInodos;                       //= 48               

  /* Número bloque del 1o inodo del disp. (inodo raíz), es el 2 porque se empieza en 0 */                                                            
  int primerInodo;                     //= 2                                               

  /* Número de bloques de datos en el disp., se calcula con el mkfs */
  int numBloquesDatos;               //= device_size / Block_size - 2 - (Lo que ocupe los bloques de inodos = 3) 

  /* Número de bloque del 1o bloque de datos */                 
  int primerBloqueDatos;            //= 1 + (lo que ocupe el bloque de inodos = 3)

  /* Tamaño total del disp. (en bytes), entre 460 KiB y 600 KiB */
  int tamDispositivo;              //= device_size;  

  /* Campo de relleno (para completar un bloque), lo que sobre */                                    
  char padding[2020];   /* El padding 2020 para que haga 2048 */
}superbloque;
 
typedef struct mapas{
  char i_map[6];            //[48]; 48 bits         //[num_inodos = 48]
  char d_map[38];               //[38];  //[300 (maximo teorico de tamanio) / 8 (bits en 1 byte) = 38] sonn los bloques de datos
  char padding[2004];    /* para que llegue a 2048 */ 
}mapas;
 

/*Los inodos ocupan 3 bloques, porque 48 *128 / 2048 es 3,   48 es la 
cantidad maxima de inodos, 128 lo que ocupa cada inodo y 2048 lo que 
ocupa cada ibloque */

typedef struct inodo{
  /* tipo fichero = 1 o tipo enlace blando = 0 */
  int tipo;

  /*Pos: posicion en bytes desde el inicio del archivo */
  int pos;

  /* 1 si open, 0 si close */
  int open;

  /*Integridad*/
  int integridad;

  /* Nombre del fichero asociado */                                                           
  char nombre[32+1];  //el +1 para el /0

  /* 10 KiB / 2048 son 5 bloques, en cada posicion se pone el bloque que está usando el archivo */                                                             
  int inodosContenidos[5]; //inodosContenidos[0] si es simbolico el inodo al que apunta

  /* maximo 10240 bytes */
  int tamanyo;

  /*Bloques que ocupan los datos del archivo del inodo*/                                                   
  int cantidadBloquesOcupados;   

  /* El tamaño del padding es 47 */
  char relleno[47];                                        
} inodo;