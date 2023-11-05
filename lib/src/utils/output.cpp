#include "utils/output.hpp"



namespace pl::utils
{
	void output(std::ostream &stream, const std::string &name, const glm::mat4 &matrix)
	{
		stream << "-------------------------\n";
		stream << name << " : \n";

		for (size_t i {0}; i < 4; ++i)
		{
			for (size_t j {0}; j < 4; ++j)
			{
				stream << matrix[j][i] << ", ";
			}

			stream << "\n";
		}

		stream << "-------------------------" << std::endl;
	}



} // namespace pl::utils
