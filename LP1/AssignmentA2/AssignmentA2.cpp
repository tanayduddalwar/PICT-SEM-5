#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

// Function to safely convert string to integer
int safeStoi(const string &str)
{
    try
    {
        return stoi(str);
    }
    catch (const invalid_argument &e)
    {
        cerr << "Invalid argument: " << str << " cannot be converted to integer" << endl;
        return -1; // Return an invalid value
    }
    catch (const out_of_range &e)
    {
        cerr << "Out of range: " << str << " is out of integer range" << endl;
        return -1; // Return an invalid value
    }
}

int main()
{
    ifstream sin("symtable.txt");
    ifstream lin("littable.txt");
    ifstream fin("ic.txt");
    ofstream fout("machineCode.txt");

    // Check if files opened successfully
    if (!sin.is_open() || !lin.is_open() || !fin.is_open() || !fout.is_open())
    {
        cerr << "Error opening one or more files." << endl;
        return 1;
    }

    string line, word;
    vector<pair<string, int>> symtab;
    vector<pair<string, int>> littab;

    // Read symbol table
    while (getline(sin, line))
    {
        stringstream st(line);
        st >> word; // Read the index
        st >> word; // Read the symbol
        string label = word;
        st >> word; // Read the address
        int address = safeStoi(word);
        if (address != -1)
        {
            symtab.push_back({label, address});
        }
    }
    sin.close();

    // Read literal table
    while (getline(lin, line))
    {
        stringstream st(line);
        st >> word; // Read the index
        st >> word; // Read the literal
        string label = word;
        st >> word; // Read the address
        int address = safeStoi(word);
        if (address != -1)
        {
            littab.push_back({label, address});
        }
    }
    lin.close();

    int lc = -1;

    // Process intermediate code
    while (getline(fin, line))
    {
        stringstream st(line);
        st >> word; // Read the location counter or directive
        if (word == "---")
        {
            fout << "No Machine Code" << endl;
            continue;
        }

        lc = safeStoi(word);
        if (lc == -1)
            continue; // Skip if invalid lc

        st >> word;
        string cls = word.substr(1, 2);
        string mnemonic = word.substr(4, 2);

        if (cls == "AD")
        {
            fout << "No Machine Code" << endl;

            if (mnemonic == "01")
            { // START
                st >> word;
                word = word.substr(3, word.length() - 4);
                lc = safeStoi(word);
            }
            else if (mnemonic == "03")
            { // ORIGIN
                st >> word;
                word = word.substr(3, word.length() - 4);
                int ind = safeStoi(word) - 1;
                if (ind >= 0 && ind < symtab.size())
                {
                    lc = symtab[ind].second;
                }
            }
        }
        else if (cls == "IS")
        {
            fout << lc << " " << mnemonic << " ";
            lc++;

            if (mnemonic == "00")
            { // STOP
                fout << "0 000" << endl;
                continue;
            }

            st >> word;
            if (word[1] != 'S' && word[1] != 'L')
            {
                fout << word.substr(1, 1) << " ";
                st >> word;
            }
            else
            {
                fout << "0 ";
            }

            int num = safeStoi(word.substr(3, word.length() - 4)) - 1;
            if (word[1] == 'S')
            {
                if (num >= 0 && num < symtab.size())
                {
                    fout << symtab[num].second << endl;
                }
            }
            else if (word[1] == 'L')
            {
                if (num >= 0 && num < littab.size())
                {
                    fout << littab[num].second << endl;
                }
            }
        }
        else if (cls == "DL")
        {
            fout << lc << " ";
            lc++;

            if (mnemonic == "01")
            { // DC
                fout << "00 0 ";
                st >> word;
                fout << "00" << word.substr(3, word.length() - 4) << endl;
            }
            else if (mnemonic == "02")
            { // DS
                fout << "No Machine Code" << endl;
            }
        }
    }

    fout.close();
    fin.close();
    cout << "\nProgram Executed\n";

    return 0;
}
