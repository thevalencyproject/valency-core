#include "NTRUencrypt.h"


// Polynomial Mathematic Functions
int NTRUencrypt::polynomialDegree(int *p) {
    for(int i = size - 1; i > -1; i--) {
        if(p[i] != 0)
            return i;

        i--;
    }

    errorLog = "Invalid Polynomial Degree";
    return 1;
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

void NTRUencrypt::modulusReduction(int *p, int mod, int *reducedPolynomial) {
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

void NTRUencrypt::polynomialMultiplication(int *p1, int *p2, int *resultPolynomial) {
    int *output = new int [size];
    int *temp1 = new int [size];
    int *temp2 = new int [size];

    int resultSize = ((sizeof(p1) / sizeof(int)) - 1) + (sizeof(p2) / sizeof(int));     // Calculates the number of elements in the resulting polynomial

    for(int i = 0; i <  (sizeof(p1) / sizeof(int)); i++)    // First entry in the array can be multiplied by everything
        output[i] = p1[0] * p2[i];
    
    memcpy(temp1, p2, size * 2);

    for(int i = 1; i < size - 1; i++) {
        fxMulX(temp1,temp1);
    }

    memcpy(resultPolynomial, output, size * 2);     // Copy the output the the resultPolynomial input
    delete[] output, temp1, temp2;
}

void NTRUencrypt::fxDivX(int *p, int *resultPolynomial) {
    int *output = new int [size];

    memcpy(output, p, size * 2);

    if(polynomialDegree(output) == (size - 1 )) {
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

void NTRUencrypt::fxMulX(int *p, int *resultPolynomial) {
    int *output = new int [size];

    for(int i = size - 2; i > 0; i--)
        output[i] = p[i - 1];

    output[0] = p[size - 2];
    output[size - 1] = 0;

    memcpy(resultPolynomial, output, size * 2);
    delete[] output;
}

void NTRUencrypt::scalarMultiplication(int *p, int s, int *resultPolynomial) {
    int *output = new int [size];

    for(int i = 0; i < size; i++)
        output[i] = s * p[i];

    memcpy(resultPolynomial, output, size * 2);
    delete[] output;
}

void NTRUencrypt::inversePolynomial(int *p, int mod, char modPower, int *resultPolynomial) {
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
            fxDivX(f, f);
            fxMulX(c, c);
            k = k + 1;
        }

        if(polynomialDegree(f) == 0) {
            scalarMultiplication(output, modularInverse(f[0], mod), output);
            modulusReduction(output, mod, output);

            for(int j = 0; j < abs(size - k - 1); i++)
                fxDivX(output, output);

            //int q = mod;
            for(int j = mod; j < pow((double) mod, (double) modPower); j = j * j) {
                polynomialMultiplication(p, output, temp);
                scalarMultiplication(temp, -1, temp);
                temp[0] = temp[0] + 2;
                polynomialMultiplication(output, temp, output);

                modulusReduction(output, (int) pow((double) mod, (double) modPower), output);
            }

            memcpy(resultPolynomial, output, size * 2);
            delete[] output;
            delete[] c;
            delete[] f;
            delete[] g;
            delete[] temp;

            return;
        }

        if(polynomialDegree(f) < polynomialDegree(g)) {
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
void NTRUencrypt::fPolynomialGenerator(int df, int *resultPolynomial) {
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

void NTRUencrypt::gPolynomialGenerator(int dg, int *resultPolynomial) {
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

void NTRUencrypt::publicKeyGenerator(int *fPolynomial, int *gPolynomial, int *resultPolynomial) {
    int *output = new int [size];
    
    inversePolynomial(fPolynomial, modQ, qDeg, output);
    scalarMultiplication(output, modP, output);
    polynomialMultiplication(output, gPolynomial, output);

    if(qDeg < 1)
        errorLog = "Wrong input of exponent of modulus q: default value of 1 was used";
    if(qDeg >= 1)
        modulusReduction(output, (int) pow((double) modQ, (double) qDeg), output);
    
    memcpy(resultPolynomial, output, size * 2);
    delete[] output;
}

// Encryption + Decryption Base Functions
void NTRUencrypt::encryption(int *mPolynomial, int *hPolynomial, int *resultPolynomial) {
    int *output = new int [size];
    int *rPolynomial = new int [size];
    gPolynomialGenerator(dg, rPolynomial);  // Generate the r polynomial

    for(int i = 0; i < size; i++) {
        mPolynomial[i] = mPolynomial[i] % modP;
        if(mPolynomial[i] <= (modP / -2))
            mPolynomial[i] = mPolynomial[i] + modP;
        if(mPolynomial[i] > (modP / 2))
            mPolynomial[i] = mPolynomial[i] - modP;
    }

    polynomialMultiplication(rPolynomial, hPolynomial, output);
    polynomialSum(output, mPolynomial, output);
    modulusReduction(output, (int) pow ((double) modQ, (double) qDeg), output);

    memcpy(resultPolynomial, output, size * 2);
    delete[] output;
    delete[] rPolynomial;
}

void NTRUencrypt::decryption (int *cipherPolynomial, int *fPolynomial, int *fpPolynomial, int *resultPolynomial) {
    int *output = new int [size];
    int *temp = new int [size];
    int qPower = (int) pow ((double) modQ, (double) qDeg);

    polynomialMultiplication(cipherPolynomial, fPolynomial, temp);
    for(int i = 0; i < size; i++) {
        temp[i] = temp[i] % qPower;
        if(temp[i] <= (qPower / -2))
            temp[i] = temp[i] + qPower;
        if(temp[i] > (qPower / 2))
            temp[i] = temp[i] - qPower;

        output[i] = temp[i] % modP;
    }

    polynomialMultiplication(output, fpPolynomial, output);
    for(int i = 0; i < size; i++) {
        temp[i] = temp[i] % modP;
        if(temp[i] <= (modP / -2))
            temp[i] = temp[i] + modP;
        if(temp[i] > (modP / 2))
            temp[i] = temp[i] - modP;
    }

    memcpy(resultPolynomial, output, size * 2);
    delete[] output;
    delete[] temp;
}


// Conversion Functions
void NTRUencrypt::charToArray(char c, int *array) {
    unsigned int x = 1;
    char16_t y = c;

    for(int i = 0; i < 16; i++) {
        array[i] = (x & y) >> i;
        x = x << 1;
    }
}

char NTRUencrypt::arrayToChar(int *array) {
    unsigned int x = 1;
    char16_t y = 0;

    for(int i = 1; i < 16; i++) {
        array[i] = array[i] << i;
        y = y | (array[i] & x);
        x = x << 1;
    }

    return (char)(y);
}

void NTRUencrypt::stringToArray(std::string message, int *array) {
    int temp[16];

    for(int i = 0; i < message.length(); i++) {
        charToArray(message[i], temp);
        for(int k = 0; k < 16; k++)
            array[k + i * 16] = temp[k];
    }
}

std::string NTRUencrypt::arrayToString(int *array, int size) {
    std::string output;
    int arraySize = size / 16;


    return output;
}

void NTRUencrypt::decimalToHex(int *decimal, std::string *hex) {
    std::stringstream s;
    s << std::hex << *decimal;
    s >> *hex;
}

void NTRUencrypt::hexToDecimal(std::string *hex, int *decimal) {
    std::stringstream s;
    s << *hex;
    s >> std::hex >> *decimal;
}

// Public Functions Below
NTRUencrypt::NTRUencrypt(int strength) {
    switch(strength) {
    case 1: N = 167, size = 167, modP = 2, modQ = 127, df = 45, dg = 35, dr = 18; break;
    case 2: N = 167, size = 167, modP = 3, modQ = 128, df = 61, dg = 20, dr = 18; break;
    case 3: N = 251, size = 251, modP = 2, modQ = 127, df = 35, dg = 35, dr = 22; break;
    case 4: N = 251, size = 251, modP = 3, modQ = 128, df = 50, dg = 24, dr = 16; break;
    case 5: N = 503, size = 503, modP = 2, modQ = 253, df = 155, dg = 100, dr = 65; break;
    case 6: N = 503, size = 503, modP = 3, modQ = 256, df = 21, dg = 72, dr = 55; break;
    case 7: N = 252, size = 252, modP = 2, modQ = 127, df = 35, dg = 35, dr = 22; break;
    default:
        errorLog = errorLog + "Invalid Constructor Parameters, setting to NTRU251:3";
        N = 251, size = 251, modP = 3, modQ = 128, df = 50, dg = 24, dr = 16;
    }
}

std::string NTRUencrypt::generatePrivateKey(int seed) {
    // Create the arrays and generate the polynomials
    int *fPolynomial = new int [size];
    int *gPolynomial = new int [size];
    
    srand(seed);            // Wierd workaround

    fPolynomialGenerator(df, fPolynomial);
    gPolynomialGenerator(dg, gPolynomial);

    // Cycle through every index in f and g polynomials, pushing data onto the end of the string
    std::string output;
    for(int i = 0; i < size; i++)
        output = output + "." + std::to_string(fPolynomial[i]);
    delete[] fPolynomial;
    for(int i = 0; i < size; i++)
        output = output + "." + std::to_string(gPolynomial[i]);
    delete[] gPolynomial;

    output.erase(0, 1);     //  Remove the '.' at the start of the key
    return output;
}

std::string NTRUencrypt::generatePublicKey(std::string privateKey) {
    privateKey = "." + privateKey;  // Add '.' to the start of the private key (to aid with iteration)

    std::vector<int> indexPosition;
    for(int i = 0; i < privateKey.size(); i++) {
        if(privateKey[i] == '.') {
            indexPosition.push_back(i);
        }
    }

    // fPolynomial
    int *fPolynomial = new int [size];
    for(int i = 0; i < size; i++) {
        fPolynomial[i] = stoi(privateKey.substr(indexPosition[i] + 1, indexPosition[i + 1] - indexPosition[i] - 1));
    }

    // gPolynomial
    int *gPolynomial = new int [size];
    for(int i = size + 1; i < (size * 2); i++) {
        gPolynomial[i] = stoi(privateKey.substr(indexPosition[i] + 1, indexPosition[i + 1] - indexPosition[i] - 1));
    }

    int *result = new int [size];
    publicKeyGenerator(fPolynomial, gPolynomial, result);

    // Convert result into a string:
    std::string output;
    for(int i = 0; i < size; i++)
        output = output + "." + std::to_string(result[i]);

    output.erase(0, 1);     // Remove the '.' at the start of the key

    fPolynomial = NULL;
    delete[] fPolynomial;
    delete[] gPolynomial;
    delete[] result;
    return output;
}

std::string NTRUencrypt::encrypt(std::string receiverKey, std::string data) {
    // Receiver Polynomial Int Array Creation
    std::vector<int> indexPosition;
    receiverKey = '.' + receiverKey + '.';
    for(int i = 0; i < receiverKey.size(); i++) {
        if(receiverKey[i] == '.') {
            indexPosition.push_back(i);
        }
    }
    int *receiverPolynomial = new int [size];
    for(int i = 0; i < size; i++) {
        receiverPolynomial[i] = stoi(receiverKey.substr(indexPosition[i] + 1, indexPosition[i + 1] - indexPosition[i] - 1));
    }

    // Get the data and encrypt, then copy to output string
    std::string output;
    if(data.length() <= (size - 1) / 16) {
        int *cipher = new int [size];
        int *d = new int [size];

        stringToArray(data, d);
        for(int i = data.length() * 16; i < size; i++)
            d[i] = 0;
        
        encryption(d, receiverPolynomial, cipher);
        memcpy(&output, cipher, size * 2);
        output = std::to_string(size) + '.' + output;

        delete[] d;
        delete[] cipher;
        return output;
    } else {
        int N = 16 * data.length() / (size - 1);    // Dynamic Size

        int *cipher = new int [N * size];
        int *d = new int [size];
        std::string temp;

        for(int i = 0; i <= N; i++) {
            temp = data.substr(i * (size - 1) / 16, (size - 1) / 16);
            stringToArray(temp, d);
            for(int j = data.length() * 16; j < size; j++)
                d[j] = 0;
            
            encryption(d, receiverPolynomial, cipher);

            for(int j = 0; j < size; j++)
                cipher[j + i * size] = d[j];    // Try swapping for d[i] if it doesnt work :)

            output = std::to_string(size) + '.' + output;

            delete[] d;
            delete[] cipher;
            return output;
        }
    }
}

std::string NTRUencrypt::decrypt(std::string privateKey, std::string data) {
    /*std::vector<int> indexPosition;
    for(int i = 0; i < data.size(); i++) {
        if(data[i] == '.') {
            indexPosition.push_back(i);
        }
    }
    int *dataPolynomial = new int [indexPosition.size() - 1];
    for(int i = 0; i < indexPosition.size(); i++) {
        dataPolynomial[i] = stoi(data.substr(indexPosition[i] + 1, indexPosition[i + 1] - indexPosition[i] - 1));
    }

    int cipherSize = indexPosition.size();

    // Receiver Polynomial Int Array Creation
    indexPosition.clear();  // Clear the vector for use below*/



    // Get the total index of the data polynomial from the string (stored in a header before the first '.')
    //    + Remove the header from the input data
    std::string index;
    std::string header = data;
    for(int i = 0; i < data.size(); i++) {
        if(data[i] == '.') {    // Once the first '.' is reached, the index can be read;
            break;
        } else {
            index = index + data[i];
            header.erase(i, 1);
        }
    }
    int dataSize = stoi(index);
    header.erase(0, 1);   // Remove the '.'

    // Create the cipher array
    int *cipher = new int [dataSize];
    memcpy(&cipher, &header, sizeof(cipher));


    // Get the f Polynomial from the private key
    // Get the number of '.'s and their positions
    std::vector<int> breakPositions;
    for(int i = 0; i < privateKey.size(); i++)
        if(privateKey[i] == '.')
            breakPositions.push_back(i);

    std::string fPolynomialString = data.substr(0, breakPositions[df]);     // fPolynomialString should look like -> 124BS.12589VBS.096CD.

    // Create an int array from the fPolynomial string
    int count = 0, prevCount = 0, hex = 0;
    std::vector<int> privateVect;
    std::string temp;
    for(int i = 0; i < privateKey.size(); i++) {
        if(privateKey[i] == '.') {
            for(int i = prevCount; i < count; i++)
                temp = temp + privateKey[i];
            
            hexToDecimal(&temp, &hex);
            privateVect.push_back(hex);

            count++;
            prevCount = count;
            temp = "";
        } else {
            count++;
        }
    }

    int *fPolynomial = new int [df];
    std::copy(privateVect.begin(), privateVect.end(), fPolynomial);
    
    // Generating fpPolynomial using the fPolynomial
    int *fpPolynomial = new int [df];
    inversePolynomial(fPolynomial, modP, 1, fpPolynomial);

    // Now that we have all correct variable types, we can input them into the given function and return the string converted output array
    std::string message;
    int *output = new int [dataSize];
    decryption(cipher, fPolynomial, fpPolynomial, output);
    message = arrayToChar(output);

    delete[] cipher;
    delete[] fPolynomial;
    delete[] fpPolynomial;
    delete[] output;
    return message;
}