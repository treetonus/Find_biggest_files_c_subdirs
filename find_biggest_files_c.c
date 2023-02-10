//Q: Could you write a similar program but which goes into subdirectories? Coment it also please.

#include <stdio.h>
#include <dirent.h> // Include the dirent library for accessing directory entries
#include <sys/stat.h> // Include the stat library for accessing file attributes
#include <stdlib.h> // Include the stdlib library for general purpose functions
 
int main(int argc, char *argv[])
{
    DIR *dp; // Pointer to a directory stream
    struct dirent *entry; // Structure containing directory entry information
    struct stat statbuf; // Structure containing file information
 
    if (argc != 2) // Check if the correct number of arguments are passed
    {
        fprintf(stderr, "Usage: %s directory_name\n", argv[0]); // Print an error message if the incorrect number of arguments is passed
        exit(1);
    }
 
    if ((dp = opendir(argv[1])) == NULL) // Open the specified directory
    {
        fprintf(stderr, "Can't open directory %s\n", argv[1]); // Print an error message if the directory cannot be opened
        exit(2);
    }
 
    chdir(argv[1]); // Change the working directory to the specified directory
 
    long int size, max_size = 0; // Initialize variables for storing filesize and maximum filesize
    char *file; // Variable for storing the filename
    while ((entry = readdir(dp)) != NULL) // Read the contents of the directory one file at a time
    {
        lstat(entry->d_name, &statbuf); // Get the file attributes
        if (S_ISDIR(statbuf.st_mode)) // Check if the file is a directory
        {
            char new_path[256]; // Create a new path to the directory
            strcpy(new_path, argv[1]); // Copy the original path
            strcat(new_path, "/"); // Add a slash to the end of the path
            strcat(new_path, entry->d_name); // Append the directory name to the end of the path
            main(2, new_path); // Call the main function again with the new path
        }
        else // If the file is not a directory
        {
            size = statbuf.st_size; // Get the size of the file
            if (size > max_size) // Check if the size is larger than the current maximum size
            {
                max_size = size; // Store the size as the new maximum size
                file = entry->d_name; // Store the filename
            }
        }
    }
    printf("%s\t%ld bytes\n", file, max_size); // Print the filename and size of the largest file
 
    closedir(dp); // Close the directory
    return 0;
}
