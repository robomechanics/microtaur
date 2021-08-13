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
Wire Wire Line
	4000 1300 4350 1300
Wire Wire Line
	4000 1400 4350 1400
Text Label 4000 1400 0    50   ~ 0
TX1
Text Label 4000 1300 0    50   ~ 0
RX1
Wire Wire Line
	4000 3100 4350 3100
Wire Wire Line
	4000 3200 4350 3200
Text Label 4000 3200 0    50   ~ 0
TX7
Text Label 4000 3100 0    50   ~ 0
RX7
Wire Wire Line
	4000 2000 4350 2000
Wire Wire Line
	4000 2100 4350 2100
Text Label 4000 2100 0    50   ~ 0
TX2
Text Label 4000 2000 0    50   ~ 0
RX2
Wire Wire Line
	6900 2200 6550 2200
Wire Wire Line
	6900 2100 6550 2100
Text Label 6900 2100 2    50   ~ 0
TX4
Text Label 6900 2200 2    50   ~ 0
RX4
Wire Wire Line
	6900 3400 6550 3400
Wire Wire Line
	6900 3300 6550 3300
Text Label 6900 3300 2    50   ~ 0
TX8
Text Label 6900 3400 2    50   ~ 0
RX8
Wire Wire Line
	6900 1800 6550 1800
Wire Wire Line
	6900 1700 6550 1700
Text Label 6900 1800 2    50   ~ 0
TX5
Text Label 6900 1700 2    50   ~ 0
RX5
Wire Wire Line
	6900 2400 6550 2400
Wire Wire Line
	6900 2300 6550 2300
Text Label 6900 2400 2    50   ~ 0
TX3
Text Label 6900 2300 2    50   ~ 0
RX3
$Comp
L Teensy:Teensy4.1 U1
U 1 1 608C3808
P 5450 3350
F 0 "U1" H 5450 5915 50  0000 C CNN
F 1 "Teensy4.1" H 5450 5824 50  0000 C CNN
F 2 "Teensy:Teensy41" H 5050 3750 50  0001 C CNN
F 3 "" H 5050 3750 50  0001 C CNN
	1    5450 3350
	1    0    0    -1  
$EndComp
Text Label 4050 2800 0    50   ~ 0
RX6
Text Label 4050 2700 0    50   ~ 0
TX6
Wire Wire Line
	4050 2700 4350 2700
Wire Wire Line
	4050 2800 4350 2800
Wire Wire Line
	6550 1900 6900 1900
Wire Wire Line
	6550 2000 6900 2000
Text Label 6900 1900 2    50   ~ 0
SCL
Text Label 6900 2000 2    50   ~ 0
SDA
Wire Wire Line
	5750 5850 6050 5850
Wire Wire Line
	6050 5950 5750 5950
Text Label 6050 5850 2    50   ~ 0
SCL
Text Label 6050 5950 2    50   ~ 0
SDA
$Comp
L microtaur-teensy41-rescue:R_Small-Device R1
U 1 1 6093F1E2
P 10100 5550
F 0 "R1" H 10159 5596 50  0000 L CNN
F 1 "10k" H 10159 5505 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 10100 5550 50  0001 C CNN
F 3 "~" H 10100 5550 50  0001 C CNN
	1    10100 5550
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:R_Small-Device R2
U 1 1 6093F5F8
P 10100 5750
F 0 "R2" H 10159 5796 50  0000 L CNN
F 1 "2.5k" H 10159 5705 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 10100 5750 50  0001 C CNN
F 3 "~" H 10100 5750 50  0001 C CNN
	1    10100 5750
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0110
U 1 1 6093F92D
P 10100 5850
F 0 "#PWR0110" H 10100 5600 50  0001 C CNN
F 1 "GND" H 10105 5677 50  0000 C CNN
F 2 "" H 10100 5850 50  0001 C CNN
F 3 "" H 10100 5850 50  0001 C CNN
	1    10100 5850
	1    0    0    -1  
$EndComp
Wire Wire Line
	10100 5650 9700 5650
Connection ~ 10100 5650
Text Label 9700 5650 0    50   ~ 0
BAT_MON
Wire Wire Line
	6900 1600 6550 1600
