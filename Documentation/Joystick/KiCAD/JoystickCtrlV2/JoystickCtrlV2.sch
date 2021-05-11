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
$Comp
L MCU_Module:Arduino_UNO_R3 A1
U 1 1 60633246
P 2450 4200
F 0 "A1" H 2450 5381 50  0000 C CNN
F 1 "Arduino_UNO_R3" H 2450 5290 50  0000 C CNN
F 2 "Module:Arduino_UNO_R3_WithMountingHoles" H 2450 4200 50  0001 C CIN
F 3 "https://www.arduino.cc/en/Main/arduinoBoardUno" H 2450 4200 50  0001 C CNN
	1    2450 4200
	1    0    0    -1  
$EndComp
$Comp
L MAX4519CSD:MAX4519CSD+ MUX1
U 1 1 6068889F
P 5350 5150
F 0 "MUX1" H 6550 5537 60  0000 C CNN
F 1 "MAX4519CSD+" H 6550 5431 60  0000 C CNN
F 2 "MAX4519CSD:MAX4519CSD&plus_" H 6550 5390 60  0001 C CNN
F 3 "" H 5350 5150 60  0000 C CNN
	1    5350 5150
	1    0    0    -1  
$EndComp
$Comp
L AD5242BRZ10:AD5242BRZ10 DigiPOT1
U 1 1 6068C48A
P 5700 3450
F 0 "DigiPOT1" H 6500 3837 60  0000 C CNN
F 1 "AD5242BRZ10" H 6500 3731 60  0000 C CNN
F 2 "AD5242BRZ10:AD5242BRZ10" H 6500 3690 60  0001 C CNN
F 3 "" H 5700 3450 60  0000 C CNN
	1    5700 3450
	1    0    0    -1  
$EndComp
$Comp
L TXS0104EDR:TXS0104EDR LvlShifter1
U 1 1 6068DCF2
P 5300 1750
F 0 "LvlShifter1" H 6500 2137 60  0000 C CNN
F 1 "TXS0104EDR" H 6500 2031 60  0000 C CNN
F 2 "TXS0104EDR:TXS0104EDR" H 6500 1990 60  0001 C CNN
F 3 "" H 5300 1750 60  0000 C CNN
	1    5300 1750
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J1
U 1 1 60694DDB
P 1250 3900
F 0 "J1" H 1358 4381 50  0000 C CNN
F 1 "Conn_01x08_Male" H 1358 4290 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 1250 3900 50  0001 C CNN
F 3 "~" H 1250 3900 50  0001 C CNN
	1    1250 3900
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J3
U 1 1 60696C2E
P 3650 3500
F 0 "J3" H 3622 3382 50  0000 R CNN
F 1 "Conn_01x08_Male" H 3622 3473 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 3650 3500 50  0001 C CNN
F 3 "~" H 3650 3500 50  0001 C CNN
	1    3650 3500
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x06_Male J4
U 1 1 606982AB
P 3650 4500
F 0 "J4" H 3622 4382 50  0000 R CNN
F 1 "Conn_01x06_Male" H 3622 4473 50  0000 R CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x06_P2.54mm_Vertical" H 3650 4500 50  0001 C CNN
F 3 "~" H 3650 4500 50  0001 C CNN
	1    3650 4500
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x10_Male J2
U 1 1 60698E49
P 1250 4800
F 0 "J2" H 1358 5381 50  0000 C CNN
F 1 "Conn_01x10_Male" H 1358 5290 50  0000 C CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x10_P2.54mm_Vertical" H 1250 4800 50  0001 C CNN
F 3 "~" H 1250 4800 50  0001 C CNN
	1    1250 4800
	1    0    0    -1  
$EndComp
Wire Wire Line
	1450 3600 1950 3600
Wire Wire Line
	1450 3800 1950 3800
Wire Wire Line
	1450 3700 1950 3700
Wire Wire Line
	1950 3900 1450 3900
Wire Wire Line
	1950 4000 1450 4000
Wire Wire Line
	1950 4100 1450 4100
Wire Wire Line
	1450 4200 1950 4200
Wire Wire Line
	1950 4300 1450 4300
Wire Wire Line
	1450 4400 1950 4400
Wire Wire Line
	1950 4500 1450 4500
Wire Wire Line
	1450 4600 1950 4600
Wire Wire Line
	1950 4900 1450 4900
Wire Wire Line
	1450 5000 1950 5000
