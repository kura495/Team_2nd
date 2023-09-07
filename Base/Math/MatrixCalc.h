#pragma once
#include "Math_Structs.h"
#include <numbers>
#include <cmath>

Matrix4x4 MakeIdentity4x4();
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
Matrix4x4 MakeScaleMatrix(const Vector3& scale);
Matrix4x4 MakeRotateXMatrix(float radian);
Matrix4x4 MakeRotateYMatrix(float radian);
Matrix4x4 MakeRotateZMatrix(float radian);
Matrix4x4 MakeRotateMatrix(Vector3 rotation);
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
float det(const Matrix4x4& m);
Matrix4x4 Inverse(const Matrix4x4& m);
//透視投影行列
Matrix4x4 MakePerspectiveFovMatrix(float FovY, float aspectRatio, float nearClip, float farClip);
//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);
//cotangent関数
float cot(float top);

Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom,float nearClip,float farCcip);