Text Label 6900 1600 2    50   ~ 0
BAT_MON
$Comp
L microtaur-teensy41-rescue:Conn_01x06-Connector_Generic J1
U 1 1 6094B3D5
P 7850 5450
F 0 "J1" H 7930 5442 50  0000 L CNN
F 1 "Conn_01x06" H 7930 5351 50  0000 L CNN
F 2 "Connector_JST:JST_SH_SM06B-SRSS-TB_1x06-1MP_P1.00mm_Horizontal" H 7850 5450 50  0001 C CNN
F 3 "~" H 7850 5450 50  0001 C CNN
	1    7850 5450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 5250 7650 5250
Wire Wire Line
	7300 5350 7650 5350
Wire Wire Line
	7300 5450 7650 5450
Wire Wire Line
	7300 5550 7650 5550
Wire Wire Line
	7300 5650 7650 5650
Wire Wire Line
	7300 5750 7650 5750
Text Label 7300 5250 0    50   ~ 0
PS2_DAT
Text Label 7300 5350 0    50   ~ 0
PS2_CMD
Text Label 7300 5450 0    50   ~ 0
ATT
Text Label 7300 5550 0    50   ~ 0
PS2_CLK
Text Label 7300 5650 0    50   ~ 0
5V
Text Label 7300 5750 0    50   ~ 0
GND
Wire Wire Line
	6550 2900 6900 2900
Wire Wire Line
	6550 3000 6900 3000
Wire Wire Line
	4350 3000 4000 3000
Wire Wire Line
	4350 2900 4000 2900
Text Label 4000 2900 0    50   ~ 0
PS2_CMD
Text Label 6900 2900 2    50   ~ 0
PS2_DAT
Text Label 6900 3000 2    50   ~ 0
PS2_CS
Text Label 4000 3000 0    50   ~ 0
PS2_CLK
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0111
U 1 1 60968EE0
P 5750 6050
F 0 "#PWR0111" H 5750 5800 50  0001 C CNN
F 1 "GND" V 5755 5922 50  0000 R CNN
F 2 "" H 5750 6050 50  0001 C CNN
F 3 "" H 5750 6050 50  0001 C CNN
	1    5750 6050
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5750 6150 6050 6150
Text Label 6050 6150 2    50   ~ 0
5V
Connection ~ 9500 5450
$Comp
L microtaur-teensy41-rescue:C_Small-Device C1
U 1 1 60984EAC
P 9500 5550
F 0 "C1" H 9592 5596 50  0000 L CNN
F 1 "0.22uF" H 9350 5450 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 9500 5550 50  0001 C CNN
F 3 "~" H 9500 5550 50  0001 C CNN
	1    9500 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 5750 9500 5750
Wire Wire Line
	9500 5750 9500 5650
Wire Wire Line
	9100 5850 9100 5750
Wire Wire Line
	9500 5450 10100 5450
Wire Wire Line
	9100 5850 10100 5850
Connection ~ 10100 5850
Wire Wire Line
	8600 5450 8800 5450
Text Label 8600 5450 0    50   ~ 0
5V
Wire Wire Line
	6550 1200 6900 1200
Text Label 6900 1200 2    50   ~ 0
5V
Wire Wire Line
	6550 1300 6900 1300
Text Label 6900 1300 2    50   ~ 0
GND
Wire Wire Line
	4000 1200 4350 1200
Text Label 4000 1200 0    50   ~ 0
GND
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0108
U 1 1 6091D001
P 10300 4250
F 0 "#PWR0108" H 10300 4000 50  0001 C CNN
F 1 "GND" V 10305 4122 50  0000 R CNN
F 2 "" H 10300 4250 50  0001 C CNN
F 3 "" H 10300 4250 50  0001 C CNN
	1    10300 4250
	0    1    1    0   
$EndComp
Text Label 9950 4150 0    50   ~ 0
RX8
Text Label 9950 4050 0    50   ~ 0
TX8
Wire Wire Line
	9950 4150 10300 4150
Wire Wire Line
	9950 4050 10300 4050
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0107
U 1 1 6091C656
P 10300 3850
F 0 "#PWR0107" H 10300 3600 50  0001 C CNN
F 1 "GND" V 10305 3722 50  0000 R CNN
F 2 "" H 10300 3850 50  0001 C CNN
F 3 "" H 10300 3850 50  0001 C CNN
	1    10300 3850
	0    1    1    0   
$EndComp
Text Label 9950 3750 0    50   ~ 0
RX7
Text Label 9950 3650 0    50   ~ 0
TX7
Wire Wire Line
	9950 3750 10300 3750