Wire Wire Line
	1950 5000 1950 5350
Wire Wire Line
	1950 5350 2350 5350
Wire Wire Line
	2350 5350 2350 5300
Wire Wire Line
	1450 5100 1850 5100
Wire Wire Line
	1850 5100 1850 5450
Wire Wire Line
	1850 5450 3100 5450
Wire Wire Line
	3100 4000 2950 4000
Wire Wire Line
	1750 5200 1750 5550
Wire Wire Line
	1750 5550 3050 5550
Wire Wire Line
	3050 5550 3050 4900
Wire Wire Line
	3050 4900 2950 4900
Wire Wire Line
	2950 5000 2950 5600
Wire Wire Line
	2950 5600 1650 5600
Wire Wire Line
	1650 5600 1650 5300
Wire Wire Line
	1650 5300 1450 5300
Wire Wire Line
	2950 4200 3450 4200
Wire Wire Line
	2950 4300 3450 4300
Wire Wire Line
	3450 4400 2950 4400
Wire Wire Line
	2950 4500 3450 4500
Wire Wire Line
	2950 4700 3450 4700
Wire Wire Line
	2950 4600 3450 4600
Wire Wire Line
	2350 3200 2350 3100
Wire Wire Line
	2350 3100 3450 3100
Wire Wire Line
	2550 5300 2550 5750
Wire Wire Line
	2550 5750 3300 5750
Wire Wire Line
	3300 5750 3300 3200
Wire Wire Line
	3300 3200 3450 3200
Wire Wire Line
	3450 3300 3350 3300
Wire Wire Line
	3350 3300 3350 5800
Wire Wire Line
	3350 5800 2450 5800
Wire Wire Line
	2450 5800 2450 5300
Wire Wire Line
	3250 3200 3250 3400
Wire Wire Line
	3250 3400 3450 3400
Wire Wire Line
	2650 3200 3250 3200
Wire Wire Line
	2550 3200 2550 3150
Wire Wire Line
	2550 3150 3200 3150
Wire Wire Line
	3200 3150 3200 3500
Wire Wire Line
	3200 3500 3450 3500
Wire Wire Line
	3450 3600 2950 3600
Wire Wire Line
	3000 3700 3450 3700
Wire Wire Line
	2950 3800 3000 3800
Wire Wire Line
	3000 3800 3000 3700
$Comp
L Connector_Generic:Conn_02x04_Odd_Even Joystick1
U 1 1 606C8239
P 9600 3400
F 0 "Joystick1" H 9650 3717 50  0000 C CNN
F 1 "Conn_02x04_Odd_Even" H 9650 3626 50  0000 C CNN
F 2 "Connector_PinSocket_2.00mm:PinSocket_2x04_P2.00mm_Vertical" H 9600 3400 50  0001 C CNN
F 3 "~" H 9600 3400 50  0001 C CNN
	1    9600 3400
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x04_Odd_Even Controller1
U 1 1 606C936D
P 9600 4250
F 0 "Controller1" H 9650 4567 50  0000 C CNN
F 1 "Conn_02x04_Odd_Even" H 9650 4476 50  0000 C CNN
F 2 "Connector_PinSocket_2.00mm:PinSocket_2x04_P2.00mm_Vertical" H 9600 4250 50  0001 C CNN
F 3 "~" H 9600 4250 50  0001 C CNN
	1    9600 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 3300 9100 3300
Wire Wire Line
	9100 3300 9100 4150
Wire Wire Line
	9100 4150 9400 4150
Wire Wire Line
	9400 3400 9000 3400
Wire Wire Line
	9000 3400 9000 4250
Wire Wire Line
	9000 4250 9400 4250
Wire Wire Line
	9400 3500 9350 3500
Wire Wire Line
	9350 3500 9350 3200
Wire Wire Line
	9350 3200 9450 3200
Wire Wire Line
	9950 3200 9950 3400
Wire Wire Line
	9950 3400 9900 3400
Wire Wire Line
	9400 3600 9300 3600
Wire Wire Line
	9300 3600 9300 3150
Wire Wire Line
	9300 3150 10000 3150
Wire Wire Line
	10000 3150 10000 3300
Wire Wire Line
	10000 3300 9900 3300
Wire Wire Line
	9400 4350 9350 4350
Wire Wire Line
	9350 4350 9350 4050
Wire Wire Line
	9350 4050 9950 4050
Wire Wire Line
	9950 4050 9950 4250
