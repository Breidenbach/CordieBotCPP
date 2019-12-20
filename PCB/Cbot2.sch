EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A3 16535 11693
encoding utf-8
Sheet 1 1
Title "Raspberry Pi HAT"
Date ""
Rev "A"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x02_Male J1
U 1 1 5DF96DA1
P 1750 1450
F 0 "J1" H 1858 1631 50  0000 C CNN
F 1 "+5V Power" H 1858 1540 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 1750 1450 50  0001 C CNN
F 3 "~" H 1750 1450 50  0001 C CNN
	1    1750 1450
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 5DF97861
P 1750 1900
F 0 "J2" H 1858 2081 50  0000 C CNN
F 1 "+5V RPi Power" H 1858 1990 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 1750 1900 50  0001 C CNN
F 3 "~" H 1750 1900 50  0001 C CNN
	1    1750 1900
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C2
U 1 1 5DFA1E24
P 2500 2300
F 0 "C2" H 2615 2346 50  0000 L CNN
F 1 "10uf" H 2615 2255 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_Tantal_D5.0mm_P2.50mm" H 2500 2300 50  0001 C CNN
F 3 "~" H 2500 2300 50  0001 C CNN
	1    2500 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 1900 2150 1900
Text GLabel 6550 1100 2    50   Input ~ 0
RPi+3.3V
Text GLabel 2750 1550 2    50   Input ~ 0
Vs+5V
Text GLabel 4900 1100 0    50   Input ~ 0
RPi+5V
Text GLabel 6950 2800 2    50   Input ~ 0
SPI_CS0
Text GLabel 6950 2700 2    50   Input ~ 0
SPI_CS1
Text GLabel 6950 3000 2    50   Input ~ 0
SPI_MOSI
Text GLabel 6950 2900 2    50   Input ~ 0
SPI_MISO
Text GLabel 6950 3100 2    50   Input ~ 0
SPI_CLK
$Comp
L Sensor_Temperature:TMP36GT9Z U1
U 1 1 5DFDBBFF
P 2450 7200
F 0 "U1" H 2322 7246 50  0000 R CNN
F 1 "TMP36GT9Z" H 2322 7155 50  0000 R CNN
F 2 "Package_TO_SOT_THT:TO-92L_HandSolder" H 2250 7450 50  0001 C CNN
F 3 "" H 2250 7450 50  0001 C CNN
	1    2450 7200
	1    0    0    -1  
$EndComp
$Comp
L Analog_ADC:MCP3002 U2
U 1 1 5DFDCAE0
P 4150 7400
F 0 "U2" H 4250 8081 50  0000 C CNN
F 1 "MCP3002" H 4400 7950 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 4150 7300 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21294E.pdf" H 4150 7600 50  0001 C CNN
	1    4150 7400
	1    0    0    -1  
$EndComp
Text GLabel 1350 6550 0    50   Input ~ 0
RPi+3.3V
$Comp
L Device:C C1
U 1 1 5DFE73E9
P 1750 6850
F 0 "C1" H 1865 6896 50  0000 L CNN
F 1 "1uf" H 1865 6805 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 1788 6700 50  0001 C CNN
F 3 "~" H 1750 6850 50  0001 C CNN
	1    1750 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 6700 1750 6550
Connection ~ 1750 8050
Wire Wire Line
	1750 8050 1750 8250
Wire Wire Line
	1350 6550 1750 6550
Connection ~ 1750 6550
Wire Wire Line
	3650 7600 3300 7600
Wire Wire Line
	3300 7600 3300 8050
Wire Wire Line
	1750 8050 2450 8050
Wire Wire Line
	1750 7000 1750 8050
Wire Wire Line
	4150 7900 4150 8050
Wire Wire Line
	4150 8050 3300 8050
Connection ~ 3300 8050
Wire Wire Line
	1950 1450 2150 1450
Wire Wire Line
	2150 1450 2150 1900
Connection ~ 2150 1900
Wire Wire Line
	1950 1550 2500 1550
Wire Wire Line
	2150 1900 2150 2550
Wire Wire Line
	2500 1550 2500 2000
Connection ~ 2500 1550
Wire Wire Line
	2500 1550 2750 1550
Wire Wire Line
	1950 2000 2500 2000
Wire Wire Line
	2500 2550 2150 2550
Wire Wire Line
	2500 2000 2500 2150
Connection ~ 2500 2000
Wire Wire Line
	2500 2450 2500 2550
Wire Wire Line
	2450 7550 2450 8050
Wire Wire Line
	1750 6550 2450 6550
