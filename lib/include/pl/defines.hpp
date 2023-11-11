#pragma once



namespace pl::defines
{
	struct Version
	{
		int major;
		int minor;
		int patch;
	};

	constexpr pl::defines::Version version {0, 6, 0};
} // namespace pl::defines
