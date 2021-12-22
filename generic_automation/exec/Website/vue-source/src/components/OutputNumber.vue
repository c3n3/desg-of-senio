<template>
    <input
        v-if="edit_name"
        v-model="persistent.name"
        @blur="edit_name = false; $emit('update')"
        @keyup.enter="edit_name = false; $emit('update')"
        v-focus>
    <h4 v-else @click="edit_name = true"> {{persistent.name}} </h4>
    <div class="number-container">
        <input
            :disabled="!(min != '-inf' || max != 'inf')"
            type="range"
            :min="min"
            :max="max"
            class="slider"
            v-model="value"
            id="myRange">
        <button id="minus" @click="dec">-</button>
        <button id="plus" @click="inc">+</button>
        <input
            type="number"
            v-if="edit_increment"
            v-model="persistent.increment"
            @blur="edit_increment = false; $emit('update')"
            @keyup.enter="edit_increment = false; $emit('update')"
            v-focus>
        <div v-else>
            <label @click="edit_increment = true"> {{persistent.increment}} {{units}} </label>
        </div>
        Value: {{value}} {{units}}
    </div>
</template>

<script>
export default {
  props: ['min', 'max', 'units', 'keystring', 'persistent_input', 'device'],
  name: 'Number',
  data: function () {
      return {
          value: 0,
          persistent: this.persistent_input,
          edit_increment: false,
          edit_name: false
      }
  },
  directives: {
    focus: {
      inserted (el) {
        el.focus()
      }
    }
  },
  methods: {
    inc: function() {
        this.value = this.normalize(parseInt(this.value) + this.persistent.increment);
    },
    dec: function() {
        this.value = this.normalize(parseInt(this.value) - this.persistent.increment);

    },
    normalize: function(newVal) {
        if (newVal < this.min) {
            return this.min;
        } else if (newVal > this.max) {
            return this.max;
        }
        return newVal;
    }
  },
  watch: {
  persistent: {
    // Update send an update to the server
     handler(val){
        console.log("Updating persistent var:  " + this.keystring + " -> " + JSON.stringify(this.persistent));
     },
     deep: true
  }
}
}
</script>

<style>
.number-container {
    display: flex;
    flex-direction: column;
}
</style>
