#include "fbxLoader.h"
#include "ofbx.h"
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>


static void pushVec3(std::vector<float>& dest, const ofbx::Vec3& v) {
    float x, y, z; 
    ofbxVec3ToFloat(v, x, y, z);
    dest.push_back(x); 
    dest.push_back(y); 
    dest.push_back(z);
}
static void pushVec2(std::vector<float>& dest, const ofbx::Vec2& v) {
    float u, vv; 
    ofbxVec2ToFloat(v, u, vv);
    dest.push_back(u); 
    dest.push_back(vv);
}

