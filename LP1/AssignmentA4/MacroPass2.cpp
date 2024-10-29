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

void removechar(string &str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
}

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

    // Reading MDT file
    while (getline(mdtfile, line)) {
        mdt.push_back(line);
    }

    // Reading KPDT file
    while (getline(kpfile, line)) {
        kptab.push_back(line);
    }

    // Reading MNT file
    while (getline(mntfile, line)) {
        istringstream iss(line);
        string name;
        int pp, kp, mdtp, kpdtp;
        iss >> name >> pp >> kp >> mdtp >> kpdtp;
        mnt[name] = MNTTAB(pp, kp, mdtp, kpdtp, name);
    }

    // Reading Intermediate File
    while (getline(in, line)) {
        istringstream iss(line);
        vector<string> parts;
        string part;

        while (iss >> part) {
            parts.push_back(part);
        }

        if (mnt.find(parts[0]) != mnt.end()) {
            MNTTAB entry = mnt[parts[0]];
            pp = entry.pp;
            kp = entry.kp;
            mdtp = entry.mdtp;
            kpdtp = entry.kptp;
            paramNo = 1;

            // Processing Positional Parameters
            for (int i = 0; i < pp; ++i) {
                removechar(parts[paramNo], ',');
                apt[paramNo] = parts[paramNo];
                aptinverse[parts[paramNo]] = paramNo;
                paramNo++;
            }

            // Processing Keyword Parameters
            int j = kpdtp - 1;
            for (int i = 0; i < kp; ++i) {
                istringstream iss(kptab[j]);
                string key, value;
                iss >> key >> value;
                apt[paramNo] = value;
                aptinverse[key] = paramNo;
                paramNo++;
                j++;
            }

            // Overriding Keyword Parameters
            for (int i = pp + 1; i < parts.size(); ++i) {
                removechar(parts[i], ',');
                istringstream iss(parts[i]);
                string name, value;
                getline(iss, name, '=');
                removechar(name, '&');
                getline(iss, value);
                apt[aptinverse[name]] = value;
            }

            // Expanding the Macro
            int i = mdtp - 1;
            while (mdt[i] != "MEND") {
                istringstream iss(mdt[i]);
                vector<string> parts;
                string word;

                while (iss >> word) {
                    parts.push_back(word);
                }

                pass2 << "+";
                for (const string &s : parts) {
                    if (s.find("(P,") != string::npos) {
                        string num = s.substr(s.find(",") + 1);
                        removechar(num, ')');
                        int paraidx = stoi(num);
                        pass2 << apt[paraidx] << "\t";
                    } else {
                        pass2 << s << "\t";
                    }
                }
                pass2 << "\n";
                i++;
            }

            // Clear Parameter Tables
            apt.clear();
            aptinverse.clear();
        } else {
            pass2 << line << "\n";
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

/*
Steps:
1.Create MNT CLASS 
2.Create Unordered map of mnt and vector of kpdtp and mdt
3.Read MDT file
4.Read KPDT File 
5.Read MNT File and store this in mnt map
6. Read intermediate File
7. Read Positional parameters first and add it in ap and apinverse map with parano
8. then add kptab parameters and add it in ap and apinverse map 
9. then from pp+1 to parts.size() run loop and add it to ap map
10. 



*/