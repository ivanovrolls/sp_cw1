The main program is invoked as
./tldmonitor begin_date end_date [file] ...
If no file is present in the arguments, stdin will be processed. Additionally, if a filename 
is the string “-“, the program will process stdin at that point.
The mainline functionality of tldmonitor.c consists of the following pseudocode:
process the arguments
create a TLD list
if no file args are provided
 process stdin
else for each file in the argument list
 open the file
 process the file
 close the file
create an iterator
while there is another entry in the iterator
 print out the percentage associated with that TLD
destroy the iterator
destroy the Date structures
destroy the TLDList
A static function process is provided to process all the log entries in a particular log file.
------------
