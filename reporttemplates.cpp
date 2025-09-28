#include "reporttemplates.h"

QString ReportTemplates::Ate_Self_Test_Report()
{
    return R"(
<html>
<body>    
<html><h2 style="text-align:center;">ATE SELF TEST REPORT</h2>
<table border="1" cellspacing="0" cellpadding="6" width="100%"style="text-align:center;">
<tr><th colspan="2">Project Name</th><td colspan="3">FTU SRU LRU ATE</td><th colspan='2'>ATE BEL P/N</th><td colspan='3'>1104 005 449 56</td></tr>
<tr><th colspan='2'>Test Date</th><td colspan='2'>{{DD-MM-YYYY}}</td><th colspan='2'>ATE Sl. No.</th><td>001</td><th colspan='2'>Test Time</th><td>{{HH:MM:SEC}}</td></tr>
<tr><th colspan='2'>ATE Checksum</th><td colspan="3">{{xxxxx}}</td><th colspan="2">Tested By</th><td colspan='3'>{{TESTED_BY}}</td></tr>
 <tr><th>User Remarks</th><td colspan='10'>{{Remarks}}</td></tr></table>
</table>
<h3 style="text-align:center;">ATE Internal Voltages/USB 4716 AE CARD 1</h3>
<table border="1" cellspacing="0" cellpadding="6" width="100%"style="text-align:center;">
<tr><th>S. No</th><th colspan='2'>Test Name</th><th colspan='2'>Expected Voltage</th><th colspan='2'>Observed Voltage</th><th colspan='2'>Current</th><th 
colspan='2'>Result</th></tr>
<tr><td>1</td><td colspan='2' style="text-align:left;">SRU Supply 3.3V</td><td colspan='2'>3.3±0.2V</td><td colspan='2'>{{SV3_OBS}}</td><td colspan='2'>{{I_3.3v}}</td><td 
colspan='2'>{{R_3}}</td></tr>
<tr><td>2</td><td colspan='2' style="text-align:left;">SRU Supply +5V</td><td colspan='2'>+5±0.2V</td><td colspan='2'>{{SV1_OBS}}</td><td colspan='2'>{{I_+5v}}</td><td colspan
='2'>{{R_PS5}}</td></tr>
<tr><td>3</td><td colspan='2' style="text-align:left;">SRU Supply -5V</td><td colspan='2'>-5±0.2V</td><td colspan='2'>{{SV2_OBS}}</td><td colspan='2'>{{I_-5v}}</td><td colspan
='2'>{{R_PS6}}</td></tr>
<tr><td>4</td><td colspan='2' style="text-align:left;">Internal Relay Cards Supply 5V</td><td colspan='2'>5±0.2V</td><td colspan='2'>{{IV1_OBS}}</td><td colspan='2'>{{I_5v}}
</td><td colspan='2'>{{R_PS3}}
</td></tr>
<tr><td>6</td><td colspan='2' style="text-align:left;"style="text-align:left;">LRU Voltage 16V
</td><td colspan='2'>16±1V</td><td colspan='2'>{{LV1_OBS}}</td><td colspan='2'>{{I_16v}}</td><td colspan='2'>
{{R_1}}</td></tr>
<tr><td>7</td><td colspan='2'style="text-align:left;" >LRU Voltage 28V </td><td colspan='2'>28±1V</td><td colspan='2'> {{LV2_OBS}} </td><td colspan='2'>{{I_28v}}</td><td colspan='2'>
{{R_2}}</td></tr>
<tr><td>8</td><td colspan='2' style="text-align:left;">LRU Voltage 32V</td><td colspan='2'>32±1V</td><td colspan='2'>{{LV3_OBS}}</td><td colspan='2'>{{I_32v}}</td><td colspan='2'>
{{R_32}}</td></tr>
<!--

<tr><td>9</td><td colspan='2' style="text-align:left;">External V</td><td colspan='2'>28±1V</td><td colspan='2'>{{EXT_VOl}}</td><td colspan='2'>{{I_28vExt}}</td><td colspan='2'>{{EXT_Res}}</td></tr>-->

<tr><th colspan='10'>USB 5856 AE Cards Loop Back Checks</th></tr>
<tr><th>Cards SL.No</th><th colspan='2'>Expected Outputs</th><th colspan='2'>Observed Outputs <th colspan='2'>Expected Inputs</th><th colspan='2'>Observed Inputs</th><th colspan='3'>RESULTS</th></tr>
<tr><td>1</td><td colspan='2'>13BDEDD</td><td colspan='2'>{{op_C1}}</td><td colspan='2'>5</td><td colspan='2'>{{ip_C1}}</td><td colspan='3'>{{r1_c}}</td></tr>
<tr><td>2</td><td colspan='2'>3FFFF3FF</td><td colspan='2'>{{op_C2}}</td><td colspan='2'>3FFFF3FF</td><td colspan='2'>{{ip_C2}}</td><td colspan='3'>{{r2_c}}</td></tr>
<tr><td>3</td><td colspan='2'>3FFFFFFF</td><td colspan='2'>{{op_C3}}</td><td colspan='2'>3FFFFFFF</td><td colspan='2'>{{ip_C3}}</td><td colspan='3'>{{r3_c}}</td></tr>
<tr><td>4</td><td colspan='2'>FF4C075F</td><td colspan='2'>{{op_C4}}</td><td colspan='2'>20043</td><td colspan='2'>{{ip_C4}}</td><td colspan='3'>{{r4_c}}</td></tr>
<tr><th colspan='10'>RS422 Loop Back Checks</th></tr>
<tr><th colspan='10'>Channel 1</th></tr>
<tr><td colspan='4'>TX DATA with Timestamp</td><td colspan='7'>{{tx1_data}}</td></tr>
<tr><td colspan='4'>RX DATA with Timestamp</td><td colspan='7'>{{rx1_data}}</td></tr>
<tr><td colspan='4'>RESULT</td><td colspan='7'>{{CH1_RES}}</td></tr>
	<tr><th colspan='10'>Channel 2</th></tr>
<tr><td colspan='4'>TX DATA with Timestamp</td><td colspan='7'> {{tx2_data}}</td></tr>
<tr><td colspan='4'>RX DATA with Timestamp</td><td colspan='7'>{{rx2_data}}</td></tr>
<tr><td colspan='4'>RESULT</td><td colspan='7'>{{CH2_RES}}</td></tr>
<tr><th colspan='12'>USB 4716 AE CARD 2</th></tr>

<tr><th rowspan='3'>Expected voltages</th><th rowspan='3'>Tolerance Range</th><th rowspan='2'colspan='8' >Observed Voltages</th></tr>
<tr>
<tr><th>Analog Input ch1</th><th>Analog input ch2</th><th>Analog 
input ch3</th><th>Analog input ch4</th><th>Analog input ch5</th><th>Analog input ch6</th><th>Analog input ch7</th><th>Analog 
input ch8</th></tr>
<tr><th rowspan='2'>2.0V</th><th rowspan='2'>1.8V to
2.2V</th><td>{{ch_1}}</td><td>{{ch_2}}</td><td>{{ch_3}}</td><td>{{ch_4}}
</td><td>{{ch_5}}</td><td>{{ch_6}}</td><td>{{ch_7}}</td><td>{{ch_8}}</td></tr>

<tr><td>{{1pass_1}}</td><td>{{1pass_2}}</td><td>{{1pass_3}}</td><td>{{1pass_4}}</td><td>{{1pass_5}}</td><td>
{{1pass_6}}</td><td>{{1pass_7}}</td><td>{{1pass_8}}</td></tr>


<tr><th rowspan='2'>1.75V</th><th rowspan='2'>1.57V to 1.95V</th><td>{{2ch_1}}</td><td>{{2ch_2}}</td><td>{{2ch_3}}</td><td>{{2ch_4}}
</td><td>{{2ch_5}}</td><td>{{2ch_6}}</td><td>{{2ch_7}}</td><td>{{2ch_8}}</td></tr>

<tr><td>{{2pass_1}}</td><td>{{2pass_2}}</td><td>{{2pass_3}}</td><td>{{2pass_4}}</td><td>{{2pass_5}}</td><td>
{{2pass_6}}</td><td>{{2pass_7}}</td><td>{{2pass_8}}</td></tr>

<tr><th rowspan='2'>1.5V</th><th rowspan='2'>1.35V to 1.65V</th><td>{{3ch_1}}</td><td>{{3ch_2}}</td><td>{{3ch_3}}</td><td>{{3ch_4}}
</td><td>{{3ch_5}}</td><td>{{3ch_6}}</td><td>{{3ch_7}}</td><td>{{3ch_8}}</td></tr>

<tr><td>{{3pass_1}}</td><td>{{3pass_2}}</td><td>{{3pass_3}}</td><td>{{3pass_4}}</td><td>{{3pass_5}}</td><td>
{{3pass_6}}</td><td>{{3pass_7}}</td><td>{{3pass_8}}</td></tr>

<tr><th rowspan='2'>1.25V</th><th rowspan='2'>1.12V to 1.37V
</th><td>{{4ch_1}}</td><td>{{4ch_2}}</td><td>{{4ch_3}}</td><td>{{4ch_4}}
</td><td>{{4ch_5}}</td><td>{{4ch_6}}</td><td>{{4ch_7}}</td><td>{{4ch_8}}</td></tr>

<tr><td>{{4pass_1}}</td><td>{{4pass_2}}</td><td>{{4pass_3}}</td><td>{{4pass_4}}</td><td>{{4pass_5}}</td><td>
{{4pass_6}}</td><td>{{4pass_7}}</td><td>{{4pass_8}}</td></tr>

<tr><th rowspan='2'>1.0V</th><th rowspan='2'>0.9V to 1.1V</th><td>{{5ch_1}}</td><td>{{5ch_2}}</td><td>{{5ch_3}}</td><td>{{5ch_4}}
</td><td>{{5ch_5}}</td><td>{{5ch_6}}</td><td>{{5ch_7}}</td><td>{{5ch_8}}</td></tr>

<tr><td>{{5pass_1}}</td><td>{{5pass_2}}</td><td>{{5pass_3}}</td><td>{{5pass_4}}</td><td>{{5pass_5}}</td><td>
{{5pass_6}}</td><td>{{5pass_7}}</td><td>{{5pass_8}}</td></tr>

<tr><th rowspan='2'>0.75V</th><th rowspan='2'>0.67V to 0.82V
</th><td>{{6ch_1}}</td><td>{{6ch_2}}</td><td>{{6ch_3}}</td><td>{{6ch_4}}
</td><td>{{6ch_5}}</td><td>{{6ch_6}}</td><td>{{6ch_7}}</td><td>{{6ch_8}}</td></tr>


<tr><td>{{6pass_1}}</td><td>{{6pass_2}}</td><td>{{6pass_3}}</td><td>{{6pass_4}}</td><td>{{6pass_5}}</td><td>
{{6pass_6}}</td><td>{{6pass_7}}</td><td>{{6pass_8}}</td></tr>
<tr><th rowspan='2'>0.5V</th><th rowspan='2'>0.45V to
0.55V
</th><td>{{7ch_1}}</td><td>{{7ch_2}}</td><td>{{7ch_3}}</td><td>{{7ch_4}}
</td><td>{{7ch_5}}</td><td>{{7ch_6}}</td><td>{{7ch_7}}</td><td>{{7ch_8}}</td></tr>

<tr><td>{{7pass_1}}</td><td>{{7pass_2}}</td><td>{{7pass_3}}</td><td>{{7pass_4}}</td><td>{{7pass_5}}</td><td>
{{7pass_6}}</td><td>{{7pass_7}}</td><td>{{7pass_8}}</td></tr>

<tr><th rowspan='2'>0.25V</th><th rowspan='2'>0.22V to 0.27V
</th><td>{{8ch_1}}</td><td>{{8ch_2}}</td><td>{{8ch_3}}</td><td>{{8ch_4}}
</td><td>{{8ch_5}}</td><td>{{8ch_6}}</td><td>{{8ch_7}}</td><td>{{8ch_8}}</td></tr>

<tr><td>{{8pass_1}}</td><td>{{8pass_2}}</td><td>{{8pass_3}}</td><td>{{8pass_4}}</td><td>{{8pass_5}}</td><td>
{{8pass_6}}</td><td>{{8pass_7}}</td><td>{{8pass_8}}</td></tr>
<tr><th rowspan='2'> 0.0V</th><th rowspan='2'>-0.2V to
0.2V</th><td>{{9ch_1}}</td><td>{{9ch_2}}</td><td>{{9ch_3}}</td><td>{{9ch_4}}
</td><td>{{9ch_5}}</td><td>{{9ch_6}}</td><td>{{9ch_7}}</td><td>{{9ch_8}}</td></tr>
<tr><td>{{9pass_1}}</td><td>{{9pass_2}}</td><td>{{9pass_3}}</td><td>{{9pass_4}}</td><td>{{9pass_5}}</td><td>
{{9pass_6}}</td><td>{{9pass_7}}</td><td>{{9pass_8}}</td></tr>
<tr><th colspan='10'>PANEL LED DISPLAY STATUS</th></tr>
<tr><td colspan='10'>{{led_status}}</td></tr>
<tr><th colspan='10'>USB OSCILLOSCOPE 5132</th></tr>
<tr><td colspan='10'>{{Amp_Osc}}</td></tr>
</table>
<br><br>
<table width="100%" style='text-align:center'>
 <td>Tested By:</td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <td>Verified By:</td>
</table>
</body>
</html>

    )";
}
//----------------------------------BIT TEST Reports LRU-------------------------------//
QString ReportTemplates::Bit_Test_Report()
{
    return R"(

<h2 style="text-align:center;">BIT TEST</h2>
<br>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">

<tr><th >Project Name</th><td >FTU SRU LRU ATE</td><th >FTU Module P/N</th><td >FTU-1104 004 107 08</td><th >FTU SL No.</th><td>{{Fsl_no}}</td></tr>
<tr><th >Test Date</th><td >{{DD-MM-YYYY}}</td><th>Test Time</th><td>{{HH:MM:SEC}}</td><th >Sub-System</th><td>FTU</td></tr>
<tr><th> Test Name</th><td>{{tester_name}}</td><th>Tested By</th><td>{{TESTED_BY}}</td><th>ATE SL No.</th><td>{{ATE_SLNO}}</td></tr>
<tr><th>LRU Internal Checksum</th><td>{{internal_c}}</td><th>LRU External Flash Checksum</th><td>{{external_c}}</td><th >ATE Checksum</th><td>{{ATE_c}}</td></tr>
 <tr><th>User Remarks</th><td colspan='8'>{{Remarks}}</td></tr>

</table>
<br><br>

<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">
    <tr><th colspan='2'>I/P Voltages</th><th > 28V&plusmn;0.42V</th><th colspan='2'>voltage Observed</th><td>{{vol_obs}}</td><th colspan='2'>Current(<0.3A)</th><td colspan='2'>{{current}}</td></tr>
	<tr><th colspan='12'>DAC - IC 1&2 CHECKS</th></tr>

<tr><th rowspan='3'>Expected voltages </th><th rowspan='3'>Tolerance Range </th><th rowspan='2'colspan='8' >Observed Voltage</th></tr>
<tr>
<tr><th>Analog Input ch1(1(H)/2(L))</th><th>Analog input ch2 (3(H)/4(L))</th><th>Analog 
input ch3 (5(H)/6(L))</th><th>Analog input ch4 (7(H)/8(L))</th><th>Analog input ch5 (9(H)/10(L))</th><th>Analog input ch6 (11(H)/12(L))</th><th>Analog input ch7 (13(H)/14(L))</th><th>Analog 
input ch8 (15(H)/16(L))</th></tr>
<tr><th rowspan='2'>2V</th><th rowspan='2'>1.9V to 2.1V</th><td>{{ch1}}</td><td>{{ch2}}</td><td>{{ch3}}</td><td>{{ch4}}</td><td>{{ch5}}</td><td>{{ch6}}</td><td>{{ch7}}</td><td>{{ch8}}</td></tr>
<tr><td>{{r_c1}}</td><td>{{r_c2}}</td><td>{{r_c3}}</td><td>{{r_c4}}</td><td>{{r_c5}}</td><td>{{r_c6}}</td><td>{{r_c7}}</td><td>{{r_c8}}</td></tr>
<tr><th rowspan='2'>1.5V</th><th rowspan='2'>1.4V to 1.6V</th><td>{{2ch1}}</td><td>{{2ch2}}</td><td>{{2ch3}}</td><td>{{2ch4}}</td><td>{{2ch5}}</td><td>{{2ch6}}</td><td>{{2ch7}}</td><td>{{2ch8}}</td></tr>
<tr><td>{{2r_c1}}</td><td>{{2r_c2}}</td><td>{{2r_c3}}</td><td>{{2r_c4}}</td><td>{{2r_c5}}</td><td>{{2r_c6}}</td><td>{{2r_c7}}</td><td>{{2r_c8}}</td></tr>
<tr><th rowspan='2'>1.0V</th><th rowspan='2'>0.9V to 1.1V
</th><td>{{3ch1}}</td><td>{{3ch2}}</td><td>{{3ch3}}</td><td>{{3ch4}}</td><td>{{3ch5}}</td><td>{{3ch6}}</td><td>{{3ch7}}</td><td>{{3ch8}}</td></tr>
<tr><td>{{3r_c1}}</td><td>{{3r_c2}}</td><td>{{3r_c3}}</td><td>{{3r_c4}}</td><td>{{3r_c5}}</td><td>{{3r_c6}}</td><td>{{3r_c7}}</td><td>{{3r_c8}}</td></tr>
<tr><th rowspan='2'>0.5V</th><th rowspan='2'> 0.3V to 0.7V</th><td>{{4ch1}}</td><td>{{4ch2}}</td><td>{{4ch3}}</td><td>{{4ch4}}</td><td>{{4ch5}}</td><td>{{4ch6}}</td><td>{{4ch7}}</td><td>{{4ch8}}</td></tr>
<tr>
<td>{{4r_c1}}</td><td>{{4r_c2}}</td><td>{{4r_c3}}</td><td>{{4r_c4}}</td><td>{{4r_c5}}</td>
<td>{{4r_c6}}</td><td>{{4r_c7}}</td><td>{{4r_c8}}</td></tr>

<tr><th rowspan='2'>0.0</th><th rowspan='2'>-0.2V to 0.2V
</th><td>{{5ch1}}</td><td>{{5ch2}}</td>
	<td>{{5ch3}}</td><td>{{5ch4}}</td><td>{{5ch5}}</td><td>{{5ch6}}</td><td>{{5ch7}}</td>
	<td>{{5ch8}}</td></tr>
<tr><td>{{5r_c1}}</td><td>{{5r_c2}}</td><td>{{5r_c3}}</td><td>{{5r_c4}}</td><td>{{5r_c5}}</td>
<td>{{5r_c6}}</td><td>{{5r_c7}}</td><td>{{5r_c8}}</td></tr>

<tr><th rowspan='2'>-0.5</th><th rowspan='2'>-0.7V to -0.3V
</th><td>{{6ch1}}</td><td>{{6ch2}}</td>
	<td>{{6ch3}}</td><td>{{6ch4}}</td><td>{{6ch5}}</td><td>{{6ch6}}</td><td>{{6ch7}}</td>
	<td>{{6ch8}}</td></tr>


<tr><td>{{6r_c1}}</td><td>{{6r_c2}}</td><td>{{6r_c3}}</td>
<td>{{6r_c4}}</td><td>{{6r_c5}}</td><td>{{6r_c6}}</td><td>{{6r_c7}}</td><td>{{6r_c8}}</td></tr>
<tr><th rowspan='2'>-1.0</th><th rowspan='2'>-1.1 to -0.9V
</th><td>{{7ch1}}</td><td>{{7ch2}}</td><td>{{7ch3}}</td><td>{{7ch4}}</td><td>{{7ch5}}</td><td>{{7ch6}}</td><td>{{7ch7}}</td><td>{{7ch8}}</td></tr>
<tr><td>{{7r_c1}}</td><td>{{7r_c2}}</td><td>{{7r_c3}}</td><td>{{7r_c4}}</td><td>{{7r_c5}}</td><td>{{7r_c6}}</td><td>{{7r_c7}}</td><td>{{7r_c8}}</td></tr>

<tr><th rowspan='2'>-1.5V</th><th rowspan='2'>-1.6V to -1.4V
</th><td>{{8ch1}}</td><td>{{8ch2}}</td>
	<td>{{8ch3}}</td><td>{{8ch4}}</td><td>{{8ch5}}</td><td>{{8ch6}}</td><td>{{8ch7}}</td>
	<td>{{8ch8}}</td></tr>

<tr><td>{{8r_c1}}</td><td>{{8r_c2}}</td><td>{{8r_c3}}</td>
<td>{{8r_c4}}</td><td>{{8r_c5}}</td><td>{{8r_c6}}</td><td>{{8r_c7}}</td><td>{{8r_c8}}</td></tr>
<tr><th rowspan='2'>-2.0V</th><th rowspan='2'>-2.1V to -1.9V
</th><td>{{9ch1}}</td><td>{{9ch2}}</td>
	<td>{{9ch3}}</td><td>{{9ch4}}</td><td>{{9ch5}}</td><td>{{9ch6}}</td><td>{{9ch7}}</td><td>{{9ch8}}</td></tr>
<tr><td>{{9r_c1}}</td><td>{{9r_c2}}</td><td>{{9r_c3}}</td><td>{{9r_c4}}</td><td>{{9r_c5}}</td><td>{{9r_c6}}</td><td>{{9r_c7}}</td><td>{{9r_c8}}</td></tr>
	<tr><th colspan='12'>DIP-DOP LOOP BACK</th></tr>
	<tr><th colspan='12'>Discrete Outputs</th></tr>
	<tr><th>Sl.No</th><th colspan='3'>Discrete Output channels</th><th colspan='2'>Expected value</th><th colspan='2'>Observed value</th><th colspan='2'>Result</th></tr>
	<tr><th>1</th><th colspan='3'>channel 1 (C2.21(H)/22(L))</th><td colspan='2'>1</td><td colspan='2'>{{Outval_1}}</td><td colspan='2'>{{D1_O_r}}</td></tr>
	<tr><th>2</th><th colspan='3'>channel 2 (C2.23(H)/24(L))</th><td colspan='2'>1</td><td colspan='2'>{{Outval_2}}</td><td colspan='2'>{{D2_O_r}}</td></tr>
	<tr><th>3</th><th colspan='3'>channel 3 (C2.25(H)/26(L))</th><td colspan='2'>1</td><td colspan='2'>{{Outval_3}}</td><td colspan='2'>{{D3_O_r}}</td></tr>
	<tr><th>4</th><th colspan='3'>channel 4 (C2.27(H)/28(L))</th><td colspan='2'>1</td><td colspan='2'>{{Outval_4}}</td><td colspan='2'>{{D4_O_r}}</td></tr>
	<tr><th>5</th><th colspan='3'>channel 5 (C2.29(H)/30(L))</th><td colspan='2'>1</td><td colspan='2'>{{Outval_5}}</td><td colspan='2'>{{D5_O_r}}</td></tr>

<tr><th colspan='12'>Discrete Inputs</th></tr>

	<tr><th>Sl.No</th><th colspan='3'>Discrete Input channels</th><th colspan='2'>Expected value</th><th colspan='2'>Observed value</th><th colspan='2'>Result</th></tr>
	<tr><th>1</th><th colspan='3'>channel 1 (C2.31(H)/33(L))</th><td colspan='2'>1</td><td colspan='2'>{{Inputval_1}}</td><td colspan='2'>{{D1_I_r}}</td></tr>
	<tr><th>2</th><th colspan='3'>channel 2 (C2.32(H)/33(L))</th><td colspan='2'>1</td><td colspan='2'>{{Inputval_2}}</td><td colspan='2'>{{D2_I_r}}</td></tr>
	<tr><th>3</th><th colspan='3'>channel 3 (C2.34(H)/33(L))</th><td colspan='2'>1</td><td colspan='2'>{{Inputval_3}}</td><td colspan='2'>{{D3_I_r}}</td></tr>
	
<tr><th colspan='12'>FRONT PANEL SWITCH STATUS</th></tr>
<tr><th>Sl.No</th><th colspan='3'>Test Name</th colspan='3'><th colspan='2'>Expected value</th><th colspan='2'>Observed Value</th><th colspan='2'>Result</th></tr>
<tr><th>1</th><th colspan='3'style="text-align:left;">  Rotary switches 1 2 3</th><td colspan='2'>000</td><td colspan='2'>{{Rotary_Status}}</td><td colspan='2'>{{RS_r}}</td></tr>
<tr><th>2</th><th colspan='3'style="text-align:left;">  Prep Switch</th><td colspan='2'>0</td><td colspan='2'>{{Prep_Status}}</td><td colspan='2'>{{PS_r}}</td></tr>
<tr><th>3</th><th colspan='3'style="text-align:left;">  Ready Init Switch</th><td colspan='2'>0</td><td colspan='2'>{{RInit_Status}}</td><td colspan='2'>{{RIS_r}}</td></tr>
<tr><th>4</th><th colspan='3'style="text-align:left;">  Abort Switch</th><td colspan='2'>0</td><td colspan='2'>{{Abort_Status}}</td><td colspan='2'>{{AS_r}}</td></tr>

<tr><th colspan='12'>RS422 COMMUNICATION PORT (17(H)/18(L))</th></tr>
<tr><th colspan='12'>Pattern 1</th></tr>
<tr><td colspan='12'>{{Pat1_data}}</td></tr>

<tr><th colspan ='2'>Expected No.of Bytes 0x55</th><th colspan ='2'>Observed No.of Bytes 0x55</th><th colspan ='2'>Expected No.of Bytes 0xaa</th><th >Observed No.of Bytes 0xaa</th><th colspan ='2'>Expected Checksum</th><th colspan ='2'>Observed Checksum</th> </tr>
<tr><td colspan='2'>512 Bytes</td><td colspan='2'>{{Obs_bytes_55}}</td><td colspan='2'>512 Bytes</td><td >{{Obs_bytes_aa}}</td><td colspan='2'>{{EXP_checksum}}</td><td colspan='2'>{{Obs_checksum}}</td></tr>
<tr><th colspan='6'>Result</th><th colspan='6'>{{Port_r}}</th></tr>
</table>
<br><br><br>
<table style='width: 80%; margin: 0 auto; text-align: center;'>
<br><br>
<tr>
    <td><b>Tested By:</b> ____________________</td><br>
    <td><b>Verified By:</b> ____________________</td>
</tr>
</table>
)";
}
/*-------data to load rs422---<tr><th colspan='10'>Data</th></tr>
<tr><td colspan="12">
    <pre style="font-family: monospace; white-space: pre-wrap; word-break: break-all;">
    {{LRU_data}}</pre>  
    </td></tr>*/
