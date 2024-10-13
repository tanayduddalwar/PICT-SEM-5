#include <bits/stdc++.h>
using namespace std;

// To store mnemonics of the opcodes
struct OPtab
{
    string opcode;   // Opcode instruction
    string mclass;   // Class of the opcode (IS, AD, DL)
    string mnemonic; // Mnemonic code of the opcode
};

// Hard-coding the class and mnemonic for respective opcode
struct OPtab optab[18] = {
    {"STOP",   "IS", "00"},
    {"ADD",    "IS", "01"},
    {"SUB",    "IS", "02"},
    {"MULT",   "IS", "03"},
    {"MOVER",  "IS", "04"},
    {"MOVEM",  "IS", "05"},
    {"COMP",   "IS", "06"},
    {"BC",     "IS", "07"},
    {"DIV",    "IS", "08"},
    {"READ",   "IS", "09"},
    {"PRINT",  "IS", "10"},
    {"START",  "AD", "01"},
    {"END",    "AD", "02"},
    {"ORIGIN", "AD", "03"},
    {"EQU",    "AD", "04"},
    {"LTORG",  "AD", "05"},
    {"DC",     "DL", "01"},
    {"DS",     "DL", "02"}
};

// Function to fetch the opcode entry
int getOP(string s)
{
    for(int i = 0; i < 18; ++i)
    {
        if(optab[i].opcode == s)
            return i;
    }
    return -1;
}

// Function to fetch the register code
int getRegID(string s)
{
    if(s == "AREG") return 1;
    else if(s == "BREG") return 2;
    else if(s == "CREG") return 3;
    else if(s == "DREG") return 4;
    else return (-1);
}

// Function to fetch conditional code
int getConditionCode(string s)
{
    if(s == "LT") return 1;
    else if(s == "LE") return 2;
    else if(s == "EQ") return 3;
    else if(s == "GT") return 4;
    else if(s == "GE") return 5;
    else if(s == "ANY") return 6;
    else return (-1);
}

// To store Symbol Table output
struct symTable
{
    int no;      // Symbol number
    string sname; // Symbol name
    string addr; // Address of the symbol
};

struct symTable ST[10];

// Function to check presence of a particular 'symbol'
bool presentST(string s)
{
    for(int i = 0; i < 10; ++i)
    {
        if(ST[i].sname == s)
            return true;
    }
    return false;
}

// Function to fetch the symbol entry
int getSymID(string s)
{
    for(int i = 0; i < 10; ++i)
    {
        if(ST[i].sname == s)
            return i;
    }
    return (-1);
}

// To store Literal Table output
struct litTable
{
    int no;      // Literal number
    string lname; // Literal name
    string addr; // Address of the literal
};

struct litTable LT[10];

// Function to check presence of a particular 'literal'
bool presentLT(string s)
{
    for(int i = 0; i < 10; ++i)
    {
        if(LT[i].lname == s)
            return true;
    }
    return false;
}

// Function to fetch the literal entry
int getLitID(string s)
{
    for(int i = 0; i < 10; ++i)
    {
        if(LT[i].lname == s)
            return i;
    }
    return (-1);
}

// To store Pool Table output
struct poolTable
{
    int no;   // Pool Table number
    string lno; // Literal number in pool table
};

struct poolTable PT[10];

