/**
 @file      Quaternion.inl
 @author    Tyrone Davison
 @date      October 2013
 */

namespace tyga
{

inline Quaternion::
Quaternion() : w(0), x(0), y(0), z(0)
{
}

inline Quaternion::
Quaternion(float W, float X, float Y, float Z) : w(W), v(X, Y, Z)
{
}

inline Quaternion::
Quaternion(float W, Vector3 V) : w(W), v(V)
{
}

} // end namespace tyga
