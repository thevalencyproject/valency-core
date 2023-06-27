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
10. LZMA Compression Algorithm
11. Traceable Ring Signatures
12. GUI Framework
<br>

**Scroll Down for Implementation Instructions**

<br>
<br>
<br>
<br>
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
4. Create a Client Object: ```Client client;```
5. Get the Server IP Address, Port, and communicate() function pointer: <br>```std::string ip = "192.168.1.1"; int port = 8088; std::string (*comm)(std::string) = communicate;```
6. Connect to the server - this will automatically communicate using the communicate() function we configured earlier: <br>
```client.connectToServer(&ip, &port, comm);```

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
4. Create a Server Object: ```Server server;```
5. Get the Port and communicate() function pointer: <br>```int port = 8088; std::string (*comm)(std::string) = communicate;```
6. Run the server - this will automatically communicate with clients using the communicate() function we configured earlier: <br>
```server.run(&port, comm);```

<br>
<br>
<br>
<br>
<br>

## Onion Routing
**Onion Client** <br>
1. Include Onion.h: ```#include "Onion.h";```
2. Create an Onion Object: ```Onion onion;```
3. Create a vector of the Node's you would like to route traffic through: <br>
```
NodeInfo n1(NetworkLocation l1(port1, ip1), nodeNTRUPublicKey1);
NodeInfo n2(NetworkLocation l2(port2, ip2), nodeNTRUPublicKey2);
NodeInfo n3(NetworkLocation l3(port3, ip3), nodeNTRUPublicKey3);

std::vector<NodeInfo> nodes;
nodes.push_back(n1); nodes.push_back(n2); nodes.push_back(n3); 
```
4. Get the data you want to send: ```std::string data = "Some Data!";```
5. Create a communicate() function - This is the function that gets run everytime there is a message from the destination server, it takes in a string (server message), and returns a string (what you want to send back to the server). <br>
```
std::string communicate(std::string serverMessage) {
  if(serverMessage == "Some Data") {
    return "Some Reply";
  } else {
    return "/quit";
  }
}
```
6. Call the onionRouting() function - this will communicate: ```onion.onionRouting(nodes, data, communicate);```
<br>

**Onion Node** <br>
1. Include OnionNode.h: ```#include "OnionNode.h"```
2. Create an OnionNode object - this takes in the port in which communication is made: ```OnionNode node = OnionNode(some_port);```
3. Get an NTRUencrypt public and private key (this can be done using the NTRUencrypt framework in Valency Core): <br>
```std::string private = "Some Private Key"; std::string public = "Some Public Key";```
4. Call the initialise() function - this takes in the private and public keys: ```node.initialise(public, private);```
5. Call the run() function: ```node.run();```

<br>
<br>
<br>
<br>
<br>

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
<br>
<br>
<br>
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
<br>
<br>
<br>
<br>

## Random Algorithm
**How to Use It:**
1. Include Random.h: ```#include "Random.h"```
2. Create a Random Object: ```Random random;```
3. Get a minimum, maximum, and seed value - seed is simply a random integer: ```int min = 0, max = 10, seed = 3;```
4. Call the random function somewhere - this will return a random integer between the minimum and maximum defined in step 3: <br>
```random.getRandomNumber(&min, &max, &seed);```, or in use: ```int output = random.getRandomNumber(&min, &max, &seed);```

<br>
<br>
<br>
<br>
<br>

## Console UI Framework
This UI framework takes strings as input for single-line functions, and string vectors for multi-line functions. <br>
The module supports multiple styles, with the ability to add custom styles (submit a pull request):

| Style         | Number        |
|:-------------:|:-------------:|
| Box           | 0             |
| Minimalistic  | 1             |
| Hyphen        | 2             |
| Arrow         | 3             |

<br>

**Setup**<br>
1. Include ConsoleUI.h: ```#include "ConsoleUI.h"```
2. Create a ConsoleUI Object - this takes in your desired style: ```ConsoleUI ui = ConsoleUI(0);```

<br>

**Functionality**<br>
To call the functions, an input of either string (single-line) or string vector (multi-line) is required. Below is a table of single and multi line functions:

