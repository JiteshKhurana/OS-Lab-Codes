#include<iostream>
using namespace std;

struct Process{
    int pid;
    int bt;
    int priority;
};

bool compare(Process a, Process b) {
   return (a.priority > b.priority);
}

void findWaitingTime(Process proc[],int n,int wt[]){
    wt[0] = 0;
    for (int i = 1; i < n; i++)
    {
        wt[i] = proc[i-1].bt+wt[i-1];
    }
}

void findTurnAroundTime(Process proc[],int n,int wt[],int tat[]){
    for (int i = 0; i < n; i++)
    {
        tat[i] = wt[i]+proc[i].bt;
    }
}
void findAvgTime(Process proc[],int n){
    int wt[n],tat[n],total_wt=0,total_tat=0;
    findWaitingTime(proc,n,wt);
    findTurnAroundTime(proc,n,wt,tat);

   cout << "Processes "<< " Burst time " << " Waiting time " << " Turn around time"<<endl;

    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt+wt[i];
        total_tat = total_tat+tat[i];
        cout<<" "<<proc[i].pid<<"\t\t"<<proc[i].bt<<"\t\t"<<wt[i]<<"\t\t"<<tat[i]<<endl;
    }
    
    cout<<"Average Waiting time = "<<(float)total_wt/(float)n<<endl;
    cout<<"Average turn around time = "<<(float)total_tat/(float)n<<endl;
}

int main(){
    Process proc[] = {{1, 10, 2}, {2, 5, 0}, {3, 8, 1}};
    int n = sizeof(proc)/sizeof(proc[0]);
    sort(proc,proc+n,compare);
    findAvgTime(proc,n);

    return 0;
}