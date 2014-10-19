#include <decode.h>
#include <ctype.h>
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

	short int readCount; /* the number of values read for the current record*/
	char val[2];            /* the caracter for the current record */
	NODE *temp = NULL;   /* the node that has just been read from the file */
	NODE *head = NULL;      /* a pointer to a node */
	NODE *first = NULL;
	NODE *last = NULL;
	/*first = newNode("A",p_fp);*/
	printf("OK so far\n");
	while (!feof(*p_fp)) {
        if( (readCount = fscanf(*p_fp,"%s",val)) != 1) {
            if (readCount <= 0)
                break;
            else {
                fprintf(stderr,"Error reading file %s: invalid record\n",p_fileName);
                fclose(*p_fp);
                exit(-3);
            }
        }
        if ((*val >= 'A' && *val <= 'Z') || (*val >= 'a' && *val <= 'z' )) {
            count++;
            printf("%s\n",val);
            printf("is a letter\n");
            temp = newNode(val,p_fp);
            if (first == last && first == NULL) {
                first = last = temp;
                first->next = last->next = NULL;
                first->back = last->back = NULL;
            }
            else {
                last->next = temp;
                temp->back = last;
                last = temp;
                first->back = last;
                last->next = first;
            }
        }
    }
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
/**     p_root      The root node of the list                        **/
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
    if (p == NULL) {
        printf("The list is empty\n");
        return;
    }
    else {
        printf("%s\n",p->value);
        p = p->next;
        while ( p!= p_node) {
            printf("%s\n",p->value);
            p = p->next;
        }
    }
}



