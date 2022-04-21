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
                                    <div v-if="output.type === 'Button'">
                                        <Button
                                            :tag="output.tag"
                                            :persistent_input="output.persistent"
                                            :keystring="id + ':' + outputId"
                                            :major="id"
                                            :minor="outputId"
                                            :type="'outputs'"
                                            :devices="devices"

                                            />
                                    </div>
                                    <div v-if="output.type === 'Encoder'">
                                        <Encoder
                                            :min="output.data.min"
                                            :max="output.data.max"
                                            :units="output.data.units"
                                            :persistent_input="output.persistent"
                                            :major="id"
                                            :minor="outputId"
                                            :type="'outputs'"
                                            :tag="output.tag"
                                            :devices="devices"
                                            />
                                    </div>
                                </ul>
                            </div>
                            <h5>Input: </h5>
                            <div v-for="(input, inputId) in device.inputs" :key="inputId">
                                <ul class="device-line">
                                    <div v-if="input.type == 'Analog'">
                                        <Analog
                                            :min="input.data.min"
                                            :max="input.data.max"
                                            :keystring="id + ':' + inputId"
                                            :persistent_input="input.persistent"
                                            :type="'inputs'"
                                            :tag="input.tag"
                                        />
                                    </div>
                                    <div v-if="input.type == 'Encoder'">
                                        <Encoder
                                            :keystring="id + ':' + inputId"
                                            :persistent_input="input.persistent"
                                            :tag="input.tag"
                                            :type="'inputs'"
                                        />
                                    </div>
                                    <div v-if="input.type == 'Button'">
                                        <Button
                                            :tag="input.tag"
                                            :persistent_input="input.persistent"
                                            :keystring="id + ':' + inputId"
                                            :type="'inputs'"
                                        />
                                    </div>
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
import Encoder from './Encoder.vue'
import Button from './Button.vue'
import Analog from './Analog.vue'
export default {
  props: ['propdata'],
  name: 'Devices',
  data: function () {
      return {
          devices: this.propdata
      }
  },
  components: {
      Encoder,
      Button,
      Analog
  },
  mounted() {
      console.log("Wat is up\n");
  }
}
</script>

<style>

.tag-label {
    font-size: 12px;
    margin-bottom: 5px;
}

</style>
