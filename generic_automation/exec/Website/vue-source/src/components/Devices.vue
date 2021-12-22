<template>
    <div style="display: flex;" class="color-1">
        <div class="main">
            <div style="min-width: 500px;">
                <div class="color-1 item-list color-word">
                    <h3>All devices</h3>
                    <div v-for="device in devices" :key="device.id">
                        <div class="item">
                            <h4 class="item-title">{{device.tag}}</h4>
                            <h5>Output: </h5>
                            <div v-for="output in device.outputs" :key="output.id">
                                <ul class="device-line">
                                    <div v-if="output.type === 'bool'">
                                        <Bool :tag="output.tag"/>
                                    </div>
                                    <div v-if="output.type === 'number'">
                                        <Number
                                            name="test"
                                            :min="output.data.min"
                                            :max="output.data.max"
                                            :units="output.data.units"/>
                                    </div>
                                </ul>
                            </div>
                            <h5>Input: </h5>
                            <div v-for="input in device.inputs" :key="input.id">
                                <ul class="device-line">
                                    {{input.type}}
                                    {{input.tag}}
                                </ul>
                            </div>
                            <div class="button-container">
                                <input class="send-button" type="button" value="Update"/>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import Number from './Number.vue'
import Bool from './Bool.vue'
export default {
  props: ['propdata'],
  name: 'Devices',
  data: function () {
      return {
          devices: this.propdata
      }
  },
  components: {
      Number,
      Bool
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
