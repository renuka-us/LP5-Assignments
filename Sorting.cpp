#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <chrono>
#include <random>
using namespace std;

void bubble(int *, int);
void parallel_bubble(int *, int);
void swap(int &, int &);
void mergesort(int a[], int i, int j);
void parallel_mergesort(int a[], int i, int j);
void merge(int a[], int i1, int j1, int i2, int j2);

void generateRandomArray(int arr[], int size, int seed)
{
    // Create a random number generator engine with the given seed

    mt19937 rng(seed);
    // Create a uniform distribution for random integers
    uniform_int_distribution<int> dist(1, 1000);
    // Generate random numbers and fill the array
    for (int i = 0; i < size; ++i)
    {
        arr[i] = dist(rng);
    }
}

void mergesort(int a[],int i,int j)
{
	int mid;
	if(i<j)
	{
    	mid=(i+j)/2;
   	 
    	
    	{

        	
        	{
            	mergesort(a,i,mid);   	 
        	}

        	
        	{
            	mergesort(a,mid+1,j);    
        	}
    	}
         
            {
                	merge(a,i,mid,mid+1,j);    
            }

}
}
void parallel_mergesort(int a[],int i,int j)
{
	int mid;
	if(i<j)
	{
    	mid=(i+j)/2;
   	 
    	#pragma omp parallel sections
    	{

        	#pragma omp section
        	{
            	mergesort(a,i,mid);   	 
        	}

        	#pragma omp section
        	{
            	mergesort(a,mid+1,j);    
        	}
    	}
             #pragma omp barrier
            {
                	merge(a,i,mid,mid+1,j);    
            }

}
}
 
void merge(int a[],int i1,int j1,int i2,int j2)
{
	int temp[1000];    
	int i,j,k;
	i=i1;    
	j=i2;    
	k=0;
    
	while(i<=j1 && j<=j2)    
	{
    	if(a[i]<a[j])
    	{
        	temp[k++]=a[i++];
    	}
    	else
    	{
        	temp[k++]=a[j++];
        }    
	}
    
	while(i<=j1)    
	{
    	temp[k++]=a[i++];
	}
   	 
	while(j<=j2)    
	{
    	temp[k++]=a[j++];
	}
   	 
	for(i=i1,j=0;i<=j2;i++,j++)
	{
    	a[i]=temp[j];
	}    
}


void bubble(int *a, int n)
{

    for (int i = 0; i < n; i++)
    {
        int first = i % 2;
        for (int j = first; j < n - 1; j += 2)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}
void parallel_bubble(int *a, int n)
{

    for (int i = 0; i < n; i++)
    {
        int first = i % 2;
#pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void swap(int &a, int &b)
{
    int test;
    test = a;
    a = b;
    b = test;
}

int main()
{


    int n,  a[n],b[n],c[n],d[n], seed = 20;
    cout << "\n enter total no of elements=>";
    cin >> n;

    generateRandomArray(a, n, seed);
    auto start = chrono::high_resolution_clock::now();
    bubble(a, n);
    auto end = std::chrono::high_resolution_clock::now();
    cout << endl;

    // Calculate the duration
    chrono::duration<double> duration = end - start;
    cout << "\n sorted array is=>  ";
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << "  ";
    }
    // Print the duration
    cout << "Time taken by Sequential Bubble sort:  " << duration.count() << " seconds" << endl;



    generateRandomArray(b, n, seed);
    start = chrono::high_resolution_clock::now();
    parallel_bubble(b, n);
    end = std::chrono::high_resolution_clock::now();
    cout << endl;

    // Calculate the duration
    duration = end - start;
    cout << "\n sorted array is=>  ";
    for (int i = 0; i < n; i++)
    {
        cout << b[i] << "  ";
    }
    // Print the duration
    cout << "Time taken by Parallel Bubble sort:  " << duration.count() << " seconds" << endl;


    generateRandomArray(d, n, seed);
    start = chrono::high_resolution_clock::now();
    parallel_mergesort(d, 0, n-1);
    end = std::chrono::high_resolution_clock::now();
    cout << endl;

    // Calculate the duration
    duration = end - start;
    cout << "\n sorted array is=>  ";
    for (int i = 0; i < n; i++)
    {
        cout << d[i] << "  ";
    }
    // Print the duration
    cout << "Time taken by Parallel Merge sort:  " << duration.count() << " seconds" << endl;

  
cout<<"Merge Sort--->>>>>>>>>";
    generateRandomArray(c, n, seed);
cout<<"Merge array Sort--->>>>>>>>>";
    
    start = chrono::high_resolution_clock::now();
    mergesort(c, 0, n-1);
    end = std::chrono::high_resolution_clock::now();
    cout << endl;
cout<<"Merge end-->>>>>";
    // Calculate the duration
    duration = end - start;
    cout << "\n sorted array is=>  ";
    for (int i = 0; i < n; i++)
    {
        cout << c[i] << "  ";
    }
    // Print the duration
    cout << "Time taken by Sequential Merge sort:  " << duration.count() << " seconds" << endl;



    return 0;
}
