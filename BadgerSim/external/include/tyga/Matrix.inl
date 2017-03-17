/**
 @file      Matrix.inl
 @author    Tyrone Davison
 @date      September 2012
 */

namespace tyga
{

inline Matrix4x4::
Matrix4x4() : _00(1), _01(0), _02(0), _03(0),
              _10(0), _11(1), _12(0), _13(0),
              _20(0), _21(0), _22(1), _23(0),
              _30(0), _31(0), _32(0), _33(1)
{
}

inline Matrix4x4::
Matrix4x4(float M00, float M01, float M02, float M03,
          float M10, float M11, float M12, float M13,
          float M20, float M21, float M22, float M23,
          float M30, float M31, float M32, float M33)
            : _00(M00), _01(M01), _02(M02), _03(M03),
              _10(M10), _11(M11), _12(M12), _13(M13),
              _20(M20), _21(M21), _22(M22), _23(M23),
              _30(M30), _31(M31), _32(M32), _33(M33)
{
}
/*
inline Matrix4x3::
Matrix4x3() : _00(1), _01(0), _02(0),
              _10(0), _11(1), _12(0),
              _20(0), _21(0), _22(1),
              _30(0), _31(0), _32(0)
{
}

inline Matrix4x3::
Matrix4x3(float M00, float M01, float M02,
          float M10, float M11, float M12,
          float M20, float M21, float M22,
          float M30, float M31, float M32) : _00(M00), _01(M01), _02(M02),
                                             _10(M10), _11(M11), _12(M12),
                                             _20(M20), _21(M21), _22(M22),
                                             _30(M30), _31(M31), _32(M32)
{
}
*/
} // end namespace tyga
