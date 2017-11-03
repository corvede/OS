#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <algorithm>
#include <sstream>
#include <vector>
using namespace std;

class Process
{
	public:
		Process()
		{
			pid = 0;
			arrival = 0;
			burst = 0;
		}
		friend istream& operator >> (istream &input, Process &process)
		{
			input >> process.pid;
			input >> process.arrival;
			input >> process.burst;
			return input;
		}
		int pid;
		int arrival;
		int burst;
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
	float avwt, avtat;
	int time = 0;
	int temp;
	int total = 0, sum = 0;

    int numJob;
    infile >> numJob;

    vector<int> id;
    vector<Process> arrive;
    vector<Process> cpu;
    vector<int> wt;
    vector<int> tat;

	int i;
	for(i = 0; i < numJob; i++)
	{
	    Process temp1;
		infile >> temp1.arrival;
		arrive.push_back(Process(temp1));
	}
	for(i = 0; i < numJob; i++)
    {
        Process temp2;
        infile >> temp2.burst;
		cpu.push_back(Process(temp2));
		id.push_back(i+1);
		//cout << "P" << id[i] << " " << arrive[i].arrival << " " << cpu[i].burst << " " << endl;

    }
	process_count = i;

	//compare burst
	for(i = 0; i < process_count; i++)
	{
		for(int j = i + 1; j < process_count; j++)
		{
			if(cpu[i].burst > cpu[j].burst)
			{
                temp = cpu[i].burst;
                cpu[i].burst = cpu[j].burst;
                cpu[j].burst = temp;

                temp = arrive[i].arrival;
                arrive[i].arrival = arrive[j].arrival;
                arrive[j].arrival = temp;

                temp = id[i];
                id[i] = id[j];
                id[j] = temp;
			}
		}
		cout << "P" << id[i] << " " << arrive[i].arrival << " " << cpu[i].burst << " " << endl;
	}

    //calculate waiting time
    cout << "----------" << endl;
	wt.push_back(0);
	for(i = 1; i < process_count; i++)
	{
	    sum += cpu[i-1].burst;
	    wt[i] = sum - arrive[i].arrival;
	    total += wt[i];
	}


	avwt = (float)total/process_count;
	total = 0;

    //calculate turnaround time
    sum = 0;
    tat.push_back(0);
	for(i = 0; i < process_count; i++)
	{
        sum += cpu[i].burst;
		tat[i] = sum - arrive[i].arrival;
		total += tat[i];
	}
	avtat = (float)total/process_count;

    //print to cmd
	cout << "Process\t   Waiting time\t   Turnaround time";
	cout << endl;
	//print to file
	outfile << "Process\t   Waiting time\t   Turnaround time";
	outfile << endl;

	for(i = 0; i < process_count; i++)
    {
        for(int j = i + 1; j < process_count; j++)
        {
            if(id[i] > id[j])
            {
                temp = wt[i];
                wt[i] = wt[j];
                wt[j] = temp;

                temp = tat[i];
                tat[i] = tat[j];
                tat[j] = temp;

                temp = id[i];
                id[i] = id[j];
                id[j] = temp;
            }
        }
    }

    for(i = 0; i < process_count; i++)
    {
        //print to cmd
        cout << "P[" << id[i] << "]" << "\t\t" <<  wt[i]  << "\t\t" <<  tat[i];
		cout << endl;
		//print to file
		outfile << "P[" << id[i] << "]" << "\t\t" <<  wt[i]  << "\t\t" <<  tat[i];
		outfile << endl;
    }

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
