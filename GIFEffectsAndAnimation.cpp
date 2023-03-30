// 	Part A creates animated GIF successfully: Yes
//	Part B creates animated GIF with effects successfully: Yes
//	Web page launches successfully from program: Yes
// 	Any other comments?

#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>

using namespace std;

void showWebPage (string URL) {
	char cURL [50];
	int i;

	for (i = 0; i < URL.length(); i=i+1){
    	cURL[i] = URL[i];
	}

	cURL[URL.length()] = '\0';
    
    ShellExecute(NULL, "open", cURL, NULL, NULL, SW_SHOWNORMAL);
}


void toGrayScale (int * red, int * green, int * blue) {
	
	int avg;

	avg = (*red + *green + *blue) /3;
	
	*red = avg;
	*green = avg;
	*blue = avg;
	

}


void toBlueTint (int * red, int * green, int * blue) {
	
	int avg;
	
	avg = (*red + *green + *blue) /3;
	
	*red = avg;
	*green = avg;
	*blue = *blue;
	

}


void toRedTint (int * red, int * green, int * blue) {
	 
	int avg;

	avg = (*red + *green + *blue) /3;
	
	*red = *red;
	*green = avg;
	*blue = avg;
}


void toSepia (int * red, int * green, int * blue) {
	int Max = 255;
	
	int newRed,  newGreen, newBlue;
	
	newRed = (*red * 0.393) + (*green * 0.769 )+ (*blue * 0.189);
	newGreen =(*red * 0.349) + (*green * 0.686) + (*blue * 0.168);
	newBlue = (*red * 0.272 )+ (*green * 0.534 )+ (*blue * 0.131);

	if (newRed > Max ){
		*red=Max;
	}	
	else
	      *red=newRed;
	if (newGreen > Max){
		*green=Max;
	}
	else
	      *green=newGreen;
	if (newBlue > Max){
		*blue=Max;
	}
	else
	      *blue=newBlue;


}
	

void brighten (int * red, int * green, int * blue, int percent) {
	
	int r, g, b;
	int max = 255;
    float pCent = (percent* 1.0)/100;
    
	r = *red + (*red * pCent); 
	g = *green + (*green * pCent);
	b = *blue + (*blue * pCent);


    if (r > max ){
		*red = max;
	}	
	else
	      *red = r;
	if (g > max){
		*green = max;
	}
	else
	      *green = g;
	if (b > max){
		*blue = max;
	}
	else
	      *blue = b;

}


