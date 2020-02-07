EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
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
P 1050 1050
F 0 "J1" H 1158 1231 50  0000 C CNN
F 1 "+5V Power" H 1158 1140 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 1050 1050 50  0001 C CNN
F 3 "~" H 1050 1050 50  0001 C CNN
	1    1050 1050
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 5DF97861
P 1050 1500
F 0 "J2" H 1158 1681 50  0000 C CNN
F 1 "+5V RPi Power" H 1158 1590 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 1050 1500 50  0001 C CNN
F 3 "~" H 1050 1500 50  0001 C CNN
	1    1050 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C2
U 1 1 5DFA1E24
P 1800 1900
F 0 "C2" H 1915 1946 50  0000 L CNN
F 1 "10uf" H 1915 1855 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_Tantal_D5.0mm_P2.50mm" H 1800 1900 50  0001 C CNN
F 3 "~" H 1800 1900 50  0001 C CNN
	1    1800 1900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 1500 1450 1500
Text GLabel 5350 1000 2    50   Input ~ 0
RPi+3.3V
Text GLabel 2050 1150 2    50   Input ~ 0
Vs+5V
Text GLabel 3700 1000 0    50   Input ~ 0
RPi+5V
Text GLabel 5750 2700 2    50   Input ~ 0
SPI_CS0
Text GLabel 5750 2600 2    50   Input ~ 0
SPI_CS1
Text GLabel 5750 2900 2    50   Input ~ 0
SPI_MOSI
Text GLabel 5750 2800 2    50   Input ~ 0
SPI_MISO
Text GLabel 5750 3000 2    50   Input ~ 0
SPI_CLK
$Comp
L Sensor_Temperature:TMP36GT9Z U1
U 1 1 5DFDBBFF
P 2450 5100
F 0 "U1" H 2322 5146 50  0000 R CNN
F 1 "TMP36GT9Z" H 2322 5055 50  0000 R CNN
F 2 "Package_TO_SOT_THT:TO-92L_HandSolder" H 2250 5350 50  0001 C CNN
F 3 "" H 2250 5350 50  0001 C CNN
	1    2450 5100
	1    0    0    -1  
$EndComp
$Comp
L Analog_ADC:MCP3002 U2
U 1 1 5DFDCAE0
P 4150 5300
F 0 "U2" H 4250 5981 50  0000 C CNN
F 1 "MCP3002" H 4400 5850 50  0000 C CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 4150 5200 50  0001 C CNN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/21294E.pdf" H 4150 5500 50  0001 C CNN
	1    4150 5300
	1    0    0    -1  
$EndComp
Text GLabel 1350 4450 0    50   Input ~ 0
RPi+3.3V
$Comp
L Device:C C1
U 1 1 5DFE73E9
P 1750 4750
F 0 "C1" H 1865 4796 50  0000 L CNN
F 1 "1uf" H 1865 4705 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D3.0mm_W1.6mm_P2.50mm" H 1788 4600 50  0001 C CNN
F 3 "~" H 1750 4750 50  0001 C CNN
	1    1750 4750
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 4600 1750 4450
Connection ~ 1750 5950
Wire Wire Line
	1750 5950 1750 6150
Wire Wire Line
	1350 4450 1750 4450
Connection ~ 1750 4450
Wire Wire Line
	3650 5500 3300 5500
Wire Wire Line
	3300 5500 3300 5950
Wire Wire Line
	1750 5950 2450 5950
Wire Wire Line
	1750 4900 1750 5950
Wire Wire Line
	4150 5800 4150 5950
Wire Wire Line
	4150 5950 3300 5950
Connection ~ 3300 5950
Wire Wire Line
	1250 1050 1450 1050
Wire Wire Line
	1450 1050 1450 1500
Connection ~ 1450 1500
Wire Wire Line
	1250 1150 1800 1150
Wire Wire Line
	1450 1500 1450 2150
Wire Wire Line
	1800 1150 1800 1600
