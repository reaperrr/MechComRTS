/*****************************************************************************
	solextract

    Extracts a file from a SOL, PKK, SAV or MPK file.

    Since these files don't store a filename inside them, we can only
	extract the files by file index.

    Written by cmunsta
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <io.h>
#include <string.h>


extern long LZDecomp(unsigned char *OutputBuffer, unsigned char *CompressedBuffer, unsigned long CompBufferLength);


FILE *infile, *outfile;


long Checksum;
long DataStartOffset;
long NumEntries;
long FileSize;
int Index;

int *CompressedFlags;
long *DataOffsets;
long *DataSizes;

unsigned char *DecompBuffer;
unsigned char *ReadBuffer;

long UncompressedSize;
long DecompSize;



void main(int argc, char *argv[])
{
	int x;
	
	printf("-- solextract -- extracts a file from a SOL, PKK, SAV or MPK file --\n\n");

	if(argc != 4)
	{
		printf("Usage:  solextract <SOL file> <file index #> <file to create>\n\n");
		printf("    Please note that SOL, PKK, SAV and MPK files do not contain\n");
		printf("    filenames making it impossible to recreate original filenames\n");
		exit(0);
	}

	if((infile = fopen(argv[1],"rb")) == NULL)
	{
		printf("Can't open %s\n",argv[1]);
		exit(0);
	}

	Index = atoi(argv[2]);

	FileSize = filelength(fileno(infile));

	fread(&Checksum,4,1,infile);
	fread(&DataStartOffset,4,1,infile);

	NumEntries = (DataStartOffset - 8) / 4;

	if(Index < 0 || Index >= NumEntries)
	{
		printf("Desired file index (%d) is out of bounds. Valid indecies are 0 to %d\n", Index, NumEntries - 1);
		exit(0);
	}

	if((outfile = fopen(argv[3],"wb")) == NULL)
	{
		printf("Can't open output file: %s\n",argv[3]);
		exit(0);
	}


	// We add one so we can fake an extra entry that will represent the end of the file.
	DataOffsets = (long *)malloc((NumEntries + 1) * sizeof(long)); // we are considering long to be 32 bits here
	if(DataOffsets == NULL)
	{
		printf("Error -- Can't alloc mem for data offset table\n");
		exit(0);
	}

	// We create a table to hold the size of all the data
	DataSizes = (long *)malloc(NumEntries * sizeof(long)); // we are considering long to be 32 bits here
	if(DataSizes == NULL)
	{
		printf("Error -- Can't alloc mem for data size table\n");
		exit(0);
	}

	// We also need an array to hold the compressed/uncompressed flags
	CompressedFlags = (int *)malloc(NumEntries * sizeof(int));
	if(CompressedFlags == NULL)
	{
		printf("Error -- Can't alloc mem for flag table\n");
		exit(0);
	}

	fread(DataOffsets, 4, NumEntries, infile);

	// Set our faked last entry.
	DataOffsets[NumEntries] = FileSize;

	// Set up the compressed flags array (and remove the flag from the offset entry)
	for(x=0;x<NumEntries;x++)
	{
		if(DataOffsets[x] & 0x40000000)
		{
			DataOffsets[x] &= ~0x40000000;	// we need to remove this flag so the offsets are correct
			CompressedFlags[x] = 1;
		}
		else
			CompressedFlags[x] = 0;
	}


	// Calc sizes of data (this is why we added that extra entry and the end of the DataOffsets array)
	for(x=0;x<NumEntries;x++)
		DataSizes[x] = DataOffsets[x+1] - DataOffsets[x];

	// Now let's try to extract an entry
	ReadBuffer = (unsigned char *)malloc(DataSizes[Index]);
	if(ReadBuffer == NULL)
	{
		printf("Error -- Can't alloc mem for read buffer\n");
		exit(0);
	}

	fseek(infile,DataOffsets[Index],SEEK_SET);

	fread(ReadBuffer,1,DataSizes[Index],infile);

	// Try decompressing the data if it is compressed
	if(CompressedFlags[Index])
	{
		// The data is compressed, so the first DWORD is the uncompressed size of the file, the remainder is
		// the compressed data
		UncompressedSize = *((long *)ReadBuffer);

		DecompBuffer = (unsigned char *)malloc(UncompressedSize + 16); // Adding a little head room just in case
		DecompSize = LZDecomp(DecompBuffer, &ReadBuffer[4], DataSizes[Index]-4);

		fwrite(DecompBuffer,1,DecompSize,outfile);
		free(DecompBuffer);
	}
	else
	{
		fwrite(ReadBuffer,1,DataSizes[Index],outfile);
	}

	free(ReadBuffer);
	free(CompressedFlags);
	free(DataOffsets);
	free(DataSizes);

	fclose(infile);
	fclose(outfile);
}


