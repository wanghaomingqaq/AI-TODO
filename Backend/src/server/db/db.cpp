#include <mysql/mysql.h>
#include <string>
#include "db.h"
#include "mymuduo/Logger.h"
#include "public.hpp"

using namespace std;

// 初始化数据库连接
Connection::Connection()
{
	_conn = mysql_init(nullptr);
    // 设置字符集为 utf8mb4
    if (mysql_options(_conn, MYSQL_SET_CHARSET_NAME, "utf8mb4") != 0) {
        fprintf(stderr, "Error setting character set: %s\n", mysql_error(_conn));
        mysql_close(_conn);
        exit(1);
    }
}

// 释放数据库连接资源
Connection::~Connection()
{
	if (_conn != nullptr)
		mysql_close(_conn);
}

// 连接数据库
bool Connection::connect(string ip, unsigned short port, string user,
	string password, string dbname)
{
    LOG_INFO("connect MySQL! ip: %s, user: %s, password: %s dbname: %s port: %d"
            ,ip.c_str()
            ,user.c_str()
            ,password.c_str()
            ,dbname.c_str()
            ,port);
	MYSQL* p = mysql_real_connect(_conn, ip.c_str(), user.c_str(),
		password.c_str(), dbname.c_str(), port, nullptr, 0);
	if (p != nullptr)
	{
		// C和C++代码默认的编码字符是ASCII，如果不设置，
		// 那么从MySQL上拉下来的中文会显示【 ？？？】
		mysql_query(_conn, "set names gbk");
        LOG("connect MySQL successfully!");
	}
    else
    {
        LOG_ERROR("connect MySQL failed! errno: %s",mysql_error(_conn));
    }

	return p;
}

// 更新操作 insert、delete、update
bool Connection::update(string sql)
{
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG("Update failed: " + sql);
        LOG("Error: " + string(mysql_error(_conn)));
		return false;
	}
	return true;
}

// 查询操作 select
MYSQL_RES* Connection::query(string sql)
{
	if (mysql_query(_conn, sql.c_str()))
	{
		LOG("Query failed: " + sql);
		return nullptr;
	}
	return mysql_use_result(_conn);
}

// 获取连接
MYSQL* Connection::getConn()
{
    return _conn;
}
// 刷新一下连接的起始空闲时间点
void Connection::refreshAliveTime()
{
	_aliveTime = clock();
}

// 返回存活的时间
clock_t Connection::getAliveTime() const
{
	return clock() - _aliveTime;
}