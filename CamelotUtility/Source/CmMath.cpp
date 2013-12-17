/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2011 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
-----------------------------------------------------------------------------
*/
#include "CmMath.h"
#include "CmVector2.h"
#include "CmVector3.h"
#include "CmVector4.h"
#include "CmRay.h"
#include "CmSphere.h"
#include "CmAABox.h"
#include "CmPlane.h"

namespace CamelotFramework
{
    const float Math::POS_INFINITY = std::numeric_limits<float>::infinity();
    const float Math::NEG_INFINITY = -std::numeric_limits<float>::infinity();
    const float Math::PI = (float)4.0f * std::atan(1.0f);
    const float Math::TWO_PI = (float)(2.0f * PI);
    const float Math::HALF_PI = (float)(0.5f * PI);
	const float Math::DEG2RAD = PI / 180.0f;
	const float Math::RAD2DEG = 180.0f / PI;
	const float Math::LOG2 = std::log(2.0f);

    Radian Math::acos(float val)
    {
        if (-1.0f < val)
        {
            if (val < 1.0f)
                return Radian(std::acos(val));
            else
                return Radian(0.0f);
        }
        else
        {
            return Radian(PI);
        }
    }

    Radian Math::asin(float val)
    {
        if (-1.0f < val)
        {
            if (val < 1.0f)
                return Radian(std::asin(val));
            else
                return Radian(HALF_PI);
        }
        else
        {
            return Radian(-HALF_PI);
        }
    }

    float Math::sign(float val)
    {
        if (val > 0.0f)
            return 1.0f;

        if (val < 0.0f)
            return -1.0f;

        return 0.0f;
    }

	float Math::invSqrt(float val)
	{
		return 1.0f/sqrt(val);
	}

	float Math::fastSin0(float val)
	{
		float angleSqr = val*val;
		float result = 7.61e-03f;
		result *= angleSqr;
		result -= 1.6605e-01f;
		result *= angleSqr;
		result += 1.0f;
		result *= val;
		return result;
	}

	float Math::fastSin1(float val)
	{
		float angleSqr = val*val;
		float result = -2.39e-08f;
		result *= angleSqr;
		result += 2.7526e-06f;
		result *= angleSqr;
		result -= 1.98409e-04f;
		result *= angleSqr;
		result += 8.3333315e-03f;
		result *= angleSqr;
		result -= 1.666666664e-01f;
		result *= angleSqr;
		result += 1.0f;
		result *= val;

		return result;
	}

	float Math::fastCos0(float val)
	{
		float angleSqr = val*val;
		float result = 3.705e-02f;
		result *= angleSqr;
		result -= 4.967e-01f;
		result *= angleSqr;
		result += 1.0f;

		return result;
	}

	float Math::fastCos1(float val)
	{
		float angleSqr = val*val;
		float result = -2.605e-07f;
		result *= angleSqr;
		result += 2.47609e-05f;
		result *= angleSqr;
		result -= 1.3888397e-03f;
		result *= angleSqr;
		result += 4.16666418e-02f;
		result *= angleSqr;
		result -= 4.999999963e-01f;
		result *= angleSqr;
		result += 1.0f;

		return result;
	}

	float Math::fastTan0(float val)
	{
		float angleSqr = val*val;
		float result = 2.033e-01f;
		result *= angleSqr;
		result += 3.1755e-01f;
		result *= angleSqr;
		result += 1.0f;
		result *= val;
		return result;
	}

	float Math::fastTan1(float val)
	{
		float angleSqr = val*val;
		float result = 9.5168091e-03f;
		result *= angleSqr;
		result += 2.900525e-03f;
		result *= angleSqr;
		result += 2.45650893e-02f;
		result *= angleSqr;
		result += 5.33740603e-02f;
		result *= angleSqr;
		result += 1.333923995e-01f;
		result *= angleSqr;
		result += 3.333314036e-01f;
		result *= angleSqr;
		result += 1.0f;
		result *= val;
		return result;
	}

