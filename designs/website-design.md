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
[
    "Device A": {
        "id": 1234
        "inputs": [
            {
                "type": "bool",
                "tag": "button",
                "id": 0
            },
            {
                "type": "direction",
                "tag": "encoder",
                "id": 1
            },
            {
                "type": "number",
                "tag": "analog",
                "id": 2
            }
        ]
        "outputs": [
            {
                "type": "number",
                "tag": "stepper",
                "id": 3,
                "data": {"min": "-inf", "max": "inf", "units": "%"}
            },
            {
                "type": "number",
                "tag": "pwm",
                "id": 4,
                "data": {"min": "0", "max": "100", "units": "%"}
            },
            {
                "type": "bool",
                "tag": "mains",
                "id": 5,
            }
        ]
    }
]