Wire Wire Line
	2450 6850 2450 6550
Wire Wire Line
	4150 6900 4150 6550
Text GLabel 5200 7300 2    50   Input ~ 0
SPI_CLK
Text GLabel 5200 7200 2    50   Input ~ 0
SPI_CS1
Text GLabel 5200 7500 2    50   Input ~ 0
SPI_MISO
Text GLabel 5200 7600 2    50   Input ~ 0
SPI_MOSI
Wire Wire Line
	5200 7200 4850 7200
Wire Wire Line
	4850 7300 5200 7300
Wire Wire Line
	5200 7500 4850 7500
Wire Wire Line
	4850 7600 5200 7600
$Comp
L Connector:Conn_01x05_Male J4
U 1 1 5E02F2B8
P 6850 5350
F 0 "J4" H 6958 5731 50  0000 C CNN
F 1 "Lights" H 6958 5640 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 6850 5350 50  0001 C CNN
F 3 "~" H 6850 5350 50  0001 C CNN
	1    6850 5350
	1    0    0    -1  
$EndComp
Text GLabel 7450 5150 2    50   Input ~ 0
SPI_MOSI
Text GLabel 7450 5250 2    50   Input ~ 0
SPI_CLK
Text GLabel 7450 5350 2    50   Input ~ 0
Vs+5V
Text GLabel 7450 5450 2    50   Input ~ 0
RPi+5V
Wire Wire Line
	7050 5150 7450 5150
Wire Wire Line
	7050 5250 7450 5250
Wire Wire Line
	7050 5350 7450 5350
Wire Wire Line
	7050 5450 7450 5450
Wire Wire Line
	7050 5550 7450 5550
Wire Wire Line
	7450 5550 7450 5900
Text Notes 15650 10400 0    50   ~ 0
1.0
Text Notes 12400 10250 0    50   ~ 0
CordieBot:  Connection HAT
$Comp
L Connector:Conn_01x03_Male J5
U 1 1 5E040113
P 10300 1000
F 0 "J5" H 10272 1024 50  0000 R CNN
F 1 "Fan" H 10272 933 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 10300 1000 50  0001 C CNN
F 3 "~" H 10300 1000 50  0001 C CNN
	1    10300 1000
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J6
U 1 1 5E041DB6
P 10300 2550
F 0 "J6" H 10272 2574 50  0000 R CNN
F 1 "Switch" H 10272 2483 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 10300 2550 50  0001 C CNN
F 3 "~" H 10300 2550 50  0001 C CNN
	1    10300 2550
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J8
U 1 1 5E043C5F
P 10600 5400
F 0 "J8" H 10572 5424 50  0000 R CNN
F 1 "Volume control" H 10572 5333 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 10600 5400 50  0001 C CNN
F 3 "~" H 10600 5400 50  0001 C CNN
	1    10600 5400
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J9
U 1 1 5E0461CC
P 10600 6050
F 0 "J9" H 10708 6231 50  0000 C CNN
F 1 "RPi Audio (1 channel)" H 10708 6140 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 10600 6050 50  0001 C CNN
F 3 "~" H 10600 6050 50  0001 C CNN
	1    10600 6050
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J7
U 1 1 5E048BAB
P 10600 4550
F 0 "J7" H 10708 4931 50  0000 C CNN
F 1 "Amplifier" H 10708 4840 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 10600 4550 50  0001 C CNN
F 3 "~" H 10600 4550 50  0001 C CNN
	1    10600 4550
	-1   0    0    -1  
$EndComp
Text GLabel 9050 900  0    50   Input ~ 0
Vs+5V
$Comp
L Diode:1N914 D1
U 1 1 5E05F788
P 9450 1200
F 0 "D1" V 9404 1279 50  0000 L CNN
F 1 "HEP170" V 9495 1279 50  0000 L CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 9450 1025 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 9450 1200 50  0001 C CNN
	1    9450 1200
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q1
U 1 1 5E06868C
P 8850 1700
F 0 "Q1" H 9040 1746 50  0000 L CNN
F 1 "2N2222" H 9040 1655 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_HandSolder" H 9050 1625 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 8850 1700 50  0001 L CNN
	1    8850 1700
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R1
U 1 1 5E071A40
P 8250 1700
F 0 "R1" V 8045 1700 50  0000 C CNN
F 1 "2K" V 8136 1700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 8290 1690 50  0001 C CNN
F 3 "~" H 8250 1700 50  0001 C CNN
	1    8250 1700
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R2
U 1 1 5E073B4C
P 9500 2850
F 0 "R2" H 9568 2896 50  0000 L CNN
F 1 "2.2K" H 9568 2805 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9540 2840 50  0001 C CNN
F 3 "~" H 9500 2850 50  0001 C CNN
	1    9500 2850
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R3
U 1 1 5E075E7E
P 9500 3250
F 0 "R3" H 9568 3296 50  0000 L CNN
F 1 "3.3K" H 9568 3205 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 9540 3240 50  0001 C CNN
F 3 "~" H 9500 3250 50  0001 C CNN
	1    9500 3250
	1    0    0    -1  
