EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A2 23386 16535
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
AC_N
Text GLabel 1800 3200 3    50   Input ~ 0
AC_N
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
F 1 "10uF" H 4300 3300 50  0000 L CNN
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
F 1 "1uF" H 3900 2800 50  0000 L CNN
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
Text GLabel 4200 1100 0    50   Input ~ 0
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
Text GLabel 10300 4800 1    50   Input ~ 0
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
Text GLabel 3100 6650 0    50   Input ~ 0
~G22
Text GLabel 3100 7050 0    50   Input ~ 0
G19
Text GLabel 5100 6250 2    50   Input ~ 0
~G19
$Comp
L Connector:Conn_01x02_Female PWM5
U 1 1 6252DCF2
P 6250 5950
F 0 "PWM5" H 6278 5926 50  0000 L CNN
F 1 "Conn_01x02_Female" H 6278 5835 50  0000 L CNN
F 2 "" H 6250 5950 50  0001 C CNN
F 3 "~" H 6250 5950 50  0001 C CNN
	1    6250 5950
	1    0    0    -1  
$EndComp
Text GLabel 5100 5750 2    50   Input ~ 0
PWM1_2
Text GLabel 3100 6550 0    50   Input ~ 0
PWM1_2
Text GLabel 6050 5950 0    50   Input ~ 0
PWM1_1
Text GLabel 6050 6050 0    50   Input ~ 0
PWM1_2
Text GLabel 3100 7150 0    50   Input ~ 0
PWM2_1
Text GLabel 5100 6350 2    50   Input ~ 0
PWM2_2
$Comp
L Connector:Conn_01x02_Female PWM6
U 1 1 62531B03
P 6250 6350
F 0 "PWM6" H 6278 6326 50  0000 L CNN
F 1 "Conn_01x02_Female" H 6278 6235 50  0000 L CNN
F 2 "" H 6250 6350 50  0001 C CNN
F 3 "~" H 6250 6350 50  0001 C CNN
	1    6250 6350
	1    0    0    -1  
$EndComp
Text GLabel 6050 6350 0    50   Input ~ 0
PWM2_1
Text GLabel 6050 6450 0    50   Input ~ 0
PWM2_2
$Comp
L Relay:SANYOU_SRD_Form_A K?
U 1 1 625529C5
P 2500 1400
F 0 "K?" H 2830 1446 50  0000 L CNN
F 1 "SRD-S-112DM(F-11)" H 2830 1355 50  0000 L CNN
F 2 "Relay_THT:Relay_SPST_SANYOU_SRD_Series_Form_A" H 2850 1350 50  0001 L CNN
F 3 "http://www.sanyourelay.ca/public/products/pdf/SRD.pdf" H 2500 1400 50  0001 C CNN
	1    2500 1400
	1    0    0    -1  
$EndComp
Text GLabel 2700 1100 1    50   Input ~ 0
AC_L
Text GLabel 2700 1700 3    50   Input ~ 0
AC_L_OUT
Text GLabel 1450 2900 0    50   Input ~ 0
AC_L
Wire Wire Line
	1450 2900 1800 2900
Connection ~ 1800 2900
$Comp
L pspice:DIODE D?
U 1 1 62569D3B
P 1450 1400
F 0 "D?" V 1496 1272 50  0000 R CNN
F 1 "DIODE" V 1405 1272 50  0000 R CNN
F 2 "" H 1450 1400 50  0001 C CNN
F 3 "~" H 1450 1400 50  0001 C CNN
	1    1450 1400
	0    -1   -1   0   
$EndComp
Text GLabel 5100 5950 2    50   Input ~ 0
G21
Text GLabel 3100 6950 0    50   Input ~ 0
G18
Wire Wire Line
	2300 1100 1450 1100
Wire Wire Line
	1450 1100 1450 1200
Wire Wire Line
	2300 1700 1450 1700
Wire Wire Line
	1450 1700 1450 1600
