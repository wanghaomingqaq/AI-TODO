<template>
  <div>
      <div class="todo-footer" v-show="todos.length" style="background-color: #ecf5ff; border-radius: 5px;margin-left: 5%; margin-right: 5%;">
        <el-row>
          <el-col :span="16">
            <div>
              <label style="margin-left: -10px;">
                <input type="checkbox" :checked="isAll" @change="checkAll"/>
              </label>
              <span>
                All Checked
              </span>
            </div>
          </el-col>
          <el-col :span="8">
            <div>
              <el-button @click="deleteAllChecked" type="primary" :icon="Delete" circle />
            </div>
          </el-col>
        </el-row>
      </div>
  </div>
</template>
<script setup>
import {
  Delete,
} from '@element-plus/icons-vue'
</script>
<script>
  export default {
    name:"TodoFooter",
    props:['todos','checkAllTodo','deleteAll'],
    computed:{
      done_count(){
        return this.todos.filter((todo)=>{
                return todo.done === true
               })
      },
      isAll(){
        return this.done_count.length === this.todos.length
      }
    },
    methods:{
      checkAll(e){
        this.checkAllTodo(e.target.checked)
      },
      deleteAllChecked(){
        this.deleteAll(this.todos.filter((todo)=>{
                return todo.done === false
               }))
      }
    }
  }
</script>
<style scoped>
  /*footer*/
  .todo-footer {
    height: 40px;
    line-height: 40px;
    margin-top: 5px;
  }

  .todo-footer label {
    display: inline-block;
    cursor: pointer;
  }

  .todo-footer label input {
    position: relative;
    top: -1px;
    vertical-align: middle;
    margin-right: 5px;
  }
</style>