Connection ~ 1800 1150
Wire Wire Line
	1800 1150 2050 1150
Wire Wire Line
	1250 1600 1800 1600
Wire Wire Line
	1800 2150 1450 2150
Wire Wire Line
	1800 1600 1800 1750
Connection ~ 1800 1600
Wire Wire Line
	1800 2050 1800 2150
Wire Wire Line
	2450 5450 2450 5950
Wire Wire Line
	1750 4450 2450 4450
Wire Wire Line
	2450 4750 2450 4450
Wire Wire Line
	4150 4800 4150 4450
Text GLabel 5200 5200 2    50   Input ~ 0
SPI_CLK
Text GLabel 5200 5100 2    50   Input ~ 0
SPI_CS1
Text GLabel 5200 5400 2    50   Input ~ 0
SPI_MISO
Text GLabel 5200 5500 2    50   Input ~ 0
SPI_MOSI
Wire Wire Line
	5200 5100 4850 5100
Wire Wire Line
	4850 5200 5200 5200
Wire Wire Line
	5200 5400 4850 5400
Wire Wire Line
	4850 5500 5200 5500
$Comp
L Connector:Conn_01x05_Male J4
U 1 1 5E02F2B8
P 6050 4300
F 0 "J4" H 6158 4681 50  0000 C CNN
F 1 "Lights" H 6158 4590 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 6050 4300 50  0001 C CNN
F 3 "~" H 6050 4300 50  0001 C CNN
	1    6050 4300
	1    0    0    -1  
$EndComp
Text GLabel 6650 4100 2    50   Input ~ 0
SPI_MOSI
Text GLabel 6650 4200 2    50   Input ~ 0
SPI_CLK
Text GLabel 6650 4300 2    50   Input ~ 0
Vs+5V
Text GLabel 6650 4400 2    50   Input ~ 0
RPi+5V
Wire Wire Line
	6250 4100 6650 4100
Wire Wire Line
	6250 4200 6650 4200
Wire Wire Line
	6250 4300 6650 4300
Wire Wire Line
	6250 4400 6650 4400
Wire Wire Line
	6250 4500 6650 4500
Wire Wire Line
	6650 4500 6650 4850
$Comp
L Connector:Conn_01x03_Male J6
U 1 1 5E041DB6
P 9750 2650
F 0 "J6" H 9722 2674 50  0000 R CNN
F 1 "Switch" H 9722 2583 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 9750 2650 50  0001 C CNN
F 3 "~" H 9750 2650 50  0001 C CNN
	1    9750 2650
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J8
U 1 1 5E043C5F
P 9850 5350
F 0 "J8" H 9822 5374 50  0000 R CNN
F 1 "Volume control" H 9822 5283 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 9850 5350 50  0001 C CNN
F 3 "~" H 9850 5350 50  0001 C CNN
	1    9850 5350
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x02_Male J9
U 1 1 5E0461CC
P 9850 6000
F 0 "J9" H 9958 6181 50  0000 C CNN
F 1 "RPi Audio (1 channel)" H 9958 6090 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x02_P2.54mm_Vertical" H 9850 6000 50  0001 C CNN
F 3 "~" H 9850 6000 50  0001 C CNN
	1    9850 6000
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x05_Male J7
U 1 1 5E048BAB
P 9850 4500
F 0 "J7" H 9958 4881 50  0000 C CNN
F 1 "Amplifier" H 9958 4790 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x05_P2.54mm_Vertical" H 9850 4500 50  0001 C CNN
F 3 "~" H 9850 4500 50  0001 C CNN
	1    9850 4500
	-1   0    0    -1  
$EndComp
$Comp
L Device:R_US R2
U 1 1 5E073B4C
P 8950 2950
F 0 "R2" H 9018 2996 50  0000 L CNN
F 1 "2.2K" H 9018 2905 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 8990 2940 50  0001 C CNN
F 3 "~" H 8950 2950 50  0001 C CNN
	1    8950 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R3
