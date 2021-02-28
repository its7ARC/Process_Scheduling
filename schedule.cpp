
// Process Scheduling

// FCFS
// SJF(Non-preemptive)
// SRTF
// Priority (Non preemptive)
// Priority (Preemptive)
// Round Robin


//inclusions
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <limits.h>
#include <math.h>
#include <algorithm>
#include <iomanip>
#include <string>
#include <cstring>
#include <queue>

//macros
#define ll int  //
#define pb push_back
#define ff first
#define ss second
#define ii pair<ll,ll>
#define vi vector<ll>
#define vii vector<pair<ll,ll>>
#define vvi vector<vector<ll>>
#define res reserve
#define mii map<ll,ll>
#define sBits __builtin_popcount    //
#define t_z __builtin_ctz   //
#define l_z __builtin_clz   //
#define lb lower_bound
#define ub upper_bound
#define inf 1e18
#define MOD 1000000007
#define fr(i,a,b) for(auto i = a; i < b; i++)
#define tr(it,a,b) for(auto it = a; it != b; it++)
using namespace std;


/*####*/


//Program


//------------------ Process Struct --------------------

struct Job{
    ll id;
    ll arrivalTime;
    ll burstTime;
    ll waitTime = -1;
    ll turnaroundTime = -1;
    ll totBurst;
    ll priority;
    
};



//----------------- FCFS ----------------------------

/* Sample Input - FCFS
 5
 2 6
 5 3
 1 8
 0 3
 4 4
 */

struct compArrTime{
    bool operator()(Job const &a, Job const &b){
        return a.arrivalTime > b.arrivalTime;
    }
};

class FCFS{
    priority_queue<Job, vector<Job>, compArrTime> q;
    vector<Job> info;
    ll id = 0;
    ll clock = 0;
public:
    void insert(ll arrivalTime, ll burstTime){
        Job j;
        j.id = ++id;
        j.arrivalTime = arrivalTime;
        j.burstTime = burstTime;
        q.push(j);
    }
    void display(Job j){
        cout << "Job " << j.id << " in CPU\nClock: " << clock << "\n";
        auto d1 = q;
        auto d3 = d1;

        Job d2;
        d1.pop();
        cout << "Ready Queue:\n";
        if(d1.empty() || d1.top().arrivalTime > clock) cout << "Empty\n";
        while(!d1.empty()){
            d2 = d1.top();
            if(d2.arrivalTime > clock) break;
            cout << "ID: " << d2.id << "\tArr. Time: " << d2.arrivalTime << "\tCPU Burst Time: " << d2.burstTime << "\n";
            d1.pop();
        }
        cout << "\n";
    }
    
    void statisticalCounter(vector<Job> v){
        cout << "Statistical Counters\n";
        double avgWaitTime = 0;
        double avgTurnaroundTime = 0;
        fr(i,0,v.size()){
            cout << "ID: " << v[i].id << "\tWait time: " << v[i].waitTime << "\tTurnaround time: " << v[i].turnaroundTime << "\n";
            avgWaitTime += v[i].waitTime;
            avgTurnaroundTime += v[i].turnaroundTime;
        }
        avgWaitTime /= v.size();
        avgTurnaroundTime /= v.size();
        cout << "Average Waiting Time = " << avgWaitTime << "\nAverage Turnaround time = " << avgTurnaroundTime << "\n";
    }
    
    void schedule(){
        if(q.empty()){
            cout << "Job underflow encountered\n";
            return;
        }
        
        Job curr;
        clock = q.top().arrivalTime;
        while(!q.empty()){
            curr = q.top();
            curr.waitTime = clock - curr.arrivalTime;
            display(curr);
            clock += curr.burstTime;
            curr.turnaroundTime = clock - curr.arrivalTime;
            info.pb(curr);
            q.pop();
        }
        statisticalCounter(info);
    }

};



//---------------------- SJF(Non-preemptive) -----------------------

/* Sample Input SJF
 5
 2 6
 5 2
 1 8
 0 3
 4 4
 */

struct compBurstTime{
    bool operator()(const Job &a, const Job &b){
        return a.burstTime > b.burstTime;
    }
};

class SJF{
    priority_queue<Job, vector<Job>, compArrTime> q;
    priority_queue<Job, vector<Job>, compBurstTime> q2;
    vector<Job> info;
    ll id = 0;
    ll clock = 0;
public:
    void insert(ll arrivalTime, ll burstTime){
        Job j;
        j.id = ++id;
        j.arrivalTime = arrivalTime;
        j.burstTime = burstTime;
        q.push(j);
    }
    void display(Job j){
        cout << "Job " << j.id << " in CPU\nClock: " << clock << "\n";
        auto d1 = q2;
        auto d3 = d1;

        Job d2;
        d1.pop();
        cout << "Ready Queue:\n";
        if(d1.empty() || d1.top().arrivalTime > clock) cout << "Empty\n";
        while(!d1.empty()){
            d2 = d1.top();
            if(d2.arrivalTime > clock) break;
            cout << "ID: " << d2.id << "\tArr. Time: " << d2.arrivalTime << "\tCPU Burst Time: " << d2.burstTime << "\n";
            d1.pop();
        }
        cout << "\n";
    }
    
