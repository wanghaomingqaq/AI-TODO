// router.js
import App from '../App.vue';
import { createRouter, createWebHistory } from 'vue-router';
import DoRegister from '../components/DoRegister.vue';
import DoLogin from '../components/DoLogin.vue';


const routes = [
  {
    path: '/register',
    component: DoRegister
  },
  {
    path: '/login',
    component: DoLogin
  },
  {
	path: '/person',
	component: App,
  }
];

const router = createRouter({
  history: createWebHistory(),
  routes
});

export default router;
