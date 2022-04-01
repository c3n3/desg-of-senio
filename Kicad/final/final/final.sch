EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 8250 2600 0    50   Input ~ 0
G36
Text GLabel 8250 2700 0    50   Input ~ 0
G39
Text GLabel 8250 2800 0    50   Input ~ 0
G34
Text GLabel 8250 2900 0    50   Input ~ 0
G35
Text GLabel 8250 3000 0    50   Input ~ 0
G32
Text GLabel 8250 3100 0    50   Input ~ 0
G33
Text GLabel 8250 3200 0    50   Input ~ 0
G25
Text GLabel 8250 3300 0    50   Input ~ 0
G26
Text GLabel 8250 3400 0    50   Input ~ 0
G27
Text GLabel 8250 3500 0    50   Input ~ 0
G14
Text GLabel 8250 3600 0    50   Input ~ 0
G12
Text GLabel 8250 3700 0    50   Input ~ 0
GND
Text GLabel 8250 3800 0    50   Input ~ 0
G13
Text GLabel 8250 3900 0    50   Input ~ 0
G9
Text GLabel 8250 4000 0    50   Input ~ 0
G10
Text GLabel 8250 4100 0    50   Input ~ 0
G11
Text GLabel 8250 4200 0    50   Input ~ 0
ESP_VIN
Text GLabel 9650 4200 2    50   Input ~ 0
G6
Text GLabel 9650 4100 2    50   Input ~ 0
G7
Text GLabel 9650 4000 2    50   Input ~ 0
G8
Text GLabel 9650 3900 2    50   Input ~ 0
G15
Text GLabel 9650 3800 2    50   Input ~ 0
G2
Text GLabel 9650 3700 2    50   Input ~ 0
G0
Text GLabel 9650 3600 2    50   Input ~ 0
G4
Text GLabel 9650 3500 2    50   Input ~ 0
G16
Text GLabel 9650 3400 2    50   Input ~ 0
G17
Text GLabel 9650 3300 2    50   Input ~ 0
G5
Text GLabel 9650 3200 2    50   Input ~ 0
G18
Text GLabel 9650 3100 2    50   Input ~ 0
G19
Text GLabel 9650 3000 2    50   Input ~ 0
GND
Text GLabel 9650 2900 2    50   Input ~ 0
G21
Text GLabel 9650 2800 2    50   Input ~ 0
G3
Text GLabel 9650 2700 2    50   Input ~ 0
G1
Text GLabel 9650 2600 2    50   Input ~ 0
G22
Text GLabel 9650 2500 2    50   Input ~ 0
G23
Text GLabel 9650 2400 2    50   Input ~ 0
GND
Text GLabel 8250 2400 0    50   Input ~ 0
ESP_3.3V
Text GLabel 8250 2500 0    50   Input ~ 0
EN
Text GLabel 4550 3300 3    50   Input ~ 0
GND
Connection ~ 4400 3200
Wire Wire Line
	4400 3300 4900 3300
Wire Wire Line
	4400 3200 4400 3300
Connection ~ 3950 3200
Wire Wire Line
	3950 3200 4400 3200
Wire Wire Line
	3650 3200 3950 3200
Wire Wire Line
	3650 3100 3650 3200
Connection ~ 4400 2900
Wire Wire Line
	4400 2900 4900 2900
Connection ~ 3950 2900
Wire Wire Line
	3950 2900 4400 2900
Wire Wire Line
	3650 2900 3950 2900
Text GLabel 2800 3100 0    50   Input ~ 0
AC_GND
Text GLabel 1800 3200 3    50   Input ~ 0
AC_GND
Wire Wire Line
	2500 2900 2800 2900
Wire Wire Line
	1800 2900 2200 2900
$Comp
L Device:Varistor RV?
U 1 1 624779DE
P 1800 3050
F 0 "RV?" H 1903 3096 50  0000 L CNN
F 1 "B72214S0351K101" H 1903 3005 50  0000 L CNN
F 2 "" V 1730 3050 50  0001 C CNN
F 3 "~" H 1800 3050 50  0001 C CNN
	1    1800 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 624771D3
P 2350 2900
F 0 "R?" V 2143 2900 50  0000 C CNN
F 1 "43F3R0E" V 2234 2900 50  0000 C CNN
F 2 "" V 2280 2900 50  0001 C CNN
F 3 "~" H 2350 2900 50  0001 C CNN
	1    2350 2900
	0    1    1    0   
$EndComp
$Comp
L Device:CP C?
U 1 1 62473C35
P 4400 3050
F 0 "C?" H 4518 3096 50  0000 L CNN
F 1 "860010472002" H 4150 3300 50  0000 L CNN
F 2 "" H 4438 2900 50  0001 C CNN
F 3 "~" H 4400 3050 50  0001 C CNN
	1    4400 3050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 624736AA
