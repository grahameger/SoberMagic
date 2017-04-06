# SoberMagic
A command line application that automatically assigns sober monitors to different social events and tiers  based on a point system.


Usage: 

./SoberMagic <input_file_name> <number of head sobers> <number of regular sobers> <BIG or SMALL>

The input file is structured as follows:

A header with the number of head sobers directly below. Followed directly by another header "REGULAR" with a number of regular sobers.

Each line with a sober monitor must have a first name, followed by whitespace, a last name, followed by white space, and an integer, followed by a newline character.

After the last head sober is another header "REGULAR" followed by whitespace, then an integer with the number of regular sobers below.

~~~~
HEAD 3
Derrick Walton  0
Moritz Wagner 0
DJ Wilson 0
REGULAR 2
Andrew Dakich 0
Mark Donnal 0
~~~~

When the program is run. It print the specified number of head sober monitors and regular sober monitors based on who has the lowest points. 

It will then increment the chosen sober's points and write them back to a file after being randomly shuffled. 
