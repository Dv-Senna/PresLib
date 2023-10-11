#pragma once



namespace pl
{
	struct Instance;
	struct InstanceImplementation;

	enum class BlockType
	{
		
	};

	struct BlockCreateInfo
	{
		pl::BlockType type;

	};

	struct Block
	{
		pl::BlockType type;
		void (*setup) (
			pl::Block *block,
			pl::InstanceImplementation *instance,
			const pl::BlockCreateInfo &createInfo
		);
		void (*draw) (pl::Block *block, pl::InstanceImplementation *instance);
		void (*cleanup) (pl::Block *block, pl::InstanceImplementation *instance);
	};

} // namespace pl
