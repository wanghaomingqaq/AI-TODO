<template>
    <div>
      <el-button type="success" round @click="submitHupu" style="margin-top: 5px;">
        今天资讯
      </el-button>
      <el-table :data="receivedData" style="width: 100%">
        <el-table-column
        prop="title"
        label="篮球资讯"
        width="500">
        <template #default="{ row }">
          <!-- 使用标题作为链接 -->
          <a :href="row.link" target="_blank">{{ row.title }}</a>
        </template>
      </el-table-column>
      </el-table>
    </div>
  </template>
  
  <script>
  import axios from 'axios';
  
  export default {
    name: 'NoteForm',
    data() {
      return {
        localInput: '',
        receivedData: [],
        loading: false
      };
    },
    methods: {
      submitHupu() {
        this.loading = true;
        axios.post('/login', { text: this.localInput, msgid: 8 })
          .then(response => {
            const posts = JSON.parse(response.data.post);
            this.receivedData = Object.entries(posts).map(([title, link]) => ({
            title, link
            }));
            console.log(this.receivedData);
            this.loading = false;
          })
          .catch(error => {
            console.error('请求错误:', error);
            this.loading = false;
          });
      }
    }
  }
  </script>
  
  <style scoped>
    .list-item {
      padding: 10px;
      border-bottom: 1px solid #ebebeb;
    }
    
    .list-item:last-child {
      border-bottom: none;
    }
    a:link {
    color: black; /* 未访问的链接颜色 */
    text-decoration: none;
    }
    a:hover {
    color: #C60100; /* 将颜色改为蓝色 */
    }
    a:visited {
    color: gray; /* 已访问的链接颜色 */
    }
  </style>
  