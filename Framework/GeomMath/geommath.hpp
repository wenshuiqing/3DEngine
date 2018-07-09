#pragma once
#include <cstdint>
#include <iostream>
#include <limits>
#include <math.h>
#ifndef PI
#define PI 3.14159265358979323846f
#endif

#ifndef TWO_PI
#define TWO_PI 3.14159265358979323846f * 2.0f
#endif

namespace My {
	template<typename T, size_t SizeOfArray>
	constexpr size_t countof(T(&)[SizeOfArray]) { return SizeOfArray; }

	template<typename T, size_t RowSize, size_t ColSize>
	constexpr size_t countof(T(&)[RowSize][ColSize]) { return RowSize * ColSize; }

	template<typename T>
	constexpr float normalize(T value) {
		return value < 0
			? -static_cast<float>(value) / std::numeric_limits<T>::min()
			: static_cast<float>(value) / std::numeric_limits<T>::max()
			;
	}

	template <template<typename> class TT, typename T, int ... Indexes>
	class swizzle {
		T v[sizeof...(Indexes)];

	public:

		TT<T>& operator=(const TT<T>& rhs)
		{
			int indexes[] = { Indexes... };
			for (int i = 0; i < sizeof...(Indexes); i++) {
				v[indexes[i]] = rhs[i];
			}
			return *(TT<T>*)this;
		}

		operator TT<T>() const
		{
			return TT<T>(v[Indexes]...);
		}

	};

	template <typename T>
	struct Vector2Type
	{
		union {
			T data[2] = { 0 };
			struct { T x, y; };
			struct { T r, g; };
			struct { T u, v; };
			swizzle<My::Vector2Type, T, 0, 1> xy;
			swizzle<My::Vector2Type, T, 1, 0> yx;
		};

		Vector2Type<T>() {};
		Vector2Type<T>(const T& _v) : x(_v), y(_v) {};
		Vector2Type<T>(const T& _x, const T& _y) : x(_x), y(_y) {};

		operator T*() { return data; };
		operator const T*() const { return static_cast<const T*>(data); };
	};

	typedef Vector2Type<float> Vector2f;

	template <typename T>
	struct Vector3Type
	{
		union {
			T data[3] = { 0 };
			struct { T x, y, z; };
			struct { T r, g, b; };
			swizzle<My::Vector2Type, T, 0, 1> xy;
			swizzle<My::Vector2Type, T, 1, 0> yx;
			swizzle<My::Vector2Type, T, 0, 2> xz;
			swizzle<My::Vector2Type, T, 2, 0> zx;
			swizzle<My::Vector2Type, T, 1, 2> yz;
			swizzle<My::Vector2Type, T, 2, 1> zy;
			swizzle<My::Vector3Type, T, 0, 1, 2> xyz;
			swizzle<My::Vector3Type, T, 1, 0, 2> yxz;
			swizzle<My::Vector3Type, T, 0, 2, 1> xzy;
			swizzle<My::Vector3Type, T, 2, 0, 1> zxy;
			swizzle<My::Vector3Type, T, 1, 2, 0> yzx;
			swizzle<My::Vector3Type, T, 2, 1, 0> zyx;
		};

		Vector3Type<T>() {};
		Vector3Type<T>(const T& _v) : x(_v), y(_v), z(_v) {};
		Vector3Type<T>(const T& _x, const T& _y, const T& _z) : x(_x), y(_y), z(_z) {};

		operator T*() { return data; };
		operator const T*() const { return static_cast<const T*>(data); };
	};

	typedef Vector3Type<float> Vector3f;

	template <typename T>
	struct Vector4Type
	{
		union {
			T data[4] = { 0 };
			struct { T x, y, z, w; };
			struct { T r, g, b, a; };
			swizzle<My::Vector3Type, T, 0, 1, 2> xyz;
			swizzle<My::Vector3Type, T, 0, 2, 1> xzy;
			swizzle<My::Vector3Type, T, 1, 0, 2> yxz;
			swizzle<My::Vector3Type, T, 1, 2, 0> yzx;
			swizzle<My::Vector3Type, T, 2, 0, 1> zxy;
			swizzle<My::Vector3Type, T, 2, 1, 0> zyx;
			swizzle<My::Vector4Type, T, 2, 1, 0, 3> bgra;
		};

