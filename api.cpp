#include "crow.h"
#include <iostream>
#include <fstream>

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        auto page = crow::mustache::load_text("main.html");
        return page;
    });

    CROW_ROUTE(app, "/form")([](){
        auto page = crow::mustache::load_text("form.html");
        return page;
    });

    CROW_ROUTE(app,"/hello/<int>")
    ([](int hello){
        if (hello >1000)
            return crow::response(400);
        return crow::response(std::to_string(hello));
    });

    CROW_ROUTE(app,"/data/print")([](){
        // define static for DEBUG
        crow::json::wvalue fullData({
            {"id", 0},
            {"name", "foo"},
            {"items", 13},
            {"cash", 42.},
            {"tax", true},
            {"cashout", 38.}
        });
        
        // read from file
        /*
        std::string path = "./";
        std::string file_name = "fdata";

        std::ifstream file(path + "/" + file_name + ".json");
        file >> fullData;
        */

        return fullData;
    });

    CROW_ROUTE(app, "/data/add").methods(crow::HTTPMethod::POST)
    ([](const crow::request& req){
        std::ostringstream os;

        auto dset = crow::json::load(req.body);
        if (!dset)
          return crow::response(400);

        auto itemsObj = dset["items"];
        int itemsCount = itemsObj.size();
        os << "\n Elemente: " << itemsCount << "\n";
        //return crow::response{os.str()};


        // os << "The key 'count' contains " << count.size() << " value(s).\n";
        //v1: for (const auto& countVal : itemsCount)
        for (int i = 0; i < itemsCount; i++)
        {
            int verkID = itemsObj[i]["verkID"].i();
            double price = itemsObj[i]["price"].d();
            os << "Transaktion: " << i << '\n';
            os << "verkID:" << verkID << ", ";
            os << "preis:" << price << "\n";

        }
        return crow::response{os.str()};
        
    });

    app.port(18080)
        .server_name("Wiesenkasse")
        .multithreaded()
        .run();
}