$EndComp
$Comp
L Connector:Raspberry_Pi_2_3 J3
U 1 1 5E08C9EE
P 5700 2600
F 0 "J3" H 5700 4081 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 6350 3900 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical" H 5700 2600 50  0001 C CNN
F 3 "https://www.raspberrypi.org/documentation/hardware/raspberrypi/schematics/rpi_SCH_3bplus_1p0_reduced.pdf" H 5700 2600 50  0001 C CNN
	1    5700 2600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1100 5500 1100
Wire Wire Line
	5600 1100 5600 1300
Wire Wire Line
	5500 1300 5500 1100
Connection ~ 5500 1100
Wire Wire Line
	5500 1100 5600 1100
Wire Wire Line
	5800 1100 5800 1300
Wire Wire Line
	6550 1100 5900 1100
Wire Wire Line
	5900 1300 5900 1100
Connection ~ 5900 1100
Wire Wire Line
	5900 1100 5800 1100
Wire Wire Line
	6500 2700 6950 2700
Wire Wire Line
	6950 2800 6500 2800
Wire Wire Line
	6500 2900 6950 2900
Wire Wire Line
	6950 3000 6500 3000
Wire Wire Line
	6500 3100 6950 3100
Text GLabel 9700 4650 0    50   Input ~ 0
Vs+5V
Wire Wire Line
	9450 1050 9450 900 
Wire Wire Line
	8950 1400 8950 1500
Wire Wire Line
	9950 1400 9950 1000
Wire Wire Line
	9950 1000 10100 1000
Wire Wire Line
	8950 1900 8950 2050
Wire Wire Line
	8400 1700 8650 1700
Connection ~ 9450 900 
Wire Wire Line
	9450 1350 9450 1400
Connection ~ 9450 1400
Wire Wire Line
	8950 1400 9450 1400
Text GLabel 4500 2200 0    50   Input ~ 0
PWM0
Wire Wire Line
	4500 2200 4900 2200
Text GLabel 7850 1700 0    50   Input ~ 0
PWM0
Wire Wire Line
	7850 1700 8100 1700
Text GLabel 9400 2450 0    50   Input ~ 0
RPi+5V
Wire Wire Line
	9500 3100 9500 3050
Wire Wire Line
	9500 2550 10100 2550
Wire Wire Line
	10100 2650 10000 2650
Wire Wire Line
	9400 2450 10100 2450
Wire Wire Line
	9500 2700 9500 2550
Text GLabel 4500 3100 0    50   Input ~ 0
SWITCH_INPUT
Wire Wire Line
	4500 3100 4900 3100
Text GLabel 9150 3050 0    50   Input ~ 0
SWITCH_INPUT
Wire Wire Line
	9150 3050 9500 3050
Connection ~ 9500 3050
Wire Wire Line
	9500 3050 9500 3000
Wire Wire Line
	9500 3400 9500 3600
Wire Wire Line
	10000 2650 10000 3050
Wire Wire Line
	9900 4750 9900 4900
Text GLabel 4500 2600 0    50   Input ~ 0
AMP_ENBL
Wire Wire Line
	4500 2600 4900 2600
Text GLabel 9050 4550 0    50   Input ~ 0
AMP_ENBL
Wire Wire Line
	9300 4350 9300 5400
Wire Wire Line
	9450 5500 9450 6050
Wire Wire Line
	9300 4350 10400 4350
Wire Wire Line
	9200 4450 10400 4450
Wire Wire Line
	9050 4550 10400 4550
Wire Wire Line
	9700 4650 10400 4650
Wire Wire Line
	9900 4750 10400 4750
Wire Wire Line
	9200 4450 9200 5300
Wire Wire Line
	9200 5300 10400 5300
Connection ~ 9200 5300
Wire Wire Line
	9200 5300 9200 6150
Wire Wire Line
	9300 5400 10400 5400
Wire Wire Line
	9450 5500 10400 5500
Wire Wire Line
	9450 6050 10400 6050
