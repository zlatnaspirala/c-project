
 - Successed tested on macos.


Protocol : UDP
Encryption: XOR encryption

Algorithm :

1. The server starts and waits for filename.
2. The client sends a filename.
3. The server receives filename.
   If file is present,
   server starts reading file
   and continues to send a buffer filled with
   file contents encrypted until file-end is reached.
4. End is marked by EOF.
5. File is received as buffers until EOF is
received. Then it is decrypted.
6. If Not present, a file not found is sent.
