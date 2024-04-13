# MYASM internal working
## The 0 memory cell
The first memory cell of a virtual disk will always be the current adress ofthe biggest bock the program is working on. E.g : if a `IFTH` is being worked on cell 436, cell 0 takes value 436, even if inside the `IFTH` there is a `READ`, the value will stay the same.

## The instructions levels
Currently there are three instruction levels in MYASM
- Level 0 instructions are meta-instructions (often passive) that don't directly interact with the program, but are still necessary to it's execution. *E.G* flags, which won't trigger any type of logic, but lead to a program breakage if removed.
- Level 1 instructions are the ones who will actually trigger some sort of logic, and that can be used on their own , with or without level 2 instructions.
- Level 2 instructions are instructions that can't be used as standalone, but instead work while being used inside a level 1 instruction, *e.g* `READ`
