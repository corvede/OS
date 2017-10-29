#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

class Process
{
	public:
		Process()
		{
			pid = 0;
			burst = 0;
		}
		friend istream& operator >> (istream &input, Process &process)
		{
			input >> process.pid;
			input >> process.burst;
			return input;
		}
		int pid;
		int burst;
} p[20];

void FCFS(ifstream& infile, ofstream& outfile)
{
	int process_count = 0;
	int job[20] = {0};
	int wt[20] = {0};
	int tat[20] = {0};
	int avwt = 0, avtat = 0;
	int time = 0, count = 0;

    int numJob;
    infile >> numJob;

    //vector<Process> myJob;

	int i;
	for(i = 0; i < numJob; i++)
	{
		//Process temp;
		infile >> job[i];
		//myJob.push_back(temp);
		//i++;
	}
	process_count = i;

	wt[0] = 0;
	for(i = 1; i < process_count; i++)
	{
		wt[i] = 0;
		for(int j = 0; j < i; j++)
		{
			wt[i] += job[j];
		}
	}

	outfile << "Process" << setw(10) << "Burst time" << setw(10) << "Waiting time" << setw(10) << "Turnaround time";
	outfile << endl;

	for(i = 0; i < process_count; i++)
	{
		tat[i] = job[i] + wt[i];
		avwt += wt[i];
		avtat += tat[i];
		outfile << "P["  << i+1 << "]" << setw(5) << job[i] << setw(5) << wt[i] << setw(5) << tat[i];
		outfile << endl;
	}

	avwt /= i;
	avtat /= i;
	outfile << "Average Waiting time: " << avwt;
	outfile << endl;
	outfile << "Average Turnaround time: " << avtat << endl;

	return;
}

int main()
{
	ifstream infile("Q1.txt");
	ofstream outfile;
	if(!infile.is_open())
	{
		cerr << "Failed to open file";
		return 1;
	}
	outfile.open("109.txt");
	FCFS(infile, outfile);

	infile.close();
	outfile.close();



    return 0;
}
