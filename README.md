# Affine Bigram cipher 

### Target platform: Ubuntu 16.04

Language: C++11 compiled under GCC 5.4.0 using CMake 3.5.2

## Installing

In bash:

```
    cmake ./CMakeLists.txt
    make
```

The executable will be placed in "build" folder.

## Brief description

Works only with Russian characters (lowercase without spaces and punctuation marks).

Letter 'ё' was replaced with letter 'е'.

Letter 'ъ' was replaced with letter 'ь'.

### Features: 

1. enciphering, 2. deciphering, 3. cryptanalysis.

### 1. Enciphering

Open text x1, x2, x3, ... is broken up into non-intersecting bigrams: (x1, x2),
(x3, x4), ... 

Where m is the number of letters in the alphabet. 

Let's number the letters of the alphabet by the numbers from 0 to m-1; 
then each bigram (x2i-1, x2i) can be transformed to the number Xi = (x2i-1)*m + x2i.

For example, the number (в,б) = (2, 1) with m = 31 corresponds to the number X = 2*31 + 1 = 63.

Biographies are encrypted independently of this rule. 

Let Xi = (x2i-1, x2i) be a bigram of plain text, 
and Yi = (y2i-1, y2i) is the corresponding encoded text bigram. 

Then Yi = (a*Xi + b) mod m^2,
where 0 < a <= m^2 (a is number mutually simple with m),  
0 <= b <= m^2 (b is random number in the indicated boundaries).

Thus, the key of the Affine Bigram cipher consists of a pair of numbers a and b.

### 2. Deciphering

When decoding, the inverse transformation is performed:
Xi = (a^-1)*(Yi - b) mod m^2

Where (a^-1) is modular multiplicative inverse.

### 3. Cryptanalysis
 
If we know that bigram x1 after encryption become bigram y1 
and bigram x2 become bigram y2:

We can get key(a,b) from system of equations:

y2 = a*x2 + b(mod m^2);

y1 = a*x1 + b(mod m^2);

As x1 and x2 we take pair from 5 most popular bigrams in russian language (ст, но, то, ен, ни).
As y1 and y2 we take pair from 5 most popular bigrams in ciphertext.

We check if we get right pairs (x1,x2; y1,y2) by calculating index of coincidence for plain text.

## How to work with the program

Put enciphered text in resources/encipheredText.txt

Run executable.

The decrypted text will be placed in resources/output.txt

## Author

* **Taras Koval** - *All work* - [TarasKoval](https://github.com/TarasKoval)

## License

No license - do what you want
