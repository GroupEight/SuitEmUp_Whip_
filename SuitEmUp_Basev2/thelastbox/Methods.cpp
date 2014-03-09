//Methods.cpp//

#include "Methods.h"

float Methods::pi(){
	return 3.1415926535897932384626433832795;
}

float MetersToPixels(float Meters){
	return (32.f * Meters);
}

float PixelsToMeters(float Pixels){
	return (Pixels / 32.f);
}