//---------------------------------DC DC Reports----------------------------------//

QString ReportTemplates::LRU_Test_Report()
{
    return R"(
<h2 style="text-align:center;">FTU LRU TEST</h2>
<br>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">

<tr><th >Project Name</th><td >FTU SRU LRU ATE</td><th >FTU Module P/N</th><td >FTU-1104 004 107 08</td><th >FTU SL No.</th><td>{{Fsl_no}}</td></tr>
<tr><th >Test Date</th><td >{{DD-MM-YYYY}}</td><th>Test Time</th><td>{{HH:MM:SEC}}</td><th >Sub-System</th><td>FTU</td></tr>
<tr><th> Test Name</th><td>{{tester_name}}</td><th>Tested By</th><td>{{TESTED_BY}}</td><th>ATE SL No.</th><td>{{ATE_SLNO}}</td></tr>
<tr><th>LRU Internal Checksum</th><td>{{internal_c}}</td><th>LRU External Flash Checksum</th><td>{{external_c}}</td><th >ATE Checksum</th><td>{{ATE_c}}</td></tr>
 <tr><th>User Remarks</th><td colspan='8'>{{Remarks}}</td></tr>
</table><br><br>

<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">
    <tr><th colspan='2'>I/P Voltages</th><th > 16V/28V/32V&plusmn;0.42V</th><th colspan='2'>voltage Observed</th><td>{{vol_obs}}</td><th colspan='2'>Current(<0.3A)</th><td colspan='2'>{{current}}</td></tr>
	<tr><th colspan='12'>DAC - IC 1&2 CHECKS</th></tr>

<tr><th rowspan='3'>Expected voltages </th><th rowspan='3'>Tolerance Range </th><th rowspan='2'colspan='8' >Observed Voltage</th></tr>
<tr>
<tr><th>Analog Input ch1(1(H)/2(L))</th><th>Analog input ch2 (3(H)/4(L))</th><th>Analog 
input ch3 (5(H)/6(L))</th><th>Analog input ch4 (7(H)/8(L))</th><th>Analog input ch5 (9(H)/10(L))</th><th>Analog input ch6 (11(H)/12(L))</th><th>Analog input ch7 (13(H)/14(L))</th><th>Analog 
input ch8 (15(H)/16(L))</th></tr>
<tr><th rowspan='2'>2V</th><th rowspan='2'>1.9V to 2.1V</th><td>{{ch1}}</td><td>{{ch2}}</td><td>{{ch3}}</td><td>{{ch4}}</td><td>{{ch5}}</td><td>{{ch6}}</td><td>{{ch7}}</td><td>{{ch8}}</td></tr>
<tr><td>{{r_c1}}</td><td>{{r_c2}}</td><td>{{r_c3}}</td><td>{{r_c4}}</td><td>{{r_c5}}</td><td>{{r_c6}}</td><td>{{r_c7}}</td><td>{{r_c8}}</td></tr>
<tr><th rowspan='2'>1.5V</th><th rowspan='2'>1.4V to 1.6V</th><td>{{2ch1}}</td><td>{{2ch2}}</td><td>{{2ch3}}</td><td>{{2ch4}}</td><td>{{2ch5}}</td><td>{{2ch6}}</td><td>{{2ch7}}</td><td>{{2ch8}}</td></tr>
<tr><td>{{2r_c1}}</td><td>{{2r_c2}}</td><td>{{2r_c3}}</td><td>{{2r_c4}}</td><td>{{2r_c5}}</td><td>{{2r_c6}}</td><td>{{2r_c7}}</td><td>{{2r_c8}}</td></tr>
<tr><th rowspan='2'>1.0V</th><th rowspan='2'>0.9V to 1.1V
</th><td>{{3ch1}}</td><td>{{3ch2}}</td><td>{{3ch3}}</td><td>{{3ch4}}</td><td>{{3ch5}}</td><td>{{3ch6}}</td><td>{{3ch7}}</td><td>{{3ch8}}</td></tr>
<tr><td>{{3r_c1}}</td><td>{{3r_c2}}</td><td>{{3r_c3}}</td><td>{{3r_c4}}</td><td>{{3r_c5}}</td><td>{{3r_c6}}</td><td>{{3r_c7}}</td><td>{{3r_c8}}</td></tr>
<tr><th rowspan='2'>0.5V</th><th rowspan='2'> 0.3V to 0.7V</th><td>{{4ch1}}</td><td>{{4ch2}}</td><td>{{4ch3}}</td><td>{{4ch4}}</td><td>{{4ch5}}</td><td>{{4ch6}}</td><td>{{4ch7}}</td><td>{{4ch8}}</td></tr>
<tr>
<td>{{4r_c1}}</td><td>{{4r_c2}}</td><td>{{4r_c3}}</td><td>{{4r_c4}}</td><td>{{4r_c5}}</td>
<td>{{4r_c6}}</td><td>{{4r_c7}}</td><td>{{4r_c8}}</td></tr>

<tr><th rowspan='2'>0.0</th><th rowspan='2'>-0.2V to 0.2V
</th><td>{{5ch1}}</td><td>{{5ch2}}</td>
	<td>{{5ch3}}</td><td>{{5ch4}}</td><td>{{5ch5}}</td><td>{{5ch6}}</td><td>{{5ch7}}</td>
	<td>{{5ch8}}</td></tr>
<tr><td>{{5r_c1}}</td><td>{{5r_c2}}</td><td>{{5r_c3}}</td><td>{{5r_c4}}</td><td>{{5r_c5}}</td>
<td>{{5r_c6}}</td><td>{{5r_c7}}</td><td>{{5r_c8}}</td></tr>

<tr><th rowspan='2'>-0.5</th><th rowspan='2'>-0.7V to -0.3V
</th><td>{{6ch1}}</td><td>{{6ch2}}</td>
	<td>{{6ch3}}</td><td>{{6ch4}}</td><td>{{6ch5}}</td><td>{{6ch6}}</td><td>{{6ch7}}</td>
	<td>{{6ch8}}</td></tr>


<tr><td>{{6r_c1}}</td><td>{{6r_c2}}</td><td>{{6r_c3}}</td>
<td>{{6r_c4}}</td><td>{{6r_c5}}</td><td>{{6r_c6}}</td><td>{{6r_c7}}</td><td>{{6r_c8}}</td></tr>
<tr><th rowspan='2'>-1.0</th><th rowspan='2'>-1.1 to -0.9V
</th><td>{{7ch1}}</td><td>{{7ch2}}</td><td>{{7ch3}}</td><td>{{7ch4}}</td><td>{{7ch5}}</td><td>{{7ch6}}</td><td>{{7ch7}}</td><td>{{7ch8}}</td></tr>
<tr><td>{{7r_c1}}</td><td>{{7r_c2}}</td><td>{{7r_c3}}</td><td>{{7r_c4}}</td><td>{{7r_c5}}</td><td>{{7r_c6}}</td><td>{{7r_c7}}</td><td>{{7r_c8}}</td></tr>

<tr><th rowspan='2'>-1.5V</th><th rowspan='2'>-1.6V to -1.4V
</th><td>{{8ch1}}</td><td>{{8ch2}}</td>
	<td>{{8ch3}}</td><td>{{8ch4}}</td><td>{{8ch5}}</td><td>{{8ch6}}</td><td>{{8ch7}}</td>
	<td>{{8ch8}}</td></tr>

<tr><td>{{8r_c1}}</td><td>{{8r_c2}}</td><td>{{8r_c3}}</td>
<td>{{8r_c4}}</td><td>{{8r_c5}}</td><td>{{8r_c6}}</td><td>{{8r_c7}}</td><td>{{8r_c8}}</td></tr>
<tr><th rowspan='2'>-2.0V</th><th rowspan='2'>-2.1V to -1.9V
</th><td>{{9ch1}}</td><td>{{9ch2}}</td>
	<td>{{9ch3}}</td><td>{{9ch4}}</td><td>{{9ch5}}</td><td>{{9ch6}}</td><td>{{9ch7}}</td><td>{{9ch8}}</td></tr>
<tr><td>{{9r_c1}}</td><td>{{9r_c2}}</td><td>{{9r_c3}}</td><td>{{9r_c4}}</td><td>{{9r_c5}}</td><td>{{9r_c6}}</td><td>{{9r_c7}}</td><td>{{9r_c8}}</td></tr>
	<tr><th colspan='12'>DIP-DOP LOOP BACK</th></tr>
	<tr><th colspan='12'>Discrete Outputs</th></tr>
	<tr><th>Sl.No</th><th colspan='3'>Discrete Output channels</th><th colspan='2'>Expected value</th><th colspan='2'>Observed value</th><th colspan='2'>Result</th></tr>
	<tr><th>1</th><th colspan='3'>channel 1 (C2.21(H)/22(L))</th><td colspan='2'>1</td><td colspan='2'>{{Outval_1}}</td><td colspan='2'>{{D1_O_r}}</td></tr>
	<tr><th>2</th><th colspan='3'>channel 2 (C2.23(H)/24(L))</th><td colspan='2'>1</td><td colspan='2'>{{Outval_2}}</td><td colspan='2'>{{D2_O_r}}</td></tr>
	<tr><th>3</th><th colspan='3'>channel 3 (C2.25(H)/26(L))</th><td colspan='2'>1</td><td colspan='2'>{{Outval_3}}</td><td colspan='2'>{{D3_O_r}}</td></tr>
	<tr><th>4</th><th colspan='3'>channel 4 (C2.27(H)/28(L))</th><td colspan='2'>1</td><td colspan='2'>{{Outval_4}}</td><td colspan='2'>{{D4_O_r}}</td></tr>
	<tr><th>5</th><th colspan='3'>channel 5 (C2.29(H)/30(L))</th><td colspan='2'>1</td><td colspan='2'>{{Outval_5}}</td><td colspan='2'>{{D5_O_r}}</td></tr>

<tr><th colspan='12'>Discrete Inputs</th></tr>

	<tr><th>Sl.No</th><th colspan='3'>Discrete Input channels</th><th colspan='2'>Expected value</th><th colspan='2'>Observed value</th><th colspan='2'>Result</th></tr>
	<tr><th>1</th><th colspan='3'>channel 1 (C2.31(H)/33(L))</th><td colspan='2'>1</td><td colspan='2'>{{Inputval_1}}</td><td colspan='2'>{{D1_I_r}}</td></tr>
	<tr><th>2</th><th colspan='3'>channel 2 (C2.32(H)/33(L))</th><td colspan='2'>1</td><td colspan='2'>{{Inputval_2}}</td><td colspan='2'>{{D2_I_r}}</td></tr>
	<tr><th>3</th><th colspan='3'>channel 3 (C2.34(H)/33(L))</th><td colspan='2'>1</td><td colspan='2'>{{Inputval_3}}</td><td colspan='2'>{{D3_I_r}}</td></tr>
	
<tr><th colspan='12'>FRONT PANEL SWITCH STATUS</th></tr>
<tr><th>Sl.No</th><th colspan='3'>Test Name</th colspan='3'><th colspan='2'>Expected value</th><th colspan='2'>Observed Value</th><th colspan='2'>Result</th></tr>
<tr><th>1</th><th colspan='3'style="text-align:left;">  Rotary switches 1 2 3</th><td colspan='2'>000</td><td colspan='2'>{{Rotary_Status}}</td><td colspan='2'>{{RS_r}}</td></tr>
<tr><th>2</th><th colspan='3'style="text-align:left;">  Prep Switch</th><td colspan='2'>0</td><td colspan='2'>{{Prep_Status}}</td><td colspan='2'>{{PS_r}}</td></tr>
<tr><th>3</th><th colspan='3'style="text-align:left;">  Ready Init Switch</th><td colspan='2'>0</td><td colspan='2'>{{RInit_Status}}</td><td colspan='2'>{{RIS_r}}</td></tr>
<tr><th>4</th><th colspan='3'style="text-align:left;">  Abort Switch</th><td colspan='2'>0</td><td colspan='2'>{{Abort_Status}}</td><td colspan='2'>{{AS_r}}</td></tr>
</table>
<br>
<b>Note:</b> Based on User Verification result are declared.(Rotary Switches 1 2 3 , Prep Switch, Ready Init Switch, Abort Switch)</b></p></td></tr>

<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">

<tr><th colspan='12'>RS422 COMMUNICATION PORT (17(H)/18(L))</th></tr>
<tr><th colspan='12'>Pattern 1</th></tr>
<tr><td colspan='12'>{{Pat1_data}}</td></tr>

<tr><th colspan ='2'>Expected No.of Bytes 0x55</th><th colspan ='2'>Observed No.of Bytes 0x55</th><th colspan ='2'>Expected No.of Bytes 0xaa</th><th >Observed No.of Bytes 0xaa</th><th colspan ='2'>Expected Checksum</th><th colspan ='2'>Observed Checksum</th> </tr>
<tr><td colspan='2'>512 Bytes</td><td colspan='2'>{{Obs_bytes_55}}</td><td colspan='2'>512 Bytes</td><td >{{Obs_bytes_aa}}</td><td colspan='2'>{{EXP_checksum}}</td><td colspan='2'>{{Obs_checksum}}</td></tr>
<tr><th colspan='6'>Result</th><th colspan='6'>{{Port_r}}</th></tr>
<tr><th colspan='12'>USB PORT DATA </th></tr>
<tr><th colspan='12'>Pattern 1</th></tr>
<tr><td colspan='12'>{{USBPat1_data}}</td></tr>
<th colspan ='6'>Expected Checksum</th><th colspan ='6'>Observed Checksum</th> </tr>
<th colspan ='6'>0x3A92</th><th colspan ='6'>{{USB_cksum1}}</th> </tr>
<tr><th colspan='6'>Result</th><th colspan='6'>{{USB_R1}}</th></tr>
<tr><th colspan='12'>Pattern 2</th></tr>
<tr><td colspan='12'>{{USBPat2_data}}</td></tr>
<th colspan ='6'>Expected Checksum</th><th colspan ='6'>Observed Checksum</th> </tr>
<th colspan ='6'>0xD7CF</th><th colspan ='6'>{{USB_cksum2}}</th> </tr>
<tr><th colspan='6'>Result</th><th colspan='6'>{{USB_R2}}</th></tr>

</table>
<br><br><br>
<table style='width: 80%; margin: 0 auto; text-align: center;'>
<br><br>
<tr>
    <td><b>Tested By:</b> ____________________</td><br>
    <td><b>Verified By:</b> ____________________</td>
</tr>
</table>
   )";
}

