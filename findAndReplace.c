#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<sys/time.h>
#define MAX 100
struct tableMap{ // This class is helping us to store characters with their jump numbers.
	char letter;
	int jump;
};
typedef struct tableMap tableMap;
int searchInTable(tableMap * table, char ch, int t_size){ // This function helps to find given chars in the table.
	int i;
	for(i = 0; i<t_size; i++){
		if((table[i].letter) == ch) // Searching chars in the table.
			return i;
	}
	return -1;
}
int * Boyer_MH(tableMap * table, char * input, int * times, char * find, int t_size, char sensitivity){ // This function jumps through text and returns the indexes of find words.
	int i,a,b;
	int update;
	int index = 0;
	int length = 10;
	int founded = 0;
	int findsize = strlen(find);
	int inputsize = strlen(input);
	int * foundArr = (int *)malloc(length*sizeof(int)); // First of all, allocating the memory with a MAX value, but we will update it if it needs.
	i = findsize -1;									// Starting to jump from the finds size because we are looking for the last chars all the time.
	
	while(i < inputsize){								// Searching untill it reaches the last of our input.
		if(sensitivity != 'C' && sensitivity != 'c')    // In the program there is a user option about case sensitivity and 
			input[i] = tolower(input[i]);               // if user picks not case sensitivity the we need to change to (common) lower case.
		
		if(input[i] != find[findsize-1]){               // It jumps depends on the table untill it finds the last character of find word in the input text.
			update = searchInTable(table, input[i], t_size); // If it is not the last letter of find word, then we are looking for the jump score for the char.
			if(update == -1)							// If it is not in it then we are jumping 
				i += findsize;							// find size.
			else
				i += table[update].jump;				
		}
		else{											// If the input char and find's last char matches;
			a = i;										// We need 2 more temporary values to track back
			b = findsize-1;								// if the input contains all other find's letters same order.
			while((input[a] == find[b]) && (b > -1)){	
				a--;
				b--;
				if(sensitivity != 'C' && sensitivity != 'c')
					input[a] = tolower(input[a]);
			}
			if(b == -1){								// If the loop end beacuse the find word reached its size;
				if(index == 0){							// it means we found the word in the text.
					foundArr[index++] = i-findsize+1;   // Storing the found indexes in the array
					founded++;							// Storing the times we have found the word.
					
				}
				else if(index > 0 && foundArr[index-1]+findsize+1 <= i-findsize+1){
					foundArr[index++] = i-findsize+1;
					if(index >= length - 5){			// If the array reaches the MAX size we are reallocating the memory.
						length += 10;
						foundArr = realloc(foundArr,length*sizeof(int));
					}
					i++;
					founded++; 
				}
				else{
					i++;
				}
			}
			else{
				update = searchInTable(table, input[a], t_size);
				if(update == -1){
					a += findsize;
					i = a;
				}
				else{
					a += table[update].jump;
					i = a;
				}
			}
		}	
	}
	*times = founded;								// Storing how much time we found the word as well.
	return foundArr;    							// And returning the array of founded indexes.
}
tableMap * createTable(char * find, int * t_size){ // This function creates a table with unique letters in the word and their jump scores.
	int i;
	int update;
	int place = 0;
	int sizeofWord = strlen(find);
	tableMap * table = (tableMap *)malloc(sizeofWord * sizeof(tableMap)); // Allocating memory, incase the word occurs only unique chars, using sizeofWord.
	for(i = 0; i<sizeofWord-1; i++){
		update = searchInTable(table, find[i], i);  // Calling the searchInTable function, it returns given chars index and -1 if it couldn't find in it.
		if(update == -1){							// If the current table doesn't contain given char;
			table[place].jump = sizeofWord - i -1;  // It creates one with the jump score,
			table[place].letter = find[i];          // and store in it our class array.
			place++;
		}
		else
			table[update].jump = sizeofWord - i -1; // If the given char is already in the table, it updates the jump score.
	}
	update = searchInTable(table, find[i], i);
	if(update == -1){
		table[place].jump = sizeofWord;
		table[place].letter = find[i];
		place++;
	}
	*t_size = place;								// To use in main function we need to store table's size as well.
	return table;									// Returning completed table.
}
char * newtext(char* input, char* replace, int* foundArr, int times, int findsize,int inputsize){ // This function changes the input text into expected one.
	int i,j;
	int shift;
	int x,firstchar;
	int replacesize = strlen(replace);
	if(replacesize > findsize){				// In the case of we are changing it to a bigger text then we need to shift the chars to the right.
		shift = replacesize - findsize;
		for(i = 0; i < times; i++){			// For every time the program found words in the text
			x = foundArr[i];				
			for(j = inputsize-1+((shift)*i); j>x+findsize-1 ; j--){ // From most right to the founded index
				input[j+shift] = input[j];							// The program is shifting the chars.
			}
			firstchar = 0;
			for(j = x; j<x+replacesize; j++){			// Replacing the word.
				input[j] = replace[firstchar];
				firstchar++;
			}
			for(j = i+1; j<times; j++)					// In the array we shifted all the 
				foundArr[j] += shift;					// other founded words.
		}
		input[inputsize+(shift*times)] = '\0';
	}
	else{
		shift = findsize - replacesize;			// In the case of decreasing the size we need to shift them to the left.
		for(i = 0; i < times; i++){
			x = foundArr[i];
			for(j = x + findsize; j<inputsize; j++){
				input[j-shift]=input[j];
			}
			firstchar = 0;
			for(j = x; j<x+replacesize; j++){
				input[j] = replace[firstchar];
				firstchar++;
			}
			for(j = i+1; j<times; j++)
				foundArr[j] -= shift;
			inputsize -= shift;
		}
		input[inputsize] = '\0';			// And placing a stop char to the end of our output.
	}
	
	return input;
}
int main(){
	int i;
	int size,findsize,replacesize;
	int times = 0, t_size = 0, expand;
	char* input;
	char ch='x';
	char filename[MAX],find[MAX],replace[MAX];
	char sensitivity;
	struct timespec begin;
	struct timespec end;
	printf("Find : ");
	gets(find);
	printf("Replace : ");
	gets(replace);
	printf("Options : Case Sensitive | Not Case Sensitive");
	printf("\nPlease Type (C) to Case Sensitive or (N) to Not Case Sensitive : ");
	scanf("%c",&sensitivity);
	findsize = strlen(find);
	replacesize = strlen(replace);
	if(sensitivity != 'C' && sensitivity != 'c'){
		for(i = 0; i<findsize; i++){
			find[i] = tolower(find[i]);
		}
	}
	FILE * fp ;
	printf("\nEnter file's name: ");
	scanf("%s",filename);
	fp = fopen(filename,"r");
	if(fp == NULL){
		perror("Unable to open file!");
		exit(1);
	}
	else{	
		fseek(fp, 0, SEEK_END); // To find out file's size
		size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		input = (char *)malloc((size+1)); // Then allocating the memory.
		fread(input, 1, size, fp);
		fclose(fp);
	}
	int inputsize = strlen(input);
	if(replacesize > findsize){						// Expanding the char array if needed.
		expand = (replacesize - findsize)*times;
		expand = expand+size;
		input = realloc(input,expand);
	}
	clock_gettime(CLOCK_MONOTONIC, &begin);
		tableMap * table = createTable(find, &t_size); // The algorithm starts with creating the table
		int * foundArr  = Boyer_MH(table, input, &times, find, t_size, sensitivity); // Then finding the words in the text.
		input = newtext(input,replace,foundArr,times,findsize,inputsize); // Then turning the text into expected one.
	clock_gettime(CLOCK_MONOTONIC, &end);			
	long int timetakenano = (long int)(end.tv_sec-begin.tv_sec)*1000000000 + (end.tv_nsec-begin.tv_nsec);
	double timetakems = (double)timetakenano / 1000;
	fp = fopen(filename,"w");
	fprintf(fp,input);												// Writing into file.
	fclose(fp);
	//-----------OUTPUT------------//                              
	system("cls");					// You may want to change this depends on your DOS.
	printf("Find: %s\n",find);
	printf("Replace: %s\n",replace);
	if(sensitivity == 'C' || sensitivity == 'c')
		printf("Option: Case Sensitive\n");
	else
		printf("Option: Not Case Sensitive\n");
	printf("Found and Replaced: %d\n",times);
	printf("Running Time: %.3lf miliseconds\n",timetakems);
	
	return 0;
}