		Vector4Type<T>() {};
		Vector4Type<T>(const T& _v) : x(_v), y(_v), z(_v), w(_v) {};
		Vector4Type<T>(const T& _x, const T& _y, const T& _z, const T& _w) : x(_x), y(_y), z(_z), w(_w) {};
		Vector4Type<T>(const Vector3Type<T>& v3) : x(v3.x), y(v3.y), z(v3.z), w(1.0f) {};
		Vector4Type<T>(const Vector3Type<T>& v3, const T& _w) : x(v3.x), y(v3.y), z(v3.z), w(_w) {};

		operator T*() { return data; };
		operator const T*() const { return static_cast<const T*>(data); };
		Vector4Type& operator=(const T* f)
		{
			for (int32_t i = 0; i < 4; i++)
			{
				data[i] = *(f + i);
			}
			return *this;
		};
	};

	typedef Vector4Type<float> Vector4f;
	typedef Vector4Type<float> Quaternion;
	typedef Vector4Type<uint8_t> R8G8B8A8Unorm;
	typedef Vector4Type<uint8_t> Vector4i;

	template <template <typename> class TT, typename T>
	std::ostream& operator<<(std::ostream& out, TT<T> vector)
	{
		out << "( ";
		for (uint32_t i = 0; i < countof(vector.data); i++) {
			out << vector.data[i] << ((i == countof(vector.data) - 1) ? ' ' : ',');
		}
		out << ")\n";

		return out;
	}

	template <template<typename> class TT, typename T>
	void VectorAdd(TT<T>& result, const TT<T>& vec1, const TT<T>& vec2)
	{
		size_t length = countof(result.data);
		for (size_t i = 0; i < length; i++)
		{
			result[i] = vec1[i] + vec2[i];
		}
	}

	template <template<typename> class TT, typename T>
	TT<T> operator+(const TT<T>& vec1, const TT<T>& vec2)
	{
		TT<T> result;
		VectorAdd(result, vec1, vec2);

		return result;
	}

	template <template<typename> class TT, typename T>
	void VectorSub(TT<T>& result, const TT<T>& vec1, const TT<T>& vec2)
	{
		size_t length = countof(result.data);
		for (size_t i = 0; i < length; i++)
		{
			result[i] = vec1[i] - vec2[i];
		}
	}

	template <template<typename> class TT, typename T>
	TT<T> operator-(const TT<T>& vec1, const TT<T>& vec2)
	{
		TT<T> result;
		VectorSub(result, vec1, vec2);

		return result;
	}


	template <template<typename> class TT, typename T>
	TT<T> operator/(const TT<T>& vec1, const T& scale)
	{
		TT<T> result;
		size_t length = countof(result.data);
		for (size_t i = 0; i < length; i++)
		{
			result[i] = vec1[i] / scale;
		}

		return result;
	}

	template <template <typename> class TT, typename T>
	inline void CrossProduct(TT<T>& result, const TT<T>& a, const TT<T>& b)
	{
		for (size_t index = 0; index < 3; index++) {
			int index_a = ((index + 1 == 3) ? 0 : index + 1);
			int index_b = ((index == 0) ? 2 : index - 1);
			result[index] = a[index_a] * b[index_b]
				- a[index_b] * b[index_a];
		}
	}

	template <template <typename> class TT, typename T>
	inline T DotProduct(const TT<T>& vec1, const TT<T>& vec2)
	{
		T result = 0;
		size_t length = countof(vec1.data);
		for (size_t i = 0; i < length; i++)
		{
			result += vec1[i] * vec2[i];
		}
		return result;
	}

	template <typename T>
	inline void MulByElement(T& result, const T& a, const T& b)
	{
		for (size_t index = 0; index < 3; index++) {
			result[index] = a[index] * b[index];
		}
	}



	
	// Matrix