Wire Wire Line
	9950 4250 9900 4250
Wire Wire Line
	9400 4450 9300 4450
Wire Wire Line
	9300 4450 9300 4000
Wire Wire Line
	9300 4000 10000 4000
Wire Wire Line
	10000 4000 10000 4150
Wire Wire Line
	10000 4150 9900 4150
Wire Wire Line
	9900 3500 10150 3500
Wire Wire Line
	10150 3500 10150 4350
Wire Wire Line
	10150 4350 9900 4350
$Comp
L power:GNDREF #PWR018
U 1 1 606AEBA9
P 10150 4350
F 0 "#PWR018" H 10150 4100 50  0001 C CNN
F 1 "GNDREF" H 10155 4177 50  0000 C CNN
F 2 "" H 10150 4350 50  0001 C CNN
F 3 "" H 10150 4350 50  0001 C CNN
	1    10150 4350
	1    0    0    -1  
$EndComp
Connection ~ 10150 4350
Text GLabel 9300 3150 0    50   Input ~ 0
Joy_X
Text GLabel 9300 3000 0    50   Input ~ 0
Joy_Y
Wire Wire Line
	9450 3000 9300 3000
Wire Wire Line
	9450 3000 9450 3200
Connection ~ 9450 3200
Wire Wire Line
	9450 3200 9950 3200
Text GLabel 9300 4000 0    50   Input ~ 0
Ctrl_X
Text GLabel 9300 3850 0    50   Input ~ 0
Ctrl_Y
Wire Wire Line
	9300 3850 9350 3850
Wire Wire Line
	9350 3850 9350 4050
Connection ~ 9350 4050
Text GLabel 1200 5200 0    50   Input ~ 0
Ard_SDA
Text GLabel 1200 5300 0    50   Input ~ 0
Ard_SCL
Wire Wire Line
	3100 5450 3100 4000
Wire Wire Line
	1200 5300 1450 5300
$Comp
L power:+2V5 #PWR017
U 1 1 606BD5FF
P 8550 3250
F 0 "#PWR017" H 8550 3100 50  0001 C CNN
F 1 "+2V5" H 8565 3423 50  0000 C CNN
F 2 "" H 8550 3250 50  0001 C CNN
F 3 "" H 8550 3250 50  0001 C CNN
	1    8550 3250
	1    0    0    -1  
$EndComp
$Comp
L power:-2V5 #PWR016
U 1 1 606BDCC0
P 8400 3400
F 0 "#PWR016" H 8400 3500 50  0001 C CNN
F 1 "-2V5" H 8415 3573 50  0000 C CNN
F 2 "" H 8400 3400 50  0001 C CNN
F 3 "" H 8400 3400 50  0001 C CNN
	1    8400 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9100 3300 8550 3300
Wire Wire Line
	8550 3300 8550 3250
Connection ~ 9100 3300
Wire Wire Line
	9000 3400 8400 3400
Connection ~ 9000 3400
$Comp
L power:+5V #PWR02
U 1 1 606C38FF
P 2650 3050
F 0 "#PWR02" H 2650 2900 50  0001 C CNN
F 1 "+5V" H 2665 3223 50  0000 C CNN
F 2 "" H 2650 3050 50  0001 C CNN
F 3 "" H 2650 3050 50  0001 C CNN
	1    2650 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2650 3200 2650 3050
Connection ~ 2650 3200
$Comp
L power:GNDREF #PWR01
U 1 1 606C6979
P 2450 5800
F 0 "#PWR01" H 2450 5550 50  0001 C CNN
F 1 "GNDREF" H 2455 5627 50  0000 C CNN
F 2 "" H 2450 5800 50  0001 C CNN
F 3 "" H 2450 5800 50  0001 C CNN
	1    2450 5800
	1    0    0    -1  
$EndComp
Connection ~ 2450 5800
$Comp
L power:GNDREF #PWR07
U 1 1 606C6FDC
P 5300 2350
F 0 "#PWR07" H 5300 2100 50  0001 C CNN
F 1 "GNDREF" H 5305 2177 50  0000 C CNN
F 2 "" H 5300 2350 50  0001 C CNN
F 3 "" H 5300 2350 50  0001 C CNN
	1    5300 2350
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR06
U 1 1 606C796C
P 5300 1750
F 0 "#PWR06" H 5300 1600 50  0001 C CNN
F 1 "+5V" H 5315 1923 50  0000 C CNN
F 2 "" H 5300 1750 50  0001 C CNN
F 3 "" H 5300 1750 50  0001 C CNN
	1    5300 1750
	1    0    0    -1  
