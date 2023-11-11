#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>

#include <glm/ext/matrix_transform.hpp>

#include "blocks/math.hpp"
#include "instance.hpp"
#include "graphics/vertices.hpp"
#include "graphics/shader.hpp"
#include "graphics/pipeline.hpp"
#include "utils/loadImage.hpp"
#include "utils/output.hpp"



namespace pl::blocks
{
	pl::utils::Id Math::s_vertices {0}, Math::s_shaders[2] {0, 0}, Math::s_pipeline {0};



	Math::Math(pl::Instance &instance, const pl::blocks::Math::CreateInfo &createInfo) : 
		pl::Block(instance),
		pl::BlockWithPosition(createInfo.position),
		pl::BlockWithSize({0.f, 0.f}),
		pl::BlockWithOrientation(createInfo.angle, createInfo.rotationCenter),
		pl::BlockWithColor(createInfo.color),
		pl::BlockWithDistortion(createInfo.distortion),
		m_texture {0}
	{
		static std::hash<std::string> hasher {};

		pl::blocks::Math::s_load(m_instance);


		if (!std::filesystem::is_directory(pl::config::texFolder) || !std::filesystem::exists(pl::config::texFolder))
			std::filesystem::create_directory(pl::config::texFolder);
			
		size_t hashInt = hasher(createInfo.equation);
		std::ostringstream stream {};
		stream << std::hex << hashInt;

		if (!std::filesystem::exists(pl::config::texFolder + stream.str() + ".png"))
		{
			pl::blocks::Math::s_generatePdf(createInfo.equation, createInfo.fontSize, stream.str());
			pl::blocks::Math::s_convertToImage(stream.str());
		}

		m_texture = pl::utils::loadImage(m_instance, pl::config::texFolder + stream.str() + ".png", m_size);

		if (m_color == pl::utils::undefined)
			m_color = m_instance.getStyle().colors.text;
	}



	Math::~Math()
	{

	}



	void Math::draw(const glm::mat4 &globalTransformation)
	{
		glm::vec3 rotationCenter {m_rotationCenter.x * m_size.x, m_rotationCenter.y * m_size.y, 0.f};
		glm::mat4 transformation {1.f};
		transformation = glm::translate(transformation, {m_position.x, m_position.y, 0.f});
		transformation = glm::translate(transformation, rotationCenter);
		transformation = glm::rotate(transformation, static_cast<float> (m_angle), {0.f, 0.f, 1.f});
		transformation = glm::translate(transformation, -rotationCenter);
		transformation = glm::scale(transformation, {m_size.x, m_size.y, 1.f});

		m_instance.getRenderer().usePipeline(s_pipeline);
			m_instance.getRenderer().setUniformValues(s_pipeline, "texture", {
				{"transformation", glm::mat4(globalTransformation * transformation * m_distortion)},
				{"color", static_cast<glm::vec4> (m_color)}
			});
			m_instance.getRenderer().bindTexture(s_pipeline, m_texture, 0);
				m_instance.getRenderer().drawVertices(s_vertices);
			m_instance.getRenderer().bindTexture(s_pipeline, 0, 0);
		m_instance.getRenderer().usePipeline(0);
	}



	void Math::s_load(pl::Instance &instance)
	{
		static bool loaded {false};
		if (loaded)
			return;

		loaded = true;

		pl::graphics::Vertices vertices {
			{
				0.f, 0.f,    1.f, 1.f,    0.f, 1.f,
				0.f, 0.f,    1.f, 0.f,    1.f, 1.f
			},
			{
				{
					{pl::graphics::VerticesChannel::color, {0, 2, 0}}
				},
				pl::graphics::VerticesUsage::staticDraw
			}
		};
		s_vertices = instance.getRenderer().registerObject(pl::utils::ObjectType::vertices, vertices);

		pl::graphics::Shader vertexShader {
			pl::graphics::ShaderType::vertex,
			"shaders/texture.vert.spv",
			"main"
		};
		s_shaders[0] = instance.getRenderer().registerObject(pl::utils::ObjectType::shader, vertexShader);
		pl::graphics::Shader fragmentShader {
			pl::graphics::ShaderType::fragment,
			"shaders/texture.frag.spv",
			"main"
		};
		s_shaders[1] = instance.getRenderer().registerObject(pl::utils::ObjectType::shader, fragmentShader);

		pl::graphics::Pipeline pipeline {
			{s_shaders[0], s_shaders[1]},
			{{
				{
					{pl::graphics::UniformFieldType::mat4, "transformation"},
					{pl::graphics::UniformFieldType::vec4, "color"}
				},
				"texture", 0
			}}
		};
		s_pipeline = instance.getRenderer().registerObject(pl::utils::ObjectType::pipeline, pipeline);
	}



	void Math::s_generatePdf(const std::string &equation, float fontSize, const std::string &hash)
	{
		std::ostringstream stream {};
		stream << R"(\documentclass[preview, margin=1px]{standalone}
\usepackage{mathrsfs}
\usepackage{slashed}
\usepackage{amsmath}
\usepackage{amssymb}
\usepackage{mathtools}
\usepackage{xcolor}
\usepackage{fix-cm}
\begin{document}
	\fontsize{)" << fontSize << R"(}{2}\selectfont{
	\mbox{\textcolor{white}{$
	)" << equation << R"($}}}
\end{document})";
		
		std::ofstream latexFile {pl::config::texFolder + hash + ".tex"};
		latexFile << stream.str();
		latexFile.close();

		if (system(("pdflatex -shell-escape -output-directory=" + pl::config::texFolder + " " + hash + ".tex").c_str()) != 0)
			throw std::runtime_error("PL : Can't compile LaTeX into a pdf");
	}



	void Math::s_convertToImage(const std::string &hash)
	{
		if (system(("convert -density 300 " + pl::config::texFolder + hash + ".pdf -quality 100 png32:" + pl::config::texFolder + hash + ".png").c_str()) != 0)
			throw std::runtime_error("PL : Can't convert pdf to png");

		
	}



} // namespace pl::blocks