	template <typename T, int ROWS, int COLS>
	struct Matrix
	{
		union {
			T data[ROWS][COLS] = { 0 };
		};

		T* operator[](int row_index) {
			return data[row_index];
		}

		const T* operator[](int row_index) const {
			return data[row_index];
		}
		operator T*() { return &data[0][0]; };
		operator const T*() const { return static_cast<const T*>(&data[0][0]); };

		Matrix& operator=(const T* _data)
		{
			for (int i = 0; i < ROWS; i++) {
				for (int j = 0; j < COLS; j++) {
					data[i][j] = *(_data + i * COLS + j);
				}
			}
			return *this;
		}
	};

	typedef Matrix<float, 4, 4> Matrix4X4f;
	typedef Matrix<float, 3, 3> Matrix3X3f;

	template <typename T, int ROWS, int COLS>
	std::ostream& operator<<(std::ostream& out, Matrix<T, ROWS, COLS> matrix)
	{
		out << std::endl;
		for (int i = 0; i < ROWS; i++) {
			for (int j = 0; j < COLS; j++) {
				out << matrix.data[i][j] << ((j == COLS - 1) ? '\n' : ',');
			}
		}
		out << std::endl;

		return out;
	}

	template <typename T, int ROWS, int COLS>
	void MatrixAdd(Matrix<T, ROWS, COLS>& result, const Matrix<T, ROWS, COLS>& matrix1, const Matrix<T, ROWS, COLS>& matrix2)
	{
		for (size_t i = 0; i < ROWS; i++)
		{
			for (size_t j = 0; j < COLS; j++)
			{
				result[i][j] = matrix1[i][j] + matrix2[i][j];
			}
		}

	}

	template <typename T, int ROWS, int COLS>
	Matrix<T, ROWS, COLS> operator+(const Matrix<T, ROWS, COLS>& matrix1, const Matrix<T, ROWS, COLS>& matrix2)
	{
		Matrix<T, ROWS, COLS> result;
		MatrixAdd(result, matrix1, matrix2);

		return result;
	}

	template <typename T, int ROWS, int COLS>
	void MatrixSub(Matrix<T, ROWS, COLS>& result, const Matrix<T, ROWS, COLS>& matrix1, const Matrix<T, ROWS, COLS>& matrix2)
	{
		for (size_t i = 0; i < ROWS; i++)
		{
			for (size_t j = 0; j < COLS; j++)
			{
				result[i][j] = matrix1[i][j] + matrix2[i][j];
			}
		}
	}

	template <typename T, int ROWS, int COLS>
	Matrix<T, ROWS, COLS> operator-(const Matrix<T, ROWS, COLS>& matrix1, const Matrix<T, ROWS, COLS>& matrix2)
	{
		Matrix<T, ROWS, COLS> result;
		MatrixSub(result, matrix1, matrix2);

		return result;
	}
	template <typename T, int ROWS, int COLS>
	void MatrixMulByElement(Matrix<T, ROWS, COLS>& result, const Matrix<T, ROWS, COLS>& matrix1, const Matrix<T, ROWS, COLS>& matrix2)
	{
		for (size_t i = 0; i < ROWS; i++)
		{
			for (size_t j = 0; j < COLS; j++)
			{
				result[i][j] = matrix1[i][j] * matrix2[i][j];
			}
		}
	}

	template <int ROWS, int COLS>
	void MatrixMulByElementi32(Matrix<int32_t, ROWS, COLS>& result, const Matrix<int32_t, ROWS, COLS>& matrix1, const Matrix<int32_t, ROWS, COLS>& matrix2)
	{
		MatrixMulByElement(matrix1, matrix2, result, countof(result.data));
	}

	template <typename T, int Da, int Db, int Dc>
	void MatrixMultiply(Matrix<T, Da, Dc>& result, const Matrix<T, Da, Db>& matrix1, const Matrix<T, Db, Dc>& matrix2)
	{
		Matrix<T, Da, Dc> temp;
		Matrix<T, Dc, Db> matrix2_transpose;
		Transpose(matrix2_transpose, matrix2);
		for (int i = 0; i < Da; i++) {
			for (int j = 0; j < Dc; j++) {
				for (int k = 0; k < Db; k++)
				{
					temp[i][j] += (*(matrix1[i] + k)) * (*(matrix2_transpose[j] + k));
				}
			}
		}
		result = temp;
	}

