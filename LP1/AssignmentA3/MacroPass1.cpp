#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Open input and output files
    ifstream inputFile("macro_input.asm");
    ofstream mntFile("mnt.txt");
    ofstream mdtFile("mdt.txt");
    ofstream kpdtFile("kpdt.txt");
    ofstream pntFile("pntab.txt");
    ofstream irFile("intermediate.txt");

    // Check if the input file opened successfully
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open macro_input.asm" << endl;
        return 1;
    }

    unordered_map<string, int> pntab;
    string line, Macroname;
    int mdtp = 1, kpdtp = 0, paramNo = 1, pp = 0, kp = 0, flag = 0;

    while (getline(inputFile, line)) {
        istringstream iss(line);
        vector<string> parts;
        string part;

        // Split the line into parts
        while (iss >> part) {
            parts.push_back(part);
        }

        // Skip empty lines
        if (parts.empty()) continue;

        // Handle MACRO definition
        if (parts[0] == "MACRO") {
            flag = 1; // Start processing a macro
            pp = 0;   // Reset pp for each new macro
            kp = 0;   // Reset kp for each new macro

            if (!getline(inputFile, line)) break;

            istringstream macroIss(line);
            parts.clear();
            while (macroIss >> part) {
                parts.push_back(part);
            }

            Macroname = parts[0]; // Save macro name            

            // Process macro parameters
            for (size_t i = 1; i < parts.size(); ++i) {
                parts[i].erase(remove(parts[i].begin(), parts[i].end(), '&'), parts[i].end());
                parts[i].erase(remove(parts[i].begin(), parts[i].end(), ','), parts[i].end());

                if (parts[i].find('=') != string::npos) {
                    ++kp;
                    size_t pos = parts[i].find('=');
                    string keyParam = parts[i].substr(0, pos);
                    string valueParam = (pos + 1 < parts[i].size()) ? parts[i].substr(pos + 1) : "-";
                    pntab[keyParam] = paramNo++;
                    kpdtFile << keyParam << "\t" << valueParam << "\n";
                } else {
                    pntab[parts[i]] = paramNo++;
                    pp++;
                }
            }

            kpdtp += kp; // Update kpdtp after processing parameters

            // Write to MNT (Macro Name Table)
            mntFile << Macroname << "\t" << pp << "\t" << kp << "\t"
                    << mdtp << "\t" << (kp == 0 ? kpdtp : (kpdtp - kp + 1)) << "\n";
        }
        else if (parts[0] == "MEND") {
            // Write MEND to MDT
            mdtFile << line << "\n";
            mdtp++; // Increment MDT pointer after adding MEND

            // Write to PNT (Parameter Name Table) for the current macro
            pntFile << Macroname << ":\t";
            for (const auto &entry : pntab) {
                pntFile << entry.first << "\t";
            }
            pntFile << "\n";

            // Clear parameter name table and reset variables for the next macro
            pntab.clear();
            pp = 0;
            kp = 0;
            paramNo = 1;
            flag = 0; // Reset the flag indicating macro definition processing
        }
        else if (flag == 1) {
            // Write macro body to MDT
            for (const string &token : parts) {
                if (token.find('&') != string::npos) {
                    string param = token;
                    param.erase(remove(param.begin(), param.end(), '&'), param.end());
                    param.erase(remove(param.begin(), param.end(), ','), param.end());
                    mdtFile << "(P," << pntab[param] << ")\t";
                } else {
                    mdtFile << token << "\t";
                }
            }
            mdtFile << "\n";
            mdtp++; // Increment MDT pointer
        }
        else {
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