Text GLabel 2300 1100 1    50   Input ~ 0
12V
$Comp
L Device:Q_NMOS_DGS Q?
U 1 1 6259E2F7
P 2200 2100
F 0 "Q?" H 2404 2146 50  0000 L CNN
F 1 "PJE8408_R1_00001" H 2404 2055 50  0000 L CNN
F 2 "" H 2400 2200 50  0001 C CNN
F 3 "~" H 2200 2100 50  0001 C CNN
	1    2200 2100
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 1700 2300 1900
Connection ~ 2300 1700
Text GLabel 2300 2300 3    50   Input ~ 0
GND
Text GLabel 4200 1600 0    50   Input ~ 0
G16
$Comp
L Device:R R?
U 1 1 625C96FC
P 1900 2250
F 0 "R?" H 1970 2296 50  0000 L CNN
F 1 "10k" H 1970 2205 50  0000 L CNN
F 2 "" V 1830 2250 50  0001 C CNN
F 3 "~" H 1900 2250 50  0001 C CNN
	1    1900 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 625CBBD8
P 1600 2100
F 0 "R?" V 1807 2100 50  0000 C CNN
F 1 "1k" V 1716 2100 50  0000 C CNN
F 2 "" V 1530 2100 50  0001 C CNN
F 3 "~" H 1600 2100 50  0001 C CNN
	1    1600 2100
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1750 2100 1900 2100
Connection ~ 1900 2100
Wire Wire Line
	1900 2100 2000 2100
Wire Wire Line
	1450 2100 1350 2100
Text GLabel 1900 2400 3    50   Input ~ 0
GND
$Comp
L Device:LED D?
U 1 1 62608137
P 5900 3100
F 0 "D?" V 5939 2983 50  0000 R CNN
F 1 "CLM3C-MKW-CWAXB133" H 6350 3250 50  0000 R CNN
F 2 "" H 5900 3100 50  0001 C CNN
F 3 "~" H 5900 3100 50  0001 C CNN
	1    5900 3100
	0    -1   -1   0   
$EndComp
$Comp
L Device:LED D?
U 1 1 62608DAF
P 6550 3500
F 0 "D?" V 6589 3383 50  0000 R CNN
F 1 "B1931UD--05D000314U1930" H 7150 3650 50  0000 R CNN
F 2 "" H 6550 3500 50  0001 C CNN
F 3 "~" H 6550 3500 50  0001 C CNN
	1    6550 3500
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 62610201
P 5900 2800
F 0 "R?" H 5970 2846 50  0000 L CNN
F 1 "440" H 5970 2755 50  0000 L CNN
F 2 "" V 5830 2800 50  0001 C CNN
F 3 "~" H 5900 2800 50  0001 C CNN
	1    5900 2800
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 6261A511
P 6550 3200
F 0 "R?" H 6620 3246 50  0000 L CNN
F 1 "600" H 6620 3155 50  0000 L CNN
F 2 "" V 6480 3200 50  0001 C CNN
F 3 "~" H 6550 3200 50  0001 C CNN
	1    6550 3200
	1    0    0    -1  
$EndComp
Text GLabel 5900 3250 3    50   Input ~ 0
GND
Text GLabel 6550 3650 3    50   Input ~ 0
GND
Text GLabel 6550 3050 1    50   Input ~ 0
5V
Text GLabel 5900 2650 1    50   Input ~ 0
12V
$Comp
L 74xx:74HC595 U?
U 1 1 62676F85
P 4600 1500
F 0 "U?" H 4600 2281 50  0000 C CNN
F 1 "SN74AHCT595N" H 4600 2190 50  0000 C CNN
F 2 "" H 4600 1500 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/sn74hc595.pdf" H 4600 1500 50  0001 C CNN
	1    4600 1500
	1    0    0    -1  
$EndComp
Text GLabel 4200 1300 0    50   Input ~ 0
G17
Text GLabel 4200 1700 0    50   Input ~ 0
GND
Text GLabel 4200 1400 0    50   Input ~ 0
5V
Text GLabel 4600 900  1    50   Input ~ 0
5V
Text GLabel 4600 2200 3    50   Input ~ 0
GND
Text GLabel 5000 1100 2    50   Input ~ 0
QA
Text GLabel 5000 1200 2    50   Input ~ 0
QB
Text GLabel 5000 1300 2    50   Input ~ 0
QC
Text GLabel 5000 1400 2    50   Input ~ 0
QD
Text GLabel 5000 1500 2    50   Input ~ 0
QE
Text GLabel 5000 1600 2    50   Input ~ 0
QF
Text GLabel 5000 1700 2    50   Input ~ 0
QG
Text GLabel 5000 1800 2    50   Input ~ 0
QH
$Comp
L Device:LED D?
U 1 1 627D516D
P 17000 2450
F 0 "D?" V 17039 2333 50  0000 R CNN
F 1 "THT_LED" V 16948 2333 50  0000 R CNN
F 2 "" H 17000 2450 50  0001 C CNN
F 3 "~" H 17000 2450 50  0001 C CNN
	1    17000 2450
	0    -1   -1   0   
