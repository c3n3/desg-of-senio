<template>
    <div style="display: flex;" class="color-1">
        <div class="main">
            <div style="min-width: 700px;">
                <div class="color-1 item-list color-word">
                    <h3>All Tasks</h3>
                    <div v-for="(task, id) in tasks" :key="id">
                        <div class="item">
                            <div style="display: flex;">
                                <input class="input-text task-title item-title" v-model="task['name']">
                                <div style="display: flex; justify-content: flex-end; flex: 1;">
                                    <div class="custom-button" @click="tasks.splice(id,1)">Delete</div>
                                    <div class="custom-button" @click="run(task['value'])">Run</div>
                                </div>
                            </div>
                            <div v-for="(command, i) in task['value']" :key="i">
                                <div v-if="(command['major'] in devices) && (command['minor'] in devices[command['major']]['outputs'])" class="task-item">
                                    <div>
                                        <div class="device-title">{{devices[command['major']]['name']}} - {{getDevice(command['major'], command['minor'])['persistent']['name']}}</div>
                                        Type: <select name="type" class="type-select" v-model="command['type']">
                                            <option v-for="(type, id) in validCommands[devices[command['major']]['outputs'][command['minor']]['tag']]" :key="id" :value="type">
                                                {{type.replace(/([A-Z])/g, ' $1')}}
                                            </option>
                                        </select>
                                        <div v-if="command['type'] != 'On' && command['type'] != 'Off'">Value: <input class="input-text" v-model="command['value']" type="number"></div>
                                    </div>
                                    <div style="display: flex; justify-content: flex-end; flex: 1;">
                                        <div><div class="custom-button" @click="task['value'].splice(i,1)"> - </div></div>
                                    </div>
                                </div>
                                <div v-else-if="command['type'] == 'Delay'" class="task-item">
                                    <div>
                                        <div class="device-title">
                                            Delay
                                        </div>
                                        Value: <input class="input-text" v-model="command['value']" type="number"> seconds
                                    </div>
                                    
                                    <div style="display: flex; justify-content: flex-end; flex: 1;">
                                        <div><div class="custom-button" @click="task['value'].splice(i,1)"> - </div></div>
                                    </div>
                                </div>
                            </div>
                            <div class="dropdown-container">
                                Add: <select name="devices" id="devices" class="fake-dropdown" :key="addValue">
                                    <option value="" disabled selected hidden>Select Device</option>
                                    <optgroup label="Non-devices" class="font-12">
                                        <option value="Delay" @click="addDelay(id)">Delay</option>
                                    </optgroup>
                                    <optgroup v-for="(device, devId) in devices" :key="devId" :label="device['name']" class="font-12">
                                            <option v-for="(sub, minor) in device['outputs']" :key="minor" @click="add(id, devId, minor)">
                                                {{sub['persistent']['name']}}
                                            </option>
                                    </optgroup>
                                </select>
                            </div>
                        </div>
                    </div>
                    <div class="custom-button" @click="tasks.push({'name': 'New Task', 'value': []})">Add Task</div>
                    <div class="custom-button" @click="save">Save</div>
                </div>
            </div>
        </div>
    </div>
</template>

<script>
import axios from 'axios'

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
          devices: this.propdata["devices"],
          addValue: false
      }
  },
  components: {
  },
  methods: {
      getDevice: function(major, minor) {
          return this.devices[major]['outputs'][minor];
      },
      addDelay: function(task) {
          console.log("Called")
          this.tasks[task]['value'].push({"value": 0, "type": "Delay", "major": 0, "minor": 0})
          this.addValue = !this.addValue
      },
      add: function(task, major, minor) {
          console.log("Called")
          let dev = this.getDevice(major, minor)
          this.tasks[task]['value'].push({"value": 0, "type": this.validCommands[dev['tag']][0], "major": parseInt(major), "minor": parseInt(minor)})
          this.addValue = !this.addValue
      },
      save: function() {
        var postStr = '/genauto/pages/tasks/save'
            + "?data=" + JSON.stringify(this.tasks)
        axios.post(postStr
            ,{ params: {}})
            .then(response => this.responseData = response.data)
            .catch(error => {});
      },
      run: function(data) {
        var postStr = '/genauto/pages/tasks/run'
            + "?data=" + JSON.stringify(data)
        axios.post(postStr
            ,{ params: {}})
            .then(response => this.responseData = response.data)
            .catch(error => {});
      }
  },
  mounted() {
      console.log("Wat is up\n");
  }
}
</script>

<style>
.task-item {
    display: flex;
    margin-bottom: 10px;
    /* border: 1px solid gray; */
    padding: 3px;
    cursor: text;
    -webkit-appearance: none;
    -moz-appearance: textfield;

}
.task-title {
    font-size: 20px;
    margin-bottom: 10px;
}
.fake-dropdown {
    background: transparent;
    color: #ced5e0;
}
.font-12 {
    font-size: 12px;
}
.dropdown-container {
    display: flex;
    flex-direction: column;
    justify-content:flex-start; 
}
.device-title {
    margin-bottom: 5px;
    border-bottom: solid 1px gray;
    font-size: 18px;
}
.type-select {
    background: transparent;
    color: #ced5e0;
    margin-top: 5px;
    margin-bottom: 5px;
}
</style>