P 3950 3050
F 0 "C?" H 4065 3096 50  0000 L CNN
F 1 "CL21B105KBFNNNE" H 3600 2750 50  0000 L CNN
F 2 "" H 3988 2900 50  0001 C CNN
F 3 "~" H 3950 3050 50  0001 C CNN
	1    3950 3050
	1    0    0    -1  
$EndComp
$Comp
L pspice:DIODE D?
U 1 1 62472A59
P 4900 3100
F 0 "D?" V 4946 2972 50  0000 R CNN
F 1 "SMBJ20A" V 4855 2972 50  0000 R CNN
F 2 "" H 4900 3100 50  0001 C CNN
F 3 "~" H 4900 3100 50  0001 C CNN
	1    4900 3100
	0    -1   -1   0   
$EndComp
$Comp
L final:esp32_dev U?
U 1 1 624B406E
P 8950 3200
F 0 "U?" H 8950 4315 50  0000 C CNN
F 1 "esp32_dev" H 8950 4224 50  0000 C CNN
F 2 "" H 9150 3200 50  0001 C CNN
F 3 "" H 9150 3200 50  0001 C CNN
	1    8950 3200
	1    0    0    -1  
$EndComp
$Comp
L final:PSK-20D-12 U?
U 1 1 624B536E
P 3250 3850
F 0 "U?" H 3225 5065 50  0000 C CNN
F 1 "PSK-20D-12" H 3225 4974 50  0000 C CNN
F 2 "" H 3250 4700 50  0001 C CNN
F 3 "" H 3250 4700 50  0001 C CNN
	1    3250 3850
	1    0    0    -1  
$EndComp
$Comp
L final:A4988 SD?
U 1 1 624B589C
P 2800 5400
F 0 "SD?" H 1950 6765 50  0000 C CNN
F 1 "A4988" H 1950 6674 50  0000 C CNN
F 2 "" H 1950 6800 50  0001 C CNN
F 3 "" H 1950 6800 50  0001 C CNN
	1    2800 5400
	1    0    0    -1  
$EndComp
$Comp
L final:L2293QTR U?
U 1 1 624BEB08
P 3100 5650
F 0 "U?" H 4100 6037 60  0000 C CNN
F 1 "L2293QTR" H 4100 5931 60  0000 C CNN
F 2 "VFQFPN32L_5X5X1_STM" H 4100 5890 60  0001 C CNN
F 3 "" H 3100 5650 60  0000 C CNN
	1    3100 5650
	1    0    0    -1  
$EndComp
$Comp
L final:ZLDO1117G50TA VREG?
U 1 1 624C06B6
P 6100 1900
F 0 "VREG?" H 6033 1925 50  0000 C CNN
F 1 "ZLDO1117G50TA" H 6033 1834 50  0000 C CNN
F 2 "" H 5950 1800 50  0001 C CNN
F 3 "" H 5950 1800 50  0001 C CNN
	1    6100 1900
	1    0    0    -1  
$EndComp
$Comp
L final:SN74LVC2G06DCKR U?
U 1 1 624C0EE2
P 2200 6150
F 0 "U?" H 2250 6475 50  0000 C CNN
F 1 "SN74LVC2G06DCKR" H 2250 6384 50  0000 C CNN
F 2 "" H 2250 6250 50  0001 C CNN
F 3 "" H 2250 6250 50  0001 C CNN
	1    2200 6150
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male S7
U 1 1 624C5830
P 2600 4700
F 0 "S7" H 2572 4582 50  0000 R CNN
F 1 "Conn_01x04_Male" H 2572 4673 50  0000 R CNN
F 2 "" H 2600 4700 50  0001 C CNN
F 3 "~" H 2600 4700 50  0001 C CNN
	1    2600 4700
	-1   0    0    1   
$EndComp
Text GLabel 3800 2900 1    50   Input ~ 0
12V
Text GLabel 2400 4300 2    50   Input ~ 0
12V
Text GLabel 2400 4400 2    50   Input ~ 0
GND
Text GLabel 2400 4900 2    50   Input ~ 0
3.3V
Text GLabel 2400 5000 2    50   Input ~ 0
GND
Text GLabel 6200 2100 2    50   Input ~ 0
12V
Text GLabel 6200 2200 2    50   Input ~ 0
5V
Text GLabel 6200 2300 2    50   Input ~ 0
GND
Text GLabel 1900 6150 0    50   Input ~ 0
GND
Text GLabel 2600 6150 2    50   Input ~ 0
3.3V
Text GLabel 3100 6450 0    50   Input ~ 0
GND
Wire Wire Line
	1500 4700 1500 4800
