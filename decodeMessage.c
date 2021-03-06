# include <decode.h>

/**********************************************************************/
/**                        Function: main                            **/
/**********************************************************************/

int main (int argc, char **argv) {

	FILE *fp; /* a file pointer for the input file */
	NODE *first = NULL; /* a pointer to the beginning of the linked list*/

	/* check that an input filename had been passed ... */
	if ( argc < 2 ) {
		fprintf( stderr, "Usage : decode <fileName>\n");
		return -1;
	}

	/* check if the file can be read */
	if ( (fp = fopen(argv[1],"r")) == NULL ) {
		fprintf( stderr, "Unable to open file %s\n", argv[1]);
		return -2;
	}

	/*printing out the given parameters*/
	printParameters(argc,argv);

	/* Read the file and construct the linked list */
	first = processFile(&fp, argv[1]);

    /*priting the elements of the list*/
	printList(first);

    /* the decoding of the message */
    decoding(first,argc,argv);

	/* Delete the list */
    deleteList(first);

	fclose(fp);

	return 0;
}
