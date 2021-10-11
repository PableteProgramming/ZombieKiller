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

    Json::Value vmap;
    //parsing vmap
    if (root.isMember("vmap")) {
        if (root["vmap"].isObject()) {
            vmap = root["vmap"];
        }
        else {
            std::cout << "vmap is not json object !" << std::endl;
            return 1;
        }
    }
    else {
        std::cout << "vmap not found" << std::endl;
        return 1;
    }

    int rows = -1;
    //parse rows
    if (vmap.isMember("rows")) {
        if (vmap["rows"].isInt()) {
            rows = vmap["rows"].asInt();
        }
        else {
            std::cout << "rows is not an int !" << std::endl;
            return 1;
        }
    }
    else {
        std::cout << "rows not found" << std::endl;
        return 1;
    }

    int cellsize = -1;
    //parse cellsize
    if (vmap.isMember("cellsize")) {
        if (vmap["cellsize"].isInt()) {
            cellsize = vmap["cellsize"].asInt();
        }
        else {
            std::cout << "cellsize is not an int !" << std::endl;
            return 1;
        }
    }
    else {
        std::cout << "cellsize not found" << std::endl;
        return 1;
    }

    std::vector<std::string> map;

    if (vmap.isMember("map")) {
        if (vmap["map"].isArray()) {
            for (int i = 0; i < rows; i++) {
                if (vmap["map"][i].isString()) {
                    map.push_back(vmap["map"][i].asString());
                }
                else {
                    std::cout << "map [" << i << "] is not a string!" << std::endl;
                    return 1;
                }
            }
        }
        else {
            std::cout << "map is not an array !" << std::endl;
            return 1;
        }
    }
    else {
        std::cout << "map not found" << std::endl;
        return 1;
    }

    std::vector<std::pair<std::string, int*>> colors;
    Json::Value c;

    //parse colors
    if (root.isMember("colors")) {
        if (root["colors"].isObject()) {
            c = root["colors"];
            if (c.isMember("num")) {
                if (c["num"].isInt()) {
                    int num = c["num"].asInt();
                    if (c.isMember("values")) {
                        if (c["values"].isArray()) {
                            for (int i = 0; i < num; i++) {
                                if (c["values"][i].isArray()) {
                                    if (c["values"][i][0].isString()) {
                                        if (c["values"][i][1].isArray()) {
                                            int v[3] = { -1,-1,-1 };
                                            for (int k = 0; k < 3; k++) {
                                                if (c["values"][i][1][k].isInt()) {
                                                    v[k] = c["values"][i][1][k].asInt();
                                                }
                                                else {
                                                    std::cout << " values[" << i << "][1]["<<k<<"] is not an int!" << std::endl;
                                                    return 1;
                                                }
                                            }
                                            std::pair<std::string, int*> p = std::make_pair(c["values"][i][0].asString(), v);
                                            colors.push_back(p);
                                        }
                                        else {
                                            std::cout << " values[" << i << "][1] is not an array!" << std::endl;
                                            return 1;
                                        }
                                    }
                                    else {
                                        std::cout << " values[" << i << "][0] is not an string!" << std::endl;
                                        return 1;
                                    }
                                }
                                else {
                                    std::cout << " values[" << i << "] is not an array!" << std::endl;
                                    return 1;
                                }
                            }
                        }
                        else {
                            std::cout << "values is not an array !" << std::endl;
                            return 1;
                        }
                    }
                    else {
                        std::cout << "values not found" << std::endl;
                        return 1;
                    }
                }
                else {
                    std::cout << "num is not an int!" << std::endl;
                    return 1;
                }
            }
            else {
                std::cout << "num not found" << std::endl;
                return 1;
            }
        }
        else {
            std::cout << "colors is not a json object !" << std::endl;
            return 1;
        }
    }
    else {
        std::cout << "colors not found" << std::endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(180, 20), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    window.clear();
    DrawMap(map, colors, cellsize, window);
    window.display();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        /*window.clear();
        DrawMap(map,colors,cellsize,window);
        window.display();*/
    }

    return 0;
}