// a4_sort_implementations.h

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <put your full name here!>
// St.# : <put your full SFU student number here>
// Email: <put your SFU email address here>
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "a4_base.h"

using namespace std;

//
// Helper method to swap values in a vector
//
template <typename T>
void swap_vals(vector<T> &v, int a, int b)
{
    T tmp = v[a];
    v[a] = v[b];
    v[b] = tmp;
}

//
// Generates random integer between min and max
//
int rand_int(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

//
// Returns a vector of n randomly chosen ints, each <= max and >= min.
//
vector<int> rand_vec(int n, int min, int max)
{
    srand(time(NULL));

    vector<int> random_vector;
    for (int i = 0; i < n; i++)
    {
        int next = rand_int(max, min);
        random_vector.push_back(next);
    }
    return random_vector;
}

//
// Generates a vector of random ints
//
vector<int> make_rand_vector(int size, int min, int max)
{
    vector<int> v;
    for (int i = 0; i < size; i++)
    {
        v.push_back(rand_int(min, max));
    }
    return v;
}

//
// Helper method to check if a vector is sorted
// in non-decreasing order
template <typename T>
bool is_sorted(vector<T> &v)
{
    for (int i = 1; i < v.size(); i++)
    {
        if (v[i - 1] > v[i])
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

//
// Reusable insertion implementation
//

template <typename T>
void insertion_sort_impl(vector<T> &v, int low, int high, ulong &num_comps)
{
    for (int i = low + 1; i <= high; ++i)
    {
        T key = v[i];
        int j = i - 1;
        while (j >= low && (num_comps++, v[j] > key))
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
};

template <typename T>
SortStats insertion_sort(vector<T> &v)
{
    clock_t start = clock();
    ulong num_comps = 0;
    insertion_sort_impl(v, 0, v.size() - 1, num_comps);
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
    ulong num_comps = 0;
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
        swap_vals(v, i, minIdx);
    }

    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;

    return SortStats{"Selection sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
}

// ********************

template <typename T>
int merge(vector<T> &left, vector<T> &right, vector<T> &v)
{
    ulong num_comps = 0;
    int low = 0;
    int high = 0;
    int idx = 0;

    while (low < left.size() && high < right.size())
    {
        num_comps += 1;
        if (left[low] <= right[high])
        {
            v[idx] = left[low];
            low += 1;
        }
        else
        {
            v[idx] = right[high];
            high += 1;
        }
        idx += 1;
    }

    while (low < left.size())
    {
        v[idx] = left[low];
        low += 1;
        idx += 1;
    }

    while (high < right.size())
    {
        v[idx] = right[high];
        high += 1;
        idx += 1;
    }
    return num_comps;
}

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
}

template <typename T>
int partition(vector<T> &v, int low, int high, ulong &num_comps)
{
    T pivot = v[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        num_comps++;
        if (v[j] <= pivot)
        {
            i++;
            swap_vals(v, i, j);
        }
    }

    swap_vals(v, i + 1, high);
    return i + 1;
}

// Implementation for quicksort
// Needs to return a ulong, so implement
// recursive function in this helper function
template <typename T>
ulong quick_sort_impl(vector<T> &v, int low, int high)
{
    ulong num_comps = 0;
    if (low < high)
    {
        int pivot = partition(v, low, high, num_comps);
        num_comps += quick_sort_impl(v, low, pivot - 1);
        num_comps += quick_sort_impl(v, pivot + 1, high);
    }
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
void iquick_sort_impl(vector<T> &v, int low, int high, ulong &comparison_count)
{
    int threshold = 10;
    if (low < high)
    {
        if (high - low + 1 <= threshold)
        {
            insertion_sort_impl(v, low, high, comparison_count);
        }
        else
        {
            int pivot = partition(v, low, high, comparison_count);
            iquick_sort_impl(v, low, pivot - 1, comparison_count);
            iquick_sort_impl(v, pivot + 1, high, comparison_count);
        }
    }
}

template <typename T>
SortStats iquick_sort(vector<T> &v)
{
    clock_t start = clock();
    ulong num_comps = 0;
    iquick_sort_impl(v, 0, v.size() - 1, num_comps);
    clock_t end = clock();
    double elapsed_cpu_time_sec = double(end - start) / CLOCKS_PER_SEC;
    return SortStats{"IQuick sort",
                     v.size(),
                     num_comps,
                     elapsed_cpu_time_sec};
};
// See description in assignment.
