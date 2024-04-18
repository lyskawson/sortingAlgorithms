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
void saveToFile(const std::vector<Movie> &vec, int numberOfItems, std::string sortType);
void runtTest(int n);
void sortMovies(std::vector<Movie> &movies, const std::string &sortType);
void shuffleVector(std::vector<Movie>& vec, int shuffle_passes, int shuffle_seed);

int main()
{
    std::string input_file_name = "../projekt2_dane.csv";
    int sort_key_pos = 3;
    int n_items = 5;
    std::string algo_name = "QUICK";
    int shuffle_passes = 10;
    int shuffle_seed = 0;

    std::vector<Movie> movies;
    movies = filterData(input_file_name, n_items);
    shuffleVector(movies, shuffle_passes, shuffle_seed);

    sortMovies(movies, algo_name);
    displayMovies(movies);
    std::cerr << "Average rating: " << average(movies) << std::endl;
    std::cerr << "Median rating: " << median(movies) << std::endl;

    return 0;
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
        std::string str_number;
        std::getline(stream, str_number, ','); //get number of movie
        int number = std::stoi(str_number);
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
                    movieVector.push_back({number, title , rating});
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
        std::cout << "No:" << movie.number << ", Title: " << movie.name << ", Rating: " << movie.rating << "\n";
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



void sortMovies(std::vector<Movie> &movies, const std::string &sortType)
{
    if (sortType == "QUICK")
    {
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(movies, 0, movies.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> duration = end - start;

        double timeInMicro = duration.count();
        std::string unit;
        double time;
        if (timeInMicro < 1000.0)
        {
            time = timeInMicro;
            unit = "us";
        }
        else if (timeInMicro >= 1000.0 && timeInMicro < 1000000.0)
        {
            time = timeInMicro/1000.0;
            unit = "ms";
        } else {
            time = timeInMicro/1000000.0;
            unit = "s";
        }
        std::cerr << "Time: " << std::fixed << std::setprecision(3) << time << " " << unit << std::endl;
    }
    else if (sortType == "MERGE")
    {
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(movies, 0, movies.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        double timeInMicro = duration.count();
        std::string unit;
        double time;
        if (timeInMicro < 1000.0)
        {
            time = timeInMicro;
            unit = "us";
        }
        else if (timeInMicro >= 1000.0 && timeInMicro < 1000000.0)
        {
            time = timeInMicro/1000.0;
            unit = "ms";
        } else {
            time = timeInMicro/1000000.0;
            unit = "s";
        }
        std::cerr << "Time: " << std::fixed << std::setprecision(3) << time << " " << unit << std::endl;
    }
    else if (sortType == "BUCKET")
    {
        auto start = std::chrono::high_resolution_clock::now();
        bucketSort(movies, movies.size());
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration = end - start;

        double timeInMicro = duration.count();
        std::string unit;
        double time;
        if (timeInMicro < 1000.0)
        {
            time = timeInMicro;
            unit = "us";
        }
        else if (timeInMicro >= 1000.0 && timeInMicro < 1000000.0)
        {
            time = timeInMicro/1000.0;
            unit = "ms";
        } else {
            time = timeInMicro/1000000.0;
            unit = "s";
        }
        std::cerr << "Time: " << std::fixed << std::setprecision(3) << time << " " << unit << std::endl;
    }
    else
    {
        std::cout << "Invalid sort type: " << sortType << std::endl;
    }
}

void shuffleVector(std::vector<Movie> &vec, int shuffle_passes = 0, int shuffle_seed = 0)
{
    if (shuffle_seed == 0)
        srand(time(NULL));
    else
        srand(shuffle_seed);


    for (int i = 0; i < shuffle_passes; ++i)
    {
        for (int j = 0; j < vec.size(); ++j)
        {
            int k = rand() % vec.size();
            std::swap(vec[j], vec[k]);
        }
    }
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
            bucketSort(sortedMovies, sortedMovies.size());
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

void saveToFile(const std::vector<Movie> &vec, int numberOfItems, std::string sortType)
{
    std::string name = "../sorted_" + std::to_string(numberOfItems);
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