| Single-Line   | Multi-Line    |
|:-------------:|:-------------:|
|               | header()      |
| message()     | message()     |
| input()       | input()       |
|               | menu()        |

There also exists the footer() function which does not take an input. The setStyle() function takes in the style you want to switch to. <br>
Below are some example function implementations:

**Example 1.** Call the header() function to produce a header with the inputted titles: <br>
```
std::vector<std::string> headerText;
headerText.push_back("First Line");
headerText.push_back("Second Line");
ui.header(headerText);
```
will display the following when the style is Box:
```
 ______________________________
|                              |
|          First Line          |
|         Second Line          |
|______________________________|
```

<br><br>

**Example 2.** Call the menu() function to produce a menu with the inputed string vector and a closed top (this will return the user selection): <br>
```
std::vector<std::string> menuText;
menuText.push_back("First Option");
menuText.push_back("Second Option");
menuText.push_back("Third Option");
int userResponse = ui.menu(menuText, true);
```
will display the following when the style is Box:
```
 ______________________________
|                              |
|  Please Select One:          |
|   1. First Option            |
|   2. Second Option           |
|   3. Third Option            |
|______________________________|

    -> 
```

<br>
<br>
<br>
<br>
<br>

## File Reader and Writer
**File Reader** <br>
1. Include FileReader.h: ```#include "FileReader.h"```
2. Create a FileReader Object: ```FileReader reader;```
3. Get the path to the file you want to read: ```std::string path = "/folder/filename.extension";```
4. Call the getData function (this will return a string vector - each index is the next line): <br> ```std::vector<std::string> fileData = reader.getData(&path);```
<br>

**File Writer** <br>
1. Include FileWriter.h: ```#include "FileWriter.h"```
2. Create a FileWriter Object: ```FileWriter writer;```
3. Get the desired filename, and append it onto where you want the file to be written: <br>
```std::string path = "/folder/filename.extension";```
4. Get the data - this can be inputted as a string, or as a string vector: ```std::string data = "Some Data";```
5. Call the createFile function (this will write the file): ```writer.createFile(&data, &path);```

<br>
<br>
<br>
<br>
<br>

## Quicksort
**How to Use It:**
1. Include Quicksort.h: ```#include "Quicksort.h"```
2. Create a QuickSort Object: ```QuickSort qsrt;```
3. Get some kind of input - the sort() function takes an array of any numerical type: <br> 
```int n = 10; float array[n] = {15.23, 85.15, 25.0, 96.87, 64.45, 13.15, 90.25, 87.85, 36.97, 25.35};```
4. Call the sort function (takes in the leftmost index, and the pivot - usually rightmost index) - this will sort the input array: ```qsrt.sort(array, 0, n-1);```

<br>
<br>
<br>
<br>
<br>

## SHA-256 Hashing Algorithm
**How to Use It:** 
1. Include SHA256.h: ```#include "SHA256.h"```
2. Create a SHA256 Object: ```SHA256 sha;```
3. Get some kind of input - hash() function takes a char[]: ```char data[] = "HASH THIS DATA!";```
4. Call the hash function somewhere - this will return the hash of the input data as a string: <br>
```sha.hash(data);```, or in use: ```std::string output = sha.hash(data);```

<br>
<br>
<br>
<br>
<br>

## LZMA Compression Algorithm
**Setup** <br>
1. Include LZMA-Compression.h: ```#include "LZMA-Compression.h";```
2. Create an LZMACompression object: ```LZMACompression lzma;```
<br>

**Compression** <br>
1. Get the data you want to compress (taken in as a string or char vector): ```std::string data = "Some Data!";```
2. Call the compress function - this will return the compressed data as the input type: <br>
```std::string compressed = lzma.compress(&data);```
<br>

**Decompression** <br>
1. Get the compressed data you want to decompress (taken in as a string or char vector): <br>
```std::string compressed = "Compressed Data!";```
2. Call the decompress function - this will return the decompressed data as the input type: <br>
```std::string decompressed = lzma.decompress(&compressed);```

<br>
<br>
<br>
<br>
<br>

## Traceable Ring Signatures

<br>
<br>
<br>
<br>
<br>

## GUI Framework

<br>
<br>
<br>
<br>
<br>

## Custom Types
