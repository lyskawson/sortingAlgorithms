#ifndef PROJECT2_SORTING_H
#define PROJECT2_SORTING_H
#include <iostream>
#include <vector>



struct Movie {
    std::string name;
    double rating;
    bool operator<(Movie compared) { return (rating < compared.rating); }
    bool operator>(Movie compared) { return (rating > compared.rating); }
};
//quickSort

void mergeSort(std::vector<Movie>& arr, int l, int r);
void quickSort(std::vector<Movie>& arr, int l, int r);
void hybridIntroSort(std::vector<Movie>& arr, int l, int r);


#endif //PROJECT2_SORTING_H
