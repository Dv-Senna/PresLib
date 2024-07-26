#include "pl/image.hpp"



namespace pl {
	Image::Image(const std::filesystem::path &path) :
		m_path {path}
	{

	}


	Image::~Image() {

	}


	bool Image::operator==(const pl::Image &image) const noexcept {
		return m_path == image.m_path;
	}


} // namespace pl
