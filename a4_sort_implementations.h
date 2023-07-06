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
void swapValues(int i, int j, vector<T> &v)
{
    T tmp = v[i];
    v[i] = v[j];
    v[j] = tmp;
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
ulong insertion_sort_impl(vector<T> &v, int low, int high)
{

    ulong num_comps = 0;
    for (int i = low; i < high; i++)
    {
        int j = i;
        while (j > 0 && (num_comps++, v[j - 1] > v[j]))
        {

            swapValues(j - 1, j, v);
            j--;
        }
    }
    return num_comps;
}

template <typename T>
SortStats insertion_sort(vector<T> &v)
{
    clock_t start = clock();
    ulong num_comps = insertion_sort_impl(v, 0, v.size());

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

    for (int i = 0; i < v.size(); i++)
    {
        int minIdx = i;
        for (int j = i + 1; j < v.size(); j++)
        {
            num_comps++;
            if (v[j] < v[minIdx])
            {
                minIdx = j;
            }
        }
        // Swap min IDX to its correct position at i
        swapValues(i, minIdx, v);
    }

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Selection sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
};

template <typename T>
int merge(vector<T> &left, vector<T> &right, vector<T> &v)
{
    ulong num_comps = 0;
    int l = 0;
    int r = 0;
    int idx = 0;

    while (l < left.size() && r < right.size())
    {
        num_comps += 1;
        if (left[l] <= right[r])
        {
            v[idx] = left[l];
            l += 1;
        }
        else
        {
            v[idx] = right[r];
            r += 1;
        }
        idx += 1;
    }

    while (l < left.size())
    {
        v[idx] = left[l];
        l += 1;
        idx += 1;
    }

    while (r < right.size())
    {
        v[idx] = right[r];
        r += 1;
        idx += 1;
    }
    return num_comps;
}

// Helper methods for MergeSort
template <typename T>
ulong merge_sort_impl(vector<T> &v)
{
    ulong num_comps = 0;

    if (v.size() <= 1)
    {
        return num_comps;
    }

    //
    // Find the mid point of the vector
    // Create two new vectors to hold each half
    //
    int mid = v.size() / 2;
    vector<T> left(v.begin(), v.begin() + mid);
    vector<T> right(v.begin() + mid, v.end());
    num_comps += merge_sort_impl(left);
    num_comps += merge_sort_impl(right);
    num_comps += merge(left, right, v);
    return num_comps;
}

template <typename T>
SortStats merge_sort(vector<T> &v)
{
    clock_t start = clock();
    ulong num_comps = merge_sort_impl(v);
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    return SortStats{"Merge sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
};

template <typename T>
int partition(vector<T> &v, int low, int high, ulong &num_comps)
{
    T p = v[high];
    int i = low;
    for (int j = low; j < high; j++)
    {
        if (v[j] < p)
        {
            swapValues(i, j, v);
            num_comps++;
            i++;
        }
    }
    swapValues(i, high, v);
    return i;
}

template <typename T>
ulong quick_sort_impl(vector<T> &v, int l, int h)
{
    ulong num_comps = 0;
    if (l >= h)
    {
        return 0;
    }
    int pivot = partition(v, l, h, num_comps);
    num_comps += quick_sort_impl(v, l, pivot - 1);
    num_comps += quick_sort_impl(v, pivot + 1, h);
    return num_comps;
}

template <typename T>
SortStats quick_sort(vector<T> &v)
{
    clock_t start = clock();
    ulong num_comps = quick_sort_impl(v, 0, v.size() - 1);

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    return SortStats{"Quick sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}

template <typename T>
SortStats shell_sort(vector<T> &v)
{
    clock_t start = clock();
    ulong num_comps = 0;
    for (int interval = v.size() / 2; interval > 0; interval /= 2)
    {
        for (int i = interval; i < v.size(); i++)
        {
            T tmp = v[i];
            int j;
            for (j = i; j >= interval && v[j - interval] > tmp; j -= interval)
            {
                v[j] = v[j - interval];
                num_comps++;
            }
            v[j] = tmp;
        }
    }

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    return SortStats{"Shell sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}

template <typename T>
ulong iquick_sort_impl(vector<T> &v, int low, int high)
{
    ulong num_comps = 0;
    if (high - low < 6)
    {
        num_comps += insertion_sort_impl(v, low, high);
    }
    else
    {

        int pivot = partition(v, low, high, num_comps);
        num_comps += iquick_sort_impl(v, low, pivot - 1);
        num_comps += iquick_sort_impl(v, pivot + 1, high);
    }

    return num_comps;
}

template <typename T>
SortStats iquick_sort(vector<T> &v)
{
    clock_t start = clock();

    ulong num_comps = iquick_sort_impl(v, 0, v.size());
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    return SortStats{"IQuick sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
};
// See description in assignment.

//
//  Generates a random number
//  bwetween max and min
//
int rand_int(int max, int min)
{
    return rand() % (max - min + 1) + min;
}

//
// Returns a vector of n randomly chosen ints, each <= max and >= min.
//
vector<int> rand_vec(int n, int min, int max)
{
    vector<int> random_vector;
    for (int i = 0; i < n; i++)
    {
        int next = rand_int(max, min);
        random_vector.push_back(next);
    }
    return random_vector;
}

//
// Put the implementations of all the functions listed in a3_base.h here.
//
