# A simple makefile

GCC=gcc -Wall -Wextra -Wpedantic -Wformat -Wshadow -Wredundant-decls \
    -Wstrict-prototypes
# Can also use -Wtraditional or -Wmissing-prototypes

all:	assembler

#  Switch to alternative versions of the all target as you're ready for them.
# all:	testLabelTable testGetNTokens
# all:	testLabelTable testGetNTokens testPass1
# all:	testLabelTable testGetNTokens testPass1 assembler

testLabelTable: assembler.h \
	LabelTable.c \
    	process_arguments.c \
	printDebug.c \
	printError.c \
	same.c \
    	testLabelTable.c
	$(GCC) -g process_arguments.c same.c \
		LabelTable.c printDebug.c printError.c testLabelTable.c \
	    	-o testLabelTable

testGetNTokens: 	assembler.h \
	getToken.c \
	getNTokens.c \
	printDebug.c \
	printError.c \
	same.c \
    	testGetNTokens.c
	$(GCC) -g testGetNTokens.c getNTokens.c getToken.c \
	    printDebug.c printError.c same.c -o testGetNTokens

testPass1: 	assembler.h \
    	LabelTable.c \
    	process_arguments.c \
	getToken.c \
	getNTokens.c \
	pass1.c \
	printDebug.c \
	printError.c \
	same.c \
	testPass1.c
	$(GCC) -g LabelTable.c process_arguments.c \
	    getNTokens.c getToken.c pass1.c \
	    printDebug.c printError.c same.c testPass1.c -o testPass1

assembler: 	assembler.h \
    	LabelTable.c \
    	process_arguments.c \
	getToken.c \
	getNTokens.c \
	pass1.c \
	pass2.c \
	printDebug.c \
	printError.c \
	same.c \
	assembler.c
	$(GCC) -g LabelTable.c process_arguments.c \
	    getNTokens.c getToken.c pass1.c pass2.c \
	    printDebug.c printError.c same.c assembler.c -o assembler

assembler.h: LabelTable.h getToken.h printFuncs.h process_arguments.h same.h
	touch assembler.h

clean: 
	rm -rf testLabelTable testGetNTokens testPass1 assembler
