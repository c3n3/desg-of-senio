<template>
<div>
    <input
        v-if="edit_name"
        v-model="persistent.name"
        @blur="edit_name = false; $emit('update')"
        @keyup.enter="edit_name = false; $emit('update')"
        v-focus>
    <h4 v-else @click="edit_name = true" class="pointer"> {{persistent.name}} </h4>
    <div class="tag-label">&nbsp;&nbsp;&nbsp;&nbsp;Type: {{tag}}</div>

    <div v-if="type === 'outputs'" class="number-container">
        <div>
            <div class="custom-button" id="plus" @click="inc">+</div>
            <div class="custom-button" id="minus" @click="dec">-</div>
        </div>
        <div class="increment-container">
            Increment:&nbsp;
            <input
                type="number"
                v-if="edit_increment"
                v-model="persistent.increment"
                @blur="edit_increment = false; $emit('update')"
                @keyup.enter="edit_increment = false; $emit('update')"
                v-focus>
            <div v-else @click="edit_increment = true" class="pointer">
                {{persistent.increment}}
            </div>
            &nbsp;{{units}}
        </div>
        Value: {{value}} {{units}}
    </div>
    <br v-if="type == 'outputs'">
    <div class="links-wrapper-wrapper" v-if="type == 'outputs'">
        <div class="links-wrapper">
            Link device to input(s):
            <div v-for="(device, dev_id) in devices" :key="dev_id" class="device-links">
                {{device.name}}:
                <div class="links">
                    <div v-for="(input, id) in device.inputs" :key="id" class="link-item">
                        <label :for="id"> {{input['persistent']['name']}}</label><br>
                        <input
                        type="checkbox"
                        :id="id"
                        :value="dev_id + ':' + id"
                        v-model="persistent['linked']"
                        >
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>
</template>

<script>
import axios from 'axios'

export default {
    props: ['min', 'max', 'units', 'major', 'minor', 'persistent_input', 'device', 'type', 'tag', 'devices'],
    name: 'Encoder',
    data: function () {
        return {
            linked: [],
            value: 0,
            keystring: this.major + ":" + this.minor,
            persistent: this.persistent_input,
            edit_increment: false,
            edit_name: false,
            delayId: 0,
            valueDelayId: 0,
            previousValue: 0
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
            this.value = this.normalize(parseInt(this.value) + parseInt(this.persistent.increment));
            this.send(this.persistent.increment);
        },
        dec: function() {
            this.value = this.normalize(parseInt(this.value) - parseInt(this.persistent.increment));
            this.send(-this.persistent.increment);
        },
        send: function(increment) {
            var postStr = '/genauto/pages/devices/encoder_send'
                + "?major=" + this.major.toString()
                + "&minor=" + this.minor.toString()
                + "&inc=" + (increment).toString();
            console.log("URL: " + postStr + "\n")
            axios.post(postStr
                ,{ params: {}})
                .then(response => {})
                .catch(error => {});
            this.previousValue = this.value;
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
                clearTimeout(this.delayId);
                this.delayId = window.setTimeout(() => {
                    console.log("This has been updated");
                    var postStr = '/genauto/pages/devices/update'
                        + "?data=" + JSON.stringify(this.persistent)
                        + "&keystring=" + this.keystring
                        + "&type=" + this.type;
                    axios.post(postStr
                        ,{ params: {}})
                        .then(response => this.responseData = response.data)
                        .catch(error => {});
                }, 1000)
            },
            deep: true
        },
    }
}
</script>

<style>
.number-container {
    display: flex;
    flex-direction: column;
}
.increment-container {
    display: flex;
}
</style>
