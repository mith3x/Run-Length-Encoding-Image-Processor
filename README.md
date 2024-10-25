### Overview
This project performs run-length encoding (RLE) on black-and-white images represented by arrays of 1s and 0s. The images are captured from a simulated camera and processed to compress data through packing and encoding techniques.

### Project Overview
The program simulates taking a black-and-white image as an array of characters ('1' for black pixels and '0' for white pixels). The image is processed in three stages:
1. **Raw Image Representation**: The image is represented as an array of characters, with '1' displayed as an asterisk (*) and '0' as a period (.).
2. **Packed Bits**: The array of 1s and 0s is packed into a more compact form, grouping each set of 8 bits (1 byte).
3. **Run-Length Encoding (RLE)**: The packed bits are further encoded to reduce repeated sequences.

### Features
- **Capture Image**: Simulates taking an image, represented as a string of binary characters.
- **Display Image**: The raw binary image can be displayed as * for 1s and . for 0s.
- **Packing**: Compresses the raw binary image by packing every 8 bits into a single byte.
- **Run-Length Encoding**: Encodes the packed image with run-length encoding to represent repeated bit sequences.

### Files
- **a2-posted.c**: The main program that handles the flow of capturing, packing, and encoding the image.
- **camera.o**: Simulates camera functionality. The function `take_photo()` is used to capture photo data.
- **Utility Functions**: Functions such as `get_bit()`, `set_bit()`, and `clear_bit()` are provided for bit manipulation.

### Functions
#### Core Functions
- `int take_photo(unsigned char out[], int* rows, int* cols)`:  
  Simulates capturing an image from a camera and stores the result in the `out[]` array. Returns the total number of characters in the photo or 0 if no image was captured.

- `void print_raw(unsigned char raw_string[], int rows, int cols)`:  
  Displays the raw binary image in human-readable form (* for 1 and . for 0).

- `int pack_bits(unsigned char unpacked_string[], int num_chars, unsigned char packed_result[])`:  
  Packs the raw image into a more compressed format by converting every 8 bits (1 byte) into packed bytes. Returns the total number of bytes packed.

- `void print_packed(const unsigned char packed[], int rows, int cols)`:  
  Displays the packed bits in human-readable form.

- `int encode_bits(unsigned char packed[], int packed_size, unsigned char encoded_result[])`:  
  Applies run-length encoding to the packed data to reduce redundancy. Returns the number of encoded bytes.

- `void print_encoded(unsigned char encoded[], int encoded_size, int rows, int cols)`:  
  Displays the encoded image in human-readable form.

#### Utility Functions
- `unsigned char get_bit(unsigned char byte, int bit)`:  
  Returns the value of the bit at the specified position in a byte.

- `unsigned char set_bit(unsigned char byte, int bit)`:  
  Sets the bit at the specified position to 1 in a byte.

- `unsigned char clear_bit(unsigned char byte, int bit)`:  
  Clears the bit at the specified position to 0 in a byte.

### Setup and Execution
#### Requirements
- Oracle VM VirtualBox with a Linux environment (e.g., Ubuntu).
- GNU Compiler Collection (GCC) installed on the virtual machine.

#### Steps to Run
1. **Set up the Virtual Machine**:  
   Make sure your Oracle VM is configured with Linux and that you have terminal access with GCC installed.
   
2. **Transfer Project Files**:  
   Place `a2-posted.c` and `camera.o` into a directory within the VM.

3. **Compile the Program**:  
   Open a terminal in the directory containing the project files and run:
     gcc -o run_length_encoding a2-posted.c camera.o
   

4. **Execute the Program**:  
   Run the program by executing the following command:
     ./run_length_encoding
  
### Notes
- This program assumes that `camera.o` provides a `take_photo()` function simulating a photo capture.
- The project uses run-length encoding (RLE) to reduce the size of repetitive data in the image.

### License
This project is licensed under the MIT License.

### Contact
Developed by Mithushan. Contact: mithushan.ravichandramohan@gmail.com
