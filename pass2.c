/**
 * void pass2 (FILE * fp, LabelTableArrayList * table)
 *      @param  fp  pointer to an open file (stdin or other file pointer)
 *                  from which to read lines of assembly source code
 *      @param  table  a pointer to an existing Label Table
 *
 * This function reads the lines in an assembly source file and print
 * machine version.  It reads MIPS assembly language and write out the
 * corresponding machine language instructions. If an error occurs, the
 * function prints an error message.
 *
 * The function in this file:
 *  - Read MIPS codes and print corresponding machine language
 *  - Get corresponding opcode for an instruction name (I and J instructions)
 *  - Get corresponding functcode for an instruction name (R instructions)
 *  - Print machine language instructions for I and J instructions
 *  - Print machine language instructions ofr R instructions
 *
 * Author: Chau Ta
 * Date:   28/02/22
 *
 * Modified by:  Chau Ta, 3/1/2022 - Replace printIntInString to Unsigned
 *                                   and Signed version
 * Modified by: Chau Ta, 3/21/2022 - Print error by stderr rather than stdout
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


/*
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
     * instruction, so it returns 0.
     */

    /* get Opcode for I instructions from 8 to 13 */
    static char * instrArrayI[] =   
    {
            "addi","addiu",
            "slti","sltiu",
            "andi","ori"
    };

    /* Loop through the array. If match an item, return associated opcode */
    int i;
    for (i = 0; i < 6; i++)
    {
        if ( strcmp(instrName, instrArrayI[i]) == SAME )
            return i + 8;       /* opcode from 8-13 */ 
    }

    /* get Opcode for other I instruction cases */
    if ( strcmp(instrName, "beq") == SAME )
        return 4;
    else if ( strcmp(instrName, "bne") == SAME )
        return 5;
    else if ( strcmp(instrName, "lw") == SAME )
        return 35;
    else if ( strcmp(instrName, "sw") == SAME )
        return 43;
    else if ( strcmp(instrName, "lui") == SAME )
        return 15;
    /* get Opcode for J instructions */
    else if ( strcmp(instrName, "j") == SAME )
        return 2;
    else if ( strcmp(instrName, "jal") == SAME )
        return 3;

    /* if not valid I and J instructions, return 0 */
    return 0;

}

/*
 * The real code and its documentation could be here or in a separate file.
 * Get funct code associated with a given instruction.
 *    @param instrName      name of instruction (input)
 *    @return  the funct code if instrName is a valid R format instruction,
 *             or -1 if instrName is not a valid R format instruction
 */
int getFunctCode(char * instrName)
{
    /* 
     * This stub only recognizes the R-format add instruction.
     */

    if ( strcmp(instrName, "sll") == SAME )
        return 0;
    else if ( strcmp(instrName, "srl") == SAME )
        return 2;
    else if ( strcmp(instrName, "jr") == SAME )
        return 8;

    /* Array of some R instructions having funct code from 32 - 43*/
    static char * instrArrayR[] =
    {
        "add", "addu", "sub", "subu",
        "and", "or", "invalid", "nor",  /* Because R instructions do not include 38 */
        "invalid", "invalid",        /* Because R instructions do not include 40 and 41 */
        "slt", "sltu"
    };

    /* loop through the array: if match an item, return associated funct code */
    int i;
    for (i = 0; i < 12; i++)    
    {
        if ( strcmp(instrName, instrArrayR[i]) == SAME )
            return i + 32;
    }
    

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
        numOperands = 1;
    else
        numOperands = 3;

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

        printInt(0, 6);     /* opcode */
        printReg(arguments[0], lineNum); /* register */
        printInt(0, 5); 
        printInt(0, 5);
        printInt(0, 5);
        printInt(functCode, 6);
        printf("\n");

    }
    /*  else if ( functCode == ??? )     // Handle sll and srl
     *  {
     *      // Shift amount is a number in a string, not an int
     *      // e.g., printIntInString(arguments[2], 5, lineNum);
     *  }
     */
    else if ( functCode == 0 || functCode == 2) /* sll & srl */
    {
        printInt(0, 11);
        printReg(arguments[1], lineNum);
        printReg(arguments[0], lineNum);
        printUnsignedIntInString(arguments[2], 5, lineNum);

        if ( functCode == 0 )
            printInt(0, 6);
        else 
            printInt(2, 6);
        
        printf("\n");
    }
    else                        /* Handle common format for add, etc. */
    {
        printDebug("funct %d \"%s\", \"%s\", and \"%s\"\n", functCode,
                            arguments[0], arguments[1], arguments[2]);

        /* Print binary for the opcode, registers, shift amount,
         * and funct code.
         */
        printInt(0, 6);
        printReg(arguments[1], lineNum);
        printReg(arguments[2], lineNum);
        printReg(arguments[0], lineNum);
        printInt(0, 5);
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

    if ( opcode == 2 || opcode == 3 )
        numOperands = 1;
    else if ( opcode == 15 )
        numOperands = 2;
    else
        numOperands = 3;

    /* Get arguments.  (Depending on instruction, should be 1, 2, or 3.) */
    if ( ! getNTokens(restOfInstruction, numOperands, arguments) )
    {
        printError("Error on line %d: %s\n", lineNum, arguments[0]);
        return;
    }

    /* J INSTRUCTIONS */
    if ( opcode == 2 || opcode == 3 ) /* j and jal */
    {
        printJumpTarget( arguments[0], table, lineNum);
    }
    /* I INSTRUCTIONS */
    else if ( opcode == 15 )    /* lui */
    {
        printInt(0, 5);
        printReg(arguments[0], lineNum);
        printUnsignedIntInString(arguments[1], 16, lineNum);
    }
    else if ( opcode == 35 || opcode == 43 )    /* lw & sw */
    {
        printReg(arguments[2], lineNum);
        printReg(arguments[0], lineNum);
        printSignedIntInString(arguments[1], 16, lineNum);
    }
    else 
    {
        if ( opcode == 4 || opcode == 5 )   /* beq & bne */
        {
            printReg(arguments[0], lineNum);
            printReg(arguments[1], lineNum);
            printBranchOffset(arguments[2] , table, PC, lineNum);
        }
        else
        {
            printReg(arguments[1], lineNum);
            printReg(arguments[0], lineNum);
            printSignedIntInString(arguments[2], 16, lineNum);
        }
    }
    printf("\n");
    /* printf(" is not implemented yet.\n"); */
}