    void statisticalCounter(vector<Job> v){
        cout << "Statistical Counters\n";
        double avgWaitTime = 0;
        double avgTurnaroundTime = 0;
        fr(i,0,v.size()){
            cout << "ID: " << v[i].id << "\tWait time: " << v[i].waitTime << "\tTurnaround time: " << v[i].turnaroundTime << "\n";
            avgWaitTime += v[i].waitTime;
            avgTurnaroundTime += v[i].turnaroundTime;
        }
        avgWaitTime /= v.size();
        avgTurnaroundTime = v.size();
        cout << "Average Waiting Time = " << avgWaitTime << "\nAverage Turnaround time = " << avgTurnaroundTime << "\n";
    }
    
    void schedule(){
        if(q.empty()){
            cout << "Job underflow encountered\n";
            return;
        }
        
        Job curr;
        clock = q.top().arrivalTime;
        while(!q.empty() || !q2.empty()){
            while(!q.empty() && q.top().arrivalTime <= clock){
                q2.push(q.top());
                q.pop();
            }
            if(q2.empty()){
                clock = q.top().arrivalTime;
                continue;
            }
            curr = q2.top();
            curr.waitTime = clock - curr.arrivalTime;
            display(curr);
            clock += curr.burstTime;
            curr.turnaroundTime = clock - curr.arrivalTime;
            info.pb(curr);
            q2.pop();
        }
        statisticalCounter(info);
    }

};


//------------------------ SRTF -----------------------------

/* Sample Input - SRTF
 SJF
 5
 2 6
 5 2
 1 8
 0 3
 4 4
 */

class SRTF{
    priority_queue<Job, vector<Job>, compArrTime> q;
    //q2 -> Ready Queue
    priority_queue<Job, vector<Job>, compBurstTime> q2;
    vector<Job> info;
    ll id = 0;
    ll clock = 0;
public:
    void insert(ll arrivalTime, ll burstTime){
        Job j;
        j.id = ++id;
        j.arrivalTime = arrivalTime;
        j.burstTime = burstTime;
        j.totBurst = burstTime;
        q.push(j);
    }
    void display(Job j){
        cout << "Job " << j.id << " in CPU\nClock: " << clock << "\n";
        auto d1 = q2;
        auto d3 = d1;

        Job d2;
        d1.pop();
        cout << "Ready Queue:\n";
        if(d1.empty() || d1.top().arrivalTime > clock) cout << "Empty\n";
        while(!d1.empty()){
            d2 = d1.top();
            if(d2.arrivalTime > clock) break;
            cout << "ID: " << d2.id << "\tArr. Time: " << d2.arrivalTime << "\tCPU Burst Time: " << d2.burstTime << "\n";
            d1.pop();
        }
        cout << "\n";
    }
    
    void statisticalCounter(vector<Job> v){
        cout << "Statistical Counters\n";
        double avgWaitTime = 0;
        double avgTurnaroundTime = 0;
        fr(i,0,v.size()){
            cout << "ID: " << v[i].id << "\tWait time: " << v[i].waitTime << "\tTurnaround time: " << v[i].turnaroundTime << "\n";
            avgWaitTime += v[i].waitTime;
            avgTurnaroundTime += v[i].turnaroundTime;
        }
        avgWaitTime /= v.size();
        avgTurnaroundTime = v.size();
        cout << "Average Waiting Time = " << avgWaitTime << "\nAverage Turnaround time = " << avgTurnaroundTime << "\n";
    }
    
    void schedule(){
        if(q.empty()){
            cout << "Job underflow encountered\n";
            return;
        }
        
        Job curr;
        clock = q.top().arrivalTime;
        
        while(!q.empty() || !q2.empty()){
            if(q2.empty()){
                clock = q.top().arrivalTime;
                q2.push(q.top());
                q.pop();
            }
            curr = q2.top();
            display(curr);
            if((!q.empty() && q.top().arrivalTime >= clock + curr.burstTime) || q.empty()){
                clock += curr.burstTime;
                curr.turnaroundTime = clock - curr.arrivalTime;
                curr.waitTime = curr.turnaroundTime - curr.totBurst;
                info.pb(curr);
                q2.pop();
            }
            else{
                auto d3 = q2.top();
                d3.burstTime -= q.top().arrivalTime - clock;
                q2.pop(); q2.push(d3);
                clock = q.top().arrivalTime;
                q2.push(q.top());
                q.pop();
            }
        }
        statisticalCounter(info);
    }

};




