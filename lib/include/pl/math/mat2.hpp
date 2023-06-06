#pragma once

#include <array>
#include <ostream>


namespace pl::math
{
	class Mat2
	{
		public:
			Mat2(float a, float b, float c, float d);
			~Mat2();

			Mat2(const pl::math::Mat2 &matrix);
			const pl::math::Mat2 &operator=(const pl::math::Mat2 &matrix);

			Mat2(pl::math::Mat2 &&matrix) noexcept;
			const pl::math::Mat2 &operator=(pl::math::Mat2 &&matrix) noexcept;


			inline float *data() noexcept {return m_data.data();}
			inline const std::array<float, 4> &get() const noexcept {return m_data;}

			inline float &operator[] (size_t i) {return m_data[i];}

			pl::math::Mat2 &operator+=(const pl::math::Mat2 &matrix);
			pl::math::Mat2 &operator-=(const pl::math::Mat2 &matrix);
			pl::math::Mat2 &operator*=(const pl::math::Mat2 &matrix);
			pl::math::Mat2 &operator*=(float value);

		
		private:
			std::array<float, 4> m_data;
	};



	inline pl::math::Mat2 operator+(pl::math::Mat2 a, const pl::math::Mat2 &b)
	{
		a += b;
		return a;
	}

	inline pl::math::Mat2 operator-(pl::math::Mat2 a, const pl::math::Mat2 &b)
	{
		a -= b;
		return a;
	}

	inline pl::math::Mat2 operator*(pl::math::Mat2 a, const pl::math::Mat2 &b)
	{
		a *= b;
		return a;
	}

	inline pl::math::Mat2 operator*(pl::math::Mat2 a, float value)
	{
		a *= value;
		return a;
	}

	inline pl::math::Mat2 operator*(float value, pl::math::Mat2 a)
	{
		a *= value;
		return a;
	}


	inline std::ostream &operator<<(std::ostream &stream, const pl::math::Mat2 &matrix)
	{
		stream << "[(" << matrix.get()[0] << ", " << matrix.get()[1] << "), ("
			<< matrix.get()[2] << ", " << matrix.get()[3] << ")]";
		return stream;
	}



	float det(const pl::math::Mat2 &matrix);
	pl::math::Mat2 inverse(const pl::math::Mat2 &matrix);



} // namespace pl::math