$EndComp
$Comp
L power:+2V5 #PWR012
U 1 1 606C800C
P 7700 1750
F 0 "#PWR012" H 7700 1600 50  0001 C CNN
F 1 "+2V5" H 7715 1923 50  0000 C CNN
F 2 "" H 7700 1750 50  0001 C CNN
F 3 "" H 7700 1750 50  0001 C CNN
	1    7700 1750
	1    0    0    -1  
$EndComp
Text GLabel 5300 1850 0    50   Input ~ 0
Ard_SDA
Text GLabel 5300 1950 0    50   Input ~ 0
Ard_SCL
Text GLabel 5300 2050 0    50   Input ~ 0
Ard_MUX
Text GLabel 5250 5150 0    50   Input ~ 0
Ctrl_MUX
Wire Wire Line
	5250 5150 5350 5150
Wire Wire Line
	5350 5150 5350 4900
Wire Wire Line
	5350 4900 7750 4900
Wire Wire Line
	7750 4900 7750 5150
Connection ~ 5350 5150
$Comp
L power:+2V5 #PWR04
U 1 1 606D1A2E
P 4800 5250
F 0 "#PWR04" H 4800 5100 50  0001 C CNN
F 1 "+2V5" H 4815 5423 50  0000 C CNN
F 2 "" H 4800 5250 50  0001 C CNN
F 3 "" H 4800 5250 50  0001 C CNN
	1    4800 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5250 4800 5250
$Comp
L power:-2V5 #PWR03
U 1 1 606D54E9
P 4700 5350
F 0 "#PWR03" H 4700 5450 50  0001 C CNN
F 1 "-2V5" H 4715 5523 50  0000 C CNN
F 2 "" H 4700 5350 50  0001 C CNN
F 3 "" H 4700 5350 50  0001 C CNN
	1    4700 5350
	1    0    0    -1  
$EndComp
$Comp
L power:+2V5 #PWR014
U 1 1 606D5F91
P 7950 5350
F 0 "#PWR014" H 7950 5200 50  0001 C CNN
F 1 "+2V5" H 7965 5523 50  0000 C CNN
F 2 "" H 7950 5350 50  0001 C CNN
F 3 "" H 7950 5350 50  0001 C CNN
	1    7950 5350
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR015
U 1 1 606D705E
P 8100 5250
F 0 "#PWR015" H 8100 5000 50  0001 C CNN
F 1 "GNDREF" H 8105 5077 50  0000 C CNN
F 2 "" H 8100 5250 50  0001 C CNN
F 3 "" H 8100 5250 50  0001 C CNN
	1    8100 5250
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR09
U 1 1 606D79E2
P 7400 4250
F 0 "#PWR09" H 7400 4000 50  0001 C CNN
F 1 "GNDREF" H 7405 4077 50  0000 C CNN
F 2 "" H 7400 4250 50  0001 C CNN
F 3 "" H 7400 4250 50  0001 C CNN
	1    7400 4250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 3950 7400 3950
Wire Wire Line
	7400 3950 7400 4050
Wire Wire Line
	7300 4150 7400 4150
Connection ~ 7400 4150
Wire Wire Line
	7400 4150 7400 4250
Wire Wire Line
	7300 4050 7400 4050
Connection ~ 7400 4050
Wire Wire Line
	7400 4050 7400 4150
Wire Wire Line
	5700 3950 5600 3950
$Comp
L power:-2V5 #PWR011
U 1 1 606E5F75
P 7500 3850
F 0 "#PWR011" H 7500 3950 50  0001 C CNN
F 1 "-2V5" H 7515 4023 50  0000 C CNN
F 2 "" H 7500 3850 50  0001 C CNN
F 3 "" H 7500 3850 50  0001 C CNN
	1    7500 3850
	1    0    0    -1  
$EndComp
$Comp
L power:+2V5 #PWR05
U 1 1 606E6CCD
P 5200 3850
F 0 "#PWR05" H 5200 3700 50  0001 C CNN
F 1 "+2V5" H 5215 4023 50  0000 C CNN
F 2 "" H 5200 3850 50  0001 C CNN
F 3 "" H 5200 3850 50  0001 C CNN
	1    5200 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 3950 5600 3850
Connection ~ 5600 3850
Wire Wire Line
	5600 3850 5700 3850