	template <typename T, int ROWS, int COLS>
	Matrix<T, ROWS, COLS> operator*(const Matrix<T, ROWS, COLS>& matrix1, const Matrix<T, ROWS, COLS>& matrix2)
	{
		Matrix<T, ROWS, COLS> result;
		MatrixMultiply(result, matrix1, matrix2);

		return result;
	}

	template <typename T, int ROWS, int COLS>
	Matrix<T, ROWS, COLS> operator*(const float scale, const Matrix<T, ROWS, COLS>& matrix)
	{
		Matrix<T, ROWS, COLS> result;

		for (size_t i = 0; i < ROWS; i++)
		{
			for (size_t j = 0; j < COLS; j++)
			{
				result[i][j] = matrix[i][j] * scale;
			}
		}
		return result;
	}

	template <typename T, int ROWS, int COLS>
	Matrix<T, ROWS, COLS> operator*(const Matrix<T, ROWS, COLS>& matrix, const float scale)
	{
		Matrix<T, ROWS, COLS> result;

		for (size_t i = 0; i < ROWS; i++)
		{
			for (size_t j = 0; j < COLS; j++)
			{
				result[i][j] = matrix[i][j] * scale;
			}
		}
		return result;
	}

	template <typename T, int ROWS, int COLS>
	Matrix<T, ROWS, COLS> operator/(const Matrix<T, ROWS, COLS>& matrix, const float scale)
	{
		Matrix<T, ROWS, COLS> result;

		for (size_t i = 0; i < ROWS; i++)
		{
			for (size_t j = 0; j < COLS; j++)
			{
				result[i][j] = matrix[i][j] / scale;
			}
		}
		return result;
	}

	template <template <typename, int, int> class TT, typename T, int ROWS, int COLS>
	inline void Transpose(TT<T, ROWS, COLS>& result, const TT<T, ROWS, COLS>& matrix1)
	{
		int i, j;
		for (i = 0; i < ROWS; i++)
			for (j = 0; j < COLS; j++)
				result[j][i] = matrix1[i][j];//转置运算。
	}

	template <typename T>
	inline T Normalize(T& value)
	{
		T result;
		float length = sqrt(DotProduct(value, value));
		result = value / length;
		return result;
	}


	template <typename T>
	inline void Normalized(T& result)
	{
		float length = sqrt(DotProduct(result, result));
		result = result / length;
	}




