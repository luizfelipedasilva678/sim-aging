# Simulator aging algorithm

## What is this?

This is simulator of aging algorith used to page substituition on OS.

## How can I execute this code?

The param of this program is a .txt file following format.

4 8  
10101011  
10000011  
00111111  
10000000  

Where the first line of this file must have 2 numbers separed
whith one white space the first number is the size of aging register
and the second number is the quantity of pages of the system.
The following lines are the sequences of references bits of each
page.

## Output

The output of this code is a file where
each line corresponds to the value of the
register for each page and last line show the
page that must be substitued.

1011   
0000   
0101   
0100   
0101   
0100   
0111   
0111   

Pagina a ser removida => 1 
