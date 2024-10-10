<template>
  <div>
    <el-button type="success" round @click="startRecognition" :loading="loading">
      开始语音识别
    </el-button>
    <el-table :data="transcripts" style="width: 100%">
      <el-table-column
        prop="text"
        label="识别内容"
        width="100%">
      </el-table-column>
      <el-table-column
        prop="timestamp"
        label="时间戳"
        width="200">
      </el-table-column>
    </el-table>
  </div>
</template>

<script setup>
import { ref, onMounted, onUnmounted } from 'vue';

const transcripts = ref([]);
const loading = ref(false);
let recognition;

onMounted(() => {
  const SpeechRecognition = window.SpeechRecognition || window.webkitSpeechRecognition;
  if (SpeechRecognition) {
    recognition = new SpeechRecognition();
    recognition.continuous = true;  // 连续识别
    recognition.lang = 'zh-CN';     // 设置语言为简体中文

    recognition.onresult = (event) => {
      for (let i = event.resultIndex; i < event.results.length; i++) {
        transcripts.value.push({
          text: event.results[i][0].transcript,
          timestamp: new Date().toLocaleTimeString()
        });
      }
    };

    recognition.onerror = (event) => {
      console.error('语音识别错误:', event.error);
      loading.value = false;
    };
  } else {
    console.error('浏览器不支持 SpeechRecognition');
  }
});

onUnmounted(() => {
  if (recognition) {
    recognition.stop();
  }
});

function startRecognition() {
  if (recognition && !loading.value) {
    recognition.start();
    loading.value = true;
    recognition.onend = () => {
      loading.value = false;
    };
  }
}
</script>