Wire Wire Line
	9950 3650 10300 3650
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0106
U 1 1 6091BA78
P 10300 3450
F 0 "#PWR0106" H 10300 3200 50  0001 C CNN
F 1 "GND" V 10305 3322 50  0000 R CNN
F 2 "" H 10300 3450 50  0001 C CNN
F 3 "" H 10300 3450 50  0001 C CNN
	1    10300 3450
	0    1    1    0   
$EndComp
Text Label 9950 3350 0    50   ~ 0
RX6
Text Label 9950 3250 0    50   ~ 0
TX6
Wire Wire Line
	9950 3350 10300 3350
Wire Wire Line
	9950 3250 10300 3250
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0105
U 1 1 6091B106
P 10300 3050
F 0 "#PWR0105" H 10300 2800 50  0001 C CNN
F 1 "GND" V 10305 2922 50  0000 R CNN
F 2 "" H 10300 3050 50  0001 C CNN
F 3 "" H 10300 3050 50  0001 C CNN
	1    10300 3050
	0    1    1    0   
$EndComp
Text Label 9950 2950 0    50   ~ 0
RX5
Text Label 9950 2850 0    50   ~ 0
TX5
Wire Wire Line
	9950 2950 10300 2950
Wire Wire Line
	9950 2850 10300 2850
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0104
U 1 1 6091A8BE
P 10300 2650
F 0 "#PWR0104" H 10300 2400 50  0001 C CNN
F 1 "GND" V 10305 2522 50  0000 R CNN
F 2 "" H 10300 2650 50  0001 C CNN
F 3 "" H 10300 2650 50  0001 C CNN
	1    10300 2650
	0    1    1    0   
$EndComp
Text Label 9950 2550 0    50   ~ 0
RX4
Text Label 9950 2450 0    50   ~ 0
TX4
Wire Wire Line
	9950 2550 10300 2550
Wire Wire Line
	9950 2450 10300 2450
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0103
U 1 1 60919F5E
P 10300 2250
F 0 "#PWR0103" H 10300 2000 50  0001 C CNN
F 1 "GND" V 10305 2122 50  0000 R CNN
F 2 "" H 10300 2250 50  0001 C CNN
F 3 "" H 10300 2250 50  0001 C CNN
	1    10300 2250
	0    1    1    0   
$EndComp
Text Label 9950 2150 0    50   ~ 0
RX3
Text Label 9950 2050 0    50   ~ 0
TX3
Wire Wire Line
	9950 2150 10300 2150
Wire Wire Line
	9950 2050 10300 2050
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0102
U 1 1 609186A5
P 10300 1850
F 0 "#PWR0102" H 10300 1600 50  0001 C CNN
F 1 "GND" V 10305 1722 50  0000 R CNN
F 2 "" H 10300 1850 50  0001 C CNN
F 3 "" H 10300 1850 50  0001 C CNN
	1    10300 1850
	0    1    1    0   
$EndComp
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0101
U 1 1 6091811A
P 10300 1450
F 0 "#PWR0101" H 10300 1200 50  0001 C CNN
F 1 "GND" V 10305 1322 50  0000 R CNN
F 2 "" H 10300 1450 50  0001 C CNN
F 3 "" H 10300 1450 50  0001 C CNN
	1    10300 1450
	0    1    1    0   
$EndComp
Text Label 9950 1750 0    50   ~ 0
RX2
Text Label 9950 1650 0    50   ~ 0
TX2
Wire Wire Line
	9950 1750 10300 1750
Wire Wire Line
	9950 1650 10300 1650
Text Label 9950 1350 0    50   ~ 0
RX1
Text Label 9950 1250 0    50   ~ 0
TX1
Wire Wire Line
	9950 1350 10300 1350
Wire Wire Line
	9950 1250 10300 1250
