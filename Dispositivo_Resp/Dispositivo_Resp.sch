EESchema Schematic File Version 4
LIBS:Dispositivo_Resp-cache
EELAYER 29 0
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
$Comp
L MCU_Microchip_ATmega:ATmega328P-PU U1
U 1 1 5CCC7040
P 4550 3150
F 0 "U1" H 3906 3196 50  0000 R CNN
F 1 "ATmega328P-PU" H 3906 3105 50  0000 R CNN
F 2 "ATMEGA328-PU:DIL28" H 4550 3150 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 4550 3150 50  0001 C CNN
	1    4550 3150
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal Y1
U 1 1 5CCC9545
P 5700 2600
F 0 "Y1" V 5654 2731 50  0000 L CNN
F 1 "16.00Mhz" V 5745 2731 50  0000 L CNN
F 2 "Crystal:Crystal_HC18-U_Vertical" H 5700 2600 50  0001 C CNN
F 3 "~" H 5700 2600 50  0001 C CNN
	1    5700 2600
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 5CCCB6DB
P 6300 2450
F 0 "C1" V 6048 2450 50  0000 C CNN
F 1 "22nF" V 6139 2450 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.4mm_W2.1mm_P2.50mm" H 6338 2300 50  0001 C CNN
F 3 "~" H 6300 2450 50  0001 C CNN
	1    6300 2450
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 5CCCBDAB
P 6300 2750
F 0 "C2" V 6048 2750 50  0000 C CNN
F 1 "22nF" V 6139 2750 50  0000 C CNN
F 2 "Capacitor_THT:C_Disc_D3.4mm_W2.1mm_P2.50mm" H 6338 2600 50  0001 C CNN
F 3 "~" H 6300 2750 50  0001 C CNN
	1    6300 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	5150 2550 5400 2550
Wire Wire Line
	5400 2550 5400 2450
Wire Wire Line
	5400 2450 5700 2450
Wire Wire Line
	5700 2450 6150 2450
Connection ~ 5700 2450
Wire Wire Line
	5150 2650 5400 2650
Wire Wire Line
	5400 2650 5400 2750
Wire Wire Line
	5400 2750 5700 2750
Wire Wire Line
	6150 2750 5700 2750
Connection ~ 5700 2750
$Comp
L Dispositivo_Resp-rescue:GY-521-GY-521 U2
U 1 1 5CCD31A6
P 9650 3250
F 0 "U2" H 9650 4053 60  0000 C CNN
F 1 "GY-521" H 9650 3947 60  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Horizontal" H 9650 3250 60  0001 C CNN
F 3 "" H 9650 3250 60  0000 C CNN
	1    9650 3250
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4550 5000 6550 5000
Wire Wire Line
	5150 3350 6350 3350
Wire Wire Line
	6350 3350 6350 3150
Wire Wire Line
	9650 2650 9650 1350
Wire Wire Line
	9650 3850 9650 5000
Wire Wire Line
	9050 2450 9050 5000
Wire Wire Line
	6450 2450 9050 2450
Connection ~ 9050 5000
Wire Wire Line
	9050 5000 9650 5000
Wire Wire Line
	8800 2750 8800 5000
Wire Wire Line
	6450 2750 8800 2750
Wire Wire Line
	8800 5000 9050 5000
Wire Wire Line
	4550 1650 4550 1350
Connection ~ 4550 1350
Wire Wire Line
	4550 1350 4650 1350
$Comp
L Device:Battery_Cell BT1
U 1 1 5CD00A39
P 2850 2900
F 0 "BT1" H 2968 2996 50  0000 L CNN
F 1 "3.3V" H 2968 2905 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Horizontal" V 2850 2960 50  0001 C CNN
F 3 "~" V 2850 2960 50  0001 C CNN
	1    2850 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 1350 2850 2550
Wire Wire Line
	2850 3000 2850 3100
Wire Wire Line
	2850 5000 4550 5000
Connection ~ 4550 5000
$Comp
L power:PWR_FLAG #FLG03
U 1 1 5CD0A556
P 2600 3100
F 0 "#FLG03" H 2600 3175 50  0001 C CNN
F 1 "PWR_FLAG" V 2600 3227 50  0000 L CNN
F 2 "" H 2600 3100 50  0001 C CNN
F 3 "~" H 2600 3100 50  0001 C CNN
	1    2600 3100
	0    -1   -1   0   
$EndComp
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5CD0B335
P 2600 2550
F 0 "#FLG01" H 2600 2625 50  0001 C CNN
F 1 "PWR_FLAG" V 2600 2677 50  0000 L CNN
F 2 "" H 2600 2550 50  0001 C CNN
F 3 "~" H 2600 2550 50  0001 C CNN
	1    2600 2550
	0    -1   -1   0   
$EndComp
Wire Wire Line
	2850 1350 4550 1350
Wire Wire Line
	2600 2550 2850 2550
Connection ~ 2850 2550
Wire Wire Line
	2850 2550 2850 2700
Wire Wire Line
	4550 4650 4550 5000
