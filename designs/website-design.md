# Website structure

## Device list
- List of devices
- - Each device has list of components
- - - Each component has a type
- - - - Input
- - - - - Analog
- - - - - Digital
- - - - Output 
- - - - - Number
- - - - - On / Off

### Component
- Type
- Input / Output
- - Number
- - On / Off
- - Analog
- - Digital
- - - Encoder / Button
- ID
- Name
- Values: Some arbitrary dictionary for that type

### Example:
{
    "Device A": {
        "id": 1234,
        "inputs": [
            {
                "type": "bool",
                "tag": "button",
                "id": 0,
                "persistent": {"name": "Button A"}
            },
            {
                "type": "direction",
                "tag": "encoder",
                "id": 1.
                "persistent": {"name": "Encoder A"}
            },
            {
                "type": "number",
                "tag": "analog",
                "id": 2,
                "data": {"min": 0, "max": 3.3},
                "persistent": {"normalize": "3.3", "units": "volts"}
            }
        ],
        "outputs": [
            {
                "type": "number",
                "tag": "stepper",
                "id": 3,
                "data": {"min": "-inf", "max": "inf", "units": "degrees"},
                "persistent": {"increment": 1, "name": "Stepper A"}
            },
            {
                "type": "number",
                "tag": "pwm",
                "id": 4,
                "data": {"min": "0", "max": "100", "units": "%"},
                "persistent": {"increment": 1, "name": "PWM A"}
            },
            {
                "type": "bool",
                "tag": "switch",
                "id": 5,
            }
        ]
    }
}