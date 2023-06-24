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
std::string encrypt(std::string k, std::string d);10. LZMA Compression Algorithm
11. Traceable Ring Signatures
12. GUI Framework
<br>

## Networking Framework
The networking framework is based on a client-server relationship, and requires custom configuration of some handling functions to achieve your desired functionality. <br>
There will be an update in the near future introducing multi-threaded networking, however for now it is only single-threaded.<br><br>
**Client**
1. Create a communicate() function wherever you are implementing client networking - This is the function that gets run everytime there is a message from the server, it takes in a string (server message), and returns a string (what you want to send back to the server) - if ```/quit``` is returned, the client will disconnect. <br>
```
std::string communicate(std::string serverMessage) {
  if(serverMessage == "Some Data") {
    return "Some Reply";
  } else {
    return "/quit";
  }
}
```
3. Include Client.h: ```#include "Client.h"```
4. Create a Client Object: ```Client c;```
5. Get the Server IP Address, Port, and communicate() function pointer: <br>```std::string ip = "192.168.1.1"; int port = 8088; std::string (*comm)(std::string) = communicate;```
6. Connect to the server - this will automatically communicate using the communicate() function we configured earlier: <br>
```c.connectToServer(&ip, &port, comm);```

<br>

**Server**
1. Create a communicate() function wherever you are implementing client networking - This is the function that gets run everytime there is a message from the client, it takes in a string (client message), and returns a string (what you want to send back to the client). <br>
```
std::string communicate(std::string clientMessage) {
  if(clientMessage == "Some Data") {
    return "Some Reply";
  } else {
    return "Another Reply";
  }
}
```
3. Include Server.h: ```#include "Server.h"```
4. Create a Server Object: ```Server s;```
5. Get the Port and communicate() function pointer: <br>```int port = 8088; std::string (*comm)(std::string) = communicate;```
6. Run the server - this will automatically communicate with clients using the communicate() function we configured earlier: <br>
```s.run(&port, comm);```

<br>

## Onion Routing

## AES Symmetric Encryption
The AES-Encryption algorithm is used to encrypt and decrypt data using a single key. This framework allows for use of 128bit, 192bit, or 256bit AES-Encryption. The public functions allow for the input and output of either char vector's or strings (char vector step-by-step shown for encryption, and string step-by-step shown for decryption).<br>

<br>

**Encryption**
1. Include AES-Encryption.h: ```#include "AES-Encryption.h"```
2. Create an AESEncryption Object with either 128bit, 192bit, or 256bit: ```AESEncryption aes = AESEncryption(128)```
3. Get a data and a key - these are taken in as a string, or as a vector of unsigned char's (ensure the key is the correct keylength (128bit=16, 192bit=24, 256bit=32)): ```std::vector<unsigned char> key; std::vector<unsigned char> data;```
4. Call the encrypt function somewhere - this will return a either a string or a vector of unsigned char's as output: <br>
```std::vector<unsigned char> output = aes.encrypt(key, data);``` <br>
**Note**: The encryption function automatically saves the # of repeats that must be applied (this makes the cipher decryptable for any size).

<br>

**Decryption**<br>
1. Include AES-Encryption.h: ```#include "AES-Encryption.h"```
2. Create an AESEncryption Object with either 128bit, 192bit, or 256bit: ```AESEncryption aes = AESEncryption(128)```
3. Get a cipher and its related key - these are taken in as a string, or as a vector of unsigned char's (ensure the key is the correct keylength (128bit=16, 192bit=24, 256bit=32)): ```std::string key; std::string data;```
4. Call the decrypt function somewhere - this will return a either a string or a vector of unsigned char's as output: <br>
```std::string output = aes.decrypt(key, data);``` <br>

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
2. Create a NTRUencrypt Object with your desired parameters (see table - p parameters >2 are currently not supported):<br>
```NTRUencrypt ntru = NTRUencrypt(4)```
<br>

**Key Generation** <br>
The keysize is dependant on the strength chosen in the constructor. The private key consists of both the f and g polynomials - making it double the size of the public key.
1. Get a random seed - this could be from concatenating a login, or through the use of some random() function: <br>
```int seed = random("LOGIN" + "PASSWORD");```
2. Generate a private key using the random seed: ```std::string private = ntru.generatePrivateKey(seed);```
3. Generate a public key using the private key: ```std::string public = ntru.generatePublicKey(private);```
<br>

**Encryption** <br>
1. Get the input data as a string: ```std::string data = "Hello World!";```
2. Get the public key of the entity you want to encrypt for: ```std::string publicKey = "some_key";```
3. Generate the cipher using the encrypt function: ```std::string cipher = ntru.encrypt(publicKey, data);```
4. Send the cipher to the recipient (this could be done using the valency-core networking framework).
<br>

**Decryption** <br>
1. Get the cipher generated with your public key: ```std::string cipher = "some_data";```
2. Get your private key (generated with ntru.generatePrivateKey(seed)): ```std::string privateKey = "some_key";```
3. Decrypt the cipher using the decrypt function: ```std::string output = ntru.decrypt(privateKey, cipher);```
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