$Comp
L microtaur-teensy41-rescue:Conn_01x03-Connector_Generic SER7
U 1 1 60916A47
P 10500 3750
F 0 "SER7" H 10580 3792 50  0000 L CNN
F 1 "Conn_01x03" H 10580 3701 50  0000 L CNN
F 2 "Connector_JST:JST_SH_SM03B-SRSS-TB_1x03-1MP_P1.00mm_Horizontal" H 10500 3750 50  0001 C CNN
F 3 "~" H 10500 3750 50  0001 C CNN
	1    10500 3750
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x03-Connector_Generic SER1
U 1 1 6090E039
P 10500 1350
F 0 "SER1" H 10580 1392 50  0000 L CNN
F 1 "Conn_01x03" H 10580 1301 50  0000 L CNN
F 2 "Connector_JST:JST_SH_SM03B-SRSS-TB_1x03-1MP_P1.00mm_Horizontal" H 10500 1350 50  0001 C CNN
F 3 "~" H 10500 1350 50  0001 C CNN
	1    10500 1350
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x03-Connector_Generic SER2
U 1 1 6090D835
P 10500 1750
F 0 "SER2" H 10580 1792 50  0000 L CNN
F 1 "Conn_01x03" H 10580 1701 50  0000 L CNN
F 2 "Connector_JST:JST_SH_SM03B-SRSS-TB_1x03-1MP_P1.00mm_Horizontal" H 10500 1750 50  0001 C CNN
F 3 "~" H 10500 1750 50  0001 C CNN
	1    10500 1750
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x03-Connector_Generic SER6
U 1 1 6090CC6A
P 10500 3350
F 0 "SER6" H 10580 3392 50  0000 L CNN
F 1 "Conn_01x03" H 10580 3301 50  0000 L CNN
F 2 "Connector_JST:JST_SH_SM03B-SRSS-TB_1x03-1MP_P1.00mm_Horizontal" H 10500 3350 50  0001 C CNN
F 3 "~" H 10500 3350 50  0001 C CNN
	1    10500 3350
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x03-Connector_Generic SER3
U 1 1 6090CC64
P 10500 2150
F 0 "SER3" H 10580 2192 50  0000 L CNN
F 1 "Conn_01x03" H 10580 2101 50  0000 L CNN
F 2 "Connector_JST:JST_SH_SM03B-SRSS-TB_1x03-1MP_P1.00mm_Horizontal" H 10500 2150 50  0001 C CNN
F 3 "~" H 10500 2150 50  0001 C CNN
	1    10500 2150
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x03-Connector_Generic SER8
U 1 1 608A52BA
P 10500 4150
F 0 "SER8" H 10580 4192 50  0000 L CNN
F 1 "Conn_01x03" H 10580 4101 50  0000 L CNN
F 2 "Connector_JST:JST_SH_SM03B-SRSS-TB_1x03-1MP_P1.00mm_Horizontal" H 10500 4150 50  0001 C CNN
F 3 "~" H 10500 4150 50  0001 C CNN
	1    10500 4150
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x03-Connector_Generic SER5
U 1 1 608A4971
P 10500 2950
F 0 "SER5" H 10580 2992 50  0000 L CNN
F 1 "Conn_01x03" H 10580 2901 50  0000 L CNN
F 2 "Connector_JST:JST_SH_SM03B-SRSS-TB_1x03-1MP_P1.00mm_Horizontal" H 10500 2950 50  0001 C CNN
F 3 "~" H 10500 2950 50  0001 C CNN
	1    10500 2950
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x03-Connector_Generic SER4
U 1 1 608A46A8
P 10500 2550
F 0 "SER4" H 10580 2592 50  0000 L CNN
F 1 "Conn_01x03" H 10580 2501 50  0000 L CNN
F 2 "Connector_JST:JST_SH_SM03B-SRSS-TB_1x03-1MP_P1.00mm_Horizontal" H 10500 2550 50  0001 C CNN
F 3 "~" H 10500 2550 50  0001 C CNN
	1    10500 2550
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0109
U 1 1 6093DB86
P 10800 5750
F 0 "#PWR0109" H 10800 5500 50  0001 C CNN
F 1 "GND" V 10805 5622 50  0000 R CNN
F 2 "" H 10800 5750 50  0001 C CNN
F 3 "" H 10800 5750 50  0001 C CNN
	1    10800 5750
	0    1    1    0   
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x02-Connector_Generic PWR1
U 1 1 608ADE78
P 11000 5750
F 0 "PWR1" H 10918 5425 50  0000 C CNN
F 1 "Conn_01x02" H 10918 5516 50  0000 C CNN
F 2 "Connector_AMASS:AMASS_XT30U-F_1x02_P5.0mm_Vertical" H 11000 5750 50  0001 C CNN
F 3 "~" H 11000 5750 50  0001 C CNN
	1    11000 5750
	1    0    0    1   
