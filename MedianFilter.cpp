#pragma hdrstop

#include "MedianFilter.h"
#include "list"
#include "algorithm"

using namespace std;
using namespace System;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::Windows::Forms;

void MedianFilter::init(){
	this->imageRed = new byte* [image->Width];
	this->imageGreen = new byte* [image->Width];
	this->imageBlue = new byte* [image->Width];
	for (int i = 0; i < image->Width; i++){
		imageRed[i] = new byte[image->Height];
		imageGreen[i] = new byte[image->Height];
		imageBlue[i] = new byte[image->Height];
	}
	for (int i = 0; i < image->Width; i++){
		for (int j = 0; j < image->Height; j++){
			Color c = image->GetPixel(i, j);
			imageRed[i][j] = (byte)c.R;
			imageGreen[i][j] = (byte)c.G;
			imageBlue[i][j] = (byte)c.B;
		}
	}
}

void MedianFilter::filtering(int n){
	list<byte> termsListRed;
	list<byte> termsListGreen;
	list<byte> termsListBlue;
	init();

	for (int i = 0; i <= image->Width - n; i++) {
		for (int j = 0; j <= image->Height - n; j++) {
			for (int x = i; x <= i + (n - 1); x++) {
				for (int y = j; y <= j + (n - 1); y++) {
					termsListRed.push_back(imageRed[x][y]);
					termsListGreen.push_back(imageGreen[x][y]);
					termsListBlue.push_back(imageBlue[x][y]);
				}
			}

			byte* termRed = new byte[termsListRed.size()];
			byte* termGreen = new byte[termsListGreen.size()];
			byte* termBlue = new byte[termsListBlue.size()];

			int k = 0;
			for (byte const& i : termsListRed)
				termRed[k++] = i;
			k = 0;
			for (byte const& i : termsListGreen)
				termGreen[k++] = i;
			k = 0;
			for (byte const& i : termsListBlue)
				termBlue[k++] = i;

			sort(termRed, termRed + termsListRed.size());
			sort(termGreen, termGreen + termsListGreen.size());
			sort(termBlue, termBlue + termsListBlue.size());

			reverse(termRed, termRed + termsListRed.size());
			reverse(termGreen, termGreen + termsListGreen.size());
			reverse(termBlue, termBlue + termsListBlue.size());

			termsListRed.clear();
			termsListGreen.clear();
			termsListBlue.clear();

			byte colorRed = termRed[(n * n) / 2];
			byte colorGreen = termGreen[(n * n) / 2];
			byte colorBlue = termBlue[(n * n) / 2];

			delete[] termRed;
			delete[] termGreen;
			delete[] termBlue;

			image->SetPixel(i + (n / 2), j + (n / 2), Color::FromArgb(colorRed, colorGreen, colorBlue));
		}
	}
}

Bitmap^ MedianFilter::getImage(){
	return image;
}

//MedianFilter.cpp