//---------------- Priority Scheduling(Non-preemptive) --------------------

/* Sample Input - NPP
 5
 0 4 1
 0 3 2
 6 7 1
 11 4 3
 12 2 2
 */

struct compPriority{
    bool operator()(const Job &a, const Job &b){
        return (a.priority != b.priority?a.priority > b.priority:a.burstTime > b.burstTime);
    }
};


class PriorityNP{
    priority_queue<Job, vector<Job>, compArrTime> q;
    priority_queue<Job, vector<Job>, compPriority> q2;
    vector<Job> info;
    ll id = 0;
    ll clock = 0;
public:
    void insert(ll arrivalTime, ll burstTime, ll priority){
        Job j;
        j.id = ++id;
        j.arrivalTime = arrivalTime;
        j.priority = priority;
        j.burstTime = burstTime;
        q.push(j);
    }
    
    void display(Job j){
        cout << "Job " << j.id << " in CPU\nClock: " << clock << "\n";
        auto d1 = q2;
        auto d3 = d1;

        Job d2;
        d1.pop();
        cout << "Ready Queue:\n";
        if(d1.empty() || d1.top().arrivalTime > clock) cout << "Empty\n";
        while(!d1.empty()){
            d2 = d1.top();
            if(d2.arrivalTime > clock) break;
            cout << "ID: " << d2.id << "\tArr. Time: " << d2.arrivalTime << "\tBurst time: " << d2.burstTime << "\tPriority: " << d2.priority << "\n";
            d1.pop();
        }
        cout << "\n";
    }
    
    void statisticalCounter(vector<Job> v){
        cout << "Statistical Counters\n";
        double avgWaitTime = 0;
        double avgTurnaroundTime = 0;
        fr(i,0,v.size()){
            cout << "ID: " << v[i].id << "\tWait time: " << v[i].waitTime << "\tTurnaround time: " << v[i].turnaroundTime << "\n";
            avgWaitTime += v[i].waitTime;
            avgTurnaroundTime += v[i].turnaroundTime;
        }
        avgWaitTime /= v.size();
        avgTurnaroundTime = v.size();
        cout << "Average Waiting Time = " << avgWaitTime << "\nAverage Turnaround time = " << avgTurnaroundTime << "\n";
    }
    
    void schedule(){
        if(q.empty()){
            cout << "Job underflow encountered\n";
            return;
        }
        
        Job curr;
        clock = q.top().arrivalTime;
        while(!q.empty() || !q2.empty()){
            while(!q.empty() && q.top().arrivalTime <= clock){
                q2.push(q.top());
                q.pop();
            }
            if(q2.empty()){
                clock = q.top().arrivalTime;
                continue;
            }
            curr = q2.top();
            curr.waitTime = clock - curr.arrivalTime;
            display(curr);
            clock += curr.burstTime;
            curr.turnaroundTime = clock - curr.arrivalTime;
            info.pb(curr);
            q2.pop();
        }
        statisticalCounter(info);
    }

};



//------------------ Priority (Preemptive) --------------------

/* Sample Input - PP
5
0 4 1
0 3 2
6 7 1
11 4 3
12 2 2
*/
 
class PriorityP{
    priority_queue<Job, vector<Job>, compArrTime> q;
    priority_queue<Job, vector<Job>, compPriority> q2;
    vector<Job> info;
    ll id = 0;
    ll clock = 0;
public:
    void insert(ll arrivalTime, ll burstTime, ll priority){
        Job j;
        j.id = ++id;
        j.arrivalTime = arrivalTime;
        j.burstTime = burstTime;
        j.totBurst = burstTime;
        j.priority = priority;
        q.push(j);
    }
    void display(Job j){
        cout << "Job " << j.id << " in CPU\nClock: " << clock << "\n";
        auto d1 = q2;
        auto d3 = d1;

        Job d2;
        d1.pop();
        cout << "Ready Queue:\n";
        if(d1.empty() || d1.top().arrivalTime > clock) cout << "Empty\n";
        while(!d1.empty()){
            d2 = d1.top();
            if(d2.arrivalTime > clock) break;
            cout << "ID: " << d2.id << "\tArr. Time: " << d2.arrivalTime << "\tCPU Burst Time: " << d2.burstTime << "\tPriority: " << d2.priority << "\n";
            d1.pop();
        }
        cout << "\n";
    }
    