$Comp
L final:A4988 SD?
U 1 1 624DC0FA
P 4850 5400
F 0 "SD?" H 4000 6765 50  0000 C CNN
F 1 "A4988" H 4000 6674 50  0000 C CNN
F 2 "" H 4000 6800 50  0001 C CNN
F 3 "" H 4000 6800 50  0001 C CNN
	1    4850 5400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male S8
U 1 1 624DC100
P 4650 4700
F 0 "S8" H 4622 4582 50  0000 R CNN
F 1 "Conn_01x04_Male" H 4622 4673 50  0000 R CNN
F 2 "" H 4650 4700 50  0001 C CNN
F 3 "~" H 4650 4700 50  0001 C CNN
	1    4650 4700
	-1   0    0    1   
$EndComp
Text GLabel 4450 4300 2    50   Input ~ 0
12V
Text GLabel 4450 4400 2    50   Input ~ 0
GND
Text GLabel 4450 4900 2    50   Input ~ 0
3.3V
Text GLabel 4450 5000 2    50   Input ~ 0
GND
Wire Wire Line
	3550 4700 3550 4800
$Comp
L final:A4988 SD?
U 1 1 624DDD5C
P 7000 5400
F 0 "SD?" H 6150 6765 50  0000 C CNN
F 1 "A4988" H 6150 6674 50  0000 C CNN
F 2 "" H 6150 6800 50  0001 C CNN
F 3 "" H 6150 6800 50  0001 C CNN
	1    7000 5400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x04_Male S9
U 1 1 624DDD62
P 6800 4700
F 0 "S9" H 6772 4582 50  0000 R CNN
F 1 "Conn_01x04_Male" H 6772 4673 50  0000 R CNN
F 2 "" H 6800 4700 50  0001 C CNN
F 3 "~" H 6800 4700 50  0001 C CNN
	1    6800 4700
	-1   0    0    1   
$EndComp
Text GLabel 6600 4300 2    50   Input ~ 0
12V
Text GLabel 6600 4400 2    50   Input ~ 0
GND
Text GLabel 6600 4900 2    50   Input ~ 0
3.3V
Text GLabel 6600 5000 2    50   Input ~ 0
GND
Wire Wire Line
	5700 4700 5700 4800
Text GLabel 1500 4900 0    50   Input ~ 0
G32
Text GLabel 1500 5000 0    50   Input ~ 0
G33
Text GLabel 3550 4900 0    50   Input ~ 0
G26
Text GLabel 3550 5000 0    50   Input ~ 0
G27
Text GLabel 5700 4900 0    50   Input ~ 0
G23
Text GLabel 5700 5000 0    50   Input ~ 0
G25
$Comp
L Connector:Conn_01x03_Female E10
U 1 1 624FA7B5
P 8850 4900
F 0 "E10" H 8878 4926 50  0000 L CNN
F 1 "Conn_01x03_Female" H 8878 4835 50  0000 L CNN
F 2 "" H 8850 4900 50  0001 C CNN
F 3 "~" H 8850 4900 50  0001 C CNN
	1    8850 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 624FC7D2
P 8400 4800
F 0 "R?" V 8193 4800 50  0000 C CNN
F 1 "10K" V 8284 4800 50  0000 C CNN
F 2 "" V 8330 4800 50  0001 C CNN
F 3 "~" H 8400 4800 50  0001 C CNN
	1    8400 4800
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 624FD2E6
P 8400 5000
F 0 "R?" V 8600 5000 50  0000 C CNN
F 1 "10K" V 8500 5000 50  0000 C CNN
F 2 "" V 8330 5000 50  0001 C CNN
F 3 "~" H 8400 5000 50  0001 C CNN
	1    8400 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	8550 4800 8650 4800
Wire Wire Line
	8550 5000 8650 5000
Text GLabel 8650 4900 0    50   Input ~ 0
GND
Text GLabel 8250 4800 0    50   Input ~ 0
3.3V
Text GLabel 8250 5000 0    50   Input ~ 0
3.3V
Text GLabel 8600 4800 1    50   Input ~ 0
G4
Text GLabel 8600 5000 3    50   Input ~ 0
G5
$Comp
L Connector:Conn_01x03_Female E11
U 1 1 6250B299
P 10550 4900
F 0 "E11" H 10578 4926 50  0000 L CNN
F 1 "Conn_01x03_Female" H 10578 4835 50  0000 L CNN
F 2 "" H 10550 4900 50  0001 C CNN
F 3 "~" H 10550 4900 50  0001 C CNN
	1    10550 4900
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6250B29F
P 10100 4800
F 0 "R?" V 9893 4800 50  0000 C CNN
F 1 "10K" V 9984 4800 50  0000 C CNN
F 2 "" V 10030 4800 50  0001 C CNN
F 3 "~" H 10100 4800 50  0001 C CNN
	1    10100 4800
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 6250B2A5
P 10100 5000
F 0 "R?" V 10300 5000 50  0000 C CNN
F 1 "10K" V 10200 5000 50  0000 C CNN
F 2 "" V 10030 5000 50  0001 C CNN
F 3 "~" H 10100 5000 50  0001 C CNN
	1    10100 5000
	0    1    1    0   
