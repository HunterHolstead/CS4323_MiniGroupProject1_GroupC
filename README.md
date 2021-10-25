# CS4323_MiniGroupProject1_GroupC

Compile the server: "gcc -o server serverDriver.c -lpthread"
Compile the client: "gcc -o client clientDriver.c MessagePassing.c -lpthread"
Run server: ./server
Run client: ./client
***Note: Server must be ran before client in order to properly work!

OVERVIEW: 
This program is designed to create a multithreaded server which receives messages from clients, 
which will scan whether or not the message sent contains misspelled items or not, 
and upon sending a correctly spelled message, the program will encrypt and store the message. 
If the user requests a file they have sent, the program will decrypt the 
message and display the original message given by the user. 

CLIENT:
The client program will show the functionality of the menu, message passing, encryption, and thread
creation/management. The menu will display Options 1-3, and will act 
depending on the option chosen. 

Option 1 sends data to the server through message passing by creating 
Processes A and B. Process A will prompt the user
to enter their message, and Process B will read the message. 
From there, Process B will determine if the message contains words
within the dictionary.txt file provided in the assignment. 
If Process B finds an invalid word, it will notify the user of which word is invalid.
Once the message has been given with no errors, the thread creation/management
function creates Thread T on the heap so that it may be reused after its initial creation. This thread
will eventually handle the encryption and communicate with the server.

Option 2 connects to the server and has the user choose which file it
wants to receive from the server. From there, the client process will 
decrypt the message and display it to the console. 

Option 3 closes all running processes and exits the program.

SERVER:
The server program will show a demonstration of a queued entry of clients via mutex locks and condition
variables, as well as the creation/management of a thread pool consisting of three threads. Test messages
will be printed five seconds after the entry of each client to show the functionality.