int main() {
    
    unsigned char Header[6] = {71, 73, 70, 56, 57, 97};
	unsigned char logicalScreenDescriptor[7] = {88, 2, 144,  1, 112, 0, 0};
	unsigned char appExtension[19] = {33, 255, 11, 78, 69, 84, 83, 67, 65, 80, 69, 50, 46, 48, 3, 1, 0, 0, 0};
	unsigned char graphicsControlExt[8] = {33, 249, 4, 8, 100, 0, 0, 0};
	
	char GIFFilenames [25];
	char GIFFilenamesEffects [25];	
	char animatedGIFFile [25];
	char effectsGIFFile [25];	
	char webPage [25];
	
	strcpy (GIFFilenames, "GIF-Filenames.txt");	
	strcpy (GIFFilenamesEffects, "GIF-Filenames-Effects.txt");		
	strcpy (animatedGIFFile, "Scenery-Animated.gif");
	strcpy (effectsGIFFile, "Scenery-Animated-Effects.gif");	
	strcpy (webPage, "Assignment3.html");
	
	cout << "Creating animated GIF ..." << endl;

	// Insert code here to create animated GIF or call function to do so.
	
	ofstream outputFile;
	outputFile.open(animatedGIFFile, ios::binary | ios::out);
	
	
    for (int i = 0; i < 6; i++){
    	outputFile.write((char*) &Header[i], sizeof (char));
	}
	
	for (int j = 0; j < 7; j++){
		outputFile.write((char*) &logicalScreenDescriptor[j], sizeof (char));
	}
    
    for (int k = 0; k < 19; k++){	
        outputFile.write((char*) &appExtension[k], sizeof (char));
    }
    
    for (int l = 0; l < 8; l++){	
        outputFile.write((char*) &graphicsControlExt[l], sizeof (char));
    }
    

	ifstream input, input1;
	
	input.open(GIFFilenames);
	
	if(!input.is_open()){
		cout << " There was an error opening the GIF filenames file.";
		return -1;
	}
	
   char gifFile[10];
	
	input >> gifFile;

	while (!input.eof()){
		input1.open(gifFile, ios::binary | ios::in);
		
		long fileLocation = 13;
    	input1.seekg(fileLocation);
	
	
	   if(!input1.is_open()){
		 cout << " There was an error opening the file.";
		 return -1;
	   }
	
		for (int l = 0; l < 8; l++){	
	        outputFile.write((char*) &graphicsControlExt[l], sizeof (char));
	    }
		
		unsigned char gifFile1;
		
		input1.read((char*) &gifFile1, sizeof(char)); 
		while (!input1.eof()){
			outputFile.write((char*) &gifFile1, sizeof(char));
			input1.read((char*) &gifFile1, sizeof(char));
		}
		input1.close();
		outputFile.seekp(-1,ios::cur);
		input >> gifFile;	
	}
	
	int val = 59;
	
	outputFile.write((char*) &val, sizeof(char));    
    
	cout << "Animated GIF created." << endl;
	cout << endl;
	
	cout << "Applying Effects to Animated GIF ..." << endl;
	
	// Insert code here to create animated GIF with effects
	//   or call function to do so.


	ofstream output;
	output.open(effectsGIFFile, ios::binary | ios::out);
	
	
    for (int i = 0; i < 6; i++){
    	output.write((char*) &Header[i], sizeof (char));
	}
	
	for (int j = 0; j < 7; j++){
		output.write((char*) &logicalScreenDescriptor[j], sizeof (char));
	}
    
    for (int k = 0; k < 19; k++){	
        output.write((char*) &appExtension[k], sizeof (char));
    }
    
    for (int l = 0; l < 8; l++){	
        output.write((char*) &graphicsControlExt[l], sizeof (char));
    }
    

	ifstream input2, input3;
	
	input2.open(GIFFilenamesEffects);
	
	if(!input2.is_open()){
		cout << " There was an error opening the GIF filenames file.";
		return -1;
	}
	
	char gifFile1[10];
	string effects;
	
	input2 >> gifFile1;

	while (!input2.eof()){
		input2 >> effects;
		cout << gifFile1 << "\t" << effects << endl;
		
		input3.open(gifFile1, ios::binary | ios::in);
		
		long fileLocation = 13;
    	input3.seekg(fileLocation);
	
	
	   if(!input3.is_open()){
		 cout << " There was an error opening the file.";
		 return -1;
	   }
	
		for (int l = 0; l < 8; l++){	
	        output.write((char*) &graphicsControlExt[l], sizeof (char));
	    }
		
		for (int w = 0; w < 10; w++){
			input3.read((char*) &gifFile1, sizeof(char));
			output.write((char*) &gifFile1, sizeof(char));
		}
		
	
		int * red;
		red = new int;
		
		int * green;
		green = new int;
		
		int * blue;
		blue = new int;
		
		unsigned char gifFile2;
	
		int pcent = 60;
		int count = 0;
		
		while (count < 256){
			input3.read((char*) &gifFile2, sizeof(char));
		    *red=gifFile2;
		    input3.read((char*) &gifFile2, sizeof(char));
		    *green=gifFile2;
		    input3.read((char*) &gifFile2, sizeof(char));
		    *blue=gifFile2;
		
		    if (effects == "grayScale")
		    	toGrayScale(red, green, blue);
		    
		    if(effects == "blueTint")
				toBlueTint(red,green,blue);
			
			if(effects == "redTint")
				toRedTint(red,green,blue);
			
			if(effects == "sepia")
				toSepia(red,green,blue);
			
			if(effects == "brighten")	
				brighten(red,green,blue,pcent);
			
			gifFile2=*red;
			output.write((char*) &gifFile2, sizeof(char));
		    
		    gifFile2=*green;
		    output.write((char*) &gifFile2, sizeof(char));
		    
		    gifFile2=*blue;
		    output.write((char*) &gifFile2, sizeof(char));
		   
			
			count++;
		}
		
		input3.read((char*) &gifFile2, sizeof(char)); 
		while (!input3.eof()){
			output.write((char*) &gifFile2, sizeof(char));
			input3.read((char*) &gifFile2, sizeof(char));
		}
		
		
		input3.close();
		output.seekp(-1,ios::cur);
		
		input2 >> gifFile1;	
	}
	
	int val1 = 59;
	
	output.write((char*) &val1, sizeof(char));    
    

	cout << "Effects Applied to Animated GIF." << endl;
	cout << endl;  
	
	cout << "About to launch Web page to display animated GIFs ..." << endl;
	
	showWebPage(webPage);
	
	cout << endl;
	cout << "End of program.";
	 
  	return 0;
}

