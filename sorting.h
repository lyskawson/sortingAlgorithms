#ifndef PROJECT2_SORTING_H
#define PROJECT2_SORTING_H
#include <iostream>
#include <vector>

struct Movie {
    std::string text;
    double key;

    bool operator<(const Movie& compared) const
    {
        return key < compared.key;
    }
    bool operator>(const Movie& compared) const
    {
        return key > compared.key;
    }

};

void merge(std::vector<Movie> &vec, int begin, int mid, int end);
void mergeSort(std::vector<Movie> &vec, int begin, int end);
void bucketSort(std::vector<Movie> &vec, int bucketSize);
void threeWayPartition(std::vector<Movie> &vec, int begin, int end, int& i, int& j);
void quickSort(std::vector<Movie> &vec, int begin, int end);
void swap(Movie& movie1, Movie& movie2);
int partition(std::vector<Movie> &vec, int begin, int end);
void quickSortStandard(std::vector<Movie> &vec, int begin, int end);








#endif //PROJECT2_SORTING_H
