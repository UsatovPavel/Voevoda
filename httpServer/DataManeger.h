#ifndef DATA_MANAGER_H_
#define DATA_MANAGER_H_
#include "libs/sqlite_orm/include/sqlite_orm/sqlite_orm.h"
// #include "libs/sqlite_orm.h"

struct User {
    int id;
    std::string username;
    std::string password;
};

struct UserScore {
    int id;
    int playedGames;
    int winGames;
};

namespace data_maneger {
using namespace sqlite_orm;
class DataManager {
public:
    static auto& getTable() {
        static auto storage = make_storage("db.sqlite",
            make_table("users",
                make_column("id", &User::id, primary_key().autoincrement()),
                make_column("username", &User::username),
                make_column("password", &User::password)),
            make_table("user_score",
                make_column("id", &UserScore::id, primary_key().autoincrement()),
                make_column("played_games", &UserScore::playedGames),
                make_column("win_games", &UserScore::winGames)));
        storage.sync_schema();
        return storage;
    }

    static User getUser(const std::string& username) {
        auto table = getTable();
        auto selectedUsers = table.get_all<User>(where(c(&User::username) == username), limit(1));
        if (selectedUsers.empty()) {
            return { -1, "None", "None" };
        }
        return selectedUsers[0];
    }

    static bool checkUser(const std::string& username) {
        User cur_user = getUser(username);
        return (cur_user.id != -1);
    }

    static UserScore getUserScore(const User& cur_user) {
        auto table = getTable();
        auto selectedUsers = table.get_all<UserScore>(where(c(&UserScore::id) == cur_user.id), limit(1));
        if (selectedUsers.empty()) {
            return { -1, 0, 0 };
        }
        return selectedUsers[0];
    }

    static void insertUser(const User& new_User) {
        auto table = getTable();
        table.insert(new_User);
    }
};

}


#endif // !DATA_MANAGER_H_