/* 
 * This is an assembler program that translates assembly language code to
 * machine code.
 *
 *
 *      The program calls pass1, passing it the input file (or stdin).
 *      That function constructs a table of instruction labels and
 *      addresses from the input, where a label's address is determined by
 *      the address of its instruction.  Instructions are assumed to be 4
 *      bytes long, with the first instruction starting at address 0.
 *      Labels that appear anywhere but at the beginning of a line are
 *      ignored.
 *
 *      The program calls pass2, passing it the input file (or stdin) and
 *      table of instruction labels in pass 1. Machine language instructions
 *      will be generated based on provided MIPS instructions. Instructions
 *      are assumed to be 32 bits long.
 *      bytes long, with the first instruction starting at address 0.
 *      Labels that appear anywhere but at the beginning of a line are
 *      ignored.
 *
 *      For example, the following three lines of code would result in a
 *      table with one entry, indicating that label A_LABEL is at address 4.
 *                add $v0, $v1, $a0   # This instruction is at address 0
 *      A_LABEL:  slt $t0, $t1, $t2   # This instruction is at address 4
 *                bne $t0, $zero, A_LABEL  # This instr. is at address 8
 *      Using that label table, the machine release machine language 
 *      instructions. For example, for the first add instruction:
 *      00000000011001000001000000100000
 *      00000001001010100100000000101010
 *      00010101000000001111111111111110
 *
 * USAGE:
 *          name [ filename ] [ 0|1 ]
 *      where "name" is the name of the executable, "filename" is an
 *      optional file containing the input to read, and " 0" or "1"
 *      specifies that debugging should be turned off or on, respectively,
 *      regardless of any calls to debug_on, debug_off, or debug_restore in
 *      the program.  Both arguments are optional; if both are present they
 *      may appear in either order.  If no filename is provided, the
 *      program reads its input from stdin.  If no debugging choice is
 *      provided, the program prints debugging messages, or not, depending
 *      on indications in the code.
 *
 * INPUT:
 *      This program expects the input to consist of lines of MIPS
 *      instructions, each of which may (or may not) contain a label at the
 *      beginning of the line.  The input should have one MIPS instruction
 *      on each line.  Labels should appear as the first token in the line,
 *      followed immediately by a colon.  Labels may also appear elsewhere
 *      in an instruction, but those labels are ignored by this program.
 *
 * OUTPUT:
 *      The program prints the machine language instructions for provided
 *      MIPS instructions.  For the example above, the
 *      output might look like:
 *      00000000011001000001000000100000
 *      00000001001010100100000000101010
 *      00010101000000001111111111111110
 *
 *      With debugging, the program generates a label table with labels
 *      and corresponding addresses. It provides opcode, functcode, register
 *      number, instruction name, and corresponding machine language parts.
 *
 * ERROR CONDITIONS:
 *      - Wrong register name
 *      - Out of bound immediate value ( decimal 33 for 5 bits )
 *      - Invalid jump address
 *      - Invalid branch address
 *      - Invalid target label
 *      - Invalid instruction name
 *
 * Author: Alyce Brady
 * Date: 2/18/99
 *
 * Modified by:  Alyce Brady, 6/10/2014
 *      Allow filename to be passed as a parameter.
 * Modified by:  Alyce Brady, 5/25/2015
 *      Support use of printErr and printDebug functions.
 *      Improve function documentation.
 * Modified by:  Alyce Brady, 6/2/2019
 *      Improve function documentation.
 * Modified by: Chau Ta, 03/01/2022
 *      Improve top-of-file comments
 */

#include "assembler.h"

int main (int argc, char * argv[])
{
    FILE * fptr;               /* file pointer */
    LabelTableArrayList table;

    /* Process command-line arguments (if any) -- input file name
     *    and/or debugging indicator (1 = on; 0 = off).
     */
    fptr = process_arguments(argc, argv);
    if ( fptr == NULL )
    {
        return 1;   /* Fatal error when processing arguments */
    }

    /* Provide warning if user did not specify input file on command line. */
    if ( fptr == stdin )
    {
        printf("%s%s%s%s", "Warning: No input file provided, ",
                "so the program is now expecting you\nto provide the input ",
                "from the keyboard or from redirected stdin.\n",
                "Type control-D to end input from keyboard.\n");
    }

    /* Call pass1 to generate the label table. */
    table = pass1 (fptr);

    /* Print the label table if debugging is turned on. */
    if ( debug_is_on() )
        printLabels (&table);

    /* If this were an assembler, we would now rewind the file pointer
     * to be back at the beginning of the file and then call pass2,
     * passing it the label table. */
     
    rewind (fptr);
    pass2(fptr, &table);

    (void) fclose(fptr);
    return 0;
}
