#include "NTRUencrypt.h"


// Polynomial Mathematic Functions
int NTRUencrypt::polynomialDegree(int *p, int size) {
    for(int i = size - 1; i > -1; i--) {
        if(p[i] != 0)
            return i;

        i--;
    }
}

int NTRUencrypt::modularInverse(int p, int m) {
    if(abs(p) >= m)
        p = p % m;
    if(p < m)
        p = p + m;

    int q, r, z;
    int r1 = m;
    int z1 = 0;
    int z2 = 1;

    for(int r2 = p; r2 > 0; r2 = r) {
        q = r1 / r2;
        r = r1 - q * r2;
        r1 = r2;
        z = z1 - 1 * z2;
        z1 = z2;
        z2 = z;
    }

    if(z1 < 0) {
        z1 - m + z1;
    }
    return z1;
}

void NTRUencrypt::modulusReduction(int *p, int size, int mod, int *reducedPolynomial) {
    for(short int i = 0; i < size; i++) {
        reducedPolynomial[i] = p[i] % mod;
        if(reducedPolynomial[i] < 0)
            reducedPolynomial[i] = reducedPolynomial[i] + mod;
    }
}

void NTRUencrypt::polynomialSum(int *p1, int *p2, int *resultPolynomial) {
    for(int i = 0; i < (sizeof(p1) / sizeof(int)); i++)
        resultPolynomial[i] = p1[i] + p2[i];
}

void NTRUencrypt::polynomialMultiplication(int *p1, int *p2, int size, int *resultPolynomial) {
    int *output = new int [size];
    int *temp1 = new int [size];
    int *temp2 = new int [size];

    int resultSize = ((sizeof(p1) / sizeof(int)) - 1) + (sizeof(p2) / sizeof(int));     // Calculates the number of elements in the resulting polynomial

    for(int i = 0; i <  (sizeof(p1) / sizeof(int)); i++)    // First entry in the array can be multiplied by everything
        output[i] = p1[0] * p2[i];
    
    memcpy(temp1, p2, size * 2);

    for(int i = 1; i < size - 1; i++) {
        fxMulX(temp1, size, temp1);

        for(int j = 0; j < size; j++) {
            scalarMultiplication(temp1, size, p1[i], temp2);
            output[j] = output[j] + temp1[j];
        }
    }

    memcpy(resultPolynomial, output, size * 2);     // Copy the output the the resultPolynomial input
    delete[] output, temp1, temp2;
}

void NTRUencrypt::fxDivX(int *p, int size, int *resultPolynomial) {
    int *output = new int [size];

    memcpy(output, p, size * 2);

    if(polynomialDegree(output, size) == (size - 1 )) {
        for(int i = 1; i < size; i++)
            output[i - 1] = p[i];
        
        output[size - 1] = p[0];
    } else {
        for(int i = 1; i < (size - 1); i++)
            output[i - 1] = p[i];
        
        output[size - 2] = p[0];
    }

    memcpy(resultPolynomial, output, size * 2);
    delete[] output;
}

void NTRUencrypt::fxMulX(int *p, int size, int *resultPolynomial) {
    int *output = new int [size];

    for(int i = size - 2; i > 0; i--)
        output[i] = p[i - 1];

    output[0] = p[size - 2];
    output[size - 1] = 0;

    memcpy(resultPolynomial, output, size * 2);
    delete[] output;
}

void NTRUencrypt::scalarMultiplication(int *p, int size, int s, int *resultPolynomial) {
    int *output = new int [size];

    for(int i = 0; i < size; i++)
        output[i] = s * p[i];

    memcpy(resultPolynomial, output, size * 2);
    delete[] output;
}

