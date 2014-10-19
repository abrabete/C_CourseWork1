#include <decode.h>

short int count = 0; /* the number of values read from the file so far */

/**********************************************************************/
/**                     Function: processFile                        **/
/**	Read the contents of the file and create a circular linked list  **/
/**				containing the characters from the file              **/
/**	Parameters:														 **/
/**		p_fp		Points to the file								 **/
/**		p_filename 	A string that contains the file name			 **/
/**																	 **/
/**	Returns:														 **/
/**		A pointer to the first node in the list.					 **/
/**********************************************************************/

NODE *processFile ( FILE **p_fp, char *p_fileName) {

	short int readCount;   /* the number of values read for the current record*/
	char val[2];           /* the caracter for the current record */
	NODE *temp = NULL;     /* the node that has just been read from the file */
	NODE *first = NULL;    /* the first node of the list */
	NODE *last = NULL;     /* the last node of the list during the file procces*/

    /* read values until the end of file */
	while (!feof(*p_fp)) {
        /* check for the corrrect content of record */
        if( (readCount = fscanf(*p_fp,"%s",val)) != 1) {
            if (readCount <= 0)
                break;
            else {
                fprintf(stderr,"Error reading file %s: invalid record\n",p_fileName);
                fclose(*p_fp);
                exit(-3);
            }
        }
        /* check if the read value is a letter or not */
        if ((*val >= 'A' && *val <= 'Z') || (*val >= 'a' && *val <= 'z' )) {
            count++;
            temp = newNode(val,p_fp);
            /* check is this is the first ellement of the list or not*/
            if (first == last && first == NULL) {
                /* adding the first ellement to the list */
                first = last = temp;
                first->next = last->next = NULL;
                first->back = last->back = NULL;
            }
            else {
                /* adding the rest of records to the list */
                last->next = temp;
                temp->back = last;
                last = temp;
                first->back = last;
                last->next = first;
            }
        }
    }
    /* returning the first element of the list */
	return first;
}

/**********************************************************************/
/**						 Function: newNode			                 **/
/**	 Allocates memory to a new node and populates it with the value	 **/
/**			  The next and back pointers are set to NULL			 **/
/**																	 **/
/**	Parameters:														 **/
/**		p_value	   The value read from file 						 **/
/**		p_fp	   The file pointer in case we get an error and want **/
/**					the input file before exiting.					 **/
/**																	 **/
/**	Returns:														 **/
/**		A pointer to the new node.									 **/
/**********************************************************************/

NODE *newNode (char *p_value, FILE **p_fp) {

	/* allocate the memory for the new node */
	NODE *node = (NODE *)malloc(sizeof(NODE));

	/* check if memory was allocated */
	if ( node == NULL ) {
		fprintf(stderr,"Memory not allocated\n");
		fclose(*p_fp);
		exit(-4);
	}

	/* populate the node value */
	strcpy(node->value,p_value);
	node->back = NULL;
	node->next = NULL;

	/* return the node */
	return node;
}

/**********************************************************************/
/**                    Function: deleteList                          **/
/**     Free the memory held by the list from the root node down     **/
/**                                                                  **/
/**  Parameters:                                                     **/
/**     p_first      The first node of the list                      **/
/**  Returns:                                                        **/
/**     (nothing)                                                    **/
/**********************************************************************/

void deleteList( NODE *p_first) {

    NODE *temp;
    short int i;
    for (i = 1; i<=count; i++) {
        temp = p_first;
        p_first = p_first->next;
        free(temp);
    }

    free(p_first);
}

/**********************************************************************/
/**                      Function: printList                         **/
/**       Prints out the elements of the circular linked list        **/
/** Parameters:                                                      **/
/**     p_node      The node that is going to be printed out         **/
/** Returns:                                                         **/
/**     (nothing)                                                    **/
/**********************************************************************/

void printList( NODE *p_node) {

    NODE *p = p_node;

    /* check if list is empty or not */
    if (p == NULL) {
        printf("The list is empty\n");
        return;
    }
    else {
        printf("Decoding wheel values:\n");
        printf("    %s",p->value);
        p = p->next;
        while ( p!= p_node) {
            printf("%s",p->value);
            p = p->next;
        }
    }
    printf("\n\n");
}


/**********************************************************************/
/**                     Function: printParameters                    **/
/**        Printing out the parameters passed to the program         **/
/**                                                                  **/
/** Parameters:                                                      **/
/**     int argc        The number of parameters                     **/
/**     char **argv     The list of parameters                       **/
/** Returns:                                                         **/
/**     (nothing)                                                    **/
/**********************************************************************/

void printParameters(int argc, char **argv) {

    printf("Parameter listing:\n");
	int i = 1;
	for (i;i<argc;i++) {
        printf("    %d: %s\n",i,argv[i]);
	}
    printf("\n");
}


/**********************************************************************/
/**                      Function: decoding                          **/
/**              The actual decoding of the message                  **/
/**                                                                  **/
/** Parameters:                                                      **/
/**     NODE *first      The pointer to the beginning of the list    **/
/**     int argc        The number of the parameters                 **/
/**     char **argv     The list of parameters                       **/
/** Returns:                                                         **/
/**     (nothing)                                                    **/
/**********************************************************************/

void decoding( NODE *first, int argc, char **argv) {

    NODE *temp;
    int i = 2;
    int x;
    int j;
    temp = first;
    printf("Decoded message:\n");
    printf("    ");
    for (i;i<argc;i++) {
        x = atoi(argv[i]);
        if ( x == 0) {
            printf("%s",temp->value);
        }
        else {
            if (x > 0) {
                for (j=0;j<x;j++) {
                    temp = temp->next;
                }
                printf("%s",temp->value);
            }
            else {
                x = -1*x;
                for (j=0;j<x;j++) {
                    temp = temp->back;
                }
                printf("%s",temp->value);
            }
        }

    }
    printf("\n");

}
