from mnuemonics import AD,DL,IS,OPCODE
from pass1 import symtab,littab
f=open("inter.txt")
codes=[]
for words in f:
    if AD in words:
        continue
    else:
        lines=words.split()
        codes.push_back(lines)
f1=open("pass.txt")
def declarative(line):
    if "(DL,01)" in line:
        words=line[2]
        words=words.zfill(3)
        f1.write("+ 00 00"+words+"\n")
    else:
        words=line[2]
        while(words!=0):
            f1.write("+ -- -- --- ")    
            words=words-1
for lines in codes:
    if("(DL,01)" in lines or "(DL,02)" in lines):
        declarative(lines)
    else:
        for words in lines:
            if words in OPCODE:
                f1.write(OPCODE[words])
            elif words in symtab:
                f1.write(symtab[words])
            elif words in littab:
                f1.write(littab[words])
            else:
                f1.write(words) 
        f1.write("\n")               


        
           