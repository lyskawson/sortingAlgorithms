#include "sorting.h"
#include <iterator>
#include <chrono>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>

std::vector<Movie> filterData(const std::string &filename, int n,int sort_key_pos );
void displayMovies(const std::vector<Movie>& movies);
double average(const std::vector<Movie> &vec);
double median(std::vector<Movie> vec);
void sortMovies(std::vector<Movie> &movies, const std::string &sortType);
void shuffleVector(std::vector<Movie>& vec, int shuffle_passes, int shuffle_seed);
std::vector<Movie>loadDataFromStdin(int sort_key_pos);

int main(int argc, const char * argv[])
{
    if(argc < 5 )
    {
        std::cout << "Usage: ./prog input_file_name sort_key_pos n_items algo_name shuffle_passes shuffle_seed << std::endl";
        return 1;
    }
    std::string input_file_name = argv[1];
    int sort_key_pos = atoi(argv[2]);
    int n_items = atoi(argv[3]);
    std::string algo_name = argv[4];

    int shuffle_passes = 0;
    int shuffle_seed = 0;

    if (argc > 5)
        shuffle_passes = std::atoi(argv[5]);

    if (argc > 6)
        shuffle_seed = std::atoi(argv[6]);


    //std::string input_file_name = "../projekt2_dane_daszek.csv";
    //int sort_key_pos = 3;
    //int n_items = 1000000;
    //std::string algo_name = "BUCKET";
    //int shuffle_passes = 0;
    //int shuffle_seed = 0;

    std::vector<Movie> movies;
    if(input_file_name == "-")
        movies = loadDataFromStdin(sort_key_pos);
    else
        movies = filterData(input_file_name, n_items,sort_key_pos);

    shuffleVector(movies, shuffle_passes, shuffle_seed);
    sortMovies(movies, algo_name);
    displayMovies(movies);
    std::cerr << "Average: " << average(movies) << std::endl;
    std::cerr << "Median: " << median(movies) << std::endl;
    return 0;
}



std::vector<Movie> filterData(const std::string &filename, int n, int sort_key_pos) {
    std::vector<Movie> movieVector;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Failed to open file: " << filename << std::endl;
        return movieVector;
    }

    std::string line;
    std::getline(file, line); //skip first line

    for (int i = 0; i < n && std::getline(file, line); ++i)
    {
        std::istringstream stream(line);
        std::string token;
        int currentCol = 0;
        double key = 0;
        bool validKey = false;

        while (std::getline(stream, token, '^'))
        {
            if (currentCol == sort_key_pos-1)
            {
                std::istringstream tokenStream(token);
                tokenStream >> key;
                if (!tokenStream.fail())
                {
                    validKey = true;
                    break;  //  parsed the key, stop parsing
                }
                break;  //skip this line
            }
            currentCol++;
        }

        if (validKey)
        {

            movieVector.push_back({line, key});
        }
    }

    return movieVector;
}

void displayMovies(const std::vector<Movie>& movies)
{
    std::cout << "Movies:\n";
    for (const auto& movie : movies)
    {
        std::cout << movie.text << "\n";
    }
}

double median(std::vector<Movie> vec)
{
    if (vec.size() % 2 == 0)
        return (vec[vec.size() / 2 - 1].key + vec[vec.size() / 2].key) / 2.0;
    else
        return vec[vec.size() / 2].key;
}

double average(const std::vector<Movie> &vec) {
    if (vec.empty())
    {
        return 0;
    }

    int sum = 0;
    for (const auto& movie : vec)
    {
        sum = sum + movie.key;
    }
    double average = static_cast<double>(sum) / vec.size();
    return average;
}

