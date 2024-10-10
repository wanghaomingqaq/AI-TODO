<template>
  <el-row class="component-container">
    <el-col :span="1">
    </el-col>
    <el-col :span="22">
      <div>
        <el-input type="textarea" :autosize="{ minRows: 3, maxRows: 6 }" v-model="localInput" placeholder="添加你的笔记！格式： #标签 内容...">
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
          <el-button type="success" round @click="submitText" style="margin-top: 5px;">
            send
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
  name: 'NoteForm',
  data() {
    return {
      localInput: '', // 用于文本框的本地数据
      recivedata: [],
      showMessage: false,
      loading: false
    };
  },
  props:['addNote'],
  methods: {

    submitText() {
      this.loading = true;

      const dataTosend = {
        text: this.localInput,
        msgid: 6
      };
      axios.post('/login', dataTosend)
        .then(response => {
          console.log('服务器响应:', response.data);
          this.recivedata = response.data.note;
          this.showMessage = true;
          // 处理服务器的响应
          this.loading = false;
          this.localInput = ''
          console.log("--------------")
          console.log(this.recivedata)
          console.log("--------------")
          // this.$emit('inputSubmitted', this.recivedata); // 向父组件发送事件
          // const todoObj = {id:nanoid(),title:this.recivedata,done:false}
    
          const todoObj = this.recivedata.map(item => {
            return {
              id: nanoid(),
              title: JSON.parse(item),
              done: false
            };
          });

          // 使用reduce按照label分组
          const groupedByLabel = todoObj.reduce((acc, cur) => {
              const label = cur.title.label;
              if (!acc[label]) {
                  acc[label] = [];
              }
              acc[label].push({
                  content: cur.title.content,
                  createTime: cur.title.createTime
              });
              return acc;
          }, {});
          console.log(groupedByLabel);
          this.recivedata = ''
          if (todoObj[0].title !== 'null') {
            this.addNote(groupedByLabel);
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
