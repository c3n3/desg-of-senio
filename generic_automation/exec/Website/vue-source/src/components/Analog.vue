<template>
    <div>
        <input
            v-if="edit_name"
            v-model="persistent.name"
            @blur="edit_name = false; $emit('update')"
            @keyup.enter="edit_name = false; $emit('update')"
            v-focus>
        <h4 v-else @click="edit_name = true" class="pointer"> {{persistent.name}} </h4>
        <div class="input-number-value">
            <div>Value: {{value}}</div>&nbsp;
            <div>
                <input
                    v-if="edit_units"
                    v-model="persistent.units"
                    @blur="edit_units = false; $emit('update')"
                    @keyup.enter="edit_units = false; $emit('update')"
                    v-focus>
                <div v-else @click="edit_units = true" class="pointer"> {{persistent.units}} </div>
            </div>
        </div>
        <div class="input-number-normalize">
            <div style="display: flex;">
                Normalize:&nbsp;'
                <input
                    v-if="edit_normalize"
                    v-model="persistent.normalize"
                    @blur="edit_normalize = false; $emit('update')"
                    @keyup.enter="edit_normalize = false; $emit('update')"
                    v-focus>
                <div v-else @click="edit_normalize = true" class="pointer">{{persistent.normalize}} </div>
                '
            </div>
        </div>
    </div>
</template>

<script>
// "type": "number",
// "tag": "analog",
// "id": 2,
// "data": {"min": 0, "max": 3.3},
// "persistent": {"normalize": "3.3", "units": "volts", "name": "Analog A"}
import axios from 'axios'

export default {
    props: ['keystring', 'min', 'max', 'persistent_input', 'type'],
    name: 'Analog',
    data: function () {
        return {
            edit_name: false,
            edit_units: false,
            edit_normalize: false,
            value: null,
            persistent: this.persistent_input,
            delayId: 0
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
        update: function() {
            // call to server for response within normal range
            var val = Math.random() * this.max;
            if (isNaN(parseFloat(this.persistent.normalize))) {
                // assume function here
            } else {
                //Math.round(val * 100) / 100
                this.value = Math.round((((this.normalize(val) - this.min) / (this.max - this.min)) * this.persistent.normalize) * 100) / 100;
            }
        },
        normalize: function(val) {
            if (val < this.min) {
                return this.min;
            } else if (val > this.max) {
                return this.max;
            }
            return val;
        }
    },
    mounted() {
        this.$nextTick(function () {
            window.setInterval(() => {
                this.update();
            }, 2000);
        })
    },
    watch: {
        persistent: {
            // Update send an update to the server
            handler(val){
                clearTimeout(this.delayId)
                this.delayId = window.setTimeout(() => {
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
        }
    }
}
</script>

<style>
    .input-number-value {
        display: flex;
        flex-direction: row;
        margin-left: 10px;
    }
    .input-number-normalize {
        margin-left: 10px;
    }
</style>
