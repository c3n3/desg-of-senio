<template>
  <div>
    <input
        v-if="edit_name"
        v-model="persistent.name"
        @blur="edit_name = false; $emit('update')"
        @keyup.enter="edit_name = false; $emit('update')"
        v-focus>
    <h4 v-else @click="edit_name = true" class="pointer"> {{persistent.name}} </h4>
    <div v-if="type == 'outputs'">
        <input type="checkbox" v-model="value" @change="check($event)">
    </div>
    <div class="tag-label">&nbsp;&nbsp;&nbsp;&nbsp;Type: {{tag}}</div>
    <br v-if="type == 'outputs'">
    <div class="links-wrapper-wrapper" v-if="type == 'outputs'">
        <div class="links-wrapper">
            Link device to input(s):
            <div v-for="(device, id) in devices" :key="id" class="device-links">
                {{device.name}}:
                <div class="links">
                    <div v-for="(input, id) in device.inputs" :key="id" class="link-item">
                        <label for="{{id}}"> {{input['persistent']['name']}}</label><br>
                        <input
                        type="checkbox"
                        id="{{id}}"
                        name="{{inputs[id]['persistent']['name']}}"
                        value="{{inputs[id]['persistent']['name']}}">
                    </div>
                </div>
            </div>
        </div>
    </div>
  </div>
</template>

<script>
import axios from 'axios'

export default {
  props: ['tag', 'persistent_input', 'keystring', 'type', 'links'],
  name: 'Button',
  data: function () {
      return {
          value: null,
          linked: null,
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
  },
  mounted() {
    console.log("Got: ");   
    console.log(this.links);   
  }
}
</script>

<style>

</style>
