#pragma once
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <array>

std::vector<std::string> stringToArray(std::string str);
std::string getCurrentTimeString();
std::string chatglm(std::string& question, std::string& model_path);
std::string getHupuRes();

#define LOG(str) \
	std::cout << __FILE__ << " : " << __LINE__ << " " << \
	__TIMESTAMP__ << " : " << str << std::endl;

enum EnMsgType
{
    LOGIN_MSG=1, //登录 
    LOGIN_MSG_ACK, //登录相应
    REG_MSG, //注册
    REG_MSG_ACK, //注册响应消息
    GET_GPT, // 请求GPT
    ADD_NOTE, //添加笔记
    GET_LOCAL_GLM, //请求本地模型
    GET_HUPU //请求虎扑

};