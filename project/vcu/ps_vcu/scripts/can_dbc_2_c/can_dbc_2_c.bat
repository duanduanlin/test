@echo off

::切换至当前目录
cd.

::经典CAN / CANFD DBC自动生成C语言代码
python -m cantools  generate_c_source -e "gb18030" PSA-CAN.dbc --node VCU

pause
