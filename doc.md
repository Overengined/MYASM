# MYASM internal working
## The 0 memory cell
The first memory cell of a virtual disk will always be the current adress of the biggest bock the program is working on. E.g : if a `IFTH` is being worked on cell 436, cell 0 takes value 436, even if inside the `IFTH` there is a `READ`, the value will stay the same.

## The instructions levels
Currently there are three instruction levels in MYASM
- Level 0 instructions are meta-instructions (often passive) that don't directly interact with the program, but are still necessary to it's execution. *E.G* flags, which won't trigger any type of logic, but lead to a program breakage if removed.
- Level 1 instructions are the ones who will actually trigger some sort of logic, and that can be used on their own , with or without level 2 instructions.
- Level 2 instructions are instructions that can't be used as standalone, but instead work while being used inside a level 1 instruction, *e.g* `READ`

## How `FLAG` works (and associated perks)
If during execution there is the need ot jump to a specific flag, the program will crawl through all the virtual disk each time no matter what until it finds the first falg named accordingly to its target. That lead to a pretty interesting side effect : since a flag is two data blocks (one `FLAG` and one `<adress>`)
, you could in theory, for some reasons that are yours, choose to rename on the fly a flag. Why ? I don't know. Maybe some weird algorith that can shift through functions like gears on a car ? 

## Little piece of knowledge regarding `WRIT`
So in this version the logic associated with the `WRIT` instruction makes so that in case of a failure to write to a specific adress, a program will go on. Same thing for the loading phase : if your program is too large, the excedentary instructions just won't be written anywhere. Might seem like a quirk at first, but if you think about it, it makes so that you can attempt write operations at absolutely garbage adresses and still have a code that somewhat works. Though I really am curious on how you're going to implement error management in a dumpsterfire like this.  
Sadly this doesn't apply to `READ`, since it is a level two instruction, if it fails, the whole thing will just crash. Your computer may self-combust.