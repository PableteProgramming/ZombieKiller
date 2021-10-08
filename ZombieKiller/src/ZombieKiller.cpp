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
    int cellz = -1;
    
    //parsing row size
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

    //parsing cell size
    if (root.isMember("cellz")) {
        if (root["cellz"].isInt()) {
            cellz = root["cellz"].asInt();
        }
        else {
            std::cout << "cellz is not an int !" << std::endl;
            return 1;
        }
    }
    else {
        std::cout << "cellz not found" << std::endl;
        return 1;
    }

    //parsing map
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

    std::cout<<std::endl;

    //parsing color values
    std::vector <int> _0_colors;
    std::vector <int> _1_colors;
    std::vector <int> _2_colors;
    if (root.isMember("colors")) {
        if (root["colors"].isObject()) {
            //parsing color0
            if (root["colors"]["0"].isArray()) {
                _0_colors.push_back(root["colors"]["0"][0].asInt());
                _0_colors.push_back(root["colors"]["0"][1].asInt());
                _0_colors.push_back(root["colors"]["0"][2].asInt());
            }
            else {
                std::cout << "Colors 0 is not an array !" << std::endl;
                return 1;
            }

            //parsing color1
            if (root["colors"]["1"].isArray()) {
                _1_colors.push_back(root["colors"]["1"][0].asInt());
                _1_colors.push_back(root["colors"]["1"][1].asInt());
                _1_colors.push_back(root["colors"]["1"][2].asInt());
            }
            else {
                std::cout << "Colors 1 is not an array !" << std::endl;
                return 1;
            }

            //parsing color2
            if (root["colors"]["2"].isArray()) {
                _2_colors.push_back(root["colors"]["2"][0].asInt());
                _2_colors.push_back(root["colors"]["2"][1].asInt());
                _2_colors.push_back(root["colors"]["2"][2].asInt());
            }
            else {
                std::cout << "Colors 2 is not an array !" << std::endl;
                return 1;
            }
        }
        else {
            std::cout << "colors is not an array !" << std::endl;
            return 1;
        }
    }
    else {
        std::cout << "colors not found" << std::endl;
        return 1;
    }

    std::cout << "color 0: " << _0_colors[0] << ";" << _0_colors[1] << ";" << _0_colors[2] << std::endl;
    std::cout << "color 1: " << _1_colors[0] << ";" << _1_colors[1] << ";" << _1_colors[2] << std::endl;
    std::cout << "color 2: " << _2_colors[0] << ";" << _2_colors[1] << ";" << _2_colors[2] << std::endl;

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