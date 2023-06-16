#include "NTRUencrypt.h"


// Polynomial Mathematic Functions
int NTRUencrypt::polynomialDegree(int *p) {
    int i = size - 1;
    while(i > -1) {
        if(i > -1) {
            if(p[i] != 0)
                break;
            i--;
        }
    }
    return i;
}

int NTRUencrypt::modularInverse(int p, int m) {
    if(abs(p) >= m)
        p = p % m;
    if(p < m)
        p = p + m;

    int q, r, r1, r2, z, z1, z2;
    r1 = m;
    r2 = p;
    z1 = 0;
    z2 = 1;

    while(r2 > 0) {
        q = r1 / r2;
		r = r1 - q * r2;
		r1 = r2;
		r2 = r;
		z = z1 - q * z2;
		z1 = z2;
		z2 = z;
    }

    if(z1 < 0) {
        z1 = m + z1;
        return z1;
    } else {
        return z1;
    }
}

void NTRUencrypt::modulusReduction(int *p, int mod, int *reducedPolynomial) {
    for(short int i = 0; i < size; i++) {
        reducedPolynomial[i] = p[i] % mod;
        if(reducedPolynomial[i] < 0)
            reducedPolynomial[i] = reducedPolynomial[i] + mod;
    }
}

void NTRUencrypt::polynomialSum(int *p1, int *p2, int *resultPolynomial) {
    for(int i = 0; i < size; i++)
        resultPolynomial[i] = p1[i] + p2[i];
}

void NTRUencrypt::polynomialMultiplication(int *p1, int *p2, int *resultPolynomial) {
    int *resPolynomial = new int [size];
    int *tempArray = new int [size];
    int *tempArray1 = new int [size];

    for(int i = 0; i < size; i++) {
        resPolynomial[i] = p1[0] * p2[i];
    }

    memcpy(tempArray, p2, size * sizeof(int));

    for(int i = 1; i < size - 1; i++) {
        fxMulX(tempArray, tempArray);

        for(int j = 0; j < size; j++) {
            scalarMultiplication(tempArray, p1[i], tempArray1);
            resPolynomial[j] = resPolynomial[j] + tempArray1[j];
        }
    }

    memcpy(resultPolynomial, resPolynomial, size * sizeof(int));

    delete[] resPolynomial;
    delete [] tempArray;
	delete [] tempArray1;
}

void NTRUencrypt::fxDivX(int *p, int *resultPolynomial) {
    int *output = new int [size];

    memcpy(output, p, size * sizeof(int));

    if(polynomialDegree(output) == (size - 1 )) {
        for(int i = 1; i < size; i++)
            output[i - 1] = p[i];
        
        output[size - 1] = p[0];
    } else {
        for(int i = 1; i < size - 1; i++)
            output[i - 1] = p[i];
        
        output[size - 2] = p[0];
    }

    memcpy(resultPolynomial, output, size * sizeof(int));
    delete[] output;
}

void NTRUencrypt::fxMulX(int *p, int *resultPolynomial) {
    int *output = new int [size];

    for(int i = size - 2; i > 0; i--)
        output[i] = p[i - 1];

    output[0] = p[size - 2];
    output[size - 1] = 0;

    memcpy(resultPolynomial, output, size * sizeof(int));
    delete[] output;
}

void NTRUencrypt::scalarMultiplication(int *p, int s, int *resultPolynomial) {
    int *output = new int [size];

    for(int i = 0; i < size; i++)
        output[i] = s * p[i];

    memcpy(resultPolynomial, output, size * sizeof(int));
    delete[] output;
}