U 1 1 5E075E7E
P 8950 3350
F 0 "R3" H 9018 3396 50  0000 L CNN
F 1 "3.3K" H 9018 3305 50  0000 L CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 8990 3340 50  0001 C CNN
F 3 "~" H 8950 3350 50  0001 C CNN
	1    8950 3350
	1    0    0    -1  
$EndComp
$Comp
L Connector:Raspberry_Pi_2_3 J3
U 1 1 5E08C9EE
P 4500 2500
F 0 "J3" H 4500 3981 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 5150 3800 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x20_P2.54mm_Vertical" H 4500 2500 50  0001 C CNN
F 3 "https://www.raspberrypi.org/documentation/hardware/raspberrypi/schematics/rpi_SCH_3bplus_1p0_reduced.pdf" H 4500 2500 50  0001 C CNN
	1    4500 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3700 1000 4300 1000
Wire Wire Line
	4400 1000 4400 1200
Wire Wire Line
	4300 1200 4300 1000
Connection ~ 4300 1000
Wire Wire Line
	4300 1000 4400 1000
Wire Wire Line
	4600 1000 4600 1200
Wire Wire Line
	5350 1000 4700 1000
Wire Wire Line
	4700 1200 4700 1000
Connection ~ 4700 1000
Wire Wire Line
	4700 1000 4600 1000
Wire Wire Line
	5300 2600 5750 2600
Wire Wire Line
	5750 2700 5300 2700
Wire Wire Line
	5300 2800 5750 2800
Wire Wire Line
	5750 2900 5300 2900
Wire Wire Line
	5300 3000 5750 3000
Text GLabel 8950 4600 0    50   Input ~ 0
Vs+5V
Text GLabel 3300 2000 0    50   Input ~ 0
FAN
Wire Wire Line
	3300 2000 3700 2000
Text GLabel 8850 2550 0    50   Input ~ 0
RPi+5V
Wire Wire Line
	8950 3200 8950 3150
Wire Wire Line
	8950 2650 9550 2650
Wire Wire Line
	9550 2750 9450 2750
Wire Wire Line
	8850 2550 9550 2550
Wire Wire Line
	8950 2800 8950 2650
Text GLabel 3300 3000 0    50   Input ~ 0
SWITCH_INPUT
Wire Wire Line
	3300 3000 3700 3000
Text GLabel 8600 3150 0    50   Input ~ 0
SWITCH_INPUT
Wire Wire Line
	8600 3150 8950 3150
Connection ~ 8950 3150
Wire Wire Line
	8950 3150 8950 3100
Wire Wire Line
	8950 3500 8950 3700
Wire Wire Line
	9450 2750 9450 3150
Wire Wire Line
	9150 4700 9150 4850
Text GLabel 3300 2500 0    50   Input ~ 0
AMP_ENBL
Wire Wire Line
	3300 2500 3700 2500
Text GLabel 8300 4500 0    50   Input ~ 0
AMP_ENBL
Wire Wire Line
	8550 4300 8550 5350
Wire Wire Line
	8700 5450 8700 6000
Wire Wire Line
	8550 4300 9650 4300
Wire Wire Line
	8450 4400 9650 4400
Wire Wire Line
	8300 4500 9650 4500
Wire Wire Line
	8950 4600 9650 4600
Wire Wire Line
	9150 4700 9650 4700
Wire Wire Line
	8450 4400 8450 5250
Wire Wire Line
	8450 5250 9650 5250
Connection ~ 8450 5250
Wire Wire Line
	8450 5250 8450 6100
Wire Wire Line
	8550 5350 9650 5350
Wire Wire Line
	8700 5450 9650 5450
Wire Wire Line
	8700 6000 9650 6000
Wire Wire Line
	8450 6100 9650 6100
