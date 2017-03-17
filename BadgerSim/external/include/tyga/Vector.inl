/**
 @file      Vector.inl
 @author    Tyrone Davison
 @date      September 2012
 */

namespace tyga
{

inline Vector2::
Vector2() : x(0), y(0)
{
}

inline Vector2::
Vector2(float V0, float V1) : x(V0), y(V1)
{
}

inline Vector3::
Vector3() : x(0), y(0), z(0)
{
}

inline Vector3::
Vector3(float V0, float V1, float V2) : x(V0), y(V1), z(V2)
{
}

inline Vector3::
Vector3(Vector2 V01, float V2) : x(V01.x), y(V01.y), z(V2)
{
}

inline Vector4::
Vector4() : x(0), y(0), z(0), w(1)
{
}

inline Vector4::
Vector4(float V0, float V1, float V2, float V3)
    : x(V0), y(V1), z(V2), w(V3)
{
}

inline Vector4::
Vector4(Vector2 V01, float V2, float V3)
    : x(V01.x), y(V01.y), z(V2), w(V3)
{
}

inline Vector4::
Vector4(Vector3 V012, float V3)
    : x(V012.x), y(V012.y), z(V012.z), w(V3)
{
}

} // end namespace tyga