void NTRUencrypt::inversePolynomial(int *p, int mod, char modPower, int *resultPolynomial) {
    int k = 0;
    int *invPol = new int [size];
    int *c = new int [size];
    int *f = new int [size];
    int *g = new int [size];
    int *temp = new int [size];

    memset(invPol, 0, size * sizeof(int));
    memset(c, 0, size * sizeof(int));
    memset(g, 0, size * sizeof(int));
    memcpy(f, p, size * sizeof(int));

    invPol[0] = 1;
    g[0] = -1;
    g[size - 1] = 1;

    k = 0;

    int count = 0;
    while(count < size * size) {
        while(f[0] == 0) {
            fxDivX(f, f);
            fxMulX(c, c);
            k = k + 1;
        }

        if(polynomialDegree(f) == 0) {
            scalarMultiplication(invPol, modularInverse(f[0], mod), invPol);
            modulusReduction(invPol, mod, invPol);

            for(int i = 0; i < abs(size - k - 1); i++) {
                fxDivX(invPol, invPol);
            }

            int q = mod;

            while(q < pow((double) mod, (double) modPower)) {
                q = q * q;
                polynomialMultiplication(p, invPol, temp);
                scalarMultiplication(temp, -1, temp);
                temp[0] = temp[0] + 2;
                polynomialMultiplication(invPol, temp, invPol);

                modulusReduction(invPol, (int) pow((double) mod, (double) modPower), invPol);
            }

            memcpy(resultPolynomial, invPol, size * sizeof(int));

            delete [] invPol;
			delete [] c;
			delete [] f;
			delete [] g;
			delete [] temp;

			return;
        }
        
        if (polynomialDegree (f) < polynomialDegree (g)) {
			int *f1 = f;
			f = g;
			g = f1;
			int *b1 = invPol;
			invPol = c;
			c = b1;
		}

        int u;
		u = f[0] * modularInverse (g[0], mod);
		u = u % mod;

		if (u < 0)
			u = mod + u;
        
        for(int i = 0; i < size; i++) {
            f[i] = (f[i] - u * g[i]);
			f[i] = f[i] % mod;
			if(f[i] < 0)
				f[i] = mod + f[i];

			invPol[i] = (invPol[i] - u * c[i]);
			invPol[i] = invPol[i] % mod;
			if(invPol[i] < 0)
				invPol[i] = mod + invPol[i];
        }
        count++;
    }

    errorLog = "Polynomial is irreversible";

    delete [] invPol;
	delete [] c;
	delete [] f;
	delete [] g;
	delete [] temp;
	return;
}


// Generator Functions
void NTRUencrypt::fPolynomialGenerator(int df, int *resultPolynomial) {
    int *output = new int [size];
    int number;
    int i = 0;

    memset(output, 0, size * sizeof(int));

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

    memcpy(resultPolynomial, output, size * sizeof(int));
    delete[] output;
}

void NTRUencrypt::gPolynomialGenerator(int dg, int *resultPolynomial) {
    int *output = new int [size];
    int number;
    int i = 0;

    memset(output, 0, size * sizeof(int));

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

    memcpy(resultPolynomial, output, size * sizeof(int));
    delete[] output;
}

void NTRUencrypt::publicKeyGenerator(int *fPolynomial, int *gPolynomial, int *resultPolynomial) {
    int *output = new int [size];
    
    inversePolynomial(fPolynomial, modQ, qDeg, output);
    scalarMultiplication(output, modP, output);
    polynomialMultiplication(output, gPolynomial, output);

    if(qDeg < 1)
        errorLog = "Wrong input of exponent of modulus q";
    if(qDeg >= 1)
        modulusReduction(output, (int) pow((double) modQ, (double) qDeg), output);
    
    memcpy(resultPolynomial, output, size * sizeof(int));
    delete[] output;
}

// Encryption + Decryption Base Functions
void NTRUencrypt::encryption(int *mPolynomial, int *hPolynomial, int *resultPolynomial) {
    int *output = new int [size];
    int *rPolynomial = new int [size];
    gPolynomialGenerator(dr, rPolynomial);  // Generate the r polynomial

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

    memcpy(resultPolynomial, output, size * sizeof(int));
    delete[] output;
    delete[] rPolynomial;
}

