# Valency Core
**This repository contains the core files used to build the valency project.**<br>
**Each section/framework is designed to be modular for reuse in other cool open-source projects!**<br>

## Valency-Core consists of the following modular components:
### Networking Framework
### Onion Routing
### AES Symmetric Encryption
### NTRUencrypt Asymmetric Encryption
### Random Algorithm
**How to Use It:**
1. Include Random.h: ```#include "Random.h"```
2. Create a Random Object: ```Random r;```
3. Get a minimum, maximum, and seed value - seed is simply a random integer: ```int min = 0, max = 10, seed = 3;```
4. Call the random function somewhere - this will return a random integer between the minimum and maximum defined in step 3: <br>
```r.getRandomNumber(&min, &max, &seed);```, or in use: ```int output = r.getRandomNumber(&min, &max, &seed);```
### Console UI Framework
### File Reader and Writer
### Quicksort
### SHA-256 Hashing Algorithm
**How to Use It:** 
1. Include SHA256.h: ```#include "SHA256.h"```
2. Create a SHA256 Object: ```SHA256 sha;```
3. Get some kind of input - hash() function takes a char[]: ```char data[] = "HASH THIS DATA!";```
4. Call the hash function somewhere - this will return the hash of the input data as a string: <br>
```sha.hash(data);```, or in use: ```std::string output = sha.hash(data);```
### LZMA Compression Algorithm
### Traceable Ring Signatures
### GUI Framework
### Custom Types
