<template>
  {{tag}} <input type="checkbox" v-model="value" @change="check($event)">
</template>

<script>
export default {
  props: ['tag'],
  name: 'Bool',
  data: function () {
      return {
          value: null
      }
  },
  methods: {
       check: function(e) {
           console.log("The value is " + this.value);
       }
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
