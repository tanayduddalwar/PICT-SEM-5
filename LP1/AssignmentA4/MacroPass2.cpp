#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include <sstream>
using namespace std;

class MNTTAB {
public:
    int pp, kp, mdtp, kptp;
    string name;

    MNTTAB() : pp(0), kp(0), mdtp(0), kptp(0), name("") {}

    MNTTAB(int pp, int kp, int mdtp, int kptp, string name) {
        this->pp = pp;
        this->kp = kp;
        this->mdtp = mdtp;
        this->kptp = kptp;
        this->name = name;
    }
};

int main() {
    unordered_map<string, MNTTAB> mnt;
    unordered_map<string, int> aptinverse;
    unordered_map<int, string> apt;

    ifstream in("intermediate.txt");
    ifstream mdtfile("mdt.txt");
    ifstream mntfile("mnt.txt");
    ifstream kpfile("kpdt.txt");
    ofstream pass2("pass2.txt");

    vector<string> mdt;
    vector<string> kptab;
    string line;
    int pp, kp, mdtp, kpdtp, paramNo;
    // Reading KPDT file
    while (getline(kpfile, line)) {
        kptab.push_back(line);  // Corrected: kpdt -> kptab to match the variable declared for KPDT storage.
    }
    
    // Reading MDT file
    while (getline(mdtfile, line)) {
        mdt.push_back(line);  // Corrected: mdtfile -> mdt, as `mdt` is where lines should be stored.
    }
    
    // Reading MNT file and storing it in mnt map
    while (getline(mntfile, line)) {
        int pp, kp, mdtp, kpdtp;
        string name;

        istringstream iss(line);
        iss >> name >> pp >> kp >> mdtp >> kpdtp;
        mnt[name] = MNTTAB(pp, kp, mdtp, kpdtp, name);  // Corrected: `MNT` -> `MNTTAB`, matching the class name.
    }

    int parano;
    // Reading the intermediate file
    while (getline(in, line)) {  // Corrected: `interfile` -> `in`, matching the ifstream variable for intermediate file.
        vector<string> parts;
        string part;
        istringstream iss(line);
        while (iss >> part) {
            parts.push_back(part);
        }

        // Check if the macro name is in the MNT
        if (mnt.find(parts[0]) != mnt.end()) {
            MNTTAB entry = mnt[parts[0]];
            pp = entry.pp;
            kp = entry.kp;
            mdtp = entry.mdtp;
            kpdtp = entry.kptp;
            parano = 1;

            // Handling positional parameters
            for (int i = 0; i < pp; i++) {
                parts[parano].erase(remove(parts[parano].begin(), parts[parano].end(), ','), parts[parano].end());
                apt[parano] = parts[parano];
                aptinverse[parts[parano]] = parano;
                parano++;
            }

            // Handling keyword parameters
            int j = kpdtp - 1;
            for (int i = 0; i < kp; i++) {
                string key, value;
                istringstream iss(kptab[j]);  // Corrected: `kpdt` -> `kptab`, matching KPDT storage.
                iss >> key >> value;
                apt[parano] = value;
                aptinverse[key] = parano;
                parano++;
                j++;
            }

            // Handling parameters in the form of `key=value`
            for (int i = pp + 1; i < parts.size(); i++) {
                parts[i].erase(remove(parts[i].begin(), parts[i].end(), ','), parts[i].end());  // Corrected: `start()` -> `begin()`
                istringstream iss(parts[i]);
                string key, value;
                getline(iss, key, '=');
                getline(iss, value);
                value.erase(remove(value.begin(), value.end(), ','), value.end());
                apt[aptinverse[key]] = value;
            }

            // Expanding macro definition using MDT entries
            int i = mdtp - 1;
            while (mdt[i] != "MEND") {
                istringstream iss(mdt[i]);
                vector<string> parts;
                string part;
                while (iss >> part) {
                    parts.push_back(part);
                }
                pass2 << "+";
                for (int i = 0; i < parts.size(); i++) {
                    if (parts[i].find("(P,") != string::npos) {
                        string num = parts[i].substr(parts[i].find("(P,") + 3);  // Corrected indexing for `(P,` extraction.
                        num.erase(remove(num.begin(), num.end(), ')'), num.end());
                        int paraidx = stoi(num);
                        pass2 << apt[paraidx] << "\t";
                    } else {
                        pass2 << parts[i] << "\t";
                    }
                }
                pass2 << "\n";
                i++;
            }

            // Clearing APT tables for next macro expansion
            apt.clear();
            aptinverse.clear();
        } else {
            pass2 << line << "\n";  // Copy non-macro lines directly
        }
    }

    // Close all files
    in.close();
    mntfile.close();
    mdtfile.close();
    kpfile.close();
    pass2.close();

    return 0;
}
