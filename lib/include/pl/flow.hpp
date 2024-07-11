#pragma once

#include <functional>
#include <typeinfo>
#include <vector>

#include "pl/core.hpp"



namespace pl {
	enum class AnchorStage {
		eInput,
		eOutput
	};

	struct Anchor final {
		pl::AnchorStage stage;
		std::type_info type;
	};

	struct ConnectionLayout final {
		pl::Anchor input;
		std::vector<pl::Anchor> output;
	};

	template <typename T>
	struct Connection final {
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

	struct Flow final {
		std::vector<pl::Node*> nodes;
		std::vector<pl::ConnectionLayout*> connections;
	};

	struct OrganisedFlow final {
		std::vector<pl::Node*> inputs;
		std::vector<pl::Node*> outputs;
		std::vector<pl::Node*> intermediates;
	};

	PL_CORE bool isFlowValid(const pl::Flow &flow);

} // namespace pl
