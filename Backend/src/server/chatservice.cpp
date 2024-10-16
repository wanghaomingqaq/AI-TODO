#include "chatservice.hpp"
#include "public.hpp"
#include <vector>
#include <mymuduo/Logger.h>
#include "gptcurl.h"
#include "note.h"
#include <functional>
/*获取单例*/
ChatService* ChatService::instance()
{
    static ChatService service;
    return &service;
}

/*构造函数
注册消息以及对应的handler回调操作
*/
ChatService::ChatService() {
    _msgHandlerMap.insert({LOGIN_MSG,std::bind(&ChatService::login,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    _msgHandlerMap.insert({REG_MSG,std::bind(&ChatService::reg,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    _msgHandlerMap.insert({GET_GPT,std::bind(&ChatService::gpt,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    _msgHandlerMap.insert({ADD_NOTE,std::bind(&ChatService::addnote,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    _msgHandlerMap.insert({GET_LOCAL_GLM,std::bind(&ChatService::gptGlm,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
    _msgHandlerMap.insert({GET_HUPU,std::bind(&ChatService::getHupu,this,std::placeholders::_1,std::placeholders::_2,std::placeholders::_3)});
}

//处理登录
void ChatService::login(HttpResponse* resp, json &js, Timestamp time)
{
    LOG_INFO("do login service!!");
    LOG_INFO("%s",js.dump().c_str());
    int id = js["id"].get<int>();
    string pwd = js["password"];

    User user = _userModel.query(id);
    if (user.getId() == id && user.getPwd() == pwd) {
        if (user.getState() == "online") {
            //不允许重复登录
            json response;
            response["msgid"] = REG_MSG_ACK;
            response["errno"] = 2;
            response["errmsg"] = "不允许重复登录";
            LOG_INFO("不允许重复登录");
            resp->setBody(response.dump());          
        }
        else
        {
            //登录成功
            user.setState("online");
            _userModel.updateState(user);

            json response;
            response["msgid"] = LOGIN_MSG_ACK;
            response["errno"] = 0;
            response["id"] = user.getId();
            response["name"] = user.getName();
            LOG_INFO("登录成功");
            resp->setBody(response.dump()); 
        }   
    }
    else
    {
        json response;
        response["msgid"] = REG_MSG_ACK;
        response["errno"] = 1;
        response["errmsg"] = "用户名或者密码错误";
        resp->setBody(response.dump()); 
    }
}

void ChatService::reg(HttpResponse* resp,json &js, Timestamp time)
{
    LOG_INFO("do reg service!!");
    string name = js["name"];
    string pwd = js["password"];

    User user;
    user.setName(name);
    user.setPwd(pwd);
    bool state = _userModel.insert(user);
    if (state) 
    {
        //注册成功
        json response;
        response["msgid"] = REG_MSG_ACK;
        response["errno"] = 0;
        response["id"] = user.getId();
        resp->setBody(response.dump()); 
    }
    else
    {
        //注册失败
        json response;
        response["msgid"] = REG_MSG_ACK;
        response["errno"] = 1;
        resp->setBody(response.dump()); 
    }
}

void ChatService::gpt(HttpResponse* resp,json &js, Timestamp time)
{
    LOG_INFO("do gpt");
    string question = js["text"].get<string>();
    string ans = generate_response(question);
    json response;
    vector<string> ansVector = stringToArray(ans);
    for (auto s: ansVector) cout<<s<<endl;
    response["todos"] = ansVector;
    resp->setBody(response.dump());
}

void ChatService::getHupu(HttpResponse* resp,json &js, Timestamp time)
{
    LOG_INFO("do getHupu");
    json response;
    std::string res = getHupuRes();
    // vector<string> resVector = stringToArray(res);
    response["post"] = res;
    resp->setBody(response.dump());
}

void ChatService::gptGlm(HttpResponse* resp,json &js, Timestamp time)
{
    LOG_INFO("do gpt");
    string model_path = "/home/workspace/InferLLM/chatglm-q4.bin";
    string question = js["text"].get<string>();
    string ans2 = chatglm(question, model_path);
    json response;
    vector<string> ansVector = stringToArray(ans2);
    for (auto s: ansVector) cout<<s<<endl;
    response["todos"] = ansVector;
    resp->setBody(response.dump());
}

void ChatService::addnote(HttpResponse* resp,json &js, Timestamp time)
{
    LOG_INFO("do addnote");
    cout<<js.dump()<<endl;
    string rec = js["text"].get<string>();
    Note note;
    string ret = note.processNote(rec);
    resp->setBody(ret);
}

MsgHandler ChatService::getHandler(int msgid) 
{
    //记录错误日志， msgid没有对应的事件处理回调
    auto it = _msgHandlerMap.find(msgid);
    if (it==_msgHandlerMap.end()) {
        return [=](HttpResponse* resp, json &js, Timestamp time) {
            LOG_ERROR("msgid:%d can not find handler!",msgid); // =是按值获取，来一个默认的空的事件处理器
        }; 
    }
    else
    {
        return _msgHandlerMap[msgid];
    } 
}