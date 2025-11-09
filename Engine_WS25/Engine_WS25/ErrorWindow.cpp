#include "ErrorWindow.hpp"

ErrorWindow::ErrorWindow(std::string message)
{
	sf::VideoMode mode = sf::VideoMode(500, 300);
	m_window.create(mode, "FATAL ERROR!");
	m_errorMessage = message;
}

void ErrorWindow::showError()
{
	try
	{
		sf::Font font = sf::Font();
		font.loadFromFile("./Assets/Fonts/Roboto.ttf"); //< somehow make more configurable location. config file/class with consts?
		sf::Text notice = sf::Text("A fatal error occured and the game could not be continued!", font, 14);
		sf::Text msg = sf::Text(m_errorMessage, font, 14);
		while (m_window.isOpen())
		{
			sf::Event event;
			if (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					m_window.close();
			}

			m_window.clear();
			m_window.draw(notice);
			m_window.draw(msg);
			m_window.display();
		}
	}
	catch(std::exception e)
	{
		m_window.close();
		// if font is unavailable just close the window, tough luck, no error message for you
	}
};
