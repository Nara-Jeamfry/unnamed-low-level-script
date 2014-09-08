fast-game-script
========================

New scripting language aimed to use host code and import host types, as to have very low transition cost and no lookup costs at all.

This project includes a Fast Game Script compiler to FGS ByteCode, and an interpreter of FGS ByteCode.

Both of these tools are included in an API header file; the intended use of Fast Game Script is
leaving all the work to the API, which checks for compilation and interpretation times (it will automatically
recompile and reload files that have been modified), handles file management and errors and allows 
access to all funcionality on Fast Game Script.

To compile: simply use the Makefile (will build all object files on .o and compile the test.c file.

A library creation for use with the gcc compiler on unix will be defined shortly.
