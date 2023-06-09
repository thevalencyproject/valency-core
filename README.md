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
The AES-Encryption algorithm is used to encrypt and decrypt data using a single key. This framework allows for use of 128bit, 192bit, or 256bit AES-Encryption. <br>
**Note:** This implementation of AES is in VERY early stages of development, and I would not advise ANYBODY to use this for purposes where security and efficiency is required.

<br>

**Encryption**
1. Include AES-Encryption.h: ```#include "AES-Encryption.h"```
2. Create an AESEncryption Object with either 128bit, 192bit, or 256bit: ```AESEncryption aes = AESEncryption(128)```
3. Get a data and a key - these are taken in as a vector of unsigned char's (ensure the key is the correct keylength (128bit=16, 192bit=24, 256bit=32)): ```std::vector<unsigned char> key; std::vector<unsigned char> data;```
4. Call the encrypt function somewhere - this will return a vector of unsigned char's as output: <br>
```std::string output = std::to_string(aes.encrypt(key, data));``` <br>
**Note**: Please ensure that you save the input data length, as this makes the data decryptable.

<br>

**Decryption**<br>
Decryption is currently not supported - an implementation will be coming within the next week of this commit :)

<br>

## NTRUencrypt Asymmetric Encryption
**Selectable Parameters**<br>
This implementation allows for selectable parameters when calling the constructor. The chosen parameters for this implementation of NTRUencrypt come from the table:
|               | N             | p     | q     | df    | dg    | dr    |       | Constructor Call |
|:-------------:|:-------------:|:-----:|:-----:|:-----:|:-----:|:-----:|:-----:|:----------------:|
| NTRU167:2     | 167           | 2     | 127   | 45    | 35    | 18    |       | 1                |
| NTRU167:3     | 167           | 3     | 128   | 61    | 20    | 18    |       | 2                |
| NTRU251:2     | 251           | 2     | 127   | 35    | 35    | 22    |       | 3                |
| NTRU251:3     | 251           | 3     | 128   | 50    | 24    | 16    |       | 4                |
| NTRU503:2     | 503           | 2     | 253   | 155   | 100   | 65    |       | 5                |
| NTRU503:3     | 503           | 3     | 256   | 21    | 72    | 55    |       | 6                |

<p align="center">
Source: Cherckesova, L. et al. (2020) ‘Post-quantum cryptosystem NTRUEnCrypt and its advantage over pre – quantum cryptosystem RSA’, E3S Web of Conferences, 224, pp. 4–4. doi:10.1051/e3sconf/202022401037.
</p>
<br>

**Setup**
1. Include NTRUencrypt.h: ```#include "NTRUencrypt.h"```
2. Create a NTRUencrypt Object with your desired parameters (see table):<br>
```NTRUencrypt ntru = NTRUencrypt(4)```
<br>

**Key Generation** <br>
1. Get a random seed - this could be from concatenating a login, or through the use of some random() function: <br>
```int seed = random("LOGIN" + "PASSWORD");```
2. Generate a private key using the random seed: ```std::string private = ntru.generatePrivateKey(seed);```
3. Generate a public key using the private key: ```std::string public = ntru.generatePublicKey(private);```
<br>

**Encryption** <br>
Instructions coming once implementation is complete (~1 to 2 days)
<br>

**Decryption** <br>
Instructions coming once implementation is complete (~1 to 2 days)

<br>

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
**How to Use It:**
1. Include Quicksort.h: ```#include "Quicksort.h"```
2. Create a QuickSort Object: ```QuickSort qsrt;```
3. Get some kind of input - the sort() function takes an array of any numerical type: <br> 
```int n = 10; float array[n] = {15.23, 85.15, 25.0, 96.87, 64.45, 13.15, 90.25, 87.85, 36.97, 25.35};```
4. Call the sort function (takes in the leftmost index, and the pivot - usually rightmost index) - this will sort the input array: ```qsrt.sort(array, 0, n-1);```

<br>

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
