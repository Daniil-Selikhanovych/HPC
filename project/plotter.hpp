#ifndef PHPPINCLUDED
#define PHPPINCLUDED
/*
#include <exception>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Color.hpp>

std::vector< sf::VertexArray > generate_vertex_array (std::vector< std::vector< double > > & data,
                                        std::vector< sf::Color > & cl, int width, int height)
{
    if (data.size() == 0 || data.size() > cl.size())
    {
        throw std::invalid_argument("size error");
    }


	std::vector< sf::VertexArray > result(data.size() + 1);
	for (auto & current: result)
        current = sf::VertexArray(sf::PrimitiveType::LinesStrip, 0);

	double max_value = *std::max_element(data[0].begin(), data[0].end());
    for (size_t i = 1; i < data.size(); i++)
        max_value = std::max(max_value, *std::max_element(data[i].begin(), data[i].end()));
    double min_value = *std::min_element(data[0].begin(), data[0].end());
    for (size_t i = 1; i < data.size(); i++)
        min_value = std::min(min_value, *std::min_element(data[i].begin(), data[i].end()));
    double range = max_value - min_value;

    for (size_t i = 0; i < data.size(); i++)
        for (size_t j = 0; j < data[i].size(); j++)
        {
            sf::Vector2f new_point((int)((double)j / data[i].size() * width),
                               height - (int)((data[i][j] - min_value) / range * height));
            result[i].append(sf::Vertex(new_point, cl[i]));
        }

    sf::Vector2f zero_point1(0, height + (int)((min_value) / range * height));
    result[result.size() - 1].append(sf::Vertex(zero_point1, sf::Color::White));

    sf::Vector2f zero_point2(width, height + (int)((min_value) / range * height));
    result[result.size() - 1].append(sf::Vertex(zero_point2, sf::Color::White));
    return result;
}


void show_plot(std::vector< std::vector< double > > & data, std::vector< sf::Color > && cl)
{
    int height = 600;
    int width = 800;
	std::vector< sf::VertexArray > lines = generate_vertex_array(data, cl, width, height);

    sf::RenderWindow window(sf::VideoMode(width, height), "Plot");
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		for (auto & l: lines)
            window.draw(l);
		window.display();
	}
}
*/

#endif // PLOTTER_HPP_INCLUDED
