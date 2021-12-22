<template>
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
            v-model="increment"
            @blur="edit_increment = false; $emit('update')"
            @keyup.enter="edit_increment = false; $emit('update')"
            v-focus>
        <div v-else>
            <label @click="edit_increment = true;"> {{increment}} </label>
        </div>
        Value: {{value}} {{units}}
    </div>
</template>

<script>
export default {
  props: ['name', 'min', 'max', 'units'],
  name: 'Number',
  data: function () {
      return {
          value: 0,
          increment: 1,
          edit_increment: false
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
        const newVal = parseInt(this.value) + this.increment;
        if (newVal > this.max) {
            this.value = this.max;
        } else {
            this.value = newVal;
        }
    },
    dec: function() {
        const newVal = parseInt(this.value) - this.increment;
        if (newVal < this.min) {
            this.value = this.min;
        } else {
            this.value = newVal;
        }
    }
  }
}
</script>

<style>
.number-container {
    display: flex;
    flex-direction: row;
}
</style>
