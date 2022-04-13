# MTRX2700 Assignment 2
### Group 4 Members
Ethan Foster, George Head, Sam Kember

## Modules
This project was split into specific modules, each of which add a different functionality. The project was desgined such that adding more commands/functions would be as simple as adding another module. Each of the modules were tested using the CodeWarrior simulator and debugger, as well as using the physical HCS12 Dragonboard, particularly for the 7 segment and music modules.

### Serial input
The serial input module allows the microcontroller to recieve data through its serial port(s). This module uses interrupts from the RDRF flag, such that time is not wasted polling the serial port. This module is interfaced with in `main.c ` by first selecting SCI0 or SCI1, enabling recive interrupts and calling the `get_next_input()` function. As serial data becomes available, an interrupt is triggered, and the data is read from the serial port into a buffer using `read_char()`. When the specified `bookend` character appears in the serial ports data register, a flag is raised and the input buffer is returned by `get_next_input`.

### Command Parsing
This module uses the output of the serial input module to determine if a command is being called. The function `parse_command()` takes a string as an input and if the string is a command keyword (`music`, `7segs` or `print`), it will wait until the required parameters are input and then execute the command. If the string is not a command keyword, an error message is output. Each command requires different parameters, which are acquired from the serial port using the `get_next_input()` function. From there, the parameters are given to each of the modules below.

### Serial output
The serial output module is interfaced with using the `print` keyword for serial input. The microcontroller will then wait firstly for a string which is to be output via the serial port, and then for a number, which is the number of times the string should be output. The `print_command` function then copies the output string to the output buffer and enables transmission interrupts. From there when an interrupt is triggered the function `send_message` is called which iterates through the string and outputs it to the serial port, however many times is required, before finally disabling interrupts so a new command can be called.

### Music Module
In the music module, the 7 notes that will be used are defined in a .h file. These sound values correlated with each note on a musical scale A-G as well as a 'rest' value that has no sound. 

Within the `music.c` file, all the code necessary for understanding the command input and outputing music is present. The file starts with a definition of the 3 songs that this module can play. The songs are built using a letter number pairing. The letter is the note to be played and the number is the length of time (1-3) which has being defined. 

All relevants ports that need to be enabled/disabled are done so in the `enable_speaker` & `disable_speaker` functions, which will be called in the main function. 

To create, the time that a not plays for 3 delay functions have being written. These unitlise the timer and overflow flags. Using different prescalars to create different 'delays'. This will make the note play for a longer or shorter time depending on the delay. An 'inbetween' delay function is also used to create spaces in between notes so there is not one continuous sound.

The `songPlay` function will put all the information together based on the song that has being choosen to be played by the inputed command (1-3). This will loop through each note & time length and correctly execute it on the dragon board. The note is read first, followed by the delay command (1-3) which is assigned to the correct delay function. The number of the song executed (1-3) is also displayed on the 7seg display on the dragon board. After each note is played, the 'inbetween' function is called to create a gap between each note.

### 7 Segment Module


