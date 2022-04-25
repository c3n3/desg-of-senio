<template>
    <div style="display: flex;" class="color-1">
        <div class="main">
            <div style="min-width: 700px;">
                <div class="color-1 item-list color-word">
                    <h3>All Events</h3>
                    <div v-for="(event, id) in events" :key="id">
                        <div class="item">
                            <div style="display: flex;">
                                <input class="input-text task-title item-title" v-model="event['name']">
                                <div style="display: flex; justify-content: flex-end; flex: 1;">
                                    <div class="custom-button" @click="events.splice(id,1)">Delete</div>
                                </div>
                            </div>
                            <div class="type-section">
                                Type: <select name="type" class="type-select" v-model="event['type']">
                                    <option value="Periodic">Periodic</option>
                                    <option value="Daily">Daily</option>
                                    <option value="Weekly">Weekly</option>
                                </select>
                            </div>
                            <div>Repeat Every</div>
                            <div class="value-section">
                                <div v-if="event['type'] == 'Periodic'">
                                    <div class="input-line"><input class="input-text" v-model="event['minutes']" min="0" max="59"> Minutes</div>
                                    <div class="input-line"><input class="input-text" v-model="event['hours']" min="0" max="1000"> Hours</div>
                                </div>
                                <div v-if="event['type'] == 'Daily'">
                                    <div class="input-line"><input class="input-text" v-model="event['minutes']" @input="event['minutes'] = limit(event['minutes'], 0, 59)"> Minute of the hour</div>
                                    <div class="input-line"><input class="input-text" v-model="event['hours']" @input="event['hours'] = limit(event['hours'], 0, 23)"> Hour of the day</div>
                                </div>
                                <div v-if="event['type'] == 'Weekly'">
                                    <div class="input-line"><input class="input-text" v-model="event['minutes']" @input="event['minutes'] = limit(event['minutes'], 0, 59)"> Minute of the hour</div>
                                    <div class="input-line"><input class="input-text" v-model="event['hours']" @input="event['hours'] = limit(event['hours'], 0, 23)"> Hour of the day</div>
                                    <div class="input-line"><input class="input-text" v-model="event['hours']" @input="event['days'] = limit(event['days'], 0, 6)"> Day of the week</div>
                                </div>
                            </div>
                            <div class="task-selection">
                                Task: <select name="type" class="type-select" v-model="event['task']">
                                    <option v-for="(task, tid) in tasks" :value="task['name']" :key="tid">{{task['name']}}</option>
                                </select>
                            </div>
                            <div v-if="!event['enabled']" class="custom-button" @click="event['enabled'] = !event['enabled']; save()">Enable</div>
                            <div v-if="event['enabled']" class="custom-button" @click="event['enabled'] = !event['enabled']; save()">Disable</div>
                        </div>
                    </div>
                    <div class="custom-button" @click="events.push({'name': 'New Task', 'type': 'Periodic', 'enabled': false, 'task': '', 'hours': 0, 'minutes': 0, 'days': 0})">Add Event</div>
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
  name: 'TimedEvents',
  data: function () {
      return {
          validCommands: {
              'Pwm': ['PwmSet', 'On', 'Off'],
              'Stepper': ['StepperRotate', 'StepperSpeed', 'On', 'Off'],
              'Switch': ['On', 'Off']
          },
          tasks: this.propdata["tasks"],
          events: this.propdata["events"],
          addValue: false
      }
  },
  components: {
  },
  methods: {
      limit: function(variable, min, max) {
          if (variable > max) {
              return max;
          } else if (variable < min) {
              return min;
          }
          return variable;
      },
      save: function() {
        var postStr = '/genauto/pages/timedevents/save'
            + "?data=" + JSON.stringify(this.events)
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
.input-line {
    margin-bottom: 5px;
    border-bottom: 1px solid gray;
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