	inline void MatrixRotationYawPitchRoll(Matrix4X4f& matrix, const float yaw, const float pitch, const float roll)
	{
		float cYaw, cPitch, cRoll, sYaw, sPitch, sRoll;


		// Get the cosine and sin of the yaw, pitch, and roll.
		cYaw = cosf(yaw);
		cPitch = cosf(pitch);
		cRoll = cosf(roll);

		sYaw = sinf(yaw);
		sPitch = sinf(pitch);
		sRoll = sinf(roll);

		// Calculate the yaw, pitch, roll rotation matrix.
		Matrix4X4f tmp = { { {
			{ (cRoll * cYaw) + (sRoll * sPitch * sYaw), (sRoll * cPitch), (cRoll * -sYaw) + (sRoll * sPitch * cYaw), 0.0f },
		{ (-sRoll * cYaw) + (cRoll * sPitch * sYaw), (cRoll * cPitch), (sRoll * sYaw) + (cRoll * sPitch * cYaw), 0.0f },
		{ (cPitch * sYaw), -sPitch, (cPitch * cYaw), 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
			} } };

		matrix = tmp;

		return;
	}

	inline void TransformCoord(Vector3f& vector, const Matrix4X4f& matrix)
	{
		Vector3f result;
		result.x = vector.x * (*(matrix[0] + 0)) + vector.y * (*(matrix[1] + 0)) + vector.z * (*(matrix[2] + 0));
		result.y = vector.x * (*(matrix[0] + 1)) + vector.y * (*(matrix[1] + 1)) + vector.z * (*(matrix[2] + 1));
		result.z = vector.x * (*(matrix[0] + 2)) + vector.y * (*(matrix[1] + 2)) + vector.z * (*(matrix[2] + 2));

		vector = result;
	}

	inline void Transform(Vector4f& vector, const Matrix4X4f& matrix)
	{
		Vector4f result;
		result.x = vector.x * (*(matrix[0] + 0)) + vector.y * (*(matrix[1] + 0)) + vector.z * (*(matrix[2] + 0)) + vector.w * (*(matrix[3] + 0));
		result.y = vector.x * (*(matrix[0] + 1)) + vector.y * (*(matrix[1] + 1)) + vector.z * (*(matrix[2] + 1)) + vector.w * (*(matrix[3] + 1));
		result.z = vector.x * (*(matrix[0] + 2)) + vector.y * (*(matrix[1] + 2)) + vector.z * (*(matrix[2] + 2)) + vector.w * (*(matrix[3] + 2));
		result.w = vector.x * (*(matrix[0] + 3)) + vector.y * (*(matrix[1] + 3)) + vector.z * (*(matrix[2] + 3)) + vector.w * (*(matrix[3] + 3));
		vector = result;
	}

	inline void BuildViewMatrix(Matrix4X4f& result, const Vector3f position, const Vector3f lookAt, const Vector3f up)
	{
		Vector3f zAxis, xAxis, yAxis;
		float result1 = 0, result2 = 0, result3 = 0;

		zAxis = lookAt - position;
		Normalize(zAxis);

		CrossProduct(xAxis, up, zAxis);
		Normalize(xAxis);

		CrossProduct(yAxis, zAxis, xAxis);

		result1 = DotProduct(xAxis, position);
		result1 = -result1;

		result2 = DotProduct(yAxis, position);
		result2 = -result2;

		result3 = DotProduct(zAxis, position);
		result3 = -result3;

		// Set the computed values in the view matrix.
		Matrix4X4f tmp = { { {
			{ xAxis.x, yAxis.x, zAxis.x, 0.0f },
		{ xAxis.y, yAxis.y, zAxis.y, 0.0f },
		{ xAxis.z, yAxis.z, zAxis.z, 0.0f },
		{ result1, result2, result3, 1.0f }
			} } };

		result = tmp;
	}

	inline void BuildIdentityMatrix(Matrix4X4f& matrix)
	{
		Matrix4X4f identity = { { {
			{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
			} } };

		matrix = identity;

		return;
	}


	inline void BuildPerspectiveFovLHMatrix(Matrix4X4f& matrix, const float fieldOfView, const float screenAspect, const float screenNear, const float screenDepth)
	{
		Matrix4X4f perspective = { { {
			{ 1.0f / (screenAspect * tanf(fieldOfView * 0.5f)), 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f / tanf(fieldOfView * 0.5f), 0.0f, 0.0f },
		{ 0.0f, 0.0f, screenDepth / (screenDepth - screenNear), 1.0f },
		{ 0.0f, 0.0f, (-screenNear * screenDepth) / (screenDepth - screenNear), 0.0f }
			} } };

		matrix = perspective;

		return;
	}
	inline void BuildPerspectiveFovRHMatrix(Matrix4X4f& matrix, const float fieldOfView, const float screenAspect, const float screenNear, const float screenDepth)
	{
		Matrix4X4f perspective = { { {
			{ 1.0f / (screenAspect * tanf(fieldOfView * 0.5f)), 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f / tanf(fieldOfView * 0.5f), 0.0f, 0.0f },
		{ 0.0f, 0.0f, screenDepth / (screenNear - screenDepth), -1.0f },
		{ 0.0f, 0.0f, (-screenNear * screenDepth) / (screenDepth - screenNear), 0.0f }
			} } };

		matrix = perspective;

		return;
	}

	inline void MatrixTranslation(Matrix4X4f& matrix, const float x, const float y, const float z)
	{
		Matrix4X4f translation = { { {
			{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ x,    y,    z, 1.0f }
			} } };

		matrix = translation;

		return;
	}

	inline void MatrixRotationX(Matrix4X4f& matrix, const float angle)
	{
		float c = cosf(angle), s = sinf(angle);

		Matrix4X4f rotation = { { {
			{ 1.0f, 0.0f, 0.0f, 0.0f },
		{ 0.0f,    c,    s, 0.0f },
		{ 0.0f,   -s,    c, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
			} } };

		matrix = rotation;

		return;
	}

	inline void MatrixScale(Matrix4X4f& matrix, const float x, const float y, const float z)
	{
		Matrix4X4f scale = { { {
			{ x, 0.0f, 0.0f, 0.0f },
		{ 0.0f,    y, 0.0f, 0.0f },
		{ 0.0f, 0.0f,    z, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
			} } };

		matrix = scale;

		return;
	}

	inline void MatrixRotationY(Matrix4X4f& matrix, const float angle)
	{
		float c = cosf(angle), s = sinf(angle);

		Matrix4X4f rotation = { { {
			{ c, 0.0f,   -s, 0.0f },
		{ 0.0f, 1.0f, 0.0f, 0.0f },
		{ s, 0.0f,    c, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f },
			} } };

		matrix = rotation;

		return;
	}


	inline void MatrixRotationZ(Matrix4X4f& matrix, const float angle)
	{
		float c = cosf(angle), s = sinf(angle);

		Matrix4X4f rotation = { { {
			{ c,    s, 0.0f, 0.0f },
		{ -s,    c, 0.0f, 0.0f },
		{ 0.0f, 0.0f, 1.0f, 0.0f },
		{ 0.0f, 0.0f, 0.0f, 1.0f }
			} } };

		matrix = rotation;

		return;
	}

	inline void MatrixRotationAxis(Matrix4X4f& matrix, const Vector3f& axis, const float angle)
	{
		float c = cosf(angle), s = sinf(angle), one_minus_c = 1.0f - c;

		Matrix4X4f rotation = { { {
			{ c + axis.x * axis.x * one_minus_c,  axis.x * axis.y * one_minus_c + axis.z * s, axis.x * axis.z * one_minus_c - axis.y * s, 0.0f },
		{ axis.x * axis.y * one_minus_c - axis.z * s, c + axis.y * axis.y * one_minus_c,  axis.y * axis.z * one_minus_c + axis.x * s, 0.0f },
		{ axis.x * axis.z * one_minus_c + axis.y * s, axis.y * axis.z * one_minus_c - axis.x * s, c + axis.z * axis.z * one_minus_c, 0.0f },
		{ 0.0f,  0.0f,  0.0f,  1.0f }
			} } };

		matrix = rotation;
	}

	inline void MatrixRotationQuaternion(Matrix4X4f& matrix, Quaternion q)
	{
		Matrix4X4f rotation = { { {
			{ 1.0f - 2.0f * q.y * q.y - 2.0f * q.z * q.z,  2.0f * q.x * q.y + 2.0f * q.w * q.z,   2.0f * q.x * q.z - 2.0f * q.w * q.y,    0.0f },
		{ 2.0f * q.x * q.y - 2.0f * q.w * q.z,    1.0f - 2.0f * q.x * q.x - 2.0f * q.z * q.z, 2.0f * q.y * q.z + 2.0f * q.w * q.x,    0.0f },
		{ 2.0f * q.x * q.z + 2.0f * q.w * q.y,    2.0f * q.y * q.z - 2.0f * q.y * q.z - 2.0f * q.w * q.x, 1.0f - 2.0f * q.x * q.x - 2.0f * q.y * q.y, 0.0f },
		{ 0.0f,   0.0f,   0.0f,   1.0f }
			} } };

		matrix = rotation;
	}


	// 00 01 02
	// 10 11 12
	// 20 21 22
	inline Matrix3X3f InverseMatrix3X3f(Matrix3X3f& matrix) {

		Matrix3X3f result;

		float det = (matrix[0][0] * matrix[1][1] * matrix[2][2] +
			matrix[0][1] * matrix[1][2] * matrix[2][0] +
			matrix[0][2] * matrix[1][0] * matrix[2][1]) -
			(matrix[0][2] * matrix[1][1] * matrix[2][0] +
				matrix[0][1] * matrix[1][0] * matrix[2][2] +
				matrix[0][0] * matrix[1][2] * matrix[2][1]);
		det = 1 / det;


		result[0][0] = det * pow(-1, 2)*(matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1]);
		result[0][1] = det * pow(-1, 3)*(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
		result[0][2] = det * pow(-1, 4)*(matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2]);

		result[1][0] = det * pow(-1, 3)*(matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2]);
		result[1][1] = det * pow(-1, 4)*(matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0]);
		result[1][2] = det * pow(-1, 5)*(matrix[0][0] * matrix[1][2] - matrix[1][0] * matrix[0][2]);

		result[2][0] = det * pow(-1, 4)*(matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1]);
		result[2][1] = det * pow(-1, 5)*(matrix[0][0] * matrix[2][1] - matrix[2][0] * matrix[0][1]);
		result[2][2] = det * pow(-1, 6)*(matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]);


