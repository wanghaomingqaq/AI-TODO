<template>
    <div class="login" clearfix>
      <div class="login-wrap">
        <el-row type="flex" justify="center">
          <el-form ref="loginForm" :model="user" :rules="rules" status-icon label-width="80px">
            <h3>登录</h3>
            <hr>
            <el-form-item prop="username" label="用户id">
              <el-input type="text" v-model="user.username" placeholder="请输入用户id" prefix-icon></el-input>
            </el-form-item>
            <el-form-item id="password" prop="password" label="密码">
              <el-input v-model="user.password" show-password placeholder="请输入密码"></el-input>
            </el-form-item>
            <router-link to="/register">注册账号</router-link>
            <el-form-item>
              <el-button type="primary" icon="el-icon-upload" @click="doLogin()">登 录</el-button>
            </el-form-item>
          </el-form>
        </el-row>
      </div>
    </div>
  </template>
   
  <script>
  import axios from "axios";
  export default {
    name: "DoLogin",
    data() {
      return {
        user: {
          username: "",
          password: ""
        }  
      };
    },
    created() {},
    methods: {
      doLogin() {
        if (!this.user.username) {
          this.$message.error("请输入用户id！");
          return;
        } else if (isNaN(Number(this.user.username)))
        {
          this.$message.error("用户id必须是数字！");
          return;
        }
         else if (!this.user.password) {
          this.$message.error("请输入密码！");
          return;
        } else {
          //校验用户名和密码是否正确;
          // this.$router.push({ path: "/personal" });

          const loginId = parseInt(this.user.username, 10);

          axios
            .post("/login/", {
              id: loginId,
              password: this.user.password,
              msgid: 1
            })
            .then(res => {
              // console.log("输出response.data.status", res.data.status);
              console.log(res.data)
              if (res.data.errno === 0) {
                this.$router.push({ path: "/personal" });
              } else {
                this.$message.error(res.data.errmsg);
              }
            });
        }
      }
    }
  };
  </script>
   
  <!-- Add "scoped" attribute to limit CSS to this component only -->
  <style scoped>
  .login {
    width: 100%;
    height: 740px;
    background: url("../assets/images/bg1.png") no-repeat;
    background-size: cover;
    overflow: hidden;
  }
  .login-wrap {
    background: url("../assets/images/login_bg.png") no-repeat;
    background-size: cover;
    width: 400px;
    height: 300px;
    margin: 215px auto;
    overflow: hidden;
    padding-top: 10px;
    line-height: 40px;
  }
  #password {
    margin-bottom: 5px;
  }
  h3 {
    color: #0babeab8;
    font-size: 24px;
  }
  hr {
    background-color: #444;
    margin: 20px auto;
  }
  a {
    text-decoration: none;
    color: #aaa;
    font-size: 15px;
  }
  a:hover {
    color: coral;
  }
  .el-button {
    width: 80%;
    margin-left: -50px;
  }
  </style>