void NTRUencrypt::inversePolynomial(int *p, int size, int mod, char modPower, int *resultPolynomial) {
    int k = 0;
    int *output = new int [size];
    memset(output, 0, size * 2);
    int *c = new int [size];
    memset(c, 0, size * 2);
    int *f = new int [size];
    memcpy(f, p, size * 2);
    int *g = new int [size];
    memset(g, 0, size * 2);
    int *temp = new int [size];

    output[0] = 1;
    g[0] = -1;
    g[size - 1] = 1;

    //int count = 0;
    for(int i = 0; i < (size * size); i++) {
        while(f[0] == 0) {
            fxDivX(f, size, f);
            fxMulX(c, size, c);
            k = k + 1;
        }

        if(polynomialDegree(f, size) == 0) {
            scalarMultiplication(output, size, modularInverse(f[0], mod), output);
            modulusReduction(output, size, mod, output);

            for(int j = 0; j < abs(size - k - 1); i++)
                fxDivX(output, size, output);

            //int q = mod;
            for(int j = mod; j < pow((double) mod, (double) modPower); j = j * j) {
                polynomialMultiplication(p, output, size, temp);
                scalarMultiplication(temp, size, -1, temp);
                temp[0] = temp[0] + 2;
                polynomialMultiplication(output, temp, size, output);

                modulusReduction(output, size, (int) pow((double) mod, (double) modPower), output);
            }

            memcpy(resultPolynomial, output, size * 2);
            delete[] output;
            delete[] c;
            delete[] f;
            delete[] g;
            delete[] temp;

            return;
        }

        if(polynomialDegree(f, size) < polynomialDegree(g, size)) {
            int *f1 = f;
            f = g;
            g = f1;
            int *b1 = output;
            output = c;
            c = b1;
        }

        int u = (f[0] * modularInverse(g[0], mod)) % mod;
        if(u < 0)
            u = mod + u;

        for(int i = 0; i < size; i++) {
            f[i] = (f[i] - u * g[i]);
			f[i] = f[i] % mod;
			if(f[i] < 0)
				f[i] = mod + f[i];

			output[i] = (output[i] - u * c[i]);
			output[i] = output[i] % mod;
			if(output[i] < 0)
				output[i] = mod + output[i];
        }
    }

    errorLog = "Polynomial is irreversible";
    delete[] output, c, f, g, temp;
    return;
}


// Generator Functions
void NTRUencrypt::fPolynomialGenerator(int size, int *resultPolynomial) {
    int *output = new int [size];
    int number;
    int i = 0;

    memset(output, 0, size * 2);

    while(i < df) {
        number = rand() % (size - 1);
        if(output[number] == 0) {
            output[number] = 1;
            i++;
        }
    }

    i = 0;
    while(i < (df - 1)) {
        number = rand() % (size - 1);
        if(output[number] == 0) {
            output[number] = -1;
            i++;
        }
    }

    memcpy(resultPolynomial, output, size * 2);
    delete[] output;
}

void NTRUencrypt::gPolynomialGenerator(int size, int *resultPolynomial) {
    int *output = new int [size];
    int number;
    int i = 0;

    memset(output, 0, size * 2);

    while(i < dg) {
        number = rand() % (size - 1);
        if(output[number] == 0) {
            output[number] = 1;
            i++;
        }
    }

    i = 0;
    while(i < (dg)) {
        number = rand() % (size - 1);
        if(output[number] == 0) {
            output[number] = -1;
            i++;
        }
    }

    memcpy(resultPolynomial, output, size * 2);
    delete[] output;
}

void NTRUencrypt::publicKeyGenerator(int *fPolynomial, int *gPolynomial, int size, int *resultPolynomial) {
    int *output = new int [size];
    
    inversePolynomial(fPolynomial, size, modQ, qDeg, output);
    scalarMultiplication(output, size, modP, output);
    polynomialMultiplication(output, gPolynomial, size, output);

    if(qDeg < 1)
        errorLog = "Wrong inpout of exponent of modulus q: default value of 1 was used";
    if(qDeg >= 1)
        modulusReduction(output, size, (int) pow((double) modQ, (double) qDeg), output);
    
    memcpy(resultPolynomial, output, size * 2);
    delete[] output;
}


// Public Functions
std::string NTRUencrypt::generatePrivateKey(int seed) {
    // Create the arrays and generate the polynomials
    int *fPolynomial = new int [N];
    int *gPolynomial = new int [N];
    fPolynomialGenerator(N, fPolynomial);
    gPolynomialGenerator(N, gPolynomial);

    // Cycle through every index in both f and g polynomials, pushing data onto the end of the string
    std::string output;
    for(int i = 0; i < N; i++)
        output = output + "-" + std::to_string(fPolynomial[i]);
    delete[] fPolynomial;
    for(int i = 0; i < N; i++)
        output = output + "-" + std::to_string(gPolynomial[i]);
    delete[] gPolynomial;

    return output;
}