$EndComp
$Comp
L microtaur-teensy41-rescue:Vdrive-power #PWR0112
U 1 1 608AFDF3
P 9500 5450
F 0 "#PWR0112" H 9300 5300 50  0001 C CNN
F 1 "Vdrive" H 9517 5623 50  0000 C CNN
F 2 "" H 9500 5450 50  0001 C CNN
F 3 "" H 9500 5450 50  0001 C CNN
	1    9500 5450
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:MountingHole-Mechanical H3
U 1 1 608B7434
P 750 7250
F 0 "H3" H 850 7296 50  0000 L CNN
F 1 "MountingHole" H 850 7205 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 750 7250 50  0001 C CNN
F 3 "~" H 750 7250 50  0001 C CNN
	1    750  7250
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:MountingHole-Mechanical H7
U 1 1 608B8276
P 1000 7250
F 0 "H7" H 1100 7296 50  0000 L CNN
F 1 "MountingHole" H 1100 7205 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 1000 7250 50  0001 C CNN
F 3 "~" H 1000 7250 50  0001 C CNN
	1    1000 7250
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:MountingHole-Mechanical H8
U 1 1 608B8652
P 1000 7450
F 0 "H8" H 1100 7496 50  0000 L CNN
F 1 "MountingHole" H 1100 7405 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 1000 7450 50  0001 C CNN
F 3 "~" H 1000 7450 50  0001 C CNN
	1    1000 7450
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:MountingHole-Mechanical H4
U 1 1 608B8ABD
P 750 7450
F 0 "H4" H 850 7496 50  0000 L CNN
F 1 "MountingHole" H 850 7405 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 750 7450 50  0001 C CNN
F 3 "~" H 750 7450 50  0001 C CNN
	1    750  7450
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:MountingHole-Mechanical H2
U 1 1 608B8C2F
P 750 7000
F 0 "H2" H 850 7046 50  0000 L CNN
F 1 "MountingHole" H 850 6955 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 750 7000 50  0001 C CNN
F 3 "~" H 750 7000 50  0001 C CNN
	1    750  7000
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:MountingHole-Mechanical H6
U 1 1 608B8EC9
P 1000 7000
F 0 "H6" H 1100 7046 50  0000 L CNN
F 1 "MountingHole" H 1100 6955 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 1000 7000 50  0001 C CNN
F 3 "~" H 1000 7000 50  0001 C CNN
	1    1000 7000
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:MountingHole-Mechanical H5
U 1 1 608B9277
P 1000 6800
F 0 "H5" H 1100 6846 50  0000 L CNN
F 1 "MountingHole" H 1100 6755 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 1000 6800 50  0001 C CNN
F 3 "~" H 1000 6800 50  0001 C CNN
	1    1000 6800
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:MountingHole-Mechanical H1
U 1 1 608B9565
P 750 6800
F 0 "H1" H 850 6846 50  0000 L CNN
F 1 "MountingHole" H 850 6755 50  0000 L CNN
F 2 "MountingHole:MountingHole_2.2mm_M2" H 750 6800 50  0001 C CNN
F 3 "~" H 750 6800 50  0001 C CNN
	1    750  6800
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x02-Connector_Generic MPOW1
U 1 1 608C3689
P 9050 1200
F 0 "MPOW1" H 9130 1192 50  0000 L CNN
F 1 "Conn_01x02" H 9130 1101 50  0000 L CNN
F 2 "Connector_AMASS:AMASS_XT30U-F_1x02_P5.0mm_Vertical" H 9050 1200 50  0001 C CNN
F 3 "~" H 9050 1200 50  0001 C CNN
	1    9050 1200
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x02-Connector_Generic MPOW2
U 1 1 608CC08E
P 9050 1500
F 0 "MPOW2" H 9130 1492 50  0000 L CNN
F 1 "Conn_01x02" H 9130 1401 50  0000 L CNN
F 2 "Connector_AMASS:AMASS_XT30U-F_1x02_P5.0mm_Vertical" H 9050 1500 50  0001 C CNN
F 3 "~" H 9050 1500 50  0001 C CNN
	1    9050 1500
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x02-Connector_Generic MPOW3
U 1 1 608CC4B3
P 9050 1800
F 0 "MPOW3" H 9130 1792 50  0000 L CNN
F 1 "Conn_01x02" H 9130 1701 50  0000 L CNN
F 2 "Connector_AMASS:AMASS_XT30U-F_1x02_P5.0mm_Vertical" H 9050 1800 50  0001 C CNN
F 3 "~" H 9050 1800 50  0001 C CNN
	1    9050 1800
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x02-Connector_Generic MPOW4
U 1 1 608CC6EE
P 9050 2100
F 0 "MPOW4" H 9130 2092 50  0000 L CNN
F 1 "Conn_01x02" H 9130 2001 50  0000 L CNN
F 2 "Connector_AMASS:AMASS_XT30U-F_1x02_P5.0mm_Vertical" H 9050 2100 50  0001 C CNN
F 3 "~" H 9050 2100 50  0001 C CNN
	1    9050 2100
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x02-Connector_Generic MPOW5
U 1 1 608CE9C3
P 9050 2400
F 0 "MPOW5" H 9130 2392 50  0000 L CNN
F 1 "Conn_01x02" H 9130 2301 50  0000 L CNN
F 2 "Connector_AMASS:AMASS_XT30U-F_1x02_P5.0mm_Vertical" H 9050 2400 50  0001 C CNN
F 3 "~" H 9050 2400 50  0001 C CNN
	1    9050 2400
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x02-Connector_Generic MPOW6
U 1 1 608CE9C9
P 9050 2700
F 0 "MPOW6" H 9130 2692 50  0000 L CNN
F 1 "Conn_01x02" H 9130 2601 50  0000 L CNN
F 2 "Connector_AMASS:AMASS_XT30U-F_1x02_P5.0mm_Vertical" H 9050 2700 50  0001 C CNN
F 3 "~" H 9050 2700 50  0001 C CNN
	1    9050 2700
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x02-Connector_Generic MPOW7
U 1 1 608CE9CF
P 9050 3000
F 0 "MPOW7" H 9130 2992 50  0000 L CNN
F 1 "Conn_01x02" H 9130 2901 50  0000 L CNN
F 2 "Connector_AMASS:AMASS_XT30U-F_1x02_P5.0mm_Vertical" H 9050 3000 50  0001 C CNN
F 3 "~" H 9050 3000 50  0001 C CNN
	1    9050 3000
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x02-Connector_Generic MPOW8
U 1 1 608CE9D5
P 9050 3300
F 0 "MPOW8" H 9130 3292 50  0000 L CNN
F 1 "Conn_01x02" H 9130 3201 50  0000 L CNN
F 2 "Connector_AMASS:AMASS_XT30U-F_1x02_P5.0mm_Vertical" H 9050 3300 50  0001 C CNN
F 3 "~" H 9050 3300 50  0001 C CNN
	1    9050 3300
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:Vdrive-power #PWR0114
U 1 1 608E45DF
P 10800 5650
F 0 "#PWR0114" H 10600 5500 50  0001 C CNN
F 1 "Vdrive" V 10818 5778 50  0000 L CNN
F 2 "" H 10800 5650 50  0001 C CNN
F 3 "" H 10800 5650 50  0001 C CNN
	1    10800 5650
	0    -1   -1   0   