$EndComp
$Comp
L Device:R R?
U 1 1 627E674B
P 17000 2150
F 0 "R?" H 17070 2196 50  0000 L CNN
F 1 "440" H 17070 2105 50  0000 L CNN
F 2 "" V 16930 2150 50  0001 C CNN
F 3 "~" H 17000 2150 50  0001 C CNN
	1    17000 2150
	1    0    0    -1  
$EndComp
Text GLabel 17000 2000 1    50   Input ~ 0
QH
Text GLabel 17000 2600 3    50   Input ~ 0
GND
$Comp
L Connector:Conn_01x03_Female J?
U 1 1 62857183
P 6700 850
F 0 "J?" V 6638 662 50  0000 R CNN
F 1 "AC_IN" V 6547 662 50  0000 R CNN
F 2 "" H 6700 850 50  0001 C CNN
F 3 "~" H 6700 850 50  0001 C CNN
	1    6700 850 
	0    -1   -1   0   
$EndComp
Text GLabel 6600 1050 3    50   Input ~ 0
AC_L
Text GLabel 6700 1050 3    50   Input ~ 0
AC_N
Text GLabel 6800 1050 3    50   Input ~ 0
GND
$Comp
L Connector:Conn_01x03_Female J?
U 1 1 628613EF
P 7500 850
F 0 "J?" V 7438 662 50  0000 R CNN
F 1 "AC_OUT" V 7347 662 50  0000 R CNN
F 2 "" H 7500 850 50  0001 C CNN
F 3 "~" H 7500 850 50  0001 C CNN
	1    7500 850 
	0    -1   -1   0   
$EndComp
Text GLabel 7400 1050 3    50   Input ~ 0
AC_L_OUT
Text GLabel 7500 1050 3    50   Input ~ 0
AC_N
Text GLabel 7600 1050 3    50   Input ~ 0
GND
$Comp
L Connector:Barrel_Jack J?
U 1 1 628EB8AE
P 1600 7150
F 0 "J?" H 1657 7475 50  0000 C CNN
F 1 "54-00164" H 1657 7384 50  0000 C CNN
F 2 "" H 1650 7110 50  0001 C CNN
F 3 "~" H 1650 7110 50  0001 C CNN
	1    1600 7150
	1    0    0    -1  
$EndComp
Text GLabel 1900 7050 2    50   Input ~ 0
12V
Text GLabel 1900 7250 2    50   Input ~ 0
GND
Text GLabel 1350 2100 0    50   Input ~ 0
QA
Text GLabel 11100 2250 0    50   Input ~ 0
QA
$Comp
L Connector:Conn_01x02_Female PWSW?
U 1 1 62794DC4
P 13050 1250
F 0 "PWSW?" H 13078 1226 50  0000 L CNN
F 1 "SW" H 13078 1135 50  0000 L CNN
F 2 "" H 13050 1250 50  0001 C CNN
F 3 "~" H 13050 1250 50  0001 C CNN
	1    13050 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_DGS Q?
U 1 1 62A82E34
P 11750 2350
F 0 "Q?" H 11954 2396 50  0000 L CNN
F 1 "PJE8408_R1_00001" H 11100 2500 50  0000 L CNN
F 2 "" H 11950 2450 50  0001 C CNN
F 3 "~" H 11750 2350 50  0001 C CNN
	1    11750 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	11100 2250 11200 2250
