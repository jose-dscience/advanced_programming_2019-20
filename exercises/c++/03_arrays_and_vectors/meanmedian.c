#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

double mean(std::vector<double> data);
double median(std::vector<double> data);

int main(void)
{
	std::vector<double> temps{};
	std::ifstream infile;
	double t;

	infile.open("temperatures.txt");
	while(!infile.eof())
	{
		infile >> t;
		temps.push_back(t);
	}
	infile.close();

	std::cout << " +The mean is: " << mean(temps) << std::endl;
	std::cout << " +The median is: " << median(temps) << std::endl;

	return 0;
}

//function: mean; calculate the mean of a std::vector<double>
//INPUT:
//   +std::vector<double>, temps; vector which contains the data
//OUTPUT: double, mean of content of data vector
double mean(std::vector<double> data)
{
	double sum{0};

	for(double x : data)
		sum += x;
	sum = sum/data.size();

	return sum;
}

//function: median; calculate the median of a std::vector<double>
//INPUT:
//   +std::vector<double>, temps; vector which contains the data
//OUTPUT: double, median of content of data vector
double median(std::vector<double> data)
{
	std::sort(data.begin(), data.end());
	return data[data.size()/2];
}
