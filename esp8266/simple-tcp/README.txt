## Simple TCP example for ESP8266 boards

This is a simple example that uses the WIFI client to establish a TCP connection.  The code
does the followings:
 - Connects to a specified host
 - Sends a clear text message
 - Read and print the message to Serial.

The server used to test this example is a simple ECHO server that is written in Go.  It does
the following
 - Listens to incoming connection
 - Upon connecting, it reads incoming bytes
 - Then sends the read bytes back to client.

# Running the sketch
1) Update the sketch with the proper information for WIFI connetion
2) Compile and upload the program 
3) Open the Serial Monitor to see output from program

# Running the Go program
$> go run simplesvr.go
