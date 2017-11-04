#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <queue>
#include <vector>
using namespace std;

class Process
{
	public:
		Process()
		{
			pid = 0; arrival = 0; burst = 0;
		}
		int pid;
		int arrival;
		int burst;
};

class Process_data
{
    public:
        result()
        {
            waiting_time = 0; turnaround_time = 0; first_time_run = 0;
        }
        int waiting_time;
        int turnaround_time;
        bool first_time_run;
};

class compare_arrival
{
	public:
		bool operator() (const Process &a, const Process &b)
		{
			return a.arrival > b.arrival;
		}
};

class compare_burst
{
	public:
		bool operator() (const Process &a, const Process &b)
		{
			if(a.burst > b.burst) return true;
			else if(a.burst == b.burst)
				if(a.arrival > b.arrival) return true;
				else if(a.arrival == b.arrival)
					if(a.pid > b.pid) return true;
				return false;
		}
};

void SRTF(ifstream& infile, ofstream& outfile)
{
    int process_count = 0;
    int wttotal, tattotal;

    int numJob;
    infile >> numJob;

    priority_queue<Process, vector<Process>, compare_arrival> arriving;
    priority_queue<Process, vector<Process>, compare_burst> get_cpu;
    vector<Process_data> result;
    vector<Process> arriving1;

    cout << "Process\t   Waiting time\t   Turnaround time" << endl;
    outfile << "Process\t   Waiting time\t   Turnaround time" << endl;

	int i,j;
	for(i = 0; i < numJob; ++i)
	{
	    Process temp1;
	    temp1.pid = i + 1;
		infile >> temp1.arrival;
		arriving1.push_back(temp1);
	}
	for(i = 0; i < numJob; ++i)
    {
        infile >> arriving1[i].burst;
        arriving.push(arriving1[i]);
    }
    process_count = i;

    //ongoing process
    Process ongoing;
    int time;
    for(time = 0; (!get_cpu.empty() || !arriving.empty()); ++time)
    {
        while(!arriving.empty())
        {
            Process temp = arriving.top();
            if(temp.arrival <= time)
            {
                get_cpu.push(temp);
                arriving.pop();
            }
            else break;
        }

        ongoing = get_cpu.top();
        get_cpu.pop();
        --ongoing.burst;

        if(ongoing.burst == 0)
        {
            cout << "P[" << ongoing.pid << "]" << "\t\t" << time - ongoing.burst << "\t\t" << ((time+1) - ongoing.arrival) << endl;
            outfile << "P[" << ongoing.pid << "]" << "\t\t" << time - ongoing.burst << "\t\t" << ((time+1) - ongoing.arrival) << endl;
        }
        else get_cpu.push(ongoing);

        wttotal += time - ongoing.burst;
        tattotal += ((time+1) - ongoing.arrival);
    }

    if(ongoing.burst != 0)
    {
        cout << "P[" << ongoing.pid << "]" << "\t\t" << (time+1) - ongoing.arrival << "\t\t" << (time+1) + ongoing.burst << endl;
        outfile << "P[" << ongoing.pid << "]" << "\t\t" << (time+1) - ongoing.arrival << "\t\t" << (time+1) + ongoing.burst << endl;
    }

    /*
    //print to cmd
	cout << "Process\t   Waiting time\t   Turnaround time";
	cout << endl;
	//print to file
	outfile << "Process\t   Waiting time\t   Turnaround time";
	outfile << endl;

    for(i = 0; i < process_count; i++)
    {
        //print to cmd
        cout << "P[" << id[i] << "]" << "\t\t" <<  wt[i]  << "\t\t" <<  tat[i];
		cout << endl;
		//print to file
		outfile << "P[" << id[i] << "]" << "\t\t" <<  wt[i]  << "\t\t" <<  tat[i];
		outfile << endl;
    }*/

    float avwt, avtat;
    avwt = wttotal/process_count;
    avtat = tattotal/process_count;

    //print to cmd
	cout << "\nAverage Waiting time: " << avwt;
	cout	<< endl;
	cout << "Average Turnaround time: " << avtat;
	cout << endl;
	//print to file
	outfile << "\nAverage Waiting time: " << avwt;
	outfile	<< endl;
	outfile << "Average Turnaround time: " << avtat;
	outfile << endl;

	return;
}

int main()
{
	ifstream infile("Q3.txt");
	ofstream outfile;
	if(!infile.is_open())
	{
		cerr << "Failed to open file";
		return 1;
	}
	outfile.open("2-3.txt");
	SRTF(infile, outfile);

	infile.close();
	outfile.close();



    return 0;
}
