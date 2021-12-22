<template>
    <div style="display: flex;" class="color-1">
        <div class="main">
            <div style="min-width: 700px;">
                <div class="color-1 item-list color-word">
                    <h3>All devices</h3>
                    <div v-for="device in devices" :key="device.id">
                        <div class="item">
                            <h4 class="item-title">{{device.tag}}</h4>
                            <h5>Output: </h5>
                            <div v-for="output in device.outputs" :key="output.id">
                                <ul class="device-line">
                                    <div v-if="output.type === 'bool'">
                                        <OutputBool :tag="output.tag"/>
                                    </div>
                                    <div v-if="output.type === 'number'">
                                        <OutputNumber
                                            :min="output.data.min"
                                            :max="output.data.max"
                                            :units="output.data.units"
                                            :persistent_input="output.persistent"
                                            :keystring="device.id + ':' + output.id"/>
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
import OutputNumber from './OutputNumber.vue'
import OutputBool from './OutputBool.vue'
export default {
  props: ['propdata'],
  name: 'Devices',
  data: function () {
      return {
          devices: this.propdata
      }
  },
  components: {
      OutputNumber,
      OutputBool
  }
}
</script>

<style>

</style>
