<template>
    <el-upload
      drag
      :auto-upload="false"
      :on-change="handleFileChange"
    > 
    </el-upload>
  </template>
  
  <script>
  import axios from 'axios';
  export default {
    methods: {
      handleFileChange(file) {
        if (!file) return;
        const reader = new FileReader();
        // const filename = file.name; // 获取文件名
  
        reader.onloadend = () => {
          this.uploadFile(reader.result);
        };
  
        reader.readAsDataURL(file.raw); // 读取文件并转换为 base64
      },
      uploadFile(fileData) {
        // 这里发送 AJAX 请求
        axios.post('login', {
          file: fileData,
          msgid: 6
        }).then(response => {
          console.log('上传成功', response);
        }).catch(error => {
          
          console.error('上传失败', error);
        });
      }
    }
  };
  </script>
  