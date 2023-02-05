#include "crow.h"
#include <iostream>
#include <fstream>
#include <sqlite3.h>

static int callback(void* data, int argc, char** argv, char** azColName) {
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return true;
}

int checkDBTable() {
    // check if standard database tables exist and create if not

    std::string check_verkTable = "SELECT 1 FROM verk;";
    std::string check_kasseTable = "SELECT 1 FROM kasse;";

    std::string create_verkTable = "CREATE TABLE verk("
                                    "ID INT PRIMARY KEY NOT NULL, "
                                    "NAME TEXT NOT NULL, "
                                    "DESCRIPTION CHAR(50), "
                                    "FEES BOOL );";

    std::string create_kasseTable = "CREATE TABLE kasse("
                                    "ID INT PRIMARY KEY NOT NULL, "
                                    "verkID INT NOT NULL, "
                                    "PRICE DOUBLE NOT NULL);";
    int exit;
	char* messaggeError;

    sqlite3* DB;
    sqlite3_open("wkdata.db", &DB);
    
    exit = sqlite3_exec(DB, check_verkTable.c_str(), callback, NULL, &messaggeError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error Checking verk Table" << std::endl;
		sqlite3_free(messaggeError);
        std::cout << "Creating Table verk" << std::endl;

        exit = sqlite3_exec(DB, create_verkTable.c_str(), callback, NULL, &messaggeError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error Creating verk Table" << std::endl;
            return false;
        }
	}
	else
		std::cout << "Table verk Check Successful" << std::endl;

	exit = sqlite3_exec(DB, check_kasseTable.c_str(), callback, NULL, &messaggeError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error Checking kasse Table" << std::endl;
		sqlite3_free(messaggeError);
        std::cout << "Creating Table kasse" << std::endl;
        
        exit = sqlite3_exec(DB, create_verkTable.c_str(), callback, NULL, &messaggeError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error Creating kasse Table" << std::endl;
            return false;
        }
	}
	else
		std::cout << "Table kasse Check Successful" << std::endl;
    
    sqlite3_close(DB);
	return true;

}

int storeData(int verkID, double price) {
    sqlite3* DB;
    char* messaggeError;
    int exit;
    sqlite3_open("wkdata.db", &DB);

    std::string storeDataSQL = "INSERT INTO kasse VALUES( "
                                    "verkID, "
                                    "price);";

    exit = sqlite3_exec(DB, storeDataSQL.c_str(), callback, NULL, &messaggeError);

	if (exit != SQLITE_OK) {
		std::cerr << "Error saving data" << std::endl;
		sqlite3_free(messaggeError);
    }

    sqlite3_close(DB);
    return true;
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
            // storeData(verkID, price);

        }
        return crow::response{os.str()};
        
    });

    app.port(18080)
        .server_name("Wiesenkasse")
        .multithreaded()
        .run();
}