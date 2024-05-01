#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
#include <ctime>
#include <chrono>
using namespace std;

// Function to generate a random array of given size
vector<int> generateRandomArray(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; ++i) {
        arr[i] = rand() % 100;  // Generate random numbers between 0 and 99
    }
    return arr;
}
// Function to find the minimum value in an array using parallel reduction
int parallelMin(const std::vector<int>& arr) {
    int min_val = arr[0];
    #pragma omp parallel for reduction(min:min_val)

    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}
int sequentialMin(const std::vector<int>& arr) {
    int min_val = arr[0];
    
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }
    return min_val;
}

// Function to find the maximum value in an array using parallel reduction
int parallelMax(const std::vector<int>& arr) {
    int max_val = arr[0];
    #pragma omp parallel for reduction(max:max_val)
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}
int sequentialMax(const std::vector<int>& arr) {
    int max_val = arr[0];
    
    for (int i = 1; i < arr.size(); ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}
// Function to compute the sum of elements in an array using parallel reduction
int parallelSum(const std::vector<int>& arr) {
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < arr.size(); ++i) {
        sum += arr[i];
    }
    return sum;
}
int sequentialSum(const std::vector<int>& arr) {
    int sum = 0;
    
    for (int i = 0; i < arr.size(); ++i) {
        sum += arr[i];
    }
    return sum;
}

// Function to compute the average of elements in an array using parallel reduction
double parallelAverage(const std::vector<int>& arr) {
    int sum = parallelSum(arr);
    return static_cast<double>(sum) / arr.size();
}
double sequentialAverage(const std::vector<int>& arr) {
    int sum = sequentialSum(arr);
    return static_cast<double>(sum) / arr.size();
}


int main() {
    int size;
    cout << "Enter the number of elements in the array: ";
    cin >> size;

    // Generate a random array
    vector<int> arr = generateRandomArray(size);
    cout<<"Input array is : ";
    for(int i=0;i<arr.size();i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<"\n";
    // Finding minimum and maximum using parallel reduction
    auto start_time =chrono::high_resolution_clock::now();
    int min_val = parallelMin(arr);
    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end_time - start_time;
    cout << "Time taken by parallel min value function: " << duration.count() << " seconds" << endl;


    start_time = chrono::high_resolution_clock::now();
    int max_val = parallelMax(arr);
     end_time = chrono::high_resolution_clock::now();
     duration = end_time - start_time;
     cout << "Time taken by parallel max value function: " << duration.count() << " seconds" << endl;

    

     start_time = chrono::high_resolution_clock::now();
    int sum = parallelSum(arr);
     end_time = chrono::high_resolution_clock::now();
     duration = end_time - start_time;
     cout << "Time taken by parallelsun function: " << duration.count() << " seconds" << endl;


     start_time = chrono::high_resolution_clock::now();
    double average = parallelAverage(arr);
     end_time = chrono::high_resolution_clock::now();
     duration = end_time - start_time;
     cout << "Time taken by parallel average functions: " << duration.count() << " seconds" << endl;


    cout << "parallel Minimum value: " << min_val << endl;
    cout << "parallel Maximum value: " << max_val << endl;
    cout << "parallel Sum: " << sum << endl;
    cout << "parallel Average: " << average << endl;

    start_time = chrono::high_resolution_clock::now();
    int sequential_min_val = sequentialMin(arr);
    end_time = chrono::high_resolution_clock::now();
    duration = end_time - start_time;
    cout << "Time taken by sequential functions: " << duration.count() << " seconds" << endl;


     start_time = chrono::high_resolution_clock::now();
    int sequential_max_val = sequentialMax(arr);
    end_time = chrono::high_resolution_clock::now();
    duration = end_time - start_time;
    cout << "Time taken by sequential functions: " << duration.count() << " seconds" << endl;


     start_time = chrono::high_resolution_clock::now();
    int sequential_sum = sequentialSum(arr);
    end_time = chrono::high_resolution_clock::now();
    duration = end_time - start_time;
    cout << "Time taken by sequential functions: " << duration.count() << " seconds" << endl;


     start_time = chrono::high_resolution_clock::now();
    double sequential_average = sequentialAverage(arr);
    end_time = chrono::high_resolution_clock::now();
    duration = end_time - start_time;
    cout << "Time taken by sequential functions: " << duration.count() << " seconds" << endl;


    cout << "sequential Minimum value: " << sequential_min_val << endl;
    cout << "sequential Maximum value: " << sequential_max_val << endl;
    cout << "sequential Sum: " << sequential_sum << endl;
    cout << "sequential Average: " << sequential_average << endl;

    return 0;
}
// g++ -fopenmp Sorting.cpp -o Sorting