QString ReportTemplates::DC_DC_Report()
{
    // QString isolationHtml =
    return R"(

<h2 style="text-align:center;">SRU LEVEL DC-DC & DISPLAY MODULES</h2>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">
<tr><th colspan='2'>Project Name</th><td colspan='2'>FTU SRU LRU ATE</td><th colspan='2'>FTU Module P/N</th><td colspan='2'>FTU-1104 004 107 08</td><th>DC DC SL No</th><td>{{DC_DC slno}}</td></tr>
<tr><th colspan='2'>Test Date</th><td colspan='2'>{{DD-MM-YYYY}}</td><th colspan='2'>Test Time</th><td colspan='2'>{{HH:MM:SEC}}</td><th>Display SL No</th><td>{{Display slno}}</td></tr>
<tr><th colspan='2'> Test Name</th><td colspan='2'>{{test_name}}</td><th>Tested By</th><td>{{TESTED_BY}}</td><th>ATE Checksum</th><td>{{ATE_cksum}}</td> <th>ATE SL No</th><td>{{ATE_SLNO}}</td></tr>  
 <tr><th>User Remarks</th><td colspan='10'>{{DC_Remarks}}</td></tr>

        <br><br>
<tr><th colspan='12'> DC-DC Module Load Checks</th></tr>
 <tr><th colspan='2'>I/P Voltages</th><th colspan='2'> 16V/28V/32V &plusmn;1V</th><td colspan='2'>{{vol_obs}}</td>
 <th colspan='2'>Current <!--&#177;0.060--></th><td colspan='2'>{{Curr_Obs}}</td></tr>
<tr><th rowspan='2'>S. No</th><th rowspan='2'>Part No</th><th  colspan='2'rowspan='2'>Test Name</th><th colspan='2'>Expected Voltage</th><th colspan='4'>Observed voltage</th></tr>
<tr><th>10% Load</th><th>100% Load</th><th >10% Load</th><th>Result </th><th>100% Load</th><th>Result </th></tr>
<tr><th rowspan='2'>1</th><th rowspan='2'>MGDS-10-H-B</th> <th rowspan='2'>3.3V O/P</th><td><b>Voltage</b></td><th>3.6V&plusmn;0.125</th><th>3.3V&plusmn;0.125V</th><td>{{ov_10l_3p3}}</td><td>{{res_v1_3p3}}</td><td>{{ov_100l_3p3}}</td><td>{{res_v100_3p3}}</td></tr>
<tr><th>Current</th><th>0.2A &plusmn;0.100A</th><th>0.2A &plusmn;0.100A</th><td>{{oi_10l_3p3}}</td><td>{{res_I1_3p3}}</td><td>{{oi_100l_3p3}}</td><td>{{res_I100_3p3}}</td></tr>
<tr><th rowspan='2'>2</th><th rowspan='4'>MGDB-10-H-C</th><th rowspan='2'>+5V O/P</th><td><b>Voltage</b></td><th>+5.3V&plusmn;0.125V</th><th>+5V&plusmn;0.125V</th><td>{{ov_10l_5V}}</td><td>{{res_v2_5V}}</td><td>{{ov_100l_5V}}</td><td>{{res_v100_5v}}</td></tr>
<tr><th>Current</th><th>0.1A &plusmn;0.100A</th><th>1A &plusmn;0.100A</th><td>{{oi_10l_5V}}</td><td>{{res_I2_5V}}</td><td>{{oi_100l_5V}}</td><td>{{res_I100_5V}}</td></tr>
<tr><th rowspan='2'>3</th><th rowspan='2'>-5V O/P</th><td><b>Voltage</b></td><th>-5.3V&plusmn;0.125V</th><th>-5V&plusmn;0.125V</th><td>{{ov_10l_N_5V}}</td><td>{{res_v3_N_5V}}</td><td>{{ov_100l_N_5V}}</td><td>{{res_V100_N_5v}}</td></tr>
<tr><th>Current</th><th>0.1A &plusmn;0.100A</th><th>1A &plusmn;0.100A</th><td>{{oi_10l_N_5V}}</td><td>{{res_I3_N_5V}}</td><td>{{oi_100l_N_5V}}</td><td>{{res_I100_N5V}}</td></tr>

</table>
<h3 style="text-align:center;">Ripple Checks</h3>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">
<tr><th>S. No</th><th>Part No</th><th colspan='2'>Test Name</th><th colspan='2'>Expected Ripple</th><th colspan='2'>Observed Ripple</th><th>Result</th></tr>
<tr><th rowspan='2'>1</th><th rowspan='2'>DC</th><th rowspan='2'>3.3V O/P</th><th> Maximum</th><td colspan='2'>{{Max_3.3Exp}}</td><td colspan='2'>{{Max_3.3Obs}}</td><td>{{Res_Max3.3}}</td></tr>
<tr><th >minimum</th><td colspan='2'>{{Min_3.3Exp}}</td><td colspan='2'>{{Min_3.3Obs}}</td><td>{{Res_Min3.3}}</td></tr>

<tr><th rowspan='2'>2</th><th rowspan='4'>DC </th><th rowspan='2'>+5V O/P</th><th> Maximum</th><td colspan='2'>{{Max_+5VExp}}</td><td colspan='2'>{{Max_+5VObs}}</td><td>{{Res_Max5}}</td></tr>
<tr><th>minimum</th><td colspan='2'>{{Min_+5VExp}}</td><td colspan='2'>{{Min_+5VObs}}</td><td>{{Res_Min5}}</td></tr>
<tr><th rowspan='2'>3</th><th rowspan='2'> -5V O/P</th><th> Maximum</th><td colspan='2'>{{Max_-5VExp}}</td><td colspan='2'>{{Max_-5VObs}}</td><td>{{Res_MaxN5}}</td></tr>
<tr><th>minimum</th><td colspan='2'>{{Min_-5VExp}}</td><td colspan='2'>{{Min_-5VObs}}</td><td>{{Res_MinN5}}</td></tr>
</table>
<h3 style="text-align:center;">Ripple Waveforms Images</h3>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">
<tr><th colspan='12'> +5V Waveform Image</th></tr>
<tr><td colspan='12'>{{Graph_Image_5}}</td></tr>	
<tr><th colspan='12'> -5V Waveform Image</th></tr>
<tr><td colspan='12'>{{Graph_Image_N_5}}</td></tr>
<tr><th colspan='12'>3.3V Waveform Image</th></tr>  
<tr><td colspan='12'>{{Graph_Image_3p3}}</td></tr> 
</table>
<h3 style="text-align:center;"> Display Module Functional Checks </h3>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">
<tr><th>S.No</th><th>Test Name</th><th>Expected Display</th><th>Observed Display</th><th>Result</th>
<tr><th>1</th><th>Display 1</th><th>0-F</th><td>{{Dis_obs1}}</td><td>{{Res_Dis1}}</td></tr>
<tr><th>2</th><th>Display 2</th><th>0-F</th><td>{{Dis_obs2}}</td><td>{{Res_Dis2}}</td></tr>
<tr><th>3</th><th>Display 3</th><th>0-F</th><td>{{Dis_obs3}}</td><td>{{Res_Dis3}}</td></tr>
</table>
<p>
<strong>NOTE:</strong> Verifys the digits on the display panel correspond to the expected display status.</p>
<table style='width:100%; text-align: center;'>
<tr>
    <td><b>Tested By:</b> </td><br><br><br><br>
    <td><b>Verified By:</b> </td>
</tr></table>



    )";
}

