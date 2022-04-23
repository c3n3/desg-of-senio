<template>
    <div style="display: flex;" class="color-1">
        <div class="main">
            <div style="min-width: 700px;">
                <div class="color-1 item-list color-word">
                    <h3>All Tasks</h3>
                    <div v-for="(task, id) in tasks" :key="id">
                        <div class="item">
                            <input class="input-text" v-model="task['name']">
                            <div v-for="(command, i) in task['value']" :key="i">
                                <div v-if="command['major'] in devices" class="task-item">
                                    <div>
                                        <select name="type" id="type" v-model="command['type']">
                                            <option v-for="(type, id) in validCommands[devices[command['major']]['outputs'][command['minor']]['tag']]" :key="id" :value="type">
                                                {{type.replace(/([A-Z])/g, ' $1')}}
                                            </option>
                                        </select>
                                        <div>Value: <input class="input-text" v-model="command['value']" type="number"></div>
                                        <small>{{devices[command['major']]['name']}}</small>
                                    </div>
                                    <div style="display: flex; justify-content: flex-end; flex: 1;">
                                        <div class="custom-button" @click="task['value'].splice(i,1)"> - </div>
                                    </div>
                                </div>
                            </div>
                            <select name="devices" id="devices">
                                <optgroup v-for="(device, id) in devices" :key="id" :label="device['name']">
                                        <option v-for="(sub, minor) in device['outputs']" :key="minor">
                                            {{sub['persistent']['name']}}
                                        </option>
                                </optgroup>
                            </select>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
export default {
  props: ['propdata'],
  name: 'Tasks',
  data: function () {
      return {
          validCommands: {
              'Pwm': ['PwmSet', 'On', 'Off'],
              'Stepper': ['StepperRotate', 'StepperSpeed', 'On', 'Off'],
              'Switch': ['On', 'Off']
          },
          tasks: this.propdata["tasks"],
          devices: this.propdata["devices"]
      }
  },
  components: {
  },
  mounted() {
      console.log("Wat is up\n");
  }
}
</script>

<style>
.task-item {
    display: flex;
    margin-bottom: 5px;
    border: 1px solid gray;
    padding: 5px;
    cursor: text;
    -webkit-appearance: none;
    -moz-appearance: textfield;
}
</style>
