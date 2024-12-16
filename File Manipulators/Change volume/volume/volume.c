
// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// https://docs.fileformat.com/audio/wav/
// Number of bytes in .wav header

const int HEADER_SIZE = 44;
const int SAMPLE_SIZE = 2;
const int BYTE = 8;
const int bytePosition_of_StartData = HEADER_SIZE + 1; //index: (HEADER_SIZE-1) + 1

uint32_t ui32_BigEndian_to_LittleEndian(uint8_t buffer[]){
    uint32_t ui32_LittleEndian = 0x0;
    uint32_t displacedBits = 0x0;
    uint32_t numBytes = 4;
    for (uint32_t i = 0; i < numBytes; i++){
        displacedBits = 0x0;
        displacedBits = (buffer[i] | displacedBits) << (BYTE * i);
        ui32_LittleEndian = ui32_LittleEndian | displacedBits;
    }
    return ui32_LittleEndian;
}

void SubArray_uint8(uint8_t sourceArray[], uint8_t destinyArray[], int startIndex, int endIndex){
    for (int sc = startIndex, dc = 0; sc < endIndex + 1; sc++, dc++){
        destinyArray[dc] = sourceArray[sc];
    }
}

//Volume modifier, a factor of 1 is the same audio, a factor of 2 is the double
void VolumeModifier(int16_t* buffer, uint32_t elementsQuantity, float newFactor){
    for (uint32_t i = 0; i < elementsQuantity; i++){

        //Temporal bigger sample
        int32_t newSample = (int32_t)(buffer[i] * newFactor);

        // Overflow control
        if (newSample > INT16_MAX){ newSample = INT16_MAX; }
        else if (newSample < INT16_MIN){ newSample = INT16_MIN; }

        buffer[i] = (int16_t)newSample;
    }
}


int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }


    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    //--------------- Copy header from input file to output file --------------------------------

    uint8_t headerBuffer[HEADER_SIZE];
    fread(headerBuffer, HEADER_SIZE, 1, input);
    fwrite(headerBuffer, HEADER_SIZE, 1, output);

    // ----------------- Read samples from input file and write updated data to output file -------------------------


    // BE -> Big Endian | LE -> Little Endian
    // Get Size of Data Section (Header: 40-43) in original source (BE)
    uint8_t BE_SizeofDataSection[4];
    SubArray_uint8(headerBuffer, BE_SizeofDataSection, 40, 43);

    // We need the size of data section in BE for read and write using buffers, and not fgetc and fputc
    uint32_t LE_SizeofDataSection = ui32_BigEndian_to_LittleEndian(BE_SizeofDataSection);

    // Marks the beginning of the data section and read into a buffer
    fseek(input, bytePosition_of_StartData - 1, SEEK_SET); // Change reading pointer

    // This buffer content the audio section.
    // The audio data section works with 16 bits signed integer numbers, so int16_t
    int16_t *audioDataBuffer = (int16_t *) malloc((LE_SizeofDataSection/SAMPLE_SIZE) * sizeof(int16_t));
    fread(audioDataBuffer, LE_SizeofDataSection, 1, input);

    // We´ll modify the audio file
    VolumeModifier(audioDataBuffer, LE_SizeofDataSection / SAMPLE_SIZE, factor);

    //Write the new audio file
    fwrite(audioDataBuffer, LE_SizeofDataSection, 1, output);

    // Close files and free pointers
    free(audioDataBuffer);
    fclose(input);
    fclose(output);
}


