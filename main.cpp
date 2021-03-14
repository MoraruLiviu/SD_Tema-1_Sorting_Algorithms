#include <iostream>
#include <fstream>
#include <random>
#include <chrono>

using namespace std;
using namespace std::chrono;


int T;
int N;
int Max;




void Bubble_Sort(int a[], int n)
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


void Merge_Sort(int a[],int l,int r)
{
    if(l>=r)
    {
        return;
    }
    int m = l+ (r-l)/2;
    Merge_Sort(a,l,m);
    Merge_Sort(a,m+1,r);
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


void Quick_Sort(int a[], int l , int r)
{
	if (l < r)
	{
		int pi  = part(a, l, r);
		Quick_Sort(a, l, pi - 1);
		Quick_Sort(a, pi + 1, r);

	}
}


void Count_Sort(int a[], int n)
{

    int output[100000];
    int c[10];
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


void sortbydigit(int a[], int n, int exp)
{
    int output[n];
    int i, c[10] = { 0 };

    for (i = 0; i < n; i++)
        c[(a[i] / exp) % 10]++;

    for (i = 1; i < 10; i++)
        c[i] += c[i - 1];

    for (i = n - 1; i >= 0; i--)
    {
        output[c[(a[i] / exp) % 10] - 1] = a[i];
        c[(a[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++)
        a[i] = output[i];
}


void radixsort(int a[], int n)
{
    int m = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > m)
            m = a[i];

    for (int exp = 1; m / exp > 0; exp *= 10)
        sortbydigit(a, n, exp);
}


int* generate_numbers(int N, int Max)
{
    int* v = new int[N];
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

        if (N>100000){
            cout<<" Nu stiu de ce, dar programul meu de generare de array cu numere random imi da stack overflow la 10^6 elemente. \n";
            cout<<" Am tot incercat sa modific alocarea memoriei si nu stiu ce sa ii fac. Trebuia sa folosesc un vector? \n";
        }
        else
        {
        if (N>10000)
            cout<<" bubble sort e mult prea incet la array-uri mai mari de 10000. Sort was successful = 0"<<endl;
        else
        {
            p = generate_numbers(N,Max);

            auto start = high_resolution_clock::now();
            Bubble_Sort(p,N);
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(stop - start);

            cout<<" Bubble_Sort "<<duration.count()<<" microsecunde."<<" Sort was successful = "<<test_Sort(p, N)<<endl;

            delete [] p;
        }


        p = generate_numbers(N,Max);

        auto start = high_resolution_clock::now();
        Merge_Sort(p,0,N);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        cout<<" Merge_Sort "<<duration.count()<<" microsecunde."<<" Sort was successful = "<<test_Sort(p, N)<<endl;

        delete [] p;

        p = generate_numbers(N,Max);

        start = high_resolution_clock::now();
        Quick_Sort(p,0,N);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        cout<<" Quick_Sort "<<duration.count()<<" microsecunde."<<" Sort was successful = "<<test_Sort(p, N)<<endl;

        delete [] p;

        p = generate_numbers(N,Max);

        start = high_resolution_clock::now();
        Count_Sort(p,N);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        cout<<" Count_Sort "<<duration.count()<<" microsecunde."<<" Sort was successful = "<<test_Sort(p, N)<<endl;

        delete [] p;

        p = generate_numbers(N,Max);

        start = high_resolution_clock::now();
        radixsort(p,N);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        cout<<" Radix_Sort "<<duration.count()<<" microsecunde."<<" Sort was successful = "<<test_Sort(p, N)<<endl;

        delete [] p;

        }
    }

    Tests.close();

    return 0;
}
