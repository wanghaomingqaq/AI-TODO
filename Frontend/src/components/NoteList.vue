<template>
  <el-collapse v-model="activeNames" @change="handleChange">
    <div v-for="(value, label) in notes" :key="label">
      <el-collapse-item :title="label" :name="label">
        <ul>
          <li v-for="(item, index) in value" :key="index">
            {{ item.content }}
          </li>
        </ul>
      </el-collapse-item>
    </div>
  </el-collapse>
</template>
<script>
  export default {
    name:"NoteList",
    props:['notes']

  }
</script>
<style scoped>
::v-deep .el-collapse-item__header {
  font-size: 16px; /* 标题字体大小 */
  padding-left: 10px !important;
  padding: 5px 0; /* 增加上下填充，从而增加整个标题区域的大小 */
  color: #000000; /* 字体颜色 */
  background-color: #FFFFFF; /* 背景颜色 */
  border-bottom: 1px solid #d3dce6; /* 底部边框 */
}

.el-collapse-item {
  border: 1px solid #d3dce6; /* 整个折叠项的边框 */
  border-radius: 3px; /* 边框圆角 */
  margin-bottom: 1px; /* 项与项之间的间距 */
  overflow: hidden; /* 确保子元素不会溢出边界 */
}

.el-collapse-item:last-child {
  margin-bottom: 0; /* 最后一个项没有底部间距 */
}

.el-collapse-item__content {
  padding: 10px; /* 内容填充 */
  line-height: 0.5; /* 内容行高 */
  background-color: #fff; /* 内容背景颜色 */
}

ul {
  list-style: none; /* 移除列表符号 */
  padding: 0;
  margin: 0;
}

li {
  font-size: 14px; /* 列表项字体大小 */
  margin-bottom: 8px; /* 列表项间隔 */
}

/* 自定义箭头图标的样式 */
.el-collapse-item__header .el-collapse-item__arrow {
  font-size: 20px; /* 箭头大小 */
  color: #495057; /* 箭头颜色 */
}
</style>
