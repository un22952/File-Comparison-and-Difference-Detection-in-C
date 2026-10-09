# File Comparison and Difference Detection in C

## Overview

This project implements a file comparison program in C that compares two text files and identifies differences using two approaches. It measures and reports the execution time of each approach to allow performance comparisons.

The program reads two input files, compares their contents, and writes detected differences into separate output files. It uses standard C file I/O, dynamic memory allocation, file metadata, and execution-time measurement.

## Features

- **File Comparison:** Compares the contents of two input files.
- **Two Comparison Methods:** Implements two approaches to compare file contents.
- **Difference Extraction:** Writes detected differences to separate output files.
- **Performance Measurement:** Measures the execution time of each comparison method in milliseconds.
- **Dynamic Memory Allocation:** Allocates buffers to store file contents during comparison.
- **File Metadata:** Uses `stat()` to obtain file sizes.
- **Error Handling:** Checks command-line arguments and file-opening failures.

## Technologies Used

- **Language:** C
- **File I/O:** `fopen()`, `fread()`, and `fwrite()`
- **Memory Management:** `malloc()` and `free()`
- **File Metadata:** `stat()`
- **Timing:** `gettimeofday()`
- **Compilation:** GCC

## Project Structure

```text
.
├── proj3.c
├── examples/
│   ├── alice1.txt
│   └── ...
├── differencesFoundInFile1.txt
├── differencesFoundInFile2.txt
└── README.md
```

The files in `examples/` are sample inputs. The two difference files are generated when the program runs.

## Compilation

Compile the program using GCC:

```bash
gcc -Wall proj3.c -o proj3.out
```

The `-Wall` flag enables common compiler warnings.

## Usage

Run the program with two input filenames:

```bash
./proj3.out <file1> <file2>
```

For example:

```bash
./proj3.out examples/alice1.txt examples/alice1.txt
```

The program compares the two files and prints the elapsed time for each comparison method.

## Comparison Methods

### Step 1: Character-by-Character Comparison

The `step1()` function reads the input files in small chunks using `fread()` and compares the current characters.

When the characters differ, the corresponding content from the first file is written to `differencesFoundInFile1.txt`.

This approach uses relatively small buffers instead of loading the entire files into memory at once.

### Step 2: In-Memory File Comparison

The `step2()` function obtains each file's size using `stat()`, allocates memory for the file contents, and reads the files into buffers.

It then compares the contents using indexed memory access and writes detected differences from the second file to `differencesFoundInFile2.txt`.

This approach demonstrates how file metadata and dynamic memory allocation can be used to compare file contents in memory.

## Output Files

| File | Description |
|---|---|
| `differencesFoundInFile1.txt` | Stores content selected by Step 1 when differences are detected. |
| `differencesFoundInFile2.txt` | Stores content selected by Step 2 when differences are detected. |

The output files are opened in write mode, so their previous contents are overwritten each time the program runs.

**Note:** These methods are custom comparison implementations rather than a complete, position-independent diff algorithm. Their results may not capture every difference correctly, particularly when the files have different lengths or contain insertions and deletions.

## Performance Measurement

The program uses `gettimeofday()` to measure the elapsed time for each method.

Example output:

```text
Step 1 took 0.125000 milliseconds
Step 2 took 0.084000 milliseconds
```

These values are illustrative; actual results depend on file size, system load, and the input contents.

You can compare performance by running the program against files of different sizes and contents.

## Error Handling

The program checks for:

- An incorrect number of command-line arguments.
- Input files that cannot be opened.
- Output files that cannot be opened.
- Failures when retrieving file metadata with `stat()`.

## Learning Objectives

This project demonstrates:

- Comparing file contents using C standard I/O.
- Working with file pointers and buffers.
- Dynamically allocating and releasing memory.
- Retrieving file metadata with `stat()`.
- Measuring execution time.
- Comparing alternative implementations of a file-processing task.

## Future Improvements

- Correctly handle files of different lengths.
- Detect insertions, deletions, and shifted content.
- Check the return values of memory allocation and file-reading operations.
- Handle empty files and binary files safely.
- Improve error handling and return nonzero exit codes on failure.
- Use a more systematic comparison algorithm to identify exact differences.

## How to Run the Example Script

If you have the provided shell script, execute it from the project directory:

```bash
chmod +x run.sh
./run.sh
```

The script compiles `proj3.c`, runs the program with the example input, and displays the generated difference files.
