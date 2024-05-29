# MYASM (c) Overengined - 2024

import vdisk as vdk
import sys

# LOADING THE PROGRAM #
file = sys.argv[1]

# defining verbosity level
try :
    verbosity = sys.argv[2]
except :
    verbosity = ""

# open the myasm file
filedata = open(file, "r").read()

# remove all duplicate whitespace characters
filedata = " ".join(filedata.split())
filedata = filedata.split(" ")

if verbosity == "v":
    print(filedata)

#create a vdisk of size specified as first instruction
if verbosity == "v":
    print("read desired disksize :", filedata[0])
disk = vdk.vdisk(int(filedata[0]))
#load data into it
disk.load(filedata)

if verbosity == "v":
    print("finished loading, executing now")

#######################

# MYASM INTERPRETER STARTS HERE #
end = False
disk.write(0,"1")
jump = False

while end == False:
    # these two lines are absurdly important
    current_cell = int(disk.read(0))
    instruction = disk.read(int(disk.read(0)))

    if instruction == "ENDP":
        # treatment of END instruction
        end = True

    if instruction == "GOTO":
        # GOTO instruction
        target = disk.read(current_cell + 1)
        for adress in range(disk.size()):
            #searches for all FLAG instructions
            if disk.read(adress) == "FLAG":
                # if the instruction is FLAG, is the next one the target name ?
                if disk.read(adress + 1)== target:
                    # set current instruction cell to FLAG + 2
                    disk.write(0,str(adress+2))
                    if verbosity == "v":
                        print("JUMPING TO FLAG", target)
                    break
    
    if instruction == "WRIT":
        # WRIT instruction
        if verbosity =="v":
            print("writing", disk.read(current_cell + 1), "at", disk.read(current_cell + 2))

        disk.write(
                    # adress specified in second argument (since function takes
                    # an int as an adress, we cast the str value that is read)
                    int(disk.read(current_cell + 2)),
                    # value specified in first argument, no need to cast it
                    disk.read(current_cell + 1)
                   )
        
        if verbosity == "v":
            print(disk)
    
    if instruction == "DSPL":
        # DSPL instructon
        if verbosity == "v":
            print("attempting DSPL instruction")

        # first case : read adress
        if disk.read(current_cell+1) == "READ":
            print(disk.read(int(disk.read(current_cell + 2))))
        # second case : simple value
        else :
            print(disk.read(current_cell + 1))

    # FIXME : you do 
    # operand = disk.read(current_cell+n), but it wont work because you are
    # reading the value of the draess,not the actual data stored AT tge adress
    # replace asap where needed with 
    # operand = disk.read(int(disk.read(current_cell+n)))
    
    if instruction == "OADD":
        # OADD instruction
        # due to the complexity of this instruction, this behaves kinda like a 
        # FSM, but cursed. Thing is we want to adapt what we will read 
        # according to what we are reading at the moment.

        # case OADD <value>
        if disk.read(current_cell + 1) != "READ":
            left_operand = int(disk.read(current_cell + 1))
            
            # case OADD <value> <value> <adress>
            if disk.read(current_cell + 2) != "READ":
                right_operand = int(disk.read(current_cell + 2))
                # read the adress and write at it
                disk.write(
                    int(disk.read(current_cell+3)),
                    left_operand + right_operand
                )

            # case OADD <value> READ <adress> <adress>
            else :
                right_operand = int(disk.read(int(disk.read(current_cell + 3))))
                disk.write(
                    int(disk.read(current_cell+4)),
                    left_operand + right_operand
                )

        else :
            # case OADD READ <adress>
            left_operand = int(disk.read(int(disk.read(current_cell + 2))))
            
            # case OADD READ <adress> <value> <adress>
            if disk.read(current_cell + 3) != "READ":
                right_operand = int(disk.read(current_cell + 3))
                # writing to adress we read
                disk.write(
                    int(disk.read(current_cell+4)),
                    left_operand + right_operand
                )

            # case OADD READ <adress> READ <adress> <adress>
            else :
                left_operand = int(disk.read(int(disk.read(current_cell + 4))))
                # writing to adress 
                disk.write(
                    int(disk.read(current_cell+5)),
                    left_operand + right_operand
                )

    if instruction == "IFTH":
        # IFTH instruction
        # this is to big to be managed in one step, so we work with a two-step
        # design : first we gather all our arguments (like for OADD) then only 
        # we do the actual logic.
        # gathering arguments :

        # case IFTH <value>
        if disk.read(current_cell + 1) != "READ":
            left_operand = int(disk.read(current_cell + 1))
            
            # case IFTH <value> <logic> <value> <flag>
            if disk.read(current_cell + 3) != "READ":
                right_operand = int(disk.read(current_cell + 3))
                # read the logic operator
                logic = disk.read(current_cell +2)
                # read the flag
                flag = disk.read(current_cell + 4)


            # case IFTH <value> <logic> READ <adress> <flag>
            else :
                right_operand = int(disk.read(int(disk.read(current_cell + 4))))
                # read logic operator
                logic = disk.read(current_cell + 2)
                # read the flag
                flag = disk.read(current_cell + 5)


        else :
            # case IFTH READ <adress>
            left_operand = int(disk.read(int(disk.read(current_cell + 2))))
            if verbosity == "v":
                print("read from disk :",int(disk.read(current_cell + 2)), "| adress :", str(current_cell+2))


            # case IFTH READ <adress> <logic> <value> <adress>
            if disk.read(current_cell + 4) != "READ":
                right_operand = int(disk.read(current_cell + 4))
                if verbosity == "v":
                    print("read from disk :",int(disk.read(current_cell + 4)))
                # read logic operator
                logic = disk.read(current_cell + 3)
                # read flag
                flag = disk.read(current_cell + 5)

            # case IFTH READ <adress> <logic> READ <adress> <adress>
            else :
                right_operand = int(disk.read(int(disk.read(current_cell + 5))))
                # read logic
                logic = disk.read(current_cell + 3)
                # read flag 
                flag = disk.read(current_cell + 6)

            # logic:

            if logic == "ISGT":

                if verbosity == "v":
                    print("evaluating if", left_operand, ">", right_operand)

                if left_operand > right_operand:
                    for adress in range(disk.size()):
                        #searches for all FLAG instructions
                        if disk.read(adress) == "FLAG":
                            # if the instruction is FLAG, is the next one the 
                            # flag name ?
                            if disk.read(adress + 1)== flag:
                                # set current instruction cell to FLAG + 2
                                disk.write(0,str(adress+2))
                                # avoid increasing current cell by one
                                jump = True
                                if verbosity == "v":
                                    print("IFTH TRUE : JUMPING TO FLAG", flag)
                                    print("wrote", str(adress+2),"on disk, corresponding to", disk.read(adress+2))
                                break

            # oh no duplicate code !!!  
            # actually don't care, because whenever we want to tweak the logic 
            # of keywords like these, it's easier and cleaner to do it on a 
            # per keyword basis instead of creating cases in a big function.              
            if logic == "ISEQ":
                if left_operand == right_operand:
                    for adress in range(disk.size()):
                        #searches for all FLAG instructions
                        if disk.read(adress) == "FLAG":
                            # if the instruction is FLAG, is the next one the 
                            # flag name ?
                            if disk.read(adress + 1)== flag:
                                # set current instruction cell to FLAG + 2
                                disk.write(0,str(adress+2))
                                # avoid increasing current cell by one
                                jump = True
                                if verbosity == "v":
                                    print("IFTH TRUE : JUMPING TO FLAG", flag)
                                    print("wrote", str(adress+2),"on disk, corresponding to", disk.read(adress+2))
                                break
    
    if jump == False:
        disk.write(0, 
                str( int( disk.read(0) ) +1 )
                )
    jump = False
        