Text Label 9050 4500 0    50   ~ 0
Select
Text Label 9050 4400 0    50   ~ 0
Sig.Ground
Text Label 9050 4300 0    50   ~ 0
Signal
Text Label 9250 4700 0    50   ~ 0
Pwr.Ground
Text Label 9200 5250 0    50   ~ 0
Ground
Text Label 9200 5350 0    50   ~ 0
Variable
Text Label 9200 5450 0    50   ~ 0
Input
Text Label 9000 6000 0    50   ~ 0
Audio
Text Label 9000 6100 0    50   ~ 0
Ground
Text Label 9000 2650 0    50   ~ 0
Switch_Output
Wire Wire Line
	4800 3800 4800 3900
Wire Wire Line
	4800 3900 4700 3900
Wire Wire Line
	4100 3900 4100 3800
Connection ~ 4800 3900
Wire Wire Line
	4800 3900 4800 4100
Wire Wire Line
	4200 3800 4200 3900
Connection ~ 4200 3900
Wire Wire Line
	4200 3900 4100 3900
Wire Wire Line
	4300 3800 4300 3900
Connection ~ 4300 3900
Wire Wire Line
	4300 3900 4200 3900
Wire Wire Line
	4400 3800 4400 3900
Connection ~ 4400 3900
Wire Wire Line
	4400 3900 4300 3900
Wire Wire Line
	4500 3800 4500 3900
Connection ~ 4500 3900
Wire Wire Line
	4500 3900 4400 3900
Wire Wire Line
	4600 3800 4600 3900
Connection ~ 4600 3900
Wire Wire Line
	4600 3900 4500 3900
Wire Wire Line
	4700 3800 4700 3900
Connection ~ 4700 3900
Wire Wire Line
	4700 3900 4600 3900
Text Label 9050 4600 0    50   ~ 0
Vcc
$Comp
L power:GND #PWR02
U 1 1 5E1AF05C
P 1450 2400
F 0 "#PWR02" H 1450 2150 50  0001 C CNN
F 1 "GND" H 1455 2227 50  0001 C CNN
F 2 "" H 1450 2400 50  0001 C CNN
F 3 "" H 1450 2400 50  0001 C CNN
	1    1450 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5E1B5C57
P 1750 6150
F 0 "#PWR01" H 1750 5900 50  0001 C CNN
F 1 "GND" H 1755 5977 50  0001 C CNN
F 2 "" H 1750 6150 50  0001 C CNN
F 3 "" H 1750 6150 50  0001 C CNN
	1    1750 6150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 5E1BE02E
P 6650 4850
F 0 "#PWR04" H 6650 4600 50  0001 C CNN
F 1 "GND" H 6655 4677 50  0001 C CNN
F 2 "" H 6650 4850 50  0001 C CNN
F 3 "" H 6650 4850 50  0001 C CNN
	1    6650 4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5E1C5E8F
P 4800 4100
F 0 "#PWR03" H 4800 3850 50  0001 C CNN
F 1 "GND" H 4805 3927 50  0001 C CNN
F 2 "" H 4800 4100 50  0001 C CNN
F 3 "" H 4800 4100 50  0001 C CNN
	1    4800 4100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5E1CFA03
P 9150 4850
F 0 "#PWR07" H 9150 4600 50  0001 C CNN
F 1 "GND" H 9155 4677 50  0001 C CNN
F 2 "" H 9150 4850 50  0001 C CNN
F 3 "" H 9150 4850 50  0001 C CNN
	1    9150 4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5E1D6CEE
P 8950 3700
F 0 "#PWR06" H 8950 3450 50  0001 C CNN
F 1 "GND" H 8955 3527 50  0001 C CNN
F 2 "" H 8950 3700 50  0001 C CNN
F 3 "" H 8950 3700 50  0001 C CNN
	1    8950 3700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5E1DE3D3
P 9450 3150
F 0 "#PWR08" H 9450 2900 50  0001 C CNN
F 1 "GND" H 9455 2977 50  0001 C CNN
F 2 "" H 9450 3150 50  0001 C CNN
F 3 "" H 9450 3150 50  0001 C CNN
	1    9450 3150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5E1E542E
