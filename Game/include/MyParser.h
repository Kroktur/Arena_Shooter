#ifndef PARSER
#define PARSER
#include "ofbx.h"

struct vect {
	const char* name;
	double x; 
	double y; 
	double z;
};

std::vector<const ofbx::Mesh*> parser();

#endif 
