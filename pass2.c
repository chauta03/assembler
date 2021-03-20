/**
 * void pass2 (FILE * fp, LabelTableArrayList * table)
 *      @param  fp  pointer to an open file (stdin or other file pointer)
 *                  from which to read lines of assembly source code
 *      @param  table  a pointer to an existing Label Table
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

void pass2 (FILE * fp, LabelTableArrayList * table)
{
    int    lineNum;            /* line number */
    int    PC = 0;             /* program counter */
    char   inst[BUFSIZ];       /* will hold instruction; BUFSIZ is max size
                                    of I/O buffer (defined in stdio.h) */
    char * instrName;          /* instruction name (e.g., "add") */
    char * restOfInstruction;  /* rest of instruction (e.g., "$t0, $t1, $t2") */

    /* Continuously read next line of input until EOF is encountered.
     */
    for (lineNum = 1; fgets (inst, BUFSIZ, fp); lineNum++)
    {
        PC += 4;

        /* Separate the instruction name from the rest of the statement.
         * If the line does not have an instruction, move on to next line.
         */
        getInstName(inst, &instrName, &restOfInstruction);
        if ( instrName == NULL )
            continue; /* Go to top of loop to read next line of input. */

        printDebug ("First non-label token is: %s\n", instrName);

        /* Determine whether this is an R-format, I-format, or J-format
         * instruction based on the opcode.  If it is an R-format
         * instruction, get the funct code also.  Then process the
         * instruction.
         */
        int opcode = getOpCode(instrName);
        printDebug("%s instruction has opcode %d.\n", instrName, opcode);
        if ( opcode == 0 )
        {
            int functCode = getFunctCode(instrName);
            printDebug("%s instruction has funct code %d.\n",
                    instrName, functCode);
            if ( functCode == -1 )
            {
                /* Print error message - this is not a valid instruction!  */
                printf("Invalid instruction %s on line %d.\n", instrName,
                        lineNum);
                continue; /* Go to top of loop to read next line of input. */
            }

            processR(lineNum, functCode, restOfInstruction);
        }
        else
        {
            processIorJ(lineNum, table, opcode, restOfInstruction, PC);
        }
    }

    return;
}


/* STUB CODE !!!
 * The real code and its documentation could be here or in a separate file.
 * Get opcode associated with a given instruction.
 *    @param instrName      name of instruction (input)
 *    @return  the opCode if instrName is a valid I or J format instruction,
 *             or 0 (i.e., if instrName is either a valid R format instruction
 *             or is not a valid instruction of any format)
 */
int getOpCode(char * instrName)
{
    /* This stub assumes that instrName is not a valid I or J format
     * instruction.
     *   (NOT NECESSARILY A GOOD ASSUMPTION -- CODE MISSING!)
     */
    return 0;
}

/* STUB CODE !!!
 * The real code and its documentation could be here or in a separate file.
 * Get funct code associated with a given instruction.
 *    @param instrName      name of instruction (input)
 *    @return  the funct code if instrName is a valid R format instruction,
 *             or -1 if instrName is not a valid R format instruction
 */
int getFunctCode(char * instrName)
{
    /* This stub only recognizes the R-format add instruction.
     *   (CODE MISSING!)
     */
    if ( strcmp(instrName, "add") == SAME )
        return 32;

    /* instrName not recognized */
    return -1;
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
void processR(int lineNum, int functCode, char * restOfInstruction)
{
    char * arguments[3];      /* registers or values after name; max of 3 */
    int numOperands;

    /* JR only has 1 operand; all other R-format instructions have 3. */
    if ( functCode == 8 )
    {
        numOperands = 1;
    }
    else
    {
        numOperands = 3;
    }

    /* Get arguments.  (Depending on instruction, should be 1, 2, or 3.) */
    if ( ! getNTokens(restOfInstruction, numOperands, arguments) )
    {
        printError("Error on line %d: %s\n", lineNum, arguments[0]);
        return;
    }

    /* Process arguments and print machine code version of instruction. */
    if ( functCode == 8 )       /* Handle jr instruction */
    {
        printDebug("jr \"%s\"\n", arguments[0]);

        /* CODE MISSING ! */

    }
    /*  else if ( functCode == ??? )     // Handle sll and srl
     *  {
     *      // Shift amount is a number in a string, not an int
     *      // e.g., printIntInString(arguments[2], 5, lineNum);
     *  }
     */
    else                        /* Handle common format for add, etc. */
    {
        printDebug("funct %d \"%s\", \"%s\", and \"%s\"\n", functCode,
                            arguments[0], arguments[1], arguments[2]);

        /* Print binary for the opcode, registers, shift amount,
         * and funct code.
         */
        /* INCOMPLETE CODE ! */
        printInt(0, 6);
        printReg(arguments[0], lineNum);
        printInt(functCode, 6);
        printf("\n");
    }

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
void processIorJ(int lineNum, LabelTableArrayList * table,
                 int opcode, char * restOfInstruction, int PC)
{
    char * arguments[3];      /* registers or values after name; max of 3 */
    int numOperands;

    /* Print the opcode (this part is the same for all I/J formats */
    printInt(opcode, 6);

    /* As with processR, the opcode will tell you how many arguments (or
     * parameters) to get from getNTokens.
     * Then, handle the various unusual formats, followed by
     * the common format for addi, addiu, andi, etc.
     */

    /* CODE MISSING ! */

    printf(" is not implemented yet.\n");
}

