#include "sorting.h"

void merge(std::vector<Movie>& vec, int begin, int mid, int end)
{
    int sub1 = mid - begin + 1;
    int sub2 = end - mid;


    std::vector<Movie> left(sub1);
    std::vector<Movie> right(sub2);

    for (int i = 0; i < sub1; i++)
        left[i] = vec[begin + i];
    for (int j = 0; j < sub2; j++)
        right[j] = vec[mid + 1 + j];

    int i = 0; //index of sub1
    int j = 0; //index of sub2
    int k = begin; //index of merged vector
    while (i < sub1 && j < sub2)
    {
        if (left[i].key <= right[j].key)
        {
            vec[k] = left[i];
            i++;
        }
        else {
            vec[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < sub1)
    {
        vec[k] = left[i];
        i++;
        k++;
    }

    while (j < sub2)
    {
        vec[k] = right[j];
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

void bucketSort(std::vector<Movie> &vec, int numBuckets)
{
    if (vec.empty())
        return;


    double minKey = vec[0].key;
    double maxKey = vec[0].key;
    for (const Movie& movie : vec)
    {
        if (movie.key < minKey)
        {
            minKey = movie.key;
        }
        if (movie.key > maxKey)
        {
            maxKey = movie.key;
        }
    }


    std::vector<std::vector<Movie>> buckets(numBuckets);
    double range = (maxKey - minKey) / numBuckets;


    for (const Movie &movie : vec)
    {
        int bucketIndex = int((movie.key - minKey) / range);
        if (bucketIndex == numBuckets)
        {
            bucketIndex--;
        }
        buckets[bucketIndex].push_back(movie);
    }


    int idx = 0;
    for (std::vector<Movie>& bucket : buckets)
    {
        std::sort(bucket.begin(), bucket.end(), [](const Movie& a, const Movie& b){return a.key < b.key;});

        for (const Movie& movie : bucket)
        {
            vec[idx++] = movie;
        }
    }
}

int partition(std::vector<Movie>& vec, int start, int end)
{
    double pivot = vec[start + (end - start) / 2].key;
    int left = start, right = end;

    while (left <= right)
    {

        while (vec[left].key < pivot)
            left++;


        while (vec[right].key > pivot)
            right--;


        if (left <= right)
        {
            swap(vec[left], vec[right]);
            left++;
            right--;
        }
    }

    return left;
}



void quickSortStandard(std::vector<Movie>& vec, int begin, int end) 
{
    if (begin < end)
    {
        int pivot = partition(vec, begin, end);
        quickSortStandard(vec, begin, pivot - 1 );
        quickSortStandard(vec, pivot + 1, end);
    }
}



void swap(Movie& movie1, Movie& movie2)
{
    Movie temp = movie1;
    movie1 = movie2;
    movie2 = temp;
}


void threeWayPartition(std::vector<Movie> &vec, int begin, int end, int& i, int& j)
{
    if (end - begin <= 1)
    {
        if (vec[end].key < vec[begin].key)
            swap(vec[end], vec[begin]);
        i = begin;
        j = end;
        return;
    }

    int mid = begin;
    double pivot = vec[end].key;
    while (mid <= end)
    {
        if (vec[mid].key < pivot)
            swap(vec[begin++], vec[mid++]);
        else if (vec[mid].key == pivot)
            mid++;
        else if (vec[mid].key > pivot)
            swap(vec[mid], vec[end--]);
    }

    i = begin - 1;
    j = mid;
}

void quickSort(std::vector<Movie> &vec, int begin, int end)
{
    if (begin < end)
    {
        int i, j;
        threeWayPartition(vec, begin, end, i, j);
        quickSort(vec, begin, i);
        quickSort(vec, j, end);
    }
}



