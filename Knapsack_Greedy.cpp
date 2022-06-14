#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include <chrono>
#include <tuple>
#include <string>
#include <math.h>


using namespace std;
using namespace std:: chrono;

bool comparator(const tuple<int, float, string> &a, const tuple<int, float, string> &b)
{
    return (get<1>(a) > get<1>(b));
}

int main()
{
	int job,t, maxt = 0;
	float p, maxp = 0;
	string name;
	vector<tuple<int, float, string> > v;

	cout<<"\n\tEnter the number of jobs to be done : ";
	cin>>job;

	for(int i = 0; i < job; i++)
	{
		cout<<"\n\tEnter the name of "<<i+1<<"th job : ";
		cin>>name;
		cout<<"\tEnter the profit and deadline of "<<name<<" : ";
		cin>>p>>t;
		v.push_back(make_tuple(t, p, name));

		if(t > maxt)
		maxt = t;
	}

	cout<<"\n\tDetails of the job you entered are : "<<endl;

	for(int i = 0; i < job; i++)
	{
		sleep(1);
		cout<<"\tJOB"<<i+1<<" =>  Name : "<<get<2>(v[i])<<", Profit = "<<get<1>(v[i])<<" and Deadline = "<<get<0>(v[i])<<endl;
	}
	sort(v.begin(), v.end(), comparator);

    vector<pair<int, string> > profit(maxt, make_pair(0, "NULL"));

    steady_clock::time_point t1 = steady_clock::now();
	for(int i = 0; i < job; i++)
	{
		for(int j = 1; j <= get<0>(v[i]); j++)
		{
			if(profit[get<0>(v[i]) - j].first == 0)
			{
				profit[get<0>(v[i]) - j].first = get<1>(v[i]);
				profit[get<0>(v[i]) - j].second = get<2>(v[i]);
				break;
			}
		}
	}
    steady_clock::time_point t2 = steady_clock::now();

    sleep(1);
    int j = 1;
    cout<<"\n\n\tJob sequence for maximum profit : "<<endl;

	for(int i = 0; i < maxt; i++)
	{
		if(profit[i].second != "NULL")
		{
			cout<<"\t"<<j<<"."<<profit[i].second;
			j++	;
		}
		maxp = maxp + profit[i].first;
	}
	sleep(1);
	cout<<"\n\n\tMaximum profit that can be earned = "<<maxp<<endl;

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    cout <<"\tSolving this job sequencing problem took me " << time_span.count() << " seconds.";
    cout << std::endl;

	return 0;
}