Wire Wire Line
	7300 3850 7450 3850
Wire Wire Line
	5700 3450 5700 3150
Wire Wire Line
	5700 3150 6550 3150
Wire Wire Line
	6550 3150 6550 3000
Wire Wire Line
	7300 3750 7350 3750
Wire Wire Line
	7350 3750 7350 3200
Wire Wire Line
	7350 3200 6450 3200
Wire Wire Line
	6450 3200 6450 3000
Wire Wire Line
	7300 3650 7450 3650
Wire Wire Line
	7450 3650 7450 3850
Connection ~ 7450 3850
Wire Wire Line
	7450 3850 7500 3850
Wire Wire Line
	5600 3850 5600 3550
Wire Wire Line
	5600 3550 5700 3550
$Comp
L power:-2V5 #PWR08
U 1 1 607069A7
P 5350 3750
F 0 "#PWR08" H 5350 3850 50  0001 C CNN
F 1 "-2V5" H 5365 3923 50  0000 C CNN
F 2 "" H 5350 3750 50  0001 C CNN
F 3 "" H 5350 3750 50  0001 C CNN
	1    5350 3750
	1    0    0    -1  
$EndComp
$Comp
L power:+2V5 #PWR010
U 1 1 607078B0
P 7500 3450
F 0 "#PWR010" H 7500 3300 50  0001 C CNN
F 1 "+2V5" H 7515 3623 50  0000 C CNN
F 2 "" H 7500 3450 50  0001 C CNN
F 3 "" H 7500 3450 50  0001 C CNN
	1    7500 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 3450 7500 3450
Wire Wire Line
	5350 3750 5700 3750
Text GLabel 5700 3650 0    50   Input ~ 0
Digi_X
Text GLabel 7300 3550 2    50   Input ~ 0
Digi_Y
Text GLabel 5700 4150 0    50   Input ~ 0
Digi_SDA
Text GLabel 5700 4050 0    50   Input ~ 0
Digi_SCL
Text GLabel 7700 1950 2    50   Input ~ 0
Digi_SCL
Text GLabel 7700 1850 2    50   Input ~ 0
Digi_SDA
Text GLabel 7700 2050 2    50   Input ~ 0
Ctrl_MUX
Wire Wire Line
	5200 3850 5600 3850
$Comp
L Device:R R1
U 1 1 6071F76F
P 7700 2500
F 0 "R1" H 7770 2546 50  0000 L CNN
F 1 "10k" H 7770 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_1206_3216Metric" V 7630 2500 50  0001 C CNN
F 3 "~" H 7700 2500 50  0001 C CNN
	1    7700 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GNDREF #PWR013
U 1 1 6072064B
P 7700 2650
F 0 "#PWR013" H 7700 2400 50  0001 C CNN
F 1 "GNDREF" H 7705 2477 50  0000 C CNN
F 2 "" H 7700 2650 50  0001 C CNN
F 3 "" H 7700 2650 50  0001 C CNN
	1    7700 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 5350 5350 5350
Wire Wire Line
	7750 5350 7950 5350
Wire Wire Line
	8100 5250 7750 5250
Text GLabel 4800 5650 0    50   Input ~ 0
Ctrl_Y
Text GLabel 8450 5650 2    50   Input ~ 0
Ctrl_X
Text GLabel 4800 5550 0    50   Input ~ 0
Joy_Y
Text GLabel 8450 5550 2    50   Input ~ 0
Joy_X
Text GLabel 8450 5450 2    50   Input ~ 0
Digi_X
Text GLabel 4800 5450 0    50   Input ~ 0
Digi_Y
Wire Wire Line
	1200 4800 1450 4800
Connection ~ 1450 4800
Wire Wire Line
	1450 4800 1950 4800
Connection ~ 1450 5300
Connection ~ 1450 5200
Wire Wire Line
	1450 5200 1200 5200
Wire Wire Line
	1450 5200 1750 5200
Text GLabel 7750 2350 2    50   Input ~ 0
Shft_En
Wire Wire Line
	7750 2350 7700 2350
Connection ~ 7700 2350
Text GLabel 1200 4700 0    50   Input ~ 0
Shft_En
Wire Wire Line
	1200 4700 1450 4700
Connection ~ 1450 4700
Wire Wire Line
	1450 4700 1950 4700
