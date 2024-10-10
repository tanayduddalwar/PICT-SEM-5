#include    <bits/stdc++.h>
using   namespace   std;

string given_ip_str="";
int no_of_subnets=0;
vector<int>given_ip_v;

vector<int>my_subnet_mask={255,255,255,0}, subnet_mask_v;
vector<int>my_ip_v={192,168,39,137};

void print(vector<int>&v)
{
    cout<<"\n"<<v[0];
    for(int i=1;i<v.size();i++)    cout<<"."<<v[i];
}

string to_string(vector<int> v)
{
    string as=to_string(v[0]);
    for(int i=1;i<v.size();i++)    
    {
        as+="."+to_string(v[i]);
    }
    return as;
}
vector<int> split(string s) {
    string delimiter=".";
    vector<int> tokens;
    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(stoi(token));
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(stoi(s));

    return tokens;
}




vector<int> calculate_subnet_mask(vector<int>given_ip_v)
{
    int bits_to_set=0,lbyte=0;
    while(pow(2,bits_to_set)<no_of_subnets) bits_to_set++;
    int pow2=7;
    for(int i=1;i<=bits_to_set;i++)
    {
        lbyte=lbyte+pow(2,pow2);
        pow2--;
    }
    
    vector<int>subnet_mask_v={255,255,255,lbyte};
    return  subnet_mask_v;
}

vector<int> andv(vector<int>v1,vector<int>v2)
{
    vector<int>as;
    for(int i=0;i<v2.size();i++)
    {
        cout<<v1[i]<<" and "<<v2[i]<<"\n";
        as.push_back(v1[i] & v2[i]);
    }
    cout<<"\n after anding: ";
    for(int i:as)   cout<<" "<<i;
    return  as;
}
void command()
{
    if(subnet_mask_v==my_subnet_mask    and     andv(my_ip_v,my_subnet_mask)==andv(given_ip_v,my_subnet_mask))  
    {
        string  cmd="ping -n 3 "+given_ip_str;
        system(cmd.c_str());
    }
}

int main()
{
    
    while(1)
    {
        cout<<"\n   Laptop Ip Address: "<<to_string(my_ip_v);
        cout<<"\n   Enter Ip of Mobile: ";
        cin>>given_ip_str;
        given_ip_v=split(given_ip_str);
        cout<<"\n   Enter number of subnets?:  ";
        cin>>no_of_subnets;

        vector<int>subnet_mask_v=calculate_subnet_mask(given_ip_v);
        cout<<"\nthe-subnet-mask-is:\t"<<to_string(subnet_mask_v);

        // print(given_ip_v);
        
        
        if(no_of_subnets==1)
        {
            string  cmd="ping -n 3 "+given_ip_str;
            system(cmd.c_str());
        }
        else    cout<<"\n-----out-of-my-subnet---------\ni-shouldnt-ping\n";
    }
    return 0;
}