//----------------------controller Cards------------------------------//
QString ReportTemplates::cntrl_cards()
{
    return R"(
<h2 style="text-align:center;">SRU LEVEL CONTROLLER MODULE</h2>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">
<tr><th>Project Name</th><td colspan='2'>FTU SRU LRU ATE</td><th colspan='2'>FTU Module P/N</th><td colspan='2'>FTU-1104 004 107 08</td><th>FTU SL No.</th><td>{{Fsl_no}}</td></tr>
<tr><th>Test Date</th><td colspan='2'>{{DD-MM-YYYY}}</td><th colspan='2'>Test Time</th><td colspan='2'>{{HH:MM:SEC}}</td><th>Sub-System</th><td>FTU</td></tr>
<tr><th> Test Name</th><td colspan='2'>{{test_name}}</td><th  colspan='2'>Tested By</th><td colspan='2'> {{TESTED_BY}}</td><th>ATE SL No.</th><td>{{ATE_SLNO}}</td></tr>
 <tr><th>ATE Checksum</th><td colspan='2'>{{ATE_cksum}}</td><th colspan='2'>Controller Module Checksum</th><td colspan='2'>{{CC_cksum}}</td><th>Controller  SL No.</th><td>{{CC_slno}}</td></tr>
 <tr><th>User Remarks</th><td colspan='8'>{{cntrl_Remarks}}</td></tr>
<!---<tr><th colspan='9'> ISOLATION RESISTANCE MEASURMENT</th></tr>
        <tr><th>S. No</th><th colspan='2'>Test Name</th><th colspan='2'>Expected Resistance</th><th colspan='2'>Observed Resistance</th><th colspan='2'>Result</th></tr>
        <tr><th>1</th><th colspan='2'>3.3V O/P</th><td colspan='2'>{{v3.3_E_R}}</td><td colspan='2'>{{v3.3_O_R}}k&Omega;</td><td colspan='2'>{{v3.3_Res}}</td></tr>
	    <tr><th>2</th><th colspan='2'>+5V O/P</th><td colspan='2'>{{v+5_E_R}}</td><td colspan='2'>{{v+5_O_R}}k&Omega;</td><td colspan='2'>{{v+5_Res}}</td></tr>
        <tr><th>3</th><th colspan='2'>-5V O/P</th><td colspan='2'>{{v-5_E_R}}</td><td colspan='2'>{{v-5_O_R}}k&Omega;</td><td colspan='2'>{{v-5_Res}}</td></tr>-->
		
		<tr><th colspan='12'>VOLTAGE CHECKS</th></tr>
<tr><th>S. No</th><th colspan='5'>Test Name</th><th>Expected Voltage</th><th>Observed voltage</th><th>Result (PASS/FAIL)</th></tr>

<tr><th rowspan='2'>1</th><th rowspan='2'colspan='2' >3.3V O/P</th><td colspan='3'><b>Voltage</b></td><th>3.3VA &plusmn;200mV</th><td>{{ov_3p3}}</td><td>{{res_3p3v}}</td></tr>
<tr><th colspan='3'>Current</th><th>0.4A &plusmn;0.100A</th><td>{{oi_3p3}}</td><td>{{res_C1}}</td></tr>
<tr><th rowspan='2'>2</th><th rowspan='2'colspan='2'>+5V O/P</th><td colspan='3'><b>Voltage</b></td><th>+5VA &plusmn; 200mV</th><td>{{ov_+5V}}</td><td>{{res_+5v}}</td></tr>
<tr><th colspan='3'>Current</th><th>0.300A &plusmn;0.100A</th><td>{{oi_+5v}}</td><td>{{res_C2}}</td></tr>
<tr><th rowspan='2'>3</th><th rowspan='2'colspan='2'>-5V O/P</th><td colspan='3'><b>Voltage</b></td><th>-5VA &plusmn; 200mV</th><td>{{ov_N5v}}</td><td>{{res_N5v}}</td></tr>
<tr><th colspan='3'>Current</th><th>0.300A &plusmn;0.100A</th><td>{{oi_N5V}}</td><td>{{res_C3}}</td></tr>
</table>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">

	<h3 style="text-align:center;">RS422 LOOP BACK CHECKS</h3>
	<tr><th colspan='10'>Channel 1</th></tr>
<tr><th colspan='7'>PATTERN1 DATA</th><td colspan='4'>{{CH1_TX}}</td></tr>
<tr><th colspan='7'>PATTERN2 DATA</th><td colspan='4'>{{CH1_RX}}</td></tr>
<tr><th colspan='7'>RESULT</th><td colspan='4'>{{C1_RES}}</td></tr>
	<tr><th colspan='10'>Channel 2</th></tr>
<tr><th colspan='7'>PATTERN1 DATA</th><td colspan='4'> {{CH2_TX}}</td></tr>
<tr><th colspan='7'>PATTERN2 DATA</th><td colspan='4'> {{CH2_RX}}</td></tr>
<tr><th colspan='7'>RESULT</th><td colspan='4'>{{C2_RES}}</td></tr>
</td></tr>   
	</table>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">
<h3 style="text-align:center;">FRONT PANEL SWITCH STATUS</h3></tr>
<tr><th colspan='12'>Rotary Switch test</th></tr>
<tr><th rowspan='2'>Sl.No</th><th colspan='3'rowspan='2'>Test Name</th><th >Expected value<th>Observed Value</th><th>Expected Value</th><th>Observed Value</th><th rowspan='2'>Result</th></tr>
<tr><th>ON</th><th>ON</th><th>OFF</th><th>OFF</th></tr>

<tr><th>1</th><th colspan='3'style="text-align:left;">  Rotary switches 1</th><td>0011 1111 1111</td><td>{{Rot_Obs_1}}</td><td>0</td><td>{{Ob_Rot_ObsOFF_1}}</td><td colspan='2'>{{Rotrary_R1}}</td></tr>
<tr><th>2</th><th colspan='3'style="text-align:left;">  Rotary switches 2</th><td>0011 1111 1111</td><td>{{Rot_Obs_2}}</td><td>0</td><td>{{Ob_Rot_ObsOFF_2}}</td><td colspan='2'>{{Rotrary_R2}}</td></tr>
<tr><th>3</th><th colspan='3'style="text-align:left;">  Rotary switches 3</th><td>0011 1111 1111</td><td>{{Rot_Obs_3}}</td><td>0</td><td>{{Ob_Rot_ObsOFF_3}}</td><td colspan='2'>{{Rotrary_R3}}</td></tr>

<tr><th colspan='12'>Monitoring switches</th></tr>
<tr><th rowspan='2'>Sl.No</th><th colspan='3' rowspan='2'>Test Name</th><th>Expected value</th><th>Observed Value</th><th>Expected Value</th><th>Observed Value</th><th colspan='2'rowspan='2'>Result</th></tr>
<tr><th>ON</th><th>ON</th><th>OFF</th><th>OFF</th></tr>

<tr><th>1</th><th colspan='3'style="text-align:left;">  Prep Switch</th><td>1</td><td>{{Ob_Prep}}</td><td>0</td><td>{{Ob_PrepOFF}}</td><td colspan='2'>{{Prep_R}}</td></tr>
<tr><th>2</th><th colspan='3'style="text-align:left;">  Ready Init Switch</th><td>1</td><td>{{Ob_ReadyI}}</td><td>0</td><td>{{Ob_ReadyIOFF}}</td><td colspan='2'>{{RInit_R}}</td></tr>
<tr><th>3</th><th colspan='3'style="text-align:left;">  Abort Switch</th><td>1</td><td>{{Ob_Abort}}</td><td>0</td><td>{{Ob_AbortOFF}}</td><td colspan='2'>{{Abort_R}}</td></tr>


</table>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">

	<h3 style="text-align:center;">DIP-DOP LOOP BACK</h3>
	<tr><th colspan='12'>Discrete Outputs</th></tr>
	<tr><th rowspan='2'>Sl.No</th><th colspan='3' rowspan='2'>Discrete Output channels</th><th>Expected value</th><th>Observed value</th><th>Expected value</th><th>Observed value</th><th colspan='2'rowspan='2'>Result</th></tr>
	<tr><th>ON</th><th>ON</th><th>OFF</th><th>OFF</th></tr>
	<tr><th>1</th><th colspan='3'>channel 1 (C2.21(H)/22(L))</th><td>1</td><td>{{D_Obs_C1}}</td><td>0</td><td>{{D_ObsOFF_C1}}</td> <td colspan='2'>{{Dis_O_Re1}}</td></tr>
	<tr><th>2</th><th colspan='3'>channel 2 (C2.23(H)/24(L))</th><td>1</td><td>{{D_Obs_C2}}</td><td>0</td><td>{{D_ObsOFF_C2}}</td> <td colspan='2'>{{Dis_O_Re2}}</td></tr>
	<tr><th>3</th><th colspan='3'>channel 3 (C2.25(H)/26(L))</th><td>1</td><td>{{D_Obs_C3}}</td><td>0</td><td>{{D_ObsOFF_C3}}</td> <td colspan='2'>{{Dis_O_Re3}}</td></tr>
	<tr><th>4</th><th colspan='3'>channel 4 (C2.27(H)/28(L))</th><td>1</td><td>{{D_Obs_C4}}</td><td>0</td><td>{{D_ObsOFF_C4}}</td> <td colspan='2'>{{Dis_O_Re4}}</td></tr>
	<tr><th>5</th><th colspan='3'>channel 5 (C2.29(H)/30(L))</th><td>1</td><td>{{D_Obs_C5}}</td><td>0</td><td>{{D_ObsOFF_C5}}</td> <td colspan='2'>{{Dis_O_Re5}}</td></tr>

<tr><th colspan='12'>Discrete Inputs</th></tr>
<tr><th rowspan='2'> Sl.No</th><th colspan='3' rowspan='2'>Discrete Input channels</th><th>Expected value</th><th>Observed value</th><th>Expected value</th><th>Observed value</th><th colspan='2'rowspan='2'>Result</th></tr>
		<tr><th>ON</th><th>ON</th><th>OFF</th><th>OFF</th></tr>
	<tr><th>1</th><th colspan='3'>channel 1 (C2.31(H)/33(L))</th><td>1</td><td>{{Obs_ch1}}</td><td>0</td><td>{{ObsOff_ch1}}</td><td colspan='2'>{{Res_I_ch1}}</td></tr>
	<tr><th>2</th><th colspan='3'>channel 2 (C2.32(H)/33(L))</th><td>1</td><td>{{Obs_ch2}}</td><td>0</td><td>{{ObsOff_ch2}}</td><td colspan='2'>{{Res_I_ch2}}</td></tr>
	<tr><th>3</th><th colspan='3'>channel 3 (C2.34(H)/33(L))</th><td>1</td><td>{{Obs_ch3}}</td><td>0</td><td>{{ObsOff_ch3}}</td><td colspan='2'>{{Res_I_ch3}}</td></tr>
	</table>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">
<h3 style = "text-align:center;" >DAC - IC 1&2 CHECKS</h3>
<tr><th rowspan='3'>Expected Voltages</th><th rowspan='3'>Tolerance Range</th><th rowspan='2'colspan='8'> Observed Voltages </th></tr>
<tr>
<tr>
<th>Analog Input ch1</th>
<th>Analog input ch2</th>
<th>Analog 
input ch3</th><th>Analog input ch4</th><th>Analog input ch5</th><th>Analog input ch6</th><th>Analog input ch7</th><th>Analog 
input ch8</th></tr>
<tr><th rowspan='2'>2V</th><th rowspan='2'>1.9V to 2.1V</th><td>{{chC_1}}</td><td>{{chC_2}}</td><td>{{chC_3}}</td><td>{{chC_4}}
</td><td>{{chC_5}}</td><td>{{chC_6}}</td><td>{{chC_7}}</td><td>{{chC_8}}</td></tr> 

<tr><td>{{1passC_1}}</td><td>{{1passC_2}}</td><td>{{1passC_3}}</td><td>{{1passC_4}}</td><td>{{1passC_5}}</td><td>
{{1passC_6}}</td><td>{{1passC_7}}</td><td>{{1passC_8}}</td></tr>

<tr><th rowspan='2'>1.5V</th><th rowspan='2'>1.4V to 1.6V
</th><td>{{2chC_1}}</td><td>{{2chC_2}}</td><td>{{2chC_3}}</td><td>{{2chC_4}}
</td><td>{{2chC_5}}</td><td>{{2chC_6}}</td><td>{{2chC_7}}</td><td>{{2chC_8}}</td></tr>

<tr><td>{{2passC_1}}</td><td>{{2passC_2}}</td><td>{{2passC_3}}</td><td>{{2passC_4}}</td><td>{{2passC_5}}</td><td>
{{2passC_6}}</td><td>{{2passC_7}}</td><td>{{2passC_8}}</td></tr>

<tr><th rowspan='2'>1.0V</th><th rowspan='2'>0.9V to 1.1V

</th><td>{{3chC_1}}</td><td>{{3chC_2}}</td><td>{{3chC_3}}</td><td>{{3chC_4}}
</td><td>{{3chC_5}}</td><td>{{3chC_6}}</td><td>{{3chC_7}}</td><td>{{3chC_8}}</td></tr>

<tr><td>{{3passC_1}}</td><td>{{3passC_2}}</td><td>{{3passC_3}}</td><td>{{3passC_4}}</td><td>{{3passC_5}}</td><td>
{{3passC_6}}</td><td>{{3passC_7}}</td><td>{{3passC_8}}</td></tr>

<tr><th rowspan='2'>0.5</th><th rowspan='2'>0.3V to 0.7V

</th><td>{{4chC_1}}</td><td>{{4chC_2}}</td><td>{{4chC_3}}</td><td>{{4chC_4}}
</td><td>{{4chC_5}}</td><td>{{4chC_6}}</td><td>{{4chC_7}}</td><td>{{4chC_8}}</td></tr>

<tr><td>{{4passC_1}}</td><td>{{4passC_2}}</td><td>{{4passC_3}}</td><td>{{4passC_4}}</td><td>{{4passC_5}}</td><td>
{{4passC_6}}</td><td>{{4passC_7}}</td><td>{{4passC_8}}</td></tr>

<tr><th rowspan='2'>0.0</th><th rowspan='2'>-0.2V to 0.2V

</th><td>{{5chC_1}}</td><td>{{5chC_2}}</td><td>{{5chC_3}}</td><td>{{5chC_4}}
</td><td>{{5chC_5}}</td><td>{{5chC_6}}</td><td>{{5chC_7}}</td><td>{{5chC_8}}</td></tr>

<tr><td>{{5passC_1}}</td><td>{{5passC_2}}</td><td>{{5passC_3}}</td><td>{{5passC_4}}</td><td>{{5passC_5}}</td><td>
{{5passC_6}}</td><td>{{5passC_7}}</td><td>{{5passC_8}}</td></tr>

<tr><th rowspan='2'>-0.5V</th><th rowspan='2'>-0.7V to -0.3V

</th><td>{{6chC_1}}</td><td>{{6chC_2}}</td><td>{{6chC_3}}</td><td>{{6chC_4}}
</td><td>{{6chC_5}}</td><td>{{6chC_6}}</td><td>{{6chC_7}}</td><td>{{6chC_8}}</td></tr>

<tr><td>{{6passC_1}}</td><td>{{6passC_2}}</td><td>{{6passC_3}}</td><td>{{6passC_4}}</td><td>{{6passC_5}}</td><td>
{{6passC_6}}</td><td>{{6passC_7}}</td><td>{{6passC_8}}</td></tr>
<tr><th rowspan='2'>-1.0V</th><th rowspan='2'>-1.1 to -0.9V

</th><td>{{7chC_1}}</td><td>{{7chC_2}}</td><td>{{7chC_3}}</td><td>{{7chC_4}}
</td><td>{{7chC_5}}</td><td>{{7chC_6}}</td><td>{{7chC_7}}</td><td>{{7chC_8}}</td></tr>


<tr><td>{{7passC_1}}</td><td>{{7passC_2}}</td><td>{{7passC_3}}</td><td>{{7passC_4}}</td><td>{{7passC_5}}</td><td>
{{7passC_6}}</td><td>{{7passC_7}}</td><td>{{7passC_8}}</td></tr>

<tr><th rowspan='2'>-1.5V</th><th rowspan='2'>-1.6V to -1.4V

</th><td>{{8chC_1}}</td><td>{{8chC_2}}</td><td>{{8chC_3}}</td><td>{{8chC_4}}
</td><td>{{8chC_5}}</td><td>{{8chC_6}}</td><td>{{8chC_7}}</td><td>{{8chC_8}}</td></tr>

<tr><td>{{8passC_1}}</td><td>{{8passC_2}}</td><td>{{8passC_3}}</td><td>{{8passC_4}}</td><td>{{8passC_5}}</td><td>
{{8passC_6}}</td><td>{{8passC_7}}</td><td>{{8passC_8}}</td></tr>
<tr><th rowspan='2'>-2.0V</th><th rowspan='2'>-2.1V to -1.9V

</th><td>{{9chC_1}}</td><td>{{9chC_2}}</td><td>{{9chC_3}}</td><td>{{9chC_4}}
</td><td>{{9chC_5}}</td><td>{{9chC_6}}</td><td>{{9chC_7}}</td><td>{{9chC_8}}</td></tr>

<tr><td>{{9passC_1}}</td><td>{{9passC_2}}</td><td>{{9passC_3}}</td><td>{{9passC_4}}</td><td>{{9passC_5}}</td><td>
{{9passC_6}}</td><td>{{9passC_7}}</td><td>{{9passC_8}}</td></tr>

</table>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">

	<h3 style="text-align:center;">CHECKSUM</h3>
<tr><th colspan='5'>External Flash Pattern Check</th><th colspan='5'>Result</th></tr>
	<tr><td colspan='5'>Pattern CRC-CheckSum calculated for 512 bytes of pattern 0xA5 in GUI Expected Checksum 0X548A</td>
<td colspan='5'> {{Exter_CCksum}},{{ExtFlash_Result}}</td></tr>
	<tr><td colspan='5'>Pattern CRC-CheckSum calculated for 512 bytes of pattern 0xF5 in GUI Expected Checksum  0XD37F</td>
<td colspan='5'>{{Exter_CCksum_2}},{{ExtFlash_Result_2}}<td></tr>
	
	</table>
<br><br>
<table width="100%" style='text-align:center'>
 <td>Tested By:</td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    <td>Verified By:</td>
</table>


)";
}
//QString ReportTemplates::cntrl_checksum()
//{
//    return R"(
//<br><br><br><br><br>

