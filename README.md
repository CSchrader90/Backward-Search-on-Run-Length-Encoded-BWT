# Backward-Search-on-Run-Length-Encoded-BWT
Search on compressed text data (Run-Length-Encoded Burrows Wheeler Transform) using FM-Index and Backward Search algorithm in C++


## Notes 
<ins>File Structure </ins>

| src  
|---b.cpp   
|---b.h  
|---s.cpp  
|---s.h  
|---indexes.cpp  
|---indexes.h  
|---main.cpp  
|---constants.h  
| files  
|---example.s  
|---example.b  
|---example.bb  
| indexes  
|---example_b.count  
|---example_b.rank  
|---example_bb.rank  
|---example_s.rank  


<ins>Using the FM-index:</ins> 

count['c'] is the number of characters lexicographically smaller than 'c'  
rank(t, 'c') returns the number of occurences of character 'c' in object up until and including index t.  
select(n, 'c') returns the first index for which there have been n occurrences of 'c'  



## Running

Two postional arguments are needed to run. A file name and a search string.  
The file name should have no extensions and correspond to the names of the multiple files that make up the FM index.  
e.g. using a file name 'example' requires that within the directory 'files' there exists example.s, example.b and example.bb  
'example.s' and 'example.b' correspond to the characters and the run-lengths (in binary representation) of the BWT, respectively.
'example.bb' must contain the stably sorted 'example.b' with respect to the lexicographical ordering of 'example.s' i.e. stably sort 'example.s' and maintain their corresponding run-lengths in 'example.b', giving 'example.bb'  

The index files will be created and saved on the first use. Subsequent uses will use the same index files. These index files save values for rank at specified intervals (defineable in constants.h)  
The select class member function of the b class uses a binary search over the rank index.


If the save interval constants are altered, the indexes files should be deleted so that they can be generated again on further calls.
