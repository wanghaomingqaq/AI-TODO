<template>
    <div style="background-color: aliceblue; text-align: center; margin: 5%; padding-top: 5px; height: 120px; border-radius: 5%;">
      <h1>今日</h1>
      <h1>ToDo</h1>
    </div>
  <div style="padding-top: 20px;">
      <el-list style="text-align:left;">
<!--        :todo 加了：才是表达式-->
        <TodoIterm
            v-for="todoObj in todos"
            :key="todoObj.id"
            :todo="todoObj"
            :checkTodo="checkTodo"
            :deleteTodo="deleteTodo">
        </TodoIterm>
      </el-list>
  </div>
</template>
<script>
  import TodoIterm from "./TodoIterm";
  export default {
    name:"TodoList",
    components: {TodoIterm},
    props:['todos','checkTodo','deleteTodo']

  }
</script>
<style>

</style>