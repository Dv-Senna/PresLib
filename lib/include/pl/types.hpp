#pragma once

#include <cstdint>

#include <se/malge/malge.hpp>



namespace pl {
	using namespace se::malge;

	using ByteCount = pl::Uint64;
	using Count = pl::Uint64;
	using Byte = pl::Uint8;

	struct Rect2i {
		pl::Int x;
		pl::Int y;
		pl::Int w;
		pl::Int h;
	};

} // namespace pl
