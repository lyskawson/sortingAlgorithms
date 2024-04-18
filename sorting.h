#ifndef PROJECT2_SORTING_H
#define PROJECT2_SORTING_H
#include <iostream>
#include <vector>



struct Movie {
    int number;
    std::string name;
    double rating;

    //bool operator<(Movie compared) { return (rating < compared.rating); }
    //bool operator>(Movie compared) { return (rating > compared.rating); }
};
//quickSort

void merge(std::vector<Movie>& vec, int begin, int mid, int end);
void quickSort(std::vector<Movie>& vec, int begin, int end);
void mergeSort(std::vector<Movie>& vec, int begin, int end);
void insertionSort(std::vector<Movie>& vec);
void bucketSort(std::vector<Movie>& vec, int n);


#endif //PROJECT2_SORTING_H