Wire Wire Line
	9200 6150 10400 6150
Text Label 9800 4550 0    50   ~ 0
Select
Text Label 9800 4450 0    50   ~ 0
Sig.Ground
Text Label 9800 4350 0    50   ~ 0
Signal
Text Label 10000 4750 0    50   ~ 0
Pwr.Ground
Text Label 9950 5300 0    50   ~ 0
Ground
Text Label 9950 5400 0    50   ~ 0
Variable
Text Label 9950 5500 0    50   ~ 0
Input
Text Label 9750 6050 0    50   ~ 0
Audio
Text Label 9750 6150 0    50   ~ 0
Ground
Text Label 9550 2550 0    50   ~ 0
Switch_Output
Wire Wire Line
	6000 3900 6000 4000
Wire Wire Line
	6000 4000 5900 4000
Wire Wire Line
	5300 4000 5300 3900
Connection ~ 6000 4000
Wire Wire Line
	6000 4000 6000 4200
Wire Wire Line
	5400 3900 5400 4000
Connection ~ 5400 4000
Wire Wire Line
	5400 4000 5300 4000
Wire Wire Line
	5500 3900 5500 4000
Connection ~ 5500 4000
Wire Wire Line
	5500 4000 5400 4000
Wire Wire Line
	5600 3900 5600 4000
Connection ~ 5600 4000
Wire Wire Line
	5600 4000 5500 4000
Wire Wire Line
	5700 3900 5700 4000
Connection ~ 5700 4000
Wire Wire Line
	5700 4000 5600 4000
Wire Wire Line
	5800 3900 5800 4000
Connection ~ 5800 4000
Wire Wire Line
	5800 4000 5700 4000
Wire Wire Line
	5900 3900 5900 4000
Connection ~ 5900 4000
Wire Wire Line
	5900 4000 5800 4000
Text Label 9800 4650 0    50   ~ 0
Vcc
$Comp
L power:GND #PWR02
U 1 1 5E1AF05C
P 2150 2800
F 0 "#PWR02" H 2150 2550 50  0001 C CNN
F 1 "GND" H 2155 2627 50  0001 C CNN
F 2 "" H 2150 2800 50  0001 C CNN
F 3 "" H 2150 2800 50  0001 C CNN
	1    2150 2800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5E1B5C57
P 1750 8250
F 0 "#PWR01" H 1750 8000 50  0001 C CNN
F 1 "GND" H 1755 8077 50  0001 C CNN
F 2 "" H 1750 8250 50  0001 C CNN
F 3 "" H 1750 8250 50  0001 C CNN
	1    1750 8250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5E1BE02E
P 7450 5900
F 0 "#PWR04" H 7450 5650 50  0001 C CNN
F 1 "GND" H 7455 5727 50  0001 C CNN
F 2 "" H 7450 5900 50  0001 C CNN
F 3 "" H 7450 5900 50  0001 C CNN
	1    7450 5900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5E1C5E8F
P 6000 4200
F 0 "#PWR03" H 6000 3950 50  0001 C CNN
F 1 "GND" H 6005 4027 50  0001 C CNN
F 2 "" H 6000 4200 50  0001 C CNN
F 3 "" H 6000 4200 50  0001 C CNN
	1    6000 4200
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5E1CFA03
P 9900 4900
F 0 "#PWR07" H 9900 4650 50  0001 C CNN
F 1 "GND" H 9905 4727 50  0001 C CNN
F 2 "" H 9900 4900 50  0001 C CNN
F 3 "" H 9900 4900 50  0001 C CNN
	1    9900 4900
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5E1D6CEE
P 9500 3600
F 0 "#PWR06" H 9500 3350 50  0001 C CNN
F 1 "GND" H 9505 3427 50  0001 C CNN
F 2 "" H 9500 3600 50  0001 C CNN
F 3 "" H 9500 3600 50  0001 C CNN
	1    9500 3600
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5E1DE3D3
P 10000 3050
F 0 "#PWR08" H 10000 2800 50  0001 C CNN
F 1 "GND" H 10005 2877 50  0001 C CNN
F 2 "" H 10000 3050 50  0001 C CNN
F 3 "" H 10000 3050 50  0001 C CNN
	1    10000 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5E1E542E
P 8950 2050
F 0 "#PWR05" H 8950 1800 50  0001 C CNN
F 1 "GND" H 8955 1877 50  0001 C CNN
F 2 "" H 8950 2050 50  0001 C CNN
F 3 "" H 8950 2050 50  0001 C CNN
	1    8950 2050
	1    0    0    -1  