$EndComp
Wire Wire Line
	10250 4800 10350 4800
Wire Wire Line
	10250 5000 10350 5000
Text GLabel 10350 4900 0    50   Input ~ 0
GND
Text GLabel 9950 4800 0    50   Input ~ 0
3.3V
Text GLabel 9950 5000 0    50   Input ~ 0
3.3V
Text GLabel 10300 4800 1    50   Input ~ 0
G13
Text GLabel 10300 5000 3    50   Input ~ 0
G39
$Comp
L Connector:Conn_01x02_Female B2
U 1 1 6250DA3A
P 8850 5850
F 0 "B2" H 8878 5826 50  0000 L CNN
F 1 "Conn_01x02_Female" H 8878 5735 50  0000 L CNN
F 2 "" H 8850 5850 50  0001 C CNN
F 3 "~" H 8850 5850 50  0001 C CNN
	1    8850 5850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6250E6BF
P 8400 5950
F 0 "R?" V 8600 5950 50  0000 C CNN
F 1 "10K" V 8500 5950 50  0000 C CNN
F 2 "" V 8330 5950 50  0001 C CNN
F 3 "~" H 8400 5950 50  0001 C CNN
	1    8400 5950
	0    1    1    0   
$EndComp
Wire Wire Line
	8550 5950 8650 5950
Text GLabel 8250 5950 0    50   Input ~ 0
3.3V
Text GLabel 8650 5850 0    50   Input ~ 0
GND
Text GLabel 8600 5950 3    50   Input ~ 0
G34
$Comp
L Connector:Conn_01x02_Female B3
U 1 1 62511485
P 8850 5350
F 0 "B3" H 8878 5326 50  0000 L CNN
F 1 "Conn_01x02_Female" H 8878 5235 50  0000 L CNN
F 2 "" H 8850 5350 50  0001 C CNN
F 3 "~" H 8850 5350 50  0001 C CNN
	1    8850 5350
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6251148B
P 8400 5450
F 0 "R?" V 8600 5450 50  0000 C CNN
F 1 "10K" V 8500 5450 50  0000 C CNN
F 2 "" V 8330 5450 50  0001 C CNN
F 3 "~" H 8400 5450 50  0001 C CNN
	1    8400 5450
	0    1    1    0   
$EndComp
Wire Wire Line
	8550 5450 8650 5450
Text GLabel 8250 5450 0    50   Input ~ 0
3.3V
Text GLabel 8650 5350 0    50   Input ~ 0
GND
Text GLabel 8600 5450 3    50   Input ~ 0
G35
$Comp
L Connector:Conn_01x02_Female B4
U 1 1 62511D41
P 8900 6300
F 0 "B4" H 8928 6276 50  0000 L CNN
F 1 "Conn_01x02_Female" H 8928 6185 50  0000 L CNN
F 2 "" H 8900 6300 50  0001 C CNN
F 3 "~" H 8900 6300 50  0001 C CNN
	1    8900 6300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 62511D47
P 8450 6400
F 0 "R?" V 8650 6400 50  0000 C CNN
F 1 "10K" V 8550 6400 50  0000 C CNN
F 2 "" V 8380 6400 50  0001 C CNN
F 3 "~" H 8450 6400 50  0001 C CNN
	1    8450 6400
	0    1    1    0   
$EndComp
Wire Wire Line
	8600 6400 8700 6400
Text GLabel 8300 6400 0    50   Input ~ 0
3.3V
Text GLabel 8700 6300 0    50   Input ~ 0
GND
Text GLabel 8650 6400 3    50   Input ~ 0
G36
Text GLabel 5100 5650 2    50   Input ~ 0
GND
Text GLabel 5100 6050 2    50   Input ~ 0
GND
Text GLabel 5100 6450 2    50   Input ~ 0
GND
Text GLabel 5100 7150 2    50   Input ~ 0
GND
Text GLabel 5100 6150 2    50   Input ~ 0
3.3V
Text GLabel 3100 6750 0    50   Input ~ 0
12V
Text GLabel 3100 6850 0    50   Input ~ 0
12V
Text GLabel 1900 6050 0    50   Input ~ 0
G22
Text GLabel 2600 6250 2    50   Input ~ 0
~G22
Text GLabel 1900 6250 0    50   Input ~ 0
G19
Text GLabel 2600 6050 2    50   Input ~ 0
~G19
Text GLabel 5100 5850 2    50   Input ~ 0
G22
$EndSCHEMATC
