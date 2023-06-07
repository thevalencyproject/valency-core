#ifndef NTRUENCRYPT_H
#define NTRUENCRYPT_H

#include <string>


class NTRUencrypt {
private:
    int bits;
    
    // Polynomial Mathematical Functions
    int polynomialDegree(int *p, int size);                                                    // Degree of the input polynomial 'p': size is the size of 'a'
    int modularInverse(int p, int m);                                                          // Modular Inverse number to p: p^-1 mod m
    void modulusReduction(int *p, int size, int modulus, int *reducedPolynomial);              // Modulus Reduction of p
    void polynomialSum(int *p1, int p2, int size, int *resultPolynomial);                      // Add p1 and p2: f(x) + g(x)
    void polynomialMultiplication(int *p1, int *p2, int size, int *resultPolynomial);          // Multiply p1 and p2: f(x) * g(x)
    void fxDivX(int *p, int size, int *resultPolynomial);                                      // f(x) / x
    void fxMulX(int *p, int size, int *resultPolynomial);                                      // f(x) * x
    void scalarMultiplication(int *p, int size, int s, int *resultPolynomial);                 // Multiply p by s: f(x) * s, where 's' is a constant
    void inversePolynomial(int *p, int size, int mod, char modPower, int *resultPolynomial);   // Inverse Polynomial of p: x^k - x^(k-1) + ... + x^2 + 1 -> {1, 0, 1, ..., -1, 1}
    
public:
    NTRUencrypt(int strength);
    ~NTRUencrypt();

    std::string generatePublicKey(std::string privateKey);  // Public Key Generator
    std::string generatePrivateKey(int seed);               // Private Key Generator - private key is fPolynomial with fpPolynomial attached on the end of it

    std::string encrypt(std::string privateKey, std::string receiverKey, std::string data);
    std::string decrypt(std::string privateKey, std::string receiverKey, std::string data);
};

#endif