void sortMovies(std::vector<Movie> &movies, const std::string &sortType)
{
    if (sortType == "MODIFIEDQUICK")
    {
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(movies, 0, movies.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::micro> duration = end - start;
        double timeInMicro = duration.count();

        double time;
        std::string unit;
        if (timeInMicro < 1000.0) {
            time = timeInMicro;
            unit = "us";
        } else if (timeInMicro < 1000000.0) {
            time = timeInMicro / 1000.0;
            unit = "ms";
        } else {
            time = timeInMicro / 1000000.0;
            unit = "s";
        }

        std::cerr << "Time: " << std::fixed << std::setprecision(3) << time << " " << unit << std::endl;
    }
    else if (sortType == "QUICK")
    {
        auto start = std::chrono::high_resolution_clock::now();
        quickSortStandard(movies, 0, movies.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::micro> duration = end - start;
        double timeInMicro = duration.count();

        double time;
        std::string unit;
        if (timeInMicro < 1000.0) {
            time = timeInMicro;
            unit = "us";
        } else if (timeInMicro < 1000000.0) {
            time = timeInMicro / 1000.0;
            unit = "ms";
        } else {
            time = timeInMicro / 1000000.0;
            unit = "s";
        }

        std::cerr << "Time: " << std::fixed << std::setprecision(3) << time << " " << unit << std::endl;
    }
    else if (sortType == "MERGE")
    {
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(movies, 0, movies.size() - 1);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::micro> duration = end - start;
        double timeInMicro = duration.count();

        double time;
        std::string unit;
        if (timeInMicro < 1000.0) {
            time = timeInMicro;
            unit = "us";
        } else if (timeInMicro < 1000000.0) {
            time = timeInMicro / 1000.0;
            unit = "ms";
        } else {
            time = timeInMicro / 1000000.0;
            unit = "s";
        }

        std::cerr << "Time: " << std::fixed << std::setprecision(3) << time << " " << unit << std::endl;
    }
    else if (sortType == "BUCKET")
    {
        auto start = std::chrono::high_resolution_clock::now();
        bucketSort(movies, 1000);
        auto end = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double, std::micro> duration = end - start;
        double timeInMicro = duration.count();

        double time;
        std::string unit;
        if (timeInMicro < 1000.0) {
            time = timeInMicro;
            unit = "us";
        } else if (timeInMicro < 1000000.0) {
            time = timeInMicro / 1000.0;
            unit = "ms";
        } else {
            time = timeInMicro / 1000000.0;
            unit = "s";
        }

        std::cerr << "Time: " << std::fixed << std::setprecision(3) << time << " " << unit << std::endl;
    }
    else
    {
        std::cout << "Invalid sort type: " << sortType << std::endl;
    }
}

void shuffleVector(std::vector<Movie> &vec, int shuffle_passes, int shuffle_seed)
{
    std::mt19937 rng;
    if (shuffle_seed == 0)
        rng.seed(std::random_device()());
    else
        rng.seed(shuffle_seed);

    std::uniform_int_distribution<int> dist(0, vec.size() - 1);
    for (int i = 0; i < shuffle_passes; ++i)
    {
        for (int j = 0; j < vec.size(); ++j)
        {
            int k = dist(rng);
            std::swap(vec[j], vec[k]);
        }
    }
    std::cerr << "Seed: " << dist(rng) << std::endl;
}

std::vector<Movie> loadDataFromStdin(int sort_key_pos)
{
    std::vector<Movie> movieVector;
    std::string line;
    std::cout << "Enter movie data lines, '^' as delimiter, enter 'exit' to stop:" << std::endl;

    while (getline(std::cin, line)) {
        if (line.empty()) continue; // Ignore empty lines

        if (line == "exit")
        {
            break;
        }

        std::istringstream stream(line);
        std::string token;
        int currentCol = 0;
        double key = 0;
        bool validKey = false;

        while (std::getline(stream, token, '^'))
        {
            if (currentCol == sort_key_pos-1) {
                std::istringstream tokenStream(token);
                if (tokenStream >> key) {
                    validKey = true;
                    break;
                }
            }
            currentCol++;
        }

        if (validKey)
        {
            movieVector.push_back({line, key});
            std::cout << "Added with key: " << key << std::endl;
        }
        else
        {
            std::cout << "No key found" << std::endl;
        }
    }

    return movieVector;
}