	float Math::fastASin0(float val)
	{
		float root = sqrt(abs(1.0f - val));
		float result = -0.0187293f;
		result *= val;
		result += 0.0742610f;
		result *= val;
		result -= 0.2121144f;
		result *= val;
		result += 1.5707288f;
		result = HALF_PI - root*result;
		return result;
	}

	float Math::fastASin1(float val)
	{
		float root = sqrt(abs(1.0f - val));
		float result = -0.0012624911f;
		result *= val;
		result += 0.0066700901f;
		result *= val;
		result -= 0.0170881256f;
		result *= val;
		result += 0.0308918810f;
		result *= val;
		result -= 0.0501743046f;
		result *= val;
		result += 0.0889789874f;
		result *= val;
		result -= 0.2145988016f;
		result *= val;
		result += 1.5707963050f;
		result = HALF_PI - root*result;
		return result;
	}

	float Math::fastACos0(float val)
	{
		float root = sqrt(abs(1.0f - val));
		float result = -0.0187293f;
		result *= val;
		result += 0.0742610f;
		result *= val;
		result -= 0.2121144f;
		result *= val;
		result += 1.5707288f;
		result *= root;
		return result;
	}

	float Math::fastACos1(float val)
	{
		float root = sqrt(abs(1.0f - val));
		float result = -0.0012624911f;
		result *= val;
		result += 0.0066700901f;
		result *= val;
		result -= 0.0170881256f;
		result *= val;
		result += 0.0308918810f;
		result *= val;
		result -= 0.0501743046f;
		result *= val;
		result += 0.0889789874f;
		result *= val;
		result -= 0.2145988016f;
		result *= val;
		result += 1.5707963050f;
		result *= root;
		return result;
	}

	float Math::fastATan0(float val)
	{
		float valueSqr = val*val;
		float result = 0.0208351f;
		result *= valueSqr;
		result -= 0.085133f;
		result *= valueSqr;
		result += 0.180141f;
		result *= valueSqr;
		result -= 0.3302995f;
		result *= valueSqr;
		result += 0.999866f;
		result *= val;
		return result;
	}

	float Math::fastATan1(float val)
	{
		float valueSqr = val*val;
		float result = 0.0028662257f;
		result *= valueSqr;
		result -= 0.0161657367f;
		result *= valueSqr;
		result += 0.0429096138f;
		result *= valueSqr;
		result -= 0.0752896400f;
		result *= valueSqr;
		result += 0.1065626393f;
		result *= valueSqr;
		result -= 0.1420889944f;
		result *= valueSqr;
		result += 0.1999355085f;
		result *= valueSqr;
		result -= 0.3333314528f;
		result *= valueSqr;
		result += 1.0f;
		result *= val;
		return result;
	}

    bool Math::approxEquals(float a, float b, float tolerance)
    {
        if (fabs(b-a) <= tolerance)
            return true;
        else
            return false;
    }

	Vector3 Math::calculateTriTangent(const Vector3& position1, const Vector3& position2, 
		const Vector3& position3, float u1, float v1, float u2, float v2, float u3, float v3)
	{
		Vector3 side0 = position1 - position2;
		Vector3 side1 = position3 - position1;

		// Calculate face normal
		Vector3 normal = side1.cross(side0);
		normal.normalize();

		// Now we use a formula to calculate the tangent. 
		float deltaV0 = v1 - v2;
		float deltaV1 = v3 - v1;
		Vector3 tangent = deltaV1 * side0 - deltaV0 * side1;
		tangent.normalize();

		// Calculate binormal
		float deltaU0 = u1 - u2;
		float deltaU1 = u3 - u1;
		Vector3 binormal = deltaU1 * side0 - deltaU0 * side1;
		binormal.normalize();

		// Now, we take the cross product of the tangents to get a vector which 
		// should point in the same direction as our normal calculated above. 
		// If it points in the opposite direction (the dot product between the normals is less than zero), 
		// then we need to reverse the s and t tangents. 
		// This is because the triangle has been mirrored when going from tangent space to object space.
		// reverse tangents if necessary.
		Vector3 tangentCross = tangent.cross(binormal);
		if (tangentCross.dot(normal) < 0.0f)
		{
			tangent = -tangent;
			binormal = -binormal;
		}

		return tangent;
	}
}
