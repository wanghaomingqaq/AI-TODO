const { defineConfig } = require('@vue/cli-service')
module.exports = defineConfig({
  transpileDependencies: true,
  devServer: {
    proxy: {
      '/login': {
        target: 'http://49.232.24.125:7777',  // 目标接口的域名
        changeOrigin: true,            // 是否改变域名
        pathRewrite: {
          '^/login': ''                  // 路径重写
        }
      }    
    }
  }
})