$Comp
L Connector:Conn_01x01_Male J6
U 1 1 60758652
P 6550 2800
F 0 "J6" V 6612 2844 50  0000 L CNN
F 1 "O1" V 6703 2844 50  0000 L CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x01_P1.00mm_Vertical" H 6550 2800 50  0001 C CNN
F 3 "~" H 6550 2800 50  0001 C CNN
	1    6550 2800
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J5
U 1 1 60759E2A
P 6450 2800
F 0 "J5" V 6512 2844 50  0000 L CNN
F 1 "O2" V 6603 2844 50  0000 L CNN
F 2 "Connector_PinHeader_1.00mm:PinHeader_1x01_P1.00mm_Vertical" H 6450 2800 50  0001 C CNN
F 3 "~" H 6450 2800 50  0001 C CNN
	1    6450 2800
	0    1    1    0   
$EndComp
$Comp
L Connector:Conn_01x03_Male J7
U 1 1 6079BCD2
P 4950 5550
F 0 "J7" H 5058 5831 50  0000 C CNN
F 1 "Y" H 5058 5740 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 4950 5550 50  0001 C CNN
F 3 "~" H 4950 5550 50  0001 C CNN
	1    4950 5550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5350 5650 5250 5650
Wire Wire Line
	5250 5650 5250 5550
Wire Wire Line
	5250 5550 5150 5550
Wire Wire Line
	5150 5550 4900 5550
Wire Wire Line
	4900 5550 4900 5650
Wire Wire Line
	4900 5650 4800 5650
Connection ~ 5150 5550
Wire Wire Line
	5150 5650 5150 5750
Wire Wire Line
	5150 5750 5300 5750
Wire Wire Line
	5300 5750 5300 5550
Wire Wire Line
	5300 5550 5350 5550
Wire Wire Line
	4800 5450 5150 5450
Connection ~ 5150 5450
Wire Wire Line
	5150 5450 5350 5450
Wire Wire Line
	4800 5550 4850 5550
Wire Wire Line
	4850 5550 4850 5750
Wire Wire Line
	4850 5750 5150 5750
Connection ~ 5150 5750
$Comp
L Connector:Conn_01x03_Male J8
U 1 1 607C6587
P 8200 5550
F 0 "J8" H 8172 5482 50  0000 R CNN
F 1 "X" H 8172 5573 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 8200 5550 50  0001 C CNN
F 3 "~" H 8200 5550 50  0001 C CNN
	1    8200 5550
	-1   0    0    1   
$EndComp
Wire Wire Line
	7750 5450 8000 5450
Connection ~ 8000 5450
Wire Wire Line
	8000 5450 8450 5450
Wire Wire Line
	7750 5550 7900 5550
Wire Wire Line
	7900 5550 7900 5650
Wire Wire Line
	7900 5650 8000 5650
Wire Wire Line
	8000 5650 8250 5650
Wire Wire Line
	8250 5650 8250 5550
Wire Wire Line
	8250 5550 8450 5550
Connection ~ 8000 5650
Wire Wire Line
	8450 5650 8300 5650
Wire Wire Line
	8300 5650 8300 5700
Wire Wire Line
	8300 5700 7950 5700
Wire Wire Line
	7800 5700 7800 5650
Wire Wire Line
	7800 5650 7750 5650
Wire Wire Line
	8000 5550 7950 5550
Wire Wire Line
	7950 5550 7950 5700
Connection ~ 7950 5700
Wire Wire Line
	7950 5700 7800 5700
Text GLabel 1200 4800 0    50   Input ~ 0
Ard_MUX
$Comp
L power:GNDREF #PWR?
U 1 1 6082FB5A
P 2350 5350
F 0 "#PWR?" H 2350 5100 50  0001 C CNN
F 1 "GNDREF" H 2355 5177 50  0000 C CNN
F 2 "" H 2350 5350 50  0001 C CNN
F 3 "" H 2350 5350 50  0001 C CNN
	1    2350 5350
	1    0    0    -1  
$EndComp
Connection ~ 2350 5350
$Comp
L power:GNDREF #PWR?
U 1 1 60830870
P 2550 5750
F 0 "#PWR?" H 2550 5500 50  0001 C CNN
F 1 "GNDREF" H 2555 5577 50  0000 C CNN
F 2 "" H 2550 5750 50  0001 C CNN
F 3 "" H 2550 5750 50  0001 C CNN
	1    2550 5750
	1    0    0    -1  
$EndComp
Connection ~ 2550 5750
$EndSCHEMATC
