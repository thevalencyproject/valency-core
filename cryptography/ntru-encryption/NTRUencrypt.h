#ifndef NTRUENCRYPT_H
#define NTRUENCRYPT_H

#include <string>


class NTRUencrypt {
private:
    // Configuration - These parameters can be found online to deduce the security margin (128, 192, 256bit) <- this will be dynamically allocated from the constructor in future updates!!!
    int N = 701;
    int modP = 3;
    int modQ = 8192;
    char qDeg;
    int df;         // F Polynomial Generation
    char dg;        // G Polynomial Generation

    // Polynomial Mathematical Functions
    int polynomialDegree(int *p, int size);                                                     // Degree of the input polynomial 'p': size is the size of 'p'
    int modularInverse(int p, int m);                                                           // Modular Inverse number to p: p^-1 mod m
    void modulusReduction(int *p, int size, int mod, int *reducedPolynomial);                   // Modulus Reduction of p
    void polynomialSum(int *p1, int *p2, int *resultPolynomial);                                // Add p1 and p2: f(x) + g(x)
    void polynomialMultiplication(int *p1, int *p2, int size, int *resultPolynomial);           // Multiply p1 and p2: f(x) * g(x) - ENSURE THAT p2 is the smaller polynomial if they are not of equal size
    void fxDivX(int *p, int size, int *resultPolynomial);                                       // f(x) / x
    void fxMulX(int *p, int size, int *resultPolynomial);                                       // f(x) * x
    void scalarMultiplication(int *p, int size, int s, int *resultPolynomial);                  // Multiply p by s: f(x) * s, where 's' is a constant
    void inversePolynomial(int *p, int size, int mod, char modPower, int *resultPolynomial);    // Inverse Polynomial of p: x^k - x^(k-1) + ... + x^2 + 1 -> {1, 0, 1, ..., -1, 1}
    
    // Conversions
    void stringToArray(std::string message, int *array);
    std::string arrayToString(int *array, int size);
    void decimalToHex(int *decimal, char *hex);
    void hexToDecimal(char *hex, int *decimal);
    
    // Generators
    void fPolynomialGenerator(int size, int *resultPolynomial);                                     // f Polynomial Generator
    void gPolynomialGenerator(int size, int *resultPolynomial);                                     // g, r polynomial generator
    void publicKeyGenerator(int *fPolynomial, int *gPolynomial, int size, int *resultPolynomial);   // h open key generation
    
public:
    NTRUencrypt(int strength);
    ~NTRUencrypt();

    std::string generatePublicKey(std::string privateKey);  // Public Key Generator
    std::string generatePrivateKey(int seed);               // Private Key Generator - private key is fPolynomial with fpPolynomial attached on the end of it

    std::string encrypt(std::string privateKey, std::string receiverKey, std::string data);
    std::string decrypt(std::string privateKey, std::string receiverKey, std::string data);
};

#endif
