#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * Method to pass the char as upper case if lower case
 */
char toUpper(char ch) 
{
	if (ch > 96 && ch < 123) {
		return ch-32;
	}
	return ch;
	
}

int parse_file(char *file)
{
	char c;
	char *f_out;
	FILE *in;
	int inBF, inIT, inEND, inDeep;
	
	// if input file exist, open it
	in = fopen(file, "r"); 
    if (in == NULL) {
        perror("Failed to open the file");
        return -1;
    }
	
 	inBF = 0; // flag to indicate if starting line for speaking (* .. : .. )
	inIT = 0; // flag to indicate if indication (@( .. ))
	inDeep = 0; // Keep track of the deep of () into @(..)
	inEND = 0; // #END line
	
	while ((c = getc(in)) != EOF) {
		if(inEND == 1){ // skip #END line
			if (c == '\n'){
				printf("\n\n");
				inEND = 0;
			}
		}
		else if(c == '*' && inBF == 0 && inIT == 0) { // detect start of * .. :
			printf("\\textbf{\\bsc{");
			inBF = 1;
		}
		else if (c == ':' && inBF == 1 && inIT == 0){ // detect end of * .. :
			printf("}}:");
			inBF = 0;
		}
		else if (c == '@' && inIT == 0) { // detect start of @(..)
			c = getc(in);
			if(c == '(') {
				printf("\\textit{(");
				inIT = 1;
			}
		}
		else if (c == '(' && inIT == 1) {
			printf("(");
			inDeep = inDeep + 1;
		}
		else if (c == ')' && inIT == 1) {
			if (inDeep == 0) {
				printf(")}");
				inIT = 0;
			}
			else {
				printf(")");
				inDeep = inDeep - 1;
			}
		}
		else if(c == '#' && inIT == 0 && inBF == 0) {
			c = getc(in);
			if(c == 'S') {
				c = getc(in);
				if(c == 'C') {
					c = getc(in);
					if(c == 'E') {
						c = getc(in);
						if(c == 'N') {
							c = getc(in);
							if(c == 'E') {
								c = getc(in);
								if(c == ' '){
									c = getc(in);
								}
								if(c >= '0' || c <= '9'){
									printf("\\clearpage\\subsection{Scène %c}", c);
								}
							}
						}
					}
				}
			} else if (c == 'E') {
				c = getc(in);
				if (c == 'N'){
					c = getc(in);
					if (c == 'D'){
						inEND = 1;
					}
				}
			}
		}
		else if (inBF == 1) {
			printf("%c", toUpper(c));
		}
		else {
			printf("%c", c);
		}
	}
 
    fclose(in);
 
    return 0;
}

int main(int argc, char *argv[])
{
	parse_file(argv[1]);
}