$Comp
L final:EE2-NU U?
U 1 1 62A943E0
P 12200 1650
F 0 "U?" H 12225 2015 50  0000 C CNN
F 1 "EE2-NU" H 12225 1924 50  0000 C CNN
F 2 "" H 12250 1250 50  0001 C CNN
F 3 "" H 12250 1250 50  0001 C CNN
	1    12200 1650
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 62AD4CFE
P 11200 2400
F 0 "R?" H 11270 2446 50  0000 L CNN
F 1 "10k" H 11270 2355 50  0000 L CNN
F 2 "" V 11130 2400 50  0001 C CNN
F 3 "~" H 11200 2400 50  0001 C CNN
	1    11200 2400
	1    0    0    -1  
$EndComp
Connection ~ 11200 2250
Text GLabel 11200 2550 3    50   Input ~ 0
GND
Text GLabel 11850 2550 3    50   Input ~ 0
GND
Wire Wire Line
	11200 2250 11550 2250
Wire Wire Line
	11550 2250 11550 2350
Wire Wire Line
	11850 2150 11850 2100
$Comp
L pspice:DIODE D?
U 1 1 62ADFB85
P 11450 1650
F 0 "D?" V 11496 1522 50  0000 R CNN
F 1 "DIODE" V 11405 1522 50  0000 R CNN
F 2 "" H 11450 1650 50  0001 C CNN
F 3 "~" H 11450 1650 50  0001 C CNN
	1    11450 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	11850 2100 11450 2100
Wire Wire Line
	11450 2100 11450 1850
Connection ~ 11850 2100
Wire Wire Line
	11850 2100 11850 2050
Wire Wire Line
	11450 1450 11450 1200
Wire Wire Line
	11450 1200 11850 1200
Wire Wire Line
	11850 1200 11850 1300
Wire Wire Line
	12150 1000 12400 1000
Text GLabel 12400 800  1    50   Input ~ 0
3.3V
$Comp
L Device:Jumper_NO_Small JP?
U 1 1 62794DE9
P 12400 900
F 0 "JP?" V 12354 948 50  0000 L CNN
F 1 "12V" V 12445 948 50  0000 L CNN
F 2 "" H 12400 900 50  0001 C CNN
F 3 "~" H 12400 900 50  0001 C CNN
	1    12400 900 
	0    1    1    0   
$EndComp
Text GLabel 12150 800  1    50   Input ~ 0
12V
Text GLabel 11900 800  1    50   Input ~ 0
5V
Wire Wire Line
	11900 1000 12000 1000
Connection ~ 12150 1000
$Comp
L Device:Jumper_NO_Small JP?
U 1 1 62794DDB
P 12150 900
F 0 "JP?" V 12104 948 50  0000 L CNN
F 1 "12V" V 12195 948 50  0000 L CNN
F 2 "" H 12150 900 50  0001 C CNN
F 3 "~" H 12150 900 50  0001 C CNN
	1    12150 900 
	0    1    1    0   
$EndComp
$Comp
L Device:Jumper_NO_Small JP?
U 1 1 62794DD5
P 11900 900
F 0 "JP?" V 11854 948 50  0000 L CNN
F 1 "5V" V 11945 948 50  0000 L CNN
F 2 "" H 11900 900 50  0001 C CNN
F 3 "~" H 11900 900 50  0001 C CNN
	1    11900 900 
	0    1    1    0   
$EndComp
Text GLabel 11700 1200 1    50   Input ~ 0
5V
Wire Wire Line
	12000 1000 12000 1300
Connection ~ 12000 1000
Wire Wire Line
	12000 1000 12150 1000
Wire Wire Line
	12300 1300 12450 1300
Wire Wire Line
	12450 1300 12450 1250
Wire Wire Line
	12450 1250 12850 1250
Text GLabel 12850 1350 0    50   Input ~ 0
GND
NoConn ~ 12150 1300
NoConn ~ 12000 2050
NoConn ~ 12150 2050
NoConn ~ 12300 2050
Text GLabel 13350 2250 0    50   Input ~ 0
QB
$Comp
L Connector:Conn_01x02_Female PWSW?
U 1 1 62B08122
P 15300 1250
F 0 "PWSW?" H 15328 1226 50  0000 L CNN
F 1 "SW" H 15328 1135 50  0000 L CNN
F 2 "" H 15300 1250 50  0001 C CNN
F 3 "~" H 15300 1250 50  0001 C CNN
	1    15300 1250
	1    0    0    -1  
