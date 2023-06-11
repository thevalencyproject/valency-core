#ifndef NTRUENCRYPT_H
#define NTRUENCRYPT_H

#include <cmath>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>


class NTRUencrypt {
private:
    // Configuration - These parameters can be found online to deduce the security margin (128, 192, 256bit) <- this will be dynamically allocated from the constructor in future updates!!!
    int N, size;     // N and size are the same parameters
    int modP;
    int modQ;
    int df;          // F Polynomial Generation
    int dg;          // G Polynomial Generation
    int dr;          // R Polynomial Generation
    char qDeg = 1;

    // Polynomial Mathematical Functions
    int polynomialDegree(int *p);                                                     // Degree of the input polynomial 'p'
    int modularInverse(int p, int m);                                                 // Modular Inverse number to p: p^-1 mod m
    void modulusReduction(int *p, int mod, int *reducedPolynomial);                   // Modulus Reduction of p
    void polynomialSum(int *p1, int *p2, int *resultPolynomial);                      // Add p1 and p2: f(x) + g(x)
    void polynomialMultiplication(int *p1, int *p2, int *resultPolynomial);           // Multiply p1 and p2: f(x) * g(x) - ENSURE THAT p2 is the smaller polynomial if they are not of equal size
    void fxDivX(int *p, int *resultPolynomial);                                       // f(x) / x
    void fxMulX(int *p, int *resultPolynomial);                                       // f(x) * x
    void scalarMultiplication(int *p, int s, int *resultPolynomial);                  // Multiply p by s: f(x) * s, where 's' is a constant
    void inversePolynomial(int *p, int mod, char modPower, int *resultPolynomial);    // Inverse Polynomial of p: x^k - x^(k-1) + ... + x^2 + 1 -> {1, 0, 1, ..., -1, 1}

    // Conversions
    void charToArray(char c, int *array);
    char arrayToChar(int *array);
    void stringToArray(std::string message, int *array);
    std::string arrayToString(int *array, int size);
    void decimalToHex(int *decimal, std::string *hex);      // Called using: hexToDecimal(&hex, &decimal);
    void hexToDecimal(std::string *hex, int *decimal);
    std::string decodeString(std::string *key);

    // Generators: f & g Polynomial make up the private key, and the h Polynomial is the public key
    void fPolynomialGenerator(int df, int *resultPolynomial);                             // f Polynomial Generator - First half of a private key
    void gPolynomialGenerator(int dg, int *resultPolynomial);                             // g and r polynomial generator - Second half of a private key (r is the random polynomial)
    void publicKeyGenerator(int *fPolynomial, int *gPolynomial, int *resultPolynomial);   // h Polynomial Generator - The public key

    // Encryption + Decryption: m Polynomial is the plaintext message represented in Polynomial form, fpPolynomial is the modular inverse of fPolynomial modulo 'p'
    void encryption(int *mPolynomial, int *hPolynomial, int *resultPolynomial);                             // Encryption h = public polynomial
    void decryption (int *cipherPolynomial, int *fPolynomial, int *fpPolynomial, int *resultPolynomial);    // Decryption: Cypher = Encrypted Data, 

public:
    NTRUencrypt(int strength);
    ~NTRUencrypt();

    std::string errorLog;

    std::string generatePublicKey(std::string privateKey);  // Public Key Generator
    std::string generatePrivateKey(int seed);               // Private Key Generator - private key is fPolynomial with gPolynomial attached on the end of it

    std::string encrypt(std::string receiverKey, std::string data);     // Uses string encryption, translates the resultPolynomial into hexadecimal
    std::string decrypt(std::string privateKey, std::string data);      // Uses string decryption, translates data from hexidecimal into a string array
};

#endif