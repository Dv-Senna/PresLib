#include "pl/slide.hpp"



namespace pl {
	Slide::Slide() :
		m_blocks {}
	{

	}


	Slide::~Slide() {

	}


	void Slide::draw() {

	}


	void Slide::registerBlock(pl::Block *block) {
		m_blocks.push_back(block);
	}


} // namespace pl
