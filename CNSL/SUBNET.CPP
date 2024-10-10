#include <iostream>
#include <cmath>
#include <string>
using namespace std;

class IPSubnetting {
private:
    string subnetMask;
    char ipClass;
    int ipAddress[4]; // Store all four octets of the IP address
    int subnetRange;
    int deviceAddress;

    // Determines the class and default subnet mask
    void determineClassAndMask() {
        if (ipAddress[0] <= 127) {
            ipClass = 'A';
            subnetMask = "255.0.0.0";
        } else if (ipAddress[0] <= 191) {
            ipClass = 'B';
            subnetMask = "255.255.0.0";
        } else if (ipAddress[0] <= 223) {
            ipClass = 'C';
            subnetMask = "255.255.255.0";
        }
    }

    // Generates a custom subnet mask based on the required number of subnets
    void createCustomMask(int numSubnets) {
        int requiredBits = ceil(log2(numSubnets));
        int maskParts[3] = {0, 0, 0};
        int fullOctets = requiredBits / 8;
        int index = 0;

        for (int i = 0; i < fullOctets; i++) {
            maskParts[index++] = 255;
        }

        int remainingBits = requiredBits % 8;
        int value = 128, accumulated = 0;

        for (int i = 0; i < remainingBits; i++) {
            accumulated += value;
            value /= 2;
        }
        maskParts[index] = accumulated;

        if (ipClass == 'A') {
            subnetMask = "255." + to_string(maskParts[0]) + "." + to_string(maskParts[1]) + "." + to_string(maskParts[2]);
        } else if (ipClass == 'B') {
            if (index > 2) {
                cout << "Cannot form subnet for class B\n";
                return;
            }
            subnetMask = "255.255." + to_string(maskParts[0]) + "." + to_string(maskParts[1]);
        } else if (ipClass == 'C') {
            if (index > 1) {
                cout << "Cannot form subnet for class C\n";
                return;
            }
            subnetMask = "255.255.255." + to_string(maskParts[0]);
        }

        cout << "Calculated Subnet Mask: " << subnetMask << endl;
        generateSubnets(numSubnets);
    }

    // Generates the network IP ranges based on the number of subnets
    void generateSubnets(int numSubnets) {
        int step = 256 / numSubnets;
        subnetRange = step;

        int subnetCount = 1;
        string baseIp = to_string(ipAddress[0]) + "." + to_string(ipAddress[1]) + "." + to_string(ipAddress[2]) + ".";

        for (int i = 0; i < 256; i += step) {
            cout << "-------------------------------------\n";
            cout << "\nSubnet " << subnetCount << endl;
            cout << baseIp << i << " (Network Address)\n";

            for (int j = 1; j < step - 1; j++) {
                cout << baseIp << i + j << endl;
            }

            cout << baseIp << i + (step - 1) << " (Broadcast Address)\n";
            subnetCount++;
            cout << "-------------------------------------\n";
        }

        // Assign a device IP within the generated subnets
        while (true) {
            cout << "Select a host address for your device: ";
            cin >> deviceAddress;
            if ((deviceAddress + 1) % step == 0 || deviceAddress % step == 0) {
                cout << "Invalid address. Please choose another.\n";
            } else {
                // Format the complete device IP for configuration
                string command = "sudo ifconfig enp0s31f6 " + formatIPAddress() + " netmask " + subnetMask;
                int x = system(command.c_str());
                if (x) {
                    cout << "Error setting IP address.\n";
                }
                break;
            }
        }
    }

    // Format the complete IP address for pinging
    string formatIPAddress() {
        return to_string(ipAddress[0]) + "." + to_string(ipAddress[1]) + "." +
               to_string(ipAddress[2]) + "." + to_string(deviceAddress);
    }

public:
    IPSubnetting() {}

    // Pings a device within the same network
    void pingDevice(int targetAddress) {
        if ((targetAddress / subnetRange) == (deviceAddress / subnetRange)) {
            if (targetAddress % subnetRange == 0 || (targetAddress + 1) % subnetRange == 0) {
                cout << "Invalid host IP.\n";
            } else {
                string command = "ping " + to_string(ipAddress[0]) + "." +
                                 to_string(ipAddress[1]) + "." +
                                 to_string(ipAddress[2]) + "." +
                                 to_string(targetAddress);
                system(command.c_str());
            }
        } else {
            cout << "Cannot ping an IP from a different network.\n";
        }
    }

    // Sets the IP address and calculates the subnet mask
    void configureIpAddress(string inputIp) {
        cout << "Setting Network IP: " << inputIp << endl;
        int idx = 0;
        string temp = "";
        for (char c : inputIp) {
            if (c == '.') {
                ipAddress[idx++] = stoi(temp);
                temp = "";
            } else {
                temp += c;
            }
        }
        ipAddress[idx] = stoi(temp);

        determineClassAndMask();
        cout << "Default Subnet Mask: " << subnetMask << endl;

        int numSubnets;
        cout << "Enter the number of subnets required: ";
        cin >> numSubnets;
        createCustomMask(numSubnets);
    }
};

int main() {
    IPSubnetting subnetTool;
    int choice;
    string ip;

    while (true) {
        cout << "\n0. Exit\n1. Configure IP\n2. Ping Device\n";
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 0) {
            break;
        } else if (choice == 1) {
            cout << "Enter Network IP: ";
            cin >> ip;
            subnetTool.configureIpAddress(ip);
        } else if (choice == 2) {
            int targetHost;
            cout << "Enter host address to ping: ";
            cin >> targetHost;
            subnetTool.pingDevice(targetHost);
        }
    }

    return 0;
}
