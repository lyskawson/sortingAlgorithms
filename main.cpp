#include "sorting.h"
#include <iterator>
#include <chrono>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>

std::vector<Movie> filterData(const std::string &filename, int n);
void displayMovies(const std::vector<Movie>& movies);
double average(const std::vector<Movie> &vec);
double median(std::vector<Movie> vec);
void saveToFile(const std::vector<Movie> &vec, int n, std::string sortType);
void runtTest(int n);

int main()
{
    runtTest(1000);


    std::vector<int> dataSize = { 10000, 100000, 500000, 1000000, 1010292 };


    /*for (int i = 0; i < 5; i++)
    {
        int n = dataSize[i];
        std::cout << "TEST " << i+1 << "/" << dataSize.size() << ": n = " << n << '\n';
        runtTest(n);
    }*/

    return 0;
}


void runtTest(int n)
{
    std::string filename = "../projekt2_dane.csv";
    std::vector<Movie> movies;
    movies =  filterData(filename, n);

    std::vector<std::string> sorts = { "merge", "quick", "intro"};

    for (const auto &sort : sorts)
    {
        std::vector<Movie> sortedMovies = movies;

        if(sort == "quick")
        {
            std::cout << "Quicksort: " << std::endl;

            auto start = std::chrono::high_resolution_clock::now();
            quickSort(sortedMovies, 0, sortedMovies.size()-1);
            displayMovies(sortedMovies);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;

            std::cout << "Sorting time: " << duration.count() << " ms\n";
            std::cout << "Average rating: " << average(movies) << std::endl;
            std::cout << "Median rating: " << median(movies) << std::endl;
            std::cout << std::endl;
        }
        else if(sort == "merge")
        {
            std::cout << "Mergesort: " << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            mergeSort(sortedMovies, 0, sortedMovies.size()-1);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << "Sorting time: " << duration.count() << " ms\n";
            std::cout << "Average rating: " << average(movies) << std::endl;
            std::cout << "Median rating: " << median(movies) << std::endl;
            std::cout << std::endl;
        }
        else if(sort == "intro")
        {
            std::cout << "Intrasort: " << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            hybridIntroSort(sortedMovies, 0, sortedMovies.size()-1);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;
            std::cout << "Sorting time: " << duration.count() << " ms\n";
            std::cout << "Average rating: " << average(movies) << std::endl;
            std::cout << "Median rating: " << median(movies) << std::endl;
            std::cout << std::endl;
        }
        else
        {
            std::cout << "No available sorting to sort the data" << std::endl;
            break;
        }

        saveToFile(sortedMovies,n, sort);


    }


}

std::vector<Movie> filterData(const std::string &filename, int n)
{
    std::vector<Movie> movieVector;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "Failed to open file: " << filename << std::endl;
        return movieVector;
    }

    std::string line;
    std::getline(file, line); //skip first line


    for (int i = 0; i < n && std::getline(file, line); ++i)
    {
        std::istringstream stream(line);
        std::string number;
        std::getline(stream, number, ','); //ignore number of movie
        std::string title;
        std::getline(stream, title, ','); //get title
        std::string str_rating;
        std::getline(stream, str_rating, ','); //get rating
        if (!str_rating.empty() )
        {
            std::istringstream stream_rating(str_rating);
            double rating;
            if (stream_rating >> rating)
            {
                if (rating > 0 && title != "")
                {
                    movieVector.push_back({title, rating});
                }
            }
        }
    }
    file.close();
    return movieVector;
}

void displayMovies(const std::vector<Movie>& movies)
{
    std::cout << "Movies:\n";
    for (const auto& movie : movies) {
        std::cout << "Title: " << movie.name << ", Rating: " << movie.rating << "\n";
    }
}

double median(std::vector<Movie> vec)
{
    if (vec.size() % 2 == 0)
        return (vec[vec.size() / 2 - 1].rating + vec[vec.size() / 2].rating) / 2.0;
    else
        return vec[vec.size() / 2].rating;
}

double average(const std::vector<Movie> &vec) {
    if (vec.empty())
    {
        return 0;
    }

    int sum = 0;
    for (const auto& movie : vec)
    {
        sum = sum + movie.rating;
    }
    double average = static_cast<double>(sum) / vec.size();
    return average;
}

void saveToFile(const std::vector<Movie> &vec, int n, std::string sortType)
{
    std::string name = "../sorted_" + std::to_string(n);
    std::ofstream file(name + "_" + sortType + "Sort.csv");
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << std::endl;
        return;
    }

    for (const auto& movie : vec)
    {
        file << "\"" << movie.name << "\"," << movie.rating << '\n';
    }

    file.close();
}