$EndComp
Wire Wire Line
	9300 900  9450 900 
Wire Wire Line
	9450 900  10100 900 
Wire Wire Line
	9050 900  9450 900 
Wire Wire Line
	9450 1400 9950 1400
Text Notes 10250 2800 0    50   ~ 0
Red
Text Notes 6800 5650 0    50   ~ 0
Red
Text Label 7150 5150 0    50   ~ 0
DI
Text Label 7150 5250 0    50   ~ 0
CI
Wire Wire Line
	2450 8050 2850 8050
Connection ~ 2450 8050
Wire Wire Line
	2700 7200 2850 7200
Wire Wire Line
	2450 6550 4150 6550
Connection ~ 2450 6550
$Comp
L Device:CP1 C3
U 1 1 5E21353D
P 2850 7650
F 0 "C3" H 2965 7696 50  0000 L CNN
F 1 "2.2uf" H 2965 7605 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_Tantal_D5.5mm_P2.50mm" H 2850 7650 50  0001 C CNN
F 3 "~" H 2850 7650 50  0001 C CNN
	1    2850 7650
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 7500 2850 7200
Connection ~ 2850 7200
Wire Wire Line
	2850 7200 3650 7200
Wire Wire Line
	2850 7800 2850 8050
Connection ~ 2850 8050
Wire Wire Line
	2850 8050 3300 8050
Wire Wire Line
	2150 2550 2150 2800
Connection ~ 2150 2550
$Comp
L Mechanical:MountingHole H1
U 1 1 5834BC4A
P 1600 9750
F 0 "H1" H 1450 9850 60  0000 C CNN
F 1 "3mm_Mounting_Hole" H 1600 9600 60  0000 C CNN
F 2 "project_footprints:NPTH_3mm_ID" H 1500 9750 60  0001 C CNN
F 3 "" H 1500 9750 60  0001 C CNN
	1    1600 9750
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5834BCDF
P 2900 9750
F 0 "H3" H 2750 9850 60  0000 C CNN
F 1 "3mm_Mounting_Hole" H 2900 9600 60  0000 C CNN
F 2 "project_footprints:NPTH_3mm_ID" H 2800 9750 60  0001 C CNN
F 3 "" H 2800 9750 60  0001 C CNN
	1    2900 9750
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5834BD62
P 1600 10300
F 0 "H2" H 1450 10400 60  0000 C CNN
F 1 "3mm_Mounting_Hole" H 1600 10150 60  0000 C CNN
F 2 "project_footprints:NPTH_3mm_ID" H 1500 10300 60  0001 C CNN
F 3 "" H 1500 10300 60  0001 C CNN
	1    1600 10300
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5834BDED
P 2900 10350
F 0 "H4" H 2750 10450 60  0000 C CNN
F 1 "3mm_Mounting_Hole" H 2900 10200 60  0000 C CNN
F 2 "project_footprints:NPTH_3mm_ID" H 2800 10350 60  0001 C CNN
F 3 "" H 2800 10350 60  0001 C CNN
	1    2900 10350
	1    0    0    -1  
$EndComp
Text Notes 1450 9450 0    118  ~ 24
Mounting Holes
Text Label 4400 3150 2    60   ~ 0
GND
Text Notes 13300 11050 0    50   ~ 0
December 19, 2019
$Comp
L Connector_Generic:Conn_02x10_Top_Bottom J10
U 1 1 5E0000D2
P 6150 9150
F 0 "J10" H 6200 9767 50  0001 C CNN
F 1 "Pads" H 6200 9676 50  0001 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x10_P2.54mm_Vertical" H 6150 9150 50  0001 C CNN
F 3 "~" H 6150 9150 50  0001 C CNN
	1    6150 9150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x10_Top_Bottom J11
U 1 1 5E002B56
P 7200 9150
F 0 "J11" H 7250 9767 50  0001 C CNN
F 1 "Pads" H 7250 9676 50  0001 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x10_P2.54mm_Vertical" H 7200 9150 50  0001 C CNN
F 3 "~" H 7200 9150 50  0001 C CNN
	1    7200 9150
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x10_Top_Bottom J12
U 1 1 5E005A61
P 8250 9150
F 0 "J12" H 8300 9675 50  0001 C CNN
F 1 "Pads" H 8300 9676 50  0001 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x10_P2.54mm_Vertical" H 8250 9150 50  0001 C CNN
F 3 "~" H 8250 9150 50  0001 C CNN
	1    8250 9150
	1    0    0    -1  
$EndComp
$EndSCHEMATC
