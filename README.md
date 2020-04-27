# find-replace-tool-USING-C-PROGRAMMING-LANGUAGE
Hey ! It is my third assignment from "Data Structures and Algorithm" class that I took at Yildiz Technical University. This repository contains; code of program , screenshots while it is processing , and Assignment's description.
# CAN YOU PLEASE JUST GIVE ME THE FUNCTION NAMES
<img src="https://github.com/sercaksoy/find-replace-tool-USING-C-PROGRAMMING-LANGUAGE/blob/master/functions/functions.png">

# What is a Find and Replace tool
  Find and Replace tool is helping to user to change a word or a string to another string. This tool consists of 2 stages;
  1. Finding the string given by the user.
  2. Overwrite the string taken by the user.
# How to find given word in the file
  You may think, it is easy to find a word in a string, First search for the first character of our "find" word and then when we found it, check if rest of the string contains rest of our "find" word. And then repeat .. That's known as Brute-Force algortihm you created. It is reliable and easy to implement. But while working with huge data it is a bit slow. So I used Boyer-Moore Horspool algorithm to find the "find" word as my assignment asked for.
# What is Boyer-Moore Horspool algorithm
  It is a simplification of the Boyer–Moore string search algorithm published by Nigel Horspool in 1980. This algorithm provides to search characters in string not by, one by one but with a jumping score table. This table mostly known as "Bad Match Table", this algorithm needs the table to be created as preprocess. There are 2 ways to create the table ;
  1. Allocating a 256*(int) byte array to store which character has how much jump score. 256 stems from ASCII table.
  2. Creating an array with a class storing a char with a jump score. This arrays size depends on find words size and exact same of              it(actually you can count repetitive letters as one).
  ###### This is how I implemented it :
  <img src="https://github.com/sercaksoy/find-replace-tool-USING-C-PROGRAMMING-LANGUAGE/blob/master/functions/createTable.png">
  # Then what ?
  Then your program is not searching the find word char by char but a jumping score. It works like; let's say your trying to find the word "whocares". This jump method repeats until it finds the last character of our word. Then rewind it. So we need to find 's' in our text. Let's say our text be ajahoekrewhocaresbbbb , now we need to find s in it. To find our last char, that means we can start to look for our word from |whocares| = 8 index. But first we need to create our table to get jump scores for each character. 
  # Creating bad match table for the above example
  Let's think we are on the some character that doesn't exist in our word. So it is impossible to find the word in wordsize length. That means we are initializing the word size as jump score for all out of word letters. Alphabet - {w,h,o,c,a,r,e,s} have jump score 8.
    Now let's think if you're on the some existing character, that means you need to shift your word wordsize-i (i is where is the character in the word.) So it looks like this ; w -> 8 - 1 = 7 , h -> 8 - 2 = 6, .... , e -> 8 - 7 = 1 and thats it because if you find s that means you are on the lastcharacter and try to match words.(Exception : If you have repetitive letters you need to take the most right ones jump score for each.)
  # Authentication for the above example
    Inserting a 'f' to point where I am showing.
    ajahoekrewhocaresbbbb -> Starting from the index 8.
           f              -> found 'r' jump 2.
    ajahoekrewhocaresbbbb
             f            -> found 'w' jump 7.
    ajahoekrewhocaresbbbb
                    f     -> found 's' try to match words.
    ajahoekrewhocaresbbbb
             whocares     -> MATCH! Word found .
   
  # We found the word OKAY, but how do we replace it ?
  After getting all found indexes we need to shift all other characters depends on replace word size - find word size if this value is positive that means your text is going to expand, if it is 0 no need to shift characters in the text. And if it is negative you have to shift your characters most left possible. After subtraction it needed to multiply with the times we found the find word. Then do the necessary operations. My code is what I told in this section. If you couldn't understand anything you can always sen me e-mails.
  # Step by step presentation
  <img src="https://github.com/sercaksoy/find-replace-tool-USING-C-PROGRAMMING-LANGUAGE/blob/master/examples/stepbystep.png">
