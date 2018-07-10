#include <iostream>
#include "geommath.hpp"
#include "portable.hpp"
using namespace std;
using namespace My;

void vector_test()
{
	Vector2f x = { 55.3f, 22.1f };
	cout << "Vector2f: ";
	cout << x;

	Vector3f a = { 1.0f, 2.0f, 3.0f };
	Vector3f b = { 5.0f, 6.0f, 7.0f };

	cout << "vec 1: ";
	cout << a;
	cout << "vec 2: ";
	cout << b;

	Vector3f c;
	CrossProduct(c, a, b);
	cout << "Cross Product of vec 1 and vec 2: ";
	cout << c;

	float d;
	d = DotProduct(a, b);
	cout << "Dot Product of vec 1 and vec 2: ";
	cout << d << std::endl;

	MulByElement(c, a, b);
	cout << "Element Product of vec 1 and vec 2: ";
	cout << c;

	Vector4f e = { -3.0f, 3.0f, 6.0f, 1.0f };
	Vector4f f = { 2.0f, 0.0f, -0.7f, 0.0f };
	cout << "vec 3: " << e;
	cout << "vec 4: " << f;

	Vector4f g = e + f;
	cout << "vec 3 + vec 4: " << g;
	g = e - f;
	cout << "vec 3 - vec 4: " << g;

	Normalize(g);
	cout << "normalized: " << g;
}

void matrix_test()
{
	Matrix4X4f m1;
	BuildIdentityMatrix(m1);

	cout << "Idendity Matrix: ";
	cout << m1;

	float yaw = 0.2f, pitch = 0.3f, roll = 0.4f;
	MatrixRotationYawPitchRoll(m1, yaw, pitch, roll);

	cout << "Matrix of yaw(" << yaw << ") pitch(" << pitch << ") roll(" << roll << "):";
	cout << m1;

	Matrix4X4f ry;
	float angle = PI / 2.0f;
	MatrixRotationY(ry, angle);

	cout << "Matrix of Rotation on Y(angle = " << angle << "):";
	cout << ry;

	Matrix4X4f rz;
	MatrixRotationZ(rz, angle);

	cout << "Matrix of Rotation on Z(angle = " << angle << "):";
	cout << rz;

	float x = 5.0f, y = 6.5f, z = -7.0f;
	Matrix4X4f translate;
	MatrixTranslation(translate, x, y, z);

	cout << "Matrix of Translation on X(" << x << ") Y(" << y << ") Z(" << z << "):";
	cout << translate;

	cout << "Matrix multiplication: Rotation Y * Rotation Z * Translation on X:";
	Matrix4X4f transform = m1 * ry * rz * translate;
	cout << transform;

	Vector3f v = { 1.0f, 0.0f, 0.0f };

	Vector3f v1 = v;
	cout << "Vector : " << v1;
	cout << "Transform by Rotation Y Matrix:";
	cout << ry;
	TransformCoord(v1, ry);
	cout << "Now the vector becomes: " << v1;
	cout << std::endl;

	v1 = v;
	cout << "Vector : " << v1;
	cout << "Transform by Rotation Z Matrix:";
	cout << rz;
	TransformCoord(v1, rz);
	cout << "Now the vector becomes: " << v1;
	cout << std::endl;

	v1 = v;
	cout << "Vector : " << v1;
	cout << "Transform by Translation Matrix:";
	cout << translate;
	TransformCoord(v1, translate);
	cout << "Now the vector becomes: " << v1;
	cout << std::endl;

	Vector3f position = { 0, 0, -5 }, lookAt = { 0, 0, 0 }, up = { 0, 1, 0 };
	Matrix4X4f view;
	BuildViewMatrix(view, position, lookAt, up);
	cout << "View Matrix with position(" << position << ") lookAt(" << lookAt << ") up(" << up << "):";
	cout << view;

	float fov = PI / 2.0f, aspect = 16.0f / 9.0f, near = 1.0f, far = 100.0f;
	Matrix4X4f perspective;
	BuildPerspectiveFovLHMatrix(perspective, fov, aspect, near, far);
	cout << "Perspective Matrix with fov(" << fov << ") aspect(" << aspect << ") near ... far(" << near << " ... " << far << "):";
	cout << perspective;

	Matrix4X4f mvp = view * perspective;
	cout << "MVP:" << mvp;



	Matrix4X4f rtemp = InverseMatrix4X4f(mvp);
	cout << "RTEMP:" << rtemp;

	Matrix4X4f E = mvp * rtemp;
	cout << "E:" << E;

	Matrix4X4f mmm = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

	Matrix4X4f mmf = { {{
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0},
		{0,0,0,0}
		}} };


	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			cout << mmm[i][j] << +"   ";
		}
		cout << endl;
	}

	Matrix8X8f jdata = { { {
		{ -76, -73, -67, -62, -58, -67, -64, -55 },
	{ -65, -69, -73, -38, -19, -43, -59, -56 },
	{ -66, -69, -60, -15,  16, -24, -62, -55 },
	{ -65, -70, -57, -6,  26, -22, -58, -59 },
	{ -61, -67, -60, -24, -2, -40, -60, -58 },
	{ -49, -63, -68, -58, -51, -60, -70, -53 },
	{ -43, -57, -64, -69, -73, -67, -63, -45 },
	{ -41, -49, -59, -60, -63, -52, -50, -34 }
		} } };

	Matrix8X8f dctf;

	dctf = DCT8X8(jdata);

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			cout << dctf[i][j] << +"   ";
		}
		cout << endl;
	}

	Matrix8X8f dctf1 = { { {
		{ -416, -33, -60,  32,  48, -40,   0,   0 },
	{ 0, -24, -56,  19,  26,   0,   0,   0 },
	{ -42,  13,  80, -24, -40,   0,   0,   0 },
	{ -42,  17,  44, -29,   0,   0,   0,   0 },
	{ 18,   0,   0,   0,   0,   0,   0,   0 },
	{ 0,   0,   0,   0,   0,   0,   0,   0 },
	{ 0,   0,   0,   0,   0,   0,   0,   0 },
	{ 0,   0,   0,   0,   0,   0,   0,   0 }
		} } };

	Matrix8X8f jdata1;

	jdata1 = IDCT8X8(dctf1);

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			cout << jdata1[i][j] << +"   ";
		}
		cout << endl;
	}

	unsigned int sada = 2;
	unsigned int a = endian_net_unsigned_int(sada);
	unsigned int b = endian_native_unsigned_int(a);

	int as = 8;
	const int * pas = &as;

	cout << *pas++ << endl;
	cout << *pas++ << endl;
	cin.get();

}

int main()
{
	cout << std::fixed;

	vector_test();
	matrix_test();

	return 0;
}

