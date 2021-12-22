<template>
  <Devices :propdata="devices"/>
</template>

<script>
    // eslint-disable-next-line no-unused-vars

import Devices from './components/Devices.vue'

export default {
  name: 'App',
  components: {
    Devices
  },
  data: function () {
    return {
      devices: JSON.parse('{"Device A":{"id": 1234,"inputs": [{"type": "bool","tag": "button","id": 0},{"type": "direction",                "tag": "encoder",                "id": 1            },            {                "type": "number",                "tag": "analog",                "id": 2            }        ],        "outputs": [            {                "type": "number",                "tag": "stepper",                "id": 3,                "data": {"min": "-inf", "max": "inf", "units": "%"}            },            {                "type": "number",                "tag": "pwm",                "id": 4,                "data": {"min": "0", "max": "100", "units": "%"}},{"type": "bool","tag": "mains","id": 5}]}}')
    }
  }
}
</script>

<style>
#app {
  color: #181c24;
}
.color-1 {
    background-color: #181c24;
}
.color-2 {
    background-color: #343c4a;
}
.color-accent {
    color: #b52b09;
}
.color-word {
    color: #ced5e0;
}
.tabs {
    display: flex;
    border-bottom: 2px solid #b52b09;
}
.tab-item {
    padding: 3px;
    margin: 3px;
    font-size: medium;
}
.custom-button {
    padding: 2px;
    margin: 5px;
    display: inline-block;
    border: 1px solid #b52b09;
    background-color: #d9ceed;
    color: #221b2e;
}
.div:hover .custom-button {
    background-color: grey;
}
.item-list {
    margin-top: 5px;
    padding: 3px;
    display: flex;
    flex-direction: column;
    max-width: 600px;
}
.item {
    background-color: #343c4a;
    margin: 5px 5px 5px 5px;
    padding: 10px;
    padding-top: 5px;
    padding-bottom: 5px;
}
.item-title {
    border-bottom: 2px solid #b52b09;
}
.main {
    flex: 1;
    display: flex;
    justify-content: center;
    align-items: center;
    flex-direction: column;
    min-width: 500px;
}

</style>
