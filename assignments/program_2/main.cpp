/* @ProgramName: Program-2
* @Author: Kanayo oji
* @Description:
*This program creates class templates for images stored as rgb values in a space delimited file format.
* @Course: 1063 Data Structures
* @Semester: Spring 2017
* @Date: 02 12 2017
*/

#include <iostream>
#include <fstream>
#include <string>
#include<math.h>

using namespace std;

/**
Structure to hold an rgb value
*/
struct rgb{
	int r;
	int g;
	int b;
};

class ImageManip{
private:
	rgb** image;
	int width;
	int height;
	ifstream infile;
	ofstream ofile;
	string ifile_name;
	string ofile_name;
public:
	void readFile(string filename){
		infile.open(filename);
		infile >> width >> height;   //Read in width and height from top of input file
		//We need this so we can make the array the right 
		//size. After we get these two values, we can
		//now allocate memory for our 2D array.

		image = new rgb*[height];    //This array points to every row

		for (int i = 0; i<height; i++){
			image[i] = new rgb[width]; //Now allocate each row of rgb's
		}

		//Read the color data in from our txt file
		for (int i = 0; i<height; i++){
			for (int j = 0; j<width; j++){
				infile >> image[i][j].r >> image[i][j].g >> image[i][j].b;
			}
		}
	}

	void writeFile(string filename){
		ofile.open(filename);
		//Write out our color data to a new file
		ofile << width << " " << height << endl;
		for (int i = 0; i<height; i++){
			for (int j = 0; j<width; j++){
				ofile << image[i][j].r << " " << image[i][j].g << " " << image[i][j].b << " ";
			}
			ofile << endl;
		}
	}

	/**
	* @FunctionName: grayScale
	* @Description:
	*     Loops through a 2D array and turns every RGB value into its grayscale equivalent.
	* @Params:
	*    rgb** image - 2D array holding rgb values
	*    int width - width of image
	*    int height - height of image
	* @Returns:
	*    void
	*/
	void grayScale(rgb** image, int width, int height){
		int gray;
		for (int r = 0; r < height; r++) {
			for (int c = 0; c < width; c++) {
				gray = (image[r][c].r + image[r][c].g + image[r][c].b) / 3;

				image[r][c].r = gray;
				image[r][c].g = gray;
				image[r][c].b = gray;
			}
		}
	}

	/**
	* @FunctionName: flipHorz
	* @Description:
	*     Loops through a 2D array and flips the image horizontally.
	* @Params:
	*    rgb** image - 2D array holding rgb values
	*    int width - width of image
	*    int height - height of image
	* @Returns:
	*    void
	*/

	void flipHorz(rgb** image, int width, int height){
		rgb temp;


		for (int i = 0; i < height; i++) {
			for (int y = 0; y < (width / 2); y++) {
				temp = image[i][y];
				image[i][y] = image[i][width - 1 - y];
				image[i][width - 1 - y] = temp;

			}
		}
	}

	/**
	* @FunctionName: flipVert
	* @Description:
	*     Loops through a 2D array and flips the image vertically.
	* @Params:
	*    rgb** image - 2D array holding rgb values
	*    int width - width of image
	*    int height - height of image
	* @Returns:
	*    void
	*/

	void flipVert(rgb** image, int width, int height){
		rgb temp;

		for (int i = 0; i < (height / 2); i++) {
			for (int y = 0; y < width; y++) {
				temp = image[i][y];
				image[i][y] = image[height - 1 - i][y];
				image[height - 1 - i][y] = temp;
			}
		}
	}
};

int main(){
	ifstream ifile;          //Input / output files
	ofstream ofile;
	ifile.open("input.txt");
	ofile.open("bot2.txt");

	int width;               //width of image
	int height;              //height of image

	rgb **imgArray;         //Pointer var for our 2D array because we         
	//don't know how big the image will be!

	ifile >> width >> height;   //Read in width and height from top of input file
	//We need this so we can make the array the right 
	//size. After we get these two values, we can
	//now allocate memory for our 2D array.

	imgArray = new rgb*[height];    //This array points to every row

	for (int i = 0; i<height; i++){
		imgArray[i] = new rgb[width]; //Now allocate each row of rgb's
	}

	//Read the color data in from our txt file
	for (int i = 0; i<height; i++){
		for (int j = 0; j<width; j++){
			ifile >> imgArray[i][j].r >> imgArray[i][j].g >> imgArray[i][j].b;
		}
	}
	ImageManip im;
	im.flipVert(imgArray, width, height);
	im.flipHorz(imgArray, width, height);
	im.grayScale(imgArray, width, height);

	//Write out our color data to a new file
	ofile << width << " " << height << endl;
	for (int i = 0; i<height; i++){
		for (int j = 0; j<width; j++){

			ofile << imgArray[i][j].r << " " << imgArray[i][j].g << " " << imgArray[i][j].b << " ";
		}
		ofile << endl;
	}


	return 0;
}
