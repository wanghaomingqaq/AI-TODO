<template>
  <div>
    <h2>Login</h2>
    <form @submit.prevent="loginUser">
      <label for="loginUsername">Username:</label>
      <input type="text" id="loginUsername" v-model="loginId" required>
      <label for="loginPassword">Password:</label>
      <input type="password" id="loginPassword" v-model="loginPassword" required>
      <button type="submit">Login</button>
    </form>

    <h2>Register</h2>
    <form @submit.prevent="registerUser">
      <label for="registerUsername">Username:</label>
      <input type="text" id="registerUsername" v-model="registerUsername" required>
      <label for="registerPassword">Password:</label>
      <input type="password" id="registerPassword" v-model="registerPassword" required>
      <button type="submit">Register</button>
    </form>
  </div>
</template>

<script>
import axios from 'axios';

export default {
  name: 'LoginForm',
  data() {
    return {
      loginId: '',
      loginPassword: '',
      registerUsername: '',
      registerPassword: ''
    };
  },
  methods: {
    async loginUser() {
      try {
        const loginId = parseInt(this.loginId, 10);
        const response = await axios.post('/login', {
          id: loginId,
          password: this.loginPassword,
          msgid: 1
        });
        console.log(response.data);
        if (response.data.errno == 0)
        {
          this.$emit('login-success', response.data);
        }
        else
        {
          console.error('Login failed:', response.data.errmsg);
        }
      } catch (error) {
        console.error(error);
      }
    },
    async registerUser() {
      try {
        const response = await axios.post('/login', {
          msgid:3,
          name: this.registerUsername,
          password: this.registerPassword,
        });
        if (response.data.errno == 0)
        {
          this.$emit('register-success', response.data);
          alert("please remember your id!!!"+response.data.id);
        }
        else
        {
          console.error('Login failed:', response.data.errmsg);
        }
      } catch (error) {
        console.error(error);
      }
    }
  }
};
</script>