$EndComp
$Comp
L Device:Q_NMOS_DGS Q?
U 1 1 62B08128
P 14000 2350
F 0 "Q?" H 14204 2396 50  0000 L CNN
F 1 "PJE8408_R1_00001" H 13350 2500 50  0000 L CNN
F 2 "" H 14200 2450 50  0001 C CNN
F 3 "~" H 14000 2350 50  0001 C CNN
	1    14000 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	13350 2250 13450 2250
$Comp
L final:EE2-NU U?
U 1 1 62B0812F
P 14450 1650
F 0 "U?" H 14475 2015 50  0000 C CNN
F 1 "EE2-NU" H 14475 1924 50  0000 C CNN
F 2 "" H 14500 1250 50  0001 C CNN
F 3 "" H 14500 1250 50  0001 C CNN
	1    14450 1650
	0    1    1    0   
$EndComp
$Comp
L Device:R R?
U 1 1 62B08135
P 13450 2400
F 0 "R?" H 13520 2446 50  0000 L CNN
F 1 "10k" H 13520 2355 50  0000 L CNN
F 2 "" V 13380 2400 50  0001 C CNN
F 3 "~" H 13450 2400 50  0001 C CNN
	1    13450 2400
	1    0    0    -1  
$EndComp
Connection ~ 13450 2250
Text GLabel 13450 2550 3    50   Input ~ 0
GND
Text GLabel 14100 2550 3    50   Input ~ 0
GND
Wire Wire Line
	13450 2250 13800 2250
Wire Wire Line
	13800 2250 13800 2350
Wire Wire Line
	14100 2150 14100 2100
$Comp
L pspice:DIODE D?
U 1 1 62B08141
P 13700 1650
F 0 "D?" V 13746 1522 50  0000 R CNN
F 1 "DIODE" V 13655 1522 50  0000 R CNN
F 2 "" H 13700 1650 50  0001 C CNN
F 3 "~" H 13700 1650 50  0001 C CNN
	1    13700 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	14100 2100 13700 2100
Wire Wire Line
	13700 2100 13700 1850
Connection ~ 14100 2100
Wire Wire Line
	14100 2100 14100 2050
Wire Wire Line
	13700 1450 13700 1200
Wire Wire Line
	13700 1200 14100 1200
Wire Wire Line
	14100 1200 14100 1300
Wire Wire Line
	14400 1000 14650 1000
Text GLabel 14650 800  1    50   Input ~ 0
3.3V
$Comp
L Device:Jumper_NO_Small JP?
U 1 1 62B08150
P 14650 900
F 0 "JP?" V 14604 948 50  0000 L CNN
F 1 "12V" V 14695 948 50  0000 L CNN
F 2 "" H 14650 900 50  0001 C CNN
F 3 "~" H 14650 900 50  0001 C CNN
	1    14650 900 
	0    1    1    0   
$EndComp
Text GLabel 14400 800  1    50   Input ~ 0
12V
Text GLabel 14150 800  1    50   Input ~ 0
5V
Wire Wire Line
	14150 1000 14250 1000
Connection ~ 14400 1000
$Comp
L Device:Jumper_NO_Small JP?
U 1 1 62B0815A
P 14400 900
F 0 "JP?" V 14354 948 50  0000 L CNN
F 1 "12V" V 14445 948 50  0000 L CNN
F 2 "" H 14400 900 50  0001 C CNN
F 3 "~" H 14400 900 50  0001 C CNN
	1    14400 900 
	0    1    1    0   
$EndComp
$Comp
L Device:Jumper_NO_Small JP?
U 1 1 62B08160
P 14150 900
F 0 "JP?" V 14104 948 50  0000 L CNN
F 1 "5V" V 14195 948 50  0000 L CNN
F 2 "" H 14150 900 50  0001 C CNN
F 3 "~" H 14150 900 50  0001 C CNN
	1    14150 900 
	0    1    1    0   
$EndComp
Text GLabel 13950 1200 1    50   Input ~ 0
5V
Wire Wire Line
	14250 1000 14250 1300
Connection ~ 14250 1000
Wire Wire Line
	14250 1000 14400 1000
Wire Wire Line
	14550 1300 14700 1300
