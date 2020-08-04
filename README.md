# Parent-Child-Process
 A parent process that will create child processes to perform tasks and will collect the output from these child

# Process
A parent process that will create child processes to perform tasks and will collect the output from these children. There are three tasks that should be performed:•Read the input file that contains Linux shell commands. Parent process will create a child process to read that file and child process will return the content of that file in the form of a string using a shared memory area.•Execute the Linux shell commands read from the input file and execute them one by one. A child process will be created to execute these commands and the output will be returned by the child process in the form of string using pipe.•The parent process will write the output of commands to the screen.


# Diagram
The following flow chart describes the flow of the program


![Screen Shot 2020-08-04 at 6 46 49 AM](https://user-images.githubusercontent.com/68686454/89285448-603a0700-d61e-11ea-9fb8-9b6d8209a632.png)
