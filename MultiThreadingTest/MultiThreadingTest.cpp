#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

int* diceArray = NULL;
bool multithread = false;

int NumberGenerator(int min, int max);
string RollDice(long long int count);
void GenerateArray(int start, int size);

int main()
{
	using std::chrono::high_resolution_clock;
	using std::chrono::duration_cast;
	using std::chrono::duration;
	using std::chrono::milliseconds;


	long long int takeCount;
	while(true)
	{
		cout << "Input ammount of dice to roll\n";
		cin >> takeCount;

		auto t1 = high_resolution_clock::now();

		cout << "Dice: " << RollDice(takeCount) << "\n";

		auto t2 = high_resolution_clock::now();
		duration<double, milli> ms_double = t2 - t1;
		cout << "Execution time: " << ms_double.count() << "ms\n";

		if (takeCount == 86)
		{
			system("CLS");
		}
		else if (takeCount == 5533)
		{
			multithread = !multithread;

			if (multithread)
			{
				cout << "Multithreading: ON\n";
			}
			else
			{
				cout << "Multithreading: OFF\n";
			}
		}
	}
}


int NumberGenerator(int min, int max) // generates a random number based on input parameters
{
	random_device rd;
	uniform_int_distribution<> distr(min, max);
	return distr(rd);
}

string RollDice(long long int count)
{
	string output;

	diceArray = new int[count];

	if (!multithread && count > 5)
	{
		for (int i = 0; i < count; i++)
		{
			diceArray[i] = NumberGenerator(1, 6);
		}
		output = "single Thread done (:";
	}
	else
	{
		int split = 0;
		int total = 0;
		split = count / 5;
		thread th1(GenerateArray, total, split);
		total += split;
		thread th2(GenerateArray, total, split);
		total += split;
		thread th3(GenerateArray, total, split);
		total += split;
		thread th4(GenerateArray, total, split);
		total += split;
		thread th5(GenerateArray, total, split);
		total += split;
		if (total < count)
		{
			GenerateArray(total, count - total);
		}
		th1.join();
		th2.join();
		th3.join();
		th4.join();
		th5.join();

		/*for (int i = 0; i < count; i++)
		{
			output += to_string(diceArray[i]) + " ";
		}*/
		output = "multithread done (:";
	}

	delete[] diceArray;
	return output;
}

void GenerateArray(int start, int size)
{
	for (int i = start; i < start + size; i++)
	{
		diceArray[i] = NumberGenerator(1, 6);
	}
}