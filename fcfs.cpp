#include<iostream>
using namespace std;

void findWaitingTime(int processes[],int n,int bt[],int wt[],int at[]){
    int service_time[n];
    service_time[0] = at[0];
    wt[0] = 0;

    for (int i = 1; i < n; i++)
    {
        service_time[i] = service_time[i-1]+bt[i-1];

        wt[i] = service_time[i]-at[i];

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

void findAvgTime(int processes[],int n,int bt[],int at[]){
    int wt[n],tat[n],total_wt = 0,total_tat = 0;;
    findWaitingTime(processes,n,bt,wt,at);

    findTurnAroundTime(processes,n,bt,wt,tat);

    cout<<"Processes "<<" Arrival Time "<<" Burst Time "<<" Completion Time "<<" Turn-Around Time "<<" Waiting Time \n";

    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt+wt[i];
        total_tat = total_tat+tat[i];
        int comple_time = tat[i]+at[i];
        cout<<" "<<i+1<<"\t\t"<<at[i]<<"\t\t"<<bt[i]<<"\t\t"<<comple_time<<"\t\t"<<tat[i]<<"\t\t"<<wt[i]<<endl;
    }
    
    cout<<"Average Waiting time = "<<(float)total_wt/(float)n<<endl;
    cout<<"Average turn around time = "<<(float)total_tat/(float)n<<endl;
}

int main(){
    int processes[] = {1,2,3,4};
    int n = sizeof(processes)/sizeof(processes[0]);
    int burst_time[] = {5,3,8,6};
    int arrival_time[] = {0,1,2,3};

    findAvgTime(processes,n,burst_time,arrival_time);
    return 0;
}