    void statisticalCounter(vector<Job> v){
        cout << "Statistical Counters\n";
        double avgWaitTime = 0;
        double avgTurnaroundTime = 0;
        fr(i,0,v.size()){
            cout << "ID: " << v[i].id << "\tWait time: " << v[i].waitTime << "\tTurnaround time: " << v[i].turnaroundTime << "\n";
            avgWaitTime += v[i].waitTime;
            avgTurnaroundTime += v[i].turnaroundTime;
        }
        avgWaitTime /= v.size();
        avgTurnaroundTime = v.size();
        cout << "Average Waiting Time = " << avgWaitTime << "\nAverage Turnaround time = " << avgTurnaroundTime << "\n";
    }
    
    void schedule(){
        if(q.empty()){
            cout << "Job underflow encountered\n";
            return;
        }
        
        Job curr;
        clock = q.top().arrivalTime;
        
        while(!q.empty() || !q2.empty()){
            if(q2.empty()){
                clock = q.top().arrivalTime;
                q2.push(q.top());
                q.pop();
            }
            curr = q2.top();
            display(curr);
            if((!q.empty() && q.top().arrivalTime >= clock + curr.burstTime) || q.empty()){
                clock += curr.burstTime;
                curr.turnaroundTime = clock - curr.arrivalTime;
                curr.waitTime = curr.turnaroundTime - curr.totBurst;
                info.pb(curr);
                q2.pop();
            }
            else{
                auto d3 = q2.top();
                d3.burstTime -= q.top().arrivalTime - clock;
                q2.pop(); q2.push(d3);
                clock = q.top().arrivalTime;
                q2.push(q.top());
                q.pop();
            }
        }
        statisticalCounter(info);
    }

};


//--------------------- Round Robin --------------------------

/*
 Sample Input - Round Robin
 4
 0 5
 1 3
 2 8
 3 6
 */


class RoundRobin{
    vector<Job> job;
    list<Job> ready;
    ll timeQuantum;
    ll clock = 0;
    ll id = 0;
    vector<Job> info;
public:
    RoundRobin(ll n = 0):timeQuantum(n){}
    void insert(ll arrTime, ll burstTime){
        Job j;
        j.id = ++id;
        j.arrivalTime = arrTime;
        j.totBurst = j.burstTime = burstTime;
        job.pb(j);
    }
    
    void display(Job j){
        cout << "Job " << j.id << " in CPU\nClock: " << clock << "\n";
        cout << "Ready Queue\n";
        tr(it,ready.begin(),ready.end()){
            if(it->arrivalTime > clock || it->id == j.id) continue;
            cout << "ID: " << it->id << "\tArr. Time: " << it->arrivalTime << "\tRemaining CPU Burst Time: " << it->burstTime << "\n";
        }
        cout << "\n";
    }
    
    void statisticalCounter(){
        cout << "Statistical Counters\n";
        double avgWaitTime = 0;
        double avgTurnaroundTime = 0;
        fr(i,0,info.size()){
            cout << "ID: " << info[i].id << "\tWait time: " << info[i].waitTime << "\tTurnaround time: " << info[i].turnaroundTime << "\n";
            avgWaitTime += info[i].waitTime;
            avgTurnaroundTime += info[i].turnaroundTime;
        }
        avgWaitTime /= info.size();
        avgTurnaroundTime = info.size();
        cout << "Average Waiting Time = " << avgWaitTime << "\nAverage Turnaround time = " << avgTurnaroundTime << "\n";
    }
    
    
    void schedule(){
        if(job.empty()){ cout << "Job Underflow Encountered\n"; return;}
    
        sort(job.begin(),job.end(),compArrTime());
        fr(i,0,job.size()) ready.pb(job[job.size()-i-1]);
        clock = ready.front().arrivalTime;
        while(!ready.empty()){
            tr(it,ready.begin(),ready.end()){
                if(it->arrivalTime > clock || it->burstTime == 0) continue;
                display(*it);
                clock += (it->burstTime > timeQuantum?timeQuantum:it->burstTime);
                it->burstTime -= (it->burstTime > timeQuantum?timeQuantum:it->burstTime);
                if(it->burstTime == 0){
                    it->turnaroundTime = clock - it->arrivalTime;
                    it->waitTime = it->turnaroundTime - it->totBurst;
                    info.pb(*it);
                    auto it2 = --it; it++;
                    ready.erase(it);
                    it = it2;
                }
            }
        }
        
        statisticalCounter();
    }
 
};



// ----------------------------------------------------------------




int main(){
    
    ll n, arrTime, burstTime;
    RoundRobin RR(3);
    cin >> n;
    fr(i,0,n){
        cin >> arrTime >> burstTime;
        RR.insert(arrTime, burstTime);
    }
    RR.schedule();
    return 0;

}


