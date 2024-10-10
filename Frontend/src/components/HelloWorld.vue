<template>
  <el-row class="component-container">
    <el-col :span="5">
      <el-select
          v-model="selectedMsgId"
          placeholder="选择msg ID"
          size="small"
          style="float: right; margin-top: 10px;"
        >
        <el-option
          v-for="item in msgIdOptions"
          :key="item.value"
          :label="item.label"
          :value="item.value"
        ></el-option>
      </el-select>
    </el-col>
    <el-col :span="22">
      <div>
        <el-input type="textarea" :autosize="{ minRows: 3, maxRows: 6 }" v-model="localInput" placeholder="说说今天做点什么吧！">
        </el-input>
      </div>
      <el-row>
        <el-col :span="21">
          <div v-if="loading">
            加载中...
            <el-icon class="is-loading"><Loading /></el-icon>
          </div>
        </el-col>
        <el-col :span="3">
          <el-button type="danger" round @click="submitText" style="margin-top: 5px;">
            发送
          </el-button>
        </el-col>
      </el-row>
    </el-col>
    <el-col :span="1"></el-col>
  </el-row>
  <el-row style="background-color: #f1f2f5; height: 15px; margin-left: -20px;  margin-right: -20px;"></el-row>  
</template>


<script>
import axios from 'axios';
import {nanoid} from 'nanoid'
import { ElMessage } from 'element-plus'
const open4 = (errormsg) => {
  ElMessage.error(errormsg)
}
export default {
  name: 'HelloWorld',
  data() {
    return {
      localInput: '', // 用于文本框的本地数据
      recivedata: [],
      showMessage: false,
      loading: false,
      msgIdOptions: [
        { label: '通义千问', value: 5 },
        { label: '本地大模型', value: 7 }
      ],
      // 新增：用于存储选中的msgId
      selectedMsgId: 5 // 默认值与初始选项匹配
    };
  },
  props:['addTodo'],
  methods: {

    submitText() {
      this.loading = true;

      const dataTosend = {
        text: this.localInput,
        msgid: this.selectedMsgId

      };
      axios.post('/login', dataTosend)
        .then(response => {
          console.log('服务器响应:', response.data);
          this.recivedata = response.data.todos;
          this.showMessage = true;
          // 处理服务器的响应
          this.loading = false;
          this.localInput = ''
          // this.$emit('inputSubmitted', this.recivedata); // 向父组件发送事件
          // const todoObj = {id:nanoid(),title:this.recivedata,done:false}
          const todoObj = this.recivedata.map(item => {
            return {
              id: nanoid(),
              title: item,
              done: false
            };
          });
          this.recivedata = ''
          console.log(todoObj)
          if (todoObj[0].title !== 'null') {
            this.addTodo(todoObj);
          } else {
            open4("未提取到关键词！")
          }
        })
        .catch(error => {
          const errorMessage = error.message; 
          open4(errorMessage)
          console.error('请求错误:', error);
          this.loading = false;
          // 处理错误ee
        });
    },
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
h3 {
  margin: 40px 0 0;
}
ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
a {
  color: #42b983;
}
::v-deep .el-textarea__inner{
    border-radius: 10px;      /* 圆角 */
    background-color: #f0f1f4; /* 背景颜色，可根据需要更改颜色值 */
}
.is-loading {
  animation: rotate 2s linear infinite;
}
@keyframes rotate {
  from {
    transform: rotate(0deg);
  }
  to {
    transform: rotate(360deg);
  }
}

</style>
