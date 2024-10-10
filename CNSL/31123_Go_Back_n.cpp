#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;

void transmission(int window_size, int total_frame, int &sent_cnt)
{
    int i = 1;
    while (i <= total_frame)
    {
        int z = 0;

        int k = i;
        while (k < i + window_size && k <= total_frame)
        {
            cout << "Frame " << k << " sent" << endl;
            sent_cnt++;
            k++;
        }

        k = i;
        sleep(1);
        while (k < i + window_size && k <= total_frame)
        {
            int f = rand() % 2;
            if (!f)
            {
                cout << "Acknowledgment for Frame " << k << endl;
                z++;
            }
            else
            {
                cout << "Timeout! Frame Number: " << k << " Not Received" << endl;
                break;
            }

            k++;
        }

        sleep(2);
        
        cout << "\n";
        if(z > 0){
            cout << "Window slided" << endl;
        }
        i = i + z;
    }
}

int main()
{
    int total_frame, sent_cnt = 0;

    int m = 2;  // Hardcoded value of m as 3
    int window_size = (1 << m) - 1;  // 2^m - 1

    cout << "Window size (2^m - 1) for m = 2 is: " << window_size << endl;

     total_frame=7;

    transmission(window_size, total_frame, sent_cnt);
    cout << "Total number of frames which were sent and resent are: " << sent_cnt << endl;

    return 0;
}
