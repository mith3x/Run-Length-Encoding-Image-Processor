/* 
This program performs a run length encoding on an array of characters.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARR 5000

/*  Function: take_photo()
    Description: Simulates taking a photo as a black-and-white image represented by
                 an array of characters '1' and '0'. The photo is stored in the out[] array.

    Output: out[]   - an array of characters to store the photo data, as a string of 1 and 0 characters
    Output: rows    - an address to an integer to store the number of rows in the photo
    Output: cols    - an address to an integer to store the number of columns in the photo

    Returns: the total number of characters in the photo data OR 0 if no photo was taken
    
*/

int take_photo(unsigned char out[], int* rows, int* cols); // initialized in the camera.o file

unsigned char get_bit(unsigned char byte, int bit); // provided to us
unsigned char set_bit(unsigned char byte, int bit); // provided to us
unsigned char clear_bit(unsigned char byte, int bit); // provided to us

void print_raw(unsigned char raw_string[], int rows, int cols);
int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]);
void print_packed(const unsigned char packed[], int rows, int cols);
int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]);
void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols);

int main() {
    unsigned char rawString[MAX_ARR];
    unsigned char packString[MAX_ARR];
    unsigned char encodeString[MAX_ARR];
    int numRows;
    int numColumns;
    int size;

    // is the picture empty (0) or not ?
    size = take_photo(rawString,&numRows, &numColumns);

    while (size !=0){
        int rawPhotoSize = numRows*numColumns;
        printf("%s %d\n", "Raw Photo: ", rawPhotoSize);
        print_raw(rawString,numRows,numColumns);
        printf("Packing Bits\n");
        int x = pack_bits(rawString,rawPhotoSize,packString);
        printf("%s %d\n", "Packed Photo: ", x);
        print_packed(rawString,numRows,numColumns);
        printf("Encoding Bits\n");
        int y = encode_bits(packString, rawPhotoSize, encodeString);
        printf("%s %d\n", "Encoded Photo: ", y);
        print_encoded(packString, rawPhotoSize, numRows, numColumns);
        size = take_photo(rawString, &numRows, &numColumns);
    }
}

/*
 * Function: print_raw(unsigned char raw_string[], int rows, int cols)
 * Purpose: Takes in the string of characters/number of rows and columns which are returned by take_photo
 * Input: string of characters returned by take_photo, as well as the number of rows and columns
 * Output: Print the 1s as asterisks(*) and the 0s as periods(.)
 */

void print_raw(unsigned char raw_string[], int rows, int cols) {
    int count = 0;
    for(int i = 0; i<rows ;i++){
        for(int j = 0; j < cols; j++){
            char drawing;
            if(raw_string[count] == '1') {
                drawing = '*';
            }else {
                drawing = '.';
            }
            printf("%c",drawing);
            count++;
        }
        printf("\n");
    }
}

/*
 * Function: pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[])
 * Purpose: Takes in the unpacked string/number of rows and columns which are returned by take_photo
 * Input: unpacked characters returned by take_photo, as well as the number of rows and columns
 * Output: A new array to store the new, packed bytes information
 */

int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[]) {
    int numBits = 0;
    int numBytes = 0;
    unsigned char newByte[8];

    // Iterate Over Every 8 bits (1 byte)
    int numIterations = num_chars / 8;
    for (int j = 0; j < numIterations; j++) {

        // Get every 8 Bits
        for (int i = 0; i < 8; ++i) {
            newByte[i] = unpacked_string[numBits];
            // check If 1 or 0
            if (newByte[i] == '1') {
                newByte[i] = set_bit( newByte[i], i);
            } else if (newByte[i] == '0') {
                newByte[i] = clear_bit(newByte[i], i);
            }
            // Add To Packed_Result
            packed_result[numBits] = newByte[i];
            numBits++;
        }
        // Clear Char Array
        for (int i = 0; i < 8; i++) {
            newByte[i] = '\0';
        }
        numBytes++;
    }
    return numBytes;
}

/*
 * Function: print_packed(unsigned char packed[], int rows, int cols)
 * Purpose: This function will take the array of packed bytes and print the 1s and 0s as symbols to draw the image
 * Input: Array of packed bytes
 * Output: Print the 1s as asterisks(*) and the 0s as periods(.)
 */

void print_packed(const unsigned char packed[], int rows, int cols){
    int bitIndex = 0;
    for(int i = 0; i<rows ;i++){
        for(int j = 0; j < cols; j++){
            unsigned char currentByte = packed[bitIndex];
            unsigned char drawing;
            if(currentByte == '1') {
                drawing = '*';
            }else {
                drawing = '.';
            }
            printf("%c",drawing);
            bitIndex++;
        }
        printf("\n");
    }
}

/*
 * Function: encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[])
 * Purpose: Take the packed bytes and number of bytes in packed array as inputs and accept
 *          an array of unsigned characters to output the new encoded bytes
 * Input: Packed bytes array and number of bytes in the packed array
 * Output: New encoded bytes
 */

int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[]){
    int encodeCounter = 0;
    int packedCounter = 0;
    int prevValue = 0;
    int currentValue = 0;
    int binaryCounter = 0;
    int count = 0;

    if(packed[0] == 0){
        encoded_result[encodeCounter] = binaryCounter;
        encodeCounter++;
        packedCounter++;
        prevValue = 0;
    }
    for (int i = packedCounter; i < packed_size; i++){
        currentValue = packed[i];
        if ((i % 8) == 0){
            count ++;
        }
        if(currentValue == prevValue){
            binaryCounter++;
        } else {
            encoded_result[encodeCounter] = binaryCounter;
            encodeCounter++;
            binaryCounter = 0;
        }
        prevValue = currentValue;
    }
    return count;
}

/*
 * Function: print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols)
 * Purpose: This function will take the array of encoded bytes and print the 1s and 0s as symbols to draw the image
 * Input: Array of encoded bytes
 * Output: Print the 1s as asterisks(*) and the 0s as periods(.)
 */

void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols){
    for(int i = 0; i<rows ;i++){
        for(int j = 0; j < cols; j++){
            unsigned char currentByte = encoded[encoded_size];
            unsigned char drawing;
            if((currentByte / 2) == 0) {
                drawing = '*';
            }else {
                drawing = '.';
            }
            printf("%c",drawing);
            encoded_size++;
        }
        printf("\n");
    }
}

/*
 * Function: get_bit(unsigned char byte, into bit)
 * Purpose: get the value of a bit at a specific position
 * Input: character and position of where the bit will be returned
 * Output: the new value of the bit at the position
 */

unsigned char get_bit(unsigned char byte, int bit) {
    return (byte >> bit) & 1;
}

/*
 * Function: set_bit(unsigned char byte, int bit)
 * Purpose: setting the bit to 1
 * Input: character and int bit that is to be changed to 1
 * Output: new value at the byte character and int bit set to 1
 */

unsigned char set_bit(unsigned char byte, int bit) {
    return byte | (1 << bit);
}

/*
 * Function: clear_bit(unsigned char byte, int bit)
 * Purpose: setting the bit to 0
 * Input: character and int bit that is to be changed to 0
 * Output: new value at the byte character and int bit set to 0
 */

unsigned char clear_bit(unsigned char byte, int bit) {
    return byte & ~(1 << bit);
}