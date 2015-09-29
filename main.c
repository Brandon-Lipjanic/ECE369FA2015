
#include <stdio.h>
#include <stdlib.h>
#include <process.h>

int* spiral(int* fwSize, int* frameAddress1, int* windowAddress1);
int compare(int* fwSize, int* frameAddress, int* windowAddress);
int SAD(int* frameAddress, int* windowAddress);
void findFramePoints(int* fwSize, int* frameAddress, int* SADAddress);
	int arrayPositions[2];
	int* arrayPositionsAddress = arrayPositions;

// frame
int frame[16][16] = {
	{7, 5, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{7, 5, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{7, 5, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{7, 5, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
	{0, 4, 2, 3, 4, 5, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60},
	{0, 5, 3, 4, 5, 6, 30, 35, 40, 45, 0, 0, 0, 0, 70,  75},
	{0, 6, 12, 18, 24, 30, 36, 42, 48, 54, 0, 0, 0, 0, 84, 90},
	{0, 4, 8, 8, 8, 8, 42, 49, 56, 63, 0, 0, 0, 0, 98, 105},
	{ 0, 1, 8, 8, 8, 8, 48, 56, 64, 72, 0, 0, 0, 0, 112, 120},
	{0, 1, 8, 8, 8, 8, 54, 63, 72, 81, 90, 99, 108, 117, 126, 135},
	{0, 10, 8, 8, 8, 8, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150},
	{0, 11, 22, 33, 44, 55, 66, 77, 88, 99, 110, 121, 132, 143, 154, 165},
	{9, 9, 9, 9, 48, 60, 72, 84, 96, 108, 120, 132, 0, 1, 2, 3},
	{9, 9, 9, 9, 52, 65, 78, 91, 104, 114, 130, 143, 1, 2, 3, 4},
	{9, 9, 9, 9, 56, 70, 84, 98, 112, 126, 140, 154, 2, 3, 4, 5},
	{9, 9, 9, 9, 60, 75, 90, 105, 120, 135, 150, 165, 3, 4, 5, 6}
};
// frame begin addres
int* frameAddress = (int *) frame;
// window
int window[4][8] = { 
	{ 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0}
};
// window address
int* windowAddress = (int *) window;
// (frame row, frame cols, window row, window col)
int fwSize[4] = {16, 16, 4, 8}; // [i, j, k, l]
// fwSize address
int* fwSizeAddress = fwSize;



void main(){
	
	int* SADAddress;

	SADAddress = spiral(fwSizeAddress, frameAddress, windowAddress);

	//findFramePoints(fwSizeAddress, frameAddress, SADAddress);

	//printf("%d, %d \n", *(arrayPositionsAddress), *(arrayPositionsAddress + 1));

	system("pause");

	return;
}

int* spiral(int* fwSize, int* frameAddress1, int* windowAddress1){

	int frameRowSize = *(fwSize);
	int frameColSize = *(fwSize + 1);
	int windowRowSize = *(fwSize + 2);
	int windowColSize = *(fwSize + 3);

	int rowDistance = (frameColSize - windowColSize + 1);			// initialize first distance moved in row
	int colDistance = (frameRowSize - windowRowSize);				// initialize first distance moved in col

	int frameWidth = frameColSize;

	int whichLoop = 1;						// determines which case statement to follow
											// will be rowRight (1), colDown(2), rowLeft(3), colUp(4)
	int* frameAddress = frameAddress1;		// initialize frame address
	int* windowAddress = windowAddress1;		// initialize window address

	int* beginAddress = frameAddress;		// starting address
	int* SADAddress = frameAddress;			// the address of the window/frame combination with the smallest SAD
	int* endAddress = frameAddress;

	int minSAD = 100000000;
	int currentSAD = 0;
	int i;

	int tempColPosition = 0;
	int tempRowPosition = 0;
	int finalColPosition = 0;
	int finalRowPosition = 0;

	while(rowDistance >= 0 && colDistance >= 0){
		switch (whichLoop){
		case 1: // row right movement
			beginAddress = endAddress;
			for (i = 0; i < rowDistance; i++){
				currentSAD = compare(fwSize, beginAddress, windowAddress);
				//findFramePoints(fwSize, frameAddress, beginAddress);
				//printf("[%d, %d], ", arrayPositions[0], arrayPositions[1]);
				if (minSAD != 100000000){
					tempColPosition = tempColPosition + 1;	//Checks to make sure were not looking at the VERY first window/frame or else the position gets messed up.
				}
				if (currentSAD < minSAD){
					minSAD = currentSAD;
					SADAddress = beginAddress;
					finalColPosition = tempColPosition;
					finalRowPosition = tempRowPosition;
				}
				beginAddress = beginAddress + 1;	// in MIPS will be beginAddress + 4
			}


			endAddress = beginAddress - 1;
			rowDistance--;
			whichLoop = 2;
		break;

		case 2: // col down movement
			beginAddress = endAddress + frameWidth;		// in MIPS will be 4 * frameWidth

			for (i = 0; i < colDistance; i++){
				currentSAD = compare(fwSize, beginAddress, windowAddress);
				tempRowPosition = tempRowPosition + 1;
				//findFramePoints(fwSize, frameAddress, beginAddress);
				//printf("[%d, %d], ", arrayPositions[0], arrayPositions[1]);
				if (currentSAD < minSAD){
					minSAD = currentSAD;
					SADAddress = beginAddress;
					finalColPosition = tempColPosition;
					finalRowPosition = tempRowPosition;
				}
				beginAddress = beginAddress + frameWidth; // in MIPS will be (frameWidth * 4)
			}

			endAddress = beginAddress - frameWidth - 1; 
			colDistance--;
			whichLoop = 3;
		break;

		case 3: // row left movement
			beginAddress = endAddress;
			for (i = rowDistance; i > 0; i--){
				currentSAD = compare(fwSize, beginAddress, windowAddress);
				tempColPosition = tempColPosition - 1;
				//findFramePoints(fwSize, frameAddress, beginAddress);
				//printf("[%d, %d], ", arrayPositions[0], arrayPositions[1]);
				if (currentSAD < minSAD){
					minSAD = currentSAD;
					SADAddress = beginAddress;
					finalColPosition = tempColPosition;
					finalRowPosition = finalRowPosition;
				}
				beginAddress = beginAddress - 1;		// in MIPS will be beginAddress - 4
			}

			endAddress = beginAddress + 1;
			rowDistance--;
			whichLoop = 4;
		break;

		case 4: // col up movement
			beginAddress = endAddress - frameWidth;		// in MIPS will be 4 * frameWidth

			for (i = colDistance; i > 0; i--){
				currentSAD = compare(fwSize, beginAddress, windowAddress);
				tempRowPosition = tempRowPosition - 1;
				//findFramePoints(fwSize, frameAddress, beginAddress);
				//printf("[%d, %d], ", arrayPositions[0], arrayPositions[1]);
				if (currentSAD < minSAD){
					minSAD = currentSAD;
					SADAddress = beginAddress;
					finalColPosition = tempColPosition;
					finalRowPosition = tempRowPosition;
				}
				beginAddress = beginAddress - frameWidth; // in MIPS will be (frameWidth * 4)
			}
			endAddress = beginAddress + frameWidth + 1;
			colDistance--;
			whichLoop = 1;
		break;
		}
	}

	printf("(%d, %d)\n",finalRowPosition, finalColPosition); 
	return SADAddress;
}


int compare(int* fwSize, int* frameAddress, int* windowAddress){


	int frameRow = *(fwSize);
	int frameCol = *(fwSize + 1);
	int windowRow = *(fwSize + 2);
	int windowCol = *(fwSize + 3);
	
	int* frameAddressColMovement = frameAddress;
	int* windowAddressColMovement = windowAddress;
	int* frameAddressRowMovement = frameAddress;
	int* windowAddressRowMovement = windowAddress;
	int row = 0;
	int col = 0;
	int sum = 0;
	int value = 0;

	for (row = 0; row < windowCol; row++){

		frameAddressColMovement = frameAddressRowMovement; // restore original addresses
		windowAddressColMovement = windowAddressRowMovement;

		for (col = 0; col < windowRow; col++){

			value = SAD(frameAddressColMovement, windowAddressColMovement);
			sum = sum + value;

			frameAddressColMovement = frameAddressColMovement + frameCol; // movement down the column of frame
			windowAddressColMovement = windowAddressColMovement + windowCol; // movement down the column of window
		}

		frameAddressRowMovement = frameAddressRowMovement + 1; // movement across the row of frame
		windowAddressRowMovement = windowAddressRowMovement + 1; // movement across the row of window
	}

	//printf("%d\n", sum);

	return sum;
}

int SAD(int* frameAddress, int* windowAddress){

	int frameVal = *frameAddress;
	int windowVal = *windowAddress;
	int result = 0;

	result = abs(frameVal - windowVal);


	return result;
}

void findFramePoints(int* fwSize, int* frameAddress, int* SADAddress) {

	int frameRows = *(fwSize);			// number of rows in frame
	int frameColumns = *(fwSize + 1);	// number of columns in frame

	int addressDifference1 = SADAddress - frameAddress;
	int addressDifference2 = SADAddress - frameAddress;
	int rowNumber = 0;
	int colNumber = 0;
	int count = 0;
	int i = 0;
	int j = 0;


	//find row number
	for (i = 0; i < frameRows; i++){

		if (addressDifference1 < frameColumns) {
			rowNumber = count;
			break;
		}
		addressDifference1 = addressDifference1 - frameColumns;
		count++;
	}

	addressDifference2 = addressDifference2 - rowNumber*frameColumns;
	count = 0;
	// find column number
	for (j = 0; j < frameColumns; j++) {
	
		if(addressDifference2 == 0){
			colNumber = count;
			break;
		}
		addressDifference2--;
		count++;
	}

	arrayPositions[0] = rowNumber;
	arrayPositions[1] = colNumber;

}

