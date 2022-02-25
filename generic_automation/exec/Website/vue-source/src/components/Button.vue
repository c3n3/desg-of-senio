<template>
  <div>
    <input
        v-if="edit_name"
        v-model="persistent.name"
        @blur="edit_name = false; $emit('update')"
        @keyup.enter="edit_name = false; $emit('update')"
        v-focus>
    <h4 v-else @click="edit_name = true" class="pointer"> {{persistent.name}} </h4>
    <div>
        {{tag}} <input type="checkbox" v-model="value" @change="check($event)">
    </div>
  </div>
</template>

<script>
import axios from 'axios'

export default {
  props: ['tag', 'persistent_input', 'keystring', 'type'],
  name: 'Button',
  data: function () {
      return {
          value: null,
          edit_name: false,
          persistent: this.persistent_input,
          responseData: null,
          delayId: 0
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
      persistent: {
          // Update send an update to the server
          handler(val){
            clearTimeout(this.delayId)
            this.delayId = window.setTimeout(() => {
                var postStr = '/genauto/pages/devices/update'
                    + "?data=" + JSON.stringify(this.persistent)
                    + "&keystring=" + this.keystring
                    + "&type=" + this.type;
                axios.post(postStr
                    ,{ params: {}})
                    .then(response => this.responseData = response.data)
                    .catch(error => {});
            }, 1000)
          },
          deep: true
      }
  }
}
</script>

<style>

</style>
