#include "usermodel.hpp"
#include "db.h"
#include <iostream>
using namespace std;
bool UserModel::insert(User &user)
{
    char sql[1024] = {0};
    sprintf(sql,"insert into user(name,password,state) values('%s','%s','%s')",
        user.getName().c_str(),user.getPwd().c_str(),user.getState().c_str());
    
    shared_ptr<Connection> mysql = sp->getConnection();
    if(mysql->update(sql)) {
        //获取插入成功的用户数据生成的主键id
        user.setId(mysql_insert_id(mysql->getConn()));
        return true;
    }
    return false;
}

User UserModel::query(int id) 
{
    char sql[1024] = {0};
    sprintf(sql,"select * from user where id = %d",id);
    
    shared_ptr<Connection> mysql = sp->getConnection();
    MYSQL_RES *res = mysql->query(sql);
    if(res != nullptr) {
        /*获取行数据*/
        MYSQL_ROW row = mysql_fetch_row(res);
        if (row != nullptr)
        {
            User user;
            user.setId(atoi(row[0]));
            user.setName(row[1]);
            user.setPwd(row[2]);
            user.setState(row[3]);
            /*释放资源*/
            mysql_free_result(res);
            return user;
        }
    }
    return User();
}
bool UserModel::updateState(User user)
{
    char sql[1024] = {0};

    sprintf(sql,"update user set state = '%s' where id = '%d'",user.getState().c_str(),user.getId());
    
    shared_ptr<Connection> mysql = sp->getConnection();
    if (mysql->update(sql))
    {
        return true;
    }
    return false;
}