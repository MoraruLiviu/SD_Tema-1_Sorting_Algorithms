#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;


int T;
int N;
int Max;
int v[1000000];



void bubble_sort(int a[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (a[j] > a[j + 1])
			{
				swap(a[j], a[j + 1]);
			}
		}
	}
}


void Merge(int a[], int l, int r)
{
    int m = l + (r-l)/2;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            a[k] = L[i];
            i++;
        }
        else
        {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        a[k] = R[j];
        j++;
        k++;
    }
}


void MergeSort(int a[],int l,int r)
{
    if(l>=r)
    {
        return;
    }
    int m = l+ (r-l)/2;
    MergeSort(a,l,m);
    MergeSort(a,m+1,r);
    Merge(a,l,r);
}


int part(int a[], int l, int r)
{
	int pivot = a[r];
	int i = l - 1;


	for (int j = l; j < r ; j++)
	{
		if (a[j] < pivot)
		{
			swap(a[++i], a[j]);
		}
	}

	swap(a[++i], a[r]);

	return i;
}



void quickSort(int a[], int l , int r)
{
	if (l < r)
	{
		int pi  = part(a, l, r);
		quickSort(a, l, pi - 1);
		quickSort(a, pi + 1, r);

	}
}



void countSort(int a[], int n)
{

    int output[100000];
    int c[100000];
    int maxim = a[0];

    for (int i = 1; i < n; i++)
    {
        if (a[i] > maxim)
            maxim = a[i];
    }

    for (int i = 0; i <= maxim; ++i)
        c[i] = 0;

    for (int i = 0; i < n; i++)
        c[a[i]]++;

    for (int i = 1; i <= maxim; i++)
        c[i] += c[i - 1];


    for (int i = n - 1; i >= 0; i--)
    {
        output[c[a[i]] - 1] = a[i];
        c[a[i]]--;
    }

    for (int i = 0; i < n; i++)
        a[i] = output[i];
}



int* generate_numbers(int N, int Max)
{
    //static int v[1000000];
    // cod luat de la: https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
    // rand() are limita la 32767
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, Max);

    for (int n = 0; n<N; n++)
    {
        v[n] = distrib(gen);
    }
    return v;
}

bool test_Sort(int p[],int N)
{
    for (int i=0; i<N-1; i++)
    {
        if (p[i]>p[i+1])
            return false;
    }
    return true;
}

int main()
{
    ifstream Tests("teste.txt");

    Tests>>T;

    for (int t=0;t<T;t++)
    {
        Tests>>N>>Max;
        cout<<"\nN= "<<N<<" Max="<<Max<<"\n\n";

        int* p;

        if (N>10000)
            cout<<" bubble sort e mult prea incet la array-uri mai mari de 10000. Sort was successful = 0"<<endl;
        else
        {
            p = generate_numbers(N,Max);

            auto start = high_resolution_clock::now();
            bubble_sort(p,N);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            cout<<" bubble_sort "<<duration.count()<<" microsecunde."<<" Sort was successful = "<<test_Sort(p, N)<<endl;
        }


        p = generate_numbers(N,Max);

        auto start = high_resolution_clock::now();
        MergeSort(p,0,N);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout<<" merge_sort "<<duration.count()<<" microsecunde."<<" Sort was successful = "<<test_Sort(p, N)<<endl;


        p = generate_numbers(N,Max);

        start = high_resolution_clock::now();
        quickSort(p,0,N);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        cout<<" quick_sort "<<duration.count()<<" microsecunde."<<" Sort was successful = "<<test_Sort(p, N)<<endl;


        p = generate_numbers(N,Max);

        start = high_resolution_clock::now();
        countSort(p,N);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        cout<<" count_sort "<<duration.count()<<" microsecunde."<<" Sort was successful = "<<test_Sort(p, N)<<endl;


    }


    Tests.close();

    return 0;
}
