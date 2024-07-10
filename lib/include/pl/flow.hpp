#pragma once

#include <functional>
#include <typeinfo>
#include <vector>



namespace pl {
	enum class AnchorStage {
		eInput,
		eOutput
	};

	struct Anchor {
		pl::AnchorStage stage;
		std::type_info type;
	};

	struct ConnectionLayout {
		pl::Anchor input;
		std::vector<pl::Anchor> output;
	};

	template <typename T>
	struct Connection {
		pl::ConnectionLayout layout;
		T value;
	};

	enum class NodeStage {
		eInput,
		eIntermediate,
		eOutput
	};

	struct Node {
		pl::NodeStage stage;
		std::vector<pl::Anchor> inputs;
		std::vector<pl::Anchor> outputs;
	};

	struct Flow {
		std::vector<pl::Node*> nodes;
		std::vector<pl::ConnectionLayout*> connections;
	};

} // namespace pl
