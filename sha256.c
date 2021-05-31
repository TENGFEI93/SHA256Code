#include <stdio.h>
#include <math.h>
#include <string.h>
#include <wctype.h>


int main()
{
    int i, j, l, q, length, length1, M, k, renum, uu, rr, r, n, length_block, t, in, inj, nj, tt;
    unsigned int midtemp = 0;
    unsigned int a = 0;
    unsigned int b = 0;
    unsigned int c = 0;
    unsigned int d = 0;
    unsigned int e = 0;
    unsigned int f = 0;
    unsigned int g = 0;
    unsigned int h = 0;
    unsigned int T1 = 0;
    unsigned int T2 = 0;
    char init_string[100000] = "\0";
    char temp1[100000] = "\0";
    char space[10] = {'0','0','1','0','0','0','0','0'};
    char temp0[10] = "\0";
    char padding[10] = "\0";
    char padding1[100] = "\0";
    char p[10] = "\0";
    char zeros[600] = "\0";
    char sha256[600] = "\0";
    char one[2] = {'1'};
    char appending[10000] = "\0";
    char appending0[10000] = "\0";
    char appending1[10000] = "\0";
    char zeropadding[10] = "\0";
    char midTemp[40] = "\0";
    unsigned int temp32[100000] = {0};
    const unsigned int K[] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };
    unsigned int H[8] = {0};
    unsigned int Me[16] = {0};
    unsigned int W[64] = {0};

    unsigned int CH(unsigned int x, unsigned int y, unsigned int z);
    unsigned int MAJ(unsigned int x, unsigned int y, unsigned int z);
    unsigned int BSIG0(unsigned int x);
    unsigned int BSIG1(unsigned int x);
    unsigned int SSIG0(unsigned int x);
    unsigned int SSIG1(unsigned int x);
    unsigned int bintodec(char *array);
    char *dectohex(unsigned int n);


    printf("input string: \n");
    scanf("%[^\n]s", init_string);

    //将字符串转换为二进制
    for (i = 0; init_string[i] != '\0'; i++)
    {
        if (init_string[i] == ' ')
        {
            strncat(temp1, space, strlen(space));
        }else
        {
            itoa(init_string[i], temp0, 2);
            for (j = 0; j < (8-strlen(temp0)); j++)
            {
                padding[j] = '0';
            }
            strncpy(p, padding, strlen(padding));
            strncat(p, temp0, strlen(temp0));
            strncat(temp1, p, strlen(p));
            memset(p, '\0', sizeof(p));
            memset(temp0, '\0', sizeof(temp0));                       
            memset(padding, '\0', sizeof(padding));
        }
    }
    
    //将转换后二进制位数补为512的整数倍
    printf("%s\n", temp1);
    length = strlen(temp1);
    printf("%d\n", length);
    M = length%512;
    if (M < 448)
    {
        for (k = 0; k < (447-M); k++)
        {
            zeros[k] = '0';
        }
    }else if (M == 448)
    {
        for (l = 0; l < 511; l++)
        {
            zeros[l] = '0';
        }       
    }else
    {
        for (q = 0; q < (959-M); q++)
        {
            zeros[q] = '0';
        }
    }
    strncat(temp1, one, strlen(one));
    strncat(temp1, zeros, strlen(zeros));
    itoa(length, appending, 2);
    printf("%s\n", appending);
    renum = (strlen(appending))%8;
    if (renum == 0)
    {
        strncpy(appending0, appending, strlen(appending));
    }else
    {
        for (uu = 0; uu < (8 - renum); uu++)
        {
            zeropadding[uu] = '0';
        }
        strncat(appending0, zeropadding, strlen(zeropadding));
        strncat(appending0, appending, strlen(appending));
    }
    if(strlen(appending0)>=64)
    {
        for(rr = 0; rr < 64; rr++)
        {
            padding1[rr] = appending0[rr + length - 64];
        }
        strncpy(appending0, padding1, strlen(padding1));
    }else
    {
        for (r = 0; r < (64-strlen(appending0)); r++)
        {
            padding1[r] = '0';
        }
        strncat(appending1, padding1, strlen(padding1));
        strncat(appending1, appending0, strlen(appending0));
    }
    strncat(temp1, appending1, strlen(appending1));
    printf("%s\n", temp1);

    H[0] = 0x6a09e667;
    H[1] = 0xbb67ae85;
    H[2] = 0x3c6ef372;
    H[3] = 0xa54ff53a;
    H[4] = 0x510e527f;
    H[5] = 0x9b05688c;
    H[6] = 0x1f83d9ab;
    H[7] = 0x5be0cd19;

    length1 = strlen(temp1);
    for (in = 0; in < length1/32; in++)
    {
        for(inj = 0; inj < 32; inj++)
        {
            midTemp[inj] = temp1[in*32 + inj];
        }
        midtemp = bintodec(midTemp);
        printf("midtemp:%d\n", midtemp);
        temp32[in] = midtemp;
        memset(midTemp, '\0', sizeof(midTemp));
    }

    length_block = strlen(temp1)/512;
    for (n = 0; n <length_block; n++)
    {
        for (nj = 0; nj < 16; nj++)
        {
            Me[nj] = temp32[n*16 + nj];
        }
        for (t = 0; t < 64; t++)
        {
            if (t < 16)
            {
                W[t] = Me[t];
            }
            else
            {
                W[t] = SSIG1(W[t-2]) + W[t-7] + SSIG0(W[t-15]) + W[t-16];
            }
        }
        a = H[0];
        b = H[1];
        c = H[2];
        d = H[3];
        e = H[4];
        f = H[5];
        g = H[6];
        h = H[7];
        for (tt = 0; tt < 64; tt++)
        {
            T1 = h + BSIG1(e) + CH(e, f, g) + K[tt] + W[tt];
            T2 = BSIG0(a) + MAJ(a,b,c);
            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        }
        H[0] = a + H[0];
        H[1] = b + H[1];
        H[2] = c + H[2];
        H[3] = d + H[3];
        H[4] = e + H[4];
        H[5] = f + H[5];
        H[6] = g + H[6];
        H[7] = h + H[7];
    }
    strncat(sha256, dectohex(H[0]), 8);
    strncat(sha256, dectohex(H[1]), 8);
    strncat(sha256, dectohex(H[2]), 8);
    strncat(sha256, dectohex(H[3]), 8);
    strncat(sha256, dectohex(H[4]), 8);
    strncat(sha256, dectohex(H[5]), 8);
    strncat(sha256, dectohex(H[6]), 8);
    strncat(sha256, dectohex(H[7]), 8);
    printf("sha256 value\n%s\n", sha256);
    system("pause");
    return 0;
}

