<template>
    <div style="display: flex;" class="color-1">
        <div class="main">
            <div style="min-width: 700px;">
                <div class="color-1 item-list color-word">
                    <h3>All devices</h3>
                    <div v-for="(device, id) in devices" :key="id">
                        <div class="item">
                            <h4 class="item-title">{{device.name}}</h4>
                            <h5>Output: </h5>
                            <div v-for="(output, outputId) in device.outputs" :key="outputId">
                                <ul class="device-line">
                                    <div v-if="output.type === 'bool'">
                                        <OutputBool
                                            :tag="output.tag"
                                            :persistent_input="output.persistent"
                                            :keystring="id + ':' + outputId"/>
                                    </div>
                                    <div v-if="output.type === 'number'">
                                        <OutputNumber
                                            :min="output.data.min"
                                            :max="output.data.max"
                                            :units="output.data.units"
                                            :persistent_input="output.persistent"
                                            :keystring="id + ':' + outputId"/>
                                    </div>
                                </ul>
                            </div>
                            <h5>Input: </h5>
                            <div v-for="(input, inputId) in device.inputs" :key="inputId">
                                <ul class="device-line">
                                    <InputNumber
                                        v-if="input.type == 'number'"
                                        :min="input.data.min"
                                        :max="input.data.max"
                                        :keystring="id + ':' + inputId"
                                        :persistent_input="input.persistent"
                                    />
                                </ul>
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
import InputNumber from './InputNumber.vue'
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
      OutputBool,
      InputNumber
  }
}
</script>

<style>
</style>