void NTRUencrypt::decryption (int *cipherPolynomial, int *fPolynomial, int *fpPolynomial, int *resultPolynomial) {
    int *temp = new int [size];
    int *secretPolynomial = new int [size];
    int qPower = (int) pow ((double) modQ, (double) qDeg);

    polynomialMultiplication(cipherPolynomial, fPolynomial, temp);
    for(int k = 0; k < size; k++) {
        temp[k] = temp[k] % qPower;
        if (temp[k] <= (qPower / -2))
			temp[k] = temp[k] + qPower;
		if (temp[k] > (qPower / 2))
			temp[k] = temp[k] - qPower;
    }

    for (int k = 0; k < size; k++)
		secretPolynomial[k] = temp[k] % modP;

    polynomialMultiplication(secretPolynomial, fpPolynomial, secretPolynomial);
    for(int k = 0; k < size; k++) {
        secretPolynomial[k] = secretPolynomial [k] % modP;
		if (secretPolynomial[k] <= (modP / -2))
			secretPolynomial[k] = secretPolynomial[k] + modP;
		if (secretPolynomial[k] > (modP / 2))
			secretPolynomial[k] = secretPolynomial[k] - modP;
    }

    memcpy(resultPolynomial, secretPolynomial, size * sizeof(int));

    delete[] temp;
    delete[] secretPolynomial;
}


// Conversion Functions
void NTRUencrypt::charToArray(char c, int *array) {
    unsigned int i = 1;
	char16_t b = c;
	
	for (int k = 0; k < 16; k++) {
		array[k] = (i & b) >> k;
		i = i << 1;
	}
}

char NTRUencrypt::arrayToChar(int *array) {
    unsigned int i = 1;
	char a = 0;
	char16_t b = 0;
	
	for (int k = 0; k < 16; k++) {
		array[k] = array[k] << k;
		b = b | (array[k] & i);
		i = i << 1;		
	}
	a = (char)(b);

	return a;
}

void NTRUencrypt::stringToArray(std::string message, int *array) {
    int temp[16];

    for(int i = 0; i < message.length(); i++) {
        charToArray(message[i], temp);
        for(int j = 0; j < 16; j++)
            array[j + i * 16] = temp[j];
    }
}

std::string NTRUencrypt::arrayToString(int *array, int size) {
    std::string output;
    int arraySize = size / 16;
    char *s = new char[arraySize + 1];
    int a[16];

    for(int i = 0; i < arraySize; i++) {
        for(int j = 0; j < 16; j++)
            a[j] = array[j + i * 16];
        
        s[i] = arrayToChar(a);
    }
    s[arraySize] = '\0';
    output = std::string(s);

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
        gPolynomial[i - size] = stoi(privateKey.substr(indexPosition[i] + 1, indexPosition[i + 1] - indexPosition[i] - 1));
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

        output = std::to_string(size);
        for(int i = 0; i < size; i++)
            output = output + '.' + std::to_string(cipher[i]);

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

            output = std::to_string(N * size);
            for(int i = 0; i < (N * size); i++)
                output = output + '.' + std::to_string(cipher[i]);

            delete[] d;
            delete[] cipher;
            return output;
        }
    }
}

std::string NTRUencrypt::decrypt(std::string privateKey, std::string data) {
    privateKey = '.' + privateKey + '.';

    // Data
    int dataSize;
    for(int i = 0; i < data.size(); i++) {
        if(data[i] == '.') {
            dataSize = stoi(data.substr(0, i - 1));
            data.erase(0, i - 1);
            break;
        }
    }
    int *cipher = new int [dataSize];
    std::vector<int> indexPosition;
    for(int i = 0; i < data.size(); i++) {
        if(data[i] == '.') {
            indexPosition.push_back(i);
        }
    }
    for(int i = 0; i < dataSize; i++) {
        cipher[i] = stoi(data.substr(indexPosition[i] + 1, indexPosition[i + 1] - indexPosition[i] - 1));
    }

    // fPolynomial
    indexPosition.clear();
    for(int i = 0; i < privateKey.size(); i++) {
        if(privateKey[i] == '.') {
            indexPosition.push_back(i);
        }
    }
    int *fPolynomial = new int [size];
    for(int i = 0; i < size; i++) {
        fPolynomial[i] = stoi(privateKey.substr(indexPosition[i] + 1, indexPosition[i + 1] - indexPosition[i] - 1));
    }

    // fpPolynomial
    int *fpPolynomial = new int [size];
    inversePolynomial(fPolynomial, modP, modQ, fpPolynomial);

    // Decryption
    int *result = new int [dataSize];
    decryption(cipher, fPolynomial, fpPolynomial, result);
    delete[] fpPolynomial;
    delete[] fPolynomial;
    delete[] cipher;
    
    // Output
    std::string output = arrayToString(result, dataSize);
    delete[] result;
    return output;
}