// <h2 style="text-align:center;">CONTROLLER MODULE USB & CHECKSUM VERIFICATION</h2>
// <table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">
//<tr><th >Project Name</th><td colspan="2">LCA MK-2 AND AMCA</td><th >Sub-System</th><td colspan="2">FTU</td></tr>
//<tr><th >Controller Module P/N</th><td colspan="2">FTU-1104 004 107 08/CTRL_MA-07</td><th>SRU Module Name</th><td colspan="2">Controller</td></tr>
//<tr><th >Test Date</th><td colspan="2">{{DD-MM-YYYY}}</td><th>Controller Module SL NO</th><td colspan="2">{{CM_sl.no}}</td></tr>

//<tr><th>Test Time</th><td colspan="2" >{{HH:MM:SS}}</td><th>ATE Sl. No.</th><td colspan="2">001</td></tr>
//<tr><th >Tested By</th><td colspan="2">{{tested_by}}</td><th>ATE Checksum</th><td colspan="2">{{checksum}}</td> </tr>

//    <tr><th  colspan='10' style="text-align:center;"> USB VERIFICATION</th></tr>
//    <tr><th  >S. No</th><th >Test Name</th><th >Expected</th> <th >Observed</th><th>Result</th></tr>
//	    <tr><th>1</th><td>USB Test</td><td>Status (Ok/Not Ok)</td><td>Ok/Not Ok</td><td>PASS</td></tr>
//    <tr><th  colspan='10' style="text-align:center;"> Checksum </th></tr>
//    <tr><th  >S. No</th><th >Test Name</th><th >Expected</th> <th >Observed</th><th>Result</th></tr>
//	    <tr><th>1</th><td>RS422 Loopback</td><td>{{E_loop}}</td><td>{{O_loop}}</td><td>{{R_1}}</td></tr>
//	    <tr><th>2</th><td>Internal Flash</td><td>{{E_IF}}</td><td>{{O_IF}}</td><td>{{R_2}}</td></tr>
//	    <tr><th>3</th><td>External Flash</td><td>{{E_EF}}</td><td>{{O_EF}}</td><td>{{R_3}}</td></tr>
//	</table>
//<br><br>
//<table style='width: 80%; margin: 0 auto; text-align: center;'>
//<tr>
//    <td><b>Tested By:</b> ____________________</td>
//    <td><b>Verified By:</b> ____________________</td>
//</tr>
//</table>
//)";
//}
//QString ReportTemplates::cntrl_voltagechecks()
//{
//    return R"(
//<br><br><br><br><br>
// <h2 style="text-align:center;">CONTROLLER MODULE VOLTAGE CHECKS</h2>
// <table border="1" cellspacing="0" cellpadding="4" width="100%">
//<tr><th >Project Name</th><td colspan="2">LCA MK-2 AND AMCA</td><th >Sub-System</th><td colspan="2">FTU</td></tr>
//<tr><th >Controller Module P/N</th><td colspan="2">FTU-1104 004 107 08/CTRL_MA-07</td><th>SRU Module Name</th><td colspan="2">Controller</td></tr>
//<tr><th >Test Date</th><td colspan="2">{{DD-MM-YYYY}}</td><th>Controller Module SL NO</th><td colspan="2">{{CM_sl.no}}</td></tr>

