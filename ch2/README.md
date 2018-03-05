# Chapter 2 Exercises OSCe9

Work on the exercises from Chapter 2 from the Operating System Concepts 9th Edition textbook for CSC4103 at LSU.

## cp.c

A program that implements a command line copy function.

### Compiling

This was compiled and tested in Ubuntu 16.04 LTS using gcc.

To compile
'''
gcc cp.c -o copy
'''

### Running

'''
./copy input_filename output_filename
'''

## simple.c

This program implements a kernel module for Linux systems that creates a linked list of 5 people's birthdays and outputs them to the kernel log buffer.

### Compiling

To compile, simply run the makefile.

'''
make
'''

The make command will produce several files.

### Running

To load the kernel module

'''
sudo insmod simple.ko
'''

To see the output from the kernel module

'''
dmesg
'''

When you are done, remove the kernel module

'''
sudo rmmod simple
'''

Finally, you may choose to clear the kernel log buffer at any time

'''
sudo dmesg -c
'''