Wire Wire Line
	14700 1300 14700 1250
Wire Wire Line
	14700 1250 15100 1250
Text GLabel 15100 1350 0    50   Input ~ 0
GND
NoConn ~ 14400 1300
NoConn ~ 14250 2050
NoConn ~ 14400 2050
NoConn ~ 14550 2050
$Comp
L Connector:Conn_01x02_Female SW?
U 1 1 62B12B4F
P 17450 1250
F 0 "SW?" H 17478 1226 50  0000 L CNN
F 1 "SW" H 17478 1135 50  0000 L CNN
F 2 "" H 17450 1250 50  0001 C CNN
F 3 "~" H 17450 1250 50  0001 C CNN
	1    17450 1250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female SW?
U 1 1 62B13C3E
P 18100 900
F 0 "SW?" H 18128 876 50  0000 L CNN
F 1 "SW" H 18128 785 50  0000 L CNN
F 2 "" H 18100 900 50  0001 C CNN
F 3 "~" H 18100 900 50  0001 C CNN
	1    18100 900 
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female SW?
U 1 1 62B14D2C
P 18100 1250
F 0 "SW?" H 18128 1226 50  0000 L CNN
F 1 "SW" H 18128 1135 50  0000 L CNN
F 2 "" H 18100 1250 50  0001 C CNN
F 3 "~" H 18100 1250 50  0001 C CNN
	1    18100 1250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female SW?
U 1 1 62B15DBD
P 18100 1600
F 0 "SW?" H 18128 1576 50  0000 L CNN
F 1 "SW" H 18128 1485 50  0000 L CNN
F 2 "" H 18100 1600 50  0001 C CNN
F 3 "~" H 18100 1600 50  0001 C CNN
	1    18100 1600
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Female SW?
U 1 1 62B1A105
P 17450 900
F 0 "SW?" H 17478 876 50  0000 L CNN
F 1 "SW" H 17478 785 50  0000 L CNN
F 2 "" H 17450 900 50  0001 C CNN
F 3 "~" H 17450 900 50  0001 C CNN
	1    17450 900 
	1    0    0    -1  
$EndComp
Text GLabel 17250 1000 0    50   Input ~ 0
GND
Text GLabel 17250 1350 0    50   Input ~ 0
GND
Text GLabel 17900 1000 0    50   Input ~ 0
GND
Text GLabel 17900 1350 0    50   Input ~ 0
GND
Text GLabel 17900 1700 0    50   Input ~ 0
GND
Text GLabel 17250 900  0    50   Input ~ 0
QC
Text GLabel 17250 1250 0    50   Input ~ 0
QD
Text GLabel 17900 900  0    50   Input ~ 0
QE
Text GLabel 17900 1250 0    50   Input ~ 0
QF
Text GLabel 17900 1600 0    50   Input ~ 0
QG
NoConn ~ 5700 4300
NoConn ~ 5700 4400
NoConn ~ 5700 4500
NoConn ~ 5700 4600
NoConn ~ 3550 4300
NoConn ~ 3550 4400
NoConn ~ 3550 4500
NoConn ~ 3550 4600
NoConn ~ 1500 4600
NoConn ~ 1500 4500
NoConn ~ 1500 4400
NoConn ~ 1500 4300
Text GLabel 8250 4200 0    50   Input ~ 0
5V
$Comp
L Connector:Conn_01x06_Female J?
U 1 1 62B6C4D3
P 3550 7750
F 0 "J?" H 3578 7726 50  0000 L CNN
F 1 "Backup_If_Motor_driver_dont_work" H 3578 7635 50  0000 L CNN
F 2 "" H 3550 7750 50  0001 C CNN
F 3 "~" H 3550 7750 50  0001 C CNN
	1    3550 7750
	1    0    0    -1  
$EndComp
Text GLabel 3350 7550 0    50   Input ~ 0
G22
Text GLabel 3350 7650 0    50   Input ~ 0
~G22
Text GLabel 3350 7750 0    50   Input ~ 0
G21
Text GLabel 3350 7850 0    50   Input ~ 0
G19
Text GLabel 3350 7950 0    50   Input ~ 0
~G19
Text GLabel 3350 8050 0    50   Input ~ 0
G18
$EndSCHEMATC
