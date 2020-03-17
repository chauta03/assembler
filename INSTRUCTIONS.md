# Assembler Programming Project

See the
[Assembler PP assignment](www.cs.kzoo.edu/cs230/Projects/AssemblerProj.html)
for the instructions for this assignment, coding tips, links to helpful
documents, and submission requirements.

The Assembler project builds upon the LabelTable functions you have already
written.  Before you start this project, make sure to first fix any errors
or make other changes that were suggested in the grading feedback to
LabelTable.  Don't forget to test your changes!

The next thing to do is to copy the C source files and header files from your
LabelTable project into this repository.  For example,
    cd ../LabelTable        (or whatever the directory name is)
    cp *.c *.h ../Assembler  (or whatever the name should be)
    cp smallSampleTestfile.mips ../Assembler

If you also copy the Makefile over, it will overwrite the Assembler project
Makefile that is already in this repository, but there is a copy in
AssemblerMakefile.

Once you have copied the appropriate LabelTable files to this repository,
compile and test them again, using `make testLabelTable`.  Then add,
commit, and push them to Kit as a starting point for the Assembler.

You should also test your LabelTable code with the `testPass1` program,
especially if didn't already do that before submitting your LabelTable
project (`make testPass1` followed by `./testPass1
smallSampleTestfile.mips`).  The main source file for this test program,
is a good template for the source file you will write for the Assembler
(you could start by copying `testPass1.c`).

The Makefile provided in this repository also has rules for a second test
program.  If you're interested, you can compile and run the test driver
that was written to test the getNTokens function provided to you: `make
testGetNTokens` followed by `./testGetNTokens`.

Note that the the `all` target in this repository assumes you are compiling
the Assembler project, and assumes that you have a file names
`assembler.c`.  If that's not the case, you will have to edit the Makefile.
You will also have to edit the Makefile whenever you create a new source
file for the project.

Following agile development principles, repeatedly Edit, Test, and Add/Commit
until the program is done. You can `git push` to Kit as often as you want.
(See the [Working with Git Repositories in
Kit](http://www.cs.kzoo.edu/CSShared/HelpFiles/Kit/RepositoryAssignments.md)
document for more information about writing a program within a Git
repository.)

Don't forget to provide a README.md file with external documentation about
your program, as described in the 
[Assembler PP assignment](www.cs.kzoo.edu/cs230/Projects/AssemblerProj.html).

When you are ready to submit your work, click on the "Turn In"
button. (You should still be able to push further changes to Kit
after turning an assignment in if you need to.)

