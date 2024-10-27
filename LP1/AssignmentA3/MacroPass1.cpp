#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    // Open input and output files
    ifstream inputFile("macro_input.asm");
    ofstream mntFile("mnt.txt");
    ofstream mdtFile("mdt.txt");
    ofstream kpdtFile("kpdt.txt");
    ofstream pntFile("pntab.txt");
    ofstream irFile("intermediate.txt");

    // Check if the input file opened successfully
    if (!inputFile.is_open())
    {
        cerr << "Error: Could not open macro_input.asm" << endl;
        return 1;
    }

    unordered_map<string, int> pntab;
    string line, Macroname;
    int mdtp = 1, kpdtp = 0, paramNo = 1, pp = 0, kp = 0, flag = 0;

    while (getline(inputFile, line))
    {
        istringstream iss(line);
        vector<string> parts;
        string part;

        // Split the line into parts
        while (iss >> part)
        {
            parts.push_back(part);
        }

        // Skip empty lines
        if (parts.empty())
            continue;

        // Handle MACRO definition
        if (parts[0] == "MACRO")
        {
            flag = 1; // Start processing a macro
            if (!getline(inputFile, line))
                break;

            istringstream macroIss(line);
            parts.clear();
            while (macroIss >> part)
            {
                parts.push_back(part);
            }

            Macroname = parts[0]; // Save macro name

            // Write to MNT (Macro Name Table)
            mntFile << Macroname << "\t" << pp << "\t" << kp << "\t"
                    << mdtp << "\t" << (kp == 0 ? kpdtp : (kpdtp + 1)) << "\n";

            // Process macro parameters
            for (size_t i = 1; i < parts.size(); ++i)
            {
                parts[i].erase(remove(parts[i].begin(), parts[i].end(), '&'), parts[i].end());
                parts[i].erase(remove(parts[i].begin(), parts[i].end(), ','), parts[i].end());

                if (parts[i].find('=') != string::npos)
                {
                    ++kp;
                    size_t pos = parts[i].find('=');
                    string keyParam = parts[i].substr(0, pos);
                    string valueParam = (pos + 1 < parts[i].size()) ? parts[i].substr(pos + 1) : "-";
                    pntab[keyParam] = paramNo++;
                    kpdtFile << keyParam << "\t" << valueParam << "\n";
                }
                else
                {
                    pntab[parts[i]] = paramNo++;
                    pp++;
                }
            }

            kpdtp += kp; // Update kpdtp after processing parameters
        }
        else if (parts[0] == "MEND")
        {
            // Write MEND to MDT
            mdtFile << line << "\n";
            flag = kp = pp = 0;
            mdtp++;
            paramNo = 1;

            // Write to PNT (Parameter Name Table)
            pntFile << Macroname << ":\t";
            //pnfile<<macroname<<"\t";
            auto it=pntab.begin();
            while(it!=pntab.end()){
                pntFile<<it->first<<"\t";
                it++;
            }
            pntFile<<"\n";
            pntab.clear();// Clear PNT for the next macro
        }
        else if (flag == 1)
        {
            // Write macro body to MDT
            for (const string &token : parts)
            {
                if (token.find('&') != string::npos)
                {
                    string param = token;
                    param.erase(remove(param.begin(), param.end(), '&'), param.end());
                    param.erase(remove(param.begin(), param.end(), ','), param.end());
                    mdtFile << "(P," << pntab[param] << ")\t";
                }
                else
                {
                    mdtFile << token << "\t";
                }
            }
            mdtFile << "\n";
            mdtp++; // Increment MDT pointer
        }
        else
        {
            // Write non-macro lines to intermediate file
            irFile << line << "\n";
        }
    }

    // Close all files
    inputFile.close();
    mntFile.close();
    mdtFile.close();
    kpdtFile.close();
    pntFile.close();
    irFile.close();

    cout << "Macro Pass1 Processing done. :)" << endl;
    return 0;
}
/*
1.  split the lines into words and store it in parts vector
2.  if parts is empty then continue
3. if parts[0]==MACRO then clear the parts first and then store again in parts the splitted words  amd write macroname and pointers in mnt then chekc got & and , if present remove them form input then chekc for = sign if present add this entry in pntab and write in kpdtab increase kp pointer
4. if parts[0]=MEND then write to mdt file and reinitialize all variables to default and then write to pp file and clear the pntab
5. else if(flag==1) then run loop over parts and find & and , if present remove them  else make entry in mdttable increase the mdp pointer
6. Close all the files
*/
