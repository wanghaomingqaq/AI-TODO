<template>
  <div style="padding: 5%;">
    <el-list-item>
        <label>
          <span>{{ note.title.label }}</span>
          <span>{{ note.title.content }}</span>
        </label>
    </el-list-item>
  </div>
</template>
<script>
  export default {
    name:"NoteIterm",
    props:['note'], //接受todo对象
    methods:{
    }
  }
</script>
<style scoped>
  /*item*/
  li {
    list-style: none;
    height: 26px;
    line-height: 26px;
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