$EndComp
$Comp
L microtaur-teensy41-rescue:USB_A-Connector J2
U 1 1 60907F17
P 3100 4150
F 0 "J2" H 3157 4617 50  0000 C CNN
F 1 "USB_A" H 3157 4526 50  0000 C CNN
F 2 "Connector_USB:USB_A_Molex_105057_Vertical" H 3250 4100 50  0001 C CNN
F 3 " ~" H 3250 4100 50  0001 C CNN
	1    3100 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 3950 3600 3950
Text Label 3600 3950 2    50   ~ 0
5V
Wire Wire Line
	3400 4150 3600 4150
Text Label 3600 4150 2    50   ~ 0
D+
Wire Wire Line
	3400 4250 3600 4250
Text Label 3600 4250 2    50   ~ 0
D-
$Comp
L microtaur-teensy41-rescue:GND-power #PWR02
U 1 1 6091D07A
P 3100 4550
F 0 "#PWR02" H 3100 4300 50  0001 C CNN
F 1 "GND" H 3200 4450 50  0000 C CNN
F 2 "" H 3100 4550 50  0001 C CNN
F 3 "" H 3100 4550 50  0001 C CNN
	1    3100 4550
	1    0    0    -1  
$EndComp
$Comp
L microtaur-teensy41-rescue:GND-power #PWR01
U 1 1 6091D5BC
P 3000 4550
F 0 "#PWR01" H 3000 4300 50  0001 C CNN
F 1 "GND" H 2900 4450 50  0000 C CNN
F 2 "" H 3000 4550 50  0001 C CNN
F 3 "" H 3000 4550 50  0001 C CNN
	1    3000 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 3950 4150 3950
Text Label 4150 3950 0    50   ~ 0
5V
Wire Wire Line
	4350 4150 4150 4150
Text Label 4150 4150 0    50   ~ 0
D+
Text Label 4150 4050 0    50   ~ 0
D-
Wire Wire Line
	4150 4050 4350 4050
