<template>
    <input
        v-if="edit_name"
        v-model="persistent.name"
        @blur="edit_name = false; $emit('update')"
        @keyup.enter="edit_name = false; $emit('update')"
        v-focus>
    <h4 v-else @click="edit_name = true" class="pointer"> {{persistent.name}} </h4>
  {{tag}} <input type="checkbox" v-model="value" @change="check($event)">
</template>

<script>
export default {
  props: ['tag', 'persistent_input', 'keystring'],
  name: 'OutputBool',
  data: function () {
      return {
          value: null,
          edit_name: false,
          persistent: this.persistent_input
      }
  },
  methods: {
       check: function(e) {
           console.log("The value is " + this.value);
       }
  },
  directives: {
      focus: {
          inserted (el) {
              el.focus()
          }
      }
  },
  watch: {
      // persistent: {
      //     // Update send an update to the server
      //     handler(val){
      //         console.log("Updating persistent var:  " + this.keystring + " -> " + JSON.stringify(this.persistent));
      //     },
      //     deep: true
      // }
  }
}
</script>

<style>

</style>