//<tr><th>Test Time</th><td colspan="2"colspan="2">HH:MM:SS</td><th>ATE Sl. No.</th><td colspan="2">001</td></tr>
//<tr><th >Tested By</th><td colspan="2">{{tested_by}}</td><th>ATE Checksum</th><td colspan="2">{{checksum}}</td> </tr>

//    <tr><th  colspan='7' style="text-align:center;">Voltage Checks</th></tr>
//    <tr><th  >S. No</th><th>Test Name</th><th >Expected Voltage</th> <th >Observed voltage</th><th>Result</th></tr>
//    <tr><th>1</th><td>3.3V Analogy</td><td>{{E_3.3v_A}}</td><td>{{O_3.3v_A}}</td><td>{{Results_1}}</td></tr>
//    <tr><th>2</th><td>4.6V Analogy</td><td>{{E_4.6v_A}}</td><td>{{O_4.6v_A}}</td><td>{{Results_2}}</td></tr>
//    <tr><th>3</th><td>-4.6V Analogy</td><td>{{E_-4.6v_A}}</td><td>{{O_-4.6v_A}}</td><td>{{Results_3}}</td></tr>

//</table>
//<br><br>
//<table style='width: 80%; margin: 0 auto; text-align: center;'>
//<tr>
//    <td><b>Tested By:</b> ____________________</td>
//    <td><b>Verified By:</b> ____________________</td>
//</tr>
//</table>
//)";
//}

//QString ReportTemplates::cntrl_Abort_Ready_Init_PrepChecks()
//{
//    return R"(
//<br><br><br><br><br>
// <h2 style="text-align:center;">CONTROLLER MODULE ABORT/READY/INIT/PREP CHECKS</h2>
// <table border="1" cellspacing="0" cellpadding="4" width="100%">
//<tr><th >Project Name</th><td colspan="2">LCA MK-2 AND AMCA</td><th >Sub-System</th><td colspan="2">FTU</td></tr>
//<tr><th >Controller Module P/N</th><td colspan="2">FTU-1104 004 107 08/CTRL_MA-07</td><th>SRU Module Name</th><td colspan="2">Controller</td></tr>
//<tr><th >Test Date</th><td colspan="2">{{DD-MM-YYYY}}</td><th>Controller Module SL NO</th><td colspan="2">{{CM_sl.no}}</td></tr>

//<tr><th>Test Time</th><td colspan="2"colspan="2">HH:MM:SS</td><th>ATE Sl. No.</th><td colspan="2">001</td></tr>
//<tr><th >Tested By</th><td colspan="2">{{tested_by}}</td><th>ATE Checksum</th><td colspan="2">{{checksum}}</td> </tr>

//    <tr><th  colspan='7' style="text-align:center;">ABORT/READY INIT/PREP Checks</th></tr>
//    <tr><th  >S. No</th><th colspan='2'>Test Name</th><th >Expected</th> <th >Observed</th><th>Result</th></tr>
//	<tr>
//	    <tr><th rowspan='4'>1</th><td rowspan='4'style="text-align: center;">Abort</td><td>Disc-1</td><td>Ok/Not Ok</td><td>{{O_D1}}</td><td>{{R_D1}}</tr>
//	    <tr><td>Disc-2</td><td>Ok/Not Ok</td><td>{{O_D2}}</td><td>{{R_D2}}</tr>
//  <tr><td>Disc-3</td><td>Ok/Not Ok</td><td>{{O_D3}}</td><td>{{R_D3}}</tr>
// <tr><td>Disc-4</td><td>Ok/Not Ok</td><td>{{O_D4}}</td><td>{{R_D4}}</tr>
//<tr><th>2</th><td style="text-align: center;">Ready INIT</td><td>Disc-5</td><td>Ok/Not Ok</td><td>{{O_D5}}</td><td>{{R_D5}}</tr>
//<tr><th>3</th><td style="text-align: center;">PREP</td><td>STATUS</td><td>Ok/Not Ok</td><td>{{O_S}}</td><td>{{R_s}}</tr>
//<tr><th>4</th><td colspan='2'style="text-align: center;">Rotary Switch-1</td><td>0x3FF</td><td>{{O_rs1}}</td><td>{{R_rs1}}</tr>
//	<tr><th>5</th><td colspan='2'style="text-align: center;">Rotary Switch-2</td><td>0x3FF</td><td>{{O_rs2}}</td><td>{{R_rs2}}</tr>
//<tr><th>6</th><td colspan='2'style="text-align: center;">Rotary Switch-3</td><td>0x3FF</td><td>{{O_rs3}}</td><td>{{R_rs3}}</tr>
//<tr><th>7</th><td colspan='2'style="text-align: center;">Discrete I/P-1<td>Ok/Not Ok</td><td>{{O_Di1}}</td><td>{{R_Di1}}</tr>
//<tr><th>8</th><td colspan='2'style="text-align: center;">Discrete I/P-2<td>Ok/Not Ok</td><td>{{O_Di2}}</td><td>{{R_Di2}}</tr>
//<tr><th>9</th><td colspan='2'style="text-align: center;">Discrete I/P-3<td>Ok/Not Ok</td><td>{{O_Di3}}</td><td>{{R_Di3}}</tr>
//	</table>
//<br><br>
//<table style='width: 80%; margin: 0 auto; text-align: center;'>
//<tr>
//    <td><b>Tested By:</b> ____________________</td>
//    <td><b>Verified By:</b> ____________________</td>
//</tr>
//</table>
//)";
//}
//QString ReportTemplates::cntrl_AnalogChecks()
//{
//    return R"(

//<br><br><br><br><br>
// <h2 style="text-align:center;">CONTROLLER MODULE ANALOG CHECKS</h2>
// <table border="1" cellspacing="0" cellpadding="4" width="100%">
//<tr><th colspan="3">Project Name</th><td colspan="4">LCA MK-2 AND AMCA</td><th colspan="3">Sub-System</th><td colspan="3">FTU</td></tr>
//<tr><th colspan="3">Controller Module P/N</th><td colspan="4">FTU-1104 004 107 08/CTRL_MA-07</td><th colspan="3">SRU Module Name</th><td colspan="3">Controller</td></tr>
//<tr><th colspan="3">Test Date</th><td colspan="4">{{DD-MM-YYYY}}</td><th colspan="3">Controller Module SL NO</th><td colspan="3">{{CM_sl.no}}</td></tr>

//<tr><th colspan="3">Test Time</th><td colspan="4">HH:MM:SS</td><th colspan="3">ATE Sl. No.</th><td colspan="3">001</td></tr>
//<tr><th colspan="3">Tested By</th><td colspan="4">{{tested_by}}</td><th colspan="3">ATE Checksum</th><td colspan="3">{{checksum}}</td> </tr>

//    <tr><th  colspan='13' style="text-align:center;">Analog Checks</th></tr>
//    <tr><th rowspan='3'>S. No</th><th rowspan='3'>Test Name</th><th rowspan='3'>Input</th><th rowspan='3'>Expected</th> <th rowspan='2'colspan='8' >Observed</th><th rowspan='3'>Result</th></tr>
//	<tr>
//	<tr><th>Ch1</th><th>Ch2</th><th>Ch3</th><th>Ch4</th><th>Ch5</th><th>Ch6</th><th>Ch7</th><th>Ch8</th></tr>
//	<tr><th rowspan='3'>1</th><td rowspan='28' style='text-align:center'>ADC to DAC Loopback Analog Channels</td><td>-2V</td><td>{{E_1}}</td><td>{{chA1}}</td><td>{{chA2}}</td>
//	<td>{{chA3}}</td><td>{{chA4}}</td><td>{{chA5}}</td><td>{{chA6}}</td><td>{{chA7}}</td><td>{{chA8}}</td><td rowspan='3'>{{R1}}</td></tr>
//<tr><tr><th colspan='2'>RESULT</td><td>{{r_c1}}</td><td>{{r_c2}}</td><td>{{r_c3}}</td><td>{{r_c4}}</td><td>{{r_c5}}</td><td>{{r_c6}}</td><td>{{r_c7}}</td><td>{{r_c8}}</td></tr>

//<tr><th rowspan='3'>2</th><td>-1.5V</td><td>{{E_2}}</td><td>{{2chA1}}</td><td>{{2chA2}}</td>
//	<td>{{2chA3}}</td><td>{{2chA4}}</td><td>{{2chA5}}</td><td>{{2chA6}}</td><td>{{2chA7}}</td><td>{{2chA8}}</td><td rowspan='3'>{{R2}}</td></tr>
//<tr><tr><th colspan='2'>RESULT</td><td>{{2r_c1}}</td><td>{{2r_c2}}</td><td>{{2r_c3}}</td><td>{{2r_c4}}</td><td>{{2r_c5}}</td><td>{{2r_c6}}</td><td>{{2r_c7}}</td><td>{{2r_c8}}</td></tr>

//<tr><th rowspan='3'>3</th><td>-1V</td><td>{{E_3}}</td><td>{{3chA1}}</td><td>{{3chA2}}</td>
//	<td>{{3chA3}}</td><td>{{3chA4}}</td><td>{{3chA5}}</td><td>{{3chA6}}</td><td>{{3chA7}}</td><td>{{3chA8}}</td><td rowspan='3'>{{R3}}</td></tr>
//<tr><tr><th colspan='2'>RESULT</td><td>{{3r_c1}}</td><td>{{3r_c2}}</td><td>{{3r_c3}}</td><td>{{3r_c4}}</td><td>{{3r_c5}}</td><td>{{3r_c6}}</td><td>{{3r_c7}}</td><td>{{3r_c8}}</td></tr>

//<tr><th rowspan='3'>4</th><td>-0.5V</td><td>{{E_4}}</td><td>{{4chA1}}</td><td>{{4chA2}}</td>
//	<td>{{4chA3}}</td><td>{{4chA4}}</td><td>{{4chA5}}</td><td>{{4chA6}}</td><td>{{4chA7}}</td><td>{{4chA8}}</td><td rowspan='3'>{{R4}}</td></tr>
//<tr><tr><th colspan='2'>RESULT</td><td>{{4r_c1}}</td><td>{{4r_c2}}</td><td>{{4r_c3}}</td><td>{{4r_c4}}</td><td>{{4r_c5}}</td><td>{{4r_c6}}</td><td>{{4r_c7}}</td><td>{{4r_c8}}</td></tr>

//<tr><th rowspan='3'>5</th><td>0V</td><td>{{E_5}}</td><td>{{5chA1}}</td><td>{{5chA2}}</td>
//	<td>{{5chA3}}</td><td>{{5chA4}}</td><td>{{5chA5}}</td><td>{{5chA6}}</td><td>{{5chA7}}</td><td>{{5chA8}}</td><td rowspan='3'>{{R5}}</td></tr>
//<tr><tr><th colspan='2'>RESULT</td><td>{{5r_c1}}</td><td>{{5r_c2}}</td><td>{{5r_c3}}</td><td>{{5r_c4}}</td><td>{{5r_c5}}</td><td>{{5r_c6}}</td><td>{{5r_c7}}</td><td>{{5r_c8}}</td></tr>

//<tr><th rowspan='3'>6</th><td>0.5V</td><td>{{E_6}}</td><td>{{6chA1}}</td><td>{{6chA2}}</td>
//	<td>{{6chA3}}</td><td>{{6chA4}}</td><td>{{6chA5}}</td><td>{{6chA6}}</td><td>{{6chA7}}</td><td>{{6chA8}}</td><td rowspan='3'>{{R6}}</td></tr>
//<tr><tr><th colspan='2'>RESULT</td><td>{{6r_c1}}</td><td>{{6r_c2}}</td><td>{{6r_c3}}</td><td>{{6r_c4}}</td><td>{{6r_c5}}</td><td>{{6r_c6}}</td><td>{{6r_c7}}</td><td>{{6r_c8}}</td></tr>

//<tr><th rowspan='3'>7</th><td>1V</td><td>{{E_7}}</td><td>{{7chA1}}</td><td>{{7chA2}}</td>
//	<td>{{7chA3}}</td><td>{{7chA4}}</td><td>{{7chA5}}</td><td>{{7chA6}}</td><td>{{7chA7}}</td><td>{{7chA8}}</td><td rowspan='3'>{{R7}}</td></tr>
//<tr><tr><th colspan='2'>RESULT</td><td>{{7r_c1}}</td><td>{{7r_c2}}</td><td>{{7r_c3}}</td><td>{{7r_c4}}</td><td>{{7r_c5}}</td><td>{{7r_c6}}</td><td>{{7r_c7}}</td><td>{{7r_c8}}</td></tr>

//<tr><th rowspan='3'>8</th><td>1.5V</td><td>{{E_8}}</td><td>{{8chA1}}</td><td>{{8ch2}}</td>
//	<td>{{8ch3}}</td><td>{{8ch4}}</td><td>{{8ch5}}</td><td>{{8ch6}}</td><td>{{8ch7}}</td><td>{{8ch8}}</td><td rowspan='3'>{{R7}}</td></tr>
//<tr><tr><th colspan='2'>RESULT</td><td>{{8r_c1}}</td><td>{{8r_c2}}</td><td>{{8r_c3}}</td><td>{{8r_c4}}</td><td>{{8r_c5}}</td><td>{{8r_c6}}</td><td>{{8r_c7}}</td><td>{{8r_c8}}</td></tr>

//<tr><th rowspan='3'>9</th><td>2V</td><td>{{E_9}}</td><td>{{9chA1}}</td><td>{{9chA2}}</td>
//	<td>{{9chA3}}</td><td>{{9chA4}}</td><td>{{9chA5}}</td><td>{{9chA6}}</td><td>{{9chA7}}</td><td>{{9chA8}}</td><td rowspan='3'>{{R9}}</td></tr>
//<tr><tr><th colspan='2'>RESULT</td><td>{{9r_c1}}</td><td>{{9r_c2}}</td><td>{{9r_c3}}</td><td>{{9r_c4}}</td><td>{{9r_c5}}</td><td>{{9r_c6}}</td><td>{{9r_c7}}</td><td>{{9r_c8}}</td></tr>

