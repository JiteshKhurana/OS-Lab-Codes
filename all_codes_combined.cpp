//FCFS
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


//SJF
#include<iostream>
using namespace std;

struct Process{
    int pid;
    int bt;
};

bool compare(Process a,Process b){
    return (a.bt<b.bt);
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
    Process proc[] = {{1, 6}, {2, 8}, {3, 7}, {4, 3}}; 
    int n = sizeof(proc)/sizeof(proc[0]);
    sort(proc,proc+n,compare);
    findAvgTime(proc,n);
    return 0;
}

//Priority
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

//RR
#include<iostream>
using namespace std;

void findWaitingTime(int processes[],int n,int bt[],int wt[],int quantum){
    int rem_bt[n]; //To store remaining burst time

    for (int i = 0; i < n; i++)
    {
        rem_bt[i] = bt[i];
    }
    
    int t=0; //Current time

    while(1){
        bool done = true;
        for (int i = 0; i < n; i++)
        {
            if(rem_bt[i]>0){
                done = false;
                if(rem_bt[i]>quantum){
                    t+=quantum;
                    rem_bt[i]-=quantum;
                }
                else{
                    t+=rem_bt[i];
                    wt[i] = t-bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if(done==true)  //If all processes are done
            break;
        
    }
}

void findTurnAroundTime(int processes[],int n,int bt[],int wt[],int tat[]){
    for (int i = 0; i < n; i++)
    {
        tat[i] = bt[i] + wt[i];
    }
}

void findAvgTime(int processes[],int n,int bt[],int quantum){
    int wt[n],tat[n],total_wt=0,total_tat=0;

    findWaitingTime(processes,n,bt,wt,quantum);

    findTurnAroundTime(processes,n,bt,wt,tat);

    cout<<"Processes "<<" Burst Time "<<" Turn-Around Time "<<" Waiting Time \n";

    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt+wt[i];
        total_tat = total_tat+tat[i];
        cout<<" "<<i+1<<"\t\t"<<bt[i]<<"\t\t"<<tat[i]<<"\t\t"<<wt[i]<<endl;
    }
    
    cout<<"Average Waiting time = "<<(float)total_wt/(float)n<<endl;
    cout<<"Average turn around time = "<<(float)total_tat/(float)n<<endl;
}


int main(){
    int processes[] = {1,2,3};
    int n = sizeof(processes)/sizeof(processes[0]);
    int burst_time[] = {10,5,8};
    int quantum = 2;
    findAvgTime(processes,n,burst_time,quantum);
    
    return 0;
}

//Banker
#include <iostream>
using namespace std;

int main()
{
    int n = 5; // No of processes
    int m = 3; // No of resources
    int alloc[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int max[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {4, 2, 2}, {5, 3, 3}};
    int available[3] = {3, 3, 2}; // Available resources

    int need[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int finish[n], ans[n], ind = 0;
    memset(finish, 0, sizeof(finish));

    for (int k = 0; k < 5; k++)
    {
        for (int i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int flag = 0;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > available[j])
                    {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0)
                {
                    ans[ind++] = i;
                    for (int y = 0; y < m; y++)
                    {
                        available[y] += alloc[i][y];
                        finish[i] = 1;
                    }
                }
            }
        }
    }

    int flag = 1;

    for (int i = 0; i < n; i++)
    {
        if (finish[i] == 0)
        {
            flag = 0;
            cout << "The given sequence is not safe";
            break;
        }
    }

    if (flag == 1)
    {
        cout << "Following is the SAFE Sequence" << endl;
        for (int i = 0; i < n; i++)
            cout << " P" << ans[i] << " ->";
    }

    return (0);
}

//first Fit
#include<iostream>
using namespace std;

void firstFit(int blockSize[], int m,
			int processSize[], int n)
{
	// Stores konsa block no. konse process ko allocate hua hai
	int allocation[n];

	// Initially no block is assigned to any process
    // memset() -> to initialize array's elements
    // This is used to set all value of array (int) is either 0 or -1.
	memset(allocation, -1, sizeof(allocation));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			if (blockSize[j] >= processSize[i])
			{
				// allocate block j to p[i] process
				allocation[i] = j;

				blockSize[j] -= processSize[i];

				break;
			}
		}
	}

	cout << "\nProcess No.\tProcess Size\tBlock no.\n";
	for (int i = 0; i < n; i++)
	{
		cout << " " << i+1 << "\t\t"
			<< processSize[i] << "\t\t";
		if (allocation[i] != -1)
			cout << allocation[i] + 1;
		else
			cout << "Not Allocated";
		cout << endl;
	}
}

