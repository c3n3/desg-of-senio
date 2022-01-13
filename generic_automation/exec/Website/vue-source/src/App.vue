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
      devices: JSON.parse(jsonInput)
    }
  },
  mounted() {
    console.log("From console: " + jsonInput);   
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
    max-width: 1000px;
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
.pointer {
    cursor: pointer;
}
.custom-button {
    background-color: #181c24;
    color: #ced5e0;
    border: 1px solid #b52b09;
    cursor: pointer;
    user-select: none;
    min-width: 25px;
    min-height: 15px;
    text-align: center;
}
.custom-button:active {     
    background-color: #343c4a;    
}
h4 {
    margin-bottom: 5px;
}
</style>
