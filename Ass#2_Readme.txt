                                                       //#OS_LAB-2_SERVER


Server will return list of files present in directory to client,and client will select one of the
file and request to the server to 
send on request of client the server will fork() a child process
to handle the file transfer smoothly with that specific client.
Statistics about each transfer session
(e.g. number of send(), total bytes transferred,client ID, file name, time taken to transfer 
the 
whole file etc.) will  be stored in the newly created file logfile.txt in the server).  Here
socket programming related systems 
calls used in the client server file. 
Here server can connect 
to the multiple clients during the execution fork() is working properly .


                             



                                      ***to run  code 
 

1..run the gen.sh file to generate 100 .txt files--./gen.sh 1 100
   
 2..run the server.c file---
arguments reqquired Server ------IP address and port number is to passed as  arguments
   
 3..run the client.c file---
arguments reqquired client ------port number  

(multiple clients can be connected to the server)


client ask for a file name from the file list provided by the serverfor tranfering.


server will send the geven file and store the informations of that tranfer session in a log file.