Wire Wire Line
	2600 3100 2850 3100
Connection ~ 2850 3100
Wire Wire Line
	2850 3100 2850 5000
NoConn ~ 10200 3150
NoConn ~ 10200 3250
NoConn ~ 10200 3350
NoConn ~ 9100 3350
Wire Wire Line
	4650 1650 4650 1350
NoConn ~ 5150 3150
NoConn ~ 5150 3050
NoConn ~ 5150 2950
NoConn ~ 5150 2850
NoConn ~ 3950 1950
NoConn ~ 5150 2450
NoConn ~ 5150 2150
NoConn ~ 5150 2050
NoConn ~ 5150 3450
NoConn ~ 5150 3650
NoConn ~ 5150 3750
NoConn ~ 5150 3850
NoConn ~ 5150 4150
NoConn ~ 5150 4250
NoConn ~ 5150 4350
NoConn ~ 5150 1950
$Comp
L Device:LED D1
U 1 1 5CD22164
P 5950 3850
F 0 "D1" H 5943 3595 50  0000 C CNN
F 1 "RED" H 5943 3686 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 5950 3850 50  0001 C CNN
F 3 "~" H 5950 3850 50  0001 C CNN
	1    5950 3850
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D2
U 1 1 5CD23FBF
P 5950 4150
F 0 "D2" H 5943 3895 50  0000 C CNN
F 1 "BLUE" H 5943 3986 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 5950 4150 50  0001 C CNN
F 3 "~" H 5950 4150 50  0001 C CNN
	1    5950 4150
	-1   0    0    1   
$EndComp
Wire Wire Line
	5800 3850 5600 3850
Wire Wire Line
	5600 3850 5600 3950
Wire Wire Line
	5600 3950 5150 3950
Wire Wire Line
	5800 4150 5600 4150
Wire Wire Line
	5600 4150 5600 4050
Wire Wire Line
	5600 4050 5150 4050
$Comp
L Device:R R3
U 1 1 5CD276F3
P 6400 3850
F 0 "R3" V 6193 3850 50  0000 C CNN
F 1 "220" V 6284 3850 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6330 3850 50  0001 C CNN
F 3 "~" H 6400 3850 50  0001 C CNN
	1    6400 3850
	0    1    1    0   
$EndComp
$Comp
L Device:R R4
U 1 1 5CD28923
P 6400 4150
F 0 "R4" V 6193 4150 50  0000 C CNN
F 1 "220" V 6284 4150 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 6330 4150 50  0001 C CNN
F 3 "~" H 6400 4150 50  0001 C CNN
	1    6400 4150
	0    1    1    0   
$EndComp
Wire Wire Line
	6100 3850 6250 3850
Wire Wire Line
	6100 4150 6250 4150
Wire Wire Line
	6550 4150 6550 5000
Connection ~ 6550 5000
Wire Wire Line
	6550 5000 6750 5000
Wire Wire Line
	6550 3850 6750 3850
Wire Wire Line
	6750 3850 6750 5000
Connection ~ 4650 1350
Wire Wire Line
	4650 1350 6675 1350
Text Label 7475 1675 0    50   ~ 0
STATE
Text Label 7475 1775 0    50   ~ 0
RXD
Text Label 7475 1875 0    50   ~ 0
TXD
Text Label 7475 1975 0    50   ~ 0
GND
Text Label 7475 2075 0    50   ~ 0
VCC
Text Label 7475 2175 0    50   ~ 0
EN
Wire Wire Line
	7150 2075 6675 2075
Wire Wire Line
	6675 2075 6675 1350
Connection ~ 6675 1350
Wire Wire Line
	6675 1350 9650 1350
Wire Wire Line
	7150 1975 6950 1975
Wire Wire Line
	6950 1975 6950 2900
Wire Wire Line
	6950 2900 7925 2900
NoConn ~ 7150 2175
NoConn ~ 7150 1675
$Comp
L Connector_Generic:Conn_01x06 J1
U 1 1 5CD3327E
P 7350 1875
F 0 "J1" H 7150 2275 50  0000 L CNN
F 1 "Conn_01x06" H 6975 2200 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Horizontal" H 7350 1875 50  0001 C CNN
F 3 "~" H 7350 1875 50  0001 C CNN
	1    7350 1875
	1    0    0    -1  
$EndComp
Wire Wire Line
	7150 1875 5350 1875
Wire Wire Line
	5350 1875 5350 2350
Wire Wire Line
	5350 2350 5150 2350
Wire Wire Line
	7150 1775 5275 1775
Wire Wire Line
	5275 1775 5275 2250
Wire Wire Line
	5275 2250 5150 2250
Connection ~ 8800 5000
Connection ~ 6750 5000
Wire Wire Line
	7925 5000 8800 5000
Connection ~ 7925 5000
Wire Wire Line
	7925 2900 7925 5000
Wire Wire Line
	6350 3150 9100 3150
Wire Wire Line
	5150 3250 9100 3250
Wire Wire Line
	6750 5000 7925 5000
$EndSCHEMATC
