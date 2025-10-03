# Multithreaded_Sorting_Application

This project demonstrates a simple parallel sorting implementation in C. It uses multithreading to divide an array into two halves, sort each half using the quicksort algorithm, and then merge the results into a single sorted array.

## Features
- **Parallel Sorting**: Two threads sort the first and second halves of the array concurrently using quicksort.
- **Merging**: A third thread merges the two sorted halves into a final sorted array.
- **Fixed Array Size**: The array has a predefined size of 10 elements for simplicity.
- **In-Place Sorting**: Quicksort operates in-place on the original array before merging.

## Sample Input Array
The program starts with the following unsorted array:  
`[38, 27, 43, 3, 9, 82, 10, 15, 5, 1]`

## Expected Output
After execution, it prints the sorted array:  
`Sorted array: 1 3 5 9 10 15 27 38 43 82`

## How It Works
1. **Thread Creation for Sorting**:
   - Thread 1: Sorts indices 0 to 4 (first half).
   - Thread 2: Sorts indices 5 to 9 (second half).
   - Both use the standard quicksort algorithm (partitioning around a pivot).

2. **Synchronization**:
   - The main thread waits for both sorting threads to complete using `pthread_join`.

3. **Merging**:
   - A third thread performs a simple two-pointer merge of the two sorted halves into a new `sortedArray`.

4. **Output**:
   - The final sorted array is printed to the console.

Note: This is a basic implementation for educational purposes. In a real-world scenario, quicksort recursion could be parallelized further, and error handling (e.g., for thread creation failures) should be added. The merge assumes the halves are correctly sorted post-quicksort.

## Building and Running
### Prerequisites
- A Unix-like system (Linux, macOS) or Windows with MinGW/Cygwin.
- GCC or compatible C compiler.
- Pthreads support (enabled by default on Unix; use `-pthread` flag).

### Compilation
```bash
gcc -o parallel_quicksort -pthread main.c
```
### Execution
```bash
./parallel_quicksort
```
### Example Output
```bash
Sorted array: 1 3 5 9 10 15 27 38 43 82
