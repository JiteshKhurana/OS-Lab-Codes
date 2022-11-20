#include<iostream>
using namespace std;

void findWaitingTime(int processes[],int n,int bt[],int wt[]){
    wt[0] = 0;

    for (int i = 1; i < n; i++)
    {
        wt[i] = wt[i-1]+bt[i-1];

        if(wt[i]<0){
            wt[i] = 0;
        }
    }

}
void findTurnAroundTime(int processes[],int n,int bt[],int wt[],int tat[]){
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
    }
}
void findAvgTime(int processes[],int n,int bt[]){
    int wt[n],tat[n],total_wt = 0,total_tat=0;
    findWaitingTime(processes,n,bt,wt);
    findTurnAroundTime(processes,n,bt,wt,tat);

    cout<<" Burst Time "<<" Completion Time "<<" Turn-Around Time "<<" Waiting Time \n";

    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt+wt[i];
        total_tat = total_tat+tat[i];
        cout<<" "<<bt[i]<<"\t\t"<<tat[i]<<"\t\t"<<tat[i]<<"\t\t"<<wt[i]<<endl;
    }
    
    cout<<"Average Waiting time = "<<(float)total_wt/(float)n<<endl;
    cout<<"Average turn around time = "<<(float)total_tat/(float)n<<endl;
}

int main(){
    int processes[] = {1,2,3,4};
    int n = sizeof(processes)/sizeof(processes[0]);
    int burst_time[] = {6,8,7,3};

    sort(burst_time,burst_time+n);

    findAvgTime(processes,n,burst_time);

    return 0;
}