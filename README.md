VelociraptorAES
===============

ECE 2524 final project. An implementation of AES and message sending.
<h2>Usage</h2>
For the server: Start the server with ./server.py port
For the client: Start the client with ./client.py host port username

Where host is the IP where the server is located, the port is the port over which the connection is established.
The username is purely for identification and can be anything you want.

<h2>Requirements</h2>
python3

<h2>Description</h2>
A server-client chat protocol that uses AES-256 for secure communication.

<h2>Limitations</h2>
Dues to bad initial design, the messages are only sent and received whenever a new message is typed. Meaning, the conversations are not exactly real-time.

Another limitation is the issue with AES working with the server and client, as right now it does not fully encrypt and decrypt the communication.

<h2>Members</h2>
James Gross, Matthew O'Neil, Michael Dunn, Lukas Lozovski
