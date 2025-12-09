[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=21758362)
# EEE Study Helper - ELEC2645 Unit 2 Project

This project is a menu-driven command line application for the ELEC2645 module.
My application is called the EEE Study Helper - a small collection of helpful tools for Electronic and Electrical Engineering students to help them with performing calculations and checking them.

### 1 Run code

You can build the code as we have been using in the labs with 
`gcc main.c funcs.c -o main.out -lm` (the `-lm` is required to link the math library). You can also use `make -B` to force a rebuild using the provided `Makefile`.

Then run the code with `./main.out`


### 2 The assignment
1. Resistor Colour Code Decoder
2. Series/Parallel Resistor Calculator
3. RC Circuit Helper
4. Unit converter


### 3 Test command

The `test.sh` script is provided to check that your code compiles correctly. This is what the autograder will use to check your submission. You can run it with `bash test.sh` or `./test.sh` or just `make test`. 

You do not need to modify this script, but you can look at it to see what it does.


### 4 Submit Solution

Use the same method as previous labs to commit and push your code to your GitHub repository for the autograder to check. 

In your final journal post, please include a link to your GitHub repository containing your code  *and* a zip file of your code as an attachment.
