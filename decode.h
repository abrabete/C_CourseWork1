#ifndef __DECODE_H
#define __DECODE_H

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**********************************************************************/
/**     This sctructure stores two nodes in the the linked list      **/
/**                One before it and one after it                    **/
/**********************************************************************/

struct anode {
	char value[10];     /* the storing of the value */
	struct anode *next; /* a pointer to the next node */
	struct anode *back; /* a pointer to the previous node */
};

typedef struct anode NODE;

/**********************************************************************/
/**                Functions included in the program                 **/
/**********************************************************************/

NODE *processFile (FILE **, char *);
NODE *newNode (char*, FILE **);
void deleteList (NODE *);
void printList (NODE *);
void printParameters(int, char **);
void decoding( NODE *, int, char **);

#endif
