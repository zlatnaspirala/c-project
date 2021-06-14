# Port Scanner
A simple port scanner tool for Windows.

## Usgae:
*"Port Scanner.exe" ip out threads*
*ip* is the IP address that will be scanned. You can use ip address or domain name.
*out* is the path to the output file. **The output file will be overwritten**.
*threads* is the number of threads that will be created. This number can move between 1 to 65536.

**Usage examples:**
~~~
"Port Scanner.exe" www.example.com example_ports.txt 1024
"Port Scanner.exe" 93.184.216.34 93.184.216.34_ports.txt 2048
~~~

**Important**
The threads share the scanning process. Every thread scans it's own ports. You **can** use lots of threads (for example, 32768 threads, 2 ports per thread) but it will slow down your PC. For the best results, the number of threads that you should use has to be 1024/2048/4096/8192.
