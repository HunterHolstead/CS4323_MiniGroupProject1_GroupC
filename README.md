# CS4323_MiniGroupProject1_GroupC
A MakeFile has been included in order to make compiling every file together easier. To use MakeFile, convert from .txt to normal MakeFile. From there, you should only have to type in the command *"make"* or *"make groupC"* in order to compile the code. Then, entering *"./groupC"* should run the program. ***Do note that there may be compiler warnings, as the code is not fully completed, but it does run the code intended to be shown so far.***


Compile the server: "gcc -o server MiniProject_Cook_Isabell.c -lpthread"
Compile the client: "gcc -o main main.c -lpthread"
Run server: ./server
Run client: ./client

OVERVIEW:
This version of the project is a proof-of-concept, and as such, parts of the  functionality have yet
to be implemented. Furthermore, interoperability between functions has not been fully implemented.

CLIENT:
The client program will show the functionality of the menu, message passing, encryption, and thread
creation/management. The menu will display Options 1-3, but only 1 and 3 are currently operational.

Option 1 simulates the message passing by creating Processes A and B. Process A will prompt the user
for a message, and Process B will read the message. The invalid word functionality has not yet been
implemented, but the encryption/decryption code is functional. Lastly, the thread creation/management
function creates Thread T on the heap so that it may be reused after its initial creation. This thread
will eventually handle the encryption and communicate with the server.

Option 3 exits the client program.

SERVER:
The server program will show a demonstration of a queued entry of clients via mutex locks and condition
variables, as well as the creation/management of a thread pool consisting of three threads. Test messages
will be printed five seconds after the entry of each client to show the functionality.
