#include "Engine.h"
#include <cmath>

Engine::Engine() {

	m_Window.create(VideoMode::getDesktopMode(), "Particles", Style::Default);
}

void Engine::run() {

	Clock clock;
	Time dt;

	cout << "Starting Particle unit tests..." << endl;
	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
	p.unitTests();
	cout << "Unit tests complete.  Starting engine..." << endl;

	while (m_Window.isOpen()) {

		dt = clock.restart();

		this->input();
		this->update(dt.asSeconds());
		this->draw();
	}
}

void Engine::input() {

	Event event;
	while (m_Window.pollEvent(event)) {

		if (event.type == Event::Closed) {

			m_Window.close();
		}

		if (event.type == Event::KeyPressed) {

			if (event.key.code == Keyboard::Escape) {

				m_Window.close();
			}
		}

		if (event.type == Event::MouseButtonPressed) {

			if (event.mouseButton.button == Mouse::Left) {

				for (size_t i = 0; i < 5; ++i) {

					m_particles.push_back(Particle(m_Window, ((rand() % 26) + 25), Mouse::getPosition()));
				}
			}
		}
	}

}

void Engine::update(float dtAsSeconds) {

	vector<Particle>::iterator iter;
	for (iter = m_particles.begin(); iter != m_particles.end();) {

		if (iter->getTTL() > 0.0) {

			iter->update(dtAsSeconds);
			++iter;
		}
		else {

			iter = m_particles.erase(iter);
		}
	}
}

void Engine::draw() {

	m_Window.clear();

	for (size_t i = 0; i < m_particles.size(); ++i) {

		m_Window.draw(m_particles.at(i));
	}

	m_Window.display();

}