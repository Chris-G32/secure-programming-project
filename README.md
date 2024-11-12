# secure-programming-project
Group project for secure programming class Fall 2024 at Kent State.

# Build command
from root of repo run 
`cmake -B ./build -S log_core && cd build && make`
# Summary
Build It; Break It; Fix It: Overview
In this project, you will implement a secure log to describe the state of an art gallery: the guests and
employees who have entered and left, and people that are in rooms. The log will be used by two
programs. One program, logappend, will append new information to this file, and the other, logread, 
will read from the file and display the state-of-the-artgallery according to a given query
over the log. Both programs will use an authentication token, supplied as a command-line argument, to
authenticate each other. You will build the most secure implementation you can; then you will have the opportunity to
attack other teams’ implementations, and fix bugs that other teams identify in your implementation.