P 8650 2050
F 0 "#PWR05" H 8650 1800 50  0001 C CNN
F 1 "GND" H 8655 1877 50  0001 C CNN
F 2 "" H 8650 2050 50  0001 C CNN
F 3 "" H 8650 2050 50  0001 C CNN
	1    8650 2050
	1    0    0    -1  
$EndComp
Text Notes 9700 2450 0    50   ~ 0
Red
Text Notes 6000 3850 0    50   ~ 0
Red
Text Label 6350 4100 0    50   ~ 0
DI
Text Label 6350 4200 0    50   ~ 0
CI
Wire Wire Line
	2450 5950 2850 5950
Connection ~ 2450 5950
Wire Wire Line
	2700 5100 2850 5100
Wire Wire Line
	2450 4450 4150 4450
Connection ~ 2450 4450
$Comp
L Device:CP1 C3
U 1 1 5E21353D
P 2850 5550
F 0 "C3" H 2965 5596 50  0000 L CNN
F 1 "2.2uf" H 2965 5505 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_Tantal_D5.5mm_P2.50mm" H 2850 5550 50  0001 C CNN
F 3 "~" H 2850 5550 50  0001 C CNN
	1    2850 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2850 5400 2850 5100
Connection ~ 2850 5100
Wire Wire Line
	2850 5100 3650 5100
Wire Wire Line
	2850 5700 2850 5950
Connection ~ 2850 5950
Wire Wire Line
	2850 5950 3300 5950
Wire Wire Line
	1450 2150 1450 2400
Connection ~ 1450 2150
$Comp
L Mechanical:MountingHole H1
U 1 1 5834BC4A
P 1300 7100
F 0 "H1" H 1150 7200 60  0000 C CNN
F 1 "3mm_Mounting_Hole" H 1300 6950 60  0000 C CNN
F 2 "project_footprints:NPTH_3mm_ID" H 1200 7100 60  0001 C CNN
F 3 "" H 1200 7100 60  0001 C CNN
	1    1300 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5834BCDF
P 2600 7100
F 0 "H3" H 2450 7200 60  0000 C CNN
F 1 "3mm_Mounting_Hole" H 2600 6950 60  0000 C CNN
F 2 "project_footprints:NPTH_3mm_ID" H 2500 7100 60  0001 C CNN
F 3 "" H 2500 7100 60  0001 C CNN
	1    2600 7100
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5834BD62
P 1300 7650
F 0 "H2" H 1150 7750 60  0000 C CNN
F 1 "3mm_Mounting_Hole" H 1300 7500 60  0000 C CNN
F 2 "project_footprints:NPTH_3mm_ID" H 1200 7650 60  0001 C CNN
F 3 "" H 1200 7650 60  0001 C CNN
	1    1300 7650
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H4
U 1 1 5834BDED
P 2600 7700
F 0 "H4" H 2450 7800 60  0000 C CNN
F 1 "3mm_Mounting_Hole" H 2600 7550 60  0000 C CNN
F 2 "project_footprints:NPTH_3mm_ID" H 2500 7700 60  0001 C CNN
F 3 "" H 2500 7700 60  0001 C CNN
	1    2600 7700
	1    0    0    -1  
$EndComp
Text Notes 1150 6800 0    118  ~ 24
Mounting Holes
$Comp
L Connector_Generic:Conn_02x10_Top_Bottom J10
U 1 1 5E0000D2
P 4000 7250
F 0 "J10" H 4050 7867 50  0001 C CNN
F 1 "Pads" H 4050 7776 50  0001 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x10_P2.54mm_Vertical" H 4000 7250 50  0001 C CNN
F 3 "~" H 4000 7250 50  0001 C CNN
	1    4000 7250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x10_Top_Bottom J11