$Comp
L microtaur-teensy41-rescue:GND-power #PWR03
U 1 1 60925E27
P 4350 4250
F 0 "#PWR03" H 4350 4000 50  0001 C CNN
F 1 "GND" V 4350 4000 50  0000 C CNN
F 2 "" H 4350 4250 50  0001 C CNN
F 3 "" H 4350 4250 50  0001 C CNN
	1    4350 4250
	0    1    1    0   
$EndComp
$Comp
L microtaur-teensy41-rescue:GND-power #PWR04
U 1 1 6092511C
P 4350 4350
F 0 "#PWR04" H 4350 4100 50  0001 C CNN
F 1 "GND" V 4350 4100 50  0000 C CNN
F 2 "" H 4350 4350 50  0001 C CNN
F 3 "" H 4350 4350 50  0001 C CNN
	1    4350 4350
	0    1    1    0   
$EndComp
$Comp
L microtaur-teensy41-rescue:Vdrive-power #PWR0115
U 1 1 608EB897
P 8850 1300
F 0 "#PWR0115" H 8650 1150 50  0001 C CNN
F 1 "Vdrive" V 8868 1428 50  0000 L CNN
F 2 "" H 8850 1300 50  0001 C CNN
F 3 "" H 8850 1300 50  0001 C CNN
	1    8850 1300
	0    -1   1    0   
$EndComp
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0113
U 1 1 608DE0A0
P 8850 1200
F 0 "#PWR0113" H 8850 950 50  0001 C CNN
F 1 "GND" V 8855 1072 50  0000 R CNN
F 2 "" H 8850 1200 50  0001 C CNN
F 3 "" H 8850 1200 50  0001 C CNN
	1    8850 1200
	0    1    -1   0   
$EndComp
$Comp
L microtaur-teensy41-rescue:Vdrive-power #PWR0116
U 1 1 6093B156
P 8850 1600
F 0 "#PWR0116" H 8650 1450 50  0001 C CNN
F 1 "Vdrive" V 8868 1728 50  0000 L CNN
F 2 "" H 8850 1600 50  0001 C CNN
F 3 "" H 8850 1600 50  0001 C CNN
	1    8850 1600
	0    -1   1    0   
$EndComp
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0117
U 1 1 6093B15C
P 8850 1500
F 0 "#PWR0117" H 8850 1250 50  0001 C CNN
F 1 "GND" V 8855 1372 50  0000 R CNN
F 2 "" H 8850 1500 50  0001 C CNN
F 3 "" H 8850 1500 50  0001 C CNN
	1    8850 1500
	0    1    -1   0   
$EndComp
$Comp
L microtaur-teensy41-rescue:Vdrive-power #PWR0118
U 1 1 6093DD87
P 8850 1900
F 0 "#PWR0118" H 8650 1750 50  0001 C CNN
F 1 "Vdrive" V 8868 2028 50  0000 L CNN
F 2 "" H 8850 1900 50  0001 C CNN
F 3 "" H 8850 1900 50  0001 C CNN
	1    8850 1900
	0    -1   1    0   
$EndComp
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0119
U 1 1 6093DD8D
P 8850 1800
F 0 "#PWR0119" H 8850 1550 50  0001 C CNN
F 1 "GND" V 8855 1672 50  0000 R CNN
F 2 "" H 8850 1800 50  0001 C CNN
F 3 "" H 8850 1800 50  0001 C CNN
	1    8850 1800
	0    1    -1   0   
$EndComp
$Comp
L microtaur-teensy41-rescue:Vdrive-power #PWR0120
U 1 1 6093DD93
P 8850 2200
F 0 "#PWR0120" H 8650 2050 50  0001 C CNN
F 1 "Vdrive" V 8868 2328 50  0000 L CNN
F 2 "" H 8850 2200 50  0001 C CNN
F 3 "" H 8850 2200 50  0001 C CNN
	1    8850 2200
	0    -1   1    0   
$EndComp
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0121
U 1 1 6093DD99
P 8850 2100
F 0 "#PWR0121" H 8850 1850 50  0001 C CNN
F 1 "GND" V 8855 1972 50  0000 R CNN
F 2 "" H 8850 2100 50  0001 C CNN
F 3 "" H 8850 2100 50  0001 C CNN
	1    8850 2100
	0    1    -1   0   
$EndComp
$Comp
L microtaur-teensy41-rescue:Vdrive-power #PWR0122
U 1 1 60941308
P 8850 2500
F 0 "#PWR0122" H 8650 2350 50  0001 C CNN
F 1 "Vdrive" V 8868 2628 50  0000 L CNN
F 2 "" H 8850 2500 50  0001 C CNN
F 3 "" H 8850 2500 50  0001 C CNN
	1    8850 2500
	0    -1   1    0   
