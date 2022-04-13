# MTRX2700-CLab-Group4
Ethan Foster, George Head, Sam Kember


1. Serial with inputs 











2. Serial with Command parser









3. Music Module
In the music module, the 7 notes that will be used are defined in a .h file. These sound values correlated with each note on a musical scale A-G as well as a 'rest' value that has no sound. 

Within the music.c file, all the code necessary for understanding the command input and outputing music is present. The file starts with a definition of the 3 songs that this module can play. The songs are built using a letter number pairing. The letter is the note to be played and the number is the length of time (1-3) which has being defined. 

All relevants ports that need to be enabled/disabled are done so in the enable_speaker & disable_speaker functions, which will be called in the main function. 

To create, the time that a not plays for 3 delay functions have being written. These unitlise the timer and overflow flags. Using different prescalars to create different 'delays'. This will make the note play for a longer or shorter time depending on the delay. An 'inbetween' delay function is also used to create spaces in between notes so there is not one continuous sound.

The songPlay function will put all the information together based on the song that has being choosen to be played by the inputed command (1-3). This will loop through each note & time length and correctly execute it on the dragon board. The note is read first, followed by the delay command (1-3) which is assigned to the correct delay function. The number of the song executed (1-3) is also displayed on the 7seg display on the dragon board. After each note is played, the 'inbetween' function is called to create a gap between each note.

