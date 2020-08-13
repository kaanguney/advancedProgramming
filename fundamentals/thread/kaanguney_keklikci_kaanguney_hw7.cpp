#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <mutex> // to keep the threads oredered
#include <thread>
#include <chrono> // for local time
#include <random>
#include <time.h>
#include <iomanip>
#include <ctime>

using namespace std;

int random_range(const int & min, const int & max) { // function taken from the hw document
	
	static mt19937 generator(time(0)); 
	uniform_int_distribution<int> distribution(min, max); 
	return distribution(generator); 
}

mutex myMutex;

int sum = 0, index = 0; // global variables to track threads

void add(int thread_id, int *dynamic_arr, int size, int start_range, int end_range) { // only thread function in the code

		this_thread::sleep_for (chrono::seconds(random_range(start_range, end_range)));

		while(index<size) {

			myMutex.lock();

			if(index<size) {
			
				time_t current = chrono::system_clock::to_time_t(chrono::system_clock::now()); // get current time

				struct tm *ptm = new struct tm;

				localtime_s(ptm, &current); // converted to localtime
			
				sum+=dynamic_arr[index];

				cout << "Thread " << thread_id <<  " added number index " << index << " to the total sum at " << put_time(ptm,"%X") << endl;

				cout << "Current sum: " << sum << endl;

				index++;
			}

			myMutex.unlock();

			this_thread::sleep_for (chrono::seconds(random_range(start_range, end_range)));
		}
}

int main() {

	string filename, line, word;

	int start_range, end_range; // in seconds 

	int size = 0; // array-size

	cout << "Please enter the file name." << endl;

	cin >> filename;

	ifstream input;

	input.open(filename.c_str()); // read the file here

	cout << "Please enter the wait range of threads." << endl;

	cin >> start_range >> end_range;

	cout << endl << endl; 
	
	// now, read the file

	while(getline(input, line)) { // count the line number with this loop...
	
		size++;
	}

	input.clear(); // to be able to read the file again for the array
	input.seekg(0);

	int * arr = new int[size]; // dynamic array created 

	// now, fill the array

	int iterator = 0;

	while(getline(input, line)) { // count the line number with this loop...
	
		istringstream iss(line);

		iss >> word;
		
		arr[iterator] = stoi(word); // convert to integer before storing
		
		iterator++;
	}

	input.clear();
	input.seekg(0); // just in case clear the errors and return to the beginning
	
	time_t current = chrono::system_clock::to_time_t(chrono::system_clock::now()); // get current time

    struct tm *ptm = new struct tm;

	localtime_s(ptm, &current); // converted to localtime

	cout << "Starting reading the array at " << put_time(ptm,"%X") << endl; // displays the current time
	
	cout << "Array stored in the memory. Starting the summation at " << put_time(ptm,"%X") << endl << endl;

	thread threads[5];
	for (int i=0; i<5; i++) {
		threads[i] = thread(&add, i+1, ref(arr), ref(size), ref(start_range), ref(end_range)); 
	}
	for (int i=0; i<5; i++) // join the threads at the end of execution to prevent early termination
		threads[i].join();
	cout << endl;

	time_t currentTime; // calculate localtime for output again

    struct tm *localTime;

    time( &currentTime );

    localTime = localtime( &currentTime );

	int Hour   = localTime->tm_hour;
    int Min    = localTime->tm_min;
    int Sec    = localTime->tm_sec;

	cout << "Adding finished at " << Hour << ":" << Min << ":" << Sec << endl;

	cout << "Sum: " << sum << endl;

	cin.get(); 
	cin.ignore(); 

	return 0;
}