
#include <stdio.h>

typedef unsigned char byte;

enum LoadErr {NoError=0, OpenError, FileFormatError, MemoryError, ReadError,	WriteError};


class RgbImage{
	unsigned char* ImagePtr;	// array of pixel values (integers range 0 to 255)
	long NumRows;				// number of rows in image
	long NumCols;				// number of columns in image
	LoadErr ErrorCode;			// error code
	static const int BLACK = 0;
public:

	RgbImage():ImagePtr(NULL),NumRows(0),NumCols(0),ErrorCode(NoError){}
	RgbImage( const char* filename ):ImagePtr(NULL),NumRows(0),NumCols(0),ErrorCode(NoError){
		LoadBmpFile( filename );
	}
	~RgbImage(){delete[] ImagePtr;}

	bool LoadBmpFile( const char *filename );		// Loads the bitmap from the specified file
	long GetNumRows() const { return NumRows; }
	long GetNumCols() const { return NumCols; }
	// Rows are word aligned
	long GetNumBytesPerRow() const { return ((3*NumCols+3)>>2)<<2; }
	const void* ImageData() const { return (void*)ImagePtr; }
	int GetErrorCode() const { return ErrorCode; }
	bool ImageLoaded() const { return (ImagePtr!=0); }

	void clear(){
		NumRows = 0;NumCols = 0;
		delete[] ImagePtr;
		ImagePtr = 0; ErrorCode = NoError;
	}


private:

	static short readShort( FILE* infile ){
		byte lowByte, hiByte;
		lowByte = fgetc(infile); hiByte = fgetc(infile);
		return (hiByte<<8)|lowByte;
	}
	static long readLong( FILE* infile ){
		byte bytes[3]; for(int i=0;i<3;i++)bytes[i]=fgetc(infile);
		long res=fgetc(infile); for(int i=2;i>=0;i--) res=(res<<8)|bytes[i];
		return res;
	}
	static void skipChars( FILE* infile, int numChars ){
		for ( int i=0; i<numChars; i++ ) fgetc( infile );
	}

	static byte dblToByte( double x ){
		return x>1.? 255 : x<0.? 0 : (unsigned char)(x*255);
	}
};
// Bitmap file format  (24 bit/pixel form)		BITMAPFILEHEADER
// Header (14 bytes)
//	 2 bytes: "BM"
//   4 bytes: long int, file size
//   4 bytes: reserved (actually 2 bytes twice)
//   4 bytes: long int, offset to raster data
// Info header (40 bytes)						BITMAPINFOHEADER
//   4 bytes: long int, size of info header (=40)
//	 4 bytes: long int, bitmap width in pixels
//   4 bytes: long int, bitmap height in pixels
//   2 bytes: short int, number of planes (=1)
//   2 bytes: short int, bits per pixel
//   4 bytes: long int, type of compression (not applicable to 24 bits/pixel)
//   4 bytes: long int, image size (not used unless compression is used)
//   4 bytes: long int, x pixels per meter
//   4 bytes: long int, y pixels per meter
//   4 bytes: colors used (not applicable to 24 bit color)
//   4 bytes: colors important (not applicable to 24 bit color)
// "long int" really means "unsigned long int"
// Pixel data: 3 bytes per pixel: RGB values (in reverse order).
//	Rows padded to multiples of four.

bool RgbImage::LoadBmpFile( const char* filename ) {
	clear(); FILE* infile;
	//int err =
	infile=fopen(filename, "rb" );		// Open for reading binary data
	if ( infile==NULL) {
		printf("Unable to open file: %s\n", filename);
		ErrorCode = OpenError;
		return false;
	}

	bool fileFormatOK = false;
	int bChar = fgetc( infile );
	int mChar = fgetc( infile );
	if ( bChar=='B' && mChar=='M' ) {			// If starts with "BM" for "BitMap"
		skipChars( infile, 4+2+2+4+4 );			// Skip 4 fields we don't care about
		NumCols = readLong( infile );
		NumRows = readLong( infile );
		skipChars( infile, 2 );					// Skip one field
		int bitsPerPixel = readShort( infile );
		skipChars( infile, 4+4+4+4+4+4 );		// Skip 6 more fields

		if ( NumCols>0 && NumCols<=100000 && NumRows>0 && NumRows<=100000
			&& bitsPerPixel==24 && !feof(infile) ) {
			fileFormatOK = true;
		}
	}
	if ( !fileFormatOK ) {
		clear();
		ErrorCode = FileFormatError;
		fprintf(stderr, "Not a valid 24-bit bitmap file: %s.\n", filename);
		fclose ( infile );
		return false;
	}

	// Allocate memory
	ImagePtr = new unsigned char[NumRows*GetNumBytesPerRow()];
	if ( !ImagePtr ) {
		fprintf(stderr, "Unable to allocate memory for %ld x %ld bitmap: %s.\n",
				NumRows, NumCols, filename);
		clear();
		ErrorCode = MemoryError;
		fclose ( infile );
		return false;
	}

	unsigned char* cPtr = ImagePtr;
	for ( int i=0; i<NumRows; i++ ) {
		int j;
		for ( j=0; j<NumCols; j++ ) {
			*(cPtr+2) = fgetc( infile );	// Blue color value
			*(cPtr+1) = fgetc( infile );	// Green color value
			*cPtr = fgetc( infile );		// Red color value
			cPtr += 3;
		}
		int k=3*NumCols;					// Num bytes already read
		for ( ; k<GetNumBytesPerRow(); k++ ) {
			fgetc( infile );				// Read and ignore padding;
			*(cPtr++) = 0;
		}
	}
	if ( feof( infile ) ) {
		fprintf( stderr, "Premature end of file: %s.\n", filename );
		clear();
		ErrorCode = ReadError;
		fclose ( infile );
		return false;
	}
	fclose( infile );
	return true;
}

