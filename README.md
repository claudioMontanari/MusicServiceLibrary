##Object Oriented Languages and Environment - CS474 
###Claudio Montanari - Music Library Service Project

####Installation

To install the project import it in a C++ editor (CLion for instance) and set the compiler to c++11.

####Features

The Music Library Service prompts the user a menu with the following commands:

- l : List all the files in the list 
- e : Ask the user an ID between 0-9 to set as current clip
- c : Ask the user to insert the data that will be used to create a new clip or update an existing one
- y : Copy the current clip into a temporary file named "temp.clip"
- i : Reads the list of commands from the file "input.inp"
- p : Ask the user to insert the new price for the current clip
- s : Save all the clip that are in memory into their file (all such files are places into the "files" directory)
- q : Quit from the system

####Notes

The __create new clip__ functionality requires the user to insert the following data (in this order):

- ID : ID of the clip that should be updated or created
- Title : the song title
- Artist : the artist name
- People : a band member (write "quit" to stop adding members)
- Genre : a number between 1-9 for the music genre (it will be mapped according to the following ordered list: POP_MUSIC, FOLK_MUSIC, JAZZ, BLUES, CLASSICAL, COUNTRY_MUSIC, REGGAE, ROCK, OPERA)
- Price : a decimal number for the price

The __read from file__ functionality require that a valid list of commands is inserted in the file "input.inp". In particular, the file should be formatted putting every input in a new line. For instance, the following is a valid input file (what follows the // is just a comment and shouldn't be placed into the input file): 

```
l               //List all the clips
c               //Create or update a clip
3               //clip ID
Jungle song     //Song title
Human creature  //Artist
Hyppo pippo     //1st Band member
Dog max         //2nd Band member
quit
2               //Genre: FOLK_MUSIC
1.50            //Price
y               //Create a copy of the current clip and save it
e               //Edit a clip
6               //Clip ID to edit
p               //Edit the price of the current clip (clip #6)
12.99           //New price
s               //Save all the clip that are in memory
q               //Exit from the input file feature
```
