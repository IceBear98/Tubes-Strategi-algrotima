#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>

using namespace std;
using namespace std:: chrono;

bool comparator(const pair<int, float> &a,
               const pair<int, float> &b)
{
    return (a.second > b.second);
}

int main()
{
	int n;             //jumlah barang
	float c, wtx, ptx;               //kapasitas knapsack yg dicapai
	vector<float> wt, pt;
	vector<pair<int, float> >vec;

    cout<<"Tool for test Job sequence problem"<<endl;
    cout<<"========================================== "<<endl;
	cout<<"nilai kapasitas yg di capai : ";
	cin>>c;
	cout<<"masukkan jumlah barang : ";
	cin>>n;

	for(int i = 0; i < n; i++)
	{
		cout<<"masukkan bobot dan nilai tiap barang : "<<i+1<<endl;
		cin>>wtx>>ptx;

		wt.push_back(wtx);
		pt.push_back(ptx);
		vec.push_back(make_pair(i, (pt.at(i)/wt.at(i)) ) );
	}

	sort(vec.begin(), vec.end(), comparator);

	int i = 0;
	float profit = 0, weight = 0;
	vector<float> fraction_x;

    steady_clock::time_point t1 = steady_clock::now();
	while(weight < c)    //Greedy algorithm
	{
		if(weight + wt.at(vec[i].first) <= c)
		{
			fraction_x.push_back(1);
			weight = weight + wt.at(vec[i].first);
		}
		else
		{
			float lastfill = (c - weight)/(wt.at(vec[i].first));
			fraction_x.push_back(lastfill);
			weight = c;
		}
		profit = profit + pt.at(vec[i].first)*fraction_x.at(i);
		i++;
	}
    steady_clock::time_point t2 = steady_clock::now();

	cout<<"\n\n\tMaximum profit yg dicapai "<<profit<<endl;

	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    cout <<"\t Time Complexity : " << time_span.count() << " seconds.";
    cout << std::endl;

	return 0;
}










