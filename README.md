# Valency Core
Each module in this repository is designed to be modular for reuse in other cool open-source projects!<br><br>
**This repository contains the following core modules used to build the valency project:**<br>
1. A Networking Framework
2. Onion Routing
3. AES Symmetric Encryption
4. NTRUencrypt Asymmetric Encryption
5. Random Algorithm
6. Console UI Framework
7. File Reader and Writer
8. Quicksort
9. SHA-256 Hashing Algorithm
<br>

## Networking Framework
The networking framework is based on a client-server relationship, and requires custom configuration of some handling functions to achieve your desired functionality. <br>
There will be an update in the near future introducing multi-threaded networking, however for now it is only single-threaded.<br><br>
**Client**
1. Configure the communicate() function in Client.cpp to achieve your desired outcomes (See example implementation for help creating your own implementation)
2. Include Client.h: ```#include "Client.h"```
3. Create a Client Object: ```Client c;```
4. Get the Server IP Address and Port: ```std::string ip = "192.168.1.1"; int port = 8088;```
5. Connect to the server - this will automatically communicate using the communicate() function we configured earlier: <br>
```c.connectToServer(&ip, &port);```

<br>

**Server**
1. Configure the handleConnection() function in Server.cpp to achieve your desired outcomes (See example implementation for help creating your own implementation)
2. Include Server.h: ```#include "Server.h"```
3. Create a Server Object: ```Server s;```
4. Get the port: ```int port = 8088;```
5. Run the server - this will automatically handle connections using the handleConnection() function we configured earlier: <br>
```s.run(&port);```

<br>

## Onion Routing

## AES Symmetric Encryption

## NTRUencrypt Asymmetric Encryption

## Random Algorithm
**How to Use It:**
1. Include Random.h: ```#include "Random.h"```
2. Create a Random Object: ```Random r;```
3. Get a minimum, maximum, and seed value - seed is simply a random integer: ```int min = 0, max = 10, seed = 3;```
4. Call the random function somewhere - this will return a random integer between the minimum and maximum defined in step 3: <br>
```r.getRandomNumber(&min, &max, &seed);```, or in use: ```int output = r.getRandomNumber(&min, &max, &seed);```

<br>

## Console UI Framework

## File Reader and Writer

## Quicksort

## SHA-256 Hashing Algorithm
**How to Use It:** 
1. Include SHA256.h: ```#include "SHA256.h"```
2. Create a SHA256 Object: ```SHA256 sha;```
3. Get some kind of input - hash() function takes a char[]: ```char data[] = "HASH THIS DATA!";```
4. Call the hash function somewhere - this will return the hash of the input data as a string: <br>
```sha.hash(data);```, or in use: ```std::string output = sha.hash(data);```

<br>

## LZMA Compression Algorithm

## Traceable Ring Signatures

## GUI Framework

## Custom Types
