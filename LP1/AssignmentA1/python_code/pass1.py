from mnuemonics import AD,IS,DL,OPCODE
symtab={}
littab={}
codes=[]
f=open("input.txt")
for words in f:
    words=words.replace(","," ")
    line=words.split()
    codes.append(line)
f.close()
lc=0
def assembler(words,line):
    global lc
    if(words=="START"):
        try:
            lc=int(line[1])
        except(IndexError,ValueError):
            lc=0
    elif(words=="END"):
        for  i in littab:
            if littab[i]=='notset':
                littab[i]=str(lc)
                lc=lc+1
    elif(words=="LTORG"):
        for i in littab:
            if(littab[i]=='notset'):
                littab[i]=str(lc)   
                lc=lc+1
    elif(words=="EQU"):
        symtab[line[0]]=symtab[line[2]] 
    elif(words=="ORIGIN"):
        if(len(line)==4 and line[2]=='+'):
            label=line[1]
            val=line[3]
            if label in symtab:
                lc=int(symtab[label])
            else:
                print("Symbol doesn't exist in the symbol table")
            try:
                lc=lc+int(val)
            except ValueError:
                print("The val is not an integer value") 
def declarative(words,line):
    global lc
    for i in line:
        if(i.isdigit()==False and i not in DL):
        
            symtab[i]=str(lc)
    if(words=="DS"):
        if(line[2].isdigit()):
            lc=lc+int(line[2])
f1=open("inter.txt","w")
for lines in codes:
    for words in lines:
        if(words in AD):
            assembler(words,lines)
            f1.write("\t"+AD[words]+" ")
        elif(words in DL):
            lc=lc+1
            declarative(words,lines)
            f1.write("\t"+DL[words]+" ")
        elif (words in IS):
            lc=lc+1
            f1.write("\t"+IS[words]+" ")    
        elif("="in words):
            littab[words]='notset'
            f1.write("\t"+words+" ")    
        elif (words.isdigit() and words in ['+']==False):
            symtab[words]='notset'
            f1.write("\t"+words+" ")
        else:
            f1.write("\t"+words+" ")
    f1.write("\n")
print(symtab)
print(littab)

