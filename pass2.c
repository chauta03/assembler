/**
 * LabelTable pass2 (FILE * fp, LabelTable table)
 *      @param  fp  pointer to an open file (stdin or other file pointer)
 *                  from which to read lines of assembly source code
 *      @param  table  an existing Label Table
 *
 * DESCRIPTION MISSING !
 *
 * Author: <author>
 * Date:   <date>
 *
 * Modified by:  
 *      Why?
 *
 */

#include "assembler.h"

/* The following stub declaration should be removed once stub has been replaced
 * by real code.
 */
void stub(char * restOfInstruction, int lineNum);

void pass2 (FILE * fp, LabelTable table)
  /* returns a copy of the label table that was constructed */
{
    int    lineNum;            /* line number */
    int    PC = 0;             /* program counter */
    char   inst[BUFSIZ];       /* will hold instruction; BUFSIZ is max size
                                    of I/O buffer (defined in stdio.h) */
    char * instrName;          /* instruction name (e.g., "add") */
    char * restOfInstruction;  /* rest of instruction (e.g., "$t0, $t1, $t2") */

    char format;               /* Is instruction 'R', 'I', or 'J'? */
    int code;                  /* opcode or funct code, depending on format */
    int numOperands;           /* number of operands for a given instruction */

    /* Continuously read next line of input until EOF is encountered.
     */
    for (lineNum = 1; fgets (inst, BUFSIZ, fp); lineNum++)
    {
        PC += 4;

        /* Separate the instruction name from the rest of the statement.
         * If the line does not have an instruction, move on to next line.
         */
        getInstruction(inst, &instrName, &restOfInstruction);
        if ( instrName == NULL )
            continue;

        printDebug ("First non-label token is: %s\n", instrName);

        /* Determine the format and the opCode or functCode. */
        getOpInfo(lineNum, instrName, &format, &code, &numOperands);
        printDebug("%s instruction is %c format, with %d op/funct code.\n",
                    instrName, format, code);

        /* This call to stub should be replaced with actual useful code
         * that processes the instruction and prints the machine code
         * translation. */
        stub(lineNum, restOfInstruction, numOperands);

        printf("\n");
    }

    return;
}

/* Get instruction.
 * This function skips any leading whitespace or label, and strips
 * comments.  It then separates the instruction name (assuming there is
 * one) from the rest of the line, "returning" pointers to those two
 * strings in the two "pass-by-reference" parameters (which should actually
 * be addresses of the values to be returned).
 *    @param input        the line read in
 *    @param instrName    address where pointer to instruction name
 *                          should be placed; NULL if the line was
 *                          empty, contained only a comment, or
 *                          contained only a label
 *    @param restOfLine   address where pointer to rest of line should
 *                          be placed
 */
void getInstruction(char * input, char ** instrName, char **restOfLine)
{
    char * tokBegin, * tokEnd;     /* used to step thru input */

    /* If the line starts with a comment, move on to next line.  */
    if ( *input == '#' )
    {
        *instrName = NULL;
        return;
    }

    /* If there's a comment later in the line, strip it off
     *  (replace the '#' with a null byte).
     */
    (void) strtok (input, "#");

    /* Read the first token, skipping any leading whitespace. */
    tokBegin = input;
    getToken (&tokBegin, &tokEnd);
        /* tokBegin now points to 1st non-whitespace character
         * in the token and tokEnd points to 1st punctuation mark
         * or whitespace after the end of the token.
         */

    /* Skip label, if any */
    if ( *(tokEnd) == ':' )
    {
        /* Line has a label!  Get new token! */
        tokBegin = tokEnd + 1;
        getToken (&tokBegin, &tokEnd);
    }

    /* If empty line or line containing only a label, get next line */
    if ( *tokBegin == '\0' )
    {
        *instrName = NULL;
        return;
    }

    /* We have a valid token; turn it into a string and set
     * tokBegin to point to the character after the end.
     */
    *tokEnd = '\0';
    *instrName = tokBegin;
    *restOfLine = tokEnd + 1;
}

/* STUB CODE !!!
 * The real code and its documentation could be here or in a separate file.
 * Get format, op/funct code, and number of operands associated with a
 * given instruction.
 *    @param line           line number, for reporting errors
 *    @param instrName      name of instruction (input)
 *    @param format         address to fill with format ('R', 'I', or 'J')
 *    @param code           address to fill with opcode or funct code 
 *    @param numOperands    address to fill with number of operands
 *                              associated with this instruction
 *                              (e.g., jr $ra has one operand,
 *                                     add $$t0, $t1, $t2 has three)
 */
void getOpInfo(int line, char * instrName,
               char * format, int * code, int * numOperands)
{
    /* This stub assumes that every instruction is an R-format add
     * instruction, which has 3 operands.
     */
    *format = 'R';
    *code = 32;
    *numOperands = 3;
}

/* STUB CODE !!!
 * The real code and its documentation could be here or in a separate file.
 *   (You can decide whether or not to require that value be non-negative.)
 * Print value in pseudo-binary (made up of character '0's and '1's).
 *      @param value   value to print in pseudo-binary
 *      @param length  length of binary code needed, in bits
 *      @pre           `value` can be represented in `length` number of bits
 *      @pre           value >= 0
 */
void printBin(int value, int length)
{
    /* This stub prints the value in decimal format rather than binary,
     * which makes reading test data easier during development.
     */
    printf("%d ", value);
}

/* STUB CODE !!!
 * Below is an example of how you would call getNTokens on "the rest of the
 * instruction" (everything after the instruction name).  For example, if
 * you had the instruction "add $t0, $t1, $t2" then restOfInstruction would
 * be "$t0, $t1, $t2" and getNTokens would fill the arguments array with
 * the strings "$t0", "$t1", and "$t2".  If you had the instruction
 * "lw $t0, 0($s1)", then getNTokens would fill the arguments array with
 * the strings "$t0", "0", and "$s1".
 *
 * When getNTokens encounters an error, it puts a pointer to the error
 * message in arguments[0].
 */
void stub(int lineNum, char * restOfInstruction, int numOperands)
{
    char * arguments[3];      /* registers or values after name; max of 3 */

    /* Get arguments.  (Depending on instruction, should be 1, 2, or 3.) */
    if ( ! getNTokens(restOfInstruction, numOperands, arguments) )
    {
        printError("Error on line %d: %s\n", lineNum, arguments[0]);
        return;
    }

    /* Print the instruction name and the arguments (assume 3 in this stub). */
    printDebug("Rest of instruction consists of 3 arguments: ");
    printDebug("\"%s\", \"%s\", and \"%s\"\n", 
                        arguments[0], arguments[1], arguments[2]);
}