$EndComp
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0123
U 1 1 6094130E
P 8850 2400
F 0 "#PWR0123" H 8850 2150 50  0001 C CNN
F 1 "GND" V 8855 2272 50  0000 R CNN
F 2 "" H 8850 2400 50  0001 C CNN
F 3 "" H 8850 2400 50  0001 C CNN
	1    8850 2400
	0    1    -1   0   
$EndComp
$Comp
L microtaur-teensy41-rescue:Vdrive-power #PWR0124
U 1 1 60941314
P 8850 2800
F 0 "#PWR0124" H 8650 2650 50  0001 C CNN
F 1 "Vdrive" V 8868 2928 50  0000 L CNN
F 2 "" H 8850 2800 50  0001 C CNN
F 3 "" H 8850 2800 50  0001 C CNN
	1    8850 2800
	0    -1   1    0   
$EndComp
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0125
U 1 1 6094131A
P 8850 2700
F 0 "#PWR0125" H 8850 2450 50  0001 C CNN
F 1 "GND" V 8855 2572 50  0000 R CNN
F 2 "" H 8850 2700 50  0001 C CNN
F 3 "" H 8850 2700 50  0001 C CNN
	1    8850 2700
	0    1    -1   0   
$EndComp
$Comp
L microtaur-teensy41-rescue:Vdrive-power #PWR0126
U 1 1 60944C09
P 8850 3100
F 0 "#PWR0126" H 8650 2950 50  0001 C CNN
F 1 "Vdrive" V 8868 3228 50  0000 L CNN
F 2 "" H 8850 3100 50  0001 C CNN
F 3 "" H 8850 3100 50  0001 C CNN
	1    8850 3100
	0    -1   1    0   
$EndComp
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0127
U 1 1 60944C0F
P 8850 3000
F 0 "#PWR0127" H 8850 2750 50  0001 C CNN
F 1 "GND" V 8855 2872 50  0000 R CNN
F 2 "" H 8850 3000 50  0001 C CNN
F 3 "" H 8850 3000 50  0001 C CNN
	1    8850 3000
	0    1    -1   0   
$EndComp
$Comp
L microtaur-teensy41-rescue:Vdrive-power #PWR0128
U 1 1 60944C15
P 8850 3400
F 0 "#PWR0128" H 8650 3250 50  0001 C CNN
F 1 "Vdrive" V 8868 3528 50  0000 L CNN
F 2 "" H 8850 3400 50  0001 C CNN
F 3 "" H 8850 3400 50  0001 C CNN
	1    8850 3400
	0    -1   1    0   
$EndComp
$Comp
L microtaur-teensy41-rescue:GND-power #PWR0129
U 1 1 60944C1B
P 8850 3300
F 0 "#PWR0129" H 8850 3050 50  0001 C CNN
F 1 "GND" V 8855 3172 50  0000 R CNN
F 2 "" H 8850 3300 50  0001 C CNN
F 3 "" H 8850 3300 50  0001 C CNN
	1    8850 3300
	0    1    -1   0   
$EndComp
$Comp
L microtaur-teensy41-rescue:Conn_01x04-Connector_Generic IMU1
U 1 1 6095C393
P 5550 6050
F 0 "IMU1" H 5468 5625 50  0000 C CNN
F 1 "Conn_01x04" H 5468 5716 50  0000 C CNN
F 2 "Connector_JST:JST_SH_BM04B-SRSS-TB_1x04-1MP_P1.00mm_Vertical" H 5550 6050 50  0001 C CNN
F 3 "~" H 5550 6050 50  0001 C CNN
	1    5550 6050
	-1   0    0    1   
$EndComp
Connection ~ 9100 5750
Wire Wire Line
	9400 5450 9500 5450
Wire Wire Line
	9300 5450 9400 5450
Connection ~ 9400 5450
$Comp
L microtaur-teensy41-rescue:LM7805_TO220-Regulator_Linear U3
U 1 1 6097103B
P 9100 5450
F 0 "U3" H 9100 5692 50  0000 C CNN
F 1 "LM7805_TO220" H 9100 5601 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Horizontal_TabDown" H 9100 5675 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7805.pdf" H 9100 5400 50  0001 C CNN
	1    9100 5450
	-1   0    0    -1  
$EndComp
$EndSCHEMATC
