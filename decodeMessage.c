# include <decode.h>

/**********************************************************************/
/*                         Function: main                             */
/**********************************************************************/

int main (int argc, char **argv) {
	
	FILE *fp; /* a file pointer for the input file */
	NODE *root = NULL; /* a pointer to the beginning of the linked list*/
	
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
	
	fclose(fp);
	return 0;
}
	
