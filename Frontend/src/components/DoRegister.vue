<template>
    <div class="login clearfix">
      <div class="login-wrap">
        <el-row type="flex" justify="center">
          <el-form ref="loginForm" :model="user" status-icon label-width="80px">
            <h3>注册</h3>
            <hr>
            <el-form-item prop="username" label="用户名">
              <el-input v-model="user.username" placeholder="请输入用户名"></el-input>
            </el-form-item>
            <el-form-item prop="password" label="设置密码">
              <el-input v-model="user.password" show-password placeholder="请输入密码"></el-input>
            </el-form-item>
            <el-form-item>
              <el-button type="primary" icon @click="doRegister()">注册账号</el-button>
            </el-form-item>
          </el-form>
        </el-row>
      </div>
    </div>
  </template>
   
  <script>
  import axios from "axios";
  export default {
    name: "DoRegister",
    data() {
      return {
        user: {
          username: "",
          email: "",
          password: ""
        },
      };
    },
    created() {
      // console.log($);
      // console.log("1111");
    },
    methods: {
      doRegister() {
        if (!this.user.username) {
          this.$message.error("请输入用户名！");
          return;
        } else {
            // this.$router.push({ path: "/" }); //无需向后台提交数据，方便前台调试
            axios
              .post("/login/", {
                msgid:3,
                name: this.user.username,
                password: this.user.password
              })
              .then(res => {
                console.log("输出response.data", res.data);
                // console.log("输出response.data.status", res.data.status);
                if (res.data.errno === 0) {
                  alert("please remeber your id, to login: "+res.data.id);
                  this.$router.push({ path: "/" });
                } else {
                  alert("您输入的用户名已存在！");
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
    line-height: 20px;
  }
   
  h3 {
    color: #0babeab8;
    font-size: 24px;
  }
  hr {
    background-color: #444;
    margin: 20px auto;
  }
   
  .el-button {
    width: 80%;
    margin-left: -50px;
  }
  </style>