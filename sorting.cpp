#include "sorting.h"


void merge(std::vector<Movie>& vec, int left, int mid, int right)
{
    int sub1 = mid - left + 1;
    int sub2 = right - mid;


    std::vector<Movie> L(sub1);
    std::vector<Movie> R(sub2);

    for (int i = 0; i < sub1; i++)
        L[i] = vec[left + i];
    for (int j = 0; j < sub2; j++)
        R[j] = vec[mid + 1 + j];

    int i = 0; //index of sub1
    int j = 0; //index of sub2
    int k = left; //index of merged vector
    while (i < sub1 && j < sub2)
    {
        if (L[i].rating <= R[j].rating)
        {
            vec[k] = L[i];
            i++;
        }
        else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < sub1)
    {
        vec[k] = L[i];
        i++;
        k++;
    }

    while (j < sub2)
    {
        vec[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(std::vector<Movie>& vec, int begin, int end)
{
    if (begin < end)
    {
        int mid = begin + (end - begin) / 2;
        mergeSort(vec, begin, mid);
        mergeSort(vec, mid + 1, end);
        merge(vec, begin, mid, end);
    }
}

int partition(std::vector<Movie> &vec, int begin, int end)
{
    Movie pivot = vec[end];
    int i = (begin - 1);

    for(int j = begin; j <= end; j++)
    {
        if(vec[j].rating < pivot.rating)
        {
            i++;
            Movie temp = vec[i];
            vec[i] = vec[j];
            vec[j] = temp;
        }
    }
    Movie temp = vec[i+1];
    vec[i+1] = vec[end];
    vec[end] = temp;
    return (i + 1);
}


void quickSort(std::vector<Movie> &vec, int begin, int end)
{
    if (end > begin )
    {
        int pivot = partition(vec, begin, end);
        quickSort(vec, begin, pivot-1);
        quickSort(vec, pivot + 1, end);
    }
}

void insertionSort(std::vector<Movie> &bucket)
{
    for (int i = 1; i < bucket.size(); i++)
    {
        Movie key = bucket[i];
        int j = i - 1;

        while (j >= 0 && bucket[j].rating > key.rating)
        {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

void bucketSort(std::vector<Movie>& vec, int n)
{
    std::vector<std::vector<Movie>> buckets(10);
    for (int i = 0; i < n; i++)
    {
        int index = static_cast<int>((vec[i].rating - 1) * n / 10);
        buckets[index].push_back(vec[i]);
    }


    for (int i = 0; i < buckets.size(); i++)
    {
        insertionSort(buckets[i]);
    }


    int k = 0;
    for (int i = 0; i < buckets.size(); ++i)
    {
        for (int j = 0; j < buckets[i].size(); ++j)
        {
            vec[k++] = buckets[i][j];
        }
    }
}