int main()
{
    ifstream fin;
    
    fin.open("input.txt");

    // Open output files
    ofstream ic, st, lt, pt;
    const char *path1 = "ic.txt"; 
    const char *path2 = "symtable.txt";
    const char *path3 = "littable.txt";
    const char *path4 = "pooltable.txt"; // File for pool table
    ic.open(path1); st.open(path2); lt.open(path3); pt.open(path4); // Open file for pool table

    string label, opcode, op1, op2;
    int scnt = 0, lcnt = 0, nlcnt = 0, pcnt = 0, LC = 0;

    cout << "\n -- ASSEMBLER PASS-1 OUTPUT --" << endl;
    cout << "\n <LABEL\tOPCODE\tOP1\tOP2\tLC\tINTERMEDIATE CODE>" << endl;

    // Process each line of the input file
    while(!fin.eof())
    {
        fin >> label >> opcode >> op1 >> op2; 
        int id; 
        string IC, lc; 

        id = getOP(opcode); 
        IC = "(" + optab[id].mclass + "," + optab[id].mnemonic + ") ";

        // Handle START opcode
        if(opcode == "START")
        {
            lc = "---";
            if(op1 != "NAN")
            {
                LC = stoi(op1);
                IC += "(C," + op1 + ")  NAN";
            }
        }

        // Handle EQU opcode
        if(opcode == "EQU")
        {
            lc = "---";
            IC += " NAN     NAN";
            if(presentST(label))
            {
                ST[getSymID(label)].addr = ST[getSymID(op1)].addr;
            }
            else
            {
                ST[scnt].no = scnt + 1;
                ST[scnt].sname = label;
                ST[scnt].addr = ST[getSymID(op1)].addr;
                scnt++;
            }
        }

        // Handle label definition
        else if(label != "NAN")
        {
            if(presentST(label))
            {
                ST[getSymID(label)].addr = to_string(LC);
            }
            else
            {
                ST[scnt].no = scnt + 1;
                ST[scnt].sname = label;
                ST[scnt].addr = to_string(LC);
                scnt++;
            }
        }

        // Handle ORIGIN opcode
        if(opcode == "ORIGIN")
        {
            string token1, token2; 
            char op;
            stringstream ss(op1);
            size_t found = op1.find('+');
            if(found != string::npos)
                op = '+';
            else
                op = '-';
            getline(ss, token1, op); 
            getline(ss, token2, op);
            lc = "---";
            if(op == '+')
            {
                LC = stoi(ST[getSymID(token1)].addr) + stoi(token2);
                IC += "(S,0" + to_string(ST[getSymID(token1)].no) + ")+" + token2 + " NAN";
            }
            else
            {
                LC = stoi(ST[getSymID(token1)].addr) - stoi(token2);
                IC += "(S,0" + to_string(ST[getSymID(token1)].no) + ")-" + token2 + " NAN";
            }
        }

        // Handle LTORG opcode
        if(opcode == "LTORG")
        {
            cout << "  " << label << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t";
            for(int i = lcnt - nlcnt; i < lcnt; ++i)
            {
                lc = to_string(LC);
                IC = "(DL,01) (C,";
                string c(1, LT[i].lname[2]);
                IC += c + ")    NAN";
                LT[i].addr = to_string(LC);
                LC++;
                if(i < lcnt - 1)
                    cout << lc << "\t" << IC << "\n\t\t\t\t";
                else
                    cout << lc << "\t" << IC << endl;
                ic << lc << "\t" << IC << endl;
            }
            
            PT[pcnt].lno = "#" + to_string(LT[lcnt - nlcnt].no); 
            PT[pcnt].no = pcnt + 1; 
            pcnt++;
            nlcnt = 0;
            continue;
        }

        // Handle END opcode
        if(opcode == "END")
        {
            lc = "---";
            IC += " NAN     NAN";
            cout << "  " << label << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t" << lc << "\t" << IC << endl;
            ic << lc << "\t" << IC << endl;
            if(nlcnt)
            {
                for(int i = lcnt - nlcnt; i < lcnt; ++i)
                {
                    lc = to_string(LC);
                    IC = "(DL,01) (C,";
                    string c(1, LT[i].lname[2]);
                    IC += c + ")    NAN";
                    LT[i].addr = to_string(LC);
                    LC++;
                    cout << "\t\t\t\t" << lc << "\t" << IC << endl;
                    ic << lc << "\t" << IC << endl;
                }
                
                PT[pcnt].lno = "#" + to_string(LT[lcnt - nlcnt].no); 
                PT[pcnt].no = pcnt + 1; 
                pcnt++;
            }
            break;
        }

        // Handle DC and DS opcodes
        if(opcode == "DC" || opcode == "DS")
        {
            lc = to_string(LC);
            if(opcode == "DS")
            {
                IC += "(C," + op1 + ")    NAN";
                LC += stoi(op1);
            }
            else
            {
                string c(1, op1[1]);
                IC += "(C," + c + ")";
                LC++;
            }
        }

        // Handle other opcodes
        if(opcode != "START" && opcode != "END" && opcode != "ORIGIN" && opcode != "EQU" && opcode != "LTORG" && opcode != "DC" && opcode != "DS")
        {
            if(op2 == "NAN")
            {
                if(op1 == "NAN")
                {
                    lc = to_string(LC);
                    LC++;
                    IC += " NAN     NAN";
                }
                else
                {
                    if(presentST(op1))
                    {
                        IC += "(S,0" + to_string(ST[getSymID(op1)].no) + ")";
                        lc = to_string(LC);
                        LC++;
                    }
                    else
                    {
                        ST[scnt].no = scnt + 1;
                        ST[scnt].sname = op1;
                        scnt++;
                        IC += "(S,0" + to_string(ST[getSymID(op1)].no) + ")";
                        lc = to_string(LC);
                        LC++;
                    }
                }
            }
            else
            {
                if(opcode == "BC")
                    IC += "(" + to_string(getConditionCode(op1)) + ")     ";
                else
                    IC += "(" + to_string(getRegID(op1)) + ")     ";

                if(op2[0] == '=') 
                {
                    LT[lcnt].no = lcnt + 1;
                    LT[lcnt].lname = op2;
                    lcnt++; 
                    nlcnt++;
                    IC += "(L,0" + to_string(LT[getLitID(op2)].no) + ")";
                }
                else 
                {
                    if(presentST(op2))
                    {
                        IC += "(S,0" + to_string(ST[getSymID(op2)].no) + ")";
                    }
                    else
                    {
                        ST[scnt].no = scnt + 1;
                        ST[scnt].sname = op2;
                        scnt++;
                        IC += "(S,0" + to_string(ST[getSymID(op2)].no) + ")";
                    }
                }
                lc = to_string(LC);
                LC++;
            }
        }

        // Console output
        cout << "  " << label << "\t" << opcode << "\t" << op1 << "\t" << op2 << "\t" << lc << "\t" << IC << endl;
        ic << lc << "\t" << IC << endl;
    }

    // Output Symbol Table
    cout << "\n----------------------------------------------------------------" << endl;
    cout << " -- SYMBOL TABLE --" << endl;
    cout << "\n <NO.\tSYMBOL\tADDRESS>" << endl;
    for(int i = 0; i < scnt; ++i)
    {
        cout << "  " << ST[i].no << "\t " << ST[i].sname << "\t  " << ST[i].addr << endl;
        st << ST[i].no << "\t " << ST[i].sname << "\t  " << ST[i].addr << endl;
    }

    // Output Literal Table
    cout << "\n----------------------------------------------------------------" << endl;
    cout << " -- LITERAL TABLE --" << endl;
    cout << "\n <NO.\tLITERAL\tADDRESS>" << endl;
    if(lcnt == 0){
        cout << "\n No literals in the source code " << endl;
        cout << endl;
    }
    for(int i = 0; i < lcnt; ++i)
    {
        cout << "  " << LT[i].no << "\t " << LT[i].lname << "\t  " << LT[i].addr << endl;
        lt << LT[i].no << "\t " << LT[i].lname << "\t  " << LT[i].addr << endl;
    }

    // Output Pool Table
    cout << "\n----------------------------------------------------------------" << endl;
    cout << " -- POOL TABLE --" << endl;
    cout << "\n <NO.\tLITERAL_NO.>" << endl;
    if(pcnt == 0){
        cout << "\n No literals in the source code " << endl;
        cout << endl;
    }
    for(int i = 0; i < pcnt; ++i)
    {
        cout << "  " << PT[i].no << "\t   " << PT[i].lno << endl;
        pt << PT[i].no << "\t   " << PT[i].lno << endl; // Write to pool table file
    }

    return 0;
}