int main()
{
	int blockSize[] = {100, 500, 200, 300, 600};
	int processSize[] = {212, 417, 112, 426};
	int m = sizeof(blockSize) / sizeof(blockSize[0]);
	int n = sizeof(processSize) / sizeof(processSize[0]);

	firstFit(blockSize, m, processSize, n);

	return 0 ;
}

//Best fit
#include<iostream>
using namespace std;

void bestFit(int blockSize[], int m, int processSize[], int n)
{
    // Stores konsa block no. konse process ko allocate hua hai
    int allocation[n];

    memset(allocation, -1, sizeof(allocation));

    for (int i=0; i<n; i++)
    {
        int bestIdx = -1;
        for (int j=0; j<m; j++)
        {
            if (blockSize[j] >= processSize[i])
            {
                if (bestIdx == -1)
                    bestIdx = j;
                else if (blockSize[bestIdx] > blockSize[j])
                    bestIdx = j;
            }
        }

        // If we could find a block for current process
        if (bestIdx != -1)
        {
            // allocate block j to p[i] process
            allocation[i] = bestIdx;

            blockSize[bestIdx] -= processSize[i];
        }
    }

    cout << "\nProcess No.\tProcess Size\tBlock no.\n";
    for (int i = 0; i < n; i++)
    {
        cout << "   " << i+1 << "\t\t" << processSize[i] << "\t\t";
        if (allocation[i] != -1)
            cout << allocation[i] + 1;
        else
            cout << "Not Allocated";
        cout << endl;
    }
}

int main()
{
    int blockSize[] = {100, 500, 200, 300, 600};
    int processSize[] = {212, 417, 112, 426};
    int m = sizeof(blockSize)/sizeof(blockSize[0]);
    int n = sizeof(processSize)/sizeof(processSize[0]);

    bestFit(blockSize, m, processSize, n);

    return 0 ;
}

//Worst fit
#include<iostream>
using namespace std;

void worstFit(int blockSize[], int m, int processSize[],
												int n)
{
    // Stores konsa block no. konse process ko allocate hua hai
	int allocation[n];

	memset(allocation, -1, sizeof(allocation));

	for (int i=0; i<n; i++)
	{
		int wstIdx = -1;
		for (int j=0; j<m; j++)
		{
			if (blockSize[j] >= processSize[i])
			{
				if (wstIdx == -1)
					wstIdx = j;
				else if (blockSize[wstIdx] < blockSize[j])
					wstIdx = j;
			}
		}

		if (wstIdx != -1)
		{
			// allocate block j to p[i] process
			allocation[i] = wstIdx;

			blockSize[wstIdx] -= processSize[i];
		}
	}

	cout << "\nProcess No.\tProcess Size\tBlock no.\n";
	for (int i = 0; i < n; i++)
	{
		cout << " " << i+1 << "\t\t" << processSize[i] << "\t\t";
		if (allocation[i] != -1)
			cout << allocation[i] + 1;
		else
			cout << "Not Allocated";
		cout << endl;
	}
}

int main()
{
	int blockSize[] = {100, 500, 200, 300, 600};
	int processSize[] = {212, 417, 112, 426};
	int m = sizeof(blockSize)/sizeof(blockSize[0]);
	int n = sizeof(processSize)/sizeof(processSize[0]);

	worstFit(blockSize, m, processSize, n);

	return 0 ;
}
