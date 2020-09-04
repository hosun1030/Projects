/*

Given two text documents as arguments, a dictionary tree will be created
from the 'aspell_list_en.txt' text file. 

Each letter of a word will be a node, which contains an EndOfWord flag which denotes a completed
or incompleted word


The second text document 'Austen-Pride-and-Prejudice.txt' will then be parsed one word at a time, 
spell checking each word by traversing the the tree. If a word ends on a node without an EndOfWord Flag
it is considered misspelled and printed out. 

*/