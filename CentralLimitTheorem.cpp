#include <iostream>
#include "boost\random.hpp"
#include <ctime>			// std::time
#include <boost/Random/detail/const_mod.hpp> // LCG class
#include <boost/math/distributions.hpp> // For non-member functions of distributions
#include <map>
#include <string>
#include "UtilitiesDJD/VectorsAndMatrices/Vector.cpp"
#include "UtilitiesDJD/ExcelDriver/ExcelMechanisms.hpp"
#include "UtilitiesDJD/Geometry/Range.cpp"
#include "UtilitiesDJD/ExceptionClasses/DatasimException.hpp"
#include <iostream>
#include <vector>

using namespace std;

// Demonstrates the Central Limit Theorem (I did this for fun)

int main()
{
	// Throwing dice
	// Mersenne Twister
	boost::random::mt19937 myRng;

	// Set the seed
	myRng.seed(static_cast<boost::uint32_t> (std::time(0)));

	// Uniform in range [1, 6]
	boost::random::discrete_distribution<int> dice{ 2 , 1 , 2, 3, 6, 5 }; // weights of rigged die ( 6 outcomes)

	int outcome = 0; // Current outcome 

	int sampleSize;
	cout << "How large would like each sample size to be?" << endl; cin >> sampleSize;
	int num_trials;
	cout << "How many trials would you like to do? " << endl; cin >> num_trials;
	vector<double> vec;
	vec.reserve(num_trials);
	long count = 0;
	int sum;

	while (count < num_trials)
	{
		count++;
		sum = 0;
		for (int i = 0; i < sampleSize; ++i)
		{
			outcome = dice(myRng); // This will generate a number in the range 
			sum += outcome;
		}
		vec.push_back((double)sum / (double)sampleSize);
	}

	Vector<double, long> Vec(61, 0.0);

	for (int j = 0; j < num_trials; ++j)
	{
		for (int i = 0; i < 61; ++i)
		{
			double d = (double)(i)* 0.1;
			if (vec[j] <= d)
			{
				Vec[i]++;
				break;
			}
		}
	}

	Vector<double, long> Abscissa(61, 0.0);
	for (int i = 0; i < 61; ++i)
	{
		Abscissa[i] = 0.1 * i;
	}

	for (int i = 0; i < 61; ++i)
	{
		cout << Abscissa[i] << "\t" << Vec[i] << endl;
	}

	try
	{
		printOneExcel(Abscissa, Vec, string("Distribution"), string("Value"), string("Frequency"));
	}
	catch (DatasimException& e)
	{
		e.print();
	}

	cout << "RYAN" << endl;

	return 0;
}
