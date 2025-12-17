#ifndef UTILS
#define UTILS
#include <vector>
#include <string>
#include "ofbx.h"

inline void ofbxVec3ToFloat(const ofbx::Vec3& v, float& x, float& y, float& z) {
#ifdef OFBX_DOUBLE_PRECISION
    x = static_cast<float>(v.x);
    y = static_cast<float>(v.y);
    z = static_cast<float>(v.z);
#else
    x = v.x; y = v.y; z = v.z;
#endif
}
inline void ofbxVec2ToFloat(const ofbx::Vec2& v, float& x, float& y) {
#ifdef OFBX_DOUBLE_PRECISION
    x = static_cast<float>(v.x);
    y = static_cast<float>(v.y);
#else
    x = v.x; y = v.y;
#endif
}
#endif
