#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/*
 * Handles exceptions that can occur in main method such as file cannot be opened
 * for reading or writing, and incorrect number of command line arguments.
 */
void handleExceptions(int argc, FILE * fptr1, FILE * fptr2, FILE * fptw1, FILE * fptw2);

// Step 1
void step1(FILE * fptr1, FILE * fptr2, FILE *fptw1);
// Step 2
void step2(FILE * fptr1, FILE * fptr2, FILE * fptw2);

/*
 * This program will read files and compare them and write any differences in another files.
 */
int main(int argc, char * * argv) {

    FILE * fptr1 = fopen(* (argv + 1), "r");
    FILE * fptr2 = fopen(* (argv + 2), "r");
    FILE * fptw1 = fopen("differencesFoundInFile1.txt", "w");
    FILE * fptw2 = fopen("differencesFoundInFile2.txt", "w");
    handleExceptions(argc, fptr1, fptr2, fptw1, fptw2);
    // time variables
    struct timeval start, end;
    long seconds, microseconds;
    double milliseconds;
    // start the timer for step1
    gettimeofday(&start, NULL);
    // step 1
    step1(fptr1, fptr2, fptw1);
    // end the timer for step1
    gettimeofday(&end, NULL);
    // calculate time for step 1
    seconds = end.tv_sec - start.tv_sec;
    microseconds = end.tv_usec - start.tv_usec;
    milliseconds = (seconds * 1000.0) + (microseconds / 1000.0);
    // print the time
    printf("Step 1 took %fl milliseconds\n", milliseconds);

    // start the timer for step2
    gettimeofday(&start, NULL);
    // step 2
    step2(fptr1, fptr2, fptw2);
    // end the timer for step2
    gettimeofday(&end, NULL);
    // calculate time for step 2
    seconds = end.tv_sec - start.tv_sec;
    microseconds = end.tv_usec - start.tv_usec;
    milliseconds = (seconds * 1000.0) + (microseconds / 1000.0);
    // print the step2
    printf("Step 2 took %fl milliseconds\n", milliseconds);

    // clsoe files
    fclose(fptr1);
    fclose(fptr2);
    fclose(fptw1);
    fclose(fptw2);
    return 0;
} // main

void step1(FILE * fptr1, FILE * fptr2, FILE * fptw1) {

    int bufSize = 2;
    char * buffer1 = (char *) malloc(sizeof(char) * bufSize); // for file 1
    * (buffer1 + 1) = '\0';
    char * buffer2 = (char *) malloc(sizeof(char) * bufSize); // for file 2
    * (buffer2 + 1) = '\0';
    int bytesRead1 = fread(buffer1, sizeof(char), bufSize - 1, fptr1);
    int bytesRead2 = fread(buffer2, sizeof(char), bufSize - 1, fptr2);
    // loop to write to the file of differences
    while (bytesRead1 > 0 || bytesRead2 > 0) {
        * (buffer1 + bytesRead1) = '\0';
        * (buffer2 + bytesRead2) = '\0';
        // write the differences
        if (* buffer1 != * buffer2) {
            fwrite(buffer1, sizeof(char), bytesRead1, fptw1);
        } // if
        bytesRead1 = fread(buffer1, sizeof(char), bufSize - 1, fptr1);
        bytesRead2 = fread(buffer2, sizeof(char), bufSize - 1, fptr2);
    } // while

    // free up memories
    free(buffer1);
    free(buffer2);

} // step1

void step2(FILE * fptr1, FILE * fptr2, FILE * fptw2) {
    // get the size of file 1 and get memories for the file
    fseek(fptr1, 0, SEEK_END);
    long fileSize1 = ftell(fptr1);
    char * buffer1 = (char *) malloc(fileSize1 + 1);
    rewind(fptr1);
    // read file 1
    fread(buffer1, 1, fileSize1, fptr1);
    * (buffer1 + fileSize1) = '\0';

    // get the size of file 2 and get memories for it
    fseek(fptr2, 0, SEEK_END);
    long fileSize2 = ftell(fptr2);
    char * buffer2 = (char *) malloc(fileSize2 + 1);
    rewind(fptr2);
    // read file 2
    fread(buffer2, 1, fileSize2, fptr2);
    * (buffer2 + fileSize2) = '\0';
    // compare the files
    int j = 0;
    for (int i = 0; i < fileSize2; i++) {
        if (i > fileSize1) { // when file 1 is shorter than file 2
            j = i - fileSize1;
        } // if
        if (* (buffer1 - j + i) != * (buffer2 + i)) {
            fwrite(buffer2 + i, sizeof(char), 1, fptw2); // write to file
        } // if
    } // for
    // free up memories
    free(buffer1);
    free(buffer2);

} // step2

void handleExceptions(int argc, FILE * fptr1, FILE * fptr2, FILE * fptw1, FILE * fptw2) {
    if (argc != 3) {
        printf("Usage: proj3.out <file1> <file2>\n");
        exit(0);
    } // if
    if (fptr2 == NULL) {
        printf("There was an error reading the second file!\n");
        exit(0);
    } // if
    if (fptr1 == NULL) {
        printf("There was an error reading the first file\n");
        exit(0);
    } // if
    if (fptw1 == NULL) {
        printf("Cannot open the first file to write!");
        exit(0);
    } // if
    if (fptw2 == NULL) {
        printf("Cannot open the second file to write!");
        exit(0);
    } // if

} // handleExceptions
