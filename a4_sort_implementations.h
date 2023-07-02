// a4_sort_implementations.h

#pragma once

#include "a4_base.h"

using namespace std;

template <typename T>
bool is_sorted(vector<T> &v)
{
    if (v.size() == 0)
    {
        return true;
    }
    for (int i = 0; i < v.size() - 1; i++)
    {
        if (v[i] > v[i + 1])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
SortStats bubble_sort(vector<T> &v)
{
    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();

    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v.size() - 1; j++)
        {
            num_comps++; // <--- num_comps is incremented here
            if (v[j] > v[j + 1])
            {
                T temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Bubble sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}

template <typename T>
SortStats insertion_sort(vector<T> &v)
{

    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();

    for (int i = 0; i < v.size(); i++)
    {
        T cur = v[i];
        int j = i - 1;
        while (j >= 0 && (v[j] > cur))
        {
            v[j + 1] = v[j];
            j--;
            num_comps++;
        }
        v[j + 1] = cur;
    }
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Insertion sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
};

template <typename T>
SortStats selection_sort(vector<T> &v)
{

    ulong num_comps = 0; // <--- num_comps is initialized to 0 here
    clock_t start = clock();

    int minIdx;
    for (int i = 0; i < v.size(); i++)
    {
        minIdx = i;
        for (int j = i + 1; j < v.size(); j++)
        {
            if (v[j] < v[i])
            {
                minIdx = j;
            }
        }
        // Swap min IDX to its correct position at i
        T tmp = v[i];
        v[i] = v[minIdx];
        v[minIdx] = tmp;
    }
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Selection sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
};

template <typename T>
SortStats merge_sort(vector<T> &v)
{
    return SortStats{"Insertion sort",
                     v.size(),
                     0,
                     0};
};

template <typename T>
SortStats quick_sort(vector<T> &v)
{
    return SortStats{"Insertion sort",
                     v.size(),
                     0,
                     0};
}

template <typename T>
SortStats shell_sort(vector<T> &v)
{
    return SortStats{"Insertion sort",
                     v.size(),
                     0,
                     0};
}

template <typename T>

SortStats iquick_sort(vector<T> &v)
{
    return SortStats{"Insertion sort",
                     v.size(),
                     0,
                     0};
};
// See description in assignment.

//
// Returns a vector of n randomly chosen ints, each <= max and >= min.
//
vector<int> rand_vec(int n, int min, int max)
{
    cout << n << min << max << endl;
    vector<int> vect;
    return vect;
}

//
// Put the implementations of all the functions listed in a3_base.h here.
//