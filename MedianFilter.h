#include "Windows.h"

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

ref class MedianFilter {
	Bitmap^ image;
	byte** imageRed;
	byte** imageGreen;
	byte** imageBlue;

	void init();
	
	public:
		MedianFilter(Bitmap^);
		void filtering(int);
		Bitmap^ getImage();
};