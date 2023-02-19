#include "crow.h"
#include <iostream>
#include <fstream>

#include "SQLiteCpp/SQLiteCpp.h"
//#include "SQLiteCpp/Database.h"

int checkDBTable() {
    SQLite::Database DB("wkdata.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

    SQLite::Statement create_verkTable(DB,"CREATE TABLE verk("
                                    "ID INT PRIMARY KEY NOT NULL, "
                                    "NAME TEXT NOT NULL, "
                                    "DESCRIPTION CHAR(255), "
                                    "FEES BOOL)");

    SQLite::Statement create_kasseTable(DB, "CREATE TABLE kasse("
                                    "ID INT PRIMARY KEY NOT NULL, "
                                    "verkID INT NOT NULL, "
                                    "PRICE DOUBLE NOT NULL)");
    
    
    const bool vExists = DB.tableExists("verk");
    std::cout << "Debug: SQLite table 'verk' exists=" << vExists << "\n";

	if (vExists != true) {
		std::cerr << "WARN: Did not find table 'verk'" << std::endl;
        std::cout << "Creating table 'verk'" << std::endl;

        try
        {
            create_verkTable.executeStep();
        }
        catch (std::exception& e)
        {
            std::cerr << "ERROR creating 'verk' table" << std::endl;
            std::cout << "exception: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }
	}

    const bool kExists = DB.tableExists("kasse");
    std::cout << "Debug: SQLite table 'kasse' exists=" << kExists << "\n";

	if (kExists != true) {
		std::cerr << "WARN: Did not find table 'kasse'" << std::endl;
        std::cout << "Creating table 'kasse'" << std::endl;

        try
        {
            create_kasseTable.executeStep();
        }
        catch (std::exception& e)
        {
            std::cerr << "ERROR creating 'kasse' table" << std::endl;
            std::cout << "exception: " << e.what() << std::endl;
            return EXIT_FAILURE;
        }
	}

	//SQLite::Database::Deleter::operator()(*DB);
    //SQLite::Database::Deleter(*DB);
    //DB.~Database::Deleter;

    return EXIT_SUCCESS;

}

int storeData(int verkID, double price) {
    SQLite::Database DB("wkdata.db3", SQLite::OPEN_READWRITE);

    SQLite::Statement storeDataSQL(DB, "INSERT INTO kasse VALUES( "
                                    "verkID, "
                                    "price)");

    try
    {
        storeDataSQL.executeStep();
    }
    catch (std::exception& e)
    {
        std::cerr << "ERROR adding data to table 'kasse'" << std::endl;
        std::cout << "exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

	//SQLite::Database::Deleter(*DB);
    //DB.Deleter::operator();
    return EXIT_SUCCESS;
}

int main() {
    crow::SimpleApp app;

    checkDBTable();

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
            storeData(verkID, price);

        }
        return crow::response{os.str()};
        
    });

    app.port(18080)
        .server_name("Wiesenkasse")
        .multithreaded()
        .run();
}