		return result;
	}



	inline Matrix4X4f InverseMatrix4X4f(Matrix4X4f& matrix) {
		Matrix4X4f result = matrix;

		float A2323 = matrix[2][2] * matrix[3][3] - matrix[2][3] * matrix[3][2];
		float A1323 = matrix[2][1] * matrix[3][3] - matrix[2][3] * matrix[3][1];
		float A1223 = matrix[2][1] * matrix[3][2] - matrix[2][2] * matrix[3][1];
		float A0323 = matrix[2][0] * matrix[3][3] - matrix[2][3] * matrix[3][0];
		float A0223 = matrix[2][0] * matrix[3][2] - matrix[2][2] * matrix[3][0];
		float A0123 = matrix[2][0] * matrix[3][1] - matrix[2][1] * matrix[3][0];
		float A2313 = matrix[1][2] * matrix[3][3] - matrix[1][3] * matrix[3][2];
		float A1313 = matrix[1][1] * matrix[3][3] - matrix[1][3] * matrix[3][1];
		float A1213 = matrix[1][1] * matrix[3][2] - matrix[1][2] * matrix[3][1];
		float A2312 = matrix[1][2] * matrix[2][3] - matrix[1][3] * matrix[2][2];
		float A1312 = matrix[1][1] * matrix[2][3] - matrix[1][3] * matrix[2][1];
		float A1212 = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
		float A0313 = matrix[1][0] * matrix[3][3] - matrix[1][3] * matrix[3][0];
		float A0213 = matrix[1][0] * matrix[3][2] - matrix[1][2] * matrix[3][0];
		float A0312 = matrix[1][0] * matrix[2][3] - matrix[1][3] * matrix[2][0];
		float A0212 = matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0];
		float A0113 = matrix[1][0] * matrix[3][1] - matrix[1][1] * matrix[3][0];
		float A0112 = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];

		//计算行列式的值
		float det = matrix[0][0] * (matrix[1][1] * A2323 - matrix[1][2] * A1323 + matrix[1][3] * A1223)
			- matrix[0][1] * (matrix[1][0] * A2323 - matrix[1][2] * A0323 + matrix[1][3] * A0223)
			+ matrix[0][2] * (matrix[1][0] * A1323 - matrix[1][1] * A0323 + matrix[1][3] * A0123)
			- matrix[0][3] * (matrix[1][0] * A1223 - matrix[1][1] * A0223 + matrix[1][2] * A0123);
		det = 1 / det;




		//Aij = ((-1)^(i+j)*Mij)T   
		result[0][0] = det * (matrix[1][1] * A2323 - matrix[1][2] * A1323 + matrix[1][3] * A1223);
		result[0][1] = det * -(matrix[0][1] * A2323 - matrix[0][2] * A1323 + matrix[0][3] * A1223);
		result[0][2] = det * (matrix[0][1] * A2313 - matrix[0][2] * A1313 + matrix[0][3] * A1213);
		result[0][3] = det * -(matrix[0][1] * A2312 - matrix[0][2] * A1312 + matrix[0][3] * A1212);
		result[1][0] = det * -(matrix[1][0] * A2323 - matrix[1][2] * A0323 + matrix[1][3] * A0223);
		result[1][1] = det * (matrix[0][0] * A2323 - matrix[0][2] * A0323 + matrix[0][3] * A0223);
		result[1][2] = det * -(matrix[0][0] * A2313 - matrix[0][2] * A0313 + matrix[0][3] * A0213);
		result[1][3] = det * (matrix[0][0] * A2312 - matrix[0][2] * A0312 + matrix[0][3] * A0212);
		result[2][0] = det * (matrix[1][0] * A1323 - matrix[1][1] * A0323 + matrix[1][3] * A0123);
		result[2][1] = det * -(matrix[0][0] * A1323 - matrix[0][1] * A0323 + matrix[0][3] * A0123);
		result[2][2] = det * (matrix[0][0] * A1313 - matrix[0][1] * A0313 + matrix[0][3] * A0113);
		result[2][3] = det * -(matrix[0][0] * A1312 - matrix[0][1] * A0312 + matrix[0][3] * A0112);
		result[3][0] = det * -(matrix[1][0] * A1223 - matrix[1][1] * A0223 + matrix[1][2] * A0123);
		result[3][1] = det * (matrix[0][0] * A1223 - matrix[0][1] * A0223 + matrix[0][2] * A0123);
		result[3][2] = det * -(matrix[0][0] * A1213 - matrix[0][1] * A0213 + matrix[0][2] * A0113);
		result[3][3] = det * (matrix[0][0] * A1212 - matrix[0][1] * A0212 + matrix[0][2] * A0112);

		return result;
	}


	typedef Matrix<float, 8, 8> Matrix8X8f;


	inline Matrix8X8f DCT8X8( Matrix8X8f indata) {
		float one_over_four = 1.0f / 4.0f;
		float PI_over_sixteen = PI / 16.0f;
		float one_over_sqrt2 = 1.0f / sqrt(2.0f);
		int length = 8;

		Matrix8X8f result;
		for (size_t u = 0; u < length; u++)
		{
			float ufactor = (u == 0) ? one_over_sqrt2 : 1.0f;
			for (size_t v = 0; v < length; v++)
			{
				float vfactor = (v == 0) ? one_over_sqrt2 : 1.0f;;

				float temp = 0;
				for (size_t x = 0; x < length; x++)
				{
					for (size_t y = 0; y < length; y++)
					{
						temp += indata[x][y] * cos((2 * x + 1)*u*PI_over_sixteen)*cos((2 * y + 1)*v*PI_over_sixteen);
					}
				}
				result[u][v] = one_over_four * ufactor*vfactor*temp;
			}
		}

		return result;
	}


	inline Matrix8X8f IDCT8X8( Matrix8X8f factor) {
		float one_over_four = 1.0f / 4.0f;
		float PI_over_sixteen = PI / 16.0f;
		float one_over_sqrt2 = 1.0f / sqrt(2.0f);
		int length = 8;
		Matrix8X8f result;
		for (size_t x = 0; x < length; x++)
		{
			for (size_t y = 0; y < length; y++)
			{
				float temp = 0;
				for (size_t u = 0; u < length; u++)
				{
					float ufactor = (u == 0) ? one_over_sqrt2 : 1.0f;
					for (size_t v = 0; v < length; v++)
					{
						float vfactor = (v == 0) ? one_over_sqrt2 : 1.0f;;
						temp += ufactor * vfactor* factor[u][v] * cos((2 * x + 1)*u*PI_over_sixteen)*cos((2 * y + 1)*v*PI_over_sixteen);
					}
				}
				result[x][y] = round(one_over_four * temp);
			}
		}
		 
		return result;
	}




}


