<template>
  <img alt="Vue logo" src="./assets/logo.png">
  <input v-model="message" placeholder="edit me">
  <p>Message is: {{ message }}</p>
  <li v-for="item in items" :key="item.message">
    {{ item }}
      <Main/>
  </li>
  
</template>

<script>
import Main from './components/Main.vue'

export default {
  name: 'App',
  data : function() {
    return {
      message: "",
      items: [1,2,3,4,5,6,7,8]
    }
  },
  components: {
    Main
  }
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}
</style>
