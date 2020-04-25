# find-replace-tool-USING-C-PROGRAMMING-LANGUAGE
Hey ! It is my third assignment from "Data Structures and Algorithm" class that I took at Yildiz Technical University. This repository contains; code of program , screenshots while it is processing , and Assignment's description.
# What is a Find and Replace tool
  Find and Replace tool is helping to user to change a word or a string to another string. This tool consists of 2 stages;
  1. Finding the string given by the user.
  2. Overwrite the string taken by the user.
# How to find given word in the file
  You may think, it is easy to find a word in a string, First search for the first character of our "find" word and then when we found it, check if rest of the string contains rest of our "find" word. And then repeat .. That's known as Brute-Force algortihm you created. It is reliable and easy to implement. But while working with huge data it is a bit slow. So I used Boyer-Moore Horspool algorithm to find the "find" word as my assignment asked for.
# What is Boyer-Moore Horspool algorithm
  It is a simplification of the Boyer–Moore string search algorithm published by Nigel Horspool in 1980. This algorithm provides to search characters in string not by, one by one but with a jumping score table. This table mostly known as "Bad Match Table", this algorithm needs the table to be created as preprocess. There are 2 ways to create the table ;
  1. Allocating a 256*(int) byte array to store which character has how much jump score. 256 stems from ASCII table.
  2. Creating an array with a class storing a char with a jump score. This arrays size depends on find words size and exact same of it.
  DEVAM BURDAN
