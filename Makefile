find_biggest_files_c : find_biggest_files_c.c
	gcc find_biggest_files_c.c -o find_biggest_files_c
valgrind_check : find_biggest_files_c
	valgrind --tool=memcheck --leak-check=yes ./find_biggest_files_c ~/Downloads/
