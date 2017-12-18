# SMU-CSE2341-Final-Project-CSV-Search-Engine
This is a project that was assigned to me during my Data Structures Class.


<b><h3>Purpose of the Project:</h3></b>

To build a program in C++ that reads in about 2 gigabytes of information from provided CSV files that contain an archive of all the questions from stack overflow between the years 2008-2016.

I must process these questions and their respective tags, index them and store them into either a custom AVL Tree or Hash Table depending on user choice

I must then be able to take in user input on which mode the user wants to run (either maintenance mode or interactive mode)

If <b>maintenance mode</b> is selected, the user can either enter a new file from a provided file path, or clear the existing index.

If  <b>interactive mode</b> is selected, the user can choose whether they want to load the files into either an AVL tree or Hash table, and once loaded they must enter a term to search for

The user can also enter certain Boolean operators such as "NOT", "AND, or "ORR" that infulence their results.

The search query is processed and the neccesary Data Structure is traversed and the top 15 results are returned to the user

The user can then enter a number 1-15 to expand the result and examine its information.

<b><h3>Data Structures Used</h3></b>

In this project I made and used my own custom self balencing <b>AVL Tree</b>, and my own <b>Hash Table</b>.

<b>If any Custom Data Structures are not included, they are all in my "My Custom Data Structures" repo.</b>


<b><h3>Instructions</h3></b>

In order to properly gain results, the specified .CSV files must be passed through the command line.

This program is currently formatted to read in a text file, that is because in an earlier version, we succesfully parsed all the CSV files and wrote them into their own .txt files

The rest of the process once the file is read in properly is pretty straight forward, as all the prompt is on screen.