//<br><br><br>

//	</table>
//<br><br>
//<table style='width: 80%; margin: 0 auto; text-align: center;'>
//<tr>
//    <td><b>Tested By:</b> ____________________</td>
//    <td><b>Verified By:</b> ____________________</td>
//</tr>
//</table>

//)";
//}
//-----------------------Display--------------//
#if 0
QString ReportTemplates::FTU_LRUChecks()
{
    return R"(
<br><br><br><br>
<h2 style="text-align:center;">FTU LRU Initial/ Final Check Sheet</h2>
<br>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">
<tr><th >Project Name</th><td colspan="2">LCA MK-2 AND AMCA</td><th colspan="2" >Sub-System</th><td colspan="2">FTU</td></tr>
<tr><th >FTU Module P/N</th><td colspan="2">FTU-1104 004 107 08</td><th colspan="2">FTU SL NO</th><td colspan="2">{{FTU_SLNO}}</td></tr>
<tr><th >Test Date</th><td colspan="2">{{DD-MM-YYYY}}</td><td  colspan="2"></td><td  colspan="2"></td></tr>
<tr><th>Test Time</th><td colspan="2" >HH:MM:SS</td><th colspan="2">ATE Sl. No.</th><td >001</td></tr>
<tr><th >Tested By</th><td colspan="2">{{tested_by}}</td><th colspan="2">ATE Checksum</th><td >{{checksum}}</td> </tr>

    <tr><th >S. No</th><th  colspan="2">Test Name</th><th >Expected</th><th >Observed</th> <th >Result</th></tr>
    <tr><th>1</th><td  colspan="2">I/P Isolation</td><td>{{Expected}}</td><td>{{observed}}</td><td>{{I_isolation_R}}</td></tr>
    <tr><th  colspan="3">I/P Voltage:</th><th> 16V/28V/32V</th><th>Current:</th><th> Result </th></tr>
    <tr><th>2</th><td colspan="2">USB Check</td><td>Ok/Not Ok</td><td>{{I_UC}}</td><td>{{I_UC_R}}</td></tr>
    <tr><th>3</th><td  colspan="2">Internal Flash Checksum</td><td>Checksum</td><td>{{I_IFC}}</td><td>{{I_IFC_R}}</td></tr>

     <tr><th>4</th><td  colspan="2">External Flash Checksum</td><td>Checksum</td><td>{{I_EFC}}</td><td>{{I_EFC_R}}</td></tr>

   <tr><th>5</th><td colspan="2">RS422 Loopback Test</td><td>Ok/Not Ok</td><td>{{I_RLT}}</td><td>{{I_RLT_R}}</td></tr>

<tr><th rowspan='4'>6</th><td rowspan='4'>Abort</td><td>Disc-1 Status</td><td>Ok/Not Ok
</td><td>{{I_Disc1}}</td><td>{{I_Disc1_R}}</td></tr>

<tr><td>Disc-2 Status</td><td>Ok/Not Ok
</td><td>{{I_Disc2}}</td><td>{{I_Disc2_R}}</td></tr>

<tr><td>Disc-3 Status</td><td>Ok/Not Ok
</td><td>{{I_Disc3}}</td><td>{{I_Disc3_R}}</td></tr>

<tr><td>Disc-4 Status</td><td>Ok/Not Ok
</td><td>{{I_Disc4}}</td><td>{{I_Disc4_R}}</td></tr>

<tr><th>7</th><td>Ready INIT</td><td>Disc-5 Status</td><td>Ok/Not Ok
</td><td>{{I_Disc5}}</td><td>{{I_Disc5_R}}</td></tr>

<tr><th>8</th><td>PREP</td><td>Status</td><td>Ok/Not Ok
</td><td>{{I_PREP}}</td><td>{{I_PREP_R}}</td></tr>

<tr><th>9</th><td>Discrete I/P-1</td><td>Status</td><td>Ok/Not Ok
</td><td>{{I_Discrete1}}</td><td>{{I_Discrete1_R}}</td></tr>

<tr><th>10</th><td>Discrete I/P-2</td><td>Status</td><td>Ok/Not Ok
</td><td>{{I_Discrete2}}</td><td>{{I_Discrete2_R}}</td></tr>

<tr><th>11</th><td>Discrete I/P-3</td><td>Status</td><td>Ok/Not Ok
</td><td>{{I_Discrete3}}</td><td>{{I_Discrete3_R}}</td></tr>


</table>
</table>

<br><br>
<table style='width: 80%; margin: 0 auto; text-align: center;'>
<tr>
    <td><b>Tested By:</b> ____________________</td>
    <td><b>Verified By:</b> ____________________</td>
</tr>
</table>

)";
}
QString ReportTemplates::FTU_LRU_AnalogChecks()
{
    return R"(
<br><br><br><br>
 <h2 style="text-align:center;">FTU LRU INITIAL/ FINAL ANALOG CHECK </h2>
 <table border="1" cellspacing="0" cellpadding="4" width="100%">
<tr><th colspan="3">Project Name</th><td colspan="4">LCA MK-2 AND AMCA</td><th colspan="3">Sub-System</th><td colspan="3">FTU</td></tr>
<tr><th colspan="3">FTU Module P/N</th><td colspan="4">1104 004 107 08</td><th colspan="3">FTU SL NO</th><td colspan="3">{{FTU_sl.no}}</td></tr>
<tr><th colspan="3">Test Date</th><td colspan="4">{{DD-MM-YYYY}}</td><th colspan="3"></th><td colspan="3"></td></tr>

<tr><th colspan="3">Test Time</th><td colspan="4">HH:MM:SS</td><th colspan="3">ATE Sl. No.</th><td colspan="3">001</td></tr>
<tr><th colspan="3">Tested By</th><td colspan="4">{{tested_by}}</td><th colspan="3">ATE Checksum</th><td colspan="3">{{checksum}}</td> </tr>

    <tr><th  colspan='13' style="text-align:center;">Analog Checks</th></tr>
    <tr><th rowspan='3'>S. No</th><th rowspan='3'>Test Name</th><th rowspan='3'>Input</th><th rowspan='3'>Expected</th> <th rowspan='2'colspan='8' >Observed</th><th rowspan='3'>Result</th></tr>
	<tr>
	<tr><th>Ch1</th><th>Ch2</th><th>Ch3</th><th>Ch4</th><th>Ch5</th><th>Ch6</th><th>Ch7</th><th>Ch8</th></tr>
	<tr><th rowspan='3'>1</th><td rowspan='28' style='text-align:center'>ADC to DAC Loopback Analog Channels</td><td>-2V</td><td>{{E_1}}</td><td>{{ch1}}</td><td>{{ch2}}</td>
	<td>{{ch3}}</td><td>{{ch4}}</td><td>{{ch5}}</td><td>{{ch6}}</td><td>{{ch7}}</td><td>{{ch8}}</td><td rowspan='3'>{{R1}}</td></tr>
<tr><tr><th colspan='2'>RESULT</td><td>{{r_c1}}</td><td>{{r_c2}}</td><td>{{r_c3}}</td><td>{{r_c4}}</td><td>{{r_c5}}</td><td>{{r_c6}}</td><td>{{r_c7}}</td><td>{{r_c8}}</td></tr>

<tr><th rowspan='3'>2</th><td>-1.5V</td><td>{{E_2}}</td><td>{{2ch1}}</td><td>{{2ch2}}</td>
	<td>{{2ch3}}</td><td>{{2ch4}}</td><td>{{2ch5}}</td><td>{{2ch6}}</td><td>{{2ch7}}</td><td>{{2ch8}}</td><td rowspan='3'>{{R2}}</td></tr>
<tr><tr><th colspan='2'>RESULT</td><td>{{2r_c1}}</td><td>{{2r_c2}}</td><td>{{2r_c3}}</td><td>{{2r_c4}}</td><td>{{2r_c5}}</td><td>{{2r_c6}}</td><td>{{2r_c7}}</td><td>{{2r_c8}}</td></tr>

<tr><th rowspan='3'>3</th><td>-1V</td><td>{{E_3}}</td><td>{{3ch1}}</td><td>{{3ch2}}</td>
	<td>{{3ch3}}</td><td>{{3ch4}}</td><td>{{3ch5}}</td><td>{{3ch6}}</td><td>{{3ch7}}</td><td>{{3ch8}}</td><td rowspan='3'>{{R3}}</td></tr>
<tr><tr><th colspan='2'>RESULT</td><td>{{3r_c1}}</td><td>{{3r_c2}}</td><td>{{3r_c3}}</td><td>{{3r_c4}}</td><td>{{3r_c5}}</td><td>{{3r_c6}}</td><td>{{3r_c7}}</td><td>{{3r_c8}}</td></tr>

<tr><th rowspan='3'>4</th><td>-0.5V</td><td>{{E_4}}</td><td>{{4ch1}}</td><td>{{4ch2}}</td>
	<td>{{4ch3}}</td><td>{{4ch4}}</td><td>{{4ch5}}</td><td>{{4ch6}}</td><td>{{4ch7}}</td><td>{{4ch8}}</td><td rowspan='3'>{{R4}}</td></tr>
<tr><tr><th colspan='2'>RESULT</td><td>{{4r_c1}}</td><td>{{4r_c2}}</td><td>{{4r_c3}}</td><td>{{4r_c4}}</td><td>{{4r_c5}}</td><td>{{4r_c6}}</td><td>{{4r_c7}}</td><td>{{4r_c8}}</td></tr>

<tr><th rowspan='3'>5</th><td>0V</td><td>{{E_5}}</td><td>{{5ch1}}</td><td>{{5ch2}}</td>
	<td>{{5ch3}}</td><td>{{5ch4}}</td><td>{{5ch5}}</td><td>{{5ch6}}</td><td>{{5ch7}}</td><td>{{5ch8}}</td><td rowspan='3'>{{R5}}</td></tr>
<tr><tr><th colspan='2'>RESULT</td><td>{{5r_c1}}</td><td>{{5r_c2}}</td><td>{{5r_c3}}</td><td>{{5r_c4}}</td><td>{{5r_c5}}</td><td>{{5r_c6}}</td><td>{{5r_c7}}</td><td>{{5r_c8}}</td></tr>

<tr><th rowspan='3'>6</th><td>0.5V</td><td>{{E_6}}</td><td>{{6ch1}}</td><td>{{6ch2}}</td>
	<td>{{6ch3}}</td><td>{{6ch4}}</td><td>{{6ch5}}</td><td>{{6ch6}}</td><td>{{6ch7}}</td><td>{{6ch8}}</td><td rowspan='3'>{{R6}}</td></tr>
<tr><tr><th colspan='2'>RESULT</td><td>{{6r_c1}}</td><td>{{6r_c2}}</td><td>{{6r_c3}}</td><td>{{6r_c4}}</td><td>{{6r_c5}}</td><td>{{6r_c6}}</td><td>{{6r_c7}}</td><td>{{6r_c8}}</td></tr>

<tr><th rowspan='3'>7</th><td>1V</td><td>{{E_7}}</td><td>{{7ch1}}</td><td>{{7ch2}}</td>
	<td>{{7ch3}}</td><td>{{7ch4}}</td><td>{{7ch5}}</td><td>{{7ch6}}</td><td>{{7ch7}}</td><td>{{7ch8}}</td><td rowspan='3'>{{R7}}</td></tr>
<tr><tr><th colspan='2'>RESULT</td><td>{{7r_c1}}</td><td>{{7r_c2}}</td><td>{{7r_c3}}</td><td>{{7r_c4}}</td><td>{{7r_c5}}</td><td>{{7r_c6}}</td><td>{{7r_c7}}</td><td>{{7r_c8}}</td></tr>

<tr><th rowspan='3'>8</th><td>1.5V</td><td>{{E_8}}</td><td>{{8ch1}}</td><td>{{8ch2}}</td>
	<td>{{8ch3}}</td><td>{{8ch4}}</td><td>{{8ch5}}</td><td>{{8ch6}}</td><td>{{8ch7}}</td><td>{{8ch8}}</td><td rowspan='3'>{{R7}}</td></tr>
<tr><tr><th colspan='2'>RESULT</td><td>{{8r_c1}}</td><td>{{8r_c2}}</td><td>{{8r_c3}}</td><td>{{8r_c4}}</td><td>{{8r_c5}}</td><td>{{8r_c6}}</td><td>{{8r_c7}}</td><td>{{8r_c8}}</td></tr>

<tr><th rowspan='3'>9</th><td>2V</td><td>{{E_9}}</td><td>{{9ch1}}</td><td>{{9ch2}}</td>
	<td>{{9ch3}}</td><td>{{9ch4}}</td><td>{{9ch5}}</td><td>{{9ch6}}</td><td>{{9ch7}}</td><td>{{9ch8}}</td><td rowspan='3'>{{R9}}</td></tr>
<tr><tr><th colspan='2'>RESULT</td><td>{{9r_c1}}</td><td>{{9r_c2}}</td><td>{{9r_c3}}</td><td>{{9r_c4}}</td><td>{{9r_c5}}</td><td>{{9r_c6}}</td><td>{{9r_c7}}</td><td>{{9r_c8}}</td></tr>

<br><br><br>


	</table>
<br><br>
<table style='width: 80%; margin: 0 auto; text-align: center;'>
<tr>
    <td><b>Tested By:</b> ____________________</td>
    <td><b>Verified By:</b> ____________________</td>
</tr>
</table>


)";
}
QString ReportTemplates::FTU_LRU_ESS_QTChecks()
{
    return R"(
<br><br><br><br>
<h2 style="text-align:center;">FTU LRU ESS/QT CHECK </h2>
<br>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">
<tr><th >Project Name</th><td colspan="2">LCA MK-2 AND AMCA</td><th colspan="2" >Sub-System</th><td colspan="2">FTU</td></tr>
<tr><th >FTU Module P/N</th><td colspan="2">FTU-1104 004 107 08</td><th colspan="2">FTU SL NO</th><td colspan="2">{{FTU_SLNO}}</td></tr>
<tr><th >Test Date</th><td colspan="2">{{DD-MM-YYYY}}</td><td  colspan="2"></td><td  colspan="2"></td></tr>
<tr><th>Test Time</th><td colspan="2" >HH:MM:SS</td><th colspan="2">ATE Sl. No.</th><td >001</td></tr>
<tr><th >Tested By</th><td colspan="2">{{tested_by}}</td><th colspan="2">ATE Checksum</th><td >{{checksum}}</td> </tr>

    <tr><th >S. No</th><th  colspan="2">Test Name</th><th >Expected</th><th >Observed</th> <th >Result</th></tr>
    <tr><th>1</th><td  colspan="2">I/P Isolation</td><td>{{Expected}}</td><td>{{observed}}</td><td>{{I_isolation_R}}</td></tr>
    <tr><th  colspan="3">I/P Voltage:</th><th>28V</th><th>Current:</th><th> Result </th></tr>
    <tr><th>2</th><td  colspan="2">Internal Flash Checksum</td><td>Checksum</td><td>{{I_IFC}}</td><td>{{I_IFC_R}}</td></tr>


   <tr><th>3</th><td colspan="2">RS422 Loopback Test</td><td>Ok/Not Ok</td><td>{{I_RLT}}</td><td>{{I_RLT_R}}</td></tr>

<tr><th rowspan='4'>4</th><td rowspan='4'>Abort</td><td>Disc-1 Status</td><td>Ok/Not Ok
</td><td>{{I_Disc1}}</td><td>{{I_Disc1_R}}</td></tr>

<tr><td>Disc-2 Status</td><td>Ok/Not Ok
</td><td>{{I_Disc2}}</td><td>{{I_Disc2_R}}</td></tr>

<tr><td>Disc-3 Status</td><td>Ok/Not Ok
</td><td>{{I_Disc3}}</td><td>{{I_Disc3_R}}</td></tr>

<tr><td>Disc-4 Status</td><td>Ok/Not Ok
</td><td>{{I_Disc4}}</td><td>{{I_Disc4_R}}</td></tr>

<tr><th>5</th><td>Ready INIT</td><td>Disc-5 Status</td><td>Ok/Not Ok
</td><td>{{I_Disc5}}</td><td>{{I_Disc5_R}}</td></tr>

<tr><th>6</th><td>PREP</td><td>Status</td><td>Ok/Not Ok
</td><td>{{I_PREP}}</td><td>{{I_PREP_R}}</td></tr>

<tr><th>7</th><td>Discrete I/P-1</td><td>Status</td><td>Ok/Not Ok
</td><td>{{I_Discrete1}}</td><td>{{I_Discrete1_R}}</td></tr>

<tr><th>8</th><td>Discrete I/P-2</td><td>Status</td><td>Ok/Not Ok
</td><td>{{I_Discrete2}}</td><td>{{I_Discrete2_R}}</td></tr>

<tr><th>9</th><td>Discrete I/P-3</td><td>Status</td><td>Ok/Not Ok
</td><td>{{I_Discrete3}}</td><td>{{I_Discrete3_R}}</td></tr>


</table>

<br><br>
<table style='width: 80%; margin: 0 auto; text-align: center;'>
<tr>
    <td><b>Tested By:</b> ____________________</td>
    <td><b>Verified By:</b> ____________________</td>
</tr>
</table>
)";
--------------
QString ReportTemplates::voltageHtml()
{
    return R"(
     <br><br>  <h2 style="text-align:center;">DCDC MODULE VOLTAGE CHECKS</h2>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">
<tr><th colspan="2">Project Name</th><td colspan="2">LCA MK-2 AND AMCA</td><th >Sub-System</th><td colspan="2">FTU</td></tr>
<tr><th colspan="2">DCDC Module P/N</th><td colspan="2">FTU-1104 004 107 08 / DCDC_MA-08</td><th >SRU Module Name</th><td colspan="2">DC-DC</td></tr>
<tr><th colspan="2">Test Date</th><td>DD-MM-YYYY</td><th colspan="2">DC-DC Module SL NO</th><td colspan="2">{{dc_sl.no}}</td></tr>
<tr><th colspan="2">Test Time</th><td>HH:MM:SS</td><th colspan="2">ATE Sl. No.</th><td colspan="2">001</td></tr>
<tr><th colspan="2">Tested By</th><td>{{tested_by}}</td><th colspan="2">ATE Checksum</th><td colspan="2" >{{checksum}}</td>  </tr>
</table>
<h3 style="text-align:center;">Voltage Checks</h3>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">

<tr><th colspan='2'> </th><td colspan='2'><b><center>Voltage</center></b></td><td colspan='2'><b>Current</b></td></tr>

<tr><th rowspan='3' colspan='2'>INPUT</th><th colspan='2'>16V</th><td colspan='2'>{{v16_current}}</td></tr>
<tr><th colspan='2'>28V</th><td colspan='2'>{{v28_current}}</td></tr>
<tr><th colspan='2'>32V</th><td colspan='2'>{{v32_current}}</td></tr>

<tr><th>S. No</th><th>Input</th><th>Test Name</th><th>Expected</th><th>Observed</th><th>Result</th></tr>
<tr><td>1</td><td>16V</td><td rowspan='3'><b>3.3V O/P Voltage</b></td><td rowspan='3'>3.3±0.25V</td><td>{{obs16_1}}</td><td>{{obs1_1_result}}</td></tr>
<tr><td>2</td><td>28V</td><td>{{obs28_1}}</td><td>{{obs2_1_result}}</td></tr>
<tr><td>3</td><td>32V</td><td>{{obs32_1}}</td><td>{{obs3_1_result}}</td></tr>

<tr><td>4</td><td>16V</td><td rowspan='3'><b>+5V O/P Voltage</b></td><td rowspan='3'>+5±0.25V</td><td>{{obs16_2}}</td><td>{{obs1_2_result}}</td></tr>
<tr><td>5</td><td>28V</td><td>{{obs28_2}}</td><td>{{obs2_2_result}}</td></tr>
<tr><td>6</td><td>32V</td><td>{{obs32_2}}</td><td>{{obs3_2_result}}</td></tr>

<tr><td>7</td><td>16V</td><td rowspan='3'><b>-5V O/P Voltage</b></td><td rowspan='3'>-5±0.25V</td><td>{{obs16_3}}</td><td>{{obs1_3_result}}</td></tr>
<tr><td>8</td><td>28V</td><td>{{obs28_3}}</td><td>{{obs2_3_result}}</td></tr>
<tr><td>9</td><td>32V</td><td>{{obs32_3}}</td><td>{{obs3_3_result}}</td></tr>
</table>

<br><br>
<table style='width:100%; text-align: center;'>
<tr>
    <td><b>Tested By:</b> </td><br><br><br><br>
    <td><b>Verified By:</b> </td>
</tr></table>
)";
}
QString ReportTemplates::loadHtml()
{
    return R"(
     <br><br>  <h2 style="text-align:center;">DC-DC MODULE LOAD CHECKS</h2>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">

<tr><th colspan="2">Project Name</th><td colspan="2">LCA MK-2 AND AMCA</td><th >Sub-System</th><td colspan="2">FTU</td></tr>
<tr><th colspan="2">DCDC Module P/N</th><td colspan="2">FTU-1104 004 107 08 / DCDC_MA-08</td><th >SRU Module Name</th><td colspan="2">DC-DC</td></tr>
<tr><th colspan="2">Test Date</th><td>DD-MM-YYYY</td><th colspan="2">DC-DC Module SL NO</th><td colspan="2">{{dc_sl.no}}</td></tr>
<tr><th colspan="2">Test Time</th><td>HH:MM:SS</td><th colspan="2">ATE Sl. No.</th><td colspan="2">001</td></tr>
<tr><th colspan="2">Tested By</th><td>{{tested_by}}</td><th colspan="2">ATE Checksum</th><td colspan="2" >{{checksum}}</td>  </tr>
</table>
<h3 style="text-align:center;">Load Checks</h3>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">

<tr><th rowspan='3' colspan='2'>INPUT Voltage</th><th >Expected</th><th>Observed</th> <th colspan='3'>Load Range</th><th>Expected</th><th>Observed</th></tr>
<tr><th rowspan='2'>28V</th><td  rowspan='2'>{{ v28_i/p_O}}</td><th colspan='3'>Current 10% Load</th><th>{{E_10%_L}}</th><th>{{O_10%_L}}</th></tr>
<tr><th colspan='3'>Current 100% Load</th><td>{{E_100%_L}}</td><th> {{O_100%_L}} </th> </tr>
<tr><th rowspan='2'>S. No</th><th  colspan='3'rowspan='2'>Test Name</th><th colspan='2'>Expected Voltage</th><th colspan='2'>Observed voltage</th><th rowspan='2'>Result (PASS/FAIL)</th></tr>
<tr><th>10% Load</th><th>100% Load</th><th >10% Load</th><th>100% Load</th></tr>
<tr><th>1</th><td colspan='2' rowspan='2'>3.3V O/P</td><td><b>Voltage</b></td><td>3.3V±0.25V</td><td>{{e100_L_V}}</td><td>{{ov_10l}}</td><td>{{ov_100}}</td> <td>{{res_v1}}</td></tr>
<tr><th>2</th><td>Current</td><td>{{v3.3_I_10L}}</td><td>{{v3.3_I_100L}}</td><td>{{oi_10l}}</td><td>{{oi_100}}</td><td>{{res_I1}}</td></tr>
<tr><th>3</th><td colspan='2' rowspan='2'>+5V O/P</td><td><b>Voltage</b></td><td>+5V±0.25V</td><td>{{e100_L_V}}</td><td>{{ov_10l}}</td><td>{{ov_100}}</td> <td>{{res_v2}}</td></tr>
<tr><th>4</th><td>Current</td><td>{{v+5_I_10L}}</td><td>{{v+5_I_100L}}</td><td>{{oi_10l}}</td><td>{{oi_100}}</td><td>{{res_I2}}</td></tr>
<tr><th>5</th><td colspan='2' rowspan='2'>-5V O/P</td><td><b>Voltage</b></td><td>-5V±0.25V</td><td>{{e100_L_V}}</td><td>{{ov_10l}}</td><td>{{ov_100}}</td> <td>{{res_v3}}</td></tr>
<tr><th>6</th><td>Current</td><td>{{v-5_I_10L}}</td><td>{{v-5_I_100L}}</td><td>{{oi_10l}}</td><td>{{oi_100}}</td><td>{{res_I3}}</td></tr>
</table>

<br><br><br><br>

<table style='width: 80%; text-align: center;'>
<tr>
    <td><b>Tested By:</b> ____________________</td><br><br>
    <td><b>Verified By:</b> ____________________</td><br><br>
</tr></table>

)";
}
QString ReportTemplates::RippleHtml()
{
    return R"(
<br><br>
 <h2 style="text-align:center;">DC-DC MODULE RIPPLE CHECKS</h2>
<table border="1" cellspacing="0" cellpadding="4" width="100%" style="text-align: center;">
<tr><th colspan="3">Project Name</th><td colspan="2">LCA MK-2 AND AMCA</td><th colspan="2" >Sub-System</th><td colspan="3">FTU</td></tr>
<tr><th colspan="3">DCDC Module P/N</th><td colspan="2">FTU-1104 004 107 08 / DCDC_MA-08</td><th colspan="2">SRU Module Name</th><td colspan="2">DC-DC</td></tr>
<tr><th colspan="3">Test Date</th><td colspan="2">DD-MM-YYYY</td><th colspan="2">DC-DC Module SL NO</th><td colspan="2">{{dc_sl.no}}</td></tr>
<tr><th colspan="3">Test Time</th><td colspan="2">HH:MM:SS</td><th colspan="2">ATE Sl. No.</th><td colspan="2">001</td></tr>
<tr><th colspan="3">Tested By</th><td  colspan="2">{{tested_by}}</td><th colspan="2">ATE Checksum</th><td colspan="2" >{{checksum}}</td>  </tr>


<tr><th  colspan='10' style="text-align:center;">Ripple Checks</th></tr>
<tr><th rowspan='2' colspan='3'>INPUT Voltage</th><td rowspan='2' >{{i/p_volt}}</td> <th rowspan='2'colspan='2'>Input Current</th><th>10% Load</th><td>{{i/p_I_10L}}</td></tr>
<tr><th>100% Load</th><td>{{i/p_I_100L}}</td></tr>
<tr><th rowspan='2' >S. No</th><th rowspan='2'colspan='2'>Test Name</th><th colspan='2'>Ripple Voltage Expected</th><th colspan='2'>Ripple Voltage Expected</th><th rowspan='2'>Result (PASS/FAIL)</th></tr>
<tr><th>No Load</th><th>100% Load</th><th >No Load</th><th>100% Load</th></tr>
<tr><th>1</th><td>3.3V O/P</td><td><b>Voltage</b><td>{{o3.3v_E_nol}}</td><td>{{o3.3v_E_load}}</td><td>{{v3.3_O_nol}}</td><td>{{O_3.3v_l}}</td><td>{{o/p_resl_3.3}}</td></tr>
<tr><th>2</th><td>+5V O/P</td><td><b>Voltage</b><td>{{o+5v_E_nol}}</td><td>{{o+5v_E_load }}</td><td>{{v+5_O_nol}}</td><td>{{O_+5v_l }}</td><td>{{o/p_resl_+5}}</td></tr>
<tr><th>3</th><td>-5V O/P</td><td><b>Voltage</b><td>{{o-5v_E_nol}}</td><td>{{o-5v_E_load }}</td><td>{{v-5_O_nol}}</td><td>{{O_-5v_l }}</td><td>{{o/p_resl_-5}}</td></tr>


</table>
<br><br><br>

<p style="text-align:center;">
  <b>Tested By: ____________ &nbsp;&nbsp;&nbsp;&nbsp;<b> Verified By: ____________
</p><br><br><br>
)";
}
#endif
QString ReportTemplates::populateTemplate(const QString &templateHtml,
                                          const QMap<QString, QString> &params)
{
    QString result = templateHtml;
    for (auto it = params.begin(); it != params.end(); ++it) {
        result.replace("{{" + it.key() + "}}", it.value());
    }
    return result;
}
