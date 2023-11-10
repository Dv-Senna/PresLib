#include <iostream>

#include "graphics/text.hpp"
#include "graphics/vertices.hpp"



namespace pl::graphics
{
	std::vector<pl::utils::Id> generateVerticesFromText(
		pl::Instance &instance,
		const std::string &font,
		int size,
		const std::string &text,
		std::vector<pl::utils::Id> &textures
	)
	{
		textures.clear();
		auto characters {instance.getFont().getCharactersFromString(font, size, text)};
		std::vector<pl::utils::Id> vertices {};
		vertices.reserve(characters.size());
		textures.reserve(characters.size());

		glm::vec2 cursorPosition {0.f, 0.f};

		for (const auto &character : characters)
		{
			pl::graphics::Vertices createInfos {
				{
					cursorPosition.x + character.bearing.x, cursorPosition.y - (character.size.y - character.bearing.y),    0.f, 1.f,
					cursorPosition.x + character.bearing.x + character.size.x, cursorPosition.y + character.bearing.y,    1.f, 0.f,
					cursorPosition.x + character.bearing.x, cursorPosition.y + character.bearing.y,    0.f, 0.f,

					cursorPosition.x + character.bearing.x, cursorPosition.y - (character.size.y - character.bearing.y),    0.f, 1.f,
					cursorPosition.x + character.bearing.x + character.size.x, cursorPosition.y - (character.size.y - character.bearing.y),    1.f, 1.f,
					cursorPosition.x + character.bearing.x + character.size.x, cursorPosition.y + character.bearing.y,    1.f, 0.f,
				},
				{{
					{pl::graphics::VerticesChannel::position, {0, 2}},
					{pl::graphics::VerticesChannel::textureCoord0, {1, 2, 2}}
				}}
			};

			vertices.push_back(instance.getRenderer().registerObject(pl::utils::ObjectType::vertices, createInfos));
			textures.push_back(character.texture);

			cursorPosition.x += character.advance;
		}

		return vertices;
	}



} // namespace pl::graphics
