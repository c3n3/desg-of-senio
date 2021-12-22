<template>
  {{tag}} <input type="checkbox" v-model="value" @change="check($event)">
</template>

<script>
export default {
  props: ['tag'],
  name: 'OutputBool',
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

</style>
