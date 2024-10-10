#include <iostream>
using namespace std;

class HammingCode{
private:
    bool iseven;
    string sender(string dataword){
        cout<<"SENDER\n";
        cout<<"Dataword: "<<dataword<<endl;
        char r[11];
        int p = 6;
        int parity[4];
        int parity_position = 1;
        for(int i = 10; i>=0; i--){
            if(i == 11 - parity_position){
                parity_position *=2;
                r[i] = '2';
            }
            else{
                r[i] = dataword[p];
                p--;
            }
        }

        //parity calculation
        parity_position = 1;
        int count;
        for(int i = 0; i<4; i++){
            p = 11;
            count = 0;
            while(p >= 0){
                p -= parity_position;
                for(int i = 0; i<parity_position; i++){
                if(r[p] == '1'){
                    count++;
                }
                p--;
                if(p<0){
                    break;
                }
                }
            }
            if(iseven){
            parity[i] = count%2;
            }
            else{
                if(count%2 == 0){
                    parity[i] = 1;
                }
                else{
                    parity[i] = 0;
                }
            }
            r[11-parity_position] = to_string(parity[i])[0];
            parity_position *= 2;
        }
        
        cout<<"Codeword: ";
        string codeword = "           ";
        for(int i = 0; i<11; i++){
            codeword[i] = r[i];
            
        }
        cout<<codeword;
        cout<<endl;
        cout<<"Parity Bits: \n";
        for(int i : parity){
            cout<<i<<" ";
        }
        cout<<endl;
        //inducing error
        char choice;

        cout<<"Do you want to induce error (y/n) : ";
        cin>>choice;

        if(choice == 'y'){
            int error = rand()%10;
            cout<<"Error will be induced at: "<<11-error<<"th position\n";
            if(codeword[error]=='0'){
            codeword[error] = '1';
            }
            else{
                codeword[error] = '0';
            }
        }
        
        cout<<endl;
        reciever(codeword);
        return r;
    }

    string reciever(string codeword){
        cout<<"Reciever\n";
        cout<<"Codeword: "<<codeword<<endl;
        int p;
        int parity[4];
        int parity_position = 1;
        //parity calculation
        int count;
        for(int i = 0; i<4; i++){
            p = 11;
            count = 0;
            while(p >= 0){
                p -= parity_position;
                for(int i = 0; i<parity_position; i++){
                if(codeword[p] == '1'){
                    count++;
                }
                p--;
                if(p<0){
                    break;
                }
                }
            }

            if(iseven){
            parity[i] = count%2;
            }
            else{
                if(count%2 == 0){
                    parity[i] = 1;
                }
                else{
                    parity[i] = 0;
                }
            }
            parity_position *= 2;
        }
        string res = "00    ";
        cout<<"Parity bits: ";
        int x = 2;
        for(int i = 3; i>=0; i--){
            cout<<parity[i]<<" ";
        res[x] = to_string(parity[i])[0];
        x++;
        }
        cout<<"\n";
        int r = binary_to_int(res);
        if(r){
            cout<<"\nAs all parity bits are not zero there is an error at "<<r<<"th position\n";
            if(codeword[11-r] == '0'){
                codeword[11-r] = '1';
            }
            else{
                codeword[11-r] = '0';
            }
            cout<<"Error corrected\n";
        }
        else{
            cout<<"\nAs all parity bits are zero recieved codeword is valid and accepted\n";
        }
            string d = "";
            parity_position = 8;
            for(int i = 0; i<=10; i++){
            if(i == 11 - parity_position){
                parity_position /=2;
            }
            else{
                d += codeword[i];
                
            }
        }
        cout<<"Dataword: "<<d<<endl;
        cout<<"Data: ";
        char c = binary_to_int(d);
        cout<<c<<endl;
        cout<<"---------------------------------------------------------------\n";

        return d;
    }

    string int_to_binary(int num){
        string r = "";
        int arr[7];
        for(int i = 6; i>=0; i--){
            arr[i] = num%2;
            num = num/2;
        }
        for(int i = 0; i<7; i++){
            r+= to_string(arr[i]);
        }
        return r;
    }
    int binary_to_int(string binary){
        
        int r = 0;
        int s = 1;
        int length = binary.size();
        for(int i = length-1; i>=0; i--){
            if(binary[i] == '1'){
                r+= s;
            }
            s*=2;
        }
        return r;
    }
public:
    HammingCode(){}

    void send(string s, bool e){
        iseven = e;
        for(char c: s){
            cout<<"---------------------------------------------------------------\n";
            cout<<"Sending : "<<c<<endl;
            sender(int_to_binary(c));

        }
    }
};


int main(){
    HammingCode h = HammingCode();
    int c;
    string data;
    while(true){
    cout<<"Enter 0 to exit\n";
    cout<<"Enter 1 to enter data\n";
        cout<<"Enter choice: ";
        cin>>c;
        if(c == 0){
            break;
        }
        if(c == 1){
            cout<<"Enter data: ";
            cin>>data;
            bool e = true;
            cout<<"Enter e for even parity\nEnter o for odd parity";
            cout<<"Enter choice (e/o): ";
            char ch;
            cin>>ch;
            if(ch == 'o'){
                e = false;
            }
            else{
                e = true;
            }
            h.send(data, e);
        }

    }
}