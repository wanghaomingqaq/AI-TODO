<template>
  <router-view/>
  <div class="common-layout">
    <el-container>
        <el-header class="header" style="height: 60px;">
        <el-row :gutter="20" class="align-center">
          <el-col :span="4">
            <div class="grid-content ep-bg-purple">
              <el-icon size="35" color="#d52c2b"><MostlyCloudy /></el-icon>
            </div>
          </el-col>
          <el-col :span="12">
          <el-row>

            <el-col :span="4"></el-col>
            <el-col :span="5">
              <el-button style="border: none;">
                <el-icon size="25" color="black"><HomeFilled /></el-icon>
              </el-button>
            </el-col>
            <el-col :span="5">
              <el-button style="border: none;">
                <el-icon size="25" color="black"><Tickets /></el-icon>
              </el-button>
            </el-col>
            <el-col :span="5">
              <el-button style="border: none;">
                <el-icon size="25" color="black"><ShoppingTrolley /></el-icon>
              </el-button>
            </el-col>
            <el-col :span="5">
              <el-button style="border: none;">
                <el-icon size="25" color="black"><VideoCamera /></el-icon>
              </el-button>
            </el-col>
          </el-row>
          </el-col>
          <el-col :span="5">
            <div class="grid-content ep-bg-purple">
              <el-input placeholder="搜索内容" class="search-input"></el-input>
            </div>
          </el-col>
          <el-col :span="2">
              <div class="header-buttons" style="padding-left: 90px;">
              
                <div>
                  <el-dropdown trigger="click" @command="handleCommand">
                    <el-avatar
                      size="large"
                      src="https://cube.elemecdn.com/0/88/03b0d39583f48206768a7534e55bcpng.png"
                    />
                    <template #dropdown>
                    <el-dropdown-menu>
                      <el-dropdown-item command="register">注册</el-dropdown-item>
                      <el-dropdown-item command="login">登录</el-dropdown-item>
                    </el-dropdown-menu>
                    </template>
                  </el-dropdown>
                </div>     
              </div>
          </el-col>
        </el-row>
        </el-header>
        <el-row style="height: 10px; background-color: #f1f2f5; padding-top: 60px;"></el-row>
        <el-container style="height: 100vh; margin-top: -20px;">
          <el-aside width="350px" style="background-color: #f1f2f5;">
            <!-- 侧边栏内容 -->
            <el-row style="height: 100vh;">
              <el-col :span="1" style=" background-color: #f1f2f5;"></el-col>
              <el-col :span="22" style=" background-color: #ffffff;">
                <el-divider content-position="left">Notes by Label</el-divider>
                <NoteList :notes="notes"></NoteList>
              </el-col>
              <el-col :span="1" style=" background-color: #f1f2f5;"></el-col>
            </el-row>
          </el-aside>
          <el-main >
            <el-row>
              <el-col :span="24">
                  <div id="app">
                    <HelloWorld :addTodo="addTodo"/>
                  </div> 
                  <div id="note" style="margin-top: 40px;">
                    <NoteForm :addNote="addNote"/>
                  </div>
                  <div id="hupu" style="margin-top: 40px;">
                    <HupuForm :addNote="addNote"/>
                  </div>                 
              </el-col>
            </el-row>
            <HelloUpdate></HelloUpdate>
            <HelloVideo></HelloVideo>
          </el-main>
          <el-aside width="350px" style="background-color: #f1f2f5;">
            <!-- 侧边栏内容 -->
            <el-row style="height: 100vh;">
              <el-col :span="1" style=" background-color: #f1f2f5;"></el-col>
              <el-col :span="14" style=" background-color: #ffffff;">
                <TodoList :todos="todos" :checkTodo="checkTodo" :deleteTodo="deleteTodo"></TodoList>
                <TodoFooter :todos="todos" :checkAllTodo="checkAllTodo" :deleteAll="deleteAll"></TodoFooter>
              </el-col>
              <el-col :span="9"></el-col>
            </el-row>
          </el-aside>
        </el-container>
    </el-container>
  </div>
</template>

<script>
import HelloWorld from './components/HelloWorld.vue';
import NoteForm from './components/NoteForm.vue';
import HupuForm from './components/HupuForm.vue';
import TodoList from "@/components/TodoList";
import NoteList from "@/components/NoteList";
import TodoFooter from "@/components/TodoFooter";
import HelloVideo from './components/HelloVideo.vue';
import HelloUpdate from './components/HelloUpdate.vue';
export default {
  name: 'App',
  components: {
    HelloWorld,
    NoteForm,
    HupuForm,
    TodoList,
    NoteList,
    TodoFooter,
    HelloVideo,
    HelloUpdate,
  },
  data() {
    return {
      // 定义一个属性来存储从子组件接收的数据
      receivedData: 'dd',
      todos:JSON.parse(localStorage.getItem('todos')) || [],
      notes: Object,
      isLoggedIn: false,
      currentUser: null,
    };
  },
  methods: {
    handleCommand(command) {
      if (command === 'register') {
        // 跳转到注册页面或执行注册逻辑
        this.$router.push('/register');
      } else if (command === 'login') {
        // 跳转到登录页面或执行登录逻辑
        this.$router.push('/login');
      }
    },
    handleLoginSuccess(user) {
      this.currentUser = user;
      this.isLoggedIn = true;
    },
    handleRegisterSuccess(user) {
      this.currentUser = user;
      this.isLoggedIn = true;
    },
    logout() {
      this.isLoggedIn = false;
      this.currentUser = null;
    },
    addTodo(todoObj){
      // 过滤掉数组中的 null 值

        this.todos.unshift(...todoObj);
      },
    addNote(noteObj){
    // 过滤掉数组中的 null 值

      this.notes = noteObj;
    },
    //取消勾选todo
    checkTodo(id){
      this.todos.forEach((todo)=>{
        if(todo.id === id){
          todo.done = !todo.done
        }
      })
    },
    //删除todo
    deleteTodo(id){
      this.todos = this.todos.filter((todo)=>{
        return todo.id !== id
      })
    },
      //全选or不选
    checkAllTodo(done){
      this.todos.forEach((todo)=>{
        todo.done = done
      })
    },
    //删除所有checked
    deleteAll(no_checked_arr){
      this.todos = no_checked_arr
    }    
  },
  watch:{
      todos:{
        deep:true,
        handler(value){
          localStorage.setItem('todos',JSON.stringify(value))
        }
      },
    }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 10px;
}
.el-row {
  margin-bottom: 20px;
}
.el-row:last-child {
  margin-bottom: 0;
}
.el-col {
  border-radius: 4px;
}
.align-center {
  display: flex;
  align-items: center; /* 这将使得el-row的所有子元素垂直居中 */
  height: 100%; /* 确保el-row占满el-header的整个高度 */
}
.el-header {
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  z-index: 1000;
  background-color: #ffffff;
  color: var(--el-text-color-primary);
}
.grid-content {
  border-radius: 4px;
  min-height: 36px;
}
</style>
