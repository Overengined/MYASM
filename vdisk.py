class vdisk():
    def __init__(self, size : int) -> None:
        # print("creating vdisk of size", size)
        self.disk = [0 for i in range(size)]

    def __repr__(self) -> str:
        print("reading ...")
        output = []
        for cell in self.disk:
            if cell != 0:
                output.append(cell)
        return str(output)
    
    def read(self,adress : int)-> int|bool:
        """
        accesses the value of a certain memory adress.
        return False if failed.
        """
        try :
            return self.disk[adress]
        except :
            return False
    
    def write(self, adress : int, content : str) -> bool:
        """
        writes a specific content at a specific memory adress.
        returns True if success, False if failed
        """
        try :
            self.disk[adress] = content
            return True
        except :
            print("[ERROR]: could not write", str(content)," to adress", str(adress))
            return False
        
    def load(self, instructions : list):
        """
        loads instructions form a program inot memory at a rate of one 
        datablock per memory cell.
        """
        adress = 1
        for instruction in instructions:
            self.write(adress, instruction)
            adress += 1

    def size(self):
        return len(self.disk)
        
