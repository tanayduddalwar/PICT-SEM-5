#include<iostream>
#include <unistd.h>
using namespace std;

int window_size = 4;

void SR( int nf)
{
   int window[nf];
   for(int i=0; i<nf; i++){
   window[i]=i;
   }
   int send[window_size], receive[window_size], acked[nf];
   for(int i=0; i<nf; i++)
   {
       acked[i]=-1;
   }
   for(int i=0; i<window_size; i++)
   {
      send[i]=-1;
      receive[i]=-1;
   }
   int i=0, k=0, p=0;
   while(i<nf)
   {
       int flag=1, j;
       for(j=0; j<=(i-window_size); j++)
       {
           if(acked[j]==0)
           {
               cout<<"Timeout for frame "<<j<<". Retransmitting frame "<<j<<endl;
               flag=0;
               break;
           }
      }
      if(flag==0)
      {
         int temp=i;
         i=j;
         // packet is lost or corrupted
            cout<<"Frame "<<i<<" is sent"<<endl;
            receive[p]=window[i];
            cout<<"Frame "<<i<<" is received"<<endl;
            acked[i]=1;
            cout<<"Ack is sent for frame "<<i<<endl;
            i=temp;
            p = (p+1)%window_size;
         
      }
      else
      {
          int rn=rand()%5;
          
          if(rn==1)
          {
             acked[i]=0;
             cout<<"Frame "<<i<<" is lost."<<endl;
             send[k]=window[i];
             i++;
             k = (k+1)%window_size;
          }
         else
         {
             send[k]=window[i];
             cout<<"Frame "<<i<<" is sent"<<endl;
             receive[p]=window[i];
             cout<<"Frame "<<i<<" is received."<<endl;
             acked[i]=1;
             cout<<"Ack is sent for frame "<<i<<endl;
             sleep(2);
             i++;
             k = (k+1)%window_size;
             p = (p+1)%window_size;
         }
      }
      cout<<"Sender Window:"<<endl;
      int temp = k;
      for(int l=0; l<window_size; l++)
      {
        
          if(send[temp]!=-1)
          cout<<send[temp]<<"  ";
          temp += 1;
          temp %= window_size;
      }

       cout<<endl;
       cout<<"Receiver Window:"<<endl;
       temp = p;
       for(int l=0; l<window_size; l++)
       {
            if(receive[temp]!=-1)
            cout<<receive[temp]<<" ";
            temp += 1;
            temp %= window_size;
       }
       cout<<endl;
       sleep(2);
   }
}

int main()
{
    int total_frame, sent_cnt = 0;

    total_frame=7;
    SR(total_frame);
    return 0;
}