unsigned int CH(unsigned int x, unsigned int y, unsigned int z)
{
    unsigned int temp;

    temp = (x & y) ^ ((~x) & (z));
    return temp;
}

unsigned int MAJ(unsigned int x, unsigned int y, unsigned int z)
{
    unsigned int temp;

    temp = (x & y) ^ (x & z) ^ (y & z);
    return temp;
}

unsigned int BSIG0(unsigned int x)
{
    unsigned int temp;

    temp = ((x >> 2) | (x << (32 - 2))) ^ ((x >> 13) | (x << (32 - 13))) ^ ((x >> 22) | (x << (32 - 22)));
    return temp;
}

unsigned int BSIG1(unsigned int x)
{
    unsigned int temp;

    temp = ((x >> 6) | (x << (32 - 6))) ^ ((x >> 11) | (x << (32 - 11))) ^ ((x >> 25) | (x << (32 - 25)));
    return temp;
}

unsigned int SSIG0(unsigned int x)
{
    unsigned int temp;

    temp = ((x >> 7) | (x << (32 - 7))) ^ ((x >> 18) | (x << (32 - 18))) ^ (x >> 3);
    return temp;
}

unsigned int SSIG1(unsigned int x)
{
    unsigned int temp;

    temp = ((x >> 17) | (x << (32 - 17))) ^ ((x >> 19) | (x << (32 - 19))) ^ (x >> 10);
    return temp;
}

unsigned int bintodec(char *array)
{
    int kk;
    int LL;
    int TT;
    unsigned int num = 0;
    char tempv[2] = "\0"; 

    LL = strlen(array);
    for(kk = 0; kk < LL; kk++)
    {
        tempv[0] = array[kk];
        TT = strtol(tempv, NULL, 2);
        num += TT*pow(2, LL-kk-1);
        memset(tempv, '\0', sizeof(tempv));
    }
    return num;
}

char* dectohex(unsigned int n)
{
    static char hexstring[10];
    static char hexstring1[10];
    static char hexstring2[10];
    memset(hexstring, '\0', sizeof(hexstring));
    memset(hexstring1, '\0', sizeof(hexstring1));
    memset(hexstring2, '\0', sizeof(hexstring2));
    char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    char padding[10] = "\0";
    unsigned int temp, j, length;
    int i = 0;
    int k = 0;

    while(n > 0)
    {
        temp = n%16;
        hexstring[i] = hex[temp];
        n = n/16;
        i++;
    }
    length = strlen(hexstring);
    for(j = 0; j < length; j++)
    {
        hexstring1[j] = hexstring[length - j - 1];
    }
    for (k = 0; k < (8 - strlen(hexstring1)); k++)
    {
        padding[k] = '0';
    }
    strncpy(hexstring2, padding, strlen(padding));
    strncat(hexstring2, hexstring1, strlen(hexstring1));

    return hexstring2; 
}

