#include "ZombieKiller.h"

//int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
int main()
{
    std::ifstream myfile;
    myfile.open("settings.json");
    Json::Value root;

    Json::CharReaderBuilder builder;
    JSONCPP_STRING errs;
    if (!parseFromStream(builder, myfile, &root, &errs)) {
        std::cout << errs << std::endl;
        return EXIT_FAILURE;
    }

    int rowz = -1;
    
    if (root.isMember("rowz")) {
        if (root["rowz"].isInt()) {
            rowz = root["rowz"].asInt();
        }
        else {
            std::cout << "rowz is not an int !" << std::endl;
            return 1;
        }
    }
    else {
        std::cout << "rowz not found" << std::endl;
        return 1;
    }
    std::cout << "rowz==" << rowz << std::endl;
    if (root.isMember("vmap")) {
        std::string vmap = root["vmap"].asString();
        int y = 0;
        for (int i = 0; i < vmap.size(); i++) {
            if (y >= rowz) {
                y = 0;
                std::cout << std::endl;
            }
            y++;
            std::cout << vmap[i];
        }
    }
    else {
        std::cout << "vmap not found !" << std::endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}