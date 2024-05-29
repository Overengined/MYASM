# The MYASM instruction set
<center><img src="MYASM.png" alt="drawing" width="200"/>  

*MYASM : your ASM*
</center>  

### How to read
all entries will contain the name fo the function followed by its code representation and information on it's arguments and level, like " Foo `FOO <arg1> <arg2>` (1) ". The correct way to read it is "I am looking at instruction Foo, a level 1 instruction, which I'll write as FOO and in the next memory cell I'll write the first argument, then in the next one the second argument" etc...

## special instructions
### first instruction : `disk size` (0)
MYASM being a language working on a virtual disk, all MYASM programs need to specify in their first instrution the size of vdisk they want to have at their disposal. typically, a value of 10000 should be more than enough while still being supported by most computers. since this first instruction is mandoatory, there is no prefix mechanic, the size is the only thing to write.
#### example 
````
10000

<rest of the program>
````
##### note
It is considered good practice to leave a blank line between the `disk size` instruction and the actual program.

## instruction set
##### note :
all MYASM instructions are keywords that live alone in their cell. no other content should ever be present with a keyword inside of a cell.

### Flag `FLAG <name>` (0)
Probably one of the most important instruction in myasm : it allows you to create a flag at the location of the instruction. See it as some kind of exit portal that works hand in hand with it's brother `Goto`

### Goto `GOTO <name>` (1)
Jumps to a flag of name given in parameter.

### Write `WRIT <value> <adress>` (1)
Write a specified numerical data at a specified adress. Can be used with an operator as data.

### Read `READ <adress>` (2)
Returns the value of a specific memory cell. Can be used in an operator. 

### If `IFTH <value|adress> <logic> <value|adress> <flag>` (1)
Jumps to a specific flag if the logic evaluation is True. See [Logic](#logic)

### Print `DSPL <value|adress>` (1)
Prints to the console the value at a specific adress.

### End of program `ENDP` (1)
Immediately stops the program

### Add `OADD <value|adress> <value|adress> <adress>` (1)
writes the sum of two values at a specific adress.

### Logic
These are the logic operators supported by MYASM

#### Greater than `ISGT`
Is true when the value before is greater than the value after

#### Equal `ISEQ`
Is true when the two values are equal.