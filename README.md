
## Project description:

This program is designed to efficiently sort various  CSV data files based on the position of a specified sorting key. It utilizes advanced sorting algorithms including standard and modified versions of Quicksort, Bucketsort, and Mergesort. Designed for command-line execution, the program requires four essential arguments: input_filename, sort_key_pos, n_items, and algo_name. Additionally, it supports optional parameters shuffle_passes and shuffle_seed for enhanced data handling. Upon execution, the program will load and filter the data from the input file, perform sorting based on the sort_key_pos, and then display the sorted data along with metrics such as the sorting time, seed, median, and average.

## Project Structure:

* ***main.cpp**: Contains the main function of the program. 
* **sorting.cpp**: Implementation  for the sorting algorithms
* **sorting.h**: Header file declaring the sorting algorithms
* **sorting.o**: Object file generated after compiling the sorting.cpp file
* **prog**: Executable program 

## Compiling Project

To compile the project, navigate to the project directory and use the following command:
* **g++ sorting.cpp -c**
* **g++ main.cpp sorting.o -o prog**

## Usage

To execute the driver program:
**./prog input_file_name sort_key_pos n_items algo_name shuffle_passes shuffle_seed**
- **sort_key_pos**: specifies the field number in the input file that serves as the sorting key
- **n_items**: specifies the number of elements to load into memory and sort
- **algo_name**: specifies the sorting algorithm to use from the following list: MERGE, QUICK, STANDARDQUICK, BUCKET
- **shuffle_passes**:  is an optional parameter, if provided it specifies the number of shuffling passes to perform on the data loaded from the file. If this parameter is not specified, no shuffling is performed.
- **shuffle_seed**: is an optional parameter, if provided it specifies the seed for the random number generator to be used to initialize the pseudorandom number generator before shuffling the data. If this parameter is not specified, the seed will be generated randomly.
## Error Handling

The program includes basic error handling. If the number of arguments provided is less than 5, it will display a usage message. 

## Author 
This program was written by Aleksander Lyskawa.

