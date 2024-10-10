<template>
  <div style="padding: 5%;">
    <el-list-item>
        <label>
          <!-- <el-checkbox v-model="todo.done" @change="handleCheck(todo.id)"></el-checkbox> -->
          <input type="checkbox" :checked='todo.done' @change="handleCheck(todo.id)"/>
          <span>{{ todo.title }}</span>
        </label>
    </el-list-item>
  </div>
</template>
<script>
  export default {
    name:"TodoIterm",
    props:['todo',"checkTodo"], //接受todo对象
    methods:{
      handleCheck(id){
        //通知app对应todo取反
        this.checkTodo(id)
      },
      itermDelete(id){
        this.deleteTodo(id)
      }
    }
  }
</script>
<style scoped>
  /*item*/
  li {
    list-style: none;
    height: 36px;
    line-height: 36px;
    padding: 0 5px;
    border-bottom: 1px solid #ddd;
  }

  li label {
    float: left;
    cursor: pointer;
  }

  li label li input {
    vertical-align: middle;
    margin-right: 6px;
    position: relative;
    top: -1px;
  }

  li button {
    float: right;
    display: none;
    margin-right: 10px;
    /*margin-top: 1px;*/
    font-size: 22px;
    color: #f5928d;
    /*margin-block: 2px;*/
  }

  li:before {
    content: initial;
  }

  li:last-child {
    border-bottom: none;
  }
  li:hover {
    background-color: #ddd;
  }
  li:hover button{
    display: block;
    /*color: #ff0000;*/
    /*margin-block: 2px;*/
    /*margin-top: 3px;*/
  }
  button:hover {
    color: #ff0000;
  }
</style>
