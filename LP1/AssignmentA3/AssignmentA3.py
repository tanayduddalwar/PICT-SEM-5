import re as regex
import itertools
import json
import os

# Clear the console
os.system('cls' if os.name == 'nt' else 'clear')

# Function to get key from a dictionary based on value
def get_key(val: str, dict: dict) -> any:
    for key, value in dict.items():
        if val == value:
            return key

# Ensure the output directory exists
output_dir = 'PICT-SEM-5/LP1/AssignmentA3/output/'
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

# Creating the MDT file
with open(f"{output_dir}/mdt.asm", 'w') as file:
    pass

# Input File(s)
inputFile = open(f'{output_dir}/program.asm', 'r')

# Output File(s)
mdtFile = open(f"{output_dir}/mdt.asm", 'a')

# Regex pattern to split on occurrence of one or more spaces
pattern = r'\s+'

# Flags
mSign = False
mDef = False

# Tables
mnt = {}
pntab = {}
kpdtab = {}

# Storage variables
macroName = ""
kpdtabIndex = 1
kpdtabLoc = 1
mntIndex = 1
mdtLoc = 1

# Loop through lines in file
for line in inputFile:
    # Skip blank lines and remove beginning and trailing whitespace(s)
    if line == '\n': continue
    line = line.strip()

    # Split the line into words
    cmd = regex.split(pattern, line.rstrip())

    # When 'MACRO' is encountered, set the macro signature flag
    if len(cmd) == 1 and cmd[0] == 'MACRO':
        mSign = True
        continue

    # If macro definition has been encountered, process its right next line
    if mSign:
        macroName = cmd.pop(0)
        pntab[macroName] = {}
        paramCnt = 0
        
        pp = 0
        kp = 0
        
        # Now, cmd contains the list of all the parameters
        for parameter in cmd:
            if ',' in parameter:
                parameter = parameter.replace(',', '')

            if '&' in parameter and '=' not in parameter:
                paramCnt += 1
                pp += 1
                paramName = parameter[1::]
                pntab[macroName][paramCnt] = paramName
                
            elif '&' in parameter and '=' in parameter:
                paramCnt += 1

                if kp == 0:
                    kpdtabLoc = kpdtabIndex

                kp += 1
                
                # Get the index of the '=' sign
                eqIndex = parameter.index('=')
                paramName = parameter[1:eqIndex:]
                paramDefValue = parameter[eqIndex + 1::]
                pntab[macroName][paramCnt] = paramName
                
                kpdtab[kpdtabIndex] = {
                    'index': kpdtabIndex, 
                    'name': paramName, 
                    'value': paramDefValue if paramDefValue else '---',
                }
                
                kpdtabIndex += 1
                
        mSign = False
        mDef = True
        mnt[mntIndex] = {
            'index': mntIndex,
            'name': macroName,
            'pp': pp,
            'kp': kp,
            'mdtp': mdtLoc,
            'kpdtp': kpdtabLoc if kp else '---',
        }
        mntIndex += 1
        continue
    
    if mDef:
        mdtLoc += 1
        callLine = ""
        
        for command in cmd:
            if ',' in command:
                command = command.replace(',', '')
            if '&' in command:
                replParamValue = f'(P,{get_key(command[1::], pntab[macroName])})'
                callLine += replParamValue + " "
            else:
                callLine += command + " "    
                
        mdtFile.write(callLine + '\n')
        continue
    
    if len(cmd) == 1 and cmd[0] == 'MEND':
        mdtLoc += 1
        mDef = False
        mdtFile.write('MEND\n')
        continue

# Write tables to JSON files
with open(f"{output_dir}/mnt.json", 'w') as json_file:
    json.dump(mnt, json_file, indent=4)

with open(f"{output_dir}/pntab.json", 'w') as json_file:
    json.dump(pntab, json_file, indent=4)

with open(f"{output_dir}/kpdtab.json", 'w') as json_file:
    json.dump(kpdtab, json_file, indent=4)

# Close all opened files
inputFile.close()
mdtFile.close()