U 1 1 5E002B56
P 4850 7250
F 0 "J11" H 4900 7867 50  0001 C CNN
F 1 "Pads" H 4900 7776 50  0001 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x10_P2.54mm_Vertical" H 4850 7250 50  0001 C CNN
F 3 "~" H 4850 7250 50  0001 C CNN
	1    4850 7250
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x10_Top_Bottom J12
U 1 1 5E005A61
P 5650 7250
F 0 "J12" H 5700 7775 50  0001 C CNN
F 1 "Pads" H 5700 7776 50  0001 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_2x10_P2.54mm_Vertical" H 5650 7250 50  0001 C CNN
F 3 "~" H 5650 7250 50  0001 C CNN
	1    5650 7250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 1400 9650 1400
Wire Wire Line
	9150 900  9800 900 
Wire Wire Line
	7550 1700 7800 1700
Text GLabel 7550 1700 0    50   Input ~ 0
FAN
Wire Wire Line
	8650 1400 9150 1400
Connection ~ 9150 1400
Wire Wire Line
	9150 1350 9150 1400
Connection ~ 9150 900 
Wire Wire Line
	8100 1700 8350 1700
Wire Wire Line
	8650 1900 8650 2050
Wire Wire Line
	9650 1000 9800 1000
Wire Wire Line
	9650 1400 9650 1000
Wire Wire Line
	8650 1400 8650 1500
Wire Wire Line
	9150 1050 9150 900 
$Comp
L Device:R_US R1
U 1 1 5E071A40
P 7950 1700
F 0 "R1" V 7745 1700 50  0000 C CNN
F 1 "2K" V 7836 1700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0204_L3.6mm_D1.6mm_P7.62mm_Horizontal" V 7990 1690 50  0001 C CNN
F 3 "~" H 7950 1700 50  0001 C CNN
	1    7950 1700
	0    1    1    0   
$EndComp
$Comp
L Transistor_BJT:2N2219 Q1
U 1 1 5E06868C
P 8550 1700
F 0 "Q1" H 8740 1746 50  0000 L CNN
F 1 "2N2222" H 8740 1655 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_HandSolder" H 8750 1625 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/2N2219-D.PDF" H 8550 1700 50  0001 L CNN
	1    8550 1700
	1    0    0    -1  
$EndComp
$Comp
L Diode:1N914 D1
U 1 1 5E05F788
P 9150 1200
F 0 "D1" V 9104 1279 50  0000 L CNN
F 1 "HEP170" V 9195 1279 50  0000 L CNN
F 2 "Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal" H 9150 1025 50  0001 C CNN
F 3 "http://www.vishay.com/docs/85622/1n914.pdf" H 9150 1200 50  0001 C CNN
	1    9150 1200
	0    1    1    0   
$EndComp
Text GLabel 8750 900  0    50   Input ~ 0
Vs+5V
$Comp
L Connector:Conn_01x03_Male J5
U 1 1 5E040113
P 10000 1000
F 0 "J5" H 9972 1024 50  0000 R CNN
F 1 "Fan" H 9972 933 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x03_P2.54mm_Vertical" H 10000 1000 50  0001 C CNN
F 3 "~" H 10000 1000 50  0001 C CNN
	1    10000 1000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9000 900  9150 900 
Wire Wire Line
	8750 900  9150 900 
Text Notes 7450 7850 0    50   ~ 0
January 26, 2020
Text Notes 9700 800  0    50   ~ 0
Red
Text Notes 9450 5800 0    50   ~ 0
Red
Text Notes 9450 5100 0    50   ~ 0
Red
Text Notes 950  1250 0    50   ~ 0
Red
Text Notes 950  1700 0    50   ~ 0
Red
Text Notes 9950 6100 0    50   ~ 0
Pins
Text Notes 9950 5250 0    50   ~ 0
Pins
Text Notes 10050 850  0    50   ~ 0
Pins
Text Notes 5750 4300 0    50   ~ 0
Pins
Text Notes 750  1100 0    50   ~ 0
Pins
Text Notes 750  1550 0    50   ~ 0
Pins
Text Notes 9650 2900 0    50   ~ 0
Socket
Text Notes 9950 4550 0    50   ~ 0
Socket
$EndSCHEMATC
