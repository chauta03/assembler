#include "assembler.h"

/*
 * The functions in this file print pseudo-binary output for:
 *    - integer values, e.g., 23
 *    - integer values represented as strings, e.g., "23"
 *    - registers, e.g., $zero ==> "00000"
 *    - jump targets
 *    - branch offsets
 * The pseudo-binary output actually consists of character 0's and 1's,
 * with the length of the binary output specified by the `numBits`
 * parameter.  The `lineNum` parameter is used when printing error
 * messages.
 *
 * Author(s):
 * Date:
 *      with assistance from:
 *      working side-by-side with:
 * 
 * Modification Log:
 *    - AB, 3/25/2020 - implement printIntInString, stub printInt,
 *                      provide skeletons for others
 *    - ???
 */

/* Print integer value in pseudo-binary (made up of character '0's and '1's).
 *      @param value   value to print in pseudo-binary
 *      @param length  length of binary code needed, in bits
 *      @pre           value can be represented in `length` number of bits
 *      @pre           value >= 0
 *   (You can decide whether or not to require that `value` be non-negative.)
 */
void printInt(int value, int length)
{
    /* Print the value passed as a parameter in decimal format.
     */

    /* STUB CODE !!!  REAL CODE MISSING !!! */

    /* This is NOT the correct final behavior of this function, but may
     * be useful during development because the output is easier to read
     * than binary (or pseudo-binary) output would be.
     * When all testing has been completed, the printf statement
     * should be removed, commented out, or turned into a printDebug.
     */
    printf(" (%d)", value);
}


/* Print register in pseudo-binary (made up of character '0's and '1's).
 *      @param regName   name of register to print in pseudo-binary
 *      @param lineNum   line number (for error messages)
 * If the register name passed as a parameter is an invalid register name,
 * this function prints "<invalid reg>" instead of the register number,
 * allowing the rest of the instruction to be parsed and printed.
 */
void printReg(char * regName, int lineNum)
{
    /* If the string contains a valid register name, print the register number.
     * Otherwise print "<invalid reg>".
     */

    /* CODE MISSING !!! */
}


/* Print value in `intInString` as pseudo-binary (made up of character
 * '0's and '1's).
 *      @param intInString   string containing integer, e.g., "23"
 *      @param length  length of binary code needed, in bits
 *      @param lineNum line number (for error messages)
 *      @pre           integer can be represented in `length` number of bits
 *      @pre           integer >= 0
 *   (You can decide whether or not to require that integer be non-negative.)
 */
void printIntInString(char * intInString, int numBits, int lineNum)
{
    char * endPtr;

    /* Convert string to decimal (base 10) value. */
    int decimal = (int) strtol(intInString, &endPtr, 10);

    /* If the string contained a valid int, print it;
     * otherwise print an error message.
     */
    if ( *intInString != '\0' && *endPtr == '\0' )
    {
        /* entire string was valid */
        printInt(decimal, numBits);
    }
    else
    {
        printError("Line %d: trying to print %s as an int (%s).\n",
                lineNum, intInString, "not a valid integer");
    }
}


/* Print address to jump to.
 *      @param targetLabel   label being branched to
 *      @param table         label table
 *      @param lineNum       line number (for error messages)
 */
void printJumpTarget(char * targetLabel, LabelTableArrayList * table,
                     int lineNum)
{
    /* This function should call findLabel to get the address associated
     * with the target label in the label table, calculate the portion of
     * the address to store in the instruction, and then print that value
     * with the appropriate number of bits.
     */

    /*  CODE MISSING !!! */

}


/* Print branch offset to branch to the target label.
 *      @param targetLabel   label being branched to
 *      @param table         label table
 *      @param PC            Program Counter (could use lineNum instead)
 *      @param lineNum       line number (for error messages)
 */
void printBranchOffset(char * targetLabel, LabelTableArrayList * table,
                       int PC, int lineNum)
{
    /* This function should call findLabel to get the address associated
     * with the target label in the label table, calculate the distance
     * from the PC to that address and the portion of that to store in the
     * instruction, and then print that value with the appropriate number
     * of bits.
     */

    /